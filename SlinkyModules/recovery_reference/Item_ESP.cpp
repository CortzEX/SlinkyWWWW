// Recovered decompiler view: Item ESP
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x40de0, 0x41a90); proximity does not prove ownership.

// CALLBACK RVA 0x40de0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/item_esp/item_esp.c
// Differential report: analysis/module_behavior_recovery/item_esp/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x40de0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180040de0(longlong param_1)

{
  float fVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  double dVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  longlong lVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  int *piVar10;
  undefined4 *puVar11;
  ulonglong uVar12;
  ulonglong uVar13;
  undefined4 uVar14;
  uint uVar15;
  double dVar16;
  double dVar17;
  undefined4 uStack_138;
  undefined4 uStack_134;
  undefined4 uStack_130;
  undefined4 uStack_12c;
  undefined8 uStack_128;
  longlong lStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  double dStack_108;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  double dStack_e8;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  double dStack_c8;
  
  if (_DAT_180302130 != 0) {
    (*(code *)*_DAT_18013e458)(0xbe2);
    fVar1 = *(float *)(param_1 + 0x28);
    lStack_120 = param_1;
    FUN_1800293c0();
    uVar5 = _DAT_18015432c;
    uVar14 = _DAT_180154328;
    dVar4 = _DAT_180154320;
    puVar3 = _DAT_180150cb8;
    puVar2 = _DAT_18013e448;
    if (_DAT_180302130 != 0) {
      puVar11 = (undefined4 *)0x180302178;
      uVar12 = 0;
      do {
        dStack_108 = *(double *)(puVar11 + -10);
        uStack_118 = *(undefined8 *)(puVar11 + -0xe);
        uStack_110 = *(undefined8 *)(puVar11 + -0xc);
        dStack_e8 = *(double *)(puVar11 + -4);
        uStack_f8 = *(undefined8 *)(puVar11 + -8);
        uStack_f0 = *(undefined8 *)(puVar11 + -6);
        FUN_180009460(&uStack_d8,&uStack_118,&uStack_f8,SUB84((double)fVar1,0));
        dStack_e8 = dStack_c8;
        uStack_f8 = CONCAT44(uStack_d4,uStack_d8);
        uStack_f0 = CONCAT44(uStack_cc,uStack_d0);
        uStack_128 = *(undefined8 *)(param_1 + 0x18);
        uStack_138 = *(undefined4 *)(param_1 + 8);
        uStack_134 = *(undefined4 *)(param_1 + 0xc);
        uStack_130 = *(undefined4 *)(param_1 + 0x10);
        uStack_12c = *(undefined4 *)(param_1 + 0x14);
        FUN_1800093d0(&uStack_118,&uStack_f8,&uStack_138);
        uStack_d8 = (undefined4)uStack_118;
        uStack_d4 = uStack_118._4_4_;
        uStack_d0 = (undefined4)uStack_110;
        uStack_cc = uStack_110._4_4_;
        dStack_c8 = dStack_108;
        (*(code *)*_DAT_180150cc0)();
        dVar16 = (double)CONCAT44(uStack_cc,uStack_d0) + dVar4;
        (*(code *)*_DAT_180150cd8)
                  ((float)(double)CONCAT44(uStack_d4,uStack_d8),
                   CONCAT44((int)((ulonglong)dVar16 >> 0x20),(float)dVar16),(float)dStack_c8);
        (*(code *)*_DAT_180150cd0)(uVar14,uVar14,uVar14);
        (*(code *)*puVar2)(puVar11[-2],puVar11[-1],*puVar11,uVar5);
        FUN_180029400();
        (*(code *)*puVar3)();
        uVar12 = uVar12 + 1;
        puVar11 = puVar11 + 0x16;
      } while (uVar12 < _DAT_180302130);
    }
    FUN_1800295a0();
    lVar7 = lStack_120;
    if (DAT_1802f1ca8 == '\x01') {
      puVar2 = *(undefined8 **)(lStack_120 + 0x20);
      uVar8 = FUN_180022d40(*puVar2,puVar2[3]);
      uVar9 = FUN_1800272a0(*puVar2,uVar8);
      uVar14 = FUN_180027200(*puVar2,uVar8);
      uVar15 = FUN_180027250(*puVar2,uVar8);
      fVar1 = *(float *)(lVar7 + 0x28);
      if (*(char *)(lVar7 + 0x2c) == '\x01') {
        FUN_1800277f0(*puVar2);
        FUN_1800278f0(*puVar2,_DAT_180154330,_DAT_180154330,_DAT_180154330,0x3f800000);
      }
      else {
        (*(code *)*_DAT_18013e458)(0xde1);
        (*(code *)*_DAT_180150ca0)(_DAT_180154330,_DAT_180154330,_DAT_180154330);
      }
      dVar16 = _DAT_180154358;
      uVar6 = _DAT_180154350;
      uVar5 = _DAT_180154330;
      dVar4 = _DAT_180154320;
      puVar3 = _DAT_180150cc8;
      if (_DAT_180302130 != 0) {
        uVar15 = uVar15 ^ _DAT_180154340;
        piVar10 = (int *)0x180302188;
        uVar13 = 0;
        uVar12 = _DAT_180302130;
        do {
          if (*(longlong *)(piVar10 + -2) != 0) {
            dStack_108 = *(double *)(piVar10 + -0xe);
            uStack_118 = *(undefined8 *)(piVar10 + -0x12);
            uStack_110 = *(undefined8 *)(piVar10 + -0x10);
            dStack_e8 = *(double *)(piVar10 + -8);
            uStack_f8 = *(undefined8 *)(piVar10 + -0xc);
            uStack_f0 = *(undefined8 *)(piVar10 + -10);
            FUN_180009460(&uStack_d8,&uStack_118,&uStack_f8,SUB84((double)fVar1,0));
            dStack_e8 = dStack_c8;
            uStack_f8 = CONCAT44(uStack_d4,uStack_d8);
            uStack_f0 = CONCAT44(uStack_cc,uStack_d0);
            uStack_128 = *(undefined8 *)(param_1 + 0x18);
            uStack_138 = *(undefined4 *)(param_1 + 8);
            uStack_134 = *(undefined4 *)(param_1 + 0xc);
            uStack_130 = *(undefined4 *)(param_1 + 0x10);
            uStack_12c = *(undefined4 *)(param_1 + 0x14);
            FUN_1800093d0(&uStack_118,&uStack_f8,&uStack_138);
            uStack_d8 = (undefined4)uStack_118;
            uStack_d4 = uStack_118._4_4_;
            uStack_d0 = (undefined4)uStack_110;
            uStack_cc = uStack_110._4_4_;
            dStack_c8 = dStack_108;
            (*(code *)*_DAT_180150cc0)();
            dVar17 = (double)CONCAT44(uStack_cc,uStack_d0) + dVar4;
            (*(code *)*_DAT_180150cd8)
                      ((float)(double)CONCAT44(uStack_d4,uStack_d8),
                       CONCAT44((int)((ulonglong)dVar17 >> 0x20),(float)dVar17),(float)dStack_c8);
            (*(code *)*puVar3)(uVar15,0,uVar5,0);
            (*(code *)*puVar3)(uVar14,uVar5,0,0);
            (*(code *)*_DAT_180150cd0)(uVar6,uVar6,uVar6);
            FUN_180027590(*puVar2,uVar9,*(undefined8 *)(piVar10 + -2),
                          (float)((double)-*piVar10 * dVar16),0xc0800000,0xffffffff,1);
            (*(code *)*_DAT_180150cb8)();
            uVar12 = _DAT_180302130;
          }
          uVar13 = uVar13 + 1;
          piVar10 = piVar10 + 0x16;
        } while (uVar13 < uVar12);
      }
      if (*(char *)(lStack_120 + 0x2c) == '\0') {
        (*(code *)*_DAT_18013e450)(0xde1);
      }
      else {
        FUN_180027820(*puVar2);
      }
    }
  }
  return;
}

