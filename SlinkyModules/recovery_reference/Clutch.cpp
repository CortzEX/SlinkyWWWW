// Recovered decompiler view: Clutch
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x488f0, 0x4a340); proximity does not prove ownership.

// CALLBACK RVA 0x488f0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/clutch_events/clutch_events.c
// Differential report: analysis/module_behavior_recovery/clutch_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x488f0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800488f0(longlong param_1)

{
  undefined8 *puVar1;
  int iVar2;
  longlong lVar3;
  undefined8 uVar4;
  double dStack_40;
  double dStack_38;
  double dStack_30;
  int iStack_24;
  int iStack_20;
  int iStack_1c;
  
  if ((0.0 < _DAT_180304a18) &&
     (_DAT_180304a18 = _DAT_180304a18 + _DAT_180156070, 0.0 < _DAT_180304a18)) {
    return;
  }
  _DAT_180304a18 = _DAT_180156074 / _DAT_1802f57c0 + _DAT_180304a18;
  puVar1 = *(undefined8 **)(param_1 + 8);
  if (((((*(char *)(puVar1 + 8) == '\x01') && (DAT_180304a1c != '\0')) &&
       (lVar3 = FUN_180022e10(*puVar1,puVar1[3]), lVar3 != 0)) &&
      ((iVar2 = FUN_180024b50(*puVar1,lVar3), iVar2 == 1 &&
       (FUN_180024ce0(&iStack_24,*puVar1,lVar3), iStack_24 == _DAT_180304a20)))) &&
     ((iStack_20 == _DAT_180304a24 &&
      ((iStack_1c == _DAT_180304a28 &&
       (iVar2 = FUN_180024b90(*puVar1,lVar3), (bool)DAT_180304a2c != (iVar2 != 1))))))) {
    uVar4 = FUN_180022cf0(*puVar1,puVar1[3]);
    uVar4 = FUN_180024f90(*puVar1,uVar4);
    FUN_180025380(*puVar1,uVar4);
    FUN_180024d80(&dStack_40,*puVar1,lVar3);
    _DAT_180304a20 = (int)dStack_40;
    _DAT_180304a24 = (int)dStack_38;
    _DAT_180304a28 = (int)dStack_30;
  }
  return;
}

// CALLBACK RVA 0x48a30; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/clutch_events/clutch_events.c
// Differential report: analysis/module_behavior_recovery/clutch_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x48a30; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180048a30(longlong param_1)

{
  if (DAT_180304a2d == '\x01') {
    *(undefined2 *)(param_1 + 8) = 0x101;
  }
  return;
}

// CALLBACK RVA 0x48a50; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/clutch_update/clutch_update.c
// Differential report: analysis/module_behavior_recovery/clutch_update/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x48a50; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180048a50(longlong param_1)

