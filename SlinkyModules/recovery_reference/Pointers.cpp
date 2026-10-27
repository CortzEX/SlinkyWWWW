// Recovered decompiler view: Pointers
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x3da80, 0x3e590); proximity does not prove ownership.

// CALLBACK RVA 0x3da80; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/pointers/pointers.c
// Differential report: analysis/module_behavior_recovery/pointers/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3da80; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003da80(longlong param_1)

{
  undefined4 uVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  double dVar6;
  double dVar7;
  undefined4 uVar8;
  undefined8 uVar9;
  ulonglong uVar10;
  longlong lVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  double dVar15;
  undefined8 extraout_XMM0_Qb;
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  double dVar18;
  
  if (_DAT_1803008a0 != 0) {
    puVar2 = *(undefined8 **)(param_1 + 0x20);
    uVar1 = *(undefined4 *)(param_1 + 0x40);
    uVar9 = FUN_180022d40(*puVar2,puVar2[3]);
    fVar12 = (float)FUN_180027200(*puVar2,uVar9);
    fVar13 = (float)FUN_180027250(*puVar2,uVar9);
    FUN_180029500();
    uVar10 = FUN_180009e60(*(undefined8 *)(param_1 + 0x28));
    uVar8 = (undefined4)(uVar10 >> 0x20);
    (*(code *)*_DAT_180150cc0)();
    if (_DAT_1802f0a10 == 0) {
      (*(code *)*_DAT_180150cd8)(uVar10 & 0xffffffff,uVar8,0);
    }
    else {
      fVar14 = _DAT_180153c74;
      if (_DAT_180153c74 <= fVar12) {
        fVar14 = fVar12;
      }
      (*(code *)*_DAT_180150cd8)(uVar10 & 0xffffffff,uVar8,0);
      (*(code *)*_DAT_180150cc8)(_DAT_180153c78 - fVar14,_DAT_180153c7c,0,0);
    }
    (*(code *)*_DAT_180150cb0)();
    (*(code *)*_DAT_18013e458)(0xb20);
    dVar7 = _DAT_180153c98;
    dVar6 = _DAT_180153c90;
    puVar5 = _DAT_180150cd8;
    puVar4 = _DAT_180150cd0;
    puVar3 = _DAT_180150cb8;
    puVar2 = _DAT_180150ca0;
    if (_DAT_1803008a0 != 0) {
      lVar11 = 0x1803008e0;
      uVar10 = 0;
      dVar18 = _DAT_180153c88;
      do {
        fVar12 = (float)FUN_18000a2b0(CONCAT44((int)((ulonglong)*(double *)(lVar11 + -0x20) >> 0x20)
                                               ,(float)*(double *)(lVar11 + -0x20)),
                                      CONCAT44((int)((ulonglong)*(double *)(lVar11 + -0x30) >> 0x20)
                                               ,(float)*(double *)(lVar11 + -0x30)),uVar1);
        fVar14 = (float)FUN_18000a2b0(CONCAT44((int)((ulonglong)*(double *)(lVar11 + -0x18) >> 0x20)
                                               ,(float)*(double *)(lVar11 + -0x18)),
                                      CONCAT44((int)((ulonglong)*(double *)(lVar11 + -0x28) >> 0x20)
                                               ,(float)*(double *)(lVar11 + -0x28)),uVar1);
        dVar15 = (double)func_0x00018013cfb0((double)fVar14 - *(double *)(param_1 + 0x18),
                                             (double)fVar12 - *(double *)(param_1 + 8));
        auVar16._0_8_ = (dVar15 * dVar18) / dVar6 + dVar7;
        auVar16._8_8_ = extraout_XMM0_Qb;
        auVar17._4_12_ = auVar16._4_12_;
        auVar17._0_4_ = (float)auVar16._0_8_ - fVar13;
        FUN_18000a210(auVar17._0_8_);
        (*(code *)*_DAT_180150cc0)();
        (*(code *)*_DAT_180150cc8)();
        (*(code *)*puVar4)();
        FUN_18000a2b0();
        FUN_18000a1f0();
        (*(code *)*puVar5)();
        if (_DAT_1802f0a88 == 0) {
          FUN_18000a2b0();
          FUN_18000a2b0();
          FUN_18000a2b0();
          dVar18 = _DAT_180153c88;
        }
        (*(code *)*puVar2)();
        FUN_180029540();
        (*(code *)*puVar2)();
        FUN_180029570();
        (*(code *)*puVar3)();
        uVar10 = uVar10 + 1;
        lVar11 = lVar11 + 0x38;
      } while (uVar10 < _DAT_1803008a0);
    }
    (*(code *)*_DAT_180150cb8)();
                    /* WARNING: Could not recover jumptable at 0x0001800295b1. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*(code *)*_DAT_18014fcf8)(0x8074);
    return;
  }
  return;
}

// CALLBACK RVA 0x3df10; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/pointers/pointers.c
// Differential report: analysis/module_behavior_recovery/pointers/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3df10; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003df10(longlong param_1)

{
  longlong *plVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  uint uVar6;
  char cVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  undefined4 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  uint uVar14;
  longlong lVar15;
  float fVar16;
  uint uVar17;
  float fVar18;
  double dVar19;
  undefined8 uStack_160;
  undefined8 uStack_158;
  double dStack_150;
  undefined4 uStack_148;
  undefined4 uStack_144;
  undefined4 uStack_140;
  undefined4 uStack_13c;
  double dStack_138;
  undefined4 uStack_128;
  undefined4 uStack_124;
  undefined4 uStack_120;
  undefined4 uStack_11c;
  double dStack_118;
  double dStack_110;
  undefined8 uStack_108;
  double dStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  double dStack_e8;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  double dStack_c8;
  
  plVar1 = *(longlong **)(param_1 + 8);
  if (plVar1[4] != 0) {
    _DAT_1803008a0 = 0;
    FUN_180023030(&uStack_128,*plVar1,plVar1[5]);
    FUN_1800230d0(&uStack_160,*plVar1,plVar1[5]);
    uVar12 = FUN_180022d40(*plVar1,plVar1[3]);
    fVar16 = (float)FUN_180027250(*plVar1,uVar12);
    uVar12 = FUN_180024600(*plVar1,plVar1[4]);
    uVar14 = (uint)DAT_1802f0b60;
    iVar8 = FUN_180024e50(*plVar1,uVar12);
    uVar6 = _DAT_180153ce0;
    dVar5 = _DAT_180153cd0;
    dVar4 = _DAT_180153cc8;
    dVar3 = _DAT_180153cc0;
    if (0 < iVar8) {
      iVar8 = 0;
      do {
        uVar13 = FUN_180024e80(*plVar1,uVar12,iVar8);
        cVar7 = (**(code **)(**(longlong **)(*plVar1 + 8) + 0xc0))
                          (*(longlong **)(*plVar1 + 8),plVar1[5],uVar13);
        if (((cVar7 == '\0') && (cVar7 = FUN_1800237b0(*plVar1,uVar13), cVar7 == '\0')) &&
           (uVar10 = FUN_18002acb0(*plVar1,uVar13), (uVar10 & uVar14 * 5 + 2) == 0)) {
          FUN_180023030(&dStack_110,*plVar1,uVar13);
          dStack_e8 = dStack_100;
          uStack_f8 = dStack_110;
          uStack_f0 = uStack_108;
          dStack_c8 = dStack_118;
          uStack_d8 = CONCAT44(uStack_124,uStack_128);
          uStack_d0 = CONCAT44(uStack_11c,uStack_120);
          dVar19 = (double)FUN_1800094b0(&uStack_f8,&uStack_d8);
          if (dVar19 <= (double)(_DAT_1802f0ac8 * _DAT_1802f0ac8)) {
            dVar2 = (double)func_0x00018013cfb0(SUB84(dStack_100 - dStack_118,0),
                                                dStack_110 - (double)CONCAT44(uStack_124,uStack_128)
                                               );
            uVar17 = FUN_18000a210((float)((dVar2 * dVar3) / dVar4 + dVar5) - fVar16);
            if (_DAT_1802f0b00 <= (float)(uVar17 & uVar6)) {
              FUN_1800230d0(&uStack_f8,*plVar1,uVar13);
              lVar15 = _DAT_1803008a0 * 0x38;
              _DAT_1803008a0 = _DAT_1803008a0 + 1;
              *(double *)(lVar15 + 0x1803008b0) = dStack_110;
              *(double *)(lVar15 + 0x1803008b8) = dStack_100;
              *(double *)(lVar15 + 0x1803008c0) = uStack_f8;
              *(double *)(lVar15 + 0x1803008c8) = dStack_e8;
              if ((float)dVar19 < 0.0) {
                fVar18 = (float)func_0x0001800af4a0();
              }
              else {
                fVar18 = SQRT((float)dVar19);
              }
              *(float *)(lVar15 + 0x1803008e0) = fVar18;
              dStack_c8 = dStack_150;
              uStack_d8 = uStack_160;
              uStack_d0 = uStack_158;
              dStack_138 = dStack_e8;
              uStack_148 = (undefined4)uStack_f8;
              uStack_144 = uStack_f8._4_4_;
              uStack_140 = (undefined4)uStack_f0;
              uStack_13c = uStack_f0._4_4_;
              dVar19 = (double)FUN_1800094f0(&uStack_d8,&uStack_148);
              *(float *)(lVar15 + 0x1803008dc) = (float)dVar19;
              if (_DAT_1802f0a88 == 2) {
                if ((uVar10 & 5) == 0) {
                  *(undefined4 *)(lVar15 + 0x1803008d8) = _DAT_1802f0b38;
                  uVar13 = _DAT_1802f0b30;
                }
                else {
                  *(undefined4 *)(lVar15 + 0x1803008d8) = _DAT_1802f0b18;
                  uVar13 = _DAT_1802f0b10;
                }
                *(undefined8 *)(lVar15 + 0x1803008d0) = uVar13;
              }
              else if (_DAT_1802f0a88 == 1) {
                uVar11 = FUN_180028e10(*plVar1,uVar13);
                FUN_1800290d0(&uStack_d8,uVar11);
                *(undefined4 *)(lVar15 + 0x1803008d8) = (undefined4)uStack_d0;
                *(undefined8 *)(lVar15 + 0x1803008d0) = uStack_d8;
              }
              if (_DAT_1803008a0 == 100) break;
            }
          }
        }
        iVar8 = iVar8 + 1;
        iVar9 = FUN_180024e50(*plVar1,uVar12);
      } while (iVar8 < iVar9);
    }
    func_0x00018013d0f0(0x1803008b0,_DAT_1803008a0,0x38,FUN_18003e570);
  }
  return;
}

// UI RVA 0x3e2d0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3e2d0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003e2d0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  undefined8 uVar2;
  
  FUN_180013e90(param_1,param_2,&UNK_180153e02);
  FUN_18000cf30(param_2,param_1,0x1802f0a98);
  FUN_18000cf30(param_2,param_1,0x1802f0ad0);
  FUN_18000cef0(param_2,param_1,0x1802f0b48);
  FUN_180013e90(param_1,param_2,&UNK_180153e07);
  FUN_18000d040(param_2,param_1,0x1802f09e0);
  FUN_18000d040(param_2,param_1,0x1802f0a58);
  FUN_18000cfb0(param_2,param_1,0x1802f08d0);
  if (_DAT_1802f0a88 == 2) {
    FUN_18000d0a0(param_2,param_1,0x1802f0b28);
    if (DAT_1802f0b60 != '\0') goto code_r0x00018000cef0;
    uVar2 = 0x1802f0b08;
  }
  else {
    if (_DAT_1802f0a88 != 0) goto code_r0x00018000cef0;
    FUN_18000d0a0(param_2,param_1,0x1802f0990);
    uVar2 = 0x1802f09b0;
  }
  FUN_18000d0a0(param_2,param_1,uVar2);
code_r0x00018000cef0:
  FUN_18000cf30(param_2,param_1,0x1802f0920);
  FUN_18000cf30(param_2,param_1,0x1802f0958);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802f0a30,0x1802f0a20,&DAT_1802f0a38);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x3e400; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3e400; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003e400(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c450(param_1,&UNK_180153e15,0x1802f0a98);
  FUN_18000c450(param_1,&UNK_180153e1b,0x1802f0ad0);
  FUN_18000c3b0(param_1,&UNK_180153e26,0x1802f0b48);
  FUN_18000c6f0(param_1,&UNK_180153e36,0x1802f09e0);
  FUN_18000c6f0(param_1,&UNK_180153e3c,0x1802f0a58);
  FUN_18000c550(param_1,&UNK_180153e47,0x1802f08d0);
  FUN_18000c7e0(param_1,&UNK_180153e56,0x1802f0990);
  FUN_18000c7e0(param_1,&UNK_180153e61,0x1802f09b0);
  FUN_18000c7e0(param_1,&UNK_180153e6b,0x1802f0b28);
  FUN_18000c7e0(param_1,&UNK_180153e79,0x1802f0b08);
  FUN_18000c450(param_1,&UNK_180153e8a,0x1802f0920);
  FUN_18000c450(param_1,&UNK_180153e90,0x1802f0958);
  uVar1 = uRam00000001802f0a39;
  uVar2 = DAT_1802f0a38;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180153e97,DAT_1802f0a38);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802f0a38;
      break;
    case 2:
      uRam00000001802f0a39 = DAT_1802f0a38;
      break;
    case 3:
      uVar2 = uRam00000001802f0a39;
    }
  }
  DAT_1802f0a38 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x3e530; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3e530; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003e530(undefined8 param_1)

{
  FUN_1800ab710(param_1,0x20,&UNK_180153ea4,
                *(undefined8 *)((ulonglong)_DAT_1802f0a10 * 8 + 0x1802f09d0));
  return;
}

// CANDIDATE_LOCAL RVA 0x3e570; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3e570; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


int FUN_18003e570(longlong param_1,longlong param_2)

{
  return (int)(*(float *)(param_2 + 0x30) - *(float *)(param_1 + 0x30));
}

