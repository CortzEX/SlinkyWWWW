// Recovered decompiler view: Player ESP
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x2eb20, 0x2fbc0); proximity does not prove ownership.

// CALLBACK RVA 0x2eb20; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/player_esp_render_3d/player_esp_render_3d.c
// Differential report: analysis/module_behavior_recovery/player_esp_render_3d/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2eb20; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002eb20(longlong param_1)

{
  float fVar1;
  uint uVar2;
  uint uVar3;
  undefined8 *puVar4;
  double dVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined8 *puVar8;
  undefined8 uVar9;
  undefined8 *puVar10;
  ulonglong uVar11;
  uint uVar12;
  float fVar13;
  undefined4 uVar14;
  ulonglong uVar15;
  ulonglong uVar16;
  double dVar17;
  float fVar18;
  undefined4 uStack_168;
  undefined4 uStack_164;
  undefined4 uStack_160;
  undefined4 uStack_15c;
  undefined8 uStack_158;
  undefined8 uStack_148;
  undefined8 uStack_140;
  double dStack_138;
  undefined8 uStack_128;
  undefined8 uStack_120;
  double dStack_118;
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  double dStack_f8;
  
  if ((_DAT_1802f7e10 != 0) && (_DAT_1802ea110 == 1)) {
    (*(code *)*_DAT_18013e458)(0xbe2);
    (*(code *)*_DAT_180150cb0)(_DAT_1802ea0c0);
    fVar1 = *(float *)(param_1 + 0x28);
    puVar4 = *(undefined8 **)(param_1 + 0x20);
    uVar9 = FUN_180022d40(*puVar4,puVar4[3]);
    uVar12 = FUN_180027250(*puVar4,uVar9);
    puVar8 = _DAT_180150cd0;
    puVar4 = _DAT_180150cb8;
    uVar7 = _DAT_1801509ec;
    uVar6 = _DAT_1801509e8;
    dVar5 = _DAT_1801509e0;
    if (_DAT_1802f7e10 != 0) {
      uVar12 = uVar12 ^ _DAT_1801509d0;
      puVar10 = (undefined8 *)0x1802f7e20;
      uVar11 = 0;
      do {
        dStack_138 = (double)puVar10[2];
        uStack_148 = *puVar10;
        uStack_140 = puVar10[1];
        dStack_118 = (double)puVar10[5];
        uStack_128 = puVar10[3];
        uStack_120 = puVar10[4];
        FUN_180009460(&uStack_108,&uStack_148,&uStack_128,SUB84((double)fVar1,0));
        dStack_118 = dStack_f8;
        uStack_128 = CONCAT44(uStack_104,uStack_108);
        uStack_120 = CONCAT44(uStack_fc,uStack_100);
        uStack_158 = *(undefined8 *)(param_1 + 0x18);
        uStack_168 = *(undefined4 *)(param_1 + 8);
        uStack_164 = *(undefined4 *)(param_1 + 0xc);
        uStack_160 = *(undefined4 *)(param_1 + 0x10);
        uStack_15c = *(undefined4 *)(param_1 + 0x14);
        FUN_1800093d0(&uStack_148,&uStack_128,&uStack_168);
        uStack_108 = (undefined4)uStack_148;
        uStack_104 = uStack_148._4_4_;
        uStack_100 = (undefined4)uStack_140;
        uStack_fc = uStack_140._4_4_;
        dStack_f8 = dStack_138;
        (*(code *)*_DAT_180150cc0)();
        dVar17 = (double)CONCAT44(uStack_fc,uStack_100) + dVar5;
        (*(code *)*_DAT_180150cd8)
                  ((float)(double)CONCAT44(uStack_104,uStack_108),
                   CONCAT44((int)((ulonglong)dVar17 >> 0x20),(float)dVar17),(float)dStack_f8);
        (*(code *)*puVar8)(uVar7,uVar6,uVar7);
        if ((DAT_1802ea138 != '\0') || (*(char *)((longlong)puVar10 + 0x4c) == '\x01')) {
          FUN_1800293c0();
          uVar14 = *(undefined4 *)(puVar10 + 6);
          uVar2 = *(uint *)((longlong)puVar10 + 0x34);
          uVar3 = *(uint *)(puVar10 + 7);
          uVar15 = (ulonglong)uVar2;
          uVar16 = (ulonglong)uVar3;
          if ((0 < *(int *)(puVar10 + 8)) &&
             (uVar15 = (ulonglong)uVar2, uVar16 = (ulonglong)uVar3, DAT_1802ea158 != '\0')) {
            fVar13 = (float)*(int *)(puVar10 + 8) - fVar1;
            fVar18 = _DAT_1801509f0;
            if (fVar13 <= _DAT_1801509f0) {
              fVar18 = fVar13;
            }
            fVar18 = fVar18 * _DAT_1801509f4;
            uVar14 = FUN_18000a2b0(uVar14,uVar6,fVar18);
            uVar15 = FUN_18000a2b0(uVar2,0,fVar18);
            uVar16 = FUN_18000a2b0(uVar3,0,fVar18);
          }
          if (DAT_1802ea178 == '\x01') {
            (*(code *)*_DAT_18013e448)(uVar14,uVar15,uVar16,_DAT_1801509f8);
            FUN_180029400();
          }
          (*(code *)*_DAT_180150ca0)(uVar14,uVar15,uVar16);
          FUN_180029430();
          FUN_1800295a0();
        }
        if (DAT_1802ea198 == '\x01') {
          (*(code *)*_DAT_180150cc8)(uVar12,0,uVar6,0);
          (*(code *)*_DAT_18013e448)(0,uVar6,0,_DAT_1801509fc);
          FUN_18002fa30(puVar10,_DAT_180150a00,uVar6,_DAT_180150a04);
        }
        (*(code *)*puVar4)();
        uVar11 = uVar11 + 1;
        puVar10 = puVar10 + 10;
      } while (uVar11 < _DAT_1802f7e10);
    }
  }
  return;
}

