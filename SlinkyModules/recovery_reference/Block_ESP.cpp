// Recovered decompiler view: Block ESP
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x3f4c0, 0x40de0); proximity does not prove ownership.

// CALLBACK RVA 0x3f4c0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/block_esp_lifecycle/block_esp_lifecycle.c
// Differential report: analysis/module_behavior_recovery/block_esp_lifecycle/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3f4c0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003f4c0(longlong param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  longlong lVar3;
  ulonglong uVar4;
  longlong lVar5;
  
  puVar2 = *(undefined8 **)(param_1 + 8);
  if ((*(char *)(puVar2 + 8) == '\x01') && (DAT_1802f19b0 != '\0')) {
    if (_DAT_1803020f0 != 0) {
      lVar5 = 0;
      uVar4 = 0;
      do {
        FUN_18003fcc0(_DAT_180302100 + lVar5);
        uVar4 = uVar4 + 1;
        lVar5 = lVar5 + 0x50;
      } while (uVar4 < _DAT_1803020f0);
    }
    DAT_1802f19b0 = '\0';
  }
  if (puVar2[4] == 0) {
    if (_DAT_1803020f0 != 0) {
      lVar5 = 0x48;
      uVar4 = 0;
      do {
        lVar3 = _DAT_180302100;
        puVar2 = (undefined8 *)(_DAT_180302100 + -0x40 + lVar5);
        *puVar2 = 0;
        puVar2[1] = 0;
        func_0x00018013cf70(*(undefined8 *)(lVar3 + -0x30 + lVar5));
        puVar2 = (undefined8 *)(lVar3 + -0x30 + lVar5);
        *puVar2 = 0;
        puVar2[1] = 0;
        *(undefined8 *)(lVar3 + -0x20 + lVar5) = 0;
        func_0x00018013cf70(*(undefined8 *)(lVar3 + -0x18 + lVar5));
        puVar2 = (undefined8 *)(lVar3 + -0x18 + lVar5);
        *puVar2 = 0;
        puVar2[1] = 0;
        *(undefined8 *)(lVar3 + -8 + lVar5) = 0;
        func_0x00018013cf70(*(undefined8 *)(lVar3 + lVar5));
        *(undefined8 *)(lVar3 + lVar5) = 0;
        uVar4 = uVar4 + 1;
        lVar5 = lVar5 + 0x50;
      } while (uVar4 < _DAT_1803020f0);
    }
    _DAT_1803020f0 = 0;
    uRam00000001803020f8 = 0;
    func_0x00018013cf70(_DAT_180302100);
    _DAT_180302100 = 0;
  }
  else {
    FUN_180026060(*puVar2);
    if (DAT_180302108 == '\x01') {
      if (_DAT_1803020f0 != 0) {
        lVar5 = 0x48;
        uVar4 = 0;
        do {
          lVar3 = _DAT_180302100;
          puVar1 = (undefined8 *)(_DAT_180302100 + -0x40 + lVar5);
          *puVar1 = 0;
          puVar1[1] = 0;
          func_0x00018013cf70(*(undefined8 *)(lVar3 + -0x30 + lVar5));
          puVar1 = (undefined8 *)(lVar3 + -0x30 + lVar5);
          *puVar1 = 0;
          puVar1[1] = 0;
          *(undefined8 *)(lVar3 + -0x20 + lVar5) = 0;
          func_0x00018013cf70(*(undefined8 *)(lVar3 + -0x18 + lVar5));
          puVar1 = (undefined8 *)(lVar3 + -0x18 + lVar5);
          *puVar1 = 0;
          puVar1[1] = 0;
          *(undefined8 *)(lVar3 + -8 + lVar5) = 0;
          func_0x00018013cf70(*(undefined8 *)(lVar3 + lVar5));
          *(undefined8 *)(lVar3 + lVar5) = 0;
          uVar4 = uVar4 + 1;
          lVar5 = lVar5 + 0x50;
        } while (uVar4 < _DAT_1803020f0);
      }
      _DAT_1803020f0 = 0;
      uRam00000001803020f8 = 0;
      func_0x00018013cf70(_DAT_180302100);
      _DAT_180302100 = 0;
      FUN_18003fed0(puVar2);
      DAT_180302108 = '\0';
    }
  }
  return;
}

// CALLBACK RVA 0x3f6a0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/block_esp_lifecycle/block_esp_lifecycle.c
// Differential report: analysis/module_behavior_recovery/block_esp_lifecycle/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3f6a0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003f6a0(longlong param_1)

{
  undefined8 *puVar1;
  longlong lVar2;
  int iVar3;
  undefined4 uVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  ulonglong uVar8;
  int iVar9;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined8 uStack_4c;
  undefined4 uStack_44;
  
  if (*(longlong *)(param_1 + 0x10) == 0x1802f1740) {
    if (*(char *)(param_1 + 0x18) == '\0') {
      if (_DAT_1803020f0 != 0) {
        lVar5 = 0x48;
        uVar8 = 0;
        do {
          lVar2 = _DAT_180302100;
          puVar1 = (undefined8 *)(_DAT_180302100 + -0x40 + lVar5);
          *puVar1 = 0;
          puVar1[1] = 0;
          uStack_60 = 0x18003f736;
          func_0x00018013cf70(*(undefined8 *)(lVar2 + -0x30 + lVar5));
          puVar1 = (undefined8 *)(lVar2 + -0x30 + lVar5);
          *puVar1 = 0;
          puVar1[1] = 0;
          *(undefined8 *)(lVar2 + -0x20 + lVar5) = 0;
          uStack_60 = 0x18003f74e;
          func_0x00018013cf70(*(undefined8 *)(lVar2 + -0x18 + lVar5));
          puVar1 = (undefined8 *)(lVar2 + -0x18 + lVar5);
          *puVar1 = 0;
          puVar1[1] = 0;
          *(undefined8 *)(lVar2 + -8 + lVar5) = 0;
          uStack_60 = 0x18003f765;
          func_0x00018013cf70(*(undefined8 *)(lVar2 + lVar5));
          *(undefined8 *)(lVar2 + lVar5) = 0;
          uVar8 = uVar8 + 1;
          lVar5 = lVar5 + 0x50;
        } while (uVar8 < _DAT_1803020f0);
      }
      _DAT_1803020f0 = 0;
      uRam00000001803020f8 = 0;
      uStack_60 = 0x18003f794;
      func_0x00018013cf70(_DAT_180302100);
      _DAT_180302100 = 0;
    }
    else {
      puVar1 = *(undefined8 **)(param_1 + 8);
      _DAT_180302128 = FUN_180040af0;
      if (**(int **)*puVar1 == 0) {
        _DAT_180302128 = FUN_180040980;
      }
      if (puVar1[4] != 0) {
        lVar5 = FUN_180024990(*puVar1,puVar1[4]);
        if (lVar5 != 0) {
          uVar6 = FUN_180024ab0(*puVar1,lVar5);
          iVar3 = FUN_180024e50(*puVar1,uVar6);
          if (0 < iVar3) {
            iVar9 = 0;
            do {
              uVar7 = FUN_180024e80(*puVar1,uVar6,iVar9);
              uVar4 = FUN_180024a10(*puVar1,uVar7);
              uStack_50 = FUN_180024a30(*puVar1,uVar7);
              uStack_68 = *puVar1;
              uStack_60 = puVar1[4];
              uStack_58 = 1;
              uStack_4c = 0;
              uStack_44 = 0;
              uStack_54 = uVar4;
              FUN_180040420(&uStack_68);
              iVar9 = iVar9 + 1;
            } while (iVar3 != iVar9);
          }
        }
        return;
      }
    }
  }
  return;
}

// CALLBACK RVA 0x3f7b0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/block_esp_render/block_esp_render.c
// Differential report: analysis/module_behavior_recovery/block_esp_render/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3f7b0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003f7b0(longlong param_1)

