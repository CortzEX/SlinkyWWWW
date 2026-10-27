// Recovered decompiler view: Name Tags
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x3c210, 0x3da80); proximity does not prove ownership.

// CALLBACK RVA 0x3c210; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/name_tags/name_tags.c
// Differential report: analysis/module_behavior_recovery/name_tags/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3c210; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003c210(longlong param_1)

{
  if ((*(char *)(param_1 + 0x18) == '\0') && (*(longlong *)(param_1 + 0x10) == 0x1802f02d0)) {
    FUN_18003d800(**(undefined8 **)(param_1 + 8));
    if (_DAT_1803007a0 != 0) {
      (**(code **)(**(longlong **)(**(longlong **)(param_1 + 8) + 8) + 0xb0))();
      _DAT_1803007a0 = 0;
    }
  }
  return;
}

// CALLBACK RVA 0x3c280; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/name_tags/name_tags.c
// Differential report: analysis/module_behavior_recovery/name_tags/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3c280; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003c280(longlong param_1)

{
  undefined8 *puVar1;
  double dVar2;
  undefined8 *puVar3;
  double dVar4;
  float fVar5;
  double dVar6;
  double dVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  float fVar10;
  float *pfVar11;
  char cVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  longlong lVar15;
  longlong lVar16;
  longlong lVar17;
  int iVar18;
  char *pcVar19;
  int iVar20;
  ulonglong uVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  longlong in_stack_fffffffffffffe48;
  undefined4 uVar26;
  float fStack_198;
  float fStack_194;
  float fStack_190;
  float fStack_18c;
  undefined8 uStack_188;
  undefined8 uStack_180;
  ulonglong uStack_178;
  float *pfStack_170;
  undefined4 uStack_168;
  undefined4 uStack_164;
  double dStack_160;
  undefined8 uStack_158;
  undefined8 uStack_148;
  double dStack_140;
  undefined8 uStack_138;
  undefined8 uStack_128;
  double dStack_120;
  undefined8 uStack_118;
  char *pcStack_110;
  longlong lStack_108;
  longlong lStack_100;
  longlong lStack_f8;
  undefined4 uStack_ec;
  
  if ((_DAT_1802fc910 != 0) && (_DAT_1803007a0 != 0)) {
    puVar1 = *(undefined8 **)(param_1 + 0x20);
    uVar13 = FUN_180022d40(*puVar1,puVar1[3]);
    uVar13 = FUN_1800272a0(*puVar1,uVar13);
    uStack_180 = FUN_180022dd0(*puVar1,puVar1[3]);
    uStack_ec = FUN_180027b50(*puVar1,_DAT_1803007a0);
    FUN_180027b70(*puVar1,_DAT_1803007a0,_DAT_1801536d0);
    uVar14 = FUN_180022d90(*puVar1,puVar1[3]);
    fVar22 = (float)FUN_1800273e0(*puVar1,uVar14,*(undefined4 *)(param_1 + 0x40));
    fVar10 = _DAT_180153714;
    uVar9 = _DAT_180153710;
    uVar8 = _DAT_180153700;
    dVar7 = _DAT_1801536f8;
    dVar6 = _DAT_1801536f0;
    fVar5 = _DAT_1801536e8;
    dVar4 = _DAT_1801536d8;
    if (_DAT_1802fc910 != 0) {
      pfStack_170 = (float *)(param_1 + 8);
      fVar22 = _DAT_1801536d4 / fVar22;
      pcVar19 = (char *)0x1802fc970;
      uVar21 = 0;
      fVar25 = _DAT_1801536e0;
      lStack_f8 = param_1;
      do {
        lStack_108 = uVar21 * 0xa0;
        uStack_138 = *(undefined8 *)(lStack_108 + 0x1802fc930);
        uStack_148 = *(undefined8 *)(lStack_108 + 0x1802fc920);
        dStack_140 = *(double *)(lStack_108 + 0x1802fc928);
        uStack_118 = *(undefined8 *)(lStack_108 + 0x1802fc948);
        uStack_128 = *(undefined8 *)(lStack_108 + 0x1802fc938);
        dStack_120 = *(double *)(lStack_108 + 0x1802fc940);
        uStack_178 = uVar21;
        FUN_180009460(&uStack_168,&uStack_148,&uStack_128,(double)*(float *)(param_1 + 0x40));
        pfVar11 = pfStack_170;
        dStack_160 = dStack_160 + dVar4;
        uStack_118 = uStack_158;
        uStack_128 = CONCAT44(uStack_164,uStack_168);
        uStack_188 = *(undefined8 *)(pfStack_170 + 4);
        fStack_198 = *pfStack_170;
        fStack_194 = pfStack_170[1];
        fStack_190 = pfStack_170[2];
        fStack_18c = pfStack_170[3];
        dStack_120 = dStack_160;
        FUN_1800093d0(&uStack_148,&uStack_128,&fStack_198);
        param_1 = lStack_f8;
        uStack_158 = uStack_138;
        uStack_168 = (undefined4)uStack_148;
        uStack_164 = uStack_148._4_4_;
        dStack_160 = dStack_140;
        cVar12 = FUN_1800295f0(pfVar11,&uStack_148,&uStack_128,&fStack_198);
        uVar26 = (undefined4)((ulonglong)in_stack_fffffffffffffe48 >> 0x20);
        if (cVar12 != '\0') {
          (*(code *)*_DAT_180150cc0)();
          (*(code *)*_DAT_180150cd8)((undefined4)uStack_128,uStack_128._4_4_,fStack_198 * fVar25);
          lVar15 = lStack_108;
          fVar23 = fStack_198 * _DAT_1801536e4;
          fVar24 = fVar23;
          if (fVar23 <= fVar5) {
            fVar24 = fVar5;
          }
          if (DAT_1802f0530 == '\0') {
            fVar24 = fVar23;
          }
          lVar16 = lStack_108 + 0x1802fc920;
          fVar24 = _DAT_1802f0510 * fVar22 * fVar24;
          (*(code *)*_DAT_180150cd0)(fVar24,fVar24,fVar24);
          dVar2 = (double)-*(int *)(lVar15 + 0x1802fc960) * dVar6 + dVar7;
          if (*(char *)(param_1 + 0x44) == '\x01') {
            FUN_180027760(*puVar1);
          }
          else {
            (*(code *)*_DAT_18013e450)(0xb71);
          }
          fVar24 = (float)dVar2;
          if (DAT_1802f0550 == '\x01') {
            if (*(char *)(param_1 + 0x44) == '\x01') {
              FUN_180027820(*puVar1);
              uVar14 = CONCAT44(uVar26,0x3f000000);
              FUN_1800278f0(*puVar1,0,0,0,uVar14);
              uVar26 = (undefined4)((ulonglong)uVar14 >> 0x20);
            }
            else {
              (*(code *)*_DAT_18013e450)(0xde1);
              (*(code *)*_DAT_18013e448)(0,0,0,uVar8);
            }
            fVar25 = (float)((double)*(int *)(lVar15 + 0x1802fc960) * dVar6 + _DAT_180153708);
            (*(code *)*_DAT_180150c98)(5);
            puVar3 = _DAT_180150ce0;
            (*(code *)*_DAT_180150ce0)(fVar24,0);
            (*(code *)*puVar3)(fVar25,0);
            (*(code *)*puVar3)(fVar24,uVar9);
            (*(code *)*puVar3)(fVar25,uVar9);
            (*(code *)*_DAT_180150ca8)();
            fVar25 = _DAT_1801536e0;
          }
          pcStack_110 = pcVar19;
          if (*(char *)(param_1 + 0x44) == '\x01') {
            FUN_1800277f0(*puVar1);
            uVar14 = CONCAT44(uVar26,0x3f800000);
            FUN_1800278f0(*puVar1,fVar5,fVar5,fVar5,uVar14);
            uVar26 = (undefined4)((ulonglong)uVar14 >> 0x20);
          }
          else {
            (*(code *)*_DAT_18013e458)(0xde1);
            (*(code *)*_DAT_180150ca0)(fVar5,fVar5,fVar5);
          }
          in_stack_fffffffffffffe48 = CONCAT44(uVar26,0xc1200000);
          FUN_180027590(*puVar1,uVar13,*(undefined8 *)(lVar15 + 0x1802fc958),
                        CONCAT44((int)((ulonglong)dVar2 >> 0x20),fVar24 + fVar10),
                        in_stack_fffffffffffffe48,0xffffffff,DAT_1802f0570);
          if (DAT_1802f0590 == '\x01') {
            if (*(char *)(lStack_f8 + 0x44) == '\x01') {
              FUN_180027730(*puVar1);
            }
            else {
              (*(code *)*_DAT_18013e458)(0xb71);
            }
            FUN_180027c90(*puVar1);
            (*(code *)*_DAT_180150cd0)(fVar5,fVar5,_DAT_180153718);
            iVar18 = *(int *)(lVar15 + 0x1802fc96c) * -8;
            lStack_100 = lVar15 + 0x1802fc970;
            uVar21 = 0;
            pcVar19 = pcStack_110;
            lStack_108 = lVar16;
            do {
              if ((*pcVar19 == '\x01') &&
                 (lVar15 = FUN_180024050(*puVar1,*(undefined8 *)(lVar16 + 0x30),uVar21 & 0xffffffff)
                 , uVar14 = uStack_180, lVar15 != 0)) {
                FUN_180027ba0(*puVar1,_DAT_1803007a0,uVar13,uStack_180,lVar15,iVar18,0xffffffe0);
                lVar16 = lStack_108;
                FUN_180027c10(*puVar1,_DAT_1803007a0,uVar13,uVar14,lVar15,iVar18,0xffffffe0,0);
                iVar18 = iVar18 + 0x10;
                in_stack_fffffffffffffe48 = lVar15;
              }
              uVar21 = uVar21 + 1;
              pcVar19 = pcVar19 + 0x10;
            } while (uVar21 != 5);
            FUN_180027cc0(*puVar1);
            if (*(char *)(lStack_f8 + 0x44) == '\0') {
              (*(code *)*_DAT_18013e458)(0xbe2);
              (*(code *)*_DAT_18013e450)(0xbc0);
              (*(code *)*_DAT_18013e438)(0x302,0x303);
            }
            else {
              FUN_180027790(*puVar1);
              FUN_180027880(*puVar1);
              FUN_1800278b0(*puVar1,0x302,0x303);
            }
            lVar15 = lStack_100;
            (*(code *)*_DAT_180150ca0)(fVar5,fVar5,fVar5);
            (*(code *)*_DAT_180150cd0)(uVar8,uVar8,uVar8);
            if (DAT_1802f05b0 == '\x01') {
              iVar18 = *(int *)(lVar16 + 0x4c) * -8;
              lVar16 = 0;
              do {
                if (*(char *)(lVar15 + lVar16 * 0x10) == '\x01') {
                  lVar15 = lVar16 * 0x10 + lVar15;
                  if ((*(longlong *)(lVar15 + 8) != 0) && (0 < *(int *)(lVar15 + 4))) {
                    iVar20 = -0x40;
                    lVar17 = 0;
                    do {
                      in_stack_fffffffffffffe48 =
                           CONCAT44((int)((ulonglong)in_stack_fffffffffffffe48 >> 0x20),
                                    (float)iVar20);
                      FUN_180027590(*puVar1,uVar13,
                                    *(undefined8 *)(*(longlong *)(lVar15 + 8) + lVar17 * 8),
                                    (float)(iVar18 * 2),in_stack_fffffffffffffe48,0xffffffff,1);
                      lVar17 = lVar17 + 1;
                      iVar20 = iVar20 + 8;
                    } while (lVar17 < *(int *)(lVar15 + 4));
                  }
                  iVar18 = iVar18 + 0x10;
                  lVar15 = lStack_100;
                }
                lVar16 = lVar16 + 1;
              } while (lVar16 != 5);
            }
          }
          (*(code *)*_DAT_180150cb8)();
          pcVar19 = pcStack_110;
          param_1 = lStack_f8;
        }
        uVar21 = uStack_178 + 1;
        pcVar19 = pcVar19 + 0xa0;
      } while (uVar21 < _DAT_1802fc910);
    }
    puVar3 = _DAT_18013e450;
    if (*(char *)(param_1 + 0x44) == '\0') {
      (*(code *)*_DAT_18013e450)(0xde1);
      (*(code *)*puVar3)(0xb71);
    }
    else {
      FUN_180027820(*puVar1);
      FUN_180027760(*puVar1);
    }
    FUN_180027b70(*puVar1,_DAT_1803007a0,uStack_ec);
  }
  return;
}