{
  ushort uVar1;
  undefined8 *puVar2;
  undefined1 auVar3 [12];
  undefined1 auVar4 [12];
  undefined1 auVar5 [12];
  undefined1 auVar6 [12];
  undefined1 auVar7 [12];
  undefined1 auVar8 [12];
  byte bVar9;
  char cVar10;
  int iVar11;
  undefined4 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  ulonglong uVar16;
  longlong lVar17;
  int iVar18;
  int iVar19;
  uint uVar20;
  int iVar21;
  uint uVar22;
  int iVar23;
  ushort *puVar24;
  uint uVar25;
  int iVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  ulonglong uVar30;
  double dVar31;
  double dVar32;
  double dVar33;
  double dVar34;
  double dVar35;
  float fVar36;
  uint uVar37;
  uint uVar38;
  undefined8 *puVar39;
  double dStack_258;
  double dStack_250;
  double dStack_248;
  double dStack_240;
  double dStack_230;
  double dStack_228;
  double dStack_220;
  double dStack_218;
  ulonglong uStack_210;
  undefined8 uStack_208;
  double dStack_200;
  double dStack_1f8;
  double dStack_1f0;
  double dStack_1e8;
  double dStack_1e0;
  double dStack_1d8;
  ulonglong uStack_1c8;
  ulonglong uStack_1c0;
  ulonglong uStack_1b8;
  longlong lStack_1b0;
  double dStack_1a8;
  double dStack_1a0;
  double dStack_198;
  ulonglong uStack_190;
  undefined8 uStack_188;
  double dStack_180;
  double dStack_178;
  double dStack_168;
  double dStack_160;
  double dStack_158;
  undefined8 uStack_150;
  double dStack_148;
  double dStack_140;
  double dStack_138;
  int iStack_130;
  int iStack_12c;
  int iStack_128;
  int iStack_124;
  ulonglong uStack_120;
  undefined8 uStack_118;
  double dStack_110;
  double dStack_108;
  double dStack_100;
  double dStack_f8;
  double dStack_f0;
  
  DAT_180304a1c = 0;
  DAT_180304a2d = 0;
  puVar2 = *(undefined8 **)(param_1 + 8);
  if (*(char *)(puVar2 + 8) != '\x01') {
    DAT_180304a1c = 0;
    DAT_180304a2d = 0;
    return;
  }
  bVar9 = FUN_180023780(*puVar2,puVar2[5]);
  iVar11 = FUN_1800239f0(*puVar2);
  iVar18 = _DAT_180304a30 + 1;
  _DAT_180304a30 = 0;
  if (iVar11 == 0) {
    _DAT_180304a30 = iVar18;
  }
  if ((((0 < _DAT_180304a34) && (_DAT_180304a34 = _DAT_180304a34 + -1, bVar9 != 0)) &&
      (cVar10 = FUN_180029f80(), cVar10 != '\0')) && (DAT_1802f5930 != '\0')) {
    uVar13 = FUN_180022cf0(*puVar2,puVar2[3]);
    uVar13 = FUN_180025080(*puVar2,uVar13);
    cVar10 = FUN_180025490(*puVar2,uVar13);
    if (cVar10 != '\0') {
      uVar13 = FUN_180023170(*puVar2,puVar2[5]);
      uVar14 = FUN_180029850();
      uVar13 = FUN_180009de0(uVar13,uVar14);
      uVar14 = FUN_180029ff0();
      dVar32 = *(double *)(&UNK_180156158 + (ulonglong)(_DAT_180304a90 < 0.0) * 8);
      uVar15 = FUN_18000a050();
      fVar27 = (float)FUN_18000a3e0(uVar15);
      fVar36 = (float)((double)fVar27 * dVar32);
      uVar15 = FUN_18000a050();
      fVar27 = (float)FUN_18000a3e0(uVar15);
      _DAT_180304a90 = (double)fVar36 + _DAT_180304a90;
      uVar15 = FUN_180009e60(CONCAT44((float)((double)fVar27 * dVar32),fVar36));
      uVar14 = FUN_180009de0(uVar14,uVar15);
      uVar16 = FUN_180009e20(uVar14,uVar13);
      uVar30 = FUN_18000a210(uVar16 & 0xffffffff);
      FUN_180029820(uVar30 & 0xffffffff | uVar16 & 0xffffffff00000000);
      DAT_180304a2d = 1;
      _DAT_180304a38 = (int)_DAT_1802f57f8;
      return;
    }
  }
  uVar13 = FUN_180023670(*puVar2,puVar2[5]);
  FUN_180025640(&dStack_258,*puVar2,uVar13);
  uVar13 = FUN_180023990(*puVar2,puVar2[5]);
  FUN_180025540(&dStack_200,*puVar2,uVar13);
  uVar13 = FUN_180023170(*puVar2,puVar2[5]);
  uVar14 = FUN_180029850();
  uVar13 = FUN_180009de0(uVar13,uVar14);
  if ((((DAT_1802f5950 & bVar9) == 0) && ((_DAT_180304a30 < 0xb || (DAT_1802f5970 == '\0')))) &&
     (lVar17 = FUN_180023930(*puVar2,puVar2[5]), lVar17 == 0)) {
    if (DAT_1802f5990 == '\x01') {
      FUN_180023550(&uStack_118,*puVar2,puVar2[5]);
      dVar32 = (double)func_0x00018013cfd0(uStack_118,dStack_108);
      if ((dVar32 != 0.0) || (NAN(dVar32))) {
        FUN_180023170(*puVar2,puVar2[5]);
        fVar27 = (float)func_0x0001800b1cf0();
        fVar36 = (float)func_0x0001800b3590();
        dVar32 = (double)func_0x00018013cfa0(((double)fVar27 * uStack_118 +
                                             (double)fVar36 * dStack_108) / dVar32);
        if (dVar32 < _DAT_180156090) goto LAB_1800490f4;
      }
      goto LAB_180048d13;
    }
LAB_1800490f4:
    dStack_198 = dStack_1f0;
    dStack_1a8 = dStack_200;
    dStack_1a0 = dStack_1f8;
    DAT_180304a2c = 0;
    dVar32 = dStack_250 + _DAT_1801560a0;
    dVar31 = (dStack_258 + dStack_240) * _DAT_180156098;
    dVar35 = (dStack_248 + dStack_230) * _DAT_180156098;
    if (**(int **)*puVar2 == 0) {
      uVar14 = 0;
    }
    else {
      uVar14 = FUN_1800242c0((undefined8 *)*puVar2,0,0,0);
    }
    dVar33 = (double)func_0x0001800b29b0(dVar31);
    dVar34 = (double)func_0x0001800b29b0(dVar32);
    uVar37 = (uint)dVar33;
    uVar38 = (uint)dVar34;
    dVar33 = (double)func_0x0001800b29b0(dVar35);
    uStack_120 = (ulonglong)(uint)(int)dVar33;
    uStack_190 = (ulonglong)uVar37;
    if (0.0 < _DAT_1802f59c8) {
      iVar11 = 1;
      uVar20 = uVar38;
      do {
        uVar15 = FUN_180024720(*puVar2,puVar2[4],uVar14,uStack_190,uVar20,uStack_120 & 0xffffffff);
        iVar18 = FUN_180024280(*puVar2,uVar15);
        if (iVar18 != 0) goto LAB_180048d13;
        fVar27 = (float)iVar11;
        iVar11 = iVar11 + 1;
        uVar20 = uVar20 - 1;
      } while (fVar27 < _DAT_1802f59c8);
    }
    fVar27 = _DAT_1801560a8;
    uStack_1c8 = (ulonglong)*(ushort *)(&UNK_180156280 + (longlong)(int)_DAT_1802f5a00 * 2);
    lStack_1b0 = -3;
    uStack_150 = uVar13;
    if ((double)_DAT_180304a24 <= dVar32) {
      uVar15 = FUN_180024720(*puVar2,puVar2[4],uVar14,_DAT_180304a20,_DAT_180304a24,_DAT_180304a28);
      iVar11 = FUN_180024280(*puVar2,uVar15);
      if (iVar11 != 0) {
        dStack_148 = (double)CONCAT44(uVar38,uVar37);
        dStack_140 = (double)CONCAT44(dStack_140._4_4_,(int)uStack_120);
        uStack_188 = (double)CONCAT44(_DAT_180304a24 - uVar38,_DAT_180304a20 - uVar37);
        dStack_180 = (double)CONCAT44(dStack_180._4_4_,_DAT_180304a28 - (int)uStack_120);
        puVar39 = &uStack_188;
        uStack_118 = dVar31;
        dStack_110 = dVar32;
        dStack_108 = dVar35;
        fVar36 = (float)FUN_180049f40(&dStack_1a8,uVar13,&uStack_118,&dStack_148,puVar39,&dStack_168
                                     );
        if (fVar36 <= _DAT_1802f5a38) {
          dStack_108 = dStack_198;
          uStack_118 = dStack_1a8;
          dStack_110 = dStack_1a0;
          dStack_138 = dStack_158;
          dStack_148 = dStack_168;
          dStack_140 = dStack_160;
          dVar33 = (double)FUN_1800094b0(&uStack_118,&dStack_148);
          if (dVar33 < _DAT_1801560b0) {
            dStack_108 = dStack_198;
            uStack_118 = dStack_1a8;
            dStack_110 = dStack_1a0;
            uVar13 = FUN_1800254f0(*puVar2,&uStack_118);
            dStack_108 = dStack_158;
            uStack_118 = dStack_168;
            dStack_110 = dStack_160;
            uVar15 = FUN_1800254f0(*puVar2,&uStack_118);
            lVar17 = FUN_180024860(*puVar2,puVar2[4],uVar13,uVar15,
                                   (ulonglong)puVar39 & 0xffffffffffffff00,1,0);
            iVar11 = _DAT_180304a20;
            iVar18 = _DAT_180304a24;
            iVar21 = _DAT_180304a28;
            if (lVar17 != 0) {
              FUN_180024ce0(&uStack_118,*puVar2,lVar17);
              if ((((int)uStack_118 != _DAT_180304a20) || (uStack_118._4_4_ != _DAT_180304a24)) ||
                 (iVar11 = (int)uStack_118, iVar18 = uStack_118._4_4_, iVar21 = dStack_110._0_4_,
                 dStack_110._0_4_ != _DAT_180304a28)) goto LAB_18004968d;
            }
            dStack_1d8 = dStack_158;
            dStack_1e8 = dStack_168;
            dStack_1e0 = dStack_160;
            iStack_12c = iVar11;
            iStack_128 = iVar18;
            iStack_124 = iVar21;
            if ((fVar36 != _DAT_1801560a8) ||
               (fVar27 = _DAT_1801560a8, NAN(fVar36) || NAN(_DAT_1801560a8))) {
              iVar19 = (int)uStack_190;
              iVar23 = iVar19 - iVar11;
              if (iVar19 < iVar11) {
                iVar23 = iVar11 - iVar19;
              }
              iVar11 = uVar38 - iVar18;
              if ((int)uVar38 < iVar18) {
                iVar11 = iVar18 - uVar38;
              }
              iVar19 = (int)uStack_120;
              iVar18 = iVar19 - iVar21;
              if (iVar19 < iVar21) {
                iVar18 = iVar21 - iVar19;
              }
              lStack_1b0 = (ulonglong)(uint)(iVar18 + iVar11 + iVar23) - 2;
              fVar27 = fVar36;
            }
          }
        }
      }
    }
LAB_18004968d:
    dVar33 = _DAT_1801560b0;
    uStack_210 = (ulonglong)uVar38;
    puVar24 = (ushort *)&UNK_180156290;
    uVar16 = 0;
    uStack_208 = uVar14;
    do {
      uVar1 = *puVar24;
      uVar22 = uVar1 >> 4 & 0xf;
      uVar25 = uVar1 >> 8 & 0xf;
      uStack_1c0 = (ulonglong)(((uVar1 & 0xf) + (int)uStack_190) - 8);
      iStack_130 = (uVar22 - 8) + (int)uStack_210;
      uVar20 = (uVar25 - 8) + (int)uStack_120;
      uStack_1b8 = (ulonglong)uVar20;
      uVar13 = FUN_180024720(*puVar2,puVar2[4],uVar14,uStack_1c0,iStack_130,uVar20);
      iVar11 = FUN_180024280(*puVar2,uVar13);
      fVar36 = _DAT_1802f5868;
      if (iVar11 != 0) {
        iVar11 = (uVar1 & 0xf) - 8;
        iVar18 = uVar25 - 8;
        if (iVar18 == 0 && iVar11 == 0) {
          uVar13 = uStack_150;
          if (DAT_1802f5a58 != '\0') goto LAB_180048d13;
          uVar13 = FUN_18000a050();
          fVar28 = (float)FUN_18000a510(0x180304ab8,uVar13);
          fVar27 = _DAT_1802f5868;
          dVar32 = (double)(fVar28 * fVar36) + _DAT_1801560c8;
          uVar13 = FUN_18000a050();
          fVar28 = (float)FUN_18000a510(0x180304a98,uVar13);
          fVar36 = _DAT_1802f5868;
          uVar13 = FUN_18000a050();
          fVar29 = (float)FUN_18000a510(0x180304aa8,uVar13);
          iVar18 = (int)uStack_1c0;
          auVar5._4_8_ = (ulonglong)((double)iVar18 + dVar32) >> 0x20;
          auVar5._0_4_ = (float)((double)iVar18 + dVar32);
          dVar33 = (double)(iVar18 + 1) - dVar32;
          auVar6._4_8_ = (ulonglong)dVar33 >> 0x20;
          auVar6._0_4_ = (float)dVar33;
          FUN_18000a1f0(auVar5._0_8_,auVar6._0_8_,(float)(dVar31 + (double)(fVar28 * fVar27)));
          iVar11 = (int)uStack_1b8;
          auVar7._4_8_ = (ulonglong)((double)iVar11 + dVar32) >> 0x20;
          auVar7._0_4_ = (float)((double)iVar11 + dVar32);
          dVar32 = (double)(iVar11 + 1) - dVar32;
          auVar8._4_8_ = (ulonglong)dVar32 >> 0x20;
          auVar8._0_4_ = (float)dVar32;
          FUN_18000a1f0(auVar7._0_8_,auVar8._0_8_,(float)(dVar35 + (double)(fVar29 * fVar36)));
          FUN_1800093b0(&uStack_118);
          _DAT_180304a58 = dStack_108;
          _DAT_180304a48 = uStack_118;
          dRam0000000180304a50 = dStack_110;
          _DAT_180304a24 = iStack_130;
          DAT_180304a2c = 1;
          _DAT_180304a20 = iVar18;
          _DAT_180304a28 = iVar11;
          goto LAB_180049a9f;
        }
        iVar23 = uVar22 - 8;
        iVar21 = -iVar11;
        if (-iVar11 < 0) {
          iVar21 = iVar11;
        }
        iVar19 = -iVar23;
        if (-iVar23 < 0) {
          iVar19 = iVar23;
        }
        iVar26 = -iVar18;
        if (-iVar18 < 0) {
          iVar26 = iVar18;
        }
        uVar30 = (ulonglong)(uint)(iVar26 + iVar19 + iVar21);
        uStack_1c8 = (ulonglong)*(ushort *)(&UNK_180156280 + uVar30 * 2);
        dStack_148 = (double)CONCAT44(uVar38,uVar37);
        dStack_140 = (double)CONCAT44(dStack_140._4_4_,(int)uStack_120);
        uStack_188 = (double)CONCAT44(iVar23,iVar11);
        dStack_180 = (double)CONCAT44(dStack_180._4_4_,iVar18);
        uStack_118 = dVar31;
        dStack_110 = dVar32;
        dStack_108 = dVar35;
        fVar36 = (float)FUN_180049f40(&dStack_1a8,uStack_150,&uStack_118,&dStack_148,&uStack_188,
                                      &dStack_168);
        if ((fVar36 <= fVar27) || (uVar14 = uStack_208, (longlong)uVar30 < lStack_1b0)) {
          dStack_108 = dStack_198;
          uStack_118 = dStack_1a8;
          dStack_110 = dStack_1a0;
          dStack_138 = dStack_158;
          dStack_148 = dStack_168;
          dStack_140 = dStack_160;
          dVar34 = (double)FUN_1800094b0(&uStack_118,&dStack_148);
          uVar14 = uStack_208;
          if (dVar34 < dVar33) {
            dStack_1d8 = dStack_158;
            dStack_1e8 = dStack_168;
            dStack_1e0 = dStack_160;
            iStack_12c = (int)uStack_1c0;
            iStack_128 = iStack_130;
            iStack_124 = (int)uStack_1b8;
            fVar27 = fVar36;
          }
        }
      }
      uVar16 = uVar16 + 1;
      puVar24 = puVar24 + 1;
    } while (uVar16 < uStack_1c8);
    uVar13 = uStack_150;
    if (_DAT_1802f5a38 < fVar27) goto LAB_180048d13;
    _DAT_180304a58 = dStack_1d8;
    _DAT_180304a48 = dStack_1e8;
    dRam0000000180304a50 = dStack_1e0;
    _DAT_180304a20 = iStack_12c;
    _DAT_180304a24 = iStack_128;
    _DAT_180304a28 = iStack_124;
LAB_180049a9f:
    uVar13 = uStack_150;
    if (_DAT_1802f5ac8 == 1) {
      uVar14 = 0;
LAB_180049abe:
      FUN_18002af50(puVar2,0x1802f5580,uVar14);
    }
    else if (_DAT_1802f5ac8 == 2) {
      uVar14 = 1;
      goto LAB_180049abe;
    }
    uVar14 = FUN_180028a50(*puVar2,puVar2[5]);
    DAT_180304a1c = FUN_180028b00(*puVar2,uVar14);
    fVar27 = _DAT_1802f5830;
    if (DAT_180304a1c != '\0') {
      uVar14 = FUN_18000a050();
      fVar36 = (float)FUN_18000a3e0(uVar14);
      _DAT_180304a38 = (int)(fVar36 * fVar27);
      _DAT_180304a34 = 10;
      DAT_180304a3c = DAT_1802f5af0;
      goto LAB_180048d5b;
    }
  }
  else {
LAB_180048d13:
    DAT_180304a1c = '\0';
  }
  if (_DAT_180304a38 < 1) {
    if (_DAT_180304a40 < 1) {
      if (DAT_180304a3c != '\x01') {
        return;
      }
      FUN_1800284f0(puVar2[1],0x1802f5580,0);
      DAT_180304a3c = 0;
      return;
    }
    _DAT_180304a40 = _DAT_180304a40 + -1;
    DAT_180304a1c = '\0';
  }
  else {
    _DAT_180304a38 = _DAT_180304a38 + -1;
    _DAT_180304a40 = (int)_DAT_1802f57f8;
  }
LAB_180048d5b:
  cVar10 = FUN_180029800(1000);
  iVar21 = _DAT_180304a40;
  iVar18 = _DAT_180304a24;
  iVar11 = _DAT_180304a20;
  if (cVar10 != '\0') {
    DAT_180304a2d = 1;
    if (DAT_180304a1c == '\0') {
      if (0 < _DAT_180304a38) {
        DAT_180304a2d = 1;
        return;
      }
      if (_DAT_180304a40 < 1) {
        DAT_180304a2d = 1;
        return;
      }
      cVar10 = FUN_180029f80();
      if (cVar10 == '\0') {
        return;
      }
      uVar13 = FUN_180023170(*puVar2,puVar2[5]);
      uVar14 = FUN_180029850();
      uVar13 = FUN_180009de0(uVar13,uVar14);
      uVar14 = FUN_180029ff0();
      uVar16 = FUN_180009e20(uVar14,uVar13);
      uVar30 = FUN_18000a210(uVar16 & 0xffffffff);
      uVar16 = FUN_180009e60(uVar30 & 0xffffffff | uVar16 & 0xffffffff00000000,
                             _DAT_1801560d8 / (float)iVar21);
    }
    else {
      dVar35 = (double)_DAT_180304a28;
      iVar21 = _DAT_180304a24 + 1;
      dVar32 = _DAT_1801560e0 + dVar35;
      FUN_1800233b0(&dStack_148,*puVar2,puVar2[5]);
      dStack_108 = dStack_138;
      uStack_118 = dStack_148;
      dStack_110 = dStack_140;
      FUN_180009430(&dStack_168,&uStack_118,_DAT_1801560e8);
      uStack_118 = (double)iVar11 + _DAT_1801560f0;
      dStack_110 = (double)iVar18 + _UNK_1801560f8;
      dStack_108 = dVar35 + _DAT_180156100;
      dStack_100 = (double)iVar11 + _UNK_180156108;
      dStack_178 = dStack_1f0;
      uStack_188 = dStack_200;
      dStack_180 = dStack_1f8;
      dStack_218 = dStack_158;
      dStack_228 = dStack_168;
      dStack_220 = dStack_160;
      dStack_f8 = (double)iVar21;
      dStack_f0 = dVar32;
      cVar10 = FUN_180009b00(&uStack_118,&uStack_188,&dStack_228,&dStack_1e8);
      if ((cVar10 != '\0') && (dStack_1e0 < (double)_DAT_180304a24 + _DAT_180156110)) {
        return;
      }
      dStack_108 = dStack_1f0;
      uStack_118 = dStack_200;
      dStack_110 = dStack_1f8;
      dStack_178 = _DAT_180304a58;
      uStack_188 = _DAT_180304a48;
      dStack_180 = dRam0000000180304a50;
      uVar14 = FUN_180009f80(&uStack_118,&uStack_188);
      uVar12 = FUN_180009e20(uVar14,uVar13);
      if ((double)(float)((ulonglong)uVar14 >> 0x20) <= _DAT_180156118) {
        FUN_18000a210(uVar12);
      }
      else {
        uVar13 = FUN_18000a050();
        FUN_18000a510(0x180304a60,uVar13,_DAT_180156098);
      }
      dVar35 = _DAT_180156128;
      dVar32 = _DAT_1801560c0;
      dVar31 = (double)_DAT_1802f5868 * _DAT_180156128 + _DAT_1801560c0;
      auVar3._4_8_ = (ulonglong)dVar31 >> 0x20;
      auVar3._0_4_ = (float)dVar31;
      uVar13 = FUN_18000a050(auVar3._0_8_);
      FUN_18000a870(0x180304a70,uVar13);
      dVar32 = (double)_DAT_1802f5868 * dVar35 + dVar32;
      auVar4._4_8_ = (ulonglong)dVar32 >> 0x20;
      auVar4._0_4_ = (float)dVar32;
      uVar13 = FUN_18000a050(auVar4._0_8_);
      FUN_18000a870(0x180304a80,uVar13);
      FUN_18000a1f0();
      FUN_18000a1f0();
      uVar13 = FUN_18000a050();
      FUN_18000a870(0x180304a70,uVar13);
      uVar13 = FUN_18000a050();
      FUN_18000a870(0x180304a80,uVar13);
      uVar16 = FUN_18000a2b0();
      lVar17 = FUN_18000a2b0();
      uVar16 = uVar16 & 0xffffffff | lVar17 << 0x20;
    }
    FUN_180029820(uVar16);
  }
  return;
}