{
  double dVar1;
  double dVar2;
  undefined8 *puVar3;
  double dVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  longlong lVar7;
  longlong lVar8;
  ulonglong uVar9;
  double dVar10;
  float fVar11;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined8 uStack_c8;
  double dStack_b8;
  double dStack_b0;
  double dStack_a8;
  double adStack_a0 [12];
  
  puVar3 = _DAT_18014fd08;
  if (_DAT_1803020f0 != 0) {
    (*(code *)*_DAT_18014fd08)(0x8074);
    (*(code *)*puVar3)(0x8076);
    (*(code *)*_DAT_180150cb0)(_DAT_1802f19e8);
    dVar4 = _DAT_180154160;
    puVar3 = _DAT_180150cb8;
    uVar5 = (ulonglong)(_DAT_1802f1a20 * _DAT_180154158);
    uVar9 = 0x1000;
    if (DAT_1802f1a78 != '\0') {
      uVar9 = (longlong)(_DAT_1802f1a20 * _DAT_180154158 - _DAT_18015415c) & (longlong)uVar5 >> 0x3f
              | uVar5;
    }
    if (_DAT_1803020f0 != 0) {
      dVar2 = *(double *)(param_1 + 8) * _DAT_180154150;
      dVar1 = _DAT_180154150 * *(double *)(param_1 + 0x18);
      lVar7 = 0;
      uVar6 = 0;
      uVar5 = _DAT_1803020f0;
      lVar8 = _DAT_180302100;
      fVar11 = _DAT_1802f1a58;
      do {
        dVar10 = (double)func_0x00018013cfd0(SUB84(dVar2 - ((double)*(int *)(lVar8 + lVar7) + dVar4)
                                                   ,0),
                                             dVar1 - ((double)*(int *)(lVar8 + 4 + lVar7) + dVar4));
        if (dVar10 <= (double)fVar11) {
          (*(code *)*_DAT_180150cc0)();
          adStack_a0[0] = (double)(*(int *)(lVar8 + lVar7) << 4);
          adStack_a0[2] = (double)(*(int *)(lVar8 + 4 + lVar7) << 4);
          adStack_a0[1] = 0.0;
          uStack_c8 = *(undefined8 *)(param_1 + 0x18);
          uStack_d8 = *(undefined4 *)(param_1 + 8);
          uStack_d4 = *(undefined4 *)(param_1 + 0xc);
          uStack_d0 = *(undefined4 *)(param_1 + 0x10);
          uStack_cc = *(undefined4 *)(param_1 + 0x14);
          FUN_1800093d0(&dStack_b8,adStack_a0,&uStack_d8);
          (*(code *)*_DAT_180150cd8)((float)dStack_b8,(float)dStack_b0,(float)dStack_a8);
          (*(code *)*_DAT_18014fd10)(3,0x1406,0x10,*(undefined8 *)(lVar8 + 0x30 + lVar7));
          (*(code *)*_DAT_180154310)(3,0x1401,0x10,*(longlong *)(lVar8 + 0x30 + lVar7) + 0xc);
          uVar5 = *(ulonglong *)(lVar8 + 0x38 + lVar7);
          if (uVar9 < uVar5) {
            uVar5 = uVar9;
          }
          (*(code *)*_DAT_18014fd00)(1,uVar5,0x1403,*(undefined8 *)(lVar8 + 0x48 + lVar7));
          (*(code *)*puVar3)();
          uVar5 = _DAT_1803020f0;
          lVar8 = _DAT_180302100;
          fVar11 = _DAT_1802f1a58;
        }
        uVar6 = uVar6 + 1;
        lVar7 = lVar7 + 0x50;
      } while (uVar6 < uVar5);
    }
    puVar3 = _DAT_18014fcf8;
    (*(code *)*_DAT_18014fcf8)(0x8074);
    (*(code *)*puVar3)(0x8076);
  }
  return;
}

// CALLBACK RVA 0x3fa40; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/block_esp_lifecycle/block_esp_lifecycle.c
// Differential report: analysis/module_behavior_recovery/block_esp_lifecycle/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3fa40; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003fa40(longlong param_1)

