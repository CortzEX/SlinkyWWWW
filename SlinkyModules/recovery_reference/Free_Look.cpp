// Recovered decompiler view: Free Look
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x37020, 0x37180); proximity does not prove ownership.

// CALLBACK RVA 0x37020; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/state_events/state_events.c
// Differential report: analysis/module_behavior_recovery/state_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x37020; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180037020(longlong param_1)

{
  longlong *plVar1;
  undefined8 *puVar2;
  char cVar3;
  undefined8 uVar4;
  
  if ((*(longlong *)(param_1 + 0x10) == 0x1802edef0) &&
     (puVar2 = *(undefined8 **)(param_1 + 8), puVar2[4] != 0)) {
    if (*(char *)(param_1 + 0x18) == '\x01') {
      DAT_1802fc508 = '\x01';
      cVar3 = FUN_180029f80();
      if (cVar3 == '\0') {
        _DAT_1802fc510 = FUN_180023170(*puVar2,puVar2[5]);
      }
      else {
        _DAT_1802fc510 = FUN_180029f90();
      }
    }
    uVar4 = FUN_180022cf0(*puVar2,puVar2[3]);
    if (*(char *)(param_1 + 0x18) != '\0') {
      _DAT_1802fc518 = FUN_180025310(*puVar2,uVar4);
      plVar1 = (longlong *)((longlong *)*puVar2)[1];
                    /* WARNING: Could not recover jumptable at 0x000180025350. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*plVar1 + 0x368))
                (plVar1,uVar4,*(undefined8 *)(*(longlong *)*puVar2 + 0x3c0),_DAT_1802ee148);
      return;
    }
    FUN_180025330(*puVar2,uVar4,_DAT_1802fc518);
    if (DAT_1802fc508 == '\x01') {
      FUN_180029fa0(_DAT_1802fc510);
      DAT_1802fc508 = '\0';
    }
  }
  return;
}

// CALLBACK RVA 0x37100; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/state_events/state_events.c
// Differential report: analysis/module_behavior_recovery/state_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x37100; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180037100(longlong param_1)

{
  *(undefined1 *)(param_1 + 8) = 1;
  *(undefined8 *)(param_1 + 0xc) = _DAT_1802fc510;
  return;
}

// UI RVA 0x37120; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x37120; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180037120(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180152405);
  cVar1 = FUN_180014d00(param_1,param_2,uRam00000001802ee130,0x1802ee118,uRam00000001802ee138,
                        uRam00000001802ee140,&DAT_1802ee148,uRam00000001802ee150);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x37160; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x37160; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180037160(undefined8 *param_1)

{
  undefined8 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  longlong lVar5;
  longlong lVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  
  uVar2 = uRam00000001802ee14c;
  uVar3 = _DAT_1802ee148;
  if (*(char *)((longlong)param_1 + 0xc) == '\0') {
    switch(*(undefined4 *)(param_1 + 1)) {
    case 0:
      lVar5 = FUN_18004e4d0(*param_1);
      iVar4 = FUN_18004d110(lVar5);
      lVar6 = lRam00000001802ee140;
      uVar3 = uVar2;
      if ((iVar4 != 0) && (uVar7 = (ulonglong)uRam00000001802ee138, uVar7 != 0)) {
        uVar1 = *(undefined8 *)(lVar5 + 0x20);
        uVar8 = 0;
        do {
          iVar4 = func_0x00018013d0a0(*(undefined8 *)(lVar6 + uVar8 * 8),uVar1);
          if (iVar4 == 0) {
            _DAT_1802ee148 = (int)uVar8;
            return;
          }
          uVar8 = uVar8 + 1;
        } while (uVar7 != uVar8);
      }
      break;
    case 1:
      lVar6 = FUN_18004f080(*param_1,&UNK_18015240a,
                            *(undefined8 *)(lRam00000001802ee140 + (ulonglong)_DAT_1802ee148 * 8));
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar6 == 0;
      uVar3 = _DAT_1802ee148;
      break;
    case 2:
      uRam00000001802ee14c = _DAT_1802ee148;
      break;
    case 3:
      uVar3 = uRam00000001802ee14c;
    }
  }
  _DAT_1802ee148 = uVar3;
  return;
}