// CALLBACK RVA 0x3ca20; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/name_tags_update/name_tags_update.c
// Differential report: analysis/module_behavior_recovery/name_tags_update/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3ca20; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003ca20(longlong param_1)

{
  longlong *plVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  char cVar10;
  char cVar11;
  short sVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  longlong lVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  longlong *plVar19;
  longlong lVar20;
  ulonglong uVar21;
  undefined *puVar22;
  longlong lVar23;
  ulonglong uVar24;
  ulonglong uVar25;
  bool bVar26;
  undefined4 uVar27;
  float fVar28;
  float fVar29;
  double dVar30;
  double dVar31;
  undefined4 uStack_1f0;
  undefined4 uStack_1ec;
  undefined4 uStack_1e8;
  undefined4 uStack_1e4;
  undefined8 uStack_1e0;
  undefined8 uStack_1d8;
  undefined8 uStack_1d0;
  undefined8 uStack_1c8;
  longlong lStack_1c0;
  longlong lStack_1b8;
  ulonglong uStack_1b0;
  longlong lStack_1a8;
  undefined8 uStack_1a0;
  undefined4 uStack_198;
  undefined4 uStack_194;
  undefined4 uStack_190;
  undefined4 uStack_18c;
  undefined8 uStack_188;
  longlong *plStack_180;
  undefined8 uStack_178;
  undefined8 uStack_170;
  undefined8 uStack_168;
  undefined8 uStack_158;
  undefined8 uStack_150;
  undefined8 uStack_148;
  uint uStack_134;
  longlong lStack_130;
  uint uStack_124;
  longlong lStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_f8;
  longlong *plStack_f0;
  
  plVar1 = *(longlong **)(param_1 + 8);
  FUN_18003d800(*plVar1);
  if (plVar1[4] == 0) {
    return;
  }
  if (_DAT_1803007a0 == 0) {
    puVar2 = (undefined8 *)*plVar1;
    plVar3 = (longlong *)puVar2[1];
    if (*(int *)*puVar2 == 0) {
      lVar16 = FUN_180027b20();
      if (lVar16 == 0) goto LAB_18003cae5;
    }
    else {
      lVar16 = FUN_180022db0(puVar2,plVar1[3]);
    }
    _DAT_1803007a0 = (**(code **)(*plVar3 + 0xa8))(plVar3,lVar16);
  }
LAB_18003cae5:
  FUN_180023030(&uStack_1f0,*plVar1,plVar1[5]);
  FUN_1800230d0(&uStack_1d8,*plVar1,plVar1[5]);
  uVar17 = FUN_180024600(*plVar1,plVar1[4]);
  plVar3 = *(longlong **)(*plVar1 + 8);
  uVar18 = FUN_180022d40(*plVar1,plVar1[3]);
  lStack_1a8 = FUN_1800272a0(*plVar1,uVar18);
  if (lStack_1a8 != 0) {
    lVar16 = (**(code **)(*plVar3 + 0x538))(plVar3,&UNK_1801537bb);
    lStack_1b8 = (**(code **)(*plVar3 + 0x538))(plVar3,&UNK_1801537be);
    if (lStack_1b8 != 0 && lVar16 != 0) {
      lStack_1c0 = lVar16;
      plStack_180 = plVar3;
      iVar13 = FUN_180024e50(*plVar1,uVar17);
      fVar9 = _DAT_180153734;
      fVar8 = _DAT_18015372c;
      fVar7 = _DAT_180153728;
      fVar6 = _DAT_180153724;
      uVar5 = _DAT_180153720;
      uVar4 = _DAT_18015371c;
      if (0 < iVar13) {
        uVar25 = 0;
        uStack_1a0 = uVar17;
        do {
          uStack_f8 = FUN_180024e80(*plVar1,uVar17,uVar25);
          cVar10 = (**(code **)(**(longlong **)(*plVar1 + 8) + 0xc0))
                             (*(longlong **)(*plVar1 + 8),uStack_f8,plVar1[5]);
          if (cVar10 == '\0') {
LAB_18003cc7e:
            uVar14 = FUN_18002acb0(*plVar1,uStack_f8);
            if (((uVar14 & 2) == 0) && (cVar11 = FUN_1800237b0(*plVar1,uStack_f8), cVar11 == '\0'))
            {
              FUN_180023030(&uStack_178,*plVar1,uStack_f8);
              uStack_108 = uStack_168;
              uStack_118 = uStack_178;
              uStack_110 = uStack_170;
              uStack_148 = uStack_1e0;
              uStack_158 = CONCAT44(uStack_1ec,uStack_1f0);
              uStack_150 = CONCAT44(uStack_1e4,uStack_1e8);
              dVar30 = (double)FUN_1800094b0(&uStack_118,&uStack_158);
              if (dVar30 <= (double)(_DAT_1802f05e8 * _DAT_1802f05e8)) {
                lVar16 = *plVar1;
                plVar3 = *(longlong **)(lVar16 + 8);
                uStack_1b0 = uVar25;
                if (DAT_1802f0628 == '\x01') {
                  uVar17 = FUN_180023800(lVar16,uStack_f8);
                  plVar19 = (longlong *)FUN_180026090(*plVar1,uVar17);
                  if ((DAT_1802f0648 != '\0') || (DAT_1802f0668 != '\0')) goto LAB_18003cd6c;
                }
                else {
                  plVar19 = (longlong *)FUN_180023830(lVar16,uStack_f8);
LAB_18003cd6c:
                  iVar15 = (**(code **)(*plVar3 + 0x540))(plVar3,plVar19);
                  lStack_130 = CONCAT44(lStack_130._4_4_,iVar15);
                  iVar13 = 0x40;
                  if (iVar15 < 0x40) {
                    iVar13 = iVar15;
                  }
                  lStack_120 = CONCAT44(lStack_120._4_4_,iVar13);
                  plStack_f0 = plVar19;
                  lVar16 = (**(code **)(*plVar3 + 0x548))(plVar3,plVar19,0);
                  FUN_18000dc20(&uStack_118,0x1803007b0,0x80);
                  uVar17 = uStack_f8;
                  if (DAT_1802f0648 == '\x01') {
                    uVar27 = FUN_180023a40(*plVar1,uStack_f8);
                    fVar28 = (float)FUN_18000a1f0(0,uVar4,uVar27);
                    uVar27 = FUN_180023fe0(*plVar1,uVar17);
                    fVar29 = (float)FUN_18000a1f0(0,uVar5,uVar27);
                    cVar11 = (fVar28 < fVar6) * '\x04' + 'a';
                    if (fVar28 < fVar7) {
                      cVar11 = 'c';
                    }
                    bVar26 = _DAT_1802f06b0 == 1;
                    if (bVar26) {
                      fVar28 = fVar28 * fVar8;
                      fVar29 = fVar29 * fVar8;
                    }
                    dVar31 = (double)fVar28;
                    cVar11 = FUN_18000dca0(&uStack_118,&UNK_1801537e7,cVar11,bVar26,dVar31);
                    plVar19 = plStack_f0;
                    if ((cVar11 == '\0') ||
                       (((0.0 < fVar29 &&
                         (cVar11 = FUN_18000dca0(&uStack_118,&UNK_1801537f0,bVar26,(double)fVar29,
                                                 dVar31), plVar19 = plStack_f0, cVar11 == '\0')) ||
                        (cVar11 = FUN_18000dc40(&uStack_118,&UNK_1801537f9), plVar19 = plStack_f0,
                        cVar11 == '\0')))) goto LAB_18003cf91;
                  }
                  if (DAT_1802f0628 == '\x01') {
                    cVar11 = FUN_18000dc40(&uStack_118,lVar16);
                    plVar19 = plStack_f0;
                    if (cVar11 != '\0') goto LAB_18003cee9;
                  }
                  else {
                    puVar22 = &UNK_180153801;
                    cVar11 = FUN_18000dc40(&uStack_118,&UNK_180153801);
                    plVar19 = plStack_f0;
                    if ((cVar11 != '\0') &&
                       (cVar11 = FUN_18000dd10(&uStack_118,
                                               CONCAT71((int7)((ulonglong)puVar22 >> 8),
                                                        ((uVar14 & 5) == 0) * '\x02') | 0x61),
                       plVar19 = plStack_f0, cVar11 != '\0')) {
                      if (0 < (int)lStack_130) {
                        iVar13 = 0;
                        do {
                          if (*(char *)(lVar16 + iVar13) == -0x3e) {
                            iVar13 = iVar13 + 2;
                          }
                          else {
                            cVar11 = FUN_18000dd10(&uStack_118);
                            plVar19 = plStack_f0;
                            if (cVar11 == '\0') goto LAB_18003cf91;
                          }
                          iVar13 = iVar13 + 1;
                        } while (iVar13 < (int)lStack_120);
                      }
LAB_18003cee9:
                      if ((DAT_1802f0668 == '\x01') &&
                         (cVar11 = (**(code **)(**(longlong **)(*plVar1 + 8) + 0xc0))
                                             (*(longlong **)(*plVar1 + 8),plVar1[5],uStack_f8),
                         plVar19 = plStack_f0, cVar11 == '\0')) {
                        if (dVar30 < 0.0) {
                          dVar31 = (double)func_0x0001800af2f0(SUB84(dVar30,0));
                        }
                        else {
                          dVar31 = SQRT(dVar30);
                        }
                        cVar11 = ((float)dVar31 < _DAT_180153730) * '\x04' + 'a';
                        if ((float)dVar31 < fVar9) {
                          cVar11 = 'c';
                        }
                        cVar11 = FUN_18000dca0(&uStack_118,&UNK_180153804,cVar11,dVar31);
                        plVar19 = plStack_f0;
                        if (cVar11 == '\0') goto LAB_18003cf91;
                      }
                      (**(code **)(*plVar3 + 0x550))(plVar3,plVar19,lVar16);
                      cVar11 = FUN_18000dd40(&uStack_118);
                      plVar19 = plStack_f0;
                      if (cVar11 != '\0') {
                        plVar19 = (longlong *)(**(code **)(*plVar3 + 0x538))(plVar3,0x1803007b0);
                      }
                    }
                  }
                }
LAB_18003cf91:
                if ((plVar19 == (longlong *)0x0) ||
                   (lVar16 = (**(code **)(*plVar3 + 0xa8))(plVar3,plVar19), uVar17 = uStack_f8,
                   lVar16 == 0)) break;
                lVar20 = (**(code **)(*plStack_180 + 0xa8))(plStack_180,uStack_f8);
                if (lVar20 == 0) {
                  (**(code **)(*plStack_180 + 0xb0))(plStack_180,lVar16);
                  break;
                }
                FUN_1800230d0(&uStack_118,*plVar1,uVar17);
                cVar11 = FUN_180023020(*plVar1);
                if ((cVar10 != '\0') && (cVar11 != '\0')) {
                  uStack_188 = uStack_168;
                  uStack_198 = (undefined4)uStack_178;
                  uStack_194 = uStack_178._4_4_;
                  uStack_190 = (undefined4)uStack_170;
                  uStack_18c = uStack_170._4_4_;
                  FUN_1800095c0(&uStack_158,&uStack_198);
                  uStack_178 = uStack_158;
                  uStack_170 = uStack_150;
                  uStack_168 = uStack_148;
                  uStack_188 = uStack_108;
                  uStack_198 = (undefined4)uStack_118;
                  uStack_194 = uStack_118._4_4_;
                  uStack_190 = (undefined4)uStack_110;
                  uStack_18c = uStack_110._4_4_;
                  FUN_1800095c0(&uStack_158,&uStack_198);
                  uStack_118 = uStack_158;
                  uStack_110 = uStack_150;
                  uStack_108 = uStack_148;
                }
                lVar23 = _DAT_1802fc910 * 0xa0;
                _DAT_1802fc910 = _DAT_1802fc910 + 1;
                *(undefined8 *)(lVar23 + 0x1802fc948) = uStack_168;
                *(undefined8 *)(lVar23 + 0x1802fc938) = uStack_178;
                *(undefined8 *)(lVar23 + 0x1802fc940) = uStack_170;
                *(undefined8 *)(lVar23 + 0x1802fc930) = uStack_108;
                *(undefined8 *)(lVar23 + 0x1802fc920) = uStack_118;
                *(undefined8 *)(lVar23 + 0x1802fc928) = uStack_110;
                *(longlong *)(lVar23 + 0x1802fc950) = lVar20;
                if ((float)dVar30 < 0.0) {
                  fVar28 = (float)func_0x0001800af4a0();
                }
                else {
                  fVar28 = SQRT((float)dVar30);
                }
                uVar17 = uStack_f8;
                *(float *)(lVar23 + 0x1802fc968) = fVar28;
                uStack_148 = uStack_1c8;
                uStack_158 = uStack_1d8;
                uStack_150 = uStack_1d0;
                uStack_188 = *(undefined8 *)(lVar23 + 0x1802fc930);
                uStack_198 = *(undefined4 *)(lVar23 + 0x1802fc920);
                uStack_194 = *(undefined4 *)(lVar23 + 0x1802fc924);
                uStack_190 = *(undefined4 *)(lVar23 + 0x1802fc928);
                uStack_18c = *(undefined4 *)(lVar23 + 0x1802fc92c);
                dVar30 = (double)FUN_1800094f0(&uStack_158,&uStack_198);
                *(float *)(lVar23 + 0x1802fc964) = (float)dVar30;
                *(longlong *)(lVar23 + 0x1802fc958) = lVar16;
                uVar27 = FUN_180027560(*plVar1,lStack_1a8,lVar16);
                *(undefined4 *)(lVar23 + 0x1802fc960) = uVar27;
                *(undefined4 *)(lVar23 + 0x1802fc96c) = 0;
                lVar16 = FUN_180024050(*plVar1,uVar17,0);
                if (lVar16 != 0) {
                  *(int *)(lVar23 + 0x1802fc96c) = *(int *)(lVar23 + 0x1802fc96c) + 1;
                }
                lStack_130 = lVar23 + 0x1802fc970;
                *(bool *)lStack_130 = lVar16 != 0;
                lVar16 = FUN_180024050(*plVar1,uVar17,1);
                if (lVar16 != 0) {
                  *(int *)(lVar23 + 0x1802fc96c) = *(int *)(lVar23 + 0x1802fc96c) + 1;
                }
                *(bool *)(lVar23 + 0x1802fc980) = lVar16 != 0;
                lVar16 = FUN_180024050(*plVar1,uVar17,2);
                if (lVar16 != 0) {
                  *(int *)(lVar23 + 0x1802fc96c) = *(int *)(lVar23 + 0x1802fc96c) + 1;
                }
                *(bool *)(lVar23 + 0x1802fc990) = lVar16 != 0;
                lVar16 = FUN_180024050(*plVar1,uVar17,3);
                if (lVar16 != 0) {
                  *(int *)(lVar23 + 0x1802fc96c) = *(int *)(lVar23 + 0x1802fc96c) + 1;
                }
                *(bool *)(lVar23 + 0x1802fc9a0) = lVar16 != 0;
                lVar16 = FUN_180024050(*plVar1,uVar17,4);
                if (lVar16 != 0) {
                  *(int *)(lVar23 + 0x1802fc96c) = *(int *)(lVar23 + 0x1802fc96c) + 1;
                }
                *(bool *)(lVar23 + 0x1802fc9b0) = lVar16 != 0;
                if (DAT_1802f05b0 == '\x01') {
                  plStack_f0 = *(longlong **)(*plVar1 + 8);
                  lStack_120 = 0;
                  do {
                    lVar20 = lStack_120 * 0x10;
                    *(undefined8 *)(lStack_130 + 8 + lVar20) = 0;
                    *(undefined4 *)(lStack_130 + 4 + lVar20) = 0;
                    lVar16 = FUN_180024050(*plVar1,uStack_f8);
                    if ((lVar16 != 0) && (lVar16 = FUN_180025de0(*plVar1,lVar16), lVar16 != 0)) {
                      uStack_134 = FUN_180027f10(*plVar1,lVar16);
                      uStack_124 = 0x19;
                      if ((int)uStack_134 < 0x19) {
                        uStack_124 = uStack_134;
                      }
                      if (0 < (int)uStack_134) {
                        uVar24 = (ulonglong)uStack_124;
                        uVar25 = 0;
                        do {
                          uVar17 = FUN_180027f40(*plVar1,lVar16,uVar25 & 0xffffffff);
                          uVar14 = FUN_180027f70(*plVar1,uVar17,lStack_1c0);
                          if (((ushort)uVar14 < 0x3f) &&
                             ((0x1ff0fff0ffc0fe00U >> ((ulonglong)(uVar14 & 0xffff) & 0x3f) & 1) ==
                              0)) {
                            sVar12 = FUN_180027f70(*plVar1,uVar17,lStack_1b8);
                            if (sVar12 < 1) {
                              sVar12 = 0;
                            }
                            if (0x62 < sVar12) {
                              sVar12 = 99;
                            }
                            *(ushort *)(uVar25 * 4 + 0x180300830) = (ushort)uVar14;
                            *(short *)(uVar25 * 4 + 0x180300832) = sVar12;
                          }
                          uVar25 = uVar25 + 1;
                        } while (uVar24 != uVar25);
                      }
                      lVar20 = lVar20 + lStack_130;
                      func_0x00018013d0f0(0x180300830,(longlong)(int)uStack_124,4,FUN_18003da60);
                      uVar14 = uStack_134;
                      uVar25 = 4;
                      if ((int)uStack_134 < 4) {
                        uVar25 = (ulonglong)uStack_134;
                      }
                      lVar16 = func_0x00018013cf60((longlong)(int)uVar25,8);
                      *(longlong *)(lVar20 + 8) = lVar16;
                      if (lVar16 == 0) break;
                      if (0 < (int)uVar14) {
                        uVar24 = 0;
                        do {
                          uVar21 = (ulonglong)*(ushort *)(uVar24 * 4 + 0x180300830);
                          if (uVar21 < 0x3f) {
                            uVar17 = *(undefined8 *)(&UNK_180153870 + uVar21 * 8);
                          }
                          else {
                            uVar17 = 0;
                          }
                          FUN_1800ab710(0x180300894,6,&UNK_180153864,uVar17,
                                        (int)*(short *)(uVar24 * 4 + 0x180300832));
                          lVar16 = (**(code **)(*plStack_f0 + 0x538))(plStack_f0,0x180300894);
                          if ((lVar16 == 0) ||
                             (lVar16 = (**(code **)(*plStack_f0 + 0xa8))(plStack_f0,lVar16),
                             lVar16 == 0)) goto LAB_18003cbed;
                          *(longlong *)(*(longlong *)(lVar20 + 8) + uVar24 * 8) = lVar16;
                          *(int *)(lVar20 + 4) = *(int *)(lVar20 + 4) + 1;
                          uVar24 = uVar24 + 1;
                        } while (uVar25 != uVar24);
                      }
                    }
                    lStack_120 = lStack_120 + 1;
                  } while (lStack_120 != 5);
                }
LAB_18003cbed:
                uVar17 = uStack_1a0;
                uVar25 = uStack_1b0;
                if (_DAT_1802fc910 == 100) break;
              }
            }
          }
          else if (DAT_1802f0608 == '\x01') {
            uVar18 = FUN_180022cf0(*plVar1,plVar1[3]);
            iVar13 = FUN_180025310(*plVar1,uVar18);
            if (iVar13 != 0) goto LAB_18003cc7e;
          }
          uVar14 = (int)uVar25 + 1;
          uVar25 = (ulonglong)uVar14;
          iVar13 = FUN_180024e50(*plVar1,uVar17);
        } while ((int)uVar14 < iVar13);
      }
      func_0x00018013d0f0(0x1802fc920,_DAT_1802fc910,0xa0,FUN_18003da40);
    }
  }
  return;
}