{
  undefined8 *puVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  longlong *plVar4;
  ulonglong uVar5;
  char cVar6;
  char cVar7;
  char cVar8;
  int iVar9;
  longlong lVar10;
  longlong lVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  ulonglong uVar15;
  longlong lVar16;
  int *piVar17;
  int iVar18;
  short *psVar19;
  ulonglong uVar20;
  int iVar21;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  ulonglong uStack_60;
  
  if (*(uint *)(param_1 + 0x18) < 2) {
    uStack_b0 = *(undefined8 *)(param_1 + 0x1c);
    uStack_78 = 0;
    uStack_70 = 0;
    uStack_88 = 0;
    uStack_80 = 0;
    uStack_98 = 0;
    uStack_90 = 0;
    uStack_a8 = 0;
    uStack_a0 = 0;
    uStack_68 = 0;
    if ((_DAT_180302100 != 0) &&
       (lVar10 = func_0x00018013d0e0(&uStack_b0,_DAT_180302100,_DAT_1803020f0,0x50,FUN_180040960),
       lVar10 != 0)) {
      *(undefined8 *)(lVar10 + 8) = 0;
      *(undefined8 *)(lVar10 + 0x10) = 0;
      func_0x00018013cf70(*(undefined8 *)(lVar10 + 0x18));
      *(undefined8 *)(lVar10 + 0x18) = 0;
      *(undefined8 *)(lVar10 + 0x20) = 0;
      *(undefined8 *)(lVar10 + 0x28) = 0;
      func_0x00018013cf70(*(undefined8 *)(lVar10 + 0x30));
      *(undefined8 *)(lVar10 + 0x30) = 0;
      *(undefined8 *)(lVar10 + 0x38) = 0;
      *(undefined8 *)(lVar10 + 0x40) = 0;
      func_0x00018013cf70(*(undefined8 *)(lVar10 + 0x48));
      *(undefined8 *)(lVar10 + 0x48) = 0;
      lVar11 = _DAT_1803020f0 + ((ulonglong)(lVar10 - _DAT_180302100) >> 4) * 0x3333333333333333;
      _DAT_1803020f0 = _DAT_1803020f0 + -1;
      func_0x0001800ab910(lVar10,lVar10 + 0x50,(lVar11 + -1) * 0x50);
    }
    if (*(int *)(param_1 + 0x18) != 1) {
      return;
    }
    lVar10 = *(longlong *)(param_1 + 8);
    uVar3 = *(undefined4 *)(param_1 + 0x20);
    uStack_60 = CONCAT44(uStack_60._4_4_,*(undefined4 *)(param_1 + 0x1c));
    lVar11 = FUN_1800248f0(lVar10,*(undefined8 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x1c),
                           uVar3);
    if (lVar11 == 0) {
      return;
    }
    uStack_b0 = 0;
    plVar4 = *(longlong **)(lVar10 + 8);
    uVar12 = FUN_1800249f0(lVar10,lVar11);
    iVar21 = 0;
    do {
      lVar11 = (**(code **)(*plVar4 + 0x568))(plVar4,uVar12,iVar21);
      if (lVar11 != 0) {
        uVar13 = FUN_180024a50(lVar10,lVar11);
        uVar14 = (**(code **)(*plVar4 + 0x6f0))(plVar4,uVar13,0);
        (*_DAT_180302128)(uStack_60 & 0xffffffff,iVar21,uVar3,uVar14,&uStack_b0);
        (**(code **)(*plVar4 + 0x6f8))(plVar4,uVar13,uVar14,0);
      }
      iVar21 = iVar21 + 1;
    } while (iVar21 != 0x10);
    uVar15 = uStack_b0;
    if (uStack_b0 == 0) {
      return;
    }
  }
  else {
    if (*(uint *)(param_1 + 0x18) != 2) {
      return;
    }
    uStack_b0 = CONCAT44(uStack_b0._4_4_,*(undefined4 *)(param_1 + 0x28));
    if (_DAT_180302120 == 0) {
      uStack_60 = 0;
    }
    else {
      uStack_60 = func_0x00018013d0e0(&uStack_b0,_DAT_180302120,_DAT_180302110,0x18,FUN_180040410);
    }
    iVar21 = FUN_18000a2f0(*(undefined4 *)(param_1 + 0x1c));
    iVar9 = FUN_18000a2f0(*(undefined4 *)(param_1 + 0x24));
    uVar20 = CONCAT44(iVar9,iVar21);
    uStack_78 = 0;
    uStack_70 = 0;
    uStack_88 = 0;
    uStack_80 = 0;
    uStack_98 = 0;
    uStack_90 = 0;
    uStack_a8 = 0;
    uStack_a0 = 0;
    uStack_68 = 0;
    uStack_b0 = uVar20;
    if (_DAT_180302100 == 0) {
      uVar15 = 0;
    }
    else {
      uVar15 = func_0x00018013d0e0(&uStack_b0,_DAT_180302100,_DAT_1803020f0,0x50,FUN_180040960);
    }
    uVar3 = *(undefined4 *)(param_1 + 0x1c);
    cVar6 = FUN_18000a300(iVar21);
    cVar6 = (char)uVar3 - cVar6;
    uVar3 = *(undefined4 *)(param_1 + 0x24);
    cVar7 = FUN_18000a300(iVar9);
    uVar5 = uStack_b0;
    cVar7 = (char)uVar3 - cVar7;
    uVar2 = *(undefined1 *)(param_1 + 0x20);
    if (uVar15 == 0) {
      if (uStack_60 == 0) {
        return;
      }
      if (_DAT_1803020f0 == 0) {
        lVar10 = 0;
      }
      else {
        piVar17 = (int *)(_DAT_180302100 + 4);
        lVar11 = 0;
        do {
          iVar18 = iVar21 - piVar17[-1];
          if (iVar18 == 0) {
            iVar18 = iVar9 - *piVar17;
          }
          lVar10 = lVar11;
          if (iVar18 < 1) break;
          lVar11 = lVar11 + 1;
          piVar17 = piVar17 + 0x14;
          lVar10 = _DAT_1803020f0;
        } while (_DAT_1803020f0 != lVar11);
      }
      cVar8 = FUN_18000e310(&DAT_180302100,0x50,_DAT_1803020f0,0x1803020f8);
      lVar11 = _DAT_180302100;
      if (cVar8 == '\0') {
        return;
      }
      lVar16 = lVar10 * 0x50;
      func_0x0001800ab910(_DAT_180302100 + lVar16 + 0x50,_DAT_180302100 + lVar16,
                          (_DAT_1803020f0 - lVar10) * 0x50);
      *(ulonglong *)(lVar11 + lVar16) = uVar20;
      puVar1 = (undefined8 *)(lVar11 + 8 + lVar16);
      *puVar1 = 0;
      puVar1[1] = 0;
      puVar1 = (undefined8 *)(lVar11 + 0x18 + lVar16);
      *puVar1 = 0;
      puVar1[1] = 0;
      puVar1 = (undefined8 *)(lVar11 + 0x28 + lVar16);
      *puVar1 = 0;
      puVar1[1] = 0;
      puVar1 = (undefined8 *)(lVar11 + 0x38 + lVar16);
      *puVar1 = 0;
      puVar1[1] = 0;
      *(undefined8 *)(lVar11 + 0x48 + lVar16) = 0;
      _DAT_1803020f0 = _DAT_1803020f0 + 1;
      if (_DAT_180302100 == 0) {
        return;
      }
      uVar15 = _DAT_180302100 + lVar16;
      lVar10 = *(longlong *)(_DAT_180302100 + 8 + lVar16);
    }
    else {
      uStack_b0._0_2_ = CONCAT11(uVar2,cVar6);
      uStack_b0._3_5_ = SUB85(uVar5,3);
      uStack_b0._0_3_ = CONCAT12(cVar7,(short)uStack_b0);
      lVar10 = *(longlong *)(uVar15 + 8);
      if (lVar10 != 0) {
        psVar19 = *(short **)(uVar15 + 0x18);
        lVar16 = lVar10 << 4;
        lVar11 = lVar10;
        do {
          lVar16 = lVar16 + -0x10;
          if ((char)psVar19[1] == cVar7 && *psVar19 == (short)uStack_b0) {
            if (uStack_60 == 0) {
              *(longlong *)(uVar15 + 8) = lVar10 + -1;
              func_0x0001800ab910(psVar19,psVar19 + 8,lVar16);
              if (*(longlong *)(uVar15 + 8) == 0) {
                FUN_18003fc60(uVar15);
                lVar10 = _DAT_1803020f0 + (uVar15 - _DAT_180302100 >> 4) * 0x3333333333333333;
                _DAT_1803020f0 = _DAT_1803020f0 + -1;
                func_0x0001800ab910(uVar15,uVar15 + 0x50,(lVar10 + -1) * 0x50);
                return;
              }
            }
            else {
              *(ulonglong *)(psVar19 + 4) = uStack_60;
            }
            goto LAB_1800408ee;
          }
          psVar19 = psVar19 + 8;
          lVar11 = lVar11 + -1;
        } while (lVar11 != 0);
      }
      if (uStack_60 == 0) {
        return;
      }
    }
    uStack_b0 = uStack_b0 & 0xffffff0000000000;
    cVar8 = FUN_18000e310(uVar15 + 0x18,0x10,lVar10,uVar15 + 0x10);
    if (cVar8 == '\0') {
      return;
    }
    lVar10 = *(longlong *)(uVar15 + 0x18);
    lVar11 = *(longlong *)(uVar15 + 8) * 0x10;
    *(char *)(lVar10 + lVar11) = cVar6;
    *(undefined1 *)(lVar10 + 1 + lVar11) = uVar2;
    *(char *)(lVar10 + 2 + lVar11) = cVar7;
    *(undefined4 *)(lVar10 + 3 + lVar11) = (undefined4)uStack_b0;
    *(undefined1 *)(lVar10 + 7 + lVar11) = uStack_b0._4_1_;
    *(ulonglong *)(lVar10 + 8 + lVar11) = uStack_60;
    *(longlong *)(uVar15 + 8) = *(longlong *)(uVar15 + 8) + 1;
  }
LAB_1800408ee:
  FUN_18003fcc0(uVar15);
  return;
}

// CALLBACK RVA 0x3fa50; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/block_esp_lifecycle/block_esp_lifecycle.c
// Differential report: analysis/module_behavior_recovery/block_esp_lifecycle/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3fa50; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003fa50(void)

