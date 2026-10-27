// Recovered decompiler view: Piercing
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x44c90, 0x44e40); proximity does not prove ownership.

// CALLBACK RVA 0x44c90; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/simple_events/simple_events.c
// Differential report: analysis/module_behavior_recovery/simple_events/simple_events_verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x44c90; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180044c90(longlong param_1)

{
  *(undefined1 *)(param_1 + 0x10) = 1;
  return;
}

// UI RVA 0x44ca0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x44ca0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180044ca0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180154d7c);
  FUN_18000d040(param_2,param_1,0x1802f3d90);
  FUN_18000cef0(param_2,param_1,0x1802f3d00);
  FUN_18000cef0(param_2,param_1,0x1802f3d20);
  FUN_18000cef0(param_2,param_1,0x1802f3d40);
  FUN_18000cef0(param_2,param_1,0x1802f3d60);
  FUN_18000cef0(param_2,param_1,0x1802f3dd0);
  FUN_180013e90(param_1,param_2,&UNK_180154d8f);
  FUN_18000cef0(param_2,param_1,0x1802f3ce0);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802f3cd0,0x1802f3cc0,&DAT_1802f3cd8);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x44d70; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x44d70; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180044d70(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c6f0(param_1,&UNK_180154d9a,0x1802f3d90);
  FUN_18000c3b0(param_1,&UNK_180154da2,0x1802f3d00);
  FUN_18000c3b0(param_1,&UNK_180154dae,0x1802f3d20);
  FUN_18000c3b0(param_1,&UNK_180154db9,0x1802f3d40);
  FUN_18000c3b0(param_1,&UNK_180154dbe,0x1802f3d60);
  FUN_18000c3b0(param_1,&UNK_180154dc6,0x1802f3dd0);
  FUN_18000c3b0(param_1,&UNK_180154dcd,0x1802f3ce0);
  uVar1 = uRam00000001802f3cd9;
  uVar2 = DAT_1802f3cd8;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180154ddc,DAT_1802f3cd8);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802f3cd8;
      break;
    case 2:
      uRam00000001802f3cd9 = DAT_1802f3cd8;
      break;
    case 3:
      uVar2 = uRam00000001802f3cd9;
    }
  }
  DAT_1802f3cd8 = uVar2;
  return;
}

