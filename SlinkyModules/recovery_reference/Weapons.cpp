// Recovered decompiler view: Weapons
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x38190, 0x384c0); proximity does not prove ownership.

// CALLBACK RVA 0x38190; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/weapons/weapons.c
// Differential report: analysis/module_behavior_recovery/weapons/verification_report.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x38190; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180038190(void)

{
  func_0x00018013cf70(_DAT_1802fc568);
  _DAT_1802fc568 = 0;
  uRam00000001802fc570 = 0;
  return;
}

// UI RVA 0x381c0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x381c0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_1800381c0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_1801529a0);
  FUN_18000cef0(param_2,param_1,0x1802eeb40);
  FUN_18000cef0(param_2,param_1,0x1802eed00);
  FUN_18000cef0(param_2,param_1,0x1802eece0);
  FUN_18000d0e0(param_2,param_1,0x1802eed20);
  FUN_180013e90(param_1,param_2,&UNK_1801529ab);
  FUN_18000cef0(param_2,param_1,0x1802eec80);
  FUN_18000cef0(param_2,param_1,0x1802eeca0);
  FUN_18000cef0(param_2,param_1,0x1802eecc0);
  FUN_180013e90(param_1,param_2,&UNK_1801529b9);
  FUN_18000cef0(param_2,param_1,0x1802eeb60);
  FUN_18000cef0(param_2,param_1,0x1802eeb80);
  FUN_18000cef0(param_2,param_1,0x1802eeba0);
  FUN_18000cef0(param_2,param_1,0x1802eebc0);
  FUN_18000cef0(param_2,param_1,0x1802eebe0);
  FUN_18000cef0(param_2,param_1,0x1802eec00);
  FUN_18000cef0(param_2,param_1,0x1802eec20);
  FUN_18000cef0(param_2,param_1,0x1802eec40);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802eec70,0x1802eec60,0x1802eec78);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x38330; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x38330; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180038330(undefined8 param_1)

{
  undefined2 uStack_1a;
  
  FUN_18000c3b0(param_1,&UNK_1801529d7,0x1802eeb40);
  FUN_18000c3b0(param_1,&UNK_1801529dc,0x1802eed00);
  FUN_18000c3b0(param_1,&UNK_1801529e3,0x1802eece0);
  FUN_18000ca00(param_1,&UNK_1801529e8,0x1802eed20);
  FUN_18000c3b0(param_1,&UNK_1801529f4,0x1802eec80);
  FUN_18000c3b0(param_1,&UNK_180152a06,0x1802eeca0);
  FUN_18000c3b0(param_1,&UNK_180152a18,0x1802eecc0);
  uStack_1a = 0x31;
  FUN_18000c3b0(param_1,&uStack_1a,0x1802eeb60);
  uStack_1a = 0x32;
  FUN_18000c3b0(param_1,&uStack_1a,0x1802eeb80);
  uStack_1a = 0x33;
  FUN_18000c3b0(param_1,&uStack_1a,0x1802eeba0);
  uStack_1a = 0x34;
  FUN_18000c3b0(param_1,&uStack_1a,0x1802eebc0);
  uStack_1a = 0x35;
  FUN_18000c3b0(param_1,&uStack_1a,0x1802eebe0);
  uStack_1a = 0x36;
  FUN_18000c3b0(param_1,&uStack_1a,0x1802eec00);
  uStack_1a = 0x37;
  FUN_18000c3b0(param_1,&uStack_1a,0x1802eec20);
  uStack_1a = 0x38;
  FUN_18000c3b0(param_1,&uStack_1a,0x1802eec40);
  uStack_1a = 0x39;
  FUN_18000c3b0(param_1,&uStack_1a,0x1802eec60);
  return;
}