{
  undefined8 *puVar1;
  longlong lVar2;
  longlong lVar3;
  ulonglong uVar4;
  
  _DAT_180302110 = 0;
  uRam0000000180302118 = 0;
  func_0x00018013cf70(_DAT_180302120);
  _DAT_180302120 = 0;
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

// UI RVA 0x3fb30; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3fb30; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003fb30(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  undefined8 unaff_RBP;
  undefined8 unaff_RDI;
  undefined4 uVar2;
  
  uVar2 = (undefined4)((ulonglong)unaff_RDI >> 0x20);
  FUN_180013e90(param_1,param_2,&UNK_180154298);
  FUN_18000cf30(param_2,param_1,0x1802f1a28);
  FUN_18000d0e0(param_2,param_1,0x1802f1950);
  FUN_180013e90(param_1,param_2,&UNK_18015429d);
  FUN_18000cef0(param_2,param_1,0x1802f1a60);
  if (DAT_1802f1a78 == '\x01') {
    FUN_18000cf30(param_2,param_1,0x1802f19f0);
  }
  FUN_180013e90(param_1,param_2,&UNK_1801542b0);
  cVar1 = FUN_180013f40(param_1,param_2,uRam00000001802f19c8,uRam00000001802f19d0,0x1802f19b8,
                        uRam00000001802f19e0,uRam00000001802f19e4,uRam00000001802f19d8,
                        CONCAT44(uVar2,uRam00000001802f19dc),&DAT_1802f19e8,unaff_RBP);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x3fbe0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3fbe0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003fbe0(undefined8 *param_1)

{
  double dVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  undefined8 uVar6;
  longlong lVar7;
  float fVar8;
  
  FUN_18000c450(param_1,&UNK_1801542be,0x1802f1a28);
  FUN_18000ca00(param_1,&UNK_1801542c4,0x1802f1950);
  FUN_18000c3b0(param_1,&UNK_1801542d3,0x1802f1a60);
  FUN_18000c450(param_1,&UNK_1801542ed,0x1802f19f0);
  fVar4 = _DAT_1802f19e8;
  if (*(char *)((longlong)param_1 + 0xc) == '\0') {
    switch(*(undefined4 *)(param_1 + 1)) {
    case 0:
      uVar6 = FUN_18004e4d0(*param_1);
      fVar4 = fRam00000001802f19ec;
      fVar3 = fRam00000001802f19e4;
      fVar2 = fRam00000001802f19e0;
      iVar5 = FUN_18004d150(uVar6);
      if (iVar5 != 0) {
        dVar1 = (double)FUN_18004d130(uVar6);
        fVar8 = (float)dVar1;
        fVar4 = fVar2;
        if ((fVar2 <= fVar8) && (fVar4 = fVar8, fVar3 < fVar8)) {
          fVar4 = fVar3;
        }
      }
      break;
    case 1:
      lVar7 = FUN_18004eeb0(*param_1,&UNK_180154300,(double)_DAT_1802f19e8);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar7 == 0;
      fVar4 = _DAT_1802f19e8;
      break;
    case 2:
      fRam00000001802f19ec = _DAT_1802f19e8;
      break;
    case 3:
      fVar4 = fRam00000001802f19ec;
    }
  }
  _DAT_1802f19e8 = fVar4;
  return;
}

// CANDIDATE_LOCAL RVA 0x3fc60; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3fc60; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003fc60(longlong param_1)

{
  *(undefined8 *)(param_1 + 8) = 0;
  *(undefined8 *)(param_1 + 0x10) = 0;
  func_0x00018013cf70(*(undefined8 *)(param_1 + 0x18));
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  func_0x00018013cf70(*(undefined8 *)(param_1 + 0x30));
  *(undefined8 *)(param_1 + 0x30) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)(param_1 + 0x40) = 0;
  func_0x00018013cf70(*(undefined8 *)(param_1 + 0x48));
  *(undefined8 *)(param_1 + 0x48) = 0;
  return;
}

// CANDIDATE_LOCAL RVA 0x3fcc0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3fcc0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003fcc0(longlong param_1)

{
  ulonglong *puVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  ulonglong uVar6;
  undefined8 uVar7;
  byte bVar8;
  short sVar9;
  longlong lVar10;
  undefined1 auVar11 [15];
  undefined1 auVar12 [14];
  undefined1 auVar13 [15];
  undefined1 auVar14 [15];
  undefined1 auVar15 [15];
  undefined1 auVar16 [14];
  undefined1 auVar17 [15];
  undefined1 auVar18 [15];
  undefined1 auVar19 [15];
  undefined1 auVar20 [15];
  undefined1 auVar21 [15];
  unkuint9 Var22;
  undefined1 auVar23 [11];
  undefined1 auVar24 [14];
  undefined1 auVar25 [15];
  undefined1 auVar26 [15];
  float fVar27;
  char cVar28;
  longlong lVar29;
  longlong lVar30;
  longlong lVar31;
  ulonglong uStack_a0;
  
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  fVar27 = _DAT_180154168;
  if (*(longlong *)(param_1 + 8) != 0) {
    uStack_a0 = 0;
    do {
      lVar10 = *(longlong *)(param_1 + 0x20);
      puVar1 = (ulonglong *)(*(longlong *)(param_1 + 0x18) + uStack_a0 * 0x10);
      lVar31 = *(longlong *)(*(longlong *)(param_1 + 0x18) + 8 + uStack_a0 * 0x10);
      fVar2 = *(float *)(lVar31 + 8);
      fVar3 = *(float *)(lVar31 + 0xc);
      fVar4 = *(float *)(lVar31 + 0x10);
      lVar30 = 8;
      lVar31 = lVar10;
      do {
        uVar6 = *puVar1;
        uVar7 = *(undefined8 *)(&UNK_1801541a8 + lVar30);
        bVar8 = *(byte *)((longlong)puVar1 + 2);
        fVar5 = *(float *)(&UNK_1801541b0 + lVar30);
        cVar28 = FUN_18000e310(param_1 + 0x30,0x10,lVar31,param_1 + 0x28);
        if (cVar28 == '\0') {
          return;
        }
        auVar11._8_6_ = 0;
        auVar11._0_8_ = uVar6;
        auVar11[0xe] = (char)(uVar6 >> 0x38);
        auVar13._8_4_ = 0;
        auVar13._0_8_ = uVar6;
        auVar13[0xc] = (char)(uVar6 >> 0x30);
        auVar13._13_2_ = auVar11._13_2_;
        auVar14._8_4_ = 0;
        auVar14._0_8_ = uVar6;
        auVar14._12_3_ = auVar13._12_3_;
        auVar15._8_2_ = 0;
        auVar15._0_8_ = uVar6;
        auVar15[10] = (char)(uVar6 >> 0x28);
        auVar15._11_4_ = auVar14._11_4_;
        auVar17._8_2_ = 0;
        auVar17._0_8_ = uVar6;
        auVar17._10_5_ = auVar15._10_5_;
        auVar18[8] = (char)(uVar6 >> 0x20);
        auVar18._0_8_ = uVar6;
        auVar18._9_6_ = auVar17._9_6_;
        auVar21._7_8_ = 0;
        auVar21._0_7_ = auVar18._8_7_;
        Var22 = CONCAT81(SUB158(auVar21 << 0x40,7),(char)(uVar6 >> 0x18));
        auVar25._9_6_ = 0;
        auVar25._0_9_ = Var22;
        auVar23._1_10_ = SUB1510(auVar25 << 0x30,5);
        auVar23[0] = (char)(uVar6 >> 0x10);
        auVar26._11_4_ = 0;
        auVar26._0_11_ = auVar23;
        auVar19[2] = (char)(uVar6 >> 8);
        auVar19._0_2_ = (ushort)uVar6;
        auVar19._3_12_ = SUB1512(auVar26 << 0x20,3);
        auVar20._2_13_ = auVar19._2_13_;
        auVar20._0_2_ = (ushort)uVar6 & 0xff;
        auVar12._10_2_ = 0;
        auVar12._0_10_ = auVar20._0_10_;
        auVar12._12_2_ = (short)Var22;
        auVar24._2_4_ = auVar12._10_4_;
        auVar24._0_2_ = auVar23._0_2_;
        auVar24._6_8_ = 0;
        auVar16._4_2_ = auVar19._2_2_;
        auVar16._0_4_ = auVar20._0_4_;
        auVar16._6_8_ = SUB148(auVar24 << 0x40,6);
        lVar31 = *(longlong *)(param_1 + 0x30);
        lVar29 = *(longlong *)(param_1 + 0x20) * 0x10;
        *(ulonglong *)(lVar31 + lVar29) =
             CONCAT44((float)((ulonglong)uVar7 >> 0x20) + (float)auVar16._4_4_,
                      (float)uVar7 + (float)(auVar20._0_4_ & 0xffff));
        *(float *)(lVar31 + 8 + lVar29) = fVar5 + (float)bVar8;
        *(char *)(lVar31 + 0xc + lVar29) = (char)(int)(fVar2 * fVar27);
        *(char *)(lVar31 + 0xd + lVar29) = (char)(int)(fVar3 * fVar27);
        *(char *)(lVar31 + 0xe + lVar29) = (char)(int)(fVar4 * fVar27);
        *(undefined1 *)(lVar31 + 0xf + lVar29) = 0xff;
        lVar31 = *(longlong *)(param_1 + 0x20) + 1;
        *(longlong *)(param_1 + 0x20) = lVar31;
        lVar30 = lVar30 + 0xc;
      } while (lVar30 != 0x68);
      lVar31 = *(longlong *)(param_1 + 0x38);
      lVar30 = 0;
      do {
        sVar9 = *(short *)(&UNK_180154210 + lVar30);
        cVar28 = FUN_18000e310(param_1 + 0x48,2,lVar31,param_1 + 0x40);
        if (cVar28 == '\0') {
          return;
        }
        *(short *)(*(longlong *)(param_1 + 0x48) + *(longlong *)(param_1 + 0x38) * 2) =
             sVar9 + (short)lVar10;
        lVar31 = *(longlong *)(param_1 + 0x38) + 1;
        *(longlong *)(param_1 + 0x38) = lVar31;
        lVar30 = lVar30 + 2;
      } while (lVar30 != 0x30);
      uStack_a0 = uStack_a0 + 1;
    } while (uStack_a0 < *(ulonglong *)(param_1 + 8));
  }
  return;
}

