// Recovered decompiler view: Debug
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x466e0, 0x46ac0); proximity does not prove ownership.

// CALLBACK RVA 0x466e0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/debug/debug.c
// Differential report: analysis/module_behavior_recovery/debug/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x466e0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_1800466e0(longlong param_1)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  byte bVar3;
  char cVar4;
  int iVar5;
  uint uVar6;
  undefined *puVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  if (*(char *)(puVar1 + 8) == '\x01') {
    if (DAT_1802f4658 == '\x01') {
      iVar5 = FUN_1800239f0(*puVar1,puVar1[5]);
      if (6 < iVar5) {
        uVar2 = *puVar1;
        uVar6 = FUN_180023760(uVar2,puVar1[5]);
        uVar10 = 0x66;
        if (iVar5 - 7U < 4) {
          uVar10 = *(undefined4 *)(&UNK_180155200 + (ulonglong)(iVar5 - 7U) * 4);
        }
        cVar4 = FUN_180023690(*puVar1,puVar1[5]);
        uVar8 = 0x38;
        uVar9 = 99;
        if (cVar4 != '\0') {
          uVar9 = uVar8;
        }
        cVar4 = FUN_180023f90(*puVar1,puVar1[5]);
        if (cVar4 != '\0') {
          uVar8 = 99;
        }
        FUN_1800291f0(uVar2,&UNK_180155136,uVar6 % 1000,uVar10,iVar5,uVar9,uVar8);
      }
    }
    bVar3 = DAT_1803049b9;
    if (DAT_1802f4678 == '\x01') {
      if ((DAT_1803049b9 & 1) != DAT_1803049b8) {
        uVar2 = *puVar1;
        DAT_1803049b8 = DAT_1803049b9 & 1;
        uVar6 = FUN_180023760(uVar2,puVar1[5]);
        puVar7 = &UNK_1801551a4;
        if ((bVar3 & 1) != 0) {
          puVar7 = &UNK_18015519d;
        }
        FUN_1800291f0(uVar2,&UNK_18015517d,uVar6 % 1000,puVar7);
      }
    }
  }
  return;
}

// CALLBACK RVA 0x46850; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/debug/debug.c
// Differential report: analysis/module_behavior_recovery/debug/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x46850; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180046850(longlong param_1)

{
  int iVar1;
  longlong lVar2;
  undefined1 uVar3;
  
  if ((*(int *)(param_1 + 0x24) != 3) && (*(int *)(param_1 + 0x24) != 0)) {
    return;
  }
  lVar2 = FUN_180026580(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10));
  uVar3 = 1;
  if (lVar2 == 0) {
    lVar2 = FUN_1800264f0(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10));
    if (lVar2 == 0) {
      return;
    }
    iVar1 = FUN_180026530(*(undefined8 *)(param_1 + 8),lVar2);
    if (iVar1 != 5) {
      return;
    }
    uVar3 = 0;
  }
  LOCK();
  UNLOCK();
  DAT_1803049b9 = uVar3;
  return;
}

// CALLBACK RVA 0x468c0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/debug/debug.c
// Differential report: analysis/module_behavior_recovery/debug/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x468c0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800468c0(longlong param_1)

{
  int *piVar1;
  
  if (DAT_1802f4698 == '\x01') {
    piVar1 = (int *)&DAT_1803049c0;
    if (*(char *)(param_1 + 0x10) != '\0') {
      piVar1 = (int *)&DAT_1803049bc;
    }
    *piVar1 = *piVar1 + 1;
    _DAT_1803049c4 = 0;
  }
  return;
}

// CALLBACK RVA 0x46900; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/debug/debug.c
// Differential report: analysis/module_behavior_recovery/debug/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x46900; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180046900(longlong param_1)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  if (*(char *)(puVar1 + 8) == '\x01') {
    if (DAT_1802f4698 == '\x01') {
      if (_DAT_1803049c4 < 10) {
        uVar5 = 0x32;
        if (_DAT_1803049bc == 1) {
          uVar5 = 0x61;
        }
        if (_DAT_1803049bc == 0) {
          uVar5 = 0x38;
        }
        uVar4 = 0x33;
        if (_DAT_1803049c0 == 1) {
          uVar4 = 0x62;
        }
        if (_DAT_1803049c0 == 0) {
          uVar4 = 0x38;
        }
        uVar2 = *puVar1;
        uVar3 = FUN_180023760(uVar2,puVar1[5]);
        FUN_1800291f0(uVar2,&UNK_1801551b1,uVar3 % 1000,uVar5,_DAT_1803049bc,uVar4,_DAT_1803049c0);
      }
      _DAT_1803049bc = 0;
      _DAT_1803049c0 = 0;
    }
    _DAT_1803049c4 = _DAT_1803049c4 + 1;
  }
  return;
}

// UI RVA 0x46a00; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x46a00; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180046a00(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_1801551db);
  FUN_18000cef0(param_2,param_1,0x1802f4680);
  FUN_18000cef0(param_2,param_1,0x1802f4640);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802f4670,0x1802f4660,&DAT_1802f4678);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x46a60; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x46a60; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180046a60(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c3b0(param_1,&UNK_1801551e0,0x1802f4680);
  FUN_18000c3b0(param_1,&UNK_1801551e7,0x1802f4640);
  uVar1 = uRam00000001802f4679;
  uVar2 = DAT_1802f4678;
  if (*(char *)((longlong)param_1 + 0xc) == '\0') {
    switch(*(undefined4 *)(param_1 + 1)) {
    case 0:
      uVar4 = FUN_18004e4d0(*param_1);
      iVar3 = FUN_1800508e0(uVar4);
      uVar2 = uVar1;
      if (iVar3 != 0) {
        iVar3 = FUN_1800508c0(uVar4);
        uVar2 = iVar3 != 0;
      }
      break;
    case 1:
      lVar5 = FUN_18004ed40(*param_1,&UNK_1801551f1,DAT_1802f4678);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802f4678;
      break;
    case 2:
      uRam00000001802f4679 = DAT_1802f4678;
      break;
    case 3:
      uVar2 = uRam00000001802f4679;
    }
  }
  DAT_1802f4678 = uVar2;
  return;
}

