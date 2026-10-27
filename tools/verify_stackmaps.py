"""Static StackMapTable validator for every class in a jar.

Parses each class file's Code attribute's StackMapTable (JVMS 4.7.9) and
verifies:
  * every verification_type_info tag is in 0..8
  * ITEM_Object (7) cp index points at a CONSTANT_Class entry
  * ITEM_Uninitialized (8) offset is inside the method's code
  * frame offsets stay monotonic and within the code length

Fails with exit code 1 and prints details when anything is off.
"""
import struct
import sys
import zipfile


class Reader:
    def __init__(self, data):
        self.d = data
        self.i = 0

    def u1(self):
        v = self.d[self.i]
        self.i += 1
        return v

    def u2(self):
        v = struct.unpack_from(">H", self.d, self.i)[0]
        self.i += 2
        return v

    def u4(self):
        v = struct.unpack_from(">I", self.d, self.i)[0]
        self.i += 4
        return v

    def skip(self, n):
        self.i += n

    def need(self, n):
        if self.i + n > len(self.d):
            raise IndexError(f"reader needs {n} bytes at offset {self.i} "
                             f"of {len(self.d)}-byte attribute")


U8_TAGS = {1: (4, "utf8"), 3: (4, "int"), 4: (4, "float"), 5: (8, "long"),
           6: (8, "double"), 7: (2, "class"), 8: (2, "string"),
           9: (4, "fieldref"), 10: (4, "methodref"), 11: (4, "ifmethodref"),
           12: (4, "nameandtype"), 15: (3, "methodhandle"), 16: (2, "methodtype"),
           17: (4, "dynamic"), 18: (4, "invokedynamic"), 19: (2, "module"),
           20: (2, "package")}


def parse_constant_pool(r):
    count = r.u2()
    pool = [None] * count
    i = 1
    while i < count:
        tag = r.u1()
        if tag == 1:
            ln = r.u2()
            pool[i] = (1, r.d[r.i:r.i + ln])
            r.skip(ln)
        elif tag in (5, 6):
            pool[i] = (tag, None)
            r.skip(8)
            i += 1
        else:
            ln, name = U8_TAGS[tag]
            pool[i] = (tag, r.d[r.i:r.i + ln])
            r.skip(ln)
        i += 1
    return pool


def utf8(pool, idx):
    if idx is None or idx >= len(pool) or pool[idx] is None or pool[idx][0] != 1:
        return None
    return pool[idx][1].decode("utf-8", "replace")


def _types(r, count, code_len, pool, where, problems):
    for _ in range(count):
        vt = r.u1()
        if vt == 7:
            hidx = r.u2()
            if hidx >= len(pool) or pool[hidx] is None or pool[hidx][0] != 7:
                problems.append(
                    f"    {where}: ITEM_Object cpool index {hidx} "
                    f"does not point at a CONSTANT_Class")
        elif vt == 8:
            hidx = r.u2()
            if hidx >= code_len:
                problems.append(
                    f"    {where}: ITEM_Uninitialized new_object offset {hidx} "
                    f"exceeds code length {code_len}")
        elif vt > 8:
            problems.append(f"    {where}: BAD verification_type tag {vt}")


def parse_stackmap(pool, where, code_len, data, problems):
    r = Reader(data)
    n = r.u2()
    off = -1
    for fi in range(n):
        tag = r.u1()
        where_f = f"{where} frame #{fi}"
        if 0 <= tag <= 63:
            off += tag + 1
        elif 64 <= tag <= 127:
            off += tag - 64 + 1
            _types(r, 1, code_len, pool, where_f, problems)
        elif tag == 247:
            off += r.u2() + 1
            _types(r, 1, code_len, pool, where_f, problems)
        elif 248 <= tag <= 250:
            off += r.u2() + 1
        elif tag == 251:
            off += r.u2() + 1
        elif 252 <= tag <= 254:
            off += r.u2() + 1
            _types(r, tag - 251, code_len, pool, where_f, problems)
        elif tag == 255:
            off += r.u2() + 1
            _types(r, r.u2(), code_len, pool, where_f, problems)
            _types(r, r.u2(), code_len, pool, where_f, problems)
        else:
            problems.append(f"    {where_f}: BAD stack map frame tag {tag}")
            return
        if off >= code_len:
            problems.append(
                f"    {where_f}: offset {off} exceeds code length {code_len}")


def inspect_class(data, problems):
    r = Reader(data)
    if r.u4() != 0xCAFEBABE:
        return "not a class file"
    r.u2()  # minor
    r.u2()  # major
    pool = parse_constant_pool(r)
    r.u2()  # access
    r.u2()  # this
    r.u2()  # super
    ic = r.u2()
    r.skip(2 * ic)
    for kind in ("field", "method"):
        members = r.u2()
        for _ in range(members):
            r.u2()  # access
            mname = utf8(pool, r.u2())
            mdesc = utf8(pool, r.u2())
            for _ in range(r.u2()):
                aname = utf8(pool, r.u2())
                alen = r.u4()
                body = r.d[r.i:r.i + alen]
                r.skip(alen)
                if aname == "Code":
                    cr = Reader(body)
                    cr.u2()
                    cr.u2()
                    clen = cr.u4()
                    cr.skip(clen)
                    cr.skip(8 * cr.u2())
                    for _ in range(cr.u2()):
                        aname2 = utf8(pool, cr.u2())
                        alen2 = cr.u4()
                        body2 = body[cr.i:cr.i + alen2]
                        cr.skip(alen2)
                        if aname2 == "StackMapTable":
                            parse_stackmap(pool, f"{mname}{mdesc}", clen,
                                           body2, problems)
    return None


def check_jar(path):
    problems = []
    classes = 0
    with zipfile.ZipFile(path) as zf:
        for entry in zf.namelist():
            if not entry.endswith(".class"):
                continue
            data = zf.read(entry)
            classes += 1
            try:
                inspect_class(data, problems)
            except Exception as exc:
                problems.append(f"    {entry}: MALFORMED ({exc})")
    print(f"{path}: {classes} classes checked")
    if problems:
        print(f"  PROBLEMS ({len(problems)}):")
        for p in problems[:40]:
            print(p)
        return False
    print("  ok")
    return True


if __name__ == "__main__":
    ok = True
    for arg in sys.argv[1:]:
        ok = check_jar(arg) and ok
    sys.exit(0 if ok else 1)
