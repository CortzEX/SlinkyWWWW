// Recovered decompiler view: Fast Accel
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x42320, 0x42650); proximity does not prove ownership.

// CALLBACK RVA 0x42320; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/fast_accel/fast_accel.c
// Differential report: analysis/module_behavior_recovery/fast_accel/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x42320; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180042320(longlong param_1)

{
  float fVar1;
  undefined8 *puVar2;
  double dVar3;
  char cVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  double dVar8;
  float fVar9;
  float fVar10;
  double dStack_88;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  double dStack_78;
  double dStack_70;
  undefined4 uStack_68;
  undefined4 uStack_64;
  double dStack_60;
  
  if ((((*(float *)(param_1 + 0x14) == 0.0) && (!NAN(*(float *)(param_1 + 0x14)))) &&
      (*(float *)(param_1 + 0x10) == 0.0)) && (!NAN(*(float *)(param_1 + 0x10)))) {
    return;
  }
  puVar2 = *(undefined8 **)(param_1 + 8);
  if ((DAT_1802f2a58 == '\x01') && (cVar4 = FUN_1800380b0(*puVar2,puVar2[5]), cVar4 == '\0')) {
    return;
  }
  if ((DAT_1802f2a78 == '\x01') && (iVar5 = FUN_1800239f0(*puVar2,puVar2[5]), 0 < iVar5)) {
    return;
  }
  FUN_180023550(&dStack_70,*puVar2,puVar2[5]);
  dVar8 = (double)func_0x00018013cfd0(SUB84(dStack_70,0),dStack_60);
  if (((dVar8 != 0.0) || (NAN(dVar8))) && (cVar4 = FUN_180023780(*puVar2,puVar2[5]), cVar4 != '\0'))
  {
    fVar7 = *(float *)(param_1 + 0x10);
    fVar1 = *(float *)(param_1 + 0x14);
    fVar10 = *(float *)(param_1 + 0x18);
    fVar6 = (float)func_0x0001800ab7c0(fVar7,fVar1);
    fVar9 = _DAT_180154700;
    if (_DAT_180154700 <= fVar6) {
      fVar9 = fVar6;
    }
    fVar10 = fVar10 / fVar9;
    fVar7 = (float)func_0x0001800ab7c0(fVar7 * fVar10,fVar10 * fVar1);
    dVar3 = (double)fVar7;
    dVar3 = (((((((((((((((((((dVar3 + 0.0) * _DAT_180154708 + dVar3) * _DAT_180154708 + dVar3) *
                            _DAT_180154708 + dVar3) * _DAT_180154708 + dVar3) * _DAT_180154708 +
                         dVar3) * _DAT_180154708 + dVar3) * _DAT_180154708 + dVar3) * _DAT_180154708
                      + dVar3) * _DAT_180154708 + dVar3) * _DAT_180154708 + dVar3) * _DAT_180154708
                   + dVar3) * _DAT_180154708 + dVar3) * _DAT_180154708 + dVar3) * _DAT_180154708 +
                dVar3) * _DAT_180154708 + dVar3) * _DAT_180154708 + dVar3) * _DAT_180154708 + dVar3)
             * _DAT_180154708 + dVar3) * _DAT_180154708 + dVar3;
    if ((*(char *)(param_1 + 0x1c) == '\x01') &&
       (cVar4 = FUN_180023690(*puVar2,puVar2[5]), cVar4 != '\0')) {
      dVar3 = dVar3 + _DAT_180154710;
    }
    if (dVar8 <= dVar3) {
      dStack_78 = (double)FUN_18000a2d0(SUB84(dVar8,0),dVar3,(double)_DAT_1802f2a38);
      dStack_70 = (dStack_70 / dVar8) * dStack_78;
      dStack_78 = (dStack_60 / dVar8) * dStack_78;
      uStack_80 = uStack_68;
      uStack_7c = uStack_64;
      dStack_60 = dStack_78;
      dStack_88 = dStack_70;
      FUN_1800235f0(*puVar2,puVar2[5],&dStack_88);
    }
  }
  return;
}

// UI RVA 0x42580; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x42580; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180042580(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180154763);
  FUN_18000cf30(param_2,param_1,0x1802f2a08);
  FUN_180013e90(param_1,param_2,&UNK_180154768);
  FUN_18000cef0(param_2,param_1,0x1802f2a60);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802f2a50,0x1802f2a40,&DAT_1802f2a58);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x425f0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x425f0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_1800425f0(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c450(param_1,&UNK_180154773,0x1802f2a08);
  FUN_18000c3b0(param_1,&UNK_180154780,0x1802f2a60);
  uVar1 = uRam00000001802f2a59;
  uVar2 = DAT_1802f2a58;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180154794,DAT_1802f2a58);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802f2a58;
      break;
    case 2:
      uRam00000001802f2a59 = DAT_1802f2a58;
      break;
    case 3:
      uVar2 = uRam00000001802f2a59;
    }
  }
  DAT_1802f2a58 = uVar2;
  return;
}

