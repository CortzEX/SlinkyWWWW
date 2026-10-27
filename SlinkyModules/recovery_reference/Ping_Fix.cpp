// Recovered decompiler view: Ping Fix
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x3e6d0, 0x3e880); proximity does not prove ownership.

// CALLBACK RVA 0x3e6d0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/simple_events/simple_events.c
// Differential report: analysis/module_behavior_recovery/simple_events/simple_events_verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3e6d0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003e6d0(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = FUN_180026c80(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10));
  if (lVar1 != 0) {
    *(undefined4 *)(param_1 + 0x24) = 3;
  }
  return;
}

// CALLBACK RVA 0x3e700; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/simple_events/simple_events.c
// Differential report: analysis/module_behavior_recovery/simple_events/simple_events_verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3e700; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003e700(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = FUN_180026cc0(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10));
  if (lVar1 != 0) {
    *(undefined4 *)(param_1 + 0x24) = 3;
  }
  return;
}

// CANDIDATE_LOCAL RVA 0x3e730; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3e730; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003e730(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4,
                  undefined8 param_5,undefined8 param_6,undefined4 param_7,undefined4 param_8)

{
  char cVar1;
  
  if (DAT_1802f0ff4 == '\x01') {
    cVar1 = FUN_18002ace0(param_1,param_3,(uint)DAT_1802f1208 * 5 + 2);
    if (cVar1 == '\0') {
      (*(code *)*_DAT_18013e458)(0x8037);
      (*(code *)*_DAT_180153f78)(_DAT_180153f24,_DAT_180153f28);
      FUN_1800274f0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
                    /* WARNING: Could not recover jumptable at 0x00018003e874. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*(code *)*_DAT_18013e450)(0x8037);
      return;
    }
  }
  FUN_1800274f0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}

