// Recovered decompiler view: Sprint
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x35d80, 0x35fd0); proximity does not prove ownership.

// CALLBACK RVA 0x35d80; ownership: direct_reference
// Verified C implementation: analysis/recovered_native_source/sprint_behavior.c
// Differential report: analysis/recovered_native_source/sprint_behavior_verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x35d80; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180035d80(longlong param_1)

{
  longlong *plVar1;
  undefined8 *puVar2;
  char cVar3;
  longlong lVar4;
  undefined8 uVar5;
  byte bVar6;
  byte bVar7;
  undefined8 unaff_RBX;
  undefined8 unaff_RBP;
  
  puVar2 = *(undefined8 **)(param_1 + 8);
  lVar4 = FUN_180022c90(*puVar2,puVar2[3]);
  bVar6 = lVar4 == 0 | DAT_1802eda68;
  bVar7 = lVar4 == 0 | DAT_1802eda68 & 1;
  uVar5 = FUN_180022cf0(*puVar2,puVar2[3]);
  uVar5 = FUN_180025210(*puVar2,uVar5);
  FUN_180025460(*puVar2,uVar5,CONCAT71((int7)((ulonglong)unaff_RBX >> 8),bVar6) & 0xffffff01);
  if (puVar2[5] != 0) {
    if (bVar7 == 0) {
      bVar7 = DAT_1802fc448;
      if (DAT_1802fc448 == 1) {
        plVar1 = (longlong *)((longlong *)*puVar2)[1];
        (**(code **)(*plVar1 + 0x1e8))
                  (plVar1,puVar2[5],*(undefined8 *)(*(longlong *)*puVar2 + 0x230),0,unaff_RBP);
        return;
      }
    }
    else {
      cVar3 = FUN_180023690(*puVar2);
      if (cVar3 != '\0') {
        FUN_1800236c0(*puVar2,puVar2[5],1);
      }
    }
  }
  DAT_1802fc448 = bVar7;
  return;
}

// CALLBACK RVA 0x35e30; ownership: direct_reference
// Verified C implementation: analysis/recovered_native_source/sprint_behavior.c
// Differential report: analysis/recovered_native_source/sprint_behavior_verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x35e30; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180035e30(longlong param_1)

{
  float fVar1;
  longlong *plVar2;
  undefined8 *puVar3;
  char cVar4;
  char cVar5;
  undefined8 unaff_RBP;
  
  puVar3 = *(undefined8 **)(param_1 + 8);
  if (((((*(float *)(param_1 + 0x14) != 0.0) || (NAN(*(float *)(param_1 + 0x14)))) ||
       (*(float *)(param_1 + 0x10) != 0.0)) || (NAN(*(float *)(param_1 + 0x10)))) &&
     ((cVar5 = FUN_180023f90(*puVar3,puVar3[5]), cVar5 == '\0' || (DAT_1802eda88 != '\0')))) {
    fVar1 = *(float *)(param_1 + 0x14);
    cVar4 = DAT_1802edaa8;
    if (((0.0 <= fVar1) && ((cVar4 = cVar5, fVar1 == 0.0 && (!NAN(fVar1))))) &&
       ((*(float *)(param_1 + 0x10) != 0.0 || (NAN(*(float *)(param_1 + 0x10)))))) {
      cVar4 = DAT_1802edac8;
    }
    if (cVar4 != '\0') {
      *(float *)(param_1 + 0x18) = (float)((double)*(float *)(param_1 + 0x18) * _DAT_1801520d0);
      plVar2 = (longlong *)((longlong *)*puVar3)[1];
      (**(code **)(*plVar2 + 0x1e8))
                (plVar2,puVar3[5],*(undefined8 *)(*(longlong *)*puVar3 + 0x230),1,unaff_RBP);
      return;
    }
  }
  return;
}

// UI RVA 0x35ef0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x35ef0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180035ef0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180152129);
  FUN_18000cef0(param_2,param_1,0x1802eda70);
  FUN_18000cef0(param_2,param_1,0x1802eda90);
  FUN_18000cef0(param_2,param_1,0x1802edab0);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802eda60,0x1802eda50,&DAT_1802eda68);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x35f60; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x35f60; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180035f60(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c3b0(param_1,&UNK_180152135,0x1802eda70);
  FUN_18000c3b0(param_1,&UNK_180152146,0x1802eda90);
  FUN_18000c3b0(param_1,&UNK_180152156,0x1802edab0);
  uVar1 = uRam00000001802eda69;
  uVar2 = DAT_1802eda68;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180152165,DAT_1802eda68);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802eda68;
      break;
    case 2:
      uRam00000001802eda69 = DAT_1802eda68;
      break;
    case 3:
      uVar2 = uRam00000001802eda69;
    }
  }
  DAT_1802eda68 = uVar2;
  return;
}