// CANDIDATE_LOCAL RVA 0x3fed0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3fed0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003fed0(undefined8 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  longlong lVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  int iVar6;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined8 uStack_4c;
  undefined4 uStack_44;
  
  lVar3 = FUN_180024990(*param_1,param_1[4]);
  if (lVar3 != 0) {
    uVar4 = FUN_180024ab0(*param_1,lVar3);
    iVar1 = FUN_180024e50(*param_1,uVar4);
    if (0 < iVar1) {
      iVar6 = 0;
      do {
        uVar5 = FUN_180024e80(*param_1,uVar4,iVar6);
        uVar2 = FUN_180024a10(*param_1,uVar5);
        uStack_50 = FUN_180024a30(*param_1,uVar5);
        uStack_68 = *param_1;
        uStack_60 = param_1[4];
        uStack_58 = 1;
        uStack_4c = 0;
        uStack_44 = 0;
        uStack_54 = uVar2;
        FUN_180040420(&uStack_68);
        iVar6 = iVar6 + 1;
      } while (iVar1 != iVar6);
    }
  }
  return;
}

// CANDIDATE_LOCAL RVA 0x3ffb0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3ffb0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003ffb0(longlong param_1,byte param_2)

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

// CANDIDATE_LOCAL RVA 0x40000; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x40000; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


undefined8 FUN_180040000(undefined8 *param_1)

{
  return *param_1;
}

// CANDIDATE_LOCAL RVA 0x40010; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x40010; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


undefined8 FUN_180040010(longlong param_1,longlong param_2)

{
  return *(undefined8 *)(*(longlong *)(param_1 + 0x10) + param_2 * 0x18);
}

// CANDIDATE_LOCAL RVA 0x40030; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x40030; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


longlong FUN_180040030(longlong param_1,longlong param_2)

{
  return *(longlong *)(param_1 + 0x10) + 8 + param_2 * 0x18;
}

// CANDIDATE_LOCAL RVA 0x40050; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x40050; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_180040050(longlong *param_1,undefined8 param_2,undefined8 *param_3)

{
  undefined8 *puVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  int iVar4;
  undefined4 uVar5;
  longlong lVar6;
  undefined8 uVar7;
  int *piVar8;
  longlong lVar9;
  longlong lVar10;
  ulonglong uVar11;
  int aiStack_4c [5];
  
  aiStack_4c[0] = FUN_18000e3c0(param_2);
  if ((aiStack_4c[0] == -1) ||
     ((_DAT_180302120 != 0 &&
      (lVar6 = func_0x00018013d0e0(aiStack_4c,_DAT_180302120,_DAT_180302110,0x18,FUN_180040410),
      lVar6 != 0)))) {
    uVar5 = 0;
  }
  else {
    lVar6 = *param_1;
    if (lVar6 == 0) {
      lVar10 = 0;
    }
    else {
      piVar8 = (int *)(param_1[2] + 0x14);
      lVar9 = 0;
      do {
        lVar10 = lVar9;
        if (aiStack_4c[0] <= *piVar8) break;
        lVar9 = lVar9 + 1;
        piVar8 = piVar8 + 6;
        lVar10 = lVar6;
      } while (lVar6 != lVar9);
    }
    uVar7 = FUN_18000e420(aiStack_4c[0]);
    iVar4 = aiStack_4c[0];
    uVar3 = *param_3;
    uVar2 = *(undefined4 *)(param_3 + 1);
    if (_DAT_1803020f0 != 0) {
      lVar6 = 0x48;
      uVar11 = 0;
      do {
        lVar9 = _DAT_180302100;
        puVar1 = (undefined8 *)(_DAT_180302100 + -0x40 + lVar6);
        *puVar1 = 0;
        puVar1[1] = 0;
        func_0x00018013cf70(*(undefined8 *)(lVar9 + -0x30 + lVar6));
        puVar1 = (undefined8 *)(lVar9 + -0x30 + lVar6);
        *puVar1 = 0;
        puVar1[1] = 0;
        *(undefined8 *)(lVar9 + -0x20 + lVar6) = 0;
        func_0x00018013cf70(*(undefined8 *)(lVar9 + -0x18 + lVar6));
        puVar1 = (undefined8 *)(lVar9 + -0x18 + lVar6);
        *puVar1 = 0;
        puVar1[1] = 0;
        *(undefined8 *)(lVar9 + -8 + lVar6) = 0;
        func_0x00018013cf70(*(undefined8 *)(lVar9 + lVar6));
        *(undefined8 *)(lVar9 + lVar6) = 0;
        uVar11 = uVar11 + 1;
        lVar6 = lVar6 + 0x50;
      } while (uVar11 < _DAT_1803020f0);
    }
    _DAT_1803020f0 = 0;
    uRam00000001803020f8 = 0;
    func_0x00018013cf70(_DAT_180302100);
    _DAT_180302100 = 0;
    DAT_180302108 = 1;
    uVar5 = FUN_18000e310(&DAT_180302120,0x18,_DAT_180302110,0x180302118);
    lVar6 = _DAT_180302120;
    if ((char)uVar5 != '\0') {
      func_0x0001800ab910(_DAT_180302120 + lVar10 * 0x18 + 0x18,_DAT_180302120 + lVar10 * 0x18,
                          (_DAT_180302110 - lVar10) * 0x18);
      *(undefined8 *)(lVar6 + lVar10 * 0x18) = uVar7;
      *(undefined8 *)(lVar6 + 8 + lVar10 * 0x18) = uVar3;
      *(undefined4 *)(lVar6 + 0x10 + lVar10 * 0x18) = uVar2;
      *(int *)(lVar6 + 0x14 + lVar10 * 0x18) = iVar4;
      _DAT_180302110 = _DAT_180302110 + 1;
    }
  }
  return uVar5;
}

// CANDIDATE_LOCAL RVA 0x40240; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x40240; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180040240(longlong *param_1,longlong param_2)

{
  undefined8 *puVar1;
  longlong lVar2;
  longlong lVar3;
  ulonglong uVar4;
  
  lVar3 = *param_1;
  *param_1 = lVar3 + -1;
  func_0x0001800ab910(param_1[2] + param_2 * 0x18,param_1[2] + param_2 * 0x18 + 0x18,
                      ((lVar3 + -1) - param_2) * 0x18);
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
  DAT_180302108 = 1;
  return;
}

// CANDIDATE_LOCAL RVA 0x40340; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x40340; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180040340(undefined8 *param_1)

{
  undefined8 *puVar1;
  longlong lVar2;
  longlong lVar3;
  ulonglong uVar4;
  
  *param_1 = 0;
  param_1[1] = 0;
  func_0x00018013cf70(param_1[2]);
  param_1[2] = 0;
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
  DAT_180302108 = 1;
  return;
}

// CANDIDATE_LOCAL RVA 0x40410; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x40410; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


int FUN_180040410(int *param_1,longlong param_2)

{
  return *param_1 - *(int *)(param_2 + 0x14);
}

// CANDIDATE_LOCAL RVA 0x40420; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x40420; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180040420(longlong *param_1)

