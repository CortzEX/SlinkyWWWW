// Recovered decompiler view: Indicators
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x3ea40, 0x3f4c0); proximity does not prove ownership.

// CALLBACK RVA 0x3ea40; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/indicators/indicators.c
// Differential report: analysis/module_behavior_recovery/indicators/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3ea40; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003ea40(longlong param_1)

{
  longlong *plVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  longlong *plVar4;
  
  if ((*(char *)(param_1 + 0x18) == '\0') && (*(longlong *)(param_1 + 0x10) == 0x1802f1440)) {
    if (_DAT_180301ea0 != 0) {
      plVar1 = *(longlong **)(**(longlong **)(param_1 + 8) + 8);
      plVar4 = (longlong *)0x180301ed8;
      uVar3 = 0;
      uVar2 = _DAT_180301ea0;
      do {
        if (*plVar4 != 0) {
          (**(code **)(*plVar1 + 0xb0))(plVar1);
          uVar2 = _DAT_180301ea0;
        }
        uVar3 = uVar3 + 1;
        plVar4 = plVar4 + 7;
      } while (uVar3 < uVar2);
    }
    _DAT_180301ea0 = 0;
  }
  return;
}

// CALLBACK RVA 0x3ead0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/indicators/indicators.c
// Differential report: analysis/module_behavior_recovery/indicators/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3ead0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003ead0(longlong param_1)

