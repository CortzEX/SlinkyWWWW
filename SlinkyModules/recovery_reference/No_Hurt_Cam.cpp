// Recovered decompiler view: No Hurt Cam
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x41f40, 0x41f90); proximity does not prove ownership.

// DIRECT_BEHAVIOR RVA 0x76a0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x76a0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800076a0(undefined8 param_1)

{
  undefined8 uStack_18;
  undefined8 uStack_10;
  
  uStack_18 = _DAT_1802f6ef0;
  uStack_10 = param_1;
  FUN_18002a000(&uStack_18);
  if (*(char *)(_DAT_18013e4a0 + 0x14) == '\x01') {
    FUN_180041f40(&uStack_18);
  }
  FUN_180027a20(&uStack_18);
  return;
}

// DIRECT_BEHAVIOR RVA 0x41f40; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x41f40; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180041f40(longlong *param_1)

{
  undefined8 uVar1;
  longlong lVar2;
  
  uVar1 = FUN_180022c00();
  lVar2 = FUN_180022c30(param_1,uVar1);
  if (lVar2 != 0) {
                    /* WARNING: Could not recover jumptable at 0x000180023a30. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*(longlong *)param_1[1] + 0x368))
              ((longlong *)param_1[1],lVar2,*(undefined8 *)(*param_1 + 0x550),0x7fffffff);
    return;
  }
  return;
}

