// Recovered decompiler view: Trajectories
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x44e40, 0x46140); proximity does not prove ownership.

// CALLBACK RVA 0x44e40; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/trajectories/trajectories.c
// Differential report: analysis/module_behavior_recovery/trajectories/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x44e40; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180044e40(longlong param_1)

{
  if ((*(char *)(param_1 + 0x18) == '\0') && (*(longlong *)(param_1 + 0x10) == 0x1802f3df0)) {
    func_0x00018013cf70(_DAT_180304478);
    _DAT_180304478 = 0;
    uRam0000000180304480 = 0;
    func_0x00018013cf70(_DAT_180304488);
    _DAT_180304488 = 0;
    uRam0000000180304490 = 0;
  }
  return;
}

// CALLBACK RVA 0x44ea0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/trajectories/trajectories.c
// Differential report: analysis/module_behavior_recovery/trajectories/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x44ea0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180044ea0(longlong param_1)

{
  double dVar1;
  undefined8 *puVar2;
  double dVar3;
  double dVar4;
  undefined1 auVar5 [16];
  undefined8 uVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  float *pfVar10;
  ulonglong uVar11;
  bool bVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  undefined1 auStack_1a0 [24];
  undefined4 uStack_188;
  undefined4 uStack_184;
  undefined4 uStack_180;
  undefined4 uStack_17c;
  double dStack_178;
  double dStack_170;
  double dStack_168;
  double dStack_160;
  undefined4 uStack_158;
  undefined4 uStack_154;
  undefined4 uStack_150;
  undefined4 uStack_14c;
  double dStack_148;
  undefined4 uStack_138;
  undefined4 uStack_134;
  undefined4 uStack_130;
  undefined4 uStack_12c;
  double dStack_128;
  undefined8 uStack_118;
  undefined8 uStack_110;
  double dStack_108;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined4 uStack_f0;
  undefined4 uStack_ec;
  double dStack_e8;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  double dStack_c8;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  double dStack_a8;
  
  if (_DAT_180304498 != 0) {
    puVar2 = *(undefined8 **)(param_1 + 0x20);
    uVar6 = FUN_180023170(*puVar2,puVar2[5]);
    FUN_180023030(&uStack_188,*puVar2,puVar2[5]);
    FUN_1800230d0(&dStack_170,*puVar2,puVar2[5]);
    dStack_108 = dStack_160;
    uStack_118 = dStack_170;
    uStack_110 = dStack_168;
    dStack_c8 = dStack_178;
    uStack_d8 = (double)CONCAT44(uStack_184,uStack_188);
    uStack_d0 = (double)CONCAT44(uStack_17c,uStack_180);
    FUN_180009460(&uStack_158,&uStack_118,&uStack_d8,(double)*(float *)(param_1 + 0x28));
    dVar3 = *(double *)(param_1 + 8);
    dVar4 = *(double *)(param_1 + 0x10);
    dVar1 = *(double *)(param_1 + 0x18);
    uStack_f8 = uStack_158;
    uStack_f4 = uStack_154;
    uStack_f0 = uStack_150;
    uStack_ec = uStack_14c;
    dStack_e8 = dStack_148;
    FUN_180045f40(puVar2,&uStack_f8,uVar6,*(undefined4 *)(param_1 + 0x28),&uStack_118,&uStack_d8);
    uVar6 = _DAT_180154df0;
    if (_DAT_180304498 != 0) {
      uVar17 = SUB84(dStack_108,0);
      uVar18 = (undefined4)((ulonglong)dStack_108 >> 0x20);
      pfVar10 = (float *)0x1803044a8;
      uVar11 = 0;
      uVar13 = (undefined4)uStack_118;
      uVar14 = uStack_118._4_4_;
      uVar15 = (undefined4)uStack_110;
      uVar16 = uStack_110._4_4_;
      do {
        dStack_a8 = (double)CONCAT44(uVar18,uVar17);
        dStack_128 = dStack_c8;
        uStack_138 = (undefined4)uStack_d8;
        uStack_134 = uStack_d8._4_4_;
        uStack_130 = (undefined4)uStack_d0;
        uStack_12c = uStack_d0._4_4_;
        uStack_b8 = (double)CONCAT44(uVar14,uVar13);
        uStack_b0 = (double)CONCAT44(uVar16,uVar15);
        FUN_180009400(&uStack_f8,&uStack_b8,&uStack_138);
        uVar16 = uStack_ec;
        uVar15 = uStack_f0;
        uVar14 = uStack_f4;
        uVar13 = uStack_f8;
        auVar5._8_4_ = uStack_f0;
        auVar5._0_8_ = CONCAT44(uStack_f4,uStack_f8);
        auVar5._12_4_ = uStack_ec;
        uVar17 = SUB84(dStack_e8,0);
        uVar18 = (undefined4)((ulonglong)dStack_e8 >> 0x20);
        *(ulonglong *)(pfVar10 + -2) =
             CONCAT44((float)(auVar5._8_8_ - dVar4),
                      (float)((double)CONCAT44(uStack_f4,uStack_f8) - dVar3));
        *pfVar10 = (float)(dStack_e8 - dVar1);
        dStack_a8 = dStack_c8;
        uStack_b8 = uStack_d8;
        uStack_b0 = uStack_d0;
        FUN_180009430(&uStack_d8,&uStack_b8,uVar6);
        uStack_d0 = uStack_d0 - (double)_DAT_180304988;
        uVar11 = uVar11 + 1;
        pfVar10 = pfVar10 + 3;
      } while (uVar11 < _DAT_180304498);
    }
    (*(code *)*_DAT_18013e458)(0xbe2);
    (*(code *)*_DAT_180150cb0)(_DAT_1802f4030);
    puVar7 = (undefined4 *)0x1802f4060;
    bVar12 = DAT_18030449c != '\0';
    if (bVar12) {
      puVar7 = (undefined4 *)0x1802f4040;
    }
    puVar9 = (undefined4 *)0x1802f4064;
    if (bVar12) {
      puVar9 = (undefined4 *)0x1802f4044;
    }
    puVar8 = (undefined4 *)0x1802f4068;
    if (bVar12) {
      puVar8 = (undefined4 *)0x1802f4048;
    }
    (*(code *)*_DAT_180150ca0)(*puVar7,*puVar9,*puVar8);
    (*(code *)*_DAT_18014fd08)(0x8074);
    (*(code *)*_DAT_18014fd10)(3,0x1406,0,0x1803044a0);
    (*(code *)*_DAT_180154f98)(3,0,_DAT_180304498);
    if (DAT_180304950 == '\x01') {
      dStack_c8 = _DAT_180304968;
      uStack_d8 = _DAT_180304958;
      uStack_d0 = dRam0000000180304960;
      dStack_e8 = _DAT_180304980;
      uStack_f8 = _DAT_180304970;
      uStack_f4 = uRam0000000180304974;
      uStack_f0 = _DAT_180304978;
      uStack_ec = uRam000000018030497c;
      FUN_180009460(&uStack_118,&uStack_d8,&uStack_f8,_DAT_180154df8);
      dStack_e8 = _DAT_180304980;
      uStack_f8 = _DAT_180304970;
      uStack_f4 = uRam0000000180304974;
      uStack_f0 = _DAT_180304978;
      uStack_ec = uRam000000018030497c;
      dStack_a8 = dStack_108;
      uStack_b8 = uStack_118;
      uStack_b0 = uStack_110;
      FUN_1800093d0(&uStack_d8,&uStack_f8,&uStack_b8);
      dStack_a8 = (double)_DAT_180304470;
      uStack_b8 = (double)CONCAT44(uRam0000000180304464,_DAT_180304460);
      uStack_b0 = (double)CONCAT44(uRam000000018030446c,uRam0000000180304468);
      FUN_180009430(&uStack_f8,&uStack_b8,_DAT_180154e00 - (double)*(float *)(param_1 + 0x28));
      dStack_a8 = dStack_108;
      uStack_b8 = uStack_118;
      uStack_b0 = uStack_110;
      dStack_128 = *(double *)(param_1 + 0x18);
      uStack_138 = *(undefined4 *)(param_1 + 8);
      uStack_134 = *(undefined4 *)(param_1 + 0xc);
      uStack_130 = *(undefined4 *)(param_1 + 0x10);
      uStack_12c = *(undefined4 *)(param_1 + 0x14);
      FUN_1800093d0(auStack_1a0,&uStack_b8,&uStack_138);
      dStack_128 = dStack_e8;
      uStack_138 = uStack_f8;
      uStack_134 = uStack_f4;
      uStack_130 = uStack_f0;
      uStack_12c = uStack_ec;
      FUN_1800093d0(&uStack_b8,auStack_1a0,&uStack_138);
      (*(code *)*_DAT_180150cc0)();
      (*(code *)*_DAT_180150cd8)((float)uStack_b8,(float)uStack_b0,(float)dStack_a8);
      (*(code *)*_DAT_180150cd0)((float)uStack_d8,(float)uStack_d0,(float)dStack_c8);
      FUN_1800293c0();
      FUN_180029430();
      (*(code *)*_DAT_180150cb8)();
    }
    FUN_1800295a0();
  }
  return;
}

