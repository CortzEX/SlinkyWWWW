// Recovered decompiler view: No Slow
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x42a20, 0x42b80); proximity does not prove ownership.

// CALLBACK RVA 0x42a20; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/simple_events/simple_events.c
// Differential report: analysis/module_behavior_recovery/simple_events/simple_events_verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x42a20; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180042a20(longlong param_1)

{
  undefined8 *puVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  longlong lVar5;
  float *pfVar6;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  cVar2 = FUN_180023f90(*puVar1,puVar1[5]);
  if (cVar2 == '\0') {
    return;
  }
  lVar5 = FUN_180028a50(*puVar1,puVar1[5]);
  if (lVar5 == 0) {
    return;
  }
  iVar3 = FUN_180025c50(*puVar1,lVar5);
  uVar4 = iVar3 - 0x105;
  if (uVar4 < 0x17) {
    if ((0x4088c0U >> (uVar4 & 0x1f) & 1) != 0) {
      pfVar6 = (float *)0x1802f2f08;
      goto LAB_180042a7a;
    }
    if (uVar4 == 0) {
      pfVar6 = (float *)0x1802f2ed0;
      goto LAB_180042a7a;
    }
  }
  pfVar6 = (float *)0x1802f2f40;
LAB_180042a7a:
  *(ulonglong *)(param_1 + 0x10) =
       CONCAT44((float)(((double)*pfVar6 / _DAT_180154800) *
                       (double)(float)((ulonglong)*(undefined8 *)(param_1 + 0x10) >> 0x20)),
                (float)(((double)*pfVar6 / _DAT_180154800) *
                       (double)(float)*(undefined8 *)(param_1 + 0x10)));
  return;
}

// UI RVA 0x42ac0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x42ac0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180042ac0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  undefined8 unaff_RBP;
  undefined8 unaff_RDI;
  undefined4 uVar2;
  
  uVar2 = (undefined4)((ulonglong)unaff_RDI >> 0x20);
  FUN_180013e90(param_1,param_2,&UNK_180154851);
  FUN_18000cf30(param_2,param_1,0x1802f2ed8);
  FUN_18000cf30(param_2,param_1,0x1802f2ea0);
  cVar1 = FUN_180013f40(param_1,param_2,uRam00000001802f2f20,uRam00000001802f2f28,0x1802f2f10,
                        uRam00000001802f2f38,uRam00000001802f2f3c,uRam00000001802f2f30,
                        CONCAT44(uVar2,uRam00000001802f2f34),0x1802f2f40,unaff_RBP);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x42b20; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x42b20; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180042b20(undefined8 *param_1)

{
  double dVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  undefined8 uVar6;
  longlong lVar7;
  float fVar8;
  
  FUN_18000c450(param_1,&UNK_180154860,0x1802f2ed8);
  FUN_18000c450(param_1,&UNK_18015486b,0x1802f2ea0);
  fVar4 = fRam00000001802f2f40;
  if (*(char *)((longlong)param_1 + 0xc) == '\0') {
    switch(*(undefined4 *)(param_1 + 1)) {
    case 0:
      uVar6 = FUN_18004e4d0(*param_1);
      fVar4 = fRam00000001802f2f44;
      fVar3 = fRam00000001802f2f3c;
      fVar2 = fRam00000001802f2f38;
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
      lVar7 = FUN_18004eeb0(*param_1,&UNK_180154874,(double)fRam00000001802f2f40);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar7 == 0;
      fVar4 = fRam00000001802f2f40;
      break;
    case 2:
      fRam00000001802f2f44 = fRam00000001802f2f40;
      break;
    case 3:
      fVar4 = fRam00000001802f2f44;
    }
  }
  fRam00000001802f2f40 = fVar4;
  return;
}

