// Recovered decompiler view: Hitboxes
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x33fc0, 0x34080); proximity does not prove ownership.

// CALLBACK RVA 0x33fc0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/simple_events/simple_events.c
// Differential report: analysis/module_behavior_recovery/simple_events/simple_events_verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x33fc0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180033fc0(longlong param_1)

{
  *(undefined1 *)(param_1 + 0x10) = 1;
  *(double *)(param_1 + 0x20) = (double)_DAT_1802ecee8;
  return;
}

// UI RVA 0x33fe0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x33fe0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180033fe0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  undefined8 unaff_RBP;
  undefined8 unaff_RDI;
  undefined4 uVar2;
  
  uVar2 = (undefined4)((ulonglong)unaff_RDI >> 0x20);
  FUN_180013e90(param_1,param_2,&UNK_180151bf7);
  cVar1 = FUN_180013f40(param_1,param_2,uRam00000001802ecec8,uRam00000001802eced0,0x1802eceb8,
                        uRam00000001802ecee0,uRam00000001802ecee4,uRam00000001802eced8,
                        CONCAT44(uVar2,uRam00000001802ecedc),&DAT_1802ecee8,unaff_RBP);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x34020; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x34020; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180034020(undefined8 *param_1)

{
  double dVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  undefined8 uVar6;
  longlong lVar7;
  float fVar8;
  
  fVar4 = _DAT_1802ecee8;
  if (*(char *)((longlong)param_1 + 0xc) == '\0') {
    switch(*(undefined4 *)(param_1 + 1)) {
    case 0:
      uVar6 = FUN_18004e4d0(*param_1);
      fVar4 = fRam00000001802eceec;
      fVar3 = fRam00000001802ecee4;
      fVar2 = fRam00000001802ecee0;
      iVar5 = FUN_18004d150(uVar6);
      if (iVar5 != 0) {
        dVar1 = (double)FUN_18004d130(uVar6);
        fVar8 = (float)dVar1;
        fVar4 = fVar2;
        if ((fVar2 <= fVar8) && (fVar4 = fVar8, fVar3 < fVar8)) {
          fVar4 = fVar3;
        }
      }
      break;
    case 1:
      lVar7 = FUN_18004eeb0(*param_1,&UNK_180151bfc,(double)_DAT_1802ecee8);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar7 == 0;
      fVar4 = _DAT_1802ecee8;
      break;
    case 2:
      fRam00000001802eceec = _DAT_1802ecee8;
      break;
    case 3:
      fVar4 = fRam00000001802eceec;
    }
  }
  _DAT_1802ecee8 = fVar4;
  return;
}

// CANDIDATE_LOCAL RVA 0x34040; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x34040; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180034040(void)

{
  FUN_1800ab710(_DAT_1802ecee8,0x20,&UNK_180151c03,(double)_DAT_1802ecee8);
  return;
}

