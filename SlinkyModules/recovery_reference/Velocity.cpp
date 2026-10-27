// Recovered decompiler view: Velocity
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x30180, 0x30e70); proximity does not prove ownership.

// CALLBACK RVA 0x30180; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/velocity/velocity.c
// Differential report: analysis/module_behavior_recovery/velocity/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x30180; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180030180(longlong param_1)

{
  undefined8 *puVar1;
  char cVar2;
  undefined8 uVar3;
  double dVar4;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined8 uStack_38;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined8 uStack_18;
  
  if (_DAT_1802eaa50 != 3) {
    return;
  }
  puVar1 = *(undefined8 **)(param_1 + 8);
  if (*(char *)(puVar1 + 8) != '\x01') {
    return;
  }
  if ((DAT_1802f9d88 & 1) != 0) {
    LOCK();
    UNLOCK();
    DAT_1802f9d88 = 0;
    return;
  }
  if (DAT_1802f9d89 == '\x01') {
    cVar2 = FUN_180030c50(puVar1);
    if (cVar2 == '\0') {
      return;
    }
    if (_DAT_1802eaa90 <= _DAT_180150e20) {
      dVar4 = (double)(float)((double)_DAT_1802eaa90 * _DAT_180150e28) + _DAT_180150e38;
      uVar3 = FUN_18000a050((float)(_DAT_180150e30 +
                                   (double)(float)((double)_DAT_1802eaa90 * _DAT_180150e28)),
                            CONCAT44((int)((ulonglong)dVar4 >> 0x20),(float)dVar4));
      cVar2 = FUN_18000aa30(0x1802f9da8,uVar3,_DAT_180150e40);
      if (cVar2 == '\0') {
        return;
      }
    }
    FUN_180023550(&uStack_28,*puVar1,puVar1[5]);
    uStack_28 = _DAT_1802f9d90;
    if ((_DAT_1802eab68 == 2) ||
       ((_DAT_1802eab68 == 1 && (cVar2 = FUN_180023780(*puVar1,puVar1[5]), cVar2 == '\0')))) {
      uStack_20 = _DAT_1802f9d98;
    }
    uStack_18 = _DAT_1802f9da0;
    uStack_38 = _DAT_1802f9da0;
    uStack_48 = (undefined4)uStack_28;
    uStack_44 = uStack_28._4_4_;
    uStack_40 = (undefined4)uStack_20;
    uStack_3c = uStack_20._4_4_;
    FUN_1800235f0(*puVar1,puVar1[5],&uStack_48);
    DAT_1802f9d89 = 0;
    return;
  }
  return;
}

// CALLBACK RVA 0x302d0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/velocity/velocity.c
// Differential report: analysis/module_behavior_recovery/velocity/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x302d0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800302d0(longlong param_1)

{
  int iVar1;
  longlong lVar2;
  float fVar3;
  float fVar4;
  
  if (*(int *)(param_1 + 0x24) == 0) {
    lVar2 = FUN_1800266b0(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10));
    if (lVar2 == 0) {
      lVar2 = FUN_180026b50(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10));
      if (lVar2 == 0) {
        lVar2 = FUN_180026b10(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10));
        if (lVar2 != 0) {
          LOCK();
          DAT_1802f9d88 = 1;
          UNLOCK();
        }
      }
      else {
        fVar3 = (float)FUN_180026b90(*(undefined8 *)(param_1 + 8),lVar2);
        fVar4 = (float)FUN_180026c30(*(undefined8 *)(param_1 + 8),lVar2);
        DAT_1802f9dbc = _DAT_180150e48 < (double)(fVar3 * fVar3 + fVar4 * fVar4);
        LOCK();
        UNLOCK();
      }
    }
    else {
      iVar1 = FUN_1800266f0(*(undefined8 *)(param_1 + 8),lVar2);
      if (iVar1 == _DAT_1802f9db8) {
        LOCK();
        DAT_1802f9dbc = 1;
        UNLOCK();
      }
    }
  }
  return;
}

// CALLBACK RVA 0x303a0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/velocity/velocity.c
// Differential report: analysis/module_behavior_recovery/velocity/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x303a0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_1800303a0(longlong param_1)

