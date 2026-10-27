// Recovered decompiler view: Auto Block
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x31570, 0x31e10); proximity does not prove ownership.

// CALLBACK RVA 0x31570; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/connected_auto_block/connected_auto_block.c
// Differential report: analysis/module_behavior_recovery/connected_auto_block/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x31570; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong FUN_180031570(longlong param_1)

{
  double *pdVar1;
  undefined8 *puVar2;
  bool bVar3;
  uint uVar4;
  char cVar5;
  byte bVar6;
  bool bVar7;
  byte bVar8;
  int iVar9;
  undefined4 uVar10;
  int iVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  ulonglong uVar14;
  int iVar15;
  
  DAT_1802f9e10 = 0;
  puVar2 = *(undefined8 **)(param_1 + 8);
  if (DAT_1802f9e11 == '\x01') {
    if ((puVar2[5] != 0) && (cVar5 = FUN_180023f90(*puVar2), cVar5 == '\0')) {
      FUN_180024020(*puVar2,puVar2[5],0);
    }
    DAT_1802f9e11 = '\0';
  }
  if (_DAT_1802f9e00 != 0) {
    _DAT_1802f9e00 = _DAT_1802f9e00 + -1;
  }
  if (*(char *)(puVar2 + 8) == '\0') {
    if (DAT_1802f9e19 == 1) {
      uVar13 = FUN_180022cf0(*puVar2,puVar2[3]);
      uVar13 = FUN_180024f90(*puVar2,uVar13);
      uVar10 = FUN_180025490(*puVar2,uVar13);
      FUN_180025460(*puVar2,uVar13,uVar10);
      DAT_1802f9e19 = 0;
    }
    DAT_1802f9e12 = '\0';
    goto LAB_18003172a;
  }
  iVar9 = FUN_1800239f0(*puVar2,puVar2[5]);
  uVar13 = *puVar2;
  uVar12 = FUN_180028a50(uVar13,puVar2[5]);
  cVar5 = FUN_180028ac0(uVar13,uVar12);
  DAT_1802f9e12 = '\0';
  if (cVar5 == '\0') {
    bVar3 = false;
    bVar6 = 0;
    bVar7 = false;
    if (DAT_1802f9e19 == 1) goto LAB_180031760;
  }
  else {
    if ((((DAT_1802eb300 == '\x01') && (*(char *)(puVar2[6] + 1) == '\0')) ||
        (cVar5 = FUN_180042c30(), cVar5 != '\0')) ||
       (DAT_1802f9e12 = DAT_1802eb320, DAT_1802eb320 != *(char *)(puVar2[6] + 2))) {
      bVar3 = false;
LAB_180031760:
      uVar13 = FUN_180022cf0(*puVar2,puVar2[3]);
      uVar12 = FUN_180024f90(*puVar2,uVar13);
      uVar13 = *puVar2;
      if (DAT_1802f9e12 == '\0') {
        uVar10 = FUN_180025490(uVar13,uVar12);
      }
      else {
        uVar10 = 0;
      }
      FUN_180025460(uVar13,uVar12,uVar10);
      bVar6 = 0;
    }
    else {
      bVar3 = true;
      if (((iVar9 == 0) && (DAT_1802eb340 != '\0')) ||
         (iVar15 = (int)_DAT_1802eb2e0,
         bVar6 = FUN_18000a460(_DAT_1802eb2e0 - (float)(int)_DAT_1802eb2e0), cVar5 = DAT_1802f9e18,
         (int)((uint)bVar6 + iVar15) < iVar9)) goto LAB_180031760;
      uVar13 = FUN_180022cf0(*puVar2,puVar2[3]);
      uVar13 = FUN_180024f90(*puVar2,uVar13);
      FUN_180025460(*puVar2,uVar13,cVar5);
      bVar6 = 1;
      if (cVar5 == '\x01') {
        FUN_180025380(*puVar2,uVar13);
        bVar3 = true;
      }
      else {
        bVar3 = true;
      }
    }
    bVar7 = false;
    DAT_1802f9e19 = bVar6;
    if (((bVar3) && (DAT_1802eb360 != '\0')) && (bVar7 = true, DAT_1802eb380 == '\x01')) {
      if (*(longlong *)(puVar2[7] + 8) == 0) {
        bVar7 = false;
      }
      else {
        pdVar1 = (double *)(puVar2[7] + 0x10);
        bVar7 = *pdVar1 <= (double)(_DAT_1802eb3b8 * _DAT_1802eb3b8) &&
                (double)(_DAT_1802eb3b8 * _DAT_1802eb3b8) != *pdVar1;
      }
    }
  }
  if (iVar9 == 10) {
    _DAT_1802f9e00 = 0;
  }
  _DAT_1802f9e08 = _DAT_1802f9e08 + 1;
  iVar9 = 0;
  bVar8 = 0;
  DAT_1802f9e10 = bVar7;
  if (9 < _DAT_1802f9e08) {
    iVar15 = FUN_180023760(*puVar2,puVar2[5]);
    iVar11 = FUN_1800239d0(*puVar2,puVar2[5]);
    if (iVar15 == iVar11 + 1) {
      _DAT_1802f9e08 = 0;
      bVar8 = 1;
    }
    else {
      bVar8 = 0;
    }
  }
  if (*(longlong *)(puVar2[7] + 8) != 0) {
    iVar9 = FUN_180023720(*puVar2);
  }
  uVar4 = _DAT_1802f9e14;
  if (iVar9 != _DAT_1802f9e0c) {
    _DAT_1802f9e08 = 0;
    bVar8 = 1;
    _DAT_1802f9e0c = iVar9;
  }
  uVar14 = (ulonglong)_DAT_1802f9e14;
  if (_DAT_1802f9e14 != 0) {
    if ((bVar8 & DAT_1802eb3d8) == 1) {
      LOCK();
      _DAT_1802f9e14 = 0;
      UNLOCK();
    }
    else {
      LOCK();
      _DAT_1802f9e14 = _DAT_1802f9e14 - 1;
      UNLOCK();
    }
    uVar14 = (ulonglong)uVar4;
    if ((DAT_1802eb3f8 == '\x01') && (uVar14 = (ulonglong)_DAT_1802f9e14, _DAT_1802f9e14 == 0)) {
      _DAT_1802f9e00 = 0;
    }
  }
  if (DAT_1802f9e18 != '\0') {
    iVar15 = _DAT_1802f9e04 + 1;
    iVar9 = (int)_DAT_1802eb238;
    _DAT_1802f9e04 = iVar15;
    bVar8 = FUN_18000a460(_DAT_1802eb238 - (float)(int)_DAT_1802eb238);
    iVar9 = (uint)bVar8 + iVar9;
    if ((bVar6 & iVar15 < iVar9) != 0) {
      return (ulonglong)CONCAT31((int3)((uint)iVar9 >> 8),iVar15 < iVar9);
    }
    uVar13 = FUN_180022cf0(*puVar2,puVar2[3]);
    uVar13 = FUN_180024f90(*puVar2,uVar13);
    FUN_180025460(*puVar2,uVar13,0);
    DAT_1802f9e19 = 1;
    uVar14 = FUN_18000a460(_DAT_1802eb270);
    if ((char)uVar14 != '\0') {
      iVar9 = (int)_DAT_1802eb2a8;
      bVar6 = FUN_18000a460(_DAT_1802eb2a8 - (float)(int)_DAT_1802eb2a8);
      LOCK();
      uVar14 = (ulonglong)_DAT_1802f9e14;
      UNLOCK();
      _DAT_1802f9e14 = (uint)bVar6 + iVar9;
    }
    DAT_1802f9e18 = 0;
    return uVar14;
  }
  if ((bVar6 & _DAT_1802f9e00 == 0) != 1) {
    return CONCAT71((int7)(uVar14 >> 8),_DAT_1802f9e00 == 0);
  }
  uVar14 = puVar2[7];
  if (*(longlong *)(uVar14 + 8) == 0) {
    return uVar14;
  }
  if ((double)(_DAT_1802eb3b8 * _DAT_1802eb3b8) < *(double *)(uVar14 + 0x10) ||
      (double)(_DAT_1802eb3b8 * _DAT_1802eb3b8) == *(double *)(uVar14 + 0x10)) {
    return uVar14;
  }
  uVar13 = FUN_180022cf0(*puVar2,puVar2[3]);
  uVar13 = FUN_180024f90(*puVar2,uVar13);
  FUN_180025460(*puVar2,uVar13,1);
  FUN_180025380(*puVar2,uVar13);
  DAT_1802f9e19 = 1;
  DAT_1802f9e18 = '\x01';
  _DAT_1802f9e00 = 10;
  _DAT_1802f9e04 = 0;
LAB_18003172a:
  LOCK();
  uVar14 = (ulonglong)_DAT_1802f9e14;
  UNLOCK();
  _DAT_1802f9e14 = 0;
  return uVar14;
}

