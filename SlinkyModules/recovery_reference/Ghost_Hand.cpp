// Recovered decompiler view: Ghost Hand
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x46e30, 0x47090); proximity does not prove ownership.

// CALLBACK RVA 0x46e30; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/simple_events/simple_events.c
// Differential report: analysis/module_behavior_recovery/simple_events/simple_events_verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x46e30; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180046e30(longlong param_1)

{
  *(undefined1 *)(param_1 + 0x10) = 1;
  return;
}

// UI RVA 0x46e40; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x46e40; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180046e40(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_18015549b);
  FUN_18000cef0(param_2,param_1,0x1802f4bc0);
  FUN_18000cef0(param_2,param_1,0x1802f4c00);
  FUN_18000cef0(param_2,param_1,0x1802f4be0);
  FUN_18000cef0(param_2,param_1,0x1802f4c20);
  FUN_180013e90(param_1,param_2,&UNK_1801554ac);
  FUN_18000cef0(param_2,param_1,0x1802f4b00);
  FUN_18000cef0(param_2,param_1,0x1802f4b20);
  FUN_18000cef0(param_2,param_1,0x1802f4ae0);
  FUN_18000cef0(param_2,param_1,0x1802f4b40);
  FUN_18000cef0(param_2,param_1,0x1802f4b60);
  FUN_18000cef0(param_2,param_1,0x1802f4b80);
  FUN_18000cef0(param_2,param_1,0x1802f4ba0);
  FUN_180013e90(param_1,param_2,&UNK_1801554be);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802f4ad0,0x1802f4ac0,&DAT_1802f4ad8);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x46f70; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x46f70; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180046f70(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c3b0(param_1,&UNK_1801554c9,0x1802f4bc0);
  FUN_18000c3b0(param_1,&UNK_1801554d5,0x1802f4c00);
  FUN_18000c3b0(param_1,&UNK_1801554e0,0x1802f4be0);
  FUN_18000c3b0(param_1,&UNK_1801554e5,0x1802f4c20);
  FUN_18000c3b0(param_1,&UNK_1801554ed,0x1802f4b00);
  FUN_18000c3b0(param_1,&UNK_1801554ff,0x1802f4b20);
  FUN_18000c3b0(param_1,&UNK_180155511,0x1802f4ae0);
  FUN_18000c3b0(param_1,&UNK_180155523,0x1802f4b40);
  FUN_18000c3b0(param_1,&UNK_180155537,0x1802f4b60);
  FUN_18000c3b0(param_1,&UNK_180155547,0x1802f4b80);
  FUN_18000c3b0(param_1,&UNK_18015555a,0x1802f4ba0);
  uVar1 = uRam00000001802f4ad9;
  uVar2 = DAT_1802f4ad8;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_18015556c,DAT_1802f4ad8);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802f4ad8;
      break;
    case 2:
      uRam00000001802f4ad9 = DAT_1802f4ad8;
      break;
    case 3:
      uVar2 = uRam00000001802f4ad9;
    }
  }
  DAT_1802f4ad8 = uVar2;
  return;
}