{
  if (*(longlong *)(param_1 + 0x10) != 0x1802ea7f0) {
    return;
  }
  DAT_1802f9d89 = 0;
  return;
}

// CALLBACK RVA 0x303c0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/velocity/velocity.c
// Differential report: analysis/module_behavior_recovery/velocity/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x303c0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800303c0(longlong param_1)

{
  undefined8 uStack_20;
  undefined8 uStack_18;
  undefined8 uStack_10;
  
  if (*(char *)(param_1 + 0x10) == '\x01') {
    if ((*(undefined8 **)(param_1 + 8))[5] != 0) {
      FUN_180023550(&uStack_20,**(undefined8 **)(param_1 + 8));
      _DAT_1802f9dd0 = uStack_10;
      _DAT_1802f9dc0 = uStack_20;
      uRam00000001802f9dc8 = uStack_18;
    }
  }
  return;
}

// CALLBACK RVA 0x30410; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/velocity/velocity.c
// Differential report: analysis/module_behavior_recovery/velocity/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x30410; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180030410(longlong param_1)

{
  undefined8 *puVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  float fVar6;
  double dStack_38;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  double dStack_28;
  
  if ((_DAT_1802eaa50 == 2) &&
     (((DAT_1802f9dd8 != '\x01' || (DAT_1802eab90 != '\0')) && (*(char *)(param_1 + 0x10) == '\x01')
      ))) {
    puVar1 = *(undefined8 **)(param_1 + 8);
    lVar5 = puVar1[5];
    if ((lVar5 != 0) && (*(char *)(puVar1[7] + 0x18) == '\x01')) {
      if (DAT_1802eaab0 == '\x01') {
        fVar6 = (float)FUN_180023ac0(*puVar1);
        if (fVar6 <= 0.0) {
          return;
        }
        lVar5 = puVar1[5];
      }
      if (DAT_1802eaaf0 == '\x01') {
        cVar2 = FUN_1800380b0(*puVar1,lVar5);
        if (cVar2 == '\0') {
          return;
        }
        lVar5 = puVar1[5];
      }
      iVar3 = FUN_180023760(*puVar1,lVar5);
      iVar4 = FUN_1800239d0(*puVar1,puVar1[5]);
      if (iVar3 == iVar4) {
        _DAT_1802f9dc0 = _DAT_1802f9dc0 * _DAT_180150e50;
        _DAT_1802f9dd0 = _DAT_180150e50 * _DAT_1802f9dd0;
        uStack_30 = uRam00000001802f9dc8;
        uStack_2c = uRam00000001802f9dcc;
        dStack_28 = _DAT_1802f9dd0;
        dStack_38 = _DAT_1802f9dc0;
        FUN_1800235f0(*puVar1,puVar1[5],&dStack_38);
        DAT_1802f9dd8 = '\x01';
      }
    }
  }
  return;
}

// CALLBACK RVA 0x30520; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/velocity/velocity.c
// Differential report: analysis/module_behavior_recovery/velocity/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x30520; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180030520(longlong param_1)