// CALLBACK RVA 0x31a50; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/connected_auto_block/connected_auto_block.c
// Differential report: analysis/module_behavior_recovery/connected_auto_block/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x31a50; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180031a50(longlong param_1)

{
  if (_DAT_1802f9e14 != 0) {
    *(undefined4 *)(param_1 + 0x24) = 1;
  }
  return;
}

// CALLBACK RVA 0x31a70; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/connected_auto_block/connected_auto_block.c
// Differential report: analysis/module_behavior_recovery/connected_auto_block/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x31a70; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong FUN_180031a70(longlong param_1)

{
  undefined8 *puVar1;
  uint uVar2;
  undefined4 uVar3;
  ulonglong uVar4;
  undefined8 uVar5;
  
  uVar4 = 0x1802eaff8;
  if (((*(longlong *)(param_1 + 0x10) == 0x1802eaff8) && (*(char *)(param_1 + 0x18) == '\0')) &&
     ((DAT_1802f9e18 & 1) != 0)) {
    if (DAT_1802f9e19 == '\x01') {
      puVar1 = *(undefined8 **)(param_1 + 8);
      uVar5 = FUN_180022cf0(*puVar1,puVar1[3]);
      uVar5 = FUN_180024f90(*puVar1,uVar5);
      uVar3 = FUN_180025490(*puVar1,uVar5);
      FUN_180025460(*puVar1,uVar5,uVar3);
      DAT_1802f9e19 = '\0';
    }
    uVar2 = _DAT_1802f9e14;
    DAT_1802f9e18 = 0;
    LOCK();
    _DAT_1802f9e14 = 0;
    uVar4 = (ulonglong)uVar2;
    UNLOCK();
  }
  return uVar4;
}