// CALLBACK RVA 0x2eea0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/player_esp_render_2d/player_esp_render_2d.c
// Differential report: analysis/module_behavior_recovery/player_esp_render_2d/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2eea0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002eea0(longlong param_1)

{
  double dVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  longlong lVar4;
  undefined8 *puVar5;
  float fVar6;
  float fVar7;
  char cVar8;
  longlong lVar9;
  longlong lVar10;
  float fVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  undefined1 auStack_1d0 [24];
  undefined4 uStack_1b8;
  undefined4 uStack_1b4;
  undefined4 uStack_1b0;
  undefined4 uStack_1ac;
  undefined8 uStack_1a8;
  undefined8 uStack_198;
  undefined8 uStack_190;
  undefined8 uStack_188;
  undefined4 uStack_178;
  undefined4 uStack_174;
  undefined4 uStack_170;
  undefined4 uStack_16c;
  undefined8 uStack_168;
  ulonglong uStack_158;
  longlong lStack_150;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  float fStack_130;
  float fStack_12c;
  undefined8 *puStack_128;
  longlong lStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  float fStack_f4;
  float fStack_f0;
  float fStack_ec;
  
  if ((_DAT_1802f7e10 != 0) && (_DAT_1802ea110 == 0)) {
    lStack_120 = param_1;
    (*(code *)*_DAT_18013e458)(0xbe2);
    (*(code *)*_DAT_180150cb0)(_DAT_1802ea0c0);
    uVar3 = _UNK_180150aa8;
    uVar2 = _DAT_180150aa0;
    if (_DAT_1802f7e10 != 0) {
      puStack_128 = (undefined8 *)(lStack_120 + 8);
      fStack_f4 = *(float *)(lStack_120 + 0x40);
      dVar1 = (double)fStack_f4;
      uStack_158 = 0;
      do {
        lStack_150 = uStack_158 * 0x50;
        uStack_188 = *(undefined8 *)(lStack_150 + 0x1802f7e30);
        uStack_198 = *(undefined8 *)(lStack_150 + 0x1802f7e20);
        uStack_190 = *(undefined8 *)(lStack_150 + 0x1802f7e28);
        uStack_108 = *(undefined8 *)(lStack_150 + 0x1802f7e48);
        uStack_118 = *(undefined8 *)(lStack_150 + 0x1802f7e38);
        uStack_110 = *(undefined8 *)(lStack_150 + 0x1802f7e40);
        FUN_180009460(&uStack_178,&uStack_198,&uStack_118,SUB84(dVar1,0));
        puVar5 = puStack_128;
        uStack_108 = uStack_168;
        uStack_118 = CONCAT44(uStack_174,uStack_178);
        uStack_110 = CONCAT44(uStack_16c,uStack_170);
        uStack_138 = puStack_128[2];
        uStack_148 = *puStack_128;
        uStack_140 = puStack_128[1];
        FUN_1800093d0(&uStack_198,&uStack_118,&uStack_148);
        uStack_168 = uStack_188;
        uStack_178 = (undefined4)uStack_198;
        uStack_174 = uStack_198._4_4_;
        uStack_170 = (undefined4)uStack_190;
        uStack_16c = uStack_190._4_4_;
        uStack_1a8 = uStack_188;
        uStack_1b8 = (undefined4)uStack_198;
        uStack_1b4 = uStack_198._4_4_;
        uStack_1b0 = (undefined4)uStack_190;
        uStack_1ac = uStack_190._4_4_;
        uStack_108 = uStack_188;
        uStack_118 = uStack_198;
        uStack_110 = uStack_190;
        uStack_138 = 0xbfd999999999999a;
        uStack_148 = uVar2;
        uStack_140 = uVar3;
        FUN_180009400(&uStack_198,&uStack_118,&uStack_148);
        cVar8 = FUN_1800295c0(puVar5,&uStack_198,&fStack_f0);
        puVar5 = puStack_128;
        lVar4 = lStack_150;
        if (cVar8 != '\0') {
          lVar9 = lStack_150 + 0x1802f7e20;
          lVar10 = 0x18;
          fVar16 = fStack_ec;
          fVar17 = fStack_f0;
          do {
            uStack_108 = uStack_1a8;
            uStack_118 = CONCAT44(uStack_1b4,uStack_1b8);
            uStack_110 = CONCAT44(uStack_1ac,uStack_1b0);
            uStack_138 = *(undefined8 *)(&UNK_180150ab0 + lVar10);
            uStack_148 = *(undefined8 *)(&DAT_180150aa0 + lVar10);
            uStack_140 = *(undefined8 *)(&UNK_180150aa8 + lVar10);
            FUN_180009400(auStack_1d0,&uStack_118,&uStack_148);
            cVar8 = FUN_1800295c0(puVar5,auStack_1d0,&fStack_130);
            if (cVar8 == '\0') goto LAB_18002efa7;
            if (fStack_f0 <= fStack_130) {
              if (fVar17 < fStack_130) {
                fVar17 = fStack_130;
              }
            }
            else {
              fStack_f0 = fStack_130;
            }
            fVar6 = fStack_f0;
            if (fStack_12c < fStack_ec) {
              fStack_ec = fStack_12c;
            }
            else if (fVar16 < fStack_12c) {
              fVar16 = fStack_12c;
            }
            fVar7 = fStack_ec;
            lVar10 = lVar10 + 0x18;
          } while (lVar10 != 0xc0);
          if (((((0.0 <= fStack_f0) && (0.0 <= fStack_ec)) &&
               (fStack_f0 <= *(float *)(lStack_120 + 0x28))) &&
              (fStack_ec <= *(float *)(lStack_120 + 0x2c))) ||
             (((0.0 <= fVar17 && (fVar17 <= *(float *)(lStack_120 + 0x28))) &&
              ((0.0 <= fVar16 && (fVar16 <= *(float *)(lStack_120 + 0x2c))))))) {
            uVar12 = *(undefined4 *)(lVar4 + 0x1802f7e50);
            uVar13 = *(undefined4 *)(lVar4 + 0x1802f7e54);
            uVar14 = *(undefined4 *)(lVar4 + 0x1802f7e58);
            if ((0 < *(int *)(lVar4 + 0x1802f7e60)) && (DAT_1802ea158 != '\0')) {
              fVar11 = (float)*(int *)(lVar4 + 0x1802f7e60) - fStack_f4;
              fVar15 = _DAT_180150a08;
              if (fVar11 <= _DAT_180150a08) {
                fVar15 = fVar11;
              }
              fVar15 = fVar15 * _DAT_180150a0c;
              uVar12 = FUN_18000a2b0(uVar12,_DAT_180150a10,fVar15);
              uVar13 = FUN_18000a2b0(uVar13,0,fVar15);
              uVar14 = FUN_18000a2b0(uVar14,0,fVar15);
            }
            if ((DAT_1802ea138 != '\0') || (*(char *)(lVar4 + 0x1802f7e6c) == '\x01')) {
              FUN_180029460();
              (*(code *)*_DAT_180150cc0)();
              (*(code *)*_DAT_180150cd8)(fVar6,fVar7,0);
              (*(code *)*_DAT_180150cd0)(fVar17 - fVar6,fVar16 - fVar7,_DAT_180150a10);
              if (DAT_1802ea178 == '\x01') {
                (*(code *)*_DAT_18013e448)(uVar12,uVar13,uVar14,_DAT_180150a14);
                FUN_1800294a0();
              }
              (*(code *)*_DAT_180150ca0)(uVar12,uVar13);
              FUN_1800294d0();
              (*(code *)*_DAT_180150cb8)();
              FUN_1800295a0();
            }
            if (DAT_1802ea198 == '\x01') {
              FUN_18002fa30(lVar9,(fVar6 - _DAT_1802ea0c0) + _DAT_180150a18 + _DAT_180150a1c,fVar7,
                            fVar16);
            }
          }
        }
LAB_18002efa7:
        uStack_158 = uStack_158 + 1;
      } while (uStack_158 < _DAT_1802f7e10);
    }
  }
  return;
}