{
  undefined8 *puVar1;
  undefined4 uVar2;
  longlong *plVar3;
  ulonglong uVar4;
  char cVar5;
  char cVar6;
  char cVar7;
  int iVar8;
  longlong lVar9;
  longlong lVar10;
  longlong lVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  ulonglong uVar15;
  longlong lVar16;
  int *piVar17;
  int iVar18;
  short *psVar19;
  ulonglong uVar20;
  int iVar21;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  ulonglong uStack_60;
  
  if (*(uint *)(param_1 + 2) < 2) {
    uStack_b0 = *(undefined8 *)((longlong)param_1 + 0x14);
    uStack_78 = 0;
    uStack_70 = 0;
    uStack_88 = 0;
    uStack_80 = 0;
    uStack_98 = 0;
    uStack_90 = 0;
    uStack_a8 = 0;
    uStack_a0 = 0;
    uStack_68 = 0;
    if ((_DAT_180302100 != 0) &&
       (lVar9 = func_0x00018013d0e0(&uStack_b0,_DAT_180302100,_DAT_1803020f0,0x50,FUN_180040960),
       lVar9 != 0)) {
      *(undefined8 *)(lVar9 + 8) = 0;
      *(undefined8 *)(lVar9 + 0x10) = 0;
      func_0x00018013cf70(*(undefined8 *)(lVar9 + 0x18));
      *(undefined8 *)(lVar9 + 0x18) = 0;
      *(undefined8 *)(lVar9 + 0x20) = 0;
      *(undefined8 *)(lVar9 + 0x28) = 0;
      func_0x00018013cf70(*(undefined8 *)(lVar9 + 0x30));
      *(undefined8 *)(lVar9 + 0x30) = 0;
      *(undefined8 *)(lVar9 + 0x38) = 0;
      *(undefined8 *)(lVar9 + 0x40) = 0;
      func_0x00018013cf70(*(undefined8 *)(lVar9 + 0x48));
      *(undefined8 *)(lVar9 + 0x48) = 0;
      lVar10 = _DAT_1803020f0 + ((ulonglong)(lVar9 - _DAT_180302100) >> 4) * 0x3333333333333333;
      _DAT_1803020f0 = _DAT_1803020f0 + -1;
      func_0x0001800ab910(lVar9,lVar9 + 0x50,(lVar10 + -1) * 0x50);
    }
    if ((int)param_1[2] != 1) {
      return;
    }
    lVar9 = *param_1;
    lVar10 = param_1[3];
    uStack_60 = CONCAT44(uStack_60._4_4_,*(undefined4 *)((longlong)param_1 + 0x14));
    lVar11 = FUN_1800248f0(lVar9,param_1[1],*(undefined4 *)((longlong)param_1 + 0x14),(int)lVar10);
    if (lVar11 == 0) {
      return;
    }
    uStack_b0 = 0;
    plVar3 = *(longlong **)(lVar9 + 8);
    uVar12 = FUN_1800249f0(lVar9,lVar11);
    iVar21 = 0;
    do {
      lVar11 = (**(code **)(*plVar3 + 0x568))(plVar3,uVar12,iVar21);
      if (lVar11 != 0) {
        uVar13 = FUN_180024a50(lVar9,lVar11);
        uVar14 = (**(code **)(*plVar3 + 0x6f0))(plVar3,uVar13,0);
        (*_DAT_180302128)(uStack_60 & 0xffffffff,iVar21,(int)lVar10,uVar14,&uStack_b0);
        (**(code **)(*plVar3 + 0x6f8))(plVar3,uVar13,uVar14,0);
      }
      iVar21 = iVar21 + 1;
    } while (iVar21 != 0x10);
    uVar15 = uStack_b0;
    if (uStack_b0 == 0) {
      return;
    }
  }
  else {
    if (*(uint *)(param_1 + 2) != 2) {
      return;
    }
    uStack_b0 = CONCAT44(uStack_b0._4_4_,(int)param_1[4]);
    if (_DAT_180302120 == 0) {
      uStack_60 = 0;
    }
    else {
      uStack_60 = func_0x00018013d0e0(&uStack_b0,_DAT_180302120,_DAT_180302110,0x18,FUN_180040410);
    }
    iVar21 = FUN_18000a2f0(*(undefined4 *)((longlong)param_1 + 0x14));
    iVar8 = FUN_18000a2f0(*(undefined4 *)((longlong)param_1 + 0x1c));
    uVar20 = CONCAT44(iVar8,iVar21);
    uStack_78 = 0;
    uStack_70 = 0;
    uStack_88 = 0;
    uStack_80 = 0;
    uStack_98 = 0;
    uStack_90 = 0;
    uStack_a8 = 0;
    uStack_a0 = 0;
    uStack_68 = 0;
    uStack_b0 = uVar20;
    if (_DAT_180302100 == 0) {
      uVar15 = 0;
    }
    else {
      uVar15 = func_0x00018013d0e0(&uStack_b0,_DAT_180302100,_DAT_1803020f0,0x50,FUN_180040960);
    }
    uVar2 = *(undefined4 *)((longlong)param_1 + 0x14);
    cVar5 = FUN_18000a300(iVar21);
    cVar5 = (char)uVar2 - cVar5;
    uVar2 = *(undefined4 *)((longlong)param_1 + 0x1c);
    cVar6 = FUN_18000a300(iVar8);
    uVar4 = uStack_b0;
    cVar6 = (char)uVar2 - cVar6;
    lVar9 = param_1[3];
    if (uVar15 == 0) {
      if (uStack_60 == 0) {
        return;
      }
      if (_DAT_1803020f0 == 0) {
        lVar10 = 0;
      }
      else {
        piVar17 = (int *)(_DAT_180302100 + 4);
        lVar11 = 0;
        do {
          iVar18 = iVar21 - piVar17[-1];
          if (iVar18 == 0) {
            iVar18 = iVar8 - *piVar17;
          }
          lVar10 = lVar11;
          if (iVar18 < 1) break;
          lVar11 = lVar11 + 1;
          piVar17 = piVar17 + 0x14;
          lVar10 = _DAT_1803020f0;
        } while (_DAT_1803020f0 != lVar11);
      }
      cVar7 = FUN_18000e310(&DAT_180302100,0x50,_DAT_1803020f0,0x1803020f8);
      lVar11 = _DAT_180302100;
      if (cVar7 == '\0') {
        return;
      }
      lVar16 = lVar10 * 0x50;
      func_0x0001800ab910(_DAT_180302100 + lVar16 + 0x50,_DAT_180302100 + lVar16,
                          (_DAT_1803020f0 - lVar10) * 0x50);
      *(ulonglong *)(lVar11 + lVar16) = uVar20;
      puVar1 = (undefined8 *)(lVar11 + 8 + lVar16);
      *puVar1 = 0;
      puVar1[1] = 0;
      puVar1 = (undefined8 *)(lVar11 + 0x18 + lVar16);
      *puVar1 = 0;
      puVar1[1] = 0;
      puVar1 = (undefined8 *)(lVar11 + 0x28 + lVar16);
      *puVar1 = 0;
      puVar1[1] = 0;
      puVar1 = (undefined8 *)(lVar11 + 0x38 + lVar16);
      *puVar1 = 0;
      puVar1[1] = 0;
      *(undefined8 *)(lVar11 + 0x48 + lVar16) = 0;
      _DAT_1803020f0 = _DAT_1803020f0 + 1;
      if (_DAT_180302100 == 0) {
        return;
      }
      uVar15 = _DAT_180302100 + lVar16;
      lVar10 = *(longlong *)(_DAT_180302100 + 8 + lVar16);
    }
    else {
      uStack_b0._0_2_ = CONCAT11((char)lVar9,cVar5);
      uStack_b0._3_5_ = SUB85(uVar4,3);
      uStack_b0._0_3_ = CONCAT12(cVar6,(short)uStack_b0);
      lVar10 = *(longlong *)(uVar15 + 8);
      if (lVar10 != 0) {
        psVar19 = *(short **)(uVar15 + 0x18);
        lVar16 = lVar10 << 4;
        lVar11 = lVar10;
        do {
          lVar16 = lVar16 + -0x10;
          if ((char)psVar19[1] == cVar6 && *psVar19 == (short)uStack_b0) {
            if (uStack_60 == 0) {
              *(longlong *)(uVar15 + 8) = lVar10 + -1;
              func_0x0001800ab910(psVar19,psVar19 + 8,lVar16);
              if (*(longlong *)(uVar15 + 8) == 0) {
                FUN_18003fc60(uVar15);
                lVar9 = _DAT_1803020f0 + (uVar15 - _DAT_180302100 >> 4) * 0x3333333333333333;
                _DAT_1803020f0 = _DAT_1803020f0 + -1;
                func_0x0001800ab910(uVar15,uVar15 + 0x50,(lVar9 + -1) * 0x50);
                return;
              }
            }
            else {
              *(ulonglong *)(psVar19 + 4) = uStack_60;
            }
            goto LAB_1800408ee;
          }
          psVar19 = psVar19 + 8;
          lVar11 = lVar11 + -1;
        } while (lVar11 != 0);
      }
      if (uStack_60 == 0) {
        return;
      }
    }
    uStack_b0 = uStack_b0 & 0xffffff0000000000;
    cVar7 = FUN_18000e310(uVar15 + 0x18,0x10,lVar10,uVar15 + 0x10);
    if (cVar7 == '\0') {
      return;
    }
    lVar10 = *(longlong *)(uVar15 + 0x18);
    lVar11 = *(longlong *)(uVar15 + 8) * 0x10;
    *(char *)(lVar10 + lVar11) = cVar5;
    *(char *)(lVar10 + 1 + lVar11) = (char)lVar9;
    *(char *)(lVar10 + 2 + lVar11) = cVar6;
    *(undefined4 *)(lVar10 + 3 + lVar11) = (undefined4)uStack_b0;
    *(undefined1 *)(lVar10 + 7 + lVar11) = uStack_b0._4_1_;
    *(ulonglong *)(lVar10 + 8 + lVar11) = uStack_60;
    *(longlong *)(uVar15 + 8) = *(longlong *)(uVar15 + 8) + 1;
  }
LAB_1800408ee:
  FUN_18003fcc0(uVar15);
  return;
}