// CALLBACK RVA 0x31b00; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/connected_auto_block/connected_auto_block.c
// Differential report: analysis/module_behavior_recovery/connected_auto_block/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x31b00; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180031b00(longlong param_1)

{
  undefined8 uVar1;
  char cVar2;
  undefined8 uVar3;
  
  if (*(char *)(param_1 + 0x10) == '\0') {
    uVar1 = **(undefined8 **)(param_1 + 8);
    uVar3 = FUN_180028a50(uVar1,(*(undefined8 **)(param_1 + 8))[5]);
    cVar2 = FUN_180028ac0(uVar1,uVar3);
    if (cVar2 == '\0') {
      LOCK();
      _DAT_1802f9e14 = 0;
      UNLOCK();
    }
    if ((DAT_1802f9e12 == '\x01') && ((DAT_1802f9e18 & 1) == 0)) {
      *(undefined1 *)(param_1 + 0x11) = 1;
    }
  }
  return;
}

// CALLBACK RVA 0x31b60; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/connected_auto_block/connected_auto_block.c
// Differential report: analysis/module_behavior_recovery/connected_auto_block/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x31b60; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180031b60(longlong param_1)

{
  longlong *plVar1;
  longlong lVar2;
  longlong *plVar3;
  
  if (DAT_1802f9e10 == '\0') {
    _DAT_1802f9e1c = 72000;
  }
  else {
    lVar2 = (*(undefined8 **)(param_1 + 8))[5];
    if (lVar2 != 0) {
      DAT_1802f9e11 = 1;
      _DAT_1802f9e1c = _DAT_1802f9e1c + -1;
      plVar3 = (longlong *)**(undefined8 **)(param_1 + 8);
      plVar1 = (longlong *)plVar3[1];
                    /* WARNING: Could not recover jumptable at 0x000180024040. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*plVar1 + 0x368))(plVar1,lVar2,*(undefined8 *)(*plVar3 + 0x5a8),_DAT_1802f9e1c);
      return;
    }
  }
  return;
}

// UI RVA 0x31bb0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x31bb0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180031bb0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_1801512da);
  FUN_18000cf30(param_2,param_1,0x1802eb388);
  FUN_18000cf30(param_2,param_1,0x1802eb2b0);
  FUN_18000cf30(param_2,param_1,0x1802eb208);
  FUN_180013e90(param_1,param_2,&UNK_1801512df);
  FUN_18000cef0(param_2,param_1,0x1802eb348);
  if (DAT_1802eb360 == '\x01') {
    FUN_18000cef0(param_2,param_1,0x1802eb368);
  }
  FUN_180013e90(param_1,param_2,&UNK_1801512f5);
  FUN_18000cf30(param_2,param_1,0x1802eb240);
  FUN_18000cf30(param_2,param_1,0x1802eb278);
  FUN_18000cef0(param_2,param_1,0x1802eb3c0);
  FUN_18000cef0(param_2,param_1,0x1802eb3e0);
  FUN_180013e90(param_1,param_2,&UNK_1801512f9);
  FUN_18000cef0(param_2,param_1,0x1802eb2e8);
  FUN_18000cef0(param_2,param_1,0x1802eb308);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802eb338,0x1802eb328,&DAT_1802eb340);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x31cf0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x31cf0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180031cf0(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c450(param_1,&UNK_180151304,0x1802eb388);
  FUN_18000c450(param_1,&UNK_18015130a,0x1802eb2b0);
  FUN_18000c450(param_1,&UNK_180151318,0x1802eb208);
  FUN_18000c3b0(param_1,&UNK_180151326,0x1802eb348);
  FUN_18000c3b0(param_1,&UNK_18015133b,0x1802eb368);
  FUN_18000c450(param_1,&UNK_18015135f,0x1802eb240);
  FUN_18000c450(param_1,&UNK_18015136a,0x1802eb278);
  FUN_18000c3b0(param_1,&UNK_180151377,0x1802eb3c0);
  FUN_18000c3b0(param_1,&UNK_180151388,0x1802eb3e0);
  FUN_18000c3b0(param_1,&UNK_180151394,0x1802eb2e8);
  FUN_18000c3b0(param_1,&UNK_1801513af,0x1802eb308);
  uVar1 = uRam00000001802eb341;
  uVar2 = DAT_1802eb340;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_1801513cb,DAT_1802eb340);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802eb340;
      break;
    case 2:
      uRam00000001802eb341 = DAT_1802eb340;
      break;
    case 3:
      uVar2 = uRam00000001802eb341;
    }
  }
  DAT_1802eb340 = uVar2;
  return;
}

