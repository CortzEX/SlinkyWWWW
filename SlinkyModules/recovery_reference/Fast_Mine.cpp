// Recovered decompiler view: Fast Mine
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x41a90, 0x41d30); proximity does not prove ownership.

// CALLBACK RVA 0x41a90; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/fast_mine/fast_mine.c
// Differential report: analysis/module_behavior_recovery/fast_mine/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x41a90; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180041a90(longlong param_1)

{
  undefined8 *puVar1;
  int iVar2;
  longlong lVar3;
  undefined8 uVar4;
  int iVar5;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  lVar3 = FUN_180022df0(*puVar1,puVar1[3]);
  if (lVar3 == 0) {
    iVar2 = 0;
  }
  else {
    _DAT_1803043c4 = FUN_180027df0(*puVar1,lVar3);
    iVar2 = FUN_180027e40(*puVar1,lVar3);
    if ((float)iVar2 <= _DAT_1802f1fd0) {
      if (iVar2 < 1) {
        _DAT_1803043c0 = iVar2;
        return;
      }
      if (DAT_1802f1ff0 == '\0') {
        _DAT_1803043c0 = iVar2;
        return;
      }
      if (iVar2 != _DAT_1803043c0) {
        _DAT_1803043c0 = iVar2;
        return;
      }
      uVar4 = *puVar1;
      iVar5 = iVar2 + -1;
    }
    else {
      uVar4 = *puVar1;
      iVar5 = (int)_DAT_1802f1fd0;
    }
    FUN_180027e60(uVar4,lVar3,iVar5);
  }
  _DAT_1803043c0 = iVar2;
  return;
}

// CALLBACK RVA 0x41b30; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/fast_mine/fast_mine.c
// Differential report: analysis/module_behavior_recovery/fast_mine/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x41b30; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180041b30(longlong param_1)

{
  longlong *plVar1;
  code *UNRECOVERED_JUMPTABLE;
  undefined8 *puVar2;
  longlong lVar3;
  float fVar4;
  
  puVar2 = *(undefined8 **)(param_1 + 8);
  lVar3 = FUN_180022df0(*puVar2,puVar2[3]);
  if (lVar3 != 0) {
    fVar4 = (float)FUN_180027df0(*puVar2,lVar3);
    if ((fVar4 != 0.0) || (NAN(fVar4))) {
      if ((_DAT_1803043c4 == 0.0) && (!NAN(_DAT_1803043c4))) {
        func_0x0001800b2920(_DAT_180154438 / fVar4);
        func_0x0001800b2920((float)((_DAT_180154440 / (double)_DAT_1802f2028) / (double)fVar4));
        plVar1 = (longlong *)((longlong *)*puVar2)[1];
        UNRECOVERED_JUMPTABLE = *(code **)(*plVar1 + 0x378);
                    /* WARNING: Could not recover jumptable at 0x000180027e30. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (*UNRECOVERED_JUMPTABLE)
                  (plVar1,lVar3,*(undefined8 *)(*(longlong *)*puVar2 + 0xbc8),UNRECOVERED_JUMPTABLE)
        ;
        return;
      }
    }
  }
  return;
}

// UI RVA 0x41c20; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x41c20; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180041c20(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_1801544ac);
  FUN_18000cf30(param_2,param_1,0x1802f1ff8);
  FUN_18000cf30(param_2,param_1,0x1802f1fa0);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802f1fe8,0x1802f1fd8,&DAT_1802f1ff0);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x41c80; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x41c80; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180041c80(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c450(param_1,&UNK_1801544b1,0x1802f1ff8);
  FUN_18000c450(param_1,&UNK_1801544b7,0x1802f1fa0);
  uVar1 = uRam00000001802f1ff1;
  uVar2 = DAT_1802f1ff0;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_1801544c3,DAT_1802f1ff0);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802f1ff0;
      break;
    case 2:
      uRam00000001802f1ff1 = DAT_1802f1ff0;
      break;
    case 3:
      uVar2 = uRam00000001802f1ff1;
    }
  }
  DAT_1802f1ff0 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x41ce0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x41ce0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180041ce0(void)

{
  FUN_1800ab710(_DAT_1802f2028,0x20,&UNK_1801544a6,(double)_DAT_1802f2028);
  return;
}

// CANDIDATE_LOCAL RVA 0x41d20; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x41d20; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


undefined1 FUN_180041d20(void)

{
  return DAT_1803043c8;
}

