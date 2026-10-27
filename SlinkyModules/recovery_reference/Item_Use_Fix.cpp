// Recovered decompiler view: Item Use Fix
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x42b80, 0x42c60); proximity does not prove ownership.

// CALLBACK RVA 0x42b80; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/access_events/access_events.c
// Differential report: analysis/module_behavior_recovery/access_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x42b80; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180042b80(longlong param_1)

{
  longlong *plVar1;
  undefined8 *puVar2;
  char cVar3;
  undefined8 uVar4;
  
  if (*(char *)(param_1 + 0x10) == '\0') {
    puVar2 = *(undefined8 **)(param_1 + 8);
    uVar4 = FUN_180022df0(*puVar2,puVar2[3]);
    cVar3 = FUN_180027e90(*puVar2,uVar4);
    DAT_1803043d4 = cVar3 != '\0';
    if ((bool)DAT_1803043d4) {
      plVar1 = (longlong *)((longlong *)*puVar2)[1];
                    /* WARNING: Could not recover jumptable at 0x000180027ed0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*plVar1 + 0x348))(plVar1,uVar4,*(undefined8 *)(*(longlong *)*puVar2 + 0xbd8),0);
      return;
    }
  }
  return;
}

// CALLBACK RVA 0x42be0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/access_events/access_events.c
// Differential report: analysis/module_behavior_recovery/access_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x42be0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180042be0(longlong param_1)

{
  longlong *plVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  
  if ((DAT_1803043d4 == '\x01') && (*(char *)(param_1 + 0x10) == '\0')) {
    puVar2 = *(undefined8 **)(param_1 + 8);
    uVar3 = FUN_180022df0(*puVar2,puVar2[3]);
    plVar1 = (longlong *)((longlong *)*puVar2)[1];
                    /* WARNING: Could not recover jumptable at 0x000180027ed0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar1 + 0x348))
              (plVar1,uVar3,*(undefined8 *)(*(longlong *)*puVar2 + 0xbd8),DAT_1803043d4);
    return;
  }
  return;
}

// CANDIDATE_LOCAL RVA 0x42c30; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x42c30; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong FUN_180042c30(void)

{
  undefined8 in_RAX;
  ulonglong uVar1;
  
  if (DAT_1802f3174 == '\x01') {
    uVar1 = CONCAT71((int7)((ulonglong)in_RAX >> 8),0 < _DAT_1803043d8 | DAT_1803043dc);
  }
  else {
    uVar1 = 0;
  }
  return uVar1 & 0xffffffffffffff01;
}