// CALLBACK RVA 0x41250; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/item_esp_update/item_esp_update.c
// Differential report: analysis/module_behavior_recovery/item_esp_update/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x41250; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180041250(longlong param_1)

{
  longlong *plVar1;
  longlong *plVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  longlong lVar9;
  longlong lVar10;
  longlong lVar11;
  ulonglong uVar12;
  byte *pbVar13;
  ulonglong uVar14;
  longlong *plVar15;
  longlong lVar16;
  ulonglong uVar17;
  double dVar18;
  double dVar19;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined8 uStack_c0;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined8 uStack_a8;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  longlong lStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  
  plVar1 = *(longlong **)(param_1 + 8);
  if (_DAT_180302130 != 0) {
    plVar2 = *(longlong **)(*plVar1 + 8);
    plVar15 = (longlong *)0x180302180;
    uVar12 = 0;
    uVar14 = _DAT_180302130;
    do {
      if (*plVar15 != 0) {
        (**(code **)(*plVar2 + 0xb0))(plVar2);
        *plVar15 = 0;
        uVar14 = _DAT_180302130;
      }
      uVar12 = uVar12 + 1;
      plVar15 = plVar15 + 0xb;
    } while (uVar12 < uVar14);
  }
  _DAT_180302130 = 0;
  if (plVar1[4] != 0) {
    FUN_180023030(&uStack_d0,*plVar1,plVar1[5]);
    uVar7 = FUN_180024620(*plVar1,plVar1[4]);
    iVar4 = FUN_180024e50(*plVar1,uVar7);
    if (0 < iVar4) {
      iVar4 = 0;
      do {
        uVar8 = FUN_180024e80(*plVar1,uVar7,iVar4);
        lVar9 = FUN_180027cf0(*plVar1,uVar8);
        if ((lVar9 != 0) && (cVar3 = FUN_1800237b0(*plVar1,lVar9), cVar3 == '\0')) {
          FUN_180023030(&uStack_98,*plVar1,lVar9);
          uStack_68 = uStack_88;
          uStack_78 = uStack_98;
          uStack_70 = uStack_90;
          uStack_a8 = uStack_c0;
          uStack_b8 = uStack_d0;
          uStack_b4 = uStack_cc;
          uStack_b0 = uStack_c8;
          uStack_ac = uStack_c4;
          dVar18 = (double)FUN_1800094b0(&uStack_78,&uStack_b8);
          if (dVar18 <= (double)(_DAT_1802f1ce0 * _DAT_1802f1ce0)) {
            lVar16 = _DAT_180302130 * 0x58;
            lVar11 = *plVar1;
            lVar10 = FUN_180027d30(lVar11,lVar9);
            if (lVar10 != 0) {
              iVar5 = FUN_180025d70(lVar11,lVar10);
              lStack_80 = CONCAT44(lStack_80._4_4_,iVar5);
              if ((0 < iVar5) && (lVar10 = FUN_180025d10(lVar11,lVar10), lVar10 != 0)) {
                uVar6 = FUN_180025c50(lVar11,lVar10);
                uStack_78 = CONCAT44(uStack_78._4_4_,uVar6);
                if (_DAT_1803043b0 == 0) {
                  lVar11 = 0;
LAB_1800414e9:
                  if (DAT_1802f1d20 == '\0') goto LAB_1800413b0;
                }
                else {
                  lVar11 = func_0x00018013d0e0(&uStack_78,_DAT_1803043b0,_DAT_1803043a0,0x18,
                                               FUN_180041830);
                  if (lVar11 == 0) goto LAB_1800414e9;
                }
                if (lVar11 == 0) {
                  lVar11 = 0x1802f1ce8;
                }
                *(undefined4 *)(lVar16 + 0x180302178) = *(undefined4 *)(lVar11 + 0x10);
                *(undefined8 *)(lVar16 + 0x180302170) = *(undefined8 *)(lVar11 + 8);
                *(undefined4 *)(lVar16 + 0x18030218c) = (undefined4)uStack_78;
                *(char *)(lVar16 + 0x180302190) = (char)lStack_80;
                *(undefined8 *)(lVar16 + 0x180302168) = uStack_88;
                *(undefined4 *)(lVar16 + 0x180302158) = (undefined4)uStack_98;
                *(undefined4 *)(lVar16 + 0x18030215c) = uStack_98._4_4_;
                *(undefined4 *)(lVar16 + 0x180302160) = (undefined4)uStack_90;
                *(undefined4 *)(lVar16 + 0x180302164) = uStack_90._4_4_;
                FUN_1800230d0(&uStack_78,*plVar1,lVar9);
                *(undefined8 *)(lVar16 + 0x180302150) = uStack_68;
                *(undefined4 *)(lVar16 + 0x180302140) = (undefined4)uStack_78;
                *(undefined4 *)(lVar16 + 0x180302144) = uStack_78._4_4_;
                *(undefined4 *)(lVar16 + 0x180302148) = (undefined4)uStack_70;
                *(undefined4 *)(lVar16 + 0x18030214c) = uStack_70._4_4_;
                _DAT_180302130 = _DAT_180302130 + 1;
                if (_DAT_180302130 == 100) break;
              }
            }
          }
        }
LAB_1800413b0:
        iVar4 = iVar4 + 1;
        iVar5 = FUN_180024e50(*plVar1,uVar7);
      } while (iVar4 < iVar5);
    }
    if ((DAT_1802f1ca8 == '\x01') && (_DAT_180302130 != 0)) {
      uVar7 = FUN_180022d40(*plVar1,plVar1[3]);
      lStack_80 = FUN_1800272a0(*plVar1,uVar7);
      dVar18 = _DAT_180154360;
      if ((lStack_80 != 0) && (_DAT_180302130 != 0)) {
        uVar14 = 0;
        do {
          lVar9 = uVar14 * 0x58;
          uVar12 = (ulonglong)*(byte *)(lVar9 + 0x180302190);
          if (uVar12 != 0) {
            pbVar13 = (byte *)0x180302190;
            uVar17 = 0;
            do {
              if ((uVar14 != uVar17) && (*(int *)(lVar9 + 0x18030218c) == *(int *)(pbVar13 + -4))) {
                uStack_88 = *(undefined8 *)(lVar9 + 0x180302168);
                uStack_98 = *(undefined8 *)(lVar9 + 0x180302158);
                uStack_90 = *(undefined8 *)(lVar9 + 0x180302160);
                uStack_68 = *(undefined8 *)(pbVar13 + -0x28);
                uStack_78 = *(undefined8 *)(pbVar13 + -0x38);
                uStack_70 = *(undefined8 *)(pbVar13 + -0x30);
                dVar19 = (double)FUN_1800094b0(&uStack_98,&uStack_78);
                if (dVar19 < dVar18) {
                  uVar12 = uVar12 + *pbVar13;
                  *pbVar13 = 0;
                }
              }
              uVar17 = uVar17 + 1;
              pbVar13 = pbVar13 + 0x58;
            } while (uVar17 < _DAT_180302130);
            uVar17 = 99;
            if (uVar12 < 99) {
              uVar17 = uVar12;
            }
            *(char *)(lVar9 + 0x180302190) = (char)uVar17;
            if (1 < uVar12) {
              lVar11 = *plVar1;
              FUN_1800ab710(0x1803043b8,5,&UNK_1801543cb);
              plVar2 = *(longlong **)(lVar11 + 8);
              lVar10 = (**(code **)(*plVar2 + 0x538))(plVar2,0x1803043b8);
              if (lVar10 != 0) {
                lVar10 = (**(code **)(*plVar2 + 0xa8))(plVar2,lVar10);
                *(longlong *)(lVar9 + 0x180302180) = lVar10;
                if (lVar10 != 0) {
                  uVar6 = FUN_180027560(lVar11,lStack_80,lVar10);
                  *(undefined4 *)(lVar9 + 0x180302188) = uVar6;
                }
                goto LAB_18004156f;
              }
            }
            *(undefined8 *)(lVar9 + 0x180302180) = 0;
          }
LAB_18004156f:
          uVar14 = uVar14 + 1;
        } while (uVar14 < _DAT_180302130);
      }
    }
  }
  return;
}

