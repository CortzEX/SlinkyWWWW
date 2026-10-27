// Recovered decompiler view: Timer Range
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x42c60, 0x43d80); proximity does not prove ownership.

// CALLBACK RVA 0x42c60; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/timer_range_events/timer_range_events.c
// Differential report: analysis/module_behavior_recovery/timer_range_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x42c60; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180042c60(longlong param_1)

{
  undefined8 *puVar1;
  longlong *plVar2;
  char cVar3;
  int iVar4;
  undefined8 uVar5;
  longlong lVar6;
  undefined8 uVar7;
  undefined1 auStack_b0 [8];
  double dStack_a8;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined8 uStack_88;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined8 uStack_68;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  if (_DAT_1803043d8 < 1) {
    DAT_1803043dd = 0;
    if ((((*(char *)(puVar1 + 8) == '\x01') && (lVar6 = puVar1[7], *(longlong *)(lVar6 + 8) != 0))
        && (_DAT_1801548c0 < *(double *)(lVar6 + 0x10) ||
            _DAT_1801548c0 == *(double *)(lVar6 + 0x10))) &&
       ((cVar3 = FUN_180023780(*puVar1,puVar1[5]), cVar3 != '\0' &&
        (iVar4 = FUN_1800239f0(*puVar1,*(undefined8 *)(lVar6 + 8)), iVar4 < 2)))) {
      if ((DAT_1802f3388 == '\x01') && (cVar3 = FUN_180029080(puVar1), cVar3 == '\0')) {
        return;
      }
      if ((DAT_1802f33a8 == '\x01') && (cVar3 = FUN_1800380b0(*puVar1,puVar1[5]), cVar3 == '\0')) {
        return;
      }
      if ((DAT_1802f33c8 == '\x01') && (cVar3 = FUN_180023f90(*puVar1,puVar1[5]), cVar3 != '\0')) {
        return;
      }
      FUN_180023550(auStack_b0,*puVar1,puVar1[5]);
      if (dStack_a8 <= 0.0) {
        uVar5 = FUN_180022cf0(*puVar1,puVar1[3]);
        uVar7 = FUN_180025080(*puVar1,uVar5);
        cVar3 = FUN_180025430(*puVar1,uVar7);
        if (cVar3 == '\0') {
          FUN_180023030(&uStack_78,*puVar1,puVar1[5]);
          cVar3 = FUN_180023020(*puVar1);
          if (cVar3 == '\0') {
            uStack_48 = uStack_68;
            uStack_58 = CONCAT44(uStack_74,uStack_78);
            uStack_50 = CONCAT44(uStack_6c,uStack_70);
            FUN_180009590(&uStack_38,&uStack_58);
            uStack_78 = (undefined4)uStack_38;
            uStack_74 = uStack_38._4_4_;
            uStack_70 = (undefined4)uStack_30;
            uStack_6c = uStack_30._4_4_;
            uStack_68 = uStack_28;
          }
          FUN_180024160(&uStack_38,*puVar1,*(undefined8 *)(lVar6 + 8));
          cVar3 = FUN_180023020(*puVar1);
          if (cVar3 == '\0') {
            uStack_88 = uStack_28;
            uStack_98 = (undefined4)uStack_38;
            uStack_94 = uStack_38._4_4_;
            uStack_90 = (undefined4)uStack_30;
            uStack_8c = uStack_30._4_4_;
            FUN_180009590(&uStack_58,&uStack_98);
            uStack_38 = uStack_58;
            uStack_30 = uStack_50;
            uStack_28 = uStack_48;
          }
          uStack_48 = uStack_68;
          uStack_58 = CONCAT44(uStack_74,uStack_78);
          uStack_50 = CONCAT44(uStack_6c,uStack_70);
          uStack_88 = uStack_28;
          uStack_98 = (undefined4)uStack_38;
          uStack_94 = uStack_38._4_4_;
          uStack_90 = (undefined4)uStack_30;
          uStack_8c = uStack_30._4_4_;
          cVar3 = FUN_180029000(*puVar1,puVar1[4],&uStack_58,&uStack_98);
          if (cVar3 != '\0') {
            FUN_180043ca0(*puVar1,uVar5);
            DAT_1803043dd = 0.0 < _DAT_1803043e0;
          }
        }
      }
    }
  }
  else {
    uVar5 = FUN_180022cf0(*puVar1,puVar1[3]);
    _DAT_1803043d8 = _DAT_1803043d8 + -1;
    if (_DAT_1803043d8 == 0 && _DAT_1802f3410 == 0) {
      FUN_180043bf0(puVar1);
    }
    if ((((*(char *)(puVar1 + 8) == '\x01') && (*(longlong *)(puVar1[7] + 8) != 0)) &&
        (lVar6 = FUN_180022e10(*puVar1,puVar1[3]), lVar6 != 0)) &&
       (iVar4 = FUN_180024b50(*puVar1,lVar6), iVar4 == 2)) {
      FUN_180022eb0(*puVar1,puVar1[3],0);
      uVar5 = FUN_180025270(*puVar1,uVar5);
      plVar2 = (longlong *)*puVar1;
      uStack_40 = 0x1800253aa;
      iVar4 = (**(code **)(*(longlong *)plVar2[1] + 800))
                        ((longlong *)plVar2[1],uVar5,*(undefined8 *)(*plVar2 + 0x480));
                    /* WARNING: Could not recover jumptable at 0x0001800253d0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*(longlong *)plVar2[1] + 0x368))
                ((longlong *)plVar2[1],uVar5,*(undefined8 *)(*plVar2 + 0x480),iVar4 + 1);
      return;
    }
  }
  return;
}

// CALLBACK RVA 0x42f00; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/timer_range_update/timer_range_update.c
// Differential report: analysis/module_behavior_recovery/timer_range_update/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x42f00; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180042f00(longlong param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  undefined8 *puVar1;
  longlong *plVar2;
  double dVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  char cVar6;
  int iVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  int iVar11;
  longlong lVar12;
  float fVar13;
  float fVar14;
  uint uVar15;
  float fVar16;
  undefined4 uVar17;
  double dVar18;
  double dVar19;
  undefined4 uVar20;
  undefined4 uVar21;
  float fVar22;
  undefined4 uVar23;
  undefined4 uVar24;
  undefined1 auStack_2f0 [24];
  undefined1 auStack_2d8 [24];
  undefined1 auStack_2c0 [16];
  undefined8 uStack_2b0;
  undefined8 uStack_2a8;
  undefined8 uStack_2a0;
  undefined8 uStack_298;
  undefined8 uStack_288;
  undefined8 uStack_280;
  undefined8 uStack_278;
  undefined8 uStack_270;
  undefined8 uStack_268;
  longlong lStack_260;
  undefined8 uStack_258;
  undefined8 uStack_250;
  undefined8 uStack_248;
  undefined8 uStack_238;
  undefined8 uStack_230;
  undefined8 uStack_228;
  undefined8 uStack_218;
  undefined8 uStack_210;
  undefined8 uStack_208;
  undefined8 uStack_1f8;
  undefined8 uStack_1f0;
  undefined8 uStack_1e8;
  undefined8 uStack_1d8;
  undefined8 uStack_1d0;
  undefined8 uStack_1c8;
  undefined8 uStack_1b8;
  undefined8 uStack_1b0;
  undefined8 uStack_1a8;
  int iStack_194;
  ulonglong uStack_190;
  undefined8 uStack_188;
  undefined8 uStack_180;
  undefined8 uStack_178;
  undefined8 uStack_168;
  undefined8 uStack_160;
  undefined8 uStack_158;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined4 uStack_130;
  undefined4 uStack_12c;
  undefined4 uStack_128;
  undefined4 uStack_124;
  undefined4 uStack_120;
  undefined4 uStack_11c;
  undefined1 auStack_118 [16];
  double dStack_108;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined4 uStack_f0;
  undefined4 uStack_ec;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  uVar8 = FUN_180022c70(*puVar1,puVar1[3]);
  if (DAT_1803043dc == '\x01') {
    _DAT_1803043f8 = _DAT_1803043f8 - *(double *)(param_1 + 0x18);
    plVar2 = (longlong *)*puVar1;
    if (0.0 < _DAT_1803043f8) {
      UNRECOVERED_JUMPTABLE = *(code **)(*(longlong *)plVar2[1] + 0x378);
                    /* WARNING: Could not recover jumptable at 0x0001800259e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE)
                ((longlong *)plVar2[1],uVar8,*(undefined8 *)(*plVar2 + 0x390),UNRECOVERED_JUMPTABLE)
      ;
      return;
    }
    uVar9 = FUN_180022c70(plVar2,puVar1[3]);
    FUN_1800259c0(*puVar1,uVar9,_DAT_1801548d0);
    DAT_1803043dc = '\0';
    LOCK();
    DAT_1803043e8 = 0;
    UNLOCK();
    if ((_DAT_1802f3410 != 1 & DAT_1802f3438) == 1) {
      uVar9 = *puVar1;
      uVar10 = FUN_180028a50(uVar9,puVar1[5]);
      cVar6 = FUN_180028ac0(uVar9,uVar10);
      if (cVar6 != '\0') {
        uVar9 = FUN_180022cf0(*puVar1,puVar1[3]);
        uVar9 = FUN_180024f90(*puVar1,uVar9);
        FUN_180025460(*puVar1,uVar9,0);
      }
    }
    if (_DAT_1802f3410 == 1) {
      FUN_180025a10(*puVar1,uVar8,(float)_DAT_1803043d8);
    }
  }
  if (_DAT_1803043f0 <= 0.0) {
    if (((DAT_1803043dd == '\x01') && (*(char *)(puVar1 + 8) == '\x01')) &&
       (lVar12 = puVar1[7], *(longlong *)(lVar12 + 8) != 0)) {
      uStack_268 = uVar8;
      lStack_260 = param_1;
      FUN_180023550(&uStack_1b8,*puVar1,puVar1[5]);
      FUN_180023030(&uStack_188,*puVar1,puVar1[5]);
      cVar6 = FUN_180023020(*puVar1);
      if (cVar6 == '\0') {
        dStack_108 = (double)uStack_178;
        auStack_118._8_8_ = uStack_180;
        auStack_118._0_8_ = uStack_188;
        FUN_180009590(&uStack_148,auStack_118);
        uStack_188 = uStack_148;
        uStack_180 = uStack_140;
        uStack_178 = uStack_138;
      }
      FUN_180023030(&uStack_1f8,*puVar1,*(undefined8 *)(lVar12 + 8));
      FUN_180024160(&uStack_1d8,*puVar1,*(undefined8 *)(lVar12 + 8));
      iVar7 = FUN_180024200(*puVar1,*(undefined8 *)(lVar12 + 8));
      uStack_270 = FUN_180023170(*puVar1,puVar1[5]);
      fVar13 = (float)func_0x0001800b3590();
      fVar14 = (float)func_0x0001800b1cf0();
      uVar15 = func_0x0001800b3590();
      fVar16 = (float)func_0x0001800b1cf0();
      dVar3 = _DAT_180154930;
      uVar8 = _DAT_180154910;
      lVar12 = 0x1802f34b0;
      if (_DAT_1802f3410 == 0) {
        lVar12 = 0x1802f3478;
      }
      if (0 < (int)*(float *)(lVar12 + 0x30)) {
        fVar22 = (float)(uVar15 ^ _DAT_1801548f0);
        uStack_190 = (ulonglong)(uint)-(int)*(float *)(lVar12 + 0x30);
        iVar11 = 1;
        uVar20 = (undefined4)_DAT_180154900;
        uVar21 = (undefined4)_DAT_180154908;
        uVar23 = (undefined4)_DAT_180154918;
        uVar24 = (undefined4)_DAT_180154928;
        iStack_194 = iVar7;
        do {
          uStack_208 = uStack_178;
          uStack_218 = uStack_188;
          uStack_210 = uStack_180;
          uStack_248 = uStack_1e8;
          uStack_258 = uStack_1f8;
          uStack_250 = uStack_1f0;
          FUN_1800093b0(&uStack_168,uVar21,uVar20,uVar21);
          dStack_108 = (double)uStack_248;
          auStack_118._0_8_ = uStack_258;
          auStack_118._8_8_ = uStack_250;
          FUN_1800093d0(&uStack_148,auStack_118,&uStack_168);
          FUN_1800093b0(&uStack_238,uVar21,(int)uVar8,uVar21);
          dStack_108 = (double)uStack_248;
          auStack_118._8_8_ = uStack_250;
          auStack_118._0_8_ = uStack_258;
          FUN_180009400(&uStack_130,auStack_118,&uStack_238);
          auStack_118._8_4_ = SUB84((double)fVar16,0);
          auStack_118._0_8_ = (double)(fVar14 * fVar22);
          auStack_118._12_4_ = (int)((ulonglong)(double)fVar16 >> 0x20);
          dStack_108 = (double)(fVar13 * fVar22);
          FUN_180009430(auStack_2c0,auStack_118,uVar23);
          dStack_108 = (double)uStack_2b0;
          FUN_180009650(auStack_2f0,auStack_118);
          uStack_f8 = uStack_128;
          uStack_f4 = uStack_124;
          uStack_f0 = uStack_120;
          uStack_ec = uStack_11c;
          dStack_108 = (double)uStack_138;
          uStack_100 = uStack_130;
          uStack_fc = uStack_12c;
          auStack_118._0_8_ = uStack_148;
          auStack_118._8_8_ = uStack_140;
          uStack_298 = uStack_208;
          uStack_2a8 = uStack_218;
          uStack_2a0 = uStack_210;
          cVar6 = FUN_1800098e0(auStack_118,&uStack_2a8,auStack_2f0);
          if (cVar6 != '\0') {
            uStack_f8 = uStack_128;
            uStack_f4 = uStack_124;
            uStack_f0 = uStack_120;
            uStack_ec = uStack_11c;
            dStack_108 = (double)uStack_138;
            uStack_100 = uStack_130;
            uStack_fc = uStack_12c;
            auStack_118._0_8_ = uStack_148;
            auStack_118._8_8_ = uStack_140;
            uStack_278 = uStack_208;
            uStack_288 = uStack_218;
            uStack_280 = uStack_210;
            FUN_180009880(&uStack_2a8,auStack_118,&uStack_288);
            dStack_108 = (double)uStack_208;
            auStack_118._0_8_ = uStack_218;
            auStack_118._8_8_ = uStack_210;
            uStack_278 = uStack_298;
            uStack_288 = uStack_2a8;
            uStack_280 = uStack_2a0;
            dVar18 = (double)FUN_1800094b0(auStack_118,&uStack_288);
            lVar12 = lStack_260;
            if (0.0 < dVar18) {
              if (dVar18 < (double)(_DAT_1802f3518 * _DAT_1802f3518)) {
                return;
              }
              if (iVar11 == -1) {
                return;
              }
              if (_DAT_1802f3410 == 1) {
                FUN_180043bf0(puVar1);
              }
              else {
                FUN_180025a10(*puVar1,uStack_268,(float)iVar11);
              }
              _DAT_1803043d8 = iVar11;
              _DAT_1803043f0 = (double)_DAT_1802f3470;
              _DAT_1803043f8 = (double)((float)iVar11 - *(float *)(lVar12 + 0x10)) * _DAT_180154920;
              return;
            }
          }
          uVar5 = _DAT_1803043e4;
          uVar4 = _DAT_1803043e0;
          uVar17 = FUN_180023b40(*puVar1,puVar1[5]);
          FUN_180029290(auStack_2d8,uStack_270,uVar4,uVar5,uVar17);
          dStack_108 = (double)uStack_1a8;
          auStack_118._8_8_ = uStack_1b0;
          auStack_118._0_8_ = uStack_1b8;
          FUN_180009400(&uStack_148,auStack_118,auStack_2d8);
          uStack_1a8 = uStack_138;
          uStack_1b8 = uStack_148;
          uStack_1b0 = uStack_140;
          dStack_108 = (double)uStack_178;
          auStack_118._8_4_ = (undefined4)uStack_180;
          auStack_118._0_8_ = uStack_188;
          auStack_118._12_4_ = uStack_180._4_4_;
          uStack_158 = uStack_138;
          uStack_168 = uStack_148;
          uStack_160 = uStack_140;
          FUN_180009400(&uStack_148,auStack_118,&uStack_168);
          uStack_188 = uStack_148;
          uStack_180 = uStack_140;
          uStack_178 = uStack_138;
          dStack_108 = (double)uStack_1a8;
          auStack_118._8_8_ = uStack_1b0;
          auStack_118._0_8_ = uStack_1b8;
          FUN_180009430(&uStack_148,auStack_118,uVar24);
          uStack_1b8 = uStack_148;
          uStack_1b0 = uStack_140;
          uStack_1a8 = uStack_138;
          if (_DAT_1802f3410 == 1) {
            dVar18 = (double)func_0x00018013cfd0(uStack_148,(int)uStack_138);
            dStack_108 = (double)uStack_178;
            auStack_118._8_8_ = uStack_180;
            auStack_118._0_8_ = uStack_188;
            uStack_158 = uStack_1c8;
            uStack_168 = uStack_1d8;
            uStack_160 = uStack_1d0;
            FUN_1800093d0(&uStack_148,auStack_118,&uStack_168);
            dVar19 = (double)func_0x00018013cfd0(uStack_148,(int)uStack_138);
            uStack_158 = uStack_138;
            uStack_168 = uStack_148;
            uStack_160 = uStack_140;
            FUN_180009430(auStack_118,&uStack_168,SUB84(dVar18 / dVar19,0));
            uStack_148 = auStack_118._0_8_;
            uStack_138 = dStack_108;
            uStack_140 = 0;
            uStack_158 = uStack_1c8;
            uStack_168 = uStack_1d8;
            uStack_160 = uStack_1d0;
            uStack_228 = dStack_108;
            uStack_238 = auStack_118._0_8_;
            uStack_230 = 0;
            FUN_180009400(auStack_118,&uStack_168,&uStack_238);
            uStack_1d8 = auStack_118._0_8_;
            uStack_1d0 = auStack_118._8_8_;
            uStack_1c8 = dStack_108;
          }
          iVar7 = iStack_194;
          if (0 < iStack_194) {
            dStack_108 = (double)uStack_1c8;
            auStack_118._8_8_ = uStack_1d0;
            auStack_118._0_8_ = uStack_1d8;
            uStack_158 = uStack_1e8;
            uStack_168 = uStack_1f8;
            uStack_160 = uStack_1f0;
            FUN_1800093d0(&uStack_148,auStack_118,&uStack_168);
            uStack_158 = uStack_138;
            uStack_168 = uStack_148;
            uStack_160 = uStack_140;
            FUN_180009430(auStack_118,&uStack_168,SUB84(dVar3 / (double)iVar7,0));
            uStack_138 = dStack_108;
            uStack_148 = auStack_118._0_8_;
            uStack_140 = auStack_118._8_8_;
            uStack_158 = uStack_1e8;
            uStack_168 = uStack_1f8;
            uStack_160 = uStack_1f0;
            uStack_228 = dStack_108;
            uStack_238 = auStack_118._0_8_;
            uStack_230 = auStack_118._8_8_;
            FUN_180009400(auStack_118,&uStack_168,&uStack_238);
            uStack_1f8 = auStack_118._0_8_;
            uStack_1f0 = auStack_118._8_8_;
            uStack_1e8 = dStack_108;
            iStack_194 = iVar7 + -1;
          }
          iVar7 = (int)uStack_190 + iVar11;
          iVar11 = iVar11 + 1;
        } while (iVar7 != 0);
      }
    }
  }
  else {
    _DAT_1803043f0 = _DAT_1803043f0 - *(double *)(param_1 + 0x18);
  }
  return;
}

// CALLBACK RVA 0x43950; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/timer_range_events/timer_range_events.c
// Differential report: analysis/module_behavior_recovery/timer_range_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x43950; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180043950(longlong param_1)

{
  if ((DAT_1803043e8 & 1) != 0) {
    *(undefined4 *)(param_1 + 0x24) = 1;
  }
  return;
}

// CALLBACK RVA 0x43970; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/timer_range_events/timer_range_events.c
// Differential report: analysis/module_behavior_recovery/timer_range_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x43970; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong FUN_180043970(longlong param_1)

{
  undefined8 *puVar1;
  byte bVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  
  uVar3 = 0x1802f3160;
  if ((*(longlong *)(param_1 + 0x10) == 0x1802f3160) && (*(char *)(param_1 + 0x18) == '\0')) {
    puVar1 = *(undefined8 **)(param_1 + 8);
    uVar4 = FUN_180022c70(*puVar1,puVar1[3]);
    FUN_1800259c0(*puVar1,uVar4,_DAT_180154938);
    bVar2 = DAT_1803043e8;
    DAT_1803043dc = 0;
    _DAT_1803043d8 = 0;
    LOCK();
    DAT_1803043e8 = 0;
    uVar3 = (ulonglong)bVar2;
    UNLOCK();
  }
  return uVar3;
}

// UI RVA 0x439e0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x439e0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800439e0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  undefined8 uVar2;
  
  FUN_180013e90(param_1,param_2,&UNK_180154a05);
  FUN_18000d040(param_2,param_1,0x1802f33e0);
  FUN_18000cf30(param_2,param_1,0x1802f34e8);
  uVar2 = 0x1802f34b0;
  if (_DAT_1802f3410 == 0) {
    uVar2 = 0x1802f3478;
  }
  FUN_18000cf30(param_2,param_1,uVar2);
  FUN_18000cf30(param_2,param_1,0x1802f3440);
  if (_DAT_1802f3410 == 0) {
    FUN_18000cef0(param_2,param_1,0x1802f3420);
  }
  FUN_180013e90(param_1,param_2,&UNK_180154a0a);
  FUN_18000cef0(param_2,param_1,0x1802f3370);
  FUN_18000cef0(param_2,param_1,0x1802f3390);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802f33c0,0x1802f33b0,&DAT_1802f33c8);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x43ad0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x43ad0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180043ad0(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c6f0(param_1,&UNK_180154a15,0x1802f33e0);
  FUN_18000c450(param_1,&UNK_180154a1a,0x1802f34e8);
  FUN_18000c450(param_1,&UNK_180154a23,0x1802f3478);
  FUN_18000c450(param_1,&UNK_180154a2c,0x1802f34b0);
  FUN_18000c450(param_1,&UNK_180154a3b,0x1802f3440);
  FUN_18000c3b0(param_1,&UNK_180154a44,0x1802f3420);
  FUN_18000c3b0(param_1,&UNK_180154a57,0x1802f3370);
  FUN_18000c3b0(param_1,&UNK_180154a6d,0x1802f3390);
  uVar1 = uRam00000001802f33c9;
  uVar2 = DAT_1802f33c8;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180154a7c,DAT_1802f33c8);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802f33c8;
      break;
    case 2:
      uRam00000001802f33c9 = DAT_1802f33c8;
      break;
    case 3:
      uVar2 = uRam00000001802f33c9;
    }
  }
  DAT_1802f33c8 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x43bb0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x43bb0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180043bb0(undefined8 param_1)

{
  FUN_1800ab710(param_1,0x20,&UNK_180154a93,
                *(undefined8 *)((ulonglong)_DAT_1802f3410 * 8 + 0x1802f33d0));
  return;
}

// CANDIDATE_LOCAL RVA 0x43bf0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x43bf0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 FUN_180043bf0(undefined8 *param_1)

{
  longlong lVar1;
  longlong *plVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  char cVar5;
  int iVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 unaff_RBP;
  undefined8 unaff_RSI;
  undefined8 unaff_RDI;
  
  uVar7 = FUN_180022c70(*param_1,param_1[3]);
  uVar4 = FUN_1800259c0(*param_1,uVar7,0);
  uVar3 = DAT_1803043e8;
  DAT_1803043dc = 1;
  if (_DAT_1802f3410 == 1) {
    LOCK();
    DAT_1803043e8 = 1;
    UNLOCK();
    uVar4 = uVar3;
  }
  else if (DAT_1802f3438 == '\x01') {
    uVar7 = *param_1;
    uVar8 = FUN_180028a50(uVar7,param_1[5]);
    cVar5 = FUN_180028ac0(uVar7,uVar8);
    uVar4 = 0;
    if (cVar5 != '\0') {
      uVar7 = FUN_180022cf0(*param_1,param_1[3]);
      uVar7 = FUN_180024f90(*param_1,uVar7);
      FUN_180025460(*param_1,uVar7,1);
      plVar2 = (longlong *)*param_1;
      lVar1 = *(longlong *)plVar2[1];
      iVar6 = (**(code **)(lVar1 + 800))
                        ((longlong *)plVar2[1],uVar7,*(undefined8 *)(*plVar2 + 0x480),lVar1,
                         unaff_RDI,unaff_RSI,unaff_RBP);
                    /* WARNING: Could not recover jumptable at 0x0001800253d0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar4 = (**(code **)(*(longlong *)plVar2[1] + 0x368))
                        ((longlong *)plVar2[1],uVar7,*(undefined8 *)(*plVar2 + 0x480),iVar6 + 1);
      return uVar4;
    }
  }
  return uVar4;
}

// CANDIDATE_LOCAL RVA 0x43ca0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x43ca0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180043ca0(undefined8 param_1,undefined8 param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  float fVar5;
  char cVar6;
  float fVar7;
  float fVar8;
  
  uVar1 = FUN_1800250d0();
  uVar2 = FUN_180025120(param_1,param_2);
  uVar3 = FUN_180025170(param_1,param_2);
  uVar4 = FUN_1800251c0(param_1,param_2);
  cVar6 = FUN_180025430(param_1,uVar1);
  fVar7 = _DAT_18015493c;
  fVar8 = _DAT_18015493c;
  if (cVar6 == '\0') {
    fVar8 = 0.0;
  }
  cVar6 = FUN_180025430(param_1,uVar2);
  fVar5 = _DAT_180154940;
  if (cVar6 != '\0') {
    fVar8 = fVar8 + _DAT_180154940;
  }
  cVar6 = FUN_180025430(param_1,uVar3);
  if (cVar6 == '\0') {
    fVar7 = 0.0;
  }
  cVar6 = FUN_180025430(param_1,uVar4);
  if (cVar6 != '\0') {
    fVar7 = fVar7 + fVar5;
  }
  _DAT_1803043e0 = fVar8;
  _DAT_1803043e4 = fVar7;
  return;
}