// CALLBACK RVA 0x2f3f0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/player_esp_update/player_esp_update.c
// Differential report: analysis/module_behavior_recovery/player_esp_update/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2f3f0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002f3f0(longlong param_1)

{
  longlong *plVar1;
  longlong *plVar2;
  longlong lVar3;
  undefined4 uVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined1 uVar13;
  uint uVar14;
  longlong lVar15;
  float fVar16;
  float fVar17;
  double dVar18;
  undefined4 uVar19;
  float fVar20;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined8 uStack_f0;
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  undefined4 uStack_e0;
  undefined4 uStack_dc;
  undefined8 uStack_d8;
  code *pcStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  uint uStack_ac;
  undefined8 uStack_a8;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined8 uStack_98;
  
  plVar1 = *(longlong **)(param_1 + 8);
  if (plVar1[4] != 0) {
    _DAT_1802f7e10 = 0;
    FUN_180023030(&uStack_100,*plVar1,plVar1[5]);
    uVar10 = FUN_180024600(*plVar1,plVar1[4]);
    uVar14 = (uint)DAT_1802ea250;
    iVar6 = FUN_180024e50(*plVar1,uVar10);
    uVar4 = _DAT_180150a20;
    if (0 < iVar6) {
      uVar14 = uVar14 * 5 + 2;
      iVar6 = 0;
      uStack_ac = uVar14;
      do {
        uVar11 = FUN_180024e80(*plVar1,uVar10,iVar6);
        cVar5 = (**(code **)(**(longlong **)(*plVar1 + 8) + 0xc0))
                          (*(longlong **)(*plVar1 + 8),plVar1[5],uVar11);
        if (((cVar5 == '\0') && (uVar8 = FUN_18002acb0(*plVar1,uVar11), (uVar8 & uVar14) == 0)) &&
           (cVar5 = FUN_1800237b0(*plVar1,uVar11), cVar5 == '\0')) {
          FUN_180023030(&uStack_e8,*plVar1,uVar11);
          uStack_b8 = uStack_d8;
          uStack_c8 = CONCAT44(uStack_e4,uStack_e8);
          uStack_c0 = CONCAT44(uStack_dc,uStack_e0);
          uStack_98 = uStack_f0;
          uStack_a8 = CONCAT44(uStack_fc,uStack_100);
          uStack_a0 = uStack_f8;
          uStack_9c = uStack_f4;
          dVar18 = (double)FUN_1800094b0(&uStack_c8,&uStack_a8);
          if (dVar18 <= (double)(_DAT_1802ea1d0 * _DAT_1802ea1d0)) {
            if (DAT_1802ea270 == '\x01') {
              plVar2 = *(longlong **)(*plVar1 + 8);
              pcStack_d0 = *(code **)(*plVar2 + 0xc0);
              uVar12 = FUN_18002b1c0();
              cVar5 = (*pcStack_d0)(plVar2,uVar11,uVar12);
              if (cVar5 == '\0') goto LAB_18002f5bd;
              uStack_a0 = _DAT_1802ea1e8;
              uStack_a8 = _DAT_1802ea1e0;
              uVar13 = 1;
            }
            else {
LAB_18002f5bd:
              if (_DAT_1802ea2c0 == 0) {
                uVar9 = FUN_180028e10(*plVar1,uVar11);
                FUN_1800290d0(&uStack_a8,uVar9);
              }
              else if ((uVar8 & 5) == 0) {
                uStack_a0 = _DAT_1802ea228;
                uStack_a8 = _DAT_1802ea220;
              }
              else {
                uStack_a0 = _DAT_1802ea208;
                uStack_a8 = _DAT_1802ea200;
              }
              uVar13 = 0;
            }
            lVar15 = _DAT_1802f7e10 * 0x50;
            _DAT_1802f7e10 = _DAT_1802f7e10 + 1;
            *(undefined8 *)(lVar15 + 0x1802f7e48) = uStack_d8;
            *(undefined4 *)(lVar15 + 0x1802f7e38) = uStack_e8;
            *(undefined4 *)(lVar15 + 0x1802f7e3c) = uStack_e4;
            *(undefined4 *)(lVar15 + 0x1802f7e40) = uStack_e0;
            *(undefined4 *)(lVar15 + 0x1802f7e44) = uStack_dc;
            FUN_1800230d0(&uStack_c8,*plVar1,uVar11);
            *(undefined8 *)(lVar15 + 0x1802f7e30) = uStack_b8;
            *(undefined8 *)(lVar15 + 0x1802f7e20) = uStack_c8;
            *(undefined8 *)(lVar15 + 0x1802f7e28) = uStack_c0;
            *(undefined4 *)(lVar15 + 0x1802f7e58) = uStack_a0;
            *(undefined8 *)(lVar15 + 0x1802f7e50) = uStack_a8;
            *(float *)(lVar15 + 0x1802f7e5c) = (float)dVar18;
            uVar9 = FUN_1800239f0(*plVar1,uVar11);
            *(undefined4 *)(lVar15 + 0x1802f7e60) = uVar9;
            *(undefined1 *)(lVar15 + 0x1802f7e6c) = uVar13;
            lVar3 = *plVar1;
            fVar16 = (float)FUN_180023a40(lVar3,uVar11);
            fVar17 = (float)FUN_180023fe0(lVar3,uVar11);
            uVar9 = 0;
            fVar20 = 0.0;
            if (0.0 <= fVar17) {
              fVar20 = fVar17;
            }
            fVar17 = (float)FUN_180023a80(lVar3,uVar11);
            fVar17 = fVar17 + fVar20;
            uVar19 = 0;
            if ((fVar17 != 0.0) || (NAN(fVar17))) {
              uVar19 = FUN_18000a1f0(0,uVar4,(fVar16 + fVar20) / fVar17);
            }
            *(undefined4 *)(lVar15 + 0x1802f7e64) = uVar19;
            if ((fVar16 != 0.0) || (NAN(fVar16))) {
              uVar9 = FUN_18000a1f0(0,uVar4,fVar20 / fVar16);
            }
            *(undefined4 *)(lVar15 + 0x1802f7e68) = uVar9;
            uVar14 = uStack_ac;
            if (_DAT_1802f7e10 == 100) break;
          }
        }
        iVar6 = iVar6 + 1;
        iVar7 = FUN_180024e50(*plVar1,uVar10);
      } while (iVar6 < iVar7);
    }
    func_0x00018013d0f0(0x1802f7e20,_DAT_1802f7e10,0x50,FUN_18002fba0);
  }
  return;
}