// CALLBACK RVA 0x45370; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/trajectories_update/trajectories_update.c
// Differential report: analysis/module_behavior_recovery/trajectories_update/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x45370; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180045370(longlong param_1)

{
  longlong *plVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined8 uVar6;
  longlong lVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  double *pdVar10;
  undefined8 *puVar11;
  ulonglong uVar12;
  float fVar13;
  float fVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  double *pdVar17;
  undefined1 auStack_260 [24];
  undefined1 auStack_248 [24];
  undefined1 auStack_230 [24];
  undefined1 auStack_218 [24];
  undefined4 uStack_200;
  undefined4 uStack_1fc;
  undefined4 uStack_1f8;
  undefined4 uStack_1f4;
  undefined8 uStack_1f0;
  double dStack_1e8;
  double dStack_1e0;
  double dStack_1d8;
  undefined4 uStack_1c8;
  undefined4 uStack_1c4;
  undefined4 uStack_1c0;
  undefined4 uStack_1bc;
  double dStack_1b8;
  undefined4 uStack_1a8;
  undefined4 uStack_1a4;
  undefined4 uStack_1a0;
  undefined4 uStack_19c;
  undefined8 uStack_198;
  undefined4 uStack_190;
  undefined4 uStack_18c;
  undefined8 uStack_178;
  undefined8 uStack_170;
  double dStack_168;
  undefined4 uStack_160;
  undefined4 uStack_15c;
  double dStack_158;
  double dStack_150;
  undefined8 uStack_148;
  undefined4 uStack_140;
  undefined4 uStack_13c;
  double dStack_138;
  double dStack_128;
  double dStack_120;
  double dStack_118;
  double dStack_108;
  double dStack_100;
  double dStack_f8;
  double dStack_e8;
  undefined8 uStack_e0;
  double dStack_d8;
  double dStack_d0;
  double dStack_c8;
  double dStack_c0;
  ulonglong uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  double dStack_98;
  undefined8 uStack_90;
  double dStack_88;
  double dStack_80;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  
  plVar1 = *(longlong **)(param_1 + 8);
  if ((char)plVar1[8] != '\x01') {
    _DAT_180304498 = 0;
    return;
  }
  cVar2 = FUN_180029f80();
  if (cVar2 != '\0') {
    _DAT_180304498 = 0;
    return;
  }
  uVar6 = FUN_180022cf0(*plVar1,plVar1[3]);
  iVar3 = FUN_180025310(*plVar1,uVar6);
  if (iVar3 != 0) {
    _DAT_180304498 = 0;
    return;
  }
  lVar7 = FUN_180028a50(*plVar1,plVar1[5]);
  if (lVar7 == 0) {
    _DAT_180304498 = 0;
    return;
  }
  uVar6 = FUN_180025c50(*plVar1,lVar7);
  iVar3 = (int)uVar6;
  if (iVar3 < 0x158) {
    if (iVar3 != 0x105) {
      if (iVar3 != 0x14c) {
        _DAT_180304498 = 0;
        return;
      }
      goto LAB_180045475;
    }
    if (DAT_1802f4090 != '\x01') {
      _DAT_180304498 = 0;
      return;
    }
    _DAT_180304988 = 0.05;
    uVar6 = FUN_180023f90(*plVar1,plVar1[5]);
    if ((char)uVar6 == '\0') {
      if (DAT_1802f40b0 != '\x01') {
        _DAT_180304498 = 0;
        return;
      }
      _DAT_18030498c = 3.0;
      _DAT_180304990 = 3.0;
    }
    else {
      uVar6 = FUN_180023fc0(*plVar1,plVar1[5]);
      fVar14 = (float)(72000 - (int)uVar6) / _DAT_180154e08;
      fVar14 = (fVar14 * fVar14 + fVar14 + fVar14) / _DAT_180154e0c;
      if ((double)fVar14 < _DAT_180154e10) {
        _DAT_180304498 = 0;
        _DAT_180304990 = 0.0;
        return;
      }
      fVar13 = _DAT_180154e18;
      if (fVar14 <= _DAT_180154e18) {
        fVar13 = fVar14;
      }
      _DAT_180304990 = (float)((double)fVar13 * _DAT_180154e20 + (double)fVar13 * _DAT_180154e20);
      if ((_DAT_180304990 == 0.0) && (!NAN(_DAT_180304990))) {
        _DAT_180304498 = 0;
        return;
      }
      fVar14 = (float)(71999 - (int)uVar6) / _DAT_180154e08;
      fVar14 = (fVar14 * fVar14 + fVar14 + fVar14) / _DAT_180154e0c;
      _DAT_18030498c = 0.0;
      if (_DAT_180154e10 <= (double)fVar14) {
        fVar13 = _DAT_180154e18;
        if (fVar14 <= _DAT_180154e18) {
          fVar13 = fVar14;
        }
        _DAT_18030498c = (float)((double)fVar13 * _DAT_180154e20 + (double)fVar13 * _DAT_180154e20);
      }
    }
  }
  else {
    if (iVar3 != 0x158) {
      if (iVar3 != 0x170) {
        _DAT_180304498 = 0;
        return;
      }
      if (DAT_1802f40d0 != '\x01') {
        _DAT_180304498 = 0;
        return;
      }
      _DAT_18030498c = 1.5;
      _DAT_180304990 = 1.5;
      _DAT_180304988 = 0.03;
      uStack_70 = (undefined4)CONCAT71((int7)((ulonglong)uVar6 >> 8),1);
      uStack_6c = 0;
      goto LAB_1800454b2;
    }
LAB_180045475:
    if (DAT_1802f40f0 != '\x01') {
      _DAT_180304498 = 0;
      return;
    }
    _DAT_18030498c = 1.5;
    _DAT_180304990 = 1.5;
    _DAT_180304988 = 0.03;
  }
  uStack_6c = (undefined4)CONCAT71((int7)((ulonglong)uVar6 >> 8),1);
  uStack_70 = 0;
LAB_1800454b2:
  uVar6 = FUN_180023170(*plVar1,plVar1[5]);
  FUN_180023030(&uStack_200,*plVar1,plVar1[5]);
  uStack_198 = uStack_1f0;
  uStack_1a8 = uStack_200;
  uStack_1a4 = uStack_1fc;
  uStack_1a0 = uStack_1f8;
  uStack_19c = uStack_1f4;
  pdVar17 = &dStack_128;
  FUN_180045f40(plVar1,&uStack_1a8,uVar6,0,pdVar17,&dStack_108);
  _DAT_180304484 = 0;
  _DAT_180304494 = 0;
  uVar6 = FUN_180024620(*plVar1,plVar1[4]);
  dStack_e8 = dStack_108 * _DAT_180154e28 + dStack_128;
  uStack_e0 = dStack_120 + _DAT_180154e30;
  dStack_d8 = _DAT_180154e28 * dStack_f8 + dStack_118;
  uStack_a8 = dStack_128;
  uStack_a0 = -100.0;
  dStack_98 = dStack_118;
  FUN_1800096e0(&uStack_1a8,&uStack_a8,&dStack_e8);
  iVar3 = FUN_180024e50(*plVar1,uVar6);
  if (0 < iVar3) {
    iVar3 = 0;
    uVar15 = (undefined4)_DAT_180154e38;
    do {
      uStack_148 = (double)FUN_180024e80(*plVar1,uVar6,iVar3);
      cVar2 = (**(code **)(**(longlong **)(*plVar1 + 8) + 0xc0))
                        (*(longlong **)(*plVar1 + 8),uStack_148,plVar1[5]);
      if ((cVar2 == '\0') && (cVar2 = FUN_180023900(*plVar1,uStack_148), cVar2 != '\0')) {
        uVar8 = FUN_180023670(*plVar1,uStack_148);
        FUN_180025640(&uStack_a8,*plVar1,uVar8);
        dStack_158 = dStack_88;
        dStack_150 = dStack_80;
        dStack_168 = dStack_98;
        uStack_160 = (undefined4)uStack_90;
        uStack_15c = uStack_90._4_4_;
        uStack_178 = uStack_a8;
        uStack_170 = uStack_a0;
        FUN_180009770(&dStack_e8,&uStack_178,uVar15);
        dStack_88 = dStack_c8;
        dStack_80 = dStack_c0;
        dStack_98 = dStack_d8;
        uStack_90 = dStack_d0;
        uStack_a8 = dStack_e8;
        uStack_a0 = uStack_e0;
        dStack_168 = (double)uStack_198;
        uStack_160 = uStack_190;
        uStack_15c = uStack_18c;
        uStack_178 = (double)CONCAT44(uStack_1a4,uStack_1a8);
        uStack_170 = (double)CONCAT44(uStack_19c,uStack_1a0);
        cVar2 = FUN_1800097d0(&dStack_e8,&uStack_178);
        if (cVar2 != '\0') {
          FUN_18000ddd0(&DAT_180304478,8,0x180304480,&uStack_148);
          FUN_18000ddd0(&DAT_180304488,0x30,0x180304490,&uStack_a8);
        }
      }
      iVar3 = iVar3 + 1;
      iVar4 = FUN_180024e50(*plVar1,uVar6);
    } while (iVar3 < iVar4);
  }
  uVar6 = _DAT_180154e40;
  uStack_b0 = 0;
  uVar15 = (undefined4)_DAT_180154e48;
  uVar16 = (undefined4)_DAT_180154e40;
  while( true ) {
    dStack_168 = dStack_118;
    uStack_178 = dStack_128;
    uStack_170 = dStack_120;
    dStack_98 = dStack_118;
    uStack_a8 = dStack_128;
    uStack_a0 = dStack_120;
    dStack_d8 = dStack_f8;
    dStack_e8 = dStack_108;
    uStack_e0 = dStack_100;
    FUN_180009400(&dStack_128,&uStack_a8,&dStack_e8);
    dStack_98 = dStack_168;
    uStack_a8 = uStack_178;
    uStack_a0 = uStack_170;
    uVar8 = FUN_1800254f0(*plVar1,&uStack_a8);
    dStack_98 = dStack_118;
    uStack_a8 = dStack_128;
    uStack_a0 = dStack_120;
    uVar9 = FUN_1800254f0(*plVar1,&uStack_a8);
    pdVar17 = (double *)((ulonglong)pdVar17 & 0xffffffffffffff00);
    lVar7 = FUN_180024860(*plVar1,plVar1[4],uVar8,uVar9,pdVar17,1,0);
    if (lVar7 != 0) {
      _DAT_180304498 = (int)uStack_b0 + 1;
      DAT_180304950 = 1;
      DAT_18030449c = (undefined1)uStack_70;
      uVar8 = FUN_180024bf0(*plVar1,lVar7);
      FUN_180025540(&uStack_a8,*plVar1,uVar8);
      dStack_118 = dStack_98;
      dStack_128 = uStack_a8;
      dStack_120 = uStack_a0;
      dStack_d8 = dStack_168;
      dStack_e8 = uStack_178;
      uStack_e0 = uStack_170;
      FUN_1800093d0(&dStack_108,&uStack_a8,&dStack_e8);
      FUN_180024c10(&dStack_e8,*plVar1,lVar7);
      FUN_1800093b0(auStack_248,uVar16,uVar16,uVar6);
      dStack_98 = dStack_d8;
      uStack_a8 = dStack_e8;
      uStack_a0 = uStack_e0;
      FUN_180009400(auStack_260,&uStack_a8,auStack_248);
      dStack_138 = dStack_d8;
      uStack_148 = dStack_e8;
      uStack_140 = (undefined4)uStack_e0;
      uStack_13c = uStack_e0._4_4_;
      FUN_1800096b0(&uStack_a8,&uStack_148,auStack_260);
      _DAT_180304958 = (undefined4)uStack_a8;
      uRam000000018030495c = uStack_a8._4_4_;
      uRam0000000180304960 = (undefined4)uStack_a0;
      uRam0000000180304964 = uStack_a0._4_4_;
      _DAT_180304968 = dStack_98;
      _DAT_180304970 = uStack_90;
      _DAT_180304978 = dStack_88;
      _DAT_180304980 = dStack_80;
      FUN_1800093b0(&uStack_a8,0,0,0);
      _DAT_180304470 = dStack_98;
      _DAT_180304460 = uStack_a8;
      dRam0000000180304468 = uStack_a0;
    }
    dStack_98 = dStack_f8;
    uStack_a8 = dStack_108;
    uStack_a0 = dStack_100;
    FUN_180009650(&uStack_148,&uStack_a8);
    if (_DAT_180304494 != 0) {
      uVar12 = 0;
      do {
        pdVar10 = (double *)FUN_18000ddc0(_DAT_180304488,0x30,0x180304490,uVar12 & 0xffffffff);
        dStack_e8 = *pdVar10;
        uStack_e0 = pdVar10[1];
        dStack_d8 = pdVar10[2];
        dStack_98 = pdVar10[2];
        dStack_d0 = pdVar10[3];
        uStack_90 = pdVar10[3];
        dStack_c8 = pdVar10[4];
        dStack_88 = pdVar10[4];
        dStack_c0 = pdVar10[5];
        dStack_80 = pdVar10[5];
        dStack_1d8 = dStack_168;
        dStack_1e8 = uStack_178;
        dStack_1e0 = uStack_170;
        dStack_1b8 = dStack_138;
        uStack_1c8 = (undefined4)uStack_148;
        uStack_1c4 = uStack_148._4_4_;
        uStack_1c0 = uStack_140;
        uStack_1bc = uStack_13c;
        uStack_a8 = dStack_e8;
        uStack_a0 = uStack_e0;
        cVar2 = FUN_1800098e0(&dStack_e8,&dStack_1e8,&uStack_1c8);
        if (cVar2 != '\0') {
          _DAT_180304498 = (int)uStack_b0 + 1;
          DAT_180304950 = 1;
          DAT_18030449c = (undefined1)uStack_6c;
          _DAT_180304958 = (undefined4)uStack_a8;
          uRam000000018030495c = uStack_a8._4_4_;
          uRam0000000180304960 = (undefined4)uStack_a0;
          uRam0000000180304964 = uStack_a0._4_4_;
          _DAT_180304968 = dStack_98;
          _DAT_180304970 = uStack_90;
          _DAT_180304978 = dStack_88;
          _DAT_180304980 = dStack_80;
          puVar11 = (undefined8 *)FUN_18000ddc0(_DAT_180304478,8,0x180304480,uVar12 & 0xffffffff);
          uVar6 = *puVar11;
          FUN_180023030(auStack_230,*plVar1,uVar6);
          FUN_1800230d0(auStack_218,*plVar1,uVar6);
          FUN_1800093d0(&dStack_e8,auStack_230,auStack_218);
          _DAT_180304460 = dStack_e8;
          dRam0000000180304468 = uStack_e0;
          _DAT_180304470 = dStack_d8;
          return;
        }
        uVar12 = uVar12 + 1;
      } while (uVar12 < _DAT_180304494);
    }
    if (lVar7 != 0) break;
    dStack_d8 = dStack_f8;
    dStack_e8 = dStack_108;
    uStack_e0 = dStack_100;
    FUN_180009430(&uStack_a8,&dStack_e8,uVar15);
    dStack_108 = uStack_a8;
    dStack_f8 = dStack_98;
    dStack_100 = uStack_a0 - (double)_DAT_180304988;
    uVar5 = (int)uStack_b0 + 1;
    uStack_b0 = (ulonglong)uVar5;
    if (uVar5 == 100) {
      _DAT_180304498 = 100;
      DAT_18030449c = 0;
      DAT_180304950 = 0;
      return;
    }
  }
  return;
}

