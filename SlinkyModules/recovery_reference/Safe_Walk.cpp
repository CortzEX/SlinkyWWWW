// Recovered decompiler view: Safe Walk
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x41d30, 0x41f40); proximity does not prove ownership.

// CALLBACK RVA 0x41d30; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/safe_walk/safe_walk.c
// Differential report: analysis/module_behavior_recovery/safe_walk/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x41d30; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180041d30(longlong param_1)

{
  undefined8 *puVar1;
  char cVar2;
  float extraout_var;
  undefined8 uVar3;
  float fVar4;
  double dStack_48;
  undefined8 uStack_40;
  double dStack_38;
  double dStack_28;
  undefined8 uStack_20;
  double dStack_18;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  if (*(char *)(puVar1 + 8) != '\x01') {
    return;
  }
  if (((DAT_1802f2290 == '\x01') &&
      (FUN_180023170(*puVar1,puVar1[5]), extraout_var < _DAT_1801544d8)) ||
     ((DAT_1802f22b0 == '\x01' && (fVar4 = (float)FUN_180023ac0(*puVar1,puVar1[5]), 0.0 < fVar4))))
  {
LAB_180041e40:
    DAT_1803043c8 = 0;
  }
  else {
    if (DAT_1802f22d0 == '\x01') {
      uVar3 = FUN_180028a50(*puVar1,puVar1[5]);
      cVar2 = FUN_180028b00(*puVar1,uVar3);
      if (cVar2 == '\0') goto LAB_180041e40;
    }
    DAT_1803043c8 = 1;
    cVar2 = FUN_180023780(*puVar1,puVar1[5]);
    if (cVar2 != '\0') {
      if ((_DAT_1802f2270 != _DAT_1801544dc) || (NAN(_DAT_1802f2270) || NAN(_DAT_1801544dc))) {
        FUN_180023550(&dStack_28,*puVar1,puVar1[5]);
        dStack_48 = dStack_28 * (double)_DAT_1802f2270;
        dStack_38 = (double)_DAT_1802f2270 * dStack_18;
        uStack_40 = uStack_20;
        dStack_28 = dStack_48;
        dStack_18 = dStack_38;
        FUN_1800235f0(*puVar1,puVar1[5],&dStack_48);
      }
    }
  }
  return;
}

// UI RVA 0x41e50; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x41e50; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180041e50(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_18015454c);
  FUN_18000cf30(param_2,param_1,0x1802f2240);
  FUN_180013e90(param_1,param_2,&UNK_180154551);
  FUN_18000cef0(param_2,param_1,0x1802f22b8);
  FUN_18000cef0(param_2,param_1,0x1802f2278);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802f22a8,0x1802f2298,&DAT_1802f22b0);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x41ed0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x41ed0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180041ed0(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c450(param_1,&UNK_18015455c,0x1802f2240);
  FUN_18000c3b0(param_1,&UNK_18015456e,0x1802f22b8);
  FUN_18000c3b0(param_1,&UNK_180154585,0x1802f2278);
  uVar1 = uRam00000001802f22b1;
  uVar2 = DAT_1802f22b0;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_18015459a,DAT_1802f22b0);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802f22b0;
      break;
    case 2:
      uRam00000001802f22b1 = DAT_1802f22b0;
      break;
    case 3:
      uVar2 = uRam00000001802f22b1;
    }
  }
  DAT_1802f22b0 = uVar2;
  return;
}