// CALLBACK RVA 0x416c0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/item_esp/item_esp.c
// Differential report: analysis/module_behavior_recovery/item_esp/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x416c0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800416c0(void)

{
  _DAT_1803043a0 = 0;
  uRam00000001803043a8 = 0;
  func_0x00018013cf70(_DAT_1803043b0);
  _DAT_1803043b0 = 0;
  return;
}

// UI RVA 0x41700; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x41700; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180041700(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  undefined8 unaff_RBP;
  
  FUN_180013e90(param_1,param_2,&UNK_1801543ce);
  FUN_18000cf30(param_2,param_1,0x1802f1cb0);
  FUN_180013e90(param_1,param_2,&UNK_1801543d3);
  FUN_18000cef0(param_2,param_1,0x1802f1c90);
  FUN_18000d0e0(param_2,param_1,0x1802f1d28);
  FUN_18000cef0(param_2,param_1,0x1802f1d08);
  if (DAT_1802f1d20 != '\x01') {
    return;
  }
  cVar1 = FUN_1800155a0(param_1,param_2,uRam00000001802f1ce8,0x1802f1cf0,unaff_RBP);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x417b0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x417b0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_1800417b0(undefined8 *param_1)

{
  undefined8 uVar1;
  longlong lVar2;
  longlong lVar3;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  float fStack_34;
  undefined8 uStack_30;
  float fStack_28;
  
  uStack_3c = 1;
  FUN_18000c450(param_1,&UNK_1801543f8,0x1802f1cb0);
  uStack_3c = 1;
  FUN_18000c3b0(param_1,&UNK_1801543fe,0x1802f1c90);
  uStack_3c = 1;
  FUN_18000ca00(param_1,&UNK_180154409,0x1802f1d28);
  uStack_3c = 1;
  FUN_18000c3b0(param_1,&UNK_180154417,0x1802f1d08);
  if (*(char *)((longlong)param_1 + 0xc) == '\0') {
    switch(*(undefined4 *)(param_1 + 1)) {
    case 0:
      uVar1 = FUN_18004e4d0(*param_1);
      fStack_28 = fRam00000001802f1d04;
      uStack_30 = uRam00000001802f1cfc;
      FUN_18000c910(&uStack_3c,uVar1,&uStack_30);
      fRam00000001802f1cf8 = fStack_34;
      uRam00000001802f1cf0 = CONCAT44(uStack_38,uStack_3c);
      break;
    case 1:
      lVar2 = FUN_18004f480(*param_1,&UNK_180154425);
      if (lVar2 == 0) {
        *(undefined1 *)((longlong)param_1 + 0xc) = 1;
      }
      else {
        lVar3 = FUN_18004eeb0(lVar2,&UNK_18013ec41,(double)(float)uRam00000001802f1cf0);
        *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar3 == 0;
        lVar3 = FUN_18004eeb0(lVar2,&UNK_18013ec43,(double)uRam00000001802f1cf0._4_4_);
        *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar3 == 0;
        lVar2 = FUN_18004eeb0(lVar2,&UNK_18013ec45,(double)fRam00000001802f1cf8);
        *(byte *)((longlong)param_1 + 0xc) = lVar2 == 0 | *(byte *)((longlong)param_1 + 0xc);
      }
      break;
    case 2:
      fRam00000001802f1d04 = fRam00000001802f1cf8;
      uRam00000001802f1cfc = uRam00000001802f1cf0;
      break;
    case 3:
      fRam00000001802f1cf8 = fRam00000001802f1d04;
      uRam00000001802f1cf0 = uRam00000001802f1cfc;
    }
  }
  return;
}

