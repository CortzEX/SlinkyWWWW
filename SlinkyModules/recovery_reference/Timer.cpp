// Recovered decompiler view: Timer
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x328f0, 0x32b30); proximity does not prove ownership.

// CALLBACK RVA 0x328f0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/state_events/state_events.c
// Differential report: analysis/module_behavior_recovery/state_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x328f0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800328f0(longlong param_1)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  char cVar3;
  int iVar4;
  undefined8 uVar5;
  undefined4 uVar6;
  undefined1 auStack_30 [8];
  double dStack_28;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  uVar2 = FUN_180022c70(*puVar1,puVar1[3]);
  if (DAT_1802ebc70 == '\x01') {
    cVar3 = FUN_180029080(puVar1);
    if (cVar3 != '\0') goto LAB_180032924;
  }
  else {
LAB_180032924:
    if (DAT_1802ebc90 == '\x01') {
      cVar3 = FUN_180023780(*puVar1,puVar1[5]);
      if (cVar3 == '\0') {
        FUN_180023550(auStack_30,*puVar1,puVar1[5]);
        if (dStack_28 < 0.0) goto LAB_18003295c;
      }
    }
    else {
LAB_18003295c:
      if (DAT_1802ebcb0 != '\x01') {
LAB_18003297b:
        uVar5 = *puVar1;
        uVar6 = _DAT_1802ebc50;
        goto LAB_180032993;
      }
      if (*(char *)(puVar1 + 8) == '\x01') {
        iVar4 = FUN_1800239f0(*puVar1,puVar1[5]);
        if (iVar4 != 0) goto LAB_18003297b;
      }
    }
  }
  uVar5 = *puVar1;
  uVar6 = _DAT_180151668;
LAB_180032993:
  FUN_1800259c0(uVar5,uVar2,uVar6);
  return;
}

// CALLBACK RVA 0x329b0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/state_events/state_events.c
// Differential report: analysis/module_behavior_recovery/state_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x329b0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800329b0(longlong param_1)

{
  longlong *plVar1;
  code *UNRECOVERED_JUMPTABLE;
  undefined8 *puVar2;
  undefined8 uVar3;
  
  if ((*(longlong *)(param_1 + 0x10) == 0x1802eba10) && (*(char *)(param_1 + 0x18) == '\0')) {
    puVar2 = *(undefined8 **)(param_1 + 8);
    uVar3 = FUN_180022c70(*puVar2,puVar2[3]);
    plVar1 = (longlong *)((longlong *)*puVar2)[1];
    UNRECOVERED_JUMPTABLE = *(code **)(*plVar1 + 0x378);
                    /* WARNING: Could not recover jumptable at 0x0001800259e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE)
              (plVar1,uVar3,*(undefined8 *)(*(longlong *)*puVar2 + 0x390),UNRECOVERED_JUMPTABLE);
    return;
  }
  return;
}

// UI RVA 0x32a00; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x32a00; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180032a00(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_1801516c5);
  FUN_18000cf30(param_2,param_1,0x1802ebc20);
  FUN_180013e90(param_1,param_2,&UNK_1801516ca);
  FUN_18000cef0(param_2,param_1,0x1802ebc58);
  FUN_18000cef0(param_2,param_1,0x1802ebc98);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802ebc88,0x1802ebc78,&DAT_1802ebc90);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x32a80; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x32a80; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180032a80(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c450(param_1,&UNK_1801516d5,0x1802ebc20);
  FUN_18000c3b0(param_1,&UNK_1801516db,0x1802ebc58);
  FUN_18000c3b0(param_1,&UNK_1801516e9,0x1802ebc98);
  uVar1 = uRam00000001802ebc91;
  uVar2 = DAT_1802ebc90;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_1801516f8,DAT_1802ebc90);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802ebc90;
      break;
    case 2:
      uRam00000001802ebc91 = DAT_1802ebc90;
      break;
    case 3:
      uVar2 = uRam00000001802ebc91;
    }
  }
  DAT_1802ebc90 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x32af0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x32af0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180032af0(void)

{
  FUN_1800ab710(_DAT_1802ebc50,0x20,&UNK_180151708,(double)_DAT_1802ebc50);
  return;
}