// UI RVA 0x3d5b0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3d5b0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003d5b0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180153bbc);
  FUN_18000cf30(param_2,param_1,0x1802f05b8);
  FUN_18000cf30(param_2,param_1,0x1802f04e0);
  FUN_18000cef0(param_2,param_1,0x1802f05f0);
  FUN_18000cef0(param_2,param_1,0x1802f0610);
  FUN_18000cef0(param_2,param_1,0x1802f0518);
  FUN_18000cef0(param_2,param_1,0x1802f0538);
  FUN_18000cef0(param_2,param_1,0x1802f0558);
  FUN_180013e90(param_1,param_2,&UNK_180153bc1);
  FUN_18000cef0(param_2,param_1,0x1802f0630);
  if (DAT_1802f0648 == '\x01') {
    FUN_18000d040(param_2,param_1,0x1802f0680);
  }
  FUN_18000cef0(param_2,param_1,0x1802f0650);
  FUN_18000cef0(param_2,param_1,0x1802f0578);
  if (DAT_1802f0590 == '\x01') {
    cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802f05a8,0x1802f0598,&DAT_1802f05b0);
    if (cVar1 != '\0') {
      DAT_1802f7338 = 1;
      return;
    }
    return;
  }
  return;
}

// SETTINGS RVA 0x3d6e0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3d6e0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003d6e0(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c450(param_1,&UNK_180153bcc,0x1802f05b8);
  FUN_18000c450(param_1,&UNK_180153bd2,0x1802f04e0);
  FUN_18000c3b0(param_1,&UNK_180153bd8,0x1802f05f0);
  FUN_18000c3b0(param_1,&UNK_180153bea,0x1802f0610);
  FUN_18000c3b0(param_1,&UNK_180153bfb,0x1802f0518);
  FUN_18000c3b0(param_1,&UNK_180153c0c,0x1802f0538);
  FUN_18000c3b0(param_1,&UNK_180153c17,0x1802f0558);
  FUN_18000c3b0(param_1,&UNK_180153c23,0x1802f0630);
  FUN_18000c6f0(param_1,&UNK_180153c2f,0x1802f0680);
  FUN_18000c3b0(param_1,&UNK_180153c3a,0x1802f0650);
  FUN_18000c3b0(param_1,&UNK_180153c48,0x1802f0578);
  uVar1 = uRam00000001802f05b1;
  uVar2 = DAT_1802f05b0;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180153c57,DAT_1802f05b0);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802f05b0;
      break;
    case 2:
      uRam00000001802f05b1 = DAT_1802f05b0;
      break;
    case 3:
      uVar2 = uRam00000001802f05b1;
    }
  }
  DAT_1802f05b0 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x3d800; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3d800; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003d800(longlong param_1)