// CANDIDATE_LOCAL RVA 0x41830; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x41830; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


int FUN_180041830(int *param_1,longlong param_2)

{
  return *param_1 - *(int *)(param_2 + 0x14);
}

// CANDIDATE_LOCAL RVA 0x41840; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x41840; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180041840(longlong param_1,byte param_2)

{
  ulonglong uVar1;
  
  uVar1 = func_0x0001800ab840();
  if ((uVar1 < 100) &&
     (((byte)((param_2 & 0xdf) + 0xbf) < 0x1a || (param_2 == 0x20 || (byte)(param_2 - 0x30) < 10))))
  {
    *(byte *)(param_1 + uVar1) = param_2;
  }
  return;
}

// CANDIDATE_LOCAL RVA 0x41890; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x41890; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


undefined8 FUN_180041890(undefined8 *param_1)

{
  return *param_1;
}

// CANDIDATE_LOCAL RVA 0x418a0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x418a0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


undefined8 FUN_1800418a0(longlong param_1,longlong param_2)

{
  return *(undefined8 *)(*(longlong *)(param_1 + 0x10) + param_2 * 0x18);
}

// CANDIDATE_LOCAL RVA 0x418c0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x418c0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


longlong FUN_1800418c0(longlong param_1,longlong param_2)

{
  return *(longlong *)(param_1 + 0x10) + 8 + param_2 * 0x18;
}