// UI RVA 0x45dc0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x45dc0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180045dc0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180154f1f);
  FUN_18000cf30(param_2,param_1,0x1802f4000);
  FUN_18000d0a0(param_2,param_1,0x1802f4038);
  FUN_18000d0a0(param_2,param_1,0x1802f4058);
  FUN_180013e90(param_1,param_2,&UNK_180154f24);
  FUN_18000cef0(param_2,param_1,0x1802f40d8);
  FUN_18000cef0(param_2,param_1,0x1802f40b8);
  FUN_18000cef0(param_2,param_1,0x1802f4078);
  if (DAT_1802f4090 != '\x01') {
    return;
  }
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802f40a8,0x1802f4098,&DAT_1802f40b0);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x45e90; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x45e90; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180045e90(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c450(param_1,&UNK_180154f38,0x1802f4000);
  FUN_18000c7e0(param_1,&UNK_180154f43,0x1802f4038);
  FUN_18000c7e0(param_1,&UNK_180154f4d,0x1802f4058);
  FUN_18000c3b0(param_1,&UNK_180154f58,0x1802f40d8);
  FUN_18000c3b0(param_1,&UNK_180154f6a,0x1802f40b8);
  FUN_18000c3b0(param_1,&UNK_180154f78,0x1802f4078);
  uVar1 = uRam00000001802f40b1;
  uVar2 = DAT_1802f40b0;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180154f83,DAT_1802f40b0);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802f40b0;
      break;
    case 2:
      uRam00000001802f40b1 = DAT_1802f40b0;
      break;
    case 3:
      uVar2 = uRam00000001802f40b1;
    }
  }
  DAT_1802f40b0 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x45f40; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x45f40; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180045f40(undefined8 *param_1,double *param_2,undefined8 param_3,undefined8 param_4,
                  double *param_5,double *param_6)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  char cVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  uint uVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  double dStack_b8;
  double dStack_b0;
  double dStack_a8;
  double dStack_98;
  double dStack_90;
  double dStack_88;
  
  fVar6 = (float)func_0x0001800b3590();
  fVar7 = (float)func_0x0001800b3590();
  fVar8 = (float)func_0x0001800b1cf0();
  uVar9 = func_0x0001800b1cf0();
  fVar12 = (float)((uint)fVar8 ^ _DAT_180154e60);
  fVar10 = (float)(uVar9 ^ _DAT_180154e60);
  fVar11 = (float)FUN_18000a2b0();
  dStack_98 = (double)(fVar12 * fVar7);
  dStack_90 = (double)fVar10;
  dStack_88 = (double)(fVar7 * fVar6);
  FUN_180009430(&dStack_b8,&dStack_98,(double)fVar11);
  dVar4 = dStack_a8;
  dVar3 = dStack_b0;
  dVar2 = dStack_b8;
  cVar5 = FUN_180023020(*param_1);
  if (cVar5 == '\0') {
    dStack_88 = param_2[2];
    dStack_98 = *param_2;
    dStack_90 = param_2[1];
    FUN_180009590(&dStack_b8,&dStack_98);
    param_2[2] = dStack_a8;
    *param_2 = dStack_b8;
    param_2[1] = dStack_b0;
    cVar5 = FUN_1800236f0(*param_1,param_1[5]);
    if (cVar5 != '\0') {
      param_2[1] = param_2[1] + _DAT_180154e70;
    }
  }
  dVar1 = _DAT_180154e78;
  *param_2 = *param_2 - (double)fVar6 * _DAT_180154e78;
  param_2[1] = param_2[1] + _DAT_180154e80;
  param_2[2] = param_2[2] - (double)fVar8 * dVar1;
  param_5[2] = param_2[2];
  dVar1 = param_2[1];
  *param_5 = *param_2;
  param_5[1] = dVar1;
  *param_6 = dVar2;
  param_6[1] = dVar3;
  param_6[2] = dVar4;
  return;
}