{
  longlong *plVar1;
  ulonglong uVar2;
  longlong lVar3;
  longlong lVar4;
  
  if (_DAT_1802fc910 != 0) {
    plVar1 = *(longlong **)(param_1 + 8);
    uVar2 = 0;
    do {
      lVar3 = uVar2 * 0xa0;
      if (*(longlong *)(lVar3 + 0x1802fc958) != 0) {
        (**(code **)(*plVar1 + 0xb0))(plVar1);
      }
      if (*(longlong *)(lVar3 + 0x1802fc950) != 0) {
        (**(code **)(*plVar1 + 0xb0))(plVar1);
      }
      lVar4 = *(longlong *)(lVar3 + 0x1802fc978);
      if (lVar4 != 0) {
        if (0 < *(int *)(lVar3 + 0x1802fc974)) {
          lVar4 = 0;
          do {
            (**(code **)(*plVar1 + 0xb0))
                      (plVar1,*(undefined8 *)(*(longlong *)(lVar3 + 0x1802fc978) + lVar4 * 8));
            lVar4 = lVar4 + 1;
          } while (lVar4 < *(int *)(lVar3 + 0x1802fc974));
          lVar4 = *(longlong *)(lVar3 + 0x1802fc978);
        }
        func_0x00018013cf70(lVar4);
        *(undefined8 *)(lVar3 + 0x1802fc978) = 0;
      }
      lVar4 = *(longlong *)(lVar3 + 0x1802fc988);
      if (lVar4 != 0) {
        if (0 < *(int *)(lVar3 + 0x1802fc984)) {
          lVar4 = 0;
          do {
            (**(code **)(*plVar1 + 0xb0))
                      (plVar1,*(undefined8 *)(*(longlong *)(lVar3 + 0x1802fc988) + lVar4 * 8));
            lVar4 = lVar4 + 1;
          } while (lVar4 < *(int *)(lVar3 + 0x1802fc984));
          lVar4 = *(longlong *)(lVar3 + 0x1802fc988);
        }
        func_0x00018013cf70(lVar4);
        *(undefined8 *)(lVar3 + 0x1802fc988) = 0;
      }
      lVar4 = *(longlong *)(lVar3 + 0x1802fc998);
      if (lVar4 != 0) {
        if (0 < *(int *)(lVar3 + 0x1802fc994)) {
          lVar4 = 0;
          do {
            (**(code **)(*plVar1 + 0xb0))
                      (plVar1,*(undefined8 *)(*(longlong *)(lVar3 + 0x1802fc998) + lVar4 * 8));
            lVar4 = lVar4 + 1;
          } while (lVar4 < *(int *)(lVar3 + 0x1802fc994));
          lVar4 = *(longlong *)(lVar3 + 0x1802fc998);
        }
        func_0x00018013cf70(lVar4);
        *(undefined8 *)(lVar3 + 0x1802fc998) = 0;
      }
      lVar4 = *(longlong *)(lVar3 + 0x1802fc9a8);
      if (lVar4 != 0) {
        if (0 < *(int *)(lVar3 + 0x1802fc9a4)) {
          lVar4 = 0;
          do {
            (**(code **)(*plVar1 + 0xb0))
                      (plVar1,*(undefined8 *)(*(longlong *)(lVar3 + 0x1802fc9a8) + lVar4 * 8));
            lVar4 = lVar4 + 1;
          } while (lVar4 < *(int *)(lVar3 + 0x1802fc9a4));
          lVar4 = *(longlong *)(lVar3 + 0x1802fc9a8);
        }
        func_0x00018013cf70(lVar4);
        *(undefined8 *)(lVar3 + 0x1802fc9a8) = 0;
      }
      lVar4 = *(longlong *)(lVar3 + 0x1802fc9b8);
      if (lVar4 != 0) {
        if (0 < *(int *)(lVar3 + 0x1802fc9b4)) {
          lVar4 = 0;
          do {
            (**(code **)(*plVar1 + 0xb0))
                      (plVar1,*(undefined8 *)(*(longlong *)(lVar3 + 0x1802fc9b8) + lVar4 * 8));
            lVar4 = lVar4 + 1;
          } while (lVar4 < *(int *)(lVar3 + 0x1802fc9b4));
          lVar4 = *(longlong *)(lVar3 + 0x1802fc9b8);
        }
        func_0x00018013cf70(lVar4);
        *(undefined8 *)(lVar3 + 0x1802fc9b8) = 0;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < _DAT_1802fc910);
  }
  _DAT_1802fc910 = 0;
  return;
}

// CANDIDATE_LOCAL RVA 0x3da40; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3da40; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


int FUN_18003da40(longlong param_1,longlong param_2)

{
  return (int)(*(float *)(param_2 + 0x48) - *(float *)(param_1 + 0x48));
}

// CANDIDATE_LOCAL RVA 0x3da60; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3da60; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


int FUN_18003da60(short *param_1,short *param_2)

{
  return *(int *)(&UNK_180153ac0 + (longlong)*param_1 * 4) -
         *(int *)(&UNK_180153ac0 + (longlong)*param_2 * 4);
}