{
  undefined8 *puVar1;
  char cVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  longlong lVar5;
  undefined8 uVar6;
  bool bVar7;
  float fVar8;
  float fVar9;
  double dVar10;
  double dVar11;
  double dStack_78;
  double dStack_70;
  double dStack_68;
  double dStack_60;
  double dStack_58;
  double dStack_50;
  
  DAT_1802f9dd8 = 0;
  if (_DAT_1802eaa50 == 2) {
    DAT_1802f9dd8 = 0;
    return;
  }
  puVar1 = *(undefined8 **)(param_1 + 8);
  if (*(char *)(puVar1 + 8) != '\x01') {
    DAT_1802f9dd8 = 0;
    return;
  }
  _DAT_1802f9db8 = FUN_180023720(*puVar1,puVar1[5]);
  LOCK();
  UNLOCK();
  if (_DAT_1802eaa50 == 1) {
    if (DAT_1802f9de0 == '\x01') {
      uVar6 = FUN_180022cf0(*puVar1,puVar1[3]);
      uVar4 = FUN_180025080(*puVar1,uVar6);
      uVar6 = *puVar1;
      uVar3 = FUN_180025490(uVar6,uVar4);
      FUN_180025460(uVar6,uVar4,uVar3);
      DAT_1802f9de0 = 0;
      return;
    }
    cVar2 = FUN_180030c50(puVar1);
    if (cVar2 == '\0') {
      return;
    }
    if (_DAT_1802eaca8 <= _DAT_180150e58) {
      dVar10 = _DAT_180150e68 + (double)(float)((double)_DAT_1802eaca8 * _DAT_180150e60);
      dVar11 = (double)(float)((double)_DAT_1802eaca8 * _DAT_180150e60) + _DAT_180150e70;
      uVar6 = FUN_18000a050(CONCAT44((int)((ulonglong)dVar10 >> 0x20),(float)dVar10),
                            CONCAT44((int)((ulonglong)dVar11 >> 0x20),(float)dVar11));
      cVar2 = FUN_18000aa30(0x1802f9da8,uVar6,_DAT_180150e78);
      if (cVar2 == '\0') {
        return;
      }
    }
    if ((DAT_1802eacc8 == '\x01') && (cVar2 = FUN_180023690(*puVar1,puVar1[5]), cVar2 == '\0')) {
      return;
    }
    cVar2 = FUN_180023780(*puVar1,puVar1[5]);
    if (cVar2 == '\0') {
      return;
    }
    FUN_180023550(&dStack_60,*puVar1,puVar1[5]);
    if (dStack_58 <= 0.0) {
      return;
    }
    uVar6 = FUN_180027960(*puVar1,8);
    lVar5 = FUN_180023c10(*puVar1,puVar1[5],uVar6);
    if (lVar5 != 0) {
      return;
    }
    uVar6 = FUN_180022cf0(*puVar1,puVar1[3]);
    uVar6 = FUN_180025080(*puVar1,uVar6);
    cVar2 = FUN_180025430(*puVar1,uVar6);
    if (cVar2 != '\0') {
      return;
    }
    FUN_180025460(*puVar1,uVar6,1);
    DAT_1802f9de0 = 1;
    return;
  }
  if (_DAT_1802eaa50 != 0) {
    return;
  }
  if (_DAT_1802f9ddc < 1) {
    LOCK();
    bVar7 = DAT_1802f9dbc == '\x01';
    if (bVar7) {
      DAT_1802f9dbc = '\0';
    }
    UNLOCK();
    if (!bVar7) {
      return;
    }
    cVar2 = FUN_180030c50(puVar1);
    if (cVar2 == '\0') {
      return;
    }
    if (_DAT_1802eabc8 <= _DAT_180150e58) {
      dVar10 = _DAT_180150e68 + (double)(float)((double)_DAT_1802eabc8 * _DAT_180150e60);
      dVar11 = (double)(float)((double)_DAT_1802eabc8 * _DAT_180150e60) + _DAT_180150e70;
      uVar6 = FUN_18000a050(CONCAT44((int)((ulonglong)dVar10 >> 0x20),(float)dVar10),
                            CONCAT44((int)((ulonglong)dVar11 >> 0x20),(float)dVar11));
      cVar2 = FUN_18000aa30(0x1802f9da8,uVar6,_DAT_180150e78);
      if (cVar2 == '\0') {
        return;
      }
    }
    FUN_180023550(&dStack_60,*puVar1,puVar1[5]);
    dVar10 = (double)func_0x00018013cfd0(dStack_60,dStack_50);
    if ((dVar10 == 0.0) && (!NAN(dVar10))) {
      return;
    }
    FUN_180023170(*puVar1,puVar1[5]);
    fVar8 = (float)func_0x0001800b1cf0();
    fVar9 = (float)func_0x0001800b3590();
    dVar10 = (double)func_0x00018013cfa0(((double)fVar8 * dStack_60 + (double)fVar9 * dStack_50) /
                                         dVar10);
    if ((double)_DAT_1802eac70 < dVar10) {
      return;
    }
    _DAT_1802f9ddc = (int)_DAT_1802eac00;
    if (_DAT_1802f9ddc < 1) goto LAB_1800305a4;
  }
  _DAT_1802f9ddc = _DAT_1802f9ddc + -1;
  if (_DAT_1802f9ddc != 0) {
    return;
  }
LAB_1800305a4:
  FUN_180023550(&dStack_60,*puVar1,puVar1[5]);
  dStack_78 = dStack_60 * (double)_DAT_1802eac38;
  dStack_68 = (double)_DAT_1802eac38 * dStack_50;
  dStack_70 = dStack_58;
  dStack_60 = dStack_78;
  dStack_50 = dStack_68;
  FUN_1800235f0(*puVar1,puVar1[5],&dStack_78);
  return;
}

