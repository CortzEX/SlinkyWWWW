// Recovered decompiler view: No Item Release
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x334c0, 0x33660); proximity does not prove ownership.

// CALLBACK RVA 0x334c0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/no_item_release/no_item_release.c
// Differential report: analysis/module_behavior_recovery/no_item_release/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x334c0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800334c0(longlong param_1)

{
  undefined8 uVar1;
  int iVar2;
  longlong lVar3;
  uint uVar4;
  
  lVar3 = FUN_180026580(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10));
  uVar1 = *(undefined8 *)(param_1 + 8);
  if (lVar3 == 0) {
    lVar3 = FUN_1800264f0(uVar1,*(undefined8 *)(param_1 + 0x10));
    if (lVar3 == 0) {
      return;
    }
    if (DAT_1802fa350 == '\0') {
      return;
    }
    iVar2 = FUN_180026530(*(undefined8 *)(param_1 + 8),lVar3);
    if (iVar2 == 5) {
      *(undefined4 *)(param_1 + 0x24) = 2;
    }
  }
  else {
    lVar3 = FUN_1800265c0(uVar1,lVar3);
    if (lVar3 == 0) {
      DAT_1802fa350 = 0;
      return;
    }
    lVar3 = FUN_180025d10(uVar1,lVar3);
    if (lVar3 == 0) {
      DAT_1802fa350 = 0;
      return;
    }
    iVar2 = FUN_180025c50(uVar1,lVar3);
    uVar4 = iVar2 - 0x105;
    if (uVar4 < 0x17) {
      if ((0x4088c0U >> (uVar4 & 0x1f) & 1) != 0) {
        if (_DAT_1802ec5e8 == 1) {
          DAT_1802fa350 = 0;
          return;
        }
        goto LAB_18003353d;
      }
      if (uVar4 == 0) {
        DAT_1802fa350 = 0;
        return;
      }
    }
    if (iVar2 == 0x15a) {
      DAT_1802fa350 = 0;
      return;
    }
    if (_DAT_1802ec5e8 != 0) {
LAB_18003353d:
      iVar2 = FUN_180025c50(uVar1,lVar3);
      DAT_1802fa350 = iVar2 != 0x105 && iVar2 != 0x15a;
      return;
    }
  }
  DAT_1802fa350 = 0;
  return;
}

// UI RVA 0x335c0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x335c0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_1800335c0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_18015196e);
  cVar1 = FUN_180014d00(param_1,param_2,uRam00000001802ec5d0,0x1802ec5b8,uRam00000001802ec5d8,
                        uRam00000001802ec5e0,&DAT_1802ec5e8,uRam00000001802ec5f0);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x33600; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x33600; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180033600(undefined8 *param_1)

{
  undefined8 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  longlong lVar5;
  longlong lVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  
  uVar2 = uRam00000001802ec5ec;
  uVar3 = _DAT_1802ec5e8;
  if (*(char *)((longlong)param_1 + 0xc) == '\0') {
    switch(*(undefined4 *)(param_1 + 1)) {
    case 0:
      lVar5 = FUN_18004e4d0(*param_1);
      iVar4 = FUN_18004d110(lVar5);
      lVar6 = lRam00000001802ec5e0;
      uVar3 = uVar2;
      if ((iVar4 != 0) && (uVar7 = (ulonglong)uRam00000001802ec5d8, uVar7 != 0)) {
        uVar1 = *(undefined8 *)(lVar5 + 0x20);
        uVar8 = 0;
        do {
          iVar4 = func_0x00018013d0a0(*(undefined8 *)(lVar6 + uVar8 * 8),uVar1);
          if (iVar4 == 0) {
            _DAT_1802ec5e8 = (int)uVar8;
            return;
          }
          uVar8 = uVar8 + 1;
        } while (uVar7 != uVar8);
      }
      break;
    case 1:
      lVar6 = FUN_18004f080(*param_1,&UNK_180151973,
                            *(undefined8 *)(lRam00000001802ec5e0 + (ulonglong)_DAT_1802ec5e8 * 8));
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar6 == 0;
      uVar3 = _DAT_1802ec5e8;
      break;
    case 2:
      uRam00000001802ec5ec = _DAT_1802ec5e8;
      break;
    case 3:
      uVar3 = uRam00000001802ec5ec;
    }
  }
  _DAT_1802ec5e8 = uVar3;
  return;
}

// CANDIDATE_LOCAL RVA 0x33620; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x33620; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180033620(undefined8 param_1)

{
  FUN_1800ab710(param_1,0x20,&UNK_180151978,
                *(undefined8 *)((ulonglong)_DAT_1802ec5e8 * 8 + 0x1802ec5a0));
  return;
}