// CANDIDATE_LOCAL RVA 0x40960; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x40960; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


int FUN_180040960(int *param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = *param_1 - *param_2;
  if (iVar1 == 0) {
    iVar1 = param_1[1] - param_2[1];
  }
  return iVar1;
}

// CANDIDATE_LOCAL RVA 0x40980; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x40980; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180040980(ulonglong param_1,char param_2,longlong param_3,longlong param_4,
                  longlong *param_5)

{
  longlong lVar1;
  char *pcVar2;
  undefined4 uVar3;
  longlong lVar4;
  ushort uVar5;
  char cVar6;
  longlong lVar7;
  longlong lVar8;
  ulonglong uVar9;
  uint uVar10;
  ulonglong uVar11;
  undefined1 uVar14;
  undefined1 uVar15;
  undefined1 uVar16;
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  
  if (_DAT_180302110 != 0) {
    uVar9 = 0;
    do {
      lVar1 = _DAT_180302120 + uVar9 * 0x18;
      uVar3 = *(undefined4 *)(_DAT_180302120 + 0x14 + uVar9 * 0x18);
      uVar16 = (undefined1)((uint)uVar3 >> 0x18);
      uVar15 = (undefined1)((uint)uVar3 >> 0x10);
      uVar14 = (undefined1)((uint)uVar3 >> 8);
      auVar12._4_4_ =
           (int)(CONCAT35(CONCAT21(CONCAT11(uVar16,uVar16),uVar15),CONCAT14(uVar15,uVar3)) >> 0x20);
      auVar12[3] = uVar14;
      auVar12[2] = uVar14;
      auVar12[0] = (undefined1)uVar3;
      auVar12[1] = auVar12[0];
      auVar12._8_8_ = 0;
      auVar12 = pshuflw(auVar12,auVar12,0);
      uVar11 = 0;
      do {
        pcVar2 = (char *)(param_4 + uVar11 * 0x10);
        auVar13[0] = -(*pcVar2 == auVar12[0]);
        auVar13[1] = -(pcVar2[1] == auVar12[1]);
        auVar13[2] = -(pcVar2[2] == auVar12[2]);
        auVar13[3] = -(pcVar2[3] == auVar12[3]);
        auVar13[4] = -(pcVar2[4] == auVar12[4]);
        auVar13[5] = -(pcVar2[5] == auVar12[5]);
        auVar13[6] = -(pcVar2[6] == auVar12[6]);
        auVar13[7] = -(pcVar2[7] == auVar12[7]);
        auVar13[8] = -(pcVar2[8] == auVar12[0]);
        auVar13[9] = -(pcVar2[9] == auVar12[1]);
        auVar13[10] = -(pcVar2[10] == auVar12[2]);
        auVar13[0xb] = -(pcVar2[0xb] == auVar12[3]);
        auVar13[0xc] = -(pcVar2[0xc] == auVar12[4]);
        auVar13[0xd] = -(pcVar2[0xd] == auVar12[5]);
        auVar13[0xe] = -(pcVar2[0xe] == auVar12[6]);
        auVar13[0xf] = -(pcVar2[0xf] == auVar12[7]);
        uVar5 = (ushort)(SUB161(auVar13 >> 7,0) & 1) | (ushort)(SUB161(auVar13 >> 0xf,0) & 1) << 1 |
                (ushort)(SUB161(auVar13 >> 0x17,0) & 1) << 2 |
                (ushort)(SUB161(auVar13 >> 0x1f,0) & 1) << 3 |
                (ushort)(SUB161(auVar13 >> 0x27,0) & 1) << 4 |
                (ushort)(SUB161(auVar13 >> 0x2f,0) & 1) << 5 |
                (ushort)(SUB161(auVar13 >> 0x37,0) & 1) << 6 |
                (ushort)(SUB161(auVar13 >> 0x3f,0) & 1) << 7 |
                (ushort)(SUB161(auVar13 >> 0x47,0) & 1) << 8 |
                (ushort)(SUB161(auVar13 >> 0x4f,0) & 1) << 9 |
                (ushort)(SUB161(auVar13 >> 0x57,0) & 1) << 10 |
                (ushort)(SUB161(auVar13 >> 0x5f,0) & 1) << 0xb |
                (ushort)(SUB161(auVar13 >> 0x67,0) & 1) << 0xc |
                (ushort)(SUB161(auVar13 >> 0x6f,0) & 1) << 0xd |
                (ushort)(SUB161(auVar13 >> 0x77,0) & 1) << 0xe | (ushort)(auVar13[0xf] >> 7) << 0xf;
        if (uVar5 != 0) {
          uVar10 = 0;
          do {
            if ((uVar5 >> (uVar10 & 0x1f) & 1) != 0) {
              lVar7 = *param_5;
              if (lVar7 == 0) {
                lVar7 = FUN_180040c90(param_1 & 0xffffffff | param_3 << 0x20);
                *param_5 = lVar7;
                if (lVar7 == 0) {
                  return;
                }
              }
              cVar6 = FUN_18000e310(lVar7 + 0x18,0x10,*(undefined8 *)(lVar7 + 8),lVar7 + 0x10);
              if (cVar6 == '\0') {
                return;
              }
              lVar4 = *(longlong *)(lVar7 + 0x18);
              lVar8 = *(longlong *)(lVar7 + 8) * 0x10;
              *(char *)(lVar4 + lVar8) = (char)uVar10;
              *(char *)(lVar4 + 1 + lVar8) =
                   (char)((uVar11 & 0xfffffffffffffff) >> 4) + param_2 * '\x10';
              *(byte *)(lVar4 + 2 + lVar8) = (byte)uVar11 & 0xf;
              *(undefined4 *)(lVar4 + 3 + lVar8) = 0;
              *(undefined1 *)(lVar4 + 7 + lVar8) = 0;
              *(longlong *)(lVar4 + 8 + lVar8) = lVar1;
              *(longlong *)(lVar7 + 8) = *(longlong *)(lVar7 + 8) + 1;
            }
            uVar10 = uVar10 + 1;
          } while (uVar10 != 0x10);
        }
        uVar11 = uVar11 + 1;
      } while (uVar11 != 0x100);
      uVar9 = uVar9 + 1;
    } while (uVar9 < _DAT_180302110);
  }
  return;
}

