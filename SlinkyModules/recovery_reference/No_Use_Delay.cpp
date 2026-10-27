// Recovered decompiler view: No Use Delay
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x3e8e0, 0x3ea40); proximity does not prove ownership.

// CALLBACK RVA 0x3e8e0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/access_events/access_events.c
// Differential report: analysis/module_behavior_recovery/access_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3e8e0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003e8e0(longlong param_1)

{
  longlong *plVar1;
  undefined8 *puVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  
  puVar2 = *(undefined8 **)(param_1 + 8);
  if (*(char *)(puVar2 + 8) == '\0') {
    _DAT_180301e90 = 0;
    iVar4 = _DAT_180301e90;
  }
  else {
    uVar7 = FUN_180022cf0(*puVar2,puVar2[3]);
    uVar7 = FUN_180024f90(*puVar2,uVar7);
    cVar3 = FUN_180025430(*puVar2,uVar7);
    uVar8 = FUN_180023f40(*puVar2,puVar2[5]);
    iVar4 = FUN_180025a60(*puVar2,uVar8);
    if (iVar4 != _DAT_180301e94) {
      _DAT_180301e90 = 0;
      uVar8 = *puVar2;
      _DAT_180301e94 = iVar4;
      uVar5 = FUN_180025490(uVar8,uVar7);
      FUN_180025460(uVar8,uVar7,uVar5);
    }
    iVar4 = _DAT_180301e90;
    if (((cVar3 != '\0') &&
        (iVar6 = FUN_180023fc0(*puVar2,puVar2[5]), iVar4 = iVar6, 0 < _DAT_180301e90)) &&
       ((_DAT_180301e90 = _DAT_180301e90 + -1, _DAT_180301e90 == 0 ||
        (iVar4 = _DAT_180301e90, (iVar6 == 0 & DAT_1802f1438) == 1)))) {
      plVar1 = (longlong *)((longlong *)*puVar2)[1];
                    /* WARNING: Could not recover jumptable at 0x000180025480. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*plVar1 + 0x348))(plVar1,uVar7,*(undefined8 *)(*(longlong *)*puVar2 + 0x478),0);
      return;
    }
  }
  _DAT_180301e90 = iVar4;
  return;
}

// UI RVA 0x3e9e0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3e9e0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003e9e0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180153fcc);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802f1430,0x1802f1420,&DAT_1802f1438);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x3ea20; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3ea20; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003ea20(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  uVar1 = uRam00000001802f1439;
  uVar2 = DAT_1802f1438;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180153fd1,DAT_1802f1438);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802f1438;
      break;
    case 2:
      uRam00000001802f1439 = DAT_1802f1438;
      break;
    case 3:
      uVar2 = uRam00000001802f1439;
    }
  }
  DAT_1802f1438 = uVar2;
  return;
}