// UI RVA 0x49c00; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x49c00; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180049c00(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_1801564bc);
  FUN_18000cf30(param_2,param_1,0x1802f59d0);
  FUN_18000cf30(param_2,param_1,0x1802f5a08);
  FUN_18000cf30(param_2,param_1,0x1802f5998);
  FUN_18000cf30(param_2,param_1,0x1802f5790);
  FUN_18000cf30(param_2,param_1,0x1802f5838);
  FUN_18000d040(param_2,param_1,0x1802f5a98);
  FUN_18000cef0(param_2,param_1,0x1802f5a40);
  FUN_180013e90(param_1,param_2,&UNK_1801564c1);
  FUN_18000cf30(param_2,param_1,0x1802f5870);
  FUN_18000cf30(param_2,param_1,0x1802f58a8);
  FUN_18000cf30(param_2,param_1,0x1802f58e0);
  FUN_18000cef0(param_2,param_1,0x1802f5a60);
  FUN_180013e90(param_1,param_2,&UNK_1801564c5);
  FUN_18000cf30(param_2,param_1,0x1802f5800);
  FUN_18000cf30(param_2,param_1,0x1802f57c8);
  FUN_18000cef0(param_2,param_1,0x1802f5918);
  FUN_18000cef0(param_2,param_1,0x1802f5ad8);
  FUN_180013e90(param_1,param_2,&UNK_1801564cf);
  FUN_18000cef0(param_2,param_1,0x1802f5938);
  FUN_18000cef0(param_2,param_1,0x1802f5958);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802f5988,0x1802f5978,&DAT_1802f5990);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x49da0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x49da0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180049da0(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c450(param_1,&UNK_1801564da,0x1802f59d0);
  FUN_18000c450(param_1,&UNK_1801564e0,0x1802f5a08);
  FUN_18000c450(param_1,&UNK_1801564ed,0x1802f5998);
  FUN_18000c450(param_1,&UNK_1801564f8,0x1802f5790);
  FUN_18000c450(param_1,&UNK_180156504,0x1802f5838);
  FUN_18000c6f0(param_1,&UNK_180156512,0x1802f5a98);
  FUN_18000c3b0(param_1,&UNK_180156520,0x1802f5a40);
  FUN_18000c450(param_1,&UNK_18015652e,0x1802f5870);
  FUN_18000c450(param_1,&UNK_180156538,0x1802f58a8);
  FUN_18000c450(param_1,&UNK_180156541,0x1802f58e0);
  FUN_18000c3b0(param_1,&UNK_180156553,0x1802f5a60);
  FUN_18000c450(param_1,&UNK_180156562,0x1802f5800);
  FUN_18000c450(param_1,&UNK_180156571,0x1802f57c8);
  FUN_18000c3b0(param_1,&UNK_180156583,0x1802f5918);
  FUN_18000c3b0(param_1,&UNK_18015659c,0x1802f5ad8);
  FUN_18000c3b0(param_1,&UNK_1801565b3,0x1802f5938);
  FUN_18000c3b0(param_1,&UNK_1801565bf,0x1802f5958);
  uVar1 = uRam00000001802f5991;
  uVar2 = DAT_1802f5990;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_1801565ce,DAT_1802f5990);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802f5990;
      break;
    case 2:
      uRam00000001802f5991 = DAT_1802f5990;
      break;
    case 3:
      uVar2 = uRam00000001802f5991;
    }
  }
  DAT_1802f5990 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x49f40; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x49f40; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