// CANDIDATE_LOCAL RVA 0x40af0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x40af0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180040af0(ulonglong param_1,char param_2,longlong param_3,longlong param_4,
                  longlong *param_5)

{
  longlong lVar1;
  longlong lVar2;
  ushort uVar3;
  char cVar4;
  longlong lVar5;
  longlong lVar6;
  ulonglong uVar7;
  char cVar8;
  ulonglong uVar9;
  int iVar10;
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  
  if (_DAT_180302110 != 0) {
    uVar9 = 0;
    do {
      lVar1 = _DAT_180302120 + uVar9 * 0x18;
      auVar11 = ZEXT416(*(uint *)(_DAT_180302120 + 0x14 + uVar9 * 0x18));
      auVar11 = pshuflw(auVar11,auVar11,0);
      uVar7 = 0;
      do {
        auVar12 = psraw(*(undefined1 (*) [16])(param_4 + uVar7 * 0x10),4);
        auVar13._0_2_ = -(ushort)(auVar12._0_2_ == auVar11._0_2_);
        auVar13._2_2_ = -(ushort)(auVar12._2_2_ == auVar11._2_2_);
        auVar13._4_2_ = -(ushort)(auVar12._4_2_ == auVar11._4_2_);
        auVar13._6_2_ = -(ushort)(auVar12._6_2_ == auVar11._6_2_);
        auVar13._8_2_ = -(ushort)(auVar12._8_2_ == auVar11._0_2_);
        auVar13._10_2_ = -(ushort)(auVar12._10_2_ == auVar11._2_2_);
        auVar13._12_2_ = -(ushort)(auVar12._12_2_ == auVar11._4_2_);
        auVar13._14_2_ = -(ushort)(auVar12._14_2_ == auVar11._6_2_);
        uVar3 = (ushort)(SUB161(auVar13 >> 7,0) & 1) | (ushort)(SUB161(auVar13 >> 0xf,0) & 1) << 1 |
                (ushort)(SUB161(auVar13 >> 0x17,0) & 1) << 2 |
                (ushort)(SUB161(auVar13 >> 0x1f,0) & 1) << 3 |
                (ushort)(SUB161(auVar13 >> 0x27,0) & 1) << 4 |
                (ushort)(SUB161(auVar13 >> 0x2f,0) & 1) << 5 |
                (ushort)(SUB161(auVar13 >> 0x37,0) & 1) << 6 |
                (ushort)(SUB161(auVar13 >> 0x3f,0) & 1) << 7 |
                (ushort)(SUB161(auVar13 >> 0x47,0) & 1) << 8 |
                (ushort)(SUB161(auVar13 >> 0x4f,0) & 1) << 9 |
                (ushort)(SUB161(auVar13 >> 0x57,0) & 1) << 10 |
                (ushort)(SUB161(auVar13 >> 0x5f,0) & 1) << 0xb |
                (ushort)(SUB161(auVar13 >> 0x67,0) & 1) << 0xc |
                (ushort)(SUB161(auVar13 >> 0x6f,0) & 1) << 0xd |
                (ushort)((byte)(auVar13._14_2_ >> 7) & 1) << 0xe | auVar13._14_2_ & 0x8000;
        if (uVar3 != 0) {
          cVar8 = ((byte)uVar7 & 1) << 3;
          iVar10 = 0;
          do {
            if ((uVar3 >> ((byte)iVar10 & 0x1f) & 3) != 0) {
              lVar5 = *param_5;
              if (lVar5 == 0) {
                lVar5 = FUN_180040c90(param_1 & 0xffffffff | param_3 << 0x20);
                *param_5 = lVar5;
                if (lVar5 == 0) {
                  return;
                }
              }
              cVar4 = FUN_18000e310(lVar5 + 0x18,0x10,*(undefined8 *)(lVar5 + 8),lVar5 + 0x10);
              if (cVar4 == '\0') {
                return;
              }
              lVar2 = *(longlong *)(lVar5 + 0x18);
              lVar6 = *(longlong *)(lVar5 + 8) * 0x10;
              *(char *)(lVar2 + lVar6) = cVar8;
              *(char *)(lVar2 + 1 + lVar6) =
                   (char)((uVar7 & 0x1fffffffffffffff) >> 5) + param_2 * '\x10';
              *(byte *)(lVar2 + 2 + lVar6) = (byte)((uVar7 & 0xffffffff) >> 1) & 0xf;
              *(undefined4 *)(lVar2 + 3 + lVar6) = 0;
              *(undefined1 *)(lVar2 + 7 + lVar6) = 0;
              *(longlong *)(lVar2 + 8 + lVar6) = lVar1;
              *(longlong *)(lVar5 + 8) = *(longlong *)(lVar5 + 8) + 1;
            }
            iVar10 = iVar10 + 2;
            cVar8 = cVar8 + '\x01';
          } while (iVar10 != 0x10);
        }
        uVar7 = uVar7 + 1;
      } while (uVar7 != 0x200);
      uVar9 = uVar9 + 1;
    } while (uVar9 < _DAT_180302110);
  }
  return;
}

// CANDIDATE_LOCAL RVA 0x40c90; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x40c90; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong FUN_180040c90(undefined8 param_1)

{
  undefined8 *puVar1;
  longlong lVar2;
  char cVar3;
  longlong lVar4;
  int *piVar5;
  int iVar6;
  longlong lVar7;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  
  uStack_40 = 0;
  uStack_38 = 0;
  uStack_50 = 0;
  uStack_48 = 0;
  uStack_60 = 0;
  uStack_58 = 0;
  uStack_70 = 0;
  uStack_68 = 0;
  uStack_30 = 0;
  uStack_78 = param_1;
  if ((_DAT_180302100 == 0) ||
     (lVar4 = func_0x00018013d0e0(&uStack_78,_DAT_180302100,_DAT_1803020f0,0x50,FUN_180040960),
     lVar4 == 0)) {
    if (_DAT_1803020f0 == 0) {
      lVar7 = 0;
    }
    else {
      piVar5 = (int *)(_DAT_180302100 + 4);
      lVar4 = 0;
      do {
        iVar6 = (int)param_1 - piVar5[-1];
        if (iVar6 == 0) {
          iVar6 = (int)((ulonglong)param_1 >> 0x20) - *piVar5;
        }
        lVar7 = lVar4;
        if (iVar6 < 1) break;
        lVar4 = lVar4 + 1;
        piVar5 = piVar5 + 0x14;
        lVar7 = _DAT_1803020f0;
      } while (_DAT_1803020f0 != lVar4);
    }
    cVar3 = FUN_18000e310(&DAT_180302100,0x50,_DAT_1803020f0,0x1803020f8);
    lVar2 = _DAT_180302100;
    if (cVar3 == '\0') {
      lVar4 = 0;
    }
    else {
      lVar4 = lVar7 * 0x50;
      func_0x0001800ab910(_DAT_180302100 + lVar4 + 0x50,_DAT_180302100 + lVar4,
                          (_DAT_1803020f0 - lVar7) * 0x50);
      *(undefined8 *)(lVar2 + lVar4) = param_1;
      puVar1 = (undefined8 *)(lVar2 + 8 + lVar4);
      *puVar1 = 0;
      puVar1[1] = 0;
      puVar1 = (undefined8 *)(lVar2 + 0x18 + lVar4);
      *puVar1 = 0;
      puVar1[1] = 0;
      puVar1 = (undefined8 *)(lVar2 + 0x28 + lVar4);
      *puVar1 = 0;
      puVar1[1] = 0;
      puVar1 = (undefined8 *)(lVar2 + 0x38 + lVar4);
      *puVar1 = 0;
      puVar1[1] = 0;
      *(undefined8 *)(lVar2 + 0x48 + lVar4) = 0;
      _DAT_1803020f0 = _DAT_1803020f0 + 1;
      lVar4 = lVar4 + _DAT_180302100;
    }
  }
  return lVar4;
}

