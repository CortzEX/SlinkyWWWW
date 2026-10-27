// Recovered decompiler view: Keep Sprint
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x3a0f0, 0x3a3c0); proximity does not prove ownership.

// CALLBACK RVA 0x3a0f0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/keep_sprint/keep_sprint.c
// Differential report: analysis/module_behavior_recovery/keep_sprint/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3a0f0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003a0f0(longlong param_1)

{
  undefined8 *puVar1;
  char cVar2;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined8 uStack_18;
  
  if (*(char *)(param_1 + 0x10) == '\x01') {
    puVar1 = *(undefined8 **)(param_1 + 8);
    if (((*(char *)(puVar1 + 8) == '\x01') &&
        (cVar2 = FUN_180023690(*puVar1,puVar1[5]), cVar2 != '\0')) &&
       (cVar2 = FUN_18000a460(_DAT_1802ef940), cVar2 != '\0')) {
      FUN_180023550(&uStack_28,*puVar1,puVar1[5]);
      _DAT_1802fc7b0 = uStack_18;
      _DAT_1802fc7a0 = uStack_28;
      uRam00000001802fc7a8 = uStack_20;
      DAT_1802fc7b8 = 1;
    }
    else {
      DAT_1802fc7b8 = 0;
    }
  }
  return;
}

// CALLBACK RVA 0x3a170; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/keep_sprint/keep_sprint.c
// Differential report: analysis/module_behavior_recovery/keep_sprint/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3a170; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003a170(longlong param_1)

{
  undefined8 *puVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  double dStack_38;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  double dStack_28;
  
  if ((DAT_1802fc7b8 == '\x01') && (*(char *)(param_1 + 0x10) == '\x01')) {
    puVar1 = *(undefined8 **)(param_1 + 8);
    lVar5 = puVar1[5];
    if (lVar5 != 0) {
      if (DAT_1802ef998 == '\x01') {
        cVar2 = FUN_180023780(*puVar1);
        if (cVar2 == '\0') {
          return;
        }
        lVar5 = puVar1[5];
      }
      iVar3 = FUN_180023760(*puVar1,lVar5);
      iVar4 = FUN_1800239d0(*puVar1,puVar1[5]);
      if ((iVar3 == iVar4) && ((DAT_1802ef9b8 != '\x01' || (*(char *)(puVar1[7] + 0x18) == '\0'))))
      {
        _DAT_1802fc7a0 = _DAT_1802fc7a0 * (double)_DAT_1802ef978;
        _DAT_1802fc7b0 = (double)_DAT_1802ef978 * _DAT_1802fc7b0;
        uStack_30 = uRam00000001802fc7a8;
        uStack_2c = uRam00000001802fc7ac;
        dStack_28 = _DAT_1802fc7b0;
        dStack_38 = _DAT_1802fc7a0;
        FUN_1800235f0(*puVar1,puVar1[5],&dStack_38);
        DAT_1802fc7b9 = 1;
      }
    }
  }
  return;
}

// CALLBACK RVA 0x3a260; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/keep_sprint/keep_sprint.c
// Differential report: analysis/module_behavior_recovery/keep_sprint/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3a260; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003a260(longlong param_1)

{
  longlong *plVar1;
  longlong lVar2;
  longlong *plVar3;
  
  if (DAT_1802fc7b9 == '\x01') {
    DAT_1802fc7b9 = '\0';
    lVar2 = (*(undefined8 **)(param_1 + 8))[5];
    if (lVar2 != 0) {
      plVar3 = (longlong *)**(undefined8 **)(param_1 + 8);
      plVar1 = (longlong *)plVar3[1];
      (**(code **)(*plVar1 + 0x1e8))(plVar1,lVar2,*(undefined8 *)(*plVar3 + 0x230),1);
      return;
    }
  }
  return;
}

// UI RVA 0x3a290; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3a290; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003a290(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180152e92);
  FUN_18000cf30(param_2,param_1,0x1802ef910);
  FUN_18000cf30(param_2,param_1,0x1802ef948);
  FUN_18000cef0(param_2,param_1,0x1802ef9a0);
  FUN_180013e90(param_1,param_2,&UNK_180152e97);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802ef990,0x1802ef980,&DAT_1802ef998);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x3a310; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3a310; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003a310(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c450(param_1,&UNK_180152ea2,0x1802ef910);
  FUN_18000c450(param_1,&UNK_180152ea9,0x1802ef948);
  FUN_18000c3b0(param_1,&UNK_180152eb5,0x1802ef9a0);
  uVar1 = uRam00000001802ef999;
  uVar2 = DAT_1802ef998;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180152ec2,DAT_1802ef998);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802ef998;
      break;
    case 2:
      uRam00000001802ef999 = DAT_1802ef998;
      break;
    case 3:
      uVar2 = uRam00000001802ef999;
    }
  }
  DAT_1802ef998 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x3a380; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3a380; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003a380(void)

{
  FUN_1800ab710(_DAT_1802ef978 * _DAT_180152e1c,0x20,&UNK_180152e63,
                (double)(_DAT_1802ef978 * _DAT_180152e1c));
  return;
}

