// Recovered decompiler view: No Jump Delay
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x35d50, 0x35d80); proximity does not prove ownership.

// CALLBACK RVA 0x35d50; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/access_events/access_events.c
// Differential report: analysis/module_behavior_recovery/access_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x35d50; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180035d50(longlong param_1)

{
  longlong *plVar1;
  undefined8 *puVar2;
  
  puVar2 = *(undefined8 **)(param_1 + 8);
  if (*(char *)(puVar2 + 8) == '\x01') {
    plVar1 = (longlong *)((longlong *)*puVar2)[1];
                    /* WARNING: Could not recover jumptable at 0x000180023ba0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar1 + 0x368))(plVar1,puVar2[5],*(undefined8 *)(*(longlong *)*puVar2 + 0x570),0)
    ;
    return;
  }
  return;
}