{
  undefined4 uVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  ulonglong uVar8;
  undefined4 *puVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  double dVar13;
  double dVar14;
  undefined8 extraout_XMM0_Qb;
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  
  if (_DAT_180301ea0 != 0) {
    puVar2 = *(undefined8 **)(param_1 + 0x20);
    uVar1 = *(undefined4 *)(param_1 + 0x40);
    uVar6 = FUN_180022d40(*puVar2,puVar2[3]);
    uVar7 = FUN_1800272a0(*puVar2,uVar6);
    fVar10 = (float)FUN_180027250(*puVar2,uVar6);
    FUN_180029500();
    uVar8 = FUN_180009e60(*(undefined8 *)(param_1 + 0x28));
    (*(code *)*_DAT_180150cc0)();
    puVar5 = _DAT_180150cd8;
    (*(code *)*_DAT_180150cd8)(uVar8 & 0xffffffff,uVar8 >> 0x20,0);
    (*(code *)*_DAT_180150cb0)();
    (*(code *)*_DAT_18013e458)(0xb20);
    dVar13 = (double)FUN_18004c270();
    func_0x0001800b1990(dVar13 * _DAT_180153fe8);
    dVar13 = _DAT_180154008;
    puVar4 = _DAT_180150cd0;
    puVar3 = _DAT_18013e448;
    if (_DAT_180301ea0 != 0) {
      puVar9 = (undefined4 *)0x180301ee4;
      uVar8 = 0;
      do {
        fVar11 = (float)FUN_18000a2b0(CONCAT44((int)((ulonglong)*(double *)(puVar9 + -9) >> 0x20),
                                               (float)*(double *)(puVar9 + -9)),
                                      CONCAT44((int)((ulonglong)*(double *)(puVar9 + -0xd) >> 0x20),
                                               (float)*(double *)(puVar9 + -0xd)),uVar1);
        fVar12 = (float)FUN_18000a2b0(CONCAT44((int)((ulonglong)*(double *)(puVar9 + -7) >> 0x20),
                                               (float)*(double *)(puVar9 + -7)),
                                      CONCAT44((int)((ulonglong)*(double *)(puVar9 + -0xb) >> 0x20),
                                               (float)*(double *)(puVar9 + -0xb)),uVar1);
        dVar14 = (double)func_0x00018013cfb0((double)fVar12 - *(double *)(param_1 + 0x18),
                                             (double)fVar11 - *(double *)(param_1 + 8));
        auVar15._0_8_ = (dVar14 * _DAT_180153ff8) / _DAT_180154000 + dVar13;
        auVar15._8_8_ = extraout_XMM0_Qb;
        auVar16._4_12_ = auVar15._4_12_;
        auVar16._0_4_ = (float)auVar15._0_8_ - fVar10;
        FUN_18000a210(auVar16._0_8_);
        (*(code *)*_DAT_180150cc0)();
        (*(code *)*_DAT_180150cc8)();
        (*(code *)*puVar5)();
        (*(code *)*puVar4)();
        if (*(longlong *)(puVar9 + -3) != 0) {
          (*(code *)*_DAT_180150cc0)();
          (*(code *)*_DAT_180150cc8)();
          if (*(char *)(param_1 + 0x44) == '\x01') {
            FUN_1800277f0(*puVar2);
            FUN_1800278f0(*puVar2);
          }
          else {
            (*(code *)*_DAT_18013e458)(0xde1);
          }
          FUN_180027590(*puVar2,uVar7,*(undefined8 *)(puVar9 + -3),
                        (float)((double)(int)-puVar9[-1] * _DAT_180153ff0),0xc0a00000,*puVar9,1);
          if (*(char *)(param_1 + 0x44) == '\x01') {
            FUN_180027820(*puVar2);
          }
          else {
            (*(code *)*_DAT_18013e450)(0xde1);
          }
          (*(code *)*_DAT_180150cb8)();
        }
        (*(code *)*puVar5)();
        (*(code *)*puVar4)();
        (*(code *)*puVar3)();
        FUN_180029540();
        (*(code *)*puVar3)();
        FUN_180029570();
        (*(code *)*_DAT_180150cb8)();
        uVar8 = uVar8 + 1;
        puVar9 = puVar9 + 0xe;
      } while (uVar8 < _DAT_180301ea0);
    }
    (*(code *)*_DAT_180150cb8)();
                    /* WARNING: Could not recover jumptable at 0x0001800295b1. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*(code *)*_DAT_18014fcf8)(0x8074);
    return;
  }
  return;
}

// CALLBACK RVA 0x3ef20; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/indicators/indicators.c
// Differential report: analysis/module_behavior_recovery/indicators/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3ef20; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003ef20(longlong param_1)

{
  longlong *plVar1;
  longlong *plVar2;
  double dVar3;
  double dVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  ulonglong uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  longlong lVar12;
  longlong lVar13;
  undefined4 uVar14;
  ulonglong uVar15;
  longlong *plVar16;
  double dVar17;
  double dVar18;
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  longlong lStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined8 uStack_98;
  
  plVar1 = *(longlong **)(param_1 + 8);
  if (_DAT_180301ea0 != 0) {
    plVar2 = *(longlong **)(*plVar1 + 8);
    plVar16 = (longlong *)0x180301ed8;
    uVar15 = 0;
    uVar9 = _DAT_180301ea0;
    do {
      if (*plVar16 != 0) {
        (**(code **)(*plVar2 + 0xb0))(plVar2);
        uVar9 = _DAT_180301ea0;
      }
      uVar15 = uVar15 + 1;
      plVar16 = plVar16 + 7;
    } while (uVar15 < uVar9);
  }
  _DAT_180301ea0 = 0;
  if (plVar1[4] != 0) {
    uVar10 = FUN_180022d40(*plVar1,plVar1[3]);
    lStack_d0 = FUN_1800272a0(*plVar1,uVar10);
    if (lStack_d0 != 0) {
      FUN_180023030(&uStack_118,*plVar1,plVar1[5]);
      uVar10 = FUN_180024620(*plVar1,plVar1[4]);
      iVar6 = FUN_180024e50(*plVar1,uVar10);
      dVar4 = _DAT_180154030;
      dVar3 = _DAT_180154028;
      if (0 < iVar6) {
        iVar6 = 0;
        do {
          uVar11 = FUN_180024e80(*plVar1,uVar10,iVar6);
          iVar7 = FUN_180023860(*plVar1,uVar11);
          cVar5 = DAT_1802f1718;
          if ((iVar7 == 0xe) || (cVar5 = DAT_1802f16f8, iVar7 == 0xc)) {
            if (cVar5 != '\0') goto LAB_18003f0d9;
          }
          else if (((iVar7 == 10) && (DAT_1802f16d8 != '\0')) &&
                  (cVar5 = FUN_180027fa0(*plVar1,uVar11), cVar5 == '\0')) {
LAB_18003f0d9:
            FUN_180023030(&uStack_100,*plVar1,uVar11);
            FUN_1800230d0(&uStack_e8,*plVar1,uVar11);
            uStack_b8 = uStack_f0;
            uStack_c8 = uStack_100;
            uStack_c0 = uStack_f8;
            uStack_98 = uStack_108;
            uStack_a8 = uStack_118;
            uStack_a4 = uStack_114;
            uStack_a0 = uStack_110;
            uStack_9c = uStack_10c;
            dVar17 = (double)FUN_1800094b0(&uStack_c8,&uStack_a8);
            if (DAT_1802f1738 == '\x01') {
              uStack_b8 = uStack_d8;
              uStack_c8 = uStack_e8;
              uStack_c0 = uStack_e0;
              uStack_98 = uStack_108;
              uStack_a8 = uStack_118;
              uStack_a4 = uStack_114;
              uStack_a0 = uStack_110;
              uStack_9c = uStack_10c;
              dVar18 = (double)FUN_1800094b0(&uStack_c8,&uStack_a8);
              if (dVar18 < dVar17) goto LAB_18003f05a;
            }
            if (dVar17 < 0.0) {
              dVar17 = (double)func_0x0001800af2f0();
            }
            else {
              dVar17 = SQRT(dVar17);
            }
            lVar12 = _DAT_180301ea0 * 0x38;
            _DAT_180301ea0 = _DAT_180301ea0 + 1;
            *(undefined8 *)(lVar12 + 0x180301eb0) = uStack_100;
            *(undefined8 *)(lVar12 + 0x180301eb8) = uStack_f0;
            *(undefined8 *)(lVar12 + 0x180301ec0) = uStack_e8;
            *(undefined8 *)(lVar12 + 0x180301ec8) = uStack_d8;
            *(int *)(lVar12 + 0x180301ed0) = iVar7;
            plVar2 = *(longlong **)(*plVar1 + 8);
            FUN_1800ab710(0x1803020e0,10,&UNK_1801540a8,dVar17);
            lVar13 = (**(code **)(*plVar2 + 0x538))(plVar2,0x1803020e0);
            if (lVar13 == 0) {
              *(undefined8 *)(lVar12 + 0x180301ed8) = 0;
            }
            else {
              lVar13 = (**(code **)(*plVar2 + 0xa8))(plVar2,lVar13);
              *(longlong *)(lVar12 + 0x180301ed8) = lVar13;
              if (lVar13 != 0) {
                uVar8 = FUN_180027560(*plVar1,lStack_d0,lVar13);
                uVar14 = 0xffff0000;
                if (dVar3 < dVar17) {
                  uVar14 = 0xffffff00;
                }
                *(undefined4 *)(lVar12 + 0x180301ee0) = uVar8;
                if (dVar4 < dVar17) {
                  uVar14 = 0xffffffff;
                }
                *(undefined4 *)(lVar12 + 0x180301ee4) = uVar14;
              }
            }
            if (_DAT_180301ea0 == 10) {
              return;
            }
          }
LAB_18003f05a:
          iVar6 = iVar6 + 1;
          iVar7 = FUN_180024e50(*plVar1,uVar10);
        } while (iVar6 < iVar7);
      }
    }
  }
  return;
}

// UI RVA 0x3f2a0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3f2a0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003f2a0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_1801540ae);
  FUN_18000cf30(param_2,param_1,0x1802f1650);
  FUN_18000cf30(param_2,param_1,0x1802f1688);
  FUN_180013e90(param_1,param_2,&UNK_1801540b3);
  FUN_18000cef0(param_2,param_1,0x1802f16c0);
  FUN_18000cef0(param_2,param_1,0x1802f16e0);
  FUN_18000cef0(param_2,param_1,0x1802f1700);
  FUN_180013e90(param_1,param_2,&UNK_1801540bc);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802f1730,0x1802f1720,&DAT_1802f1738);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x3f360; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3f360; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003f360(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c450(param_1,&UNK_1801540c7,0x1802f1650);
  FUN_18000c450(param_1,&UNK_1801540cd,0x1802f1688);
  FUN_18000c3b0(param_1,&UNK_1801540d4,0x1802f16c0);
  FUN_18000c3b0(param_1,&UNK_1801540df,0x1802f16e0);
  FUN_18000c3b0(param_1,&UNK_1801540ed,0x1802f1700);
  uVar1 = uRam00000001802f1739;
  uVar2 = DAT_1802f1738;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_1801540f8,DAT_1802f1738);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802f1738;
      break;
    case 2:
      uRam00000001802f1739 = DAT_1802f1738;
      break;
    case 3:
      uVar2 = uRam00000001802f1739;
    }
  }
  DAT_1802f1738 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x3f400; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3f400; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003f400(void)

{
  undefined8 *puVar1;
  longlong lVar2;
  longlong lVar3;
  ulonglong uVar4;
  
  if (_DAT_1803020f0 != 0) {
    lVar3 = 0x48;
    uVar4 = 0;
    do {
      lVar2 = _DAT_180302100;
      puVar1 = (undefined8 *)(_DAT_180302100 + -0x40 + lVar3);
      *puVar1 = 0;
      puVar1[1] = 0;
      func_0x00018013cf70(*(undefined8 *)(lVar2 + -0x30 + lVar3));
      puVar1 = (undefined8 *)(lVar2 + -0x30 + lVar3);
      *puVar1 = 0;
      puVar1[1] = 0;
      *(undefined8 *)(lVar2 + -0x20 + lVar3) = 0;
      func_0x00018013cf70(*(undefined8 *)(lVar2 + -0x18 + lVar3));
      puVar1 = (undefined8 *)(lVar2 + -0x18 + lVar3);
      *puVar1 = 0;
      puVar1[1] = 0;
      *(undefined8 *)(lVar2 + -8 + lVar3) = 0;
      func_0x00018013cf70(*(undefined8 *)(lVar2 + lVar3));
      *(undefined8 *)(lVar2 + lVar3) = 0;
      uVar4 = uVar4 + 1;
      lVar3 = lVar3 + 0x50;
    } while (uVar4 < _DAT_1803020f0);
  }
  _DAT_1803020f0 = 0;
  uRam00000001803020f8 = 0;
  func_0x00018013cf70(_DAT_180302100);
  _DAT_180302100 = 0;
  return;
}

