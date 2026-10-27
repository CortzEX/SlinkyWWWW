// Recovered decompiler view: Strafe
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x41f90, 0x42320); proximity does not prove ownership.

// CALLBACK RVA 0x41f90; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/strafe/strafe.c
// Differential report: analysis/module_behavior_recovery/strafe/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x41f90; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180041f90(longlong param_1)

{
  DAT_1803043cc = FUN_180023690(**(undefined8 **)(param_1 + 8),(*(undefined8 **)(param_1 + 8))[5]);
  return;
}

// CALLBACK RVA 0x41fc0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/strafe/strafe.c
// Differential report: analysis/module_behavior_recovery/strafe/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x41fc0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180041fc0(longlong param_1)

{
  float fVar1;
  undefined8 *puVar2;
  double dVar3;
  char cVar4;
  int iVar5;
  float fVar6;
  float *pfVar7;
  byte bVar8;
  undefined4 uVar9;
  uint uVar10;
  double dVar11;
  undefined4 uVar12;
  double dVar13;
  undefined8 uStack_98;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined8 uStack_70;
  
  if ((((*(float *)(param_1 + 0x14) == 0.0) && (!NAN(*(float *)(param_1 + 0x14)))) &&
      (*(float *)(param_1 + 0x10) == 0.0)) && (!NAN(*(float *)(param_1 + 0x10)))) {
    return;
  }
  puVar2 = *(undefined8 **)(param_1 + 8);
  if ((DAT_1802f27f0 == '\x01') && (cVar4 = FUN_1800380b0(*puVar2,puVar2[5]), cVar4 == '\0')) {
    return;
  }
  iVar5 = FUN_1800239f0(*puVar2,puVar2[5]);
  if (_DAT_1802f2728 < (float)iVar5) {
    return;
  }
  cVar4 = FUN_180023780(*puVar2,puVar2[5]);
  if (cVar4 == '\0') {
    pfVar7 = (float *)0x1802f2760;
  }
  else {
    if (*(char *)(param_1 + 0x1c) == '\x01') {
      bVar8 = DAT_1803043cc ^ 1;
      pfVar7 = (float *)0x1802f2798;
      goto LAB_180042084;
    }
    pfVar7 = (float *)0x1802f27d0;
  }
  bVar8 = 0;
LAB_180042084:
  fVar1 = *pfVar7;
  if ((fVar1 != 0.0) || (NAN(fVar1))) {
    FUN_180023550(&uStack_80,*puVar2,puVar2[5]);
    dVar11 = (double)func_0x00018013cfd0((undefined4)uStack_80);
    if (bVar8 != 0) {
      dVar11 = dVar11 + _DAT_1801545f0;
    }
    fVar6 = (float)FUN_180023170(*puVar2,puVar2[5]);
    if (*(float *)(param_1 + 0x10) < 0.0) {
      uVar9 = (undefined4)_DAT_1801545f8;
      uVar12 = (undefined4)((ulonglong)_DAT_1801545f8 >> 0x20);
    }
    else {
      uVar9 = 0;
      uVar12 = 0;
    }
    if (0.0 < *(float *)(param_1 + 0x10)) {
      uVar9 = (undefined4)_DAT_180154600;
      uVar12 = (undefined4)((ulonglong)_DAT_180154600 >> 0x20);
    }
    dVar13 = (double)fVar6;
    if (*(float *)(param_1 + 0x14) <= 0.0) {
      if (0.0 <= *(float *)(param_1 + 0x14)) {
        dVar3 = (double)CONCAT44(uVar12,uVar9) * _DAT_180154608;
      }
      else {
        dVar13 = dVar13 + _DAT_180154610;
        dVar3 = (double)CONCAT44(uVar12,uVar9) * _DAT_180154618;
      }
    }
    else {
      dVar3 = (double)CONCAT44(uVar12,uVar9) * _DAT_180154620;
    }
    fVar6 = (float)(((dVar3 + dVar13) * _DAT_180154628) / _DAT_180154610);
    uVar10 = func_0x0001800b1cf0(fVar6);
    uStack_80 = FUN_18000a2d0((undefined4)uStack_80,
                              (double)(float)(uVar10 ^ _DAT_180154630) * dVar11,(double)fVar1);
    fVar6 = (float)func_0x0001800b3590(fVar6);
    uStack_88 = FUN_18000a2d0((undefined4)uStack_70,(double)fVar6 * dVar11,(double)fVar1);
    uStack_90 = uStack_78;
    uStack_8c = uStack_74;
    uStack_70 = uStack_88;
    uStack_98 = uStack_80;
    FUN_1800235f0(*puVar2,puVar2[5],&uStack_98);
  }
  return;
}

// UI RVA 0x42200; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x42200; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180042200(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_18015469f);
  FUN_18000cf30(param_2,param_1,0x1802f2768);
  FUN_18000cf30(param_2,param_1,0x1802f27a0);
  FUN_18000cf30(param_2,param_1,0x1802f2730);
  FUN_180013e90(param_1,param_2,&UNK_1801546a8);
  FUN_18000cf30(param_2,param_1,0x1802f26f8);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802f27e8,0x1802f27d8,&DAT_1802f27f0);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x422a0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x422a0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_1800422a0(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c450(param_1,&UNK_1801546b3,0x1802f2768);
  FUN_18000c450(param_1,&UNK_1801546c1,0x1802f27a0);
  FUN_18000c450(param_1,&UNK_1801546d1,0x1802f2730);
  FUN_18000c450(param_1,&UNK_1801546de,0x1802f26f8);
  uVar1 = uRam00000001802f27f1;
  uVar2 = DAT_1802f27f0;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_1801546ec,DAT_1802f27f0);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802f27f0;
      break;
    case 2:
      uRam00000001802f27f1 = DAT_1802f27f0;
      break;
    case 3:
      uVar2 = uRam00000001802f27f1;
    }
  }
  DAT_1802f27f0 = uVar2;
  return;
}