// UI RVA 0x2f770; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2f770; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002f770(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180150bd9);
  FUN_18000cf30(param_2,param_1,0x1802ea1a0);
  FUN_18000cef0(param_2,param_1,0x1802ea238);
  FUN_180013e90(param_1,param_2,&UNK_180150bde);
  FUN_18000d040(param_2,param_1,0x1802ea0e0);
  FUN_18000d040(param_2,param_1,0x1802ea290);
  if (_DAT_1802ea2c0 == 1) {
    FUN_18000d0a0(param_2,param_1,0x1802ea218);
    if (DAT_1802ea250 == '\0') {
      FUN_18000d0a0(param_2,param_1,0x1802ea1f8);
    }
  }
  FUN_18000cef0(param_2,param_1,0x1802ea258);
  if (DAT_1802ea270 == '\x01') {
    FUN_18000d0a0(param_2,param_1,0x1802ea1d8);
  }
  FUN_18000cf30(param_2,param_1,0x1802ea090);
  FUN_18000cef0(param_2,param_1,0x1802ea120);
  if (DAT_1802ea138 == '\x01') {
    FUN_18000cef0(param_2,param_1,0x1802ea160);
    FUN_18000cef0(param_2,param_1,0x1802ea140);
  }
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802ea190,0x1802ea180,&DAT_1802ea198);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x2f8c0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2f8c0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18002f8c0(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c6f0(param_1,&UNK_180150bec,0x1802ea0e0);
  FUN_18000c450(param_1,&UNK_180150bf1,0x1802ea1a0);
  FUN_18000c3b0(param_1,&UNK_180150bf7,0x1802ea238);
  FUN_18000c6f0(param_1,&UNK_180150c07,0x1802ea290);
  FUN_18000c7e0(param_1,&UNK_180150c12,0x1802ea218);
  FUN_18000c7e0(param_1,&UNK_180150c20,0x1802ea1f8);
  FUN_18000c3b0(param_1,&UNK_180150c31,0x1802ea258);
  FUN_18000c7e0(param_1,&UNK_180150c47,0x1802ea1d8);
  FUN_18000c450(param_1,&UNK_180150c54,0x1802ea090);
  FUN_18000c3b0(param_1,&UNK_180150c5f,0x1802ea140);
  FUN_18000c3b0(param_1,&UNK_180150c6b,0x1802ea160);
  FUN_18000c3b0(param_1,&UNK_180150c72,0x1802ea120);
  uVar1 = uRam00000001802ea199;
  uVar2 = DAT_1802ea198;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180150c7e,DAT_1802ea198);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802ea198;
      break;
    case 2:
      uRam00000001802ea199 = DAT_1802ea198;
      break;
    case 3:
      uVar2 = uRam00000001802ea199;
    }
  }
  DAT_1802ea198 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x2f9f0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2f9f0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002f9f0(undefined8 param_1)

