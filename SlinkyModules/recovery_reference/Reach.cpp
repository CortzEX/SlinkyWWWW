// Recovered decompiler view: Reach
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x2ffb0, 0x30180); proximity does not prove ownership.

// CALLBACK RVA 0x2ffb0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/simple_events/simple_events.c
// Differential report: analysis/module_behavior_recovery/simple_events/simple_events_verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2ffb0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002ffb0(longlong param_1)

{
  undefined8 *puVar1;
  char cVar2;
  int iVar3;
  
  if (0 < _DAT_1802f9d84) {
    _DAT_1802f9d84 = _DAT_1802f9d84 + -1;
  }
  puVar1 = *(undefined8 **)(param_1 + 8);
  if ((DAT_1802ea7e8 != '\x01') || (cVar2 = FUN_180023690(*puVar1,puVar1[5]), cVar2 != '\0')) {
    if ((_DAT_1802f9d84 == 0) && (iVar3 = FUN_1800239d0(*puVar1,puVar1[5]), iVar3 != _DAT_1802f9d80)
       ) {
      _DAT_1802f9d84 = 9;
      _DAT_1802f9d80 = iVar3;
    }
    if ((float)_DAT_1802f9d84 < _DAT_1802ea7c8) {
      *(undefined1 *)(param_1 + 0x10) = 1;
      *(double *)(param_1 + 0x18) = (double)_DAT_1802ea790;
    }
  }
  return;
}

// UI RVA 0x30060; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x30060; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180030060(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180150ddc);
  FUN_18000cf30(param_2,param_1,0x1802ea760);
  FUN_180013e90(param_1,param_2,&UNK_180150de1);
  FUN_18000cf30(param_2,param_1,0x1802ea798);
  FUN_180013e90(param_1,param_2,&UNK_180150dea);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802ea7e0,0x1802ea7d0,&DAT_1802ea7e8);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x300e0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x300e0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_1800300e0(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c450(param_1,&UNK_180150df5,0x1802ea760);
  FUN_18000c450(param_1,&UNK_180150dfe,0x1802ea798);
  uVar1 = uRam00000001802ea7e9;
  uVar2 = DAT_1802ea7e8;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180150e0c,DAT_1802ea7e8);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802ea7e8;
      break;
    case 2:
      uRam00000001802ea7e9 = DAT_1802ea7e8;
      break;
    case 3:
      uVar2 = uRam00000001802ea7e9;
    }
  }
  DAT_1802ea7e8 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x30140; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x30140; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180030140(void)

{
  FUN_1800ab710(_DAT_1802ea790,0x20,&UNK_180150e1b,(double)_DAT_1802ea790);
  return;
}