// CANDIDATE_LOCAL RVA 0x418e0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x418e0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_1800418e0(longlong *param_1,undefined8 param_2,undefined8 *param_3)

{
  undefined4 uVar1;
  undefined8 uVar2;
  int iVar3;
  undefined4 uVar4;
  longlong lVar5;
  undefined8 uVar6;
  int *piVar7;
  longlong lVar8;
  longlong lVar9;
  int iStack_3c;
  
  iStack_3c = FUN_18000e3c0(param_2);
  if ((iStack_3c == -1) ||
     ((_DAT_1803043b0 != 0 &&
      (lVar5 = func_0x00018013d0e0(&iStack_3c,_DAT_1803043b0,_DAT_1803043a0,0x18,FUN_180041830),
      lVar5 != 0)))) {
    uVar4 = 0;
  }
  else {
    lVar5 = *param_1;
    if (lVar5 == 0) {
      lVar9 = 0;
    }
    else {
      piVar7 = (int *)(param_1[2] + 0x14);
      lVar8 = 0;
      do {
        lVar9 = lVar8;
        if (iStack_3c <= *piVar7) break;
        lVar8 = lVar8 + 1;
        piVar7 = piVar7 + 6;
        lVar9 = lVar5;
      } while (lVar5 != lVar8);
    }
    uVar6 = FUN_18000e420(iStack_3c);
    iVar3 = iStack_3c;
    uVar2 = *param_3;
    uVar1 = *(undefined4 *)(param_3 + 1);
    uVar4 = FUN_18000e310(&DAT_1803043b0,0x18,_DAT_1803043a0,0x1803043a8);
    lVar5 = _DAT_1803043b0;
    if ((char)uVar4 != '\0') {
      func_0x0001800ab910(_DAT_1803043b0 + lVar9 * 0x18 + 0x18,_DAT_1803043b0 + lVar9 * 0x18,
                          (_DAT_1803043a0 - lVar9) * 0x18);
      *(undefined8 *)(lVar5 + lVar9 * 0x18) = uVar6;
      *(undefined8 *)(lVar5 + 8 + lVar9 * 0x18) = uVar2;
      *(undefined4 *)(lVar5 + 0x10 + lVar9 * 0x18) = uVar1;
      *(int *)(lVar5 + 0x14 + lVar9 * 0x18) = iVar3;
      _DAT_1803043a0 = _DAT_1803043a0 + 1;
    }
  }
  return uVar4;
}

