#include "ConfigurationPersistence.hpp"
#include "ByteStrings.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>

namespace reconstruction::configuration {
namespace {
template<class T> T load(const void *base, std::size_t offset) {
    T value; std::memcpy(&value, static_cast<const std::uint8_t *>(base)+offset,sizeof value); return value;
}
template<class T> void store(void *base,std::size_t offset,T value) {
    std::memcpy(static_cast<std::uint8_t *>(base)+offset,&value,sizeof value);
}
Word address(const void *value) { return reinterpret_cast<Word>(value); }
const std::uint16_t *wideConstant(const Dependencies &d,std::size_t offset) {
    return reinterpret_cast<const std::uint16_t *>(d.image+offset);
}
}
std::uint32_t initializePath_4c590(std::uint16_t **path,const Dependencies &d) {
    const auto *base=d.environment(d.context,wideConstant(d,0x156fcc));
    if(!base || load<std::uint16_t>(base,0)==0) return 0x3ec;
    const auto length=d.wideLength(d.context,base);
    const auto capacity=length+1;
    auto *copy=static_cast<std::uint16_t *>(d.allocateZeroed(d.context,capacity,2));
    if(!copy) return 0x3ed;
    d.copyWide(d.context,copy,capacity,base,length);
    *path=copy;
    return 0;
}
std::uint32_t formatPath_4c6a0(std::uint16_t *destination,std::uint64_t capacity,
    const std::uint16_t *format,const Word *argumentWords,const Dependencies &d) {
    const auto options=*d.formatOptions(d.context);
    return d.formatWide(d.context,options,destination,capacity,format,0,argumentWords);
}
std::uint32_t appendPath_4c610(std::uint16_t **path,const std::uint8_t *component,const Dependencies &d) {
    const auto oldLength=d.wideLength(d.context,*path);
    const auto componentLength=recovered_string_length_ab840(component);
    auto *next=static_cast<std::uint16_t *>(d.allocateZeroed(d.context,0x105,2));
    if(!next) return 0x3ed;
    const auto capacityWord=std::uint32_t(oldLength)+std::uint32_t(componentLength)+2u;
    const auto capacity=std::uint64_t(std::int64_t(std::bit_cast<std::int32_t>(capacityWord)));
    const Word arguments[]{address(*path),address(component)};
    // Native ignores the formatter's status and frees the reloaded old pointer.
    formatPath_4c6a0(next,capacity,wideConstant(d,0x156fe4),arguments,d);
    d.release(d.context,*path);
    *path=next;
    return 0;
}
void parentPath_4c700(std::uint16_t **path,const Dependencies &d) {
    auto *base=reinterpret_cast<std::uint8_t *>(*path);
    auto offset=d.wideLength(d.context,*path)*2;
    do {
        if(load<std::uint16_t>(base,std::size_t(offset))==0x5c) {
            base+=offset;
            break;
        }
        offset-=2;
    } while(offset!=0);
    const std::uint16_t zero=0;
    std::memcpy(base,&zero,2);
}
std::uint32_t ensureDirectory_4c740(std::uint16_t **path,const Dependencies &d) {
    if(d.createDirectory(d.context,*path,0)!=0) return 0;
    return d.lastError(d.context)==0xb7 ? 0 : 0x3f6;
}
std::uint32_t deletePath_4c780(std::uint16_t **path,const Dependencies &d) {
    return d.deleteFile(d.context,*path) ? 0 : 0x3f3;
}
std::uint32_t readText_4ca30(std::uint16_t **path,std::uint8_t **text,const Dependencies &d) {
    const auto handle=d.openFile(d.context,*path,0x80000000,1,0,3,0x80,0);
    if(handle==~Word{}) return 0x3f0;
    const auto length=d.fileSize(d.context,handle,0);
    if(length==0xffffffffu) { d.close(d.context,handle);return 0x3ef; }
    auto *buffer=reinterpret_cast<std::uint8_t *>(d.calls(0x13cf80,std::uint32_t(length+1u)));
    // Allocation failure bypasses the close path in this build.
    if(!buffer) return 0x3ed;
    std::uint32_t result=0;
    if(length) {
        const auto reader=d.readService(d.context,0x100beec);
        std::uint64_t total=0;
        std::uint32_t read;
        do {
            if(!d.read(d.context,reader,handle,buffer+total,length-std::uint32_t(total),&read,0)) {
                result=0x3f1;break;
            }
            if(read==0) { result=0x3fa;break; }
            total+=read;
        } while(total<length);
    }
    if(result) d.calls(0x13cf70,address(buffer));
    else { buffer[length]=0;*text=buffer; }
    d.close(d.context,handle);
    return result;
}
std::uint32_t writeText_4cc40(std::uint16_t **path,const std::uint8_t *text,
    std::uint8_t replace,const Dependencies &d) {
    const auto handle=d.openFile(d.context,*path,0x40000000,0,0,std::uint32_t(replace)+1,0x80,0);
    if(handle==~Word{}) return d.lastError(d.context)==0x50 ? 0x3f4 : 0x3f0;
    const auto length=recovered_string_length_ab840(text);
    const auto writer=d.writeService(d.context,0x1003f20);
    std::uint64_t writtenTotal=0;
    std::uint32_t result=0;
    std::uint32_t written=d.incomingWriteCount;
    // A successful zero-byte write retries forever in this build. No invented
    // progress guard changes that behavior; verification uses bounded tooling.
    while(writtenTotal<length) {
        const auto success=d.write(d.context,writer,handle,text+writtenTotal,
            std::uint32_t(length)-std::uint32_t(writtenTotal),&written,0);
        writtenTotal+=written;
        if(success==0) { result=0x3f2; break; }
    }
    d.close(d.context,handle);
    return result;
}
void releasePath_4cd20(std::uint16_t **path,const Dependencies &d) {
    d.release(d.context,*path);
    *path=nullptr;
}
std::uint8_t serializeModule_ce20(Word root,const std::uint8_t *descriptor,const Dependencies &d) {
    const auto object=d.calls(0x4f480,root,load<Word>(descriptor,0));
    auto flags=load<std::uint32_t>(descriptor,0x18);
    if(!(flags&2) && load<std::uint8_t>(descriptor,0x14)==1) {
        if(!d.calls(0x4ed40,object,address(d.image+0x13ec65),1)) return 0;
        flags=load<std::uint32_t>(descriptor,0x18);
    }
    if(!(flags&1)) {
        const auto bind=load<std::uint32_t>(descriptor,0x1c);
        if(bind) {
            if(!d.calls(0x4eeb0,object,address(d.image+0x13ec6a),std::bit_cast<Word>(double(bind)))) return 0;
            flags=load<std::uint32_t>(descriptor,0x18);
        }
        if(!(flags&8) && load<std::uint8_t>(descriptor,0x20)==1)
            if(!d.calls(0x4ed40,object,address(d.image+0x13ec71),1)) return 0;
    }
    const auto callback=load<Word>(descriptor,0x200);
    if(!callback) return 1;
    SettingsContext settings{reinterpret_cast<void *>(object),1,0,{0,0,0}};
    d.calls(callback,address(&settings));
    return settings.error^std::uint8_t{1};
}
Word profileRecords_eea0(const std::uint8_t *profiles,std::uint64_t *count) {
    *count=load<Word>(profiles,0);
    return *count ? load<Word>(profiles,0x10) : 0;
}
Word serializeConfiguration_bc70(const std::uint8_t *registry,const std::uint8_t *profiles,const Dependencies &d) {
    const auto root=d.calls(0x4f590);
    if(!root) return 0;
    Word text=0;
    auto limit=load<Word>(registry,8);
    for(Word index=0;index<limit;++index) {
        const auto table=load<Word>(registry,0);
        const auto descriptor=load<Word>(reinterpret_cast<const void *>(table),std::size_t(index*8));
        if(load<std::uint8_t>(reinterpret_cast<const void *>(descriptor),0x18)&0x10) {
            if(!serializeModule_ce20(root,reinterpret_cast<const std::uint8_t *>(descriptor),d)) goto cleanup;
            limit=load<Word>(registry,8);
        }
    }
    {
        const auto array=d.calls(0x4f5d0,root,address(d.image+0x13ec52));
        if(!array) goto cleanup;
        Word count;
        auto *record=reinterpret_cast<const std::uint8_t *>(profileRecords_eea0(profiles,&count));
        limit=count;
        for(Word index=0;index<limit;++index,record+=0x40) {
            if(load<std::uint32_t>(record,0x38)==0) continue;
            const auto object=d.calls(0x4f590);
            if(!object) goto cleanup;
            if(!d.calls(0x4f080,object,address(d.image+0x13ec47),load<Word>(record,0))) goto cleanup;
            const auto bind=load<std::uint32_t>(record,0x38);
            if(!d.calls(0x4eeb0,object,address(d.image+0x13ec60),std::bit_cast<Word>(double(bind)))) goto cleanup;
            if(std::uint32_t(d.calls(0x4e560,array,object))==0) goto cleanup;
            limit=count;
        }
    }
    text=d.calls(0x4dbe0,root);
cleanup:
    // Only the root is deleted here. Native failures before array attachment
    // can leave a newly allocated profile object unattached; preserve that quirk.
    d.calls(0x4d240,root);
    return text;
}
std::uint32_t saveConfiguration_bbd0(const std::uint8_t *registry,const std::uint8_t *profiles,const Dependencies &d) {
    std::uint16_t *path;
    auto status=initializePath_4c590(&path,d);
    if(status) return status;
    status=appendPath_4c610(&path,d.image+0x13ec08,d);
    if(!status) status=ensureDirectory_4c740(&path,d);
    if(!status) status=appendPath_4c610(&path,d.image+0x13ec10,d);
    if(!status) {
        const auto text=serializeConfiguration_bc70(registry,profiles,d);
        if(text) {
            status=writeText_4cc40(&path,reinterpret_cast<const std::uint8_t *>(text),1,d);
            d.calls(0x4d3b0,text);
        } else status=0x1388;
    }
    releasePath_4cd20(&path,d);
    return status;
}
Word profileMetadata_ea90(const std::uint8_t *profiles) { return load<Word>(profiles,0x18); }
Word currentProfile_c1f0(const Dependencies &d) { return load<Word>(d.image,0x2f7340); }
std::uint8_t pendingChanges_c200(const Dependencies &d) { return load<std::uint8_t>(d.image,0x2f7338); }
void setCurrentProfile_bfc0(const std::uint8_t *name,const Dependencies &d) {
    const auto old=currentProfile_c1f0(d);
    if(old) d.calls(0x13cf70,old);
    if(!name) { store<Word>(d.image,0x2f7340,0);return; }
    const auto length=recovered_string_length_ab840(name);
    const auto next=d.calls(0x13cf80,length+1);
    store(d.image,0x2f7340,next);
    if(!next) return;
    d.calls(0x13d0b0,next,address(name),length);
    store<std::uint8_t>(reinterpret_cast<void *>(next),std::size_t(length),0);
}
Word forwardModuleBind_28a30(const std::uint8_t *registry,const std::uint8_t *descriptor,
    std::uint32_t bind,const Dependencies &d) {
    return d.calls(load<Word>(registry,0x308),address(descriptor),bind);
}
std::uint8_t applyModule_cd20(Word root,const std::uint8_t *registry,
    std::uint8_t *descriptor,const Dependencies &d) {
    const auto object=d.calls(0x4e4d0,root,load<Word>(descriptor,0));
    auto flags=load<std::uint32_t>(descriptor,0x18);
    if(!(flags&2)) {
        const auto node=d.calls(0x4e4d0,object,address(d.image+0x13ec65));
        const auto enabled=std::uint32_t(d.calls(0x508c0,node))!=0;
        d.calls(0x284f0,address(registry),address(descriptor),std::uint8_t(enabled));
        flags=load<std::uint32_t>(descriptor,0x18);
    }
    if(!(flags&1)) {
        const auto node=d.calls(0x4e4d0,object,address(d.image+0x13ec6a));
        std::uint32_t bind=0;
        if(std::uint32_t(d.calls(0x4d150,node))) {
            const auto sum=_mm_add_sd(_mm_set_sd(load<double>(reinterpret_cast<void *>(node),0x30)),
                _mm_set_sd(load<double>(d.image,0x13ec00)));
            const auto converted=std::uint32_t(_mm_cvttsd_si64(sum));
            if(converted-0x68u>=std::uint32_t(-0x67)) bind=converted;
        }
        forwardModuleBind_28a30(registry,descriptor,bind,d);
        std::uint8_t hidden=0;
        if(!(load<std::uint8_t>(descriptor,0x18)&8)) {
            const auto node=d.calls(0x4e4d0,object,address(d.image+0x13ec71));
            hidden=std::uint32_t(d.calls(0x508c0,node))!=0;
        }
        store(descriptor,0x20,hidden);
    }
    const auto callback=load<Word>(descriptor,0x200);
    if(!callback) return 1;
    SettingsContext settings{reinterpret_cast<void *>(object),0,0,{0,0,0}};
    d.calls(callback,address(&settings));
    return settings.error^std::uint8_t{1};
}
std::uint8_t applyProfile_c030(const std::uint8_t *text,const std::uint8_t *registry,const Dependencies &d) {
    const auto root=d.calls(0x4da70,address(text));
    if(!root) return 0;
    std::uint8_t result=1;
    auto limit=load<Word>(registry,8);
    for(Word index=0;index<limit;++index) {
        const auto table=load<Word>(registry,0);
        auto *descriptor=reinterpret_cast<std::uint8_t *>(load<Word>(reinterpret_cast<void *>(table),std::size_t(index*8)));
        if(load<std::uint8_t>(descriptor,0x18)&0x10) continue;
        if(!applyModule_cd20(root,registry,descriptor,d)) { result=0;break; }
        limit=load<Word>(registry,8);
    }
    d.calls(0x4d240,root);
    return result;
}
Word serializeProfile_c170(const std::uint8_t *registry,const Dependencies &d) {
    const auto root=d.calls(0x4f590);
    Word result=0;
    if(root) {
        auto limit=load<Word>(registry,8);
        for(Word index=0;index<limit;++index) {
            const auto table=load<Word>(registry,0);
            const auto *descriptor=reinterpret_cast<const std::uint8_t *>(load<Word>(reinterpret_cast<void *>(table),std::size_t(index*8)));
            if(load<std::uint8_t>(descriptor,0x18)&0x10) continue;
            if(!serializeModule_ce20(root,descriptor,d)) goto cleanup;
            limit=load<Word>(registry,8);
        }
        result=d.calls(0x4dbe0,root);
    }
cleanup:
    d.calls(0x4d240,root);
    return result;
}
std::uint32_t loadProfile_be40(const std::uint8_t *name,const std::uint8_t *registry,const Dependencies &d) {
    if(!name) {
        for(Word index=0;index<load<Word>(registry,8);++index) {
            const auto table=load<Word>(registry,0);
            auto *descriptor=reinterpret_cast<std::uint8_t *>(load<Word>(reinterpret_cast<void *>(table),std::size_t(index*8)));
            if(load<std::uint8_t>(descriptor,0x18)&0x10) continue;
            forwardModuleBind_28a30(registry,descriptor,0,d);
            store<std::uint8_t>(descriptor,0x20,0);
            if(!(load<std::uint8_t>(descriptor,0x18)&2)) d.calls(0x284f0,address(registry),address(descriptor),0);
            const auto callback=load<Word>(descriptor,0x200);
            if(callback) {
                SettingsContext settings;
                std::memcpy(&settings,d.image+0x13ec78,sizeof settings);
                d.calls(callback,address(&settings));
            }
        }
        const auto current=currentProfile_c1f0(d);
        if(current) d.calls(0x13cf70,current);
        store<Word>(d.image,0x2f7340,0);
        store<std::uint8_t>(d.image,0x2f7338,0);
        return 0;
    }
    std::uint16_t *path;
    auto status=initializePath_4c590(&path,d);
    if(status) return status;
    status=appendPath_4c610(&path,d.image+0x13ec08,d);
    if(!status) status=ensureDirectory_4c740(&path,d);
    if(!status) status=appendPath_4c610(&path,d.image+0x13ec30,d);
    if(!status) status=ensureDirectory_4c740(&path,d);
    if(!status) status=appendPath_4c610(&path,name,d);
    if(!status) {
        std::uint8_t *text;
        status=readText_4ca30(&path,&text,d);
        if(!status) {
            status=0x1389;
            if(applyProfile_c030(text,registry,d)) {
                setCurrentProfile_bfc0(name,d);
                store<std::uint8_t>(d.image,0x2f7338,0);
                status=0;
            }
            d.calls(0x13cf70,address(text));
        }
    }
    releasePath_4cd20(&path,d);
    return status;
}
std::uint32_t saveProfile_c0b0(const std::uint8_t *name,std::uint8_t replace,
    const std::uint8_t *registry,const Dependencies &d) {
    std::uint16_t *path;
    auto status=initializePath_4c590(&path,d);
    if(status) return status;
    status=appendPath_4c610(&path,d.image+0x13ec08,d);
    if(!status) status=ensureDirectory_4c740(&path,d);
    if(!status) status=appendPath_4c610(&path,d.image+0x13ec30,d);
    // Native profile saving does not ensure this second directory.
    if(!status) status=appendPath_4c610(&path,name,d);
    if(!status) {
        const auto text=serializeProfile_c170(registry,d);
        if(!text) status=0x1388;
        else {
            status=writeText_4cc40(&path,reinterpret_cast<const std::uint8_t *>(text),replace,d);
            if(!status) {
                setCurrentProfile_bfc0(name,d);
                store<std::uint8_t>(d.image,0x2f7338,0);
            }
            d.calls(0x4d3b0,text);
        }
    }
    releasePath_4cd20(&path,d);
    return status;
}
}