FUN_180049f40(undefined8 *param_1,undefined8 param_2,double *param_3,int *param_4,uint *param_5,
             undefined8 *param_6)

{
  double dVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined1 auVar6 [16];
  double dVar7;
  double dVar8;
  uint uVar9;
  uint uVar10;
  undefined8 uVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  ulonglong uVar21;
  ulonglong uVar22;
  undefined1 auVar23 [16];
  undefined1 auVar24 [16];
  undefined1 auVar25 [16];
  double dVar26;
  double dVar27;
  double dVar28;
  double dVar29;
  double dVar30;
  undefined4 uVar31;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  int iStack_e4;
  int iStack_e0;
  int iStack_dc;
  undefined8 extraout_XMM0_Qb;
  
  fVar18 = _DAT_1802f5868;
  iStack_e0 = *param_4;
  iStack_e4 = param_4[1];
  uVar2 = *param_5;
  uVar3 = param_5[1];
  iStack_dc = param_4[2];
  uVar4 = param_5[2];
  uStack_f0 = param_2;
  uVar11 = FUN_18000a050(param_1,_DAT_180156170);
  dVar26 = _DAT_180156178;
  fVar15 = (float)FUN_18000a510(0x180304ab8,uVar11,SUB84(_DAT_180156178,0));
  fVar19 = _DAT_1802f5868;
  uVar12 = *param_5;
  uVar5 = param_5[2];
  uVar11 = FUN_18000a050();
  uVar31 = (undefined4)_DAT_180156188;
  fVar16 = (float)FUN_18000a510(0x180304ac8,uVar11,uVar31);
  fVar20 = _DAT_1802f5868;
  uVar11 = FUN_18000a050();
  fVar17 = (float)FUN_18000a510(0x180304ad8,uVar11,uVar31);
  dVar7 = (double)(fVar17 * fVar20);
  dVar8 = (double)(fVar16 * fVar19);
  dVar1 = *param_3;
  if (DAT_1802f5a78 == '\0') {
    uVar31 = SUB84(_DAT_180156178,0);
    uVar21 = func_0x0001800b2170(dVar1,uVar31);
    dVar29 = param_3[2];
    uVar22 = func_0x0001800b2170(dVar29,uVar31);
    dVar28 = (double)(uVar21 & _DAT_180156190);
    dVar30 = (double)(uVar22 & _UNK_180156198);
    uVar22 = -(ulonglong)(_DAT_180304a58 < dVar29);
    uVar21 = (ulonglong)_UNK_1801561b8 & -(ulonglong)(_DAT_180304a48 < dVar1);
    auVar25._0_8_ = ~uVar22 & _DAT_1801561c0;
    auVar25._8_8_ = ~-(ulonglong)(_DAT_180304a48 < dVar1) & _UNK_1801561c8;
    auVar6._8_4_ = (int)uVar21;
    auVar6._0_8_ = (ulonglong)_DAT_1801561b0 & uVar22;
    auVar6._12_4_ = (int)(uVar21 >> 0x20);
    dVar7 = dVar7 + (double)((ulonglong)(dVar28 + _DAT_1801561b0) & _DAT_180156190 &
                             -(ulonglong)(_DAT_1801561a0 < dVar28) |
                            ~-(ulonglong)(_DAT_1801561a0 < dVar28) & (ulonglong)dVar28) *
                    SUB168(auVar25 | auVar6,0);
    dVar8 = dVar8 + (double)((ulonglong)(dVar30 + _UNK_1801561b8) & _UNK_180156198 &
                             -(ulonglong)(_UNK_1801561a8 < dVar30) |
                            ~-(ulonglong)(_UNK_1801561a8 < dVar30) & (ulonglong)dVar30) *
                    SUB168(auVar25 | auVar6,8);
  }
  uVar10 = -uVar2;
  if ((int)-uVar2 < 0) {
    uVar10 = uVar2;
  }
  uVar9 = -uVar4;
  if ((int)-uVar4 < 0) {
    uVar9 = uVar4;
  }
  dVar28 = (double)(fVar18 * fVar15) + _DAT_1801561d0;
  dVar26 = dVar26 - dVar28;
  dVar29 = (double)(uVar4 >> 0x1f);
  dVar27 = dVar26;
  dVar30 = dVar29;
  if (uVar9 < uVar10) {
    dVar29 = dVar28;
    dVar27 = (double)(uVar2 >> 0x1f);
    dVar28 = (double)(uVar2 >> 0x1f);
    dVar30 = dVar26;
  }
  uVar10 = -uVar12;
  if ((int)uVar10 < 0) {
    uVar10 = uVar12;
  }
  uVar12 = -uVar5;
  if ((int)uVar12 < 0) {
    uVar12 = uVar5;
  }
  iVar13 = uVar4 + iStack_dc;
  iVar14 = uVar3 + iStack_e4;
  dVar28 = dVar28 + (double)(int)(uVar2 + iStack_e0);
  fVar18 = (float)FUN_18000a1f0(CONCAT44((int)((ulonglong)dVar28 >> 0x20),(float)dVar28),
                                (float)(dVar27 + (double)(int)(uVar2 + iStack_e0)),
                                (float)(dVar8 + dVar1));
  dVar1 = (double)iVar14 + _DAT_1801561d8;
  fVar19 = (float)FUN_18000a1f0(0,_DAT_1801561e0,
                                (float)((double)(int)(uVar12 + uVar10) * _DAT_1801561d8));
  fVar20 = (float)FUN_18000a1f0((float)(dVar29 + (double)iVar13),(float)(dVar30 + (double)iVar13),
                                (float)(dVar7 + param_3[2]));
  FUN_1800093b0(&uStack_108,SUB84((double)fVar18,0),SUB84((double)fVar19 + dVar1,0),(double)fVar20);
  uStack_138 = param_1[2];
  uStack_148 = *param_1;
  uStack_140 = param_1[1];
  uStack_118 = uStack_f8;
  uStack_128 = uStack_108;
  uStack_120 = uStack_100;
  uVar11 = FUN_180009f80(&uStack_148,&uStack_128);
  uVar21 = FUN_180009e20(uVar11,uStack_f0);
  auVar23._0_8_ = FUN_18000a210(uVar21 & 0xffffffff);
  auVar23._8_8_ = extraout_XMM0_Qb;
  *param_6 = uStack_108;
  param_6[1] = uStack_100;
  param_6[2] = uStack_f8;
  auVar24._4_12_ = SUB1612(auVar23 & _DAT_1801561f0,4);
  auVar24._0_4_ = SUB164(auVar23 & _DAT_1801561f0,0) + ABS((float)(uVar21 >> 0x20));
  return auVar24._0_8_;
}