// CANDIDATE_LOCAL RVA 0x41a20; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x41a20; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180041a20(longlong *param_1,longlong param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  longlong lVar16;
  longlong lVar17;
  ulonglong uVar18;
  undefined8 *puVar19;
  longlong lVar20;
  ulonglong uVar21;
  ulonglong uVar22;
  
  lVar20 = *param_1;
  puVar1 = (undefined8 *)(param_1[2] + param_2 * 0x18);
  *param_1 = lVar20 + -1;
  lVar16 = param_1[2] + param_2 * 0x18;
  puVar19 = (undefined8 *)(lVar16 + 0x18);
  param_2 = (lVar20 + -1) - param_2;
  uVar18 = param_2 * 0x18;
  if (uVar18 < 0x10) {
    if (uVar18 < 4) {
      if (uVar18 != 0) {
        uVar4 = *(undefined1 *)((longlong)puVar19 + (uVar18 >> 1));
        uVar5 = *(undefined1 *)(lVar16 + 0x17 + uVar18);
        *(undefined1 *)puVar1 = *(undefined1 *)puVar19;
        *(undefined1 *)((longlong)puVar1 + (uVar18 >> 1)) = uVar4;
        *(undefined1 *)((longlong)puVar1 + (uVar18 - 1)) = uVar5;
      }
    }
    else {
      uVar21 = (ulonglong)((uint)(uVar18 >> 1) & 4);
      lVar20 = (uVar18 - 4) - uVar21;
      uVar6 = *(undefined4 *)((longlong)puVar19 + uVar21);
      uVar7 = *(undefined4 *)((longlong)puVar19 + lVar20);
      uVar8 = *(undefined4 *)(lVar16 + 0x14 + uVar18);
      *(undefined4 *)puVar1 = *(undefined4 *)puVar19;
      *(undefined4 *)((longlong)puVar1 + uVar21) = uVar6;
      *(undefined4 *)((longlong)puVar1 + lVar20) = uVar7;
      *(undefined4 *)((longlong)puVar1 + (uVar18 - 4)) = uVar8;
    }
  }
  else if (uVar18 < 0x40) {
    uVar21 = (ulonglong)((uint)(uVar18 >> 1) & 0x10);
    lVar20 = (uVar18 - 0x10) - uVar21;
    uVar9 = *(undefined8 *)(lVar16 + 0x20);
    uVar10 = *(undefined8 *)((longlong)puVar19 + uVar21);
    uVar11 = ((undefined8 *)((longlong)puVar19 + uVar21))[1];
    puVar2 = (undefined8 *)((longlong)puVar19 + lVar20);
    uVar12 = *puVar2;
    uVar13 = puVar2[1];
    puVar2 = (undefined8 *)(lVar16 + 8 + uVar18);
    uVar14 = *puVar2;
    uVar15 = puVar2[1];
    *puVar1 = *puVar19;
    puVar1[1] = uVar9;
    *(undefined8 *)((longlong)puVar1 + uVar21) = uVar10;
    ((undefined8 *)((longlong)puVar1 + uVar21))[1] = uVar11;
    puVar19 = (undefined8 *)((longlong)puVar1 + lVar20);
    *puVar19 = uVar12;
    puVar19[1] = uVar13;
    puVar1[param_2 * 3 + -2] = uVar14;
    (puVar1 + param_2 * 3 + -2)[1] = uVar15;
  }
  else if (puVar19 < puVar1) {
    puVar2 = (undefined8 *)(lVar16 + 8 + uVar18);
    uVar9 = *puVar2;
    uVar10 = puVar2[1];
    uVar11 = *puVar19;
    uVar12 = *(undefined8 *)(lVar16 + 0x20);
    uVar18 = (ulonglong)(puVar1 + param_2 * 3) & 0xfffffffffffffff0;
    uVar21 = uVar18 - (longlong)puVar1;
    if (0xf < uVar21) {
      uVar22 = uVar21 >> 4;
      lVar16 = 1;
      if (2 < uVar22 - 1) {
        lVar20 = -0x10;
        do {
          puVar2 = (undefined8 *)((longlong)puVar19 + lVar20 + uVar21);
          uVar13 = puVar2[1];
          *(undefined8 *)(uVar18 + lVar20) = *puVar2;
          ((undefined8 *)(uVar18 + lVar20))[1] = uVar13;
          puVar2 = (undefined8 *)((longlong)puVar19 + lVar20 + (uVar21 - 0x10));
          uVar13 = puVar2[1];
          puVar3 = (undefined8 *)((uVar18 - 0x10) + lVar20);
          *puVar3 = *puVar2;
          puVar3[1] = uVar13;
          puVar2 = (undefined8 *)((longlong)puVar19 + lVar20 + (uVar21 - 0x20));
          uVar13 = puVar2[1];
          puVar3 = (undefined8 *)((uVar18 - 0x20) + lVar20);
          *puVar3 = *puVar2;
          puVar3[1] = uVar13;
          puVar2 = (undefined8 *)((longlong)puVar19 + lVar20 + (uVar21 - 0x30));
          uVar13 = puVar2[1];
          puVar3 = (undefined8 *)((uVar18 - 0x30) + lVar20);
          *puVar3 = *puVar2;
          puVar3[1] = uVar13;
          lVar20 = lVar20 + -0x40;
          lVar17 = lVar16 - (uVar22 & 0xfffffffffffffffc);
          lVar16 = lVar16 + 4;
        } while (lVar17 != -3);
      }
      if ((uVar22 & 3) != 0) {
        lVar20 = 0;
        do {
          puVar2 = (undefined8 *)((longlong)puVar19 + lVar20 + uVar21 + lVar16 * -0x10);
          uVar13 = puVar2[1];
          puVar3 = (undefined8 *)(uVar18 + lVar16 * -0x10 + lVar20);
          *puVar3 = *puVar2;
          puVar3[1] = uVar13;
          lVar20 = lVar20 + -0x10;
        } while ((ulonglong)(((uint)uVar22 & 3) << 4) + lVar20 != 0);
      }
    }
    *puVar1 = uVar11;
    puVar1[1] = uVar12;
    puVar1[param_2 * 3 + -2] = uVar9;
    (puVar1 + param_2 * 3 + -2)[1] = uVar10;
  }
  else {
    uVar9 = *puVar19;
    uVar10 = *(undefined8 *)(lVar16 + 0x20);
    puVar2 = (undefined8 *)(lVar16 + 8 + uVar18);
    uVar11 = *puVar2;
    uVar12 = puVar2[1];
    uVar21 = (ulonglong)((uint)puVar19 & 0xf);
    uVar18 = (uVar18 + uVar21) - 0x10 >> 4;
    if (uVar18 - 1 < 3) {
      uVar22 = 0;
    }
    else {
      uVar22 = 0;
      lVar20 = -uVar21;
      do {
        lVar17 = lVar20 + 0x40;
        puVar2 = (undefined8 *)(lVar16 + -0x18 + lVar17);
        uVar13 = puVar2[1];
        puVar3 = (undefined8 *)((longlong)puVar1 + lVar20 + 0x10);
        *puVar3 = *puVar2;
        puVar3[1] = uVar13;
        puVar2 = (undefined8 *)(lVar16 + -8 + lVar17);
        uVar13 = puVar2[1];
        puVar3 = (undefined8 *)((longlong)puVar1 + lVar20 + 0x20);
        *puVar3 = *puVar2;
        puVar3[1] = uVar13;
        puVar2 = (undefined8 *)(lVar16 + 8 + lVar17);
        uVar13 = puVar2[1];
        puVar3 = (undefined8 *)((longlong)puVar1 + lVar20 + 0x30);
        *puVar3 = *puVar2;
        puVar3[1] = uVar13;
        uVar13 = ((undefined8 *)((longlong)puVar19 + lVar17))[1];
        *(undefined8 *)((longlong)puVar1 + lVar17) = *(undefined8 *)((longlong)puVar19 + lVar17);
        ((undefined8 *)((longlong)puVar1 + lVar17))[1] = uVar13;
        uVar22 = uVar22 + 4;
        lVar20 = lVar17;
      } while ((uVar18 & 0xfffffffffffffffc) != uVar22);
    }
    if ((uVar18 & 3) != 0) {
      lVar16 = uVar22 * 0x10 - uVar21;
      uVar21 = 0;
      do {
        puVar2 = (undefined8 *)((longlong)puVar19 + uVar21 + lVar16 + 0x10);
        uVar13 = puVar2[1];
        puVar3 = (undefined8 *)((longlong)puVar1 + uVar21 + lVar16 + 0x10);
        *puVar3 = *puVar2;
        puVar3[1] = uVar13;
        uVar21 = uVar21 + 0x10;
      } while (((uint)uVar18 & 3) << 4 != uVar21);
    }
    puVar1[param_2 * 3 + -2] = uVar11;
    (puVar1 + param_2 * 3 + -2)[1] = uVar12;
    *puVar1 = uVar9;
    puVar1[1] = uVar10;
  }
  return;
}

// CANDIDATE_LOCAL RVA 0x41a60; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x41a60; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180041a60(undefined8 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  func_0x00018013cf70(param_1[2]);
  param_1[2] = 0;
  return;
}