// CALLBACK RVA 0x308e0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/velocity/velocity.c
// Differential report: analysis/module_behavior_recovery/velocity/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x308e0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800308e0(longlong param_1)

{
  undefined8 uStack_20;
  undefined8 uStack_18;
  undefined8 uStack_10;
  
  if ((*(undefined8 **)(param_1 + 8))[5] != 0) {
    FUN_180023550(&uStack_20,**(undefined8 **)(param_1 + 8));
    _DAT_1802f9da0 = uStack_10;
    _DAT_1802f9d90 = uStack_20;
    _DAT_1802f9d98 = uStack_18;
    DAT_1802f9d89 = 1;
  }
  return;
}

// UI RVA 0x30930; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x30930; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180030930(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  undefined8 uVar2;
  
  FUN_180013e90(param_1,param_2,&UNK_180150fed);
  FUN_18000d040(param_2,param_1,0x1802eaa20);
  switch(_DAT_1802eaa50) {
  case 0:
    FUN_18000cf30(param_2,param_1,0x1802eab98);
    FUN_18000cf30(param_2,param_1,0x1802eac40);
    FUN_18000cf30(param_2,param_1,0x1802eac08);
    uVar2 = 0x1802eabd0;
    break;
  case 1:
    uVar2 = 0x1802eac78;
    break;
  case 2:
    FUN_18000cef0(param_2,param_1,0x1802eab78);
    goto LAB_180030a00;
  case 3:
    FUN_18000d040(param_2,param_1,0x1802eab38);
    uVar2 = 0x1802eaa60;
    break;
  default:
    goto LAB_180030a00;
  }
  FUN_18000cf30(param_2,param_1,uVar2);
LAB_180030a00:
  FUN_180013e90(param_1,param_2,&UNK_180150ff2);
  if (_DAT_1802eaa50 != 2) {
    FUN_18000cef0(param_2,param_1,0x1802eaaf8);
    FUN_18000cef0(param_2,param_1,0x1802eaab8);
  }
  FUN_18000cef0(param_2,param_1,0x1802eaa98);
  FUN_18000cef0(param_2,param_1,0x1802eaad8);
  if (_DAT_1802eaa50 != 1) {
    return;
  }
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802eacc0,0x1802eacb0,&DAT_1802eacc8);
  if (cVar1 == '\0') {
    return;
  }
  DAT_1802f7338 = 1;
  return;
}

// SETTINGS RVA 0x30a90; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x30a90; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180030a90(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c6f0(param_1,&UNK_180150ffd,0x1802eaa20);
  FUN_18000c450(param_1,&UNK_180151002,0x1802eab98);
  FUN_18000c450(param_1,&UNK_180151010,0x1802eac40);
  FUN_18000c450(param_1,&UNK_180151014,0x1802eac08);
  FUN_18000c450(param_1,&UNK_180151022,0x1802eabd0);
  FUN_18000c450(param_1,&UNK_18015102f,0x1802eac78);
  FUN_18000c3b0(param_1,&UNK_18015103b,0x1802eab78);
  FUN_18000c6f0(param_1,&UNK_180151054,0x1802eab38);
  FUN_18000c450(param_1,&UNK_180151064,0x1802eaa60);
  FUN_18000c3b0(param_1,&UNK_180151072,0x1802eaaf8);
  FUN_18000c3b0(param_1,&UNK_180151081,0x1802eaab8);
  FUN_18000c3b0(param_1,&UNK_18015108f,0x1802eaa98);
  FUN_18000c3b0(param_1,&UNK_18015109f,0x1802eaad8);
  uVar1 = uRam00000001802eacc9;
  uVar2 = DAT_1802eacc8;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_1801510ae,DAT_1802eacc8);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802eacc8;
      break;
    case 2:
      uRam00000001802eacc9 = DAT_1802eacc8;
      break;
    case 3:
      uVar2 = uRam00000001802eacc9;
    }
  }
  DAT_1802eacc8 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x30be0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x30be0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180030be0(undefined4 param_1)