{
  FUN_1800ab710(param_1,0x20,&UNK_180150c8e,
                *(undefined8 *)((ulonglong)_DAT_1802ea110 * 8 + 0x1802ea0d0));
  return;
}

// CANDIDATE_LOCAL RVA 0x2fa30; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2fa30; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002fa30(longlong param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  code *pcVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  
  uVar6 = FUN_18000a2b0(param_4,param_3,*(undefined4 *)(param_1 + 0x44));
  puVar3 = _DAT_180150ca0;
  (*(code *)*_DAT_180150ca0)(0,0,0);
  puVar2 = _DAT_180150c98;
  (*(code *)*_DAT_180150c98)(1);
  puVar5 = _DAT_180150ce0;
  (*(code *)*_DAT_180150ce0)(param_2,param_3);
  (*(code *)*puVar5)(param_2,uVar6);
  puVar4 = _DAT_180150ca8;
  (*(code *)*_DAT_180150ca8)();
  uVar7 = uVar6;
  if (0.0 < *(float *)(param_1 + 0x48)) {
    uVar7 = FUN_18000a2b0(uVar6,param_4);
    (*(code *)*puVar3)(_DAT_180150a24,_DAT_180150a28,0);
    (*(code *)*puVar2)(1);
    (*(code *)*puVar5)(param_2,uVar6);
    (*(code *)*puVar5)(param_2,uVar7);
    (*(code *)*puVar4)();
  }
  uVar6 = _DAT_180150a24;
  pcVar1 = (code *)*puVar3;
  uVar8 = FUN_18000a2b0(_DAT_180150a24,0,*(undefined4 *)(param_1 + 0x44));
  uVar6 = FUN_18000a2b0(0,uVar6,*(undefined4 *)(param_1 + 0x44));
  (*pcVar1)(uVar8,uVar6,0);
  (*(code *)*puVar2)(1);
  (*(code *)*puVar5)(param_2,uVar7);
  (*(code *)*puVar5)(param_2,param_4);
                    /* WARNING: Could not recover jumptable at 0x00018002fb92. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)*puVar4)();
  return;
}

// CANDIDATE_LOCAL RVA 0x2fba0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2fba0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


int FUN_18002fba0(longlong param_1,longlong param_2)

{
  return (int)(*(float *)(param_2 + 0x3c) - *(float *)(param_1 + 0x3c));
}