{
  if ((ulonglong)_DAT_1802eaa50 == 0) {
    FUN_1800ab710(_DAT_1802eac38 * _DAT_180150ea0,0x20,&UNK_180150f6c,
                  (double)(_DAT_1802eac38 * _DAT_180150ea0));
  }
  else {
    FUN_1800ab710(param_1,0x20,&UNK_1801510c5,
                  *(undefined8 *)((ulonglong)_DAT_1802eaa50 * 8 + 0x1802eaa00));
  }
  return;
}

// CANDIDATE_LOCAL RVA 0x30c50; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x30c50; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong FUN_180030c50(longlong *param_1)

{
  double dVar1;
  uint uVar2;
  char cVar3;
  float fVar4;
  int iVar5;
  float fVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 unaff_RDI;
  ulonglong uVar9;
  float fVar10;
  uint uVar11;
  double dVar12;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  
  if (DAT_1802eaab0 == '\x01') {
    fVar10 = (float)FUN_180023ac0(*param_1,param_1[5]);
    if (0.0 < fVar10) goto LAB_180030ca2;
  }
  else {
LAB_180030ca2:
    if (DAT_1802eaad0 == '\x01') {
      cVar3 = FUN_180029080(param_1);
      if (cVar3 == '\0') goto LAB_180030e42;
    }
    if (DAT_1802eaaf0 == '\x01') {
      cVar3 = FUN_1800380b0(*param_1,param_1[5]);
      if (cVar3 == '\0') goto LAB_180030e42;
    }
    uVar9 = CONCAT71((int7)((ulonglong)unaff_RDI >> 8),1);
    if (DAT_1802eab10 != '\x01') goto LAB_180030e44;
    FUN_180023030(&uStack_118,*param_1,param_1[5]);
    fVar4 = (float)FUN_180023170(*param_1,param_1[5]);
    uVar7 = FUN_180024600(*param_1,param_1[4]);
    iVar5 = FUN_180024e50(*param_1,uVar7);
    fVar10 = _DAT_180150ed0;
    uVar2 = _DAT_180150ec0;
    dVar1 = _DAT_180150eb0;
    uVar9 = 0;
    if (iVar5 < 1) goto LAB_180030e44;
    do {
      uVar8 = FUN_180024e80(*param_1,uVar7,uVar9);
      cVar3 = (**(code **)(**(longlong **)(*param_1 + 8) + 0xc0))
                        (*(longlong **)(*param_1 + 8),param_1[5],uVar8);
      if (cVar3 == '\0') {
        uStack_98 = uStack_108;
        uStack_a8 = uStack_118;
        uStack_a0 = uStack_110;
        FUN_180023030(&uStack_100,*param_1,uVar8);
        uStack_d8 = uStack_98;
        uStack_e8 = uStack_a8;
        uStack_e0 = uStack_a0;
        uStack_b8 = uStack_f0;
        uStack_c8 = uStack_100;
        uStack_c0 = uStack_f8;
        dVar12 = (double)FUN_1800094b0(&uStack_e8,&uStack_c8);
        if (dVar12 <= dVar1) {
          uStack_d8 = uStack_98;
          uStack_e8 = uStack_a8;
          uStack_e0 = uStack_a0;
          uStack_b8 = uStack_f0;
          uStack_c8 = uStack_100;
          uStack_c0 = uStack_f8;
          fVar6 = (float)FUN_180009f80(&uStack_e8,&uStack_c8);
          uVar11 = FUN_18000a210(fVar6 - fVar4);
          if ((float)(uVar11 & uVar2) <= fVar10) {
            uVar9 = CONCAT71((int7)(uVar9 >> 8),1);
            goto LAB_180030e44;
          }
        }
      }
      uVar11 = (int)uVar9 + 1;
      uVar9 = (ulonglong)uVar11;
      iVar5 = FUN_180024e50(*param_1,uVar7);
    } while ((int)uVar11 < iVar5);
  }
LAB_180030e42:
  uVar9 = 0;
LAB_180030e44:
  return uVar9 & 0xffffffff;
}

