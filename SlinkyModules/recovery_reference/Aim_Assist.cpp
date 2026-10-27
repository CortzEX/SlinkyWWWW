// Recovered decompiler view: Aim Assist
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x2b200, 0x2ca10); proximity does not prove ownership.

// CALLBACK RVA 0x2b200; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/aim_assist_update/aim_assist_update.c
// Differential report: analysis/module_behavior_recovery/aim_assist_update/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2b200; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002b200(longlong param_1)

{
  double dVar1;
  undefined8 *puVar2;
  double dVar3;
  char cVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  ulonglong uVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  ulonglong uVar14;
  ulonglong uVar15;
  ulonglong uVar16;
  longlong lVar17;
  float fVar18;
  undefined8 unaff_XMM6_Qa;
  undefined8 unaff_XMM6_Qb;
  float fVar19;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_48;
  undefined8 uStack_40;
  
  puVar2 = *(undefined8 **)(param_1 + 8);
  if (*(char *)(puVar2 + 8) != '\x01') {
    return;
  }
  if (DAT_1802f7bd8 != '\0') {
    cVar4 = FUN_180029800(100);
    if (cVar4 == '\0') {
      return;
    }
    if ((DAT_1802f7c20 == '\0') && (_DAT_1802e9020 == 3)) {
      DAT_1802f7c20 = '\x01';
    }
    else if (DAT_1802f7c20 == '\0') goto LAB_18002b34f;
    cVar4 = FUN_180029f80();
    if (cVar4 == '\0') {
      return;
    }
LAB_18002b34f:
    fVar10 = *(float *)(param_1 + 0x10);
    FUN_1800230d0(&uStack_80,*puVar2,puVar2[5]);
    FUN_180023030(&uStack_68,*puVar2,puVar2[5]);
    uStack_e8 = uStack_58;
    uStack_f8 = uStack_68;
    uStack_f0 = uStack_60;
    FUN_1800093d0(&uStack_b8,&uStack_f8,&uStack_98);
    uStack_88 = uStack_a8;
    uStack_98 = uStack_b8;
    uStack_90 = uStack_b0;
    FUN_180009430(&uStack_f8,&uStack_98,(double)fVar10);
    FUN_180009400(&uStack_d8,&uStack_98,&uStack_f8);
    cVar4 = FUN_180023020(*puVar2);
    if (cVar4 == '\0') {
      uStack_58 = uStack_c8;
      uStack_68 = uStack_d8;
      uStack_60 = uStack_d0;
      FUN_180009590(&uStack_80,&uStack_68);
      uStack_d8 = CONCAT44(uStack_7c,uStack_80);
      uStack_d0 = CONCAT44(uStack_74,uStack_78);
      uStack_c8 = CONCAT44(uStack_6c,uStack_70);
    }
    uStack_58 = _DAT_1802f7bf8;
    uStack_68 = _DAT_1802f7be8;
    uStack_60 = uRam00000001802f7bf0;
    uStack_a8 = _DAT_1802f7c10;
    uStack_b8 = _DAT_1802f7c00;
    uStack_b0 = uRam00000001802f7c08;
    FUN_180009460(&uStack_80,&uStack_68,&uStack_b8,(double)*(float *)(param_1 + 0x10));
    uStack_58 = uStack_c8;
    uStack_68 = uStack_d8;
    uStack_60 = uStack_d0;
    uVar5 = FUN_180009f80(&uStack_68,&uStack_b8);
    uVar6 = FUN_180023170(*puVar2,puVar2[5]);
    uVar7 = FUN_180029850();
    uVar6 = FUN_180009de0(uVar6,uVar7);
    uVar8 = FUN_180009e20(uVar5,uVar6);
    uVar14 = FUN_18000a210(uVar8 & 0xffffffff);
    uVar8 = uVar14 & 0xffffffff | uVar8 & 0xffffffff00000000;
    if ((_DAT_1802e9020 == 3) && (DAT_1802e9048 == '\0')) {
      uVar7 = FUN_180029ff0();
      uVar14 = FUN_180009e20(uVar7,uVar6);
      uVar15 = FUN_18000a210(uVar14 & 0xffffffff);
      uVar15 = uVar15 & 0xffffffff | uVar14 & 0xffffffff00000000;
      uVar6 = FUN_180029ff0();
      uVar14 = FUN_180009e20(uVar5,uVar6);
      uVar16 = FUN_18000a210(uVar14 & 0xffffffff);
      fVar10 = (float)FUN_180009f60(uVar15);
      if (fVar10 < _DAT_18014fef0) {
        fVar10 = (float)FUN_180009f60(uVar16 & 0xffffffff | uVar14 & 0xffffffff00000000);
        fVar11 = (float)FUN_180009f60(uVar8);
        if (fVar10 < fVar11) {
          FUN_180029820(uVar15);
          return;
        }
      }
    }
    FUN_18002bf40(uVar8,(float)*(double *)(param_1 + 0x18));
    return;
  }
  if (DAT_1802f7c20 != '\x01') {
    return;
  }
  uStack_48 = unaff_XMM6_Qa;
  uStack_40 = unaff_XMM6_Qb;
  cVar4 = FUN_180029f80();
  if ((cVar4 == '\0') || (cVar4 = FUN_180029800(100), cVar4 == '\0')) {
    DAT_1802f7c20 = 0;
    return;
  }
  uVar5 = FUN_180023170(*puVar2,puVar2[5]);
  uVar6 = FUN_180029850();
  uVar5 = FUN_180009de0(uVar5,uVar6);
  uVar6 = FUN_180029ff0();
  uVar8 = FUN_180009e20(uVar6,uVar5);
  fVar10 = (float)FUN_18000a210(uVar8 & 0xffffffff);
  fVar11 = (float)FUN_180009f60((ulonglong)(uint)fVar10 | uVar8 & 0xffffffff00000000);
  if (fVar11 < _DAT_18014fef0) {
    DAT_1802f7c20 = '\0';
  }
  dVar1 = *(double *)(param_1 + 0x18);
  uStack_b8 = uStack_48;
  uStack_b0 = uStack_40;
  fVar11 = (float)((uVar8 & 0xffffffff00000000) >> 0x20);
  fVar18 = 0.0;
  if (fVar10 <= 0.0) {
    fVar9 = fVar10 + _DAT_1802e8f10;
    if (0.0 <= fVar10 + _DAT_1802e8f10) {
      fVar9 = fVar18;
    }
    if (0.0 < fVar11) goto LAB_18002c091;
LAB_18002bfb7:
    fVar10 = _DAT_1802e8f10 + fVar11;
    if (0.0 <= _DAT_1802e8f10 + fVar11) {
      fVar10 = fVar18;
    }
  }
  else {
    fVar9 = fVar10 - _DAT_1802e8f10;
    if (fVar10 - _DAT_1802e8f10 <= 0.0) {
      fVar9 = fVar18;
    }
    if (fVar11 <= 0.0) goto LAB_18002bfb7;
LAB_18002c091:
    fVar10 = fVar11 - _DAT_1802e8f10;
    if (fVar11 - _DAT_1802e8f10 <= 0.0) {
      fVar10 = fVar18;
    }
  }
  if (_DAT_1802e9020 != 2) {
    uStack_e0 = 0x18002bfe4;
    uVar5 = FUN_18000a050(uVar8 >> 0x20,_DAT_18014ff04);
    uStack_e0 = 0x18002bffb;
    fVar11 = (float)FUN_18000a510(0x1802f7c28,uVar5,_DAT_18014ff08);
    fVar18 = _DAT_18014ff34;
    fVar11 = (float)((_DAT_18014ff20 / (double)fVar11) *
                     (double)(float)(_DAT_18014ff10 & (uint)fVar9) + _DAT_18014ff28);
    if (fVar11 <= 0.0) {
      fVar11 = 0.0;
    }
    fVar10 = fVar10 * fVar11;
    if (_DAT_1802e9020 != 2) {
      fVar11 = _DAT_1802e8f88;
      fVar19 = _DAT_1802e8f50;
      if (_DAT_1802e9020 == 3) {
        fVar19 = _DAT_18014ff30;
        if (_DAT_18014ff30 <= _DAT_1802e8f50) {
          fVar19 = _DAT_1802e8f50;
        }
        if (_DAT_1802e8f88 < _DAT_18014ff30) {
          fVar11 = _DAT_18014ff30;
        }
      }
      fVar19 = fVar19 * _DAT_18014ff34;
      uStack_e0 = 0x18002c1d5;
      uVar5 = FUN_18000a050();
      dVar3 = _DAT_18014ff28;
      uStack_e0 = 0x18002c1f1;
      fVar12 = (float)FUN_18000a510(0x1802f7c48,uVar5,_DAT_18014ff28);
      uStack_e0 = 0x18002c211;
      uVar5 = FUN_18000a050();
      uStack_e0 = 0x18002c224;
      fVar13 = (float)FUN_18000a510(0x1802f7c58,uVar5,dVar3);
      uStack_e0 = 0x18002c24b;
      uVar5 = FUN_18000a510(0x1802f7c68,0x3f8666663f733333,_DAT_18014ff40);
      if (_DAT_1802e9020 == 1) {
        uStack_e0 = 0x18002c28f;
        uVar8 = FUN_18000a1f0();
        uStack_e0 = 0x18002c2b5;
        lVar17 = FUN_18000a1f0();
        uVar8 = uVar8 & 0xffffffff | lVar17 << 0x20;
      }
      else {
        uStack_e0 = 0x18002c2ed;
        uVar5 = FUN_180009e60(CONCAT44(fVar13 * fVar11 * fVar18 * fVar11 * fVar18 * fVar10,
                                       fVar12 * fVar19 * fVar19 * fVar9),uVar5);
        uStack_e0 = 0x18002c2f9;
        uVar8 = FUN_180009e60(uVar5,(float)dVar1);
        if (ABS((float)uVar8) <= (float)((uint)fVar9 & _DAT_18014ff10)) {
          fVar9 = (float)uVar8;
        }
        uVar14 = uVar8 >> 0x20;
        if ((float)((uint)fVar10 & _DAT_18014ff10) < ABS((float)(uVar8 >> 0x20))) {
          uVar14 = (ulonglong)(uint)fVar10;
        }
        uVar8 = (ulonglong)(uint)fVar9 | uVar14 << 0x20;
      }
      fVar9 = (float)uVar8;
      fVar10 = (float)(uVar8 >> 0x20);
      if (_DAT_1802e9020 != 2) {
        uStack_e0 = 0x18002c386;
        uVar5 = FUN_18000a050();
        uStack_e0 = 0x18002c39d;
        fVar11 = (float)FUN_18000a510(0x1802f7c38,uVar5,_DAT_18014ff28);
        fVar10 = fVar10 + fVar11;
      }
      goto LAB_18002c0ba;
    }
  }
  uVar8 = (ulonglong)(uint)fVar9;
  if (DAT_1802e8fa8 == '\0') {
    fVar10 = 0.0;
  }
LAB_18002c0ba:
  if (DAT_1802e8fc8 == '\x01') {
    fVar11 = (float)(_DAT_1802f7c18 & _DAT_18014ff10);
    if ((float)(_DAT_1802f7c1c & _DAT_18014ff10) < (float)((uint)fVar10 & _DAT_18014ff10) &&
        fVar10 != 0.0) {
      fVar10 = fVar10 * ((float)(_DAT_1802f7c1c & _DAT_18014ff10) /
                        (float)((uint)fVar10 & _DAT_18014ff10));
    }
    _DAT_1802f7c18 = 0;
    uVar8 = uVar8 & 0xffffffff;
    if (fVar11 < (float)((uint)fVar9 & _DAT_18014ff10) && fVar9 != 0.0) {
      uVar8 = (ulonglong)(uint)((fVar11 / (float)((uint)fVar9 & _DAT_18014ff10)) * fVar9);
    }
  }
  _DAT_1802f7b58 =
       FUN_180009de0(_DAT_1802f7b58,uVar8 & 0xffffffff | (ulonglong)(uint)fVar10 << 0x20);
  _DAT_1802f7b60 = 0;
  return;
}

// CALLBACK RVA 0x2b5b0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/aim_assist_events/aim_assist_events.c
// Differential report: analysis/module_behavior_recovery/aim_assist_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2b5b0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002b5b0(longlong param_1)

{
  if ((*(longlong *)(param_1 + 0x10) == 0x1802e8cc0) && (*(char *)(param_1 + 0x18) == '\0')) {
    if (_DAT_1802f7be0 != 0) {
      (**(code **)(**(longlong **)(**(longlong **)(param_1 + 8) + 8) + 0xb0))();
    }
    _DAT_1802f7be0 = 0;
    DAT_1802f7bd8 = 0;
  }
  return;
}

// CALLBACK RVA 0x2b610; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/aim_assist_events/aim_assist_events.c
// Differential report: analysis/module_behavior_recovery/aim_assist_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2b610; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18002b610(longlong param_1)

{
  if ((DAT_1802f7c20 == '\x01') && (*(undefined1 *)(param_1 + 8) = 1, DAT_1802e9068 == '\x01')) {
    *(undefined1 *)(param_1 + 9) = 1;
  }
  return;
}

// CALLBACK RVA 0x2b630; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/aim_assist_selection/aim_assist_selection.c
// Differential report: analysis/module_behavior_recovery/aim_assist_selection/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2b630; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002b630(longlong param_1)

{
  longlong *plVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  longlong lVar9;
  double dStack_c0;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined8 uStack_a8;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined8 uStack_88;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined8 uStack_70;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  double dStack_48;
  
  _DAT_1802f7c18 = 0;
  plVar1 = *(longlong **)(param_1 + 8);
  if ((char)plVar1[8] != '\x01') goto LAB_18002b922;
  if (((DAT_1802e90d8 == '\x01') && (_DAT_1802e9020 != 3)) &&
     (cVar2 = FUN_180023690(*plVar1,plVar1[5]), cVar2 == '\0')) {
    DAT_1802f7bd8 = 0;
    return;
  }
  bVar3 = FUN_180029080(plVar1);
  if (DAT_1802e90f8 == '\x01') {
    if (bVar3 == 0) {
      bVar3 = FUN_18000a460(_DAT_18014fef4);
      _DAT_1802f7c78 = bVar3 + 1;
      goto LAB_18002b922;
    }
    if (_DAT_1802f7c78 != 0 && _DAT_1802e9020 < 2) {
      _DAT_1802f7c78 = _DAT_1802f7c78 + -1;
      goto LAB_18002b922;
    }
  }
  if ((((bVar3 & DAT_1802e9118) == 1) && (lVar6 = FUN_180022e10(*plVar1,plVar1[3]), lVar6 != 0)) &&
     (iVar4 = FUN_180024b50(*plVar1,lVar6), iVar4 == 1)) {
    DAT_1802f7bd8 = 0;
    return;
  }
  if ((DAT_1802e9138 != '\x01') || (cVar2 = FUN_1800380b0(*plVar1,plVar1[5]), cVar2 != '\0')) {
    FUN_180023030(&uStack_98,*plVar1,plVar1[5]);
    cVar2 = FUN_180023020(*plVar1);
    if (cVar2 == '\0') {
      uStack_a8 = uStack_88;
      uStack_b8 = uStack_98;
      uStack_b4 = uStack_94;
      uStack_b0 = uStack_90;
      uStack_ac = uStack_8c;
      FUN_180009590(&uStack_80,&uStack_b8);
      uStack_98 = uStack_80;
      uStack_94 = uStack_7c;
      uStack_90 = uStack_78;
      uStack_8c = uStack_74;
      uStack_88 = uStack_70;
    }
    cVar2 = FUN_180029f80();
    if (cVar2 == '\0') {
      uVar7 = FUN_180023170(*plVar1,plVar1[5]);
    }
    else {
      uVar7 = FUN_180029ff0();
    }
    dStack_c0 = (double)_DAT_1802e90b4;
    uStack_58 = _DAT_1802e8f14;
    uStack_54 = 0x7f7fffff;
    uStack_50 = 0x7fffffff;
    uStack_4c = 0;
    if (_DAT_1802e9180 == 0) {
      uStack_68 = _DAT_1802e8f14;
      uStack_64 = 0x7f7fffff;
      uStack_60 = 0x7fffffff;
      uStack_5c = 0;
      dStack_48 = dStack_c0;
      if (_DAT_1802f7be0 != 0) {
        uStack_a8 = uStack_88;
        uStack_b8 = uStack_98;
        uStack_b4 = uStack_94;
        uStack_b0 = uStack_90;
        uStack_ac = uStack_8c;
        cVar2 = FUN_18002c3b0(plVar1,_DAT_1802f7be0,&uStack_b8,uVar7,1,&dStack_48,&uStack_64,
                              &uStack_60,&uStack_5c,&uStack_68,&uStack_80,&DAT_1802f7bd8);
        if (cVar2 != '\0') {
          _DAT_1802f7be8 = _DAT_1802f7c00;
          uRam00000001802f7bf0 = uRam00000001802f7c08;
          _DAT_1802f7bf8 = _DAT_1802f7c10;
          _DAT_1802f7c00 = CONCAT44(uStack_7c,uStack_80);
          uRam00000001802f7c08 = CONCAT44(uStack_74,uStack_78);
          _DAT_1802f7c10 = uStack_70;
          return;
        }
        if (_DAT_1802f7be0 != 0) {
          (**(code **)(**(longlong **)(*plVar1 + 8) + 0xb0))();
        }
        _DAT_1802f7be0 = 0;
        DAT_1802f7bd8 = 0;
      }
    }
    uVar8 = FUN_180024600(*plVar1,plVar1[4]);
    iVar4 = FUN_180024e50(*plVar1,uVar8);
    if (0 < iVar4) {
      iVar4 = 0;
      lVar6 = 0;
      do {
        lVar9 = FUN_180024e80(*plVar1,uVar8,iVar4);
        cVar2 = (**(code **)(**(longlong **)(*plVar1 + 8) + 0xc0))
                          (*(longlong **)(*plVar1 + 8),plVar1[5],lVar9);
        if (cVar2 == '\0') {
          uStack_a8 = uStack_88;
          uStack_b8 = uStack_98;
          uStack_b4 = uStack_94;
          uStack_b0 = uStack_90;
          uStack_ac = uStack_8c;
          cVar2 = FUN_18002c3b0(plVar1,lVar9,&uStack_b8,uVar7,0,&dStack_c0,&uStack_54,&uStack_50,
                                &uStack_4c,&uStack_58,&uStack_80,&dStack_48);
          if (cVar2 != '\0') {
            lVar6 = lVar9;
          }
        }
        iVar4 = iVar4 + 1;
        iVar5 = FUN_180024e50(*plVar1,uVar8);
      } while (iVar4 < iVar5);
      if (lVar6 != 0) {
        cVar2 = (**(code **)(**(longlong **)(*plVar1 + 8) + 0xc0))
                          (*(longlong **)(*plVar1 + 8),_DAT_1802f7be0,lVar6);
        if (cVar2 == '\0') {
          _DAT_1802f7be8 = CONCAT44(uStack_7c,uStack_80);
          uRam00000001802f7bf0 = CONCAT44(uStack_74,uStack_78);
          _DAT_1802f7bf8 = uStack_70;
        }
        else {
          _DAT_1802f7bf8 = _DAT_1802f7c10;
          _DAT_1802f7be8 = _DAT_1802f7c00;
          uRam00000001802f7bf0 = uRam00000001802f7c08;
        }
        _DAT_1802f7c10 = uStack_70;
        uRam00000001802f7c08 = CONCAT44(uStack_74,uStack_78);
        _DAT_1802f7c00 = CONCAT44(uStack_7c,uStack_80);
        DAT_1802f7bd8 = dStack_48._0_1_;
        plVar1 = *(longlong **)(*plVar1 + 8);
        if (_DAT_1802f7be0 != 0) {
          (**(code **)(*plVar1 + 0xb0))(plVar1);
        }
        lVar6 = (**(code **)(*plVar1 + 0xa8))(plVar1,lVar6);
        if (lVar6 != 0) {
          _DAT_1802f7be0 = lVar6;
          return;
        }
        return;
      }
    }
  }
LAB_18002b922:
  if (_DAT_1802f7be0 != 0) {
    (**(code **)(**(longlong **)(*plVar1 + 8) + 0xb0))();
  }
  _DAT_1802f7be0 = 0;
  DAT_1802f7bd8 = 0;
  return;
}

// UI RVA 0x2bae0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2bae0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002bae0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_1801501b4);
  FUN_18000d040(param_2,param_1,0x1802e8ff0);
  if (_DAT_1802e9020 == 3) {
    FUN_18000cef0(param_2,param_1,0x1802e9050);
    FUN_18000cef0(param_2,param_1,0x1802e9030);
  }
  else if (_DAT_1802e9020 == 2) {
    FUN_18000cef0(param_2,param_1,0x1802e8f90);
    goto LAB_18002bb7c;
  }
  FUN_18000cf30(param_2,param_1,0x1802e8f20);
  FUN_18000cf30(param_2,param_1,0x1802e8f58);
LAB_18002bb7c:
  FUN_18000cf30(param_2,param_1,0x1802e9190);
  FUN_18000cf30(param_2,param_1,0x1802e9238);
  FUN_180013e90(param_1,param_2,&UNK_1801501b8);
  FUN_18000cf30(param_2,param_1,0x1802e91c8);
  FUN_18000cf30(param_2,param_1,0x1802e9200);
  FUN_180013e90(param_1,param_2,&UNK_1801501c4);
  FUN_18000d040(param_2,param_1,0x1802e9150);
  if (_DAT_1802e9180 == 1) {
    FUN_18000d040(param_2,param_1,0x1802e92f0);
  }
  else if (_DAT_1802e9180 == 0) {
    FUN_18000cef0(param_2,param_1,0x1802e9290);
  }
  FUN_18000cfb0(param_2,param_1,0x1802e9070);
  FUN_18000cfb0(param_2,param_1,0x1802e8ed0);
  FUN_180013e90(param_1,param_2,&UNK_1801501cb);
  if (_DAT_1802e9020 != 3) {
    FUN_18000cef0(param_2,param_1,0x1802e90c0);
  }
  FUN_18000cef0(param_2,param_1,0x1802e90e0);
  FUN_18000cef0(param_2,param_1,0x1802e8fb0);
  FUN_18000cef0(param_2,param_1,0x1802e9100);
  FUN_18000cef0(param_2,param_1,0x1802e9120);
  FUN_18000cef0(param_2,param_1,0x1802e9270);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802e92c0,0x1802e92b0,&DAT_1802e92c8);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x2bd00; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2bd00; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18002bd00(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c6f0(param_1,&UNK_1801501d6,0x1802e8ff0);
  FUN_18000c450(param_1,&UNK_1801501db,0x1802e8f20);
  FUN_18000c450(param_1,&UNK_1801501e5,0x1802e8f58);
  FUN_18000c3b0(param_1,&UNK_1801501ef,0x1802e8f90);
  FUN_18000c3b0(param_1,&UNK_180150200,0x1802e9050);
  FUN_18000c3b0(param_1,&UNK_180150214,0x1802e9030);
  FUN_18000c450(param_1,&UNK_18015022d,0x1802e9190);
  FUN_18000c450(param_1,&UNK_180150235,0x1802e9238);
  FUN_18000c450(param_1,&UNK_180150247,0x1802e91c8);
  FUN_18000c450(param_1,&UNK_18015025a,0x1802e9200);
  FUN_18000c6f0(param_1,&UNK_18015026d,0x1802e9150);
  FUN_18000c6f0(param_1,&UNK_180150279,0x1802e92f0);
  FUN_18000c3b0(param_1,&UNK_180150281,0x1802e9290);
  FUN_18000c550(param_1,&UNK_180150292,0x1802e9070);
  FUN_18000c550(param_1,&UNK_180150298,0x1802e8ed0);
  FUN_18000c3b0(param_1,&UNK_18015029c,0x1802e90c0);
  FUN_18000c3b0(param_1,&UNK_1801502ab,0x1802e90e0);
  FUN_18000c3b0(param_1,&UNK_1801502c1,0x1802e8fb0);
  FUN_18000c3b0(param_1,&UNK_1801502d5,0x1802e9100);
  FUN_18000c3b0(param_1,&UNK_1801502ec,0x1802e9120);
  FUN_18000c3b0(param_1,&UNK_1801502fb,0x1802e9270);
  uVar1 = uRam00000001802e92c9;
  uVar2 = DAT_1802e92c8;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180150308,DAT_1802e92c8);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802e92c8;
      break;
    case 2:
      uRam00000001802e92c9 = DAT_1802e92c8;
      break;
    case 3:
      uVar2 = uRam00000001802e92c9;
    }
  }
  DAT_1802e92c8 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x2bf00; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2bf00; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002bf00(undefined8 param_1)

{
  FUN_1800ab710(param_1,0x20,&UNK_18015031e,
                *(undefined8 *)((ulonglong)_DAT_1802e9020 * 8 + 0x1802e8fd0));
  return;
}

// CANDIDATE_LOCAL RVA 0x2bf40; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2bf40; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002bf40(ulonglong param_1,undefined8 param_2)

{
  double dVar1;
  undefined8 uVar2;
  ulonglong uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  ulonglong uVar8;
  longlong lVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  
  fVar11 = (float)param_1;
  fVar5 = (float)(param_1 >> 0x20);
  fVar10 = 0.0;
  if (fVar11 <= 0.0) {
    fVar4 = fVar11 + _DAT_1802e8f10;
    if (0.0 <= fVar11 + _DAT_1802e8f10) {
      fVar4 = fVar10;
    }
    if (fVar5 <= 0.0) goto LAB_18002bfb7;
LAB_18002c091:
    fVar11 = fVar5 - _DAT_1802e8f10;
    if (fVar5 - _DAT_1802e8f10 <= 0.0) {
      fVar11 = 0.0;
    }
  }
  else {
    fVar4 = fVar11 - _DAT_1802e8f10;
    if (fVar11 - _DAT_1802e8f10 <= 0.0) {
      fVar4 = fVar10;
    }
    if (0.0 < fVar5) goto LAB_18002c091;
LAB_18002bfb7:
    fVar11 = _DAT_1802e8f10 + fVar5;
    if (0.0 <= _DAT_1802e8f10 + fVar5) {
      fVar11 = fVar10;
    }
  }
  if (_DAT_1802e9020 != 2) {
    uVar2 = FUN_18000a050(param_1 >> 0x20,_DAT_18014ff04);
    fVar5 = (float)FUN_18000a510(0x1802f7c28,uVar2,_DAT_18014ff08);
    fVar10 = _DAT_18014ff34;
    fVar5 = (float)((_DAT_18014ff20 / (double)fVar5) * (double)(float)(_DAT_18014ff10 & (uint)fVar4)
                   + _DAT_18014ff28);
    if (fVar5 <= 0.0) {
      fVar5 = 0.0;
    }
    fVar11 = fVar11 * fVar5;
    if (_DAT_1802e9020 != 2) {
      fVar5 = _DAT_1802e8f88;
      fVar12 = _DAT_1802e8f50;
      if (_DAT_1802e9020 == 3) {
        fVar12 = _DAT_18014ff30;
        if (_DAT_18014ff30 <= _DAT_1802e8f50) {
          fVar12 = _DAT_1802e8f50;
        }
        if (_DAT_1802e8f88 < _DAT_18014ff30) {
          fVar5 = _DAT_18014ff30;
        }
      }
      fVar12 = fVar12 * _DAT_18014ff34;
      uVar2 = FUN_18000a050();
      dVar1 = _DAT_18014ff28;
      fVar6 = (float)FUN_18000a510(0x1802f7c48,uVar2,_DAT_18014ff28);
      uVar2 = FUN_18000a050();
      fVar7 = (float)FUN_18000a510(0x1802f7c58,uVar2,dVar1);
      uVar2 = FUN_18000a510(0x1802f7c68,0x3f8666663f733333,_DAT_18014ff40);
      if (_DAT_1802e9020 == 1) {
        uVar8 = FUN_18000a1f0();
        lVar9 = FUN_18000a1f0();
        uVar8 = uVar8 & 0xffffffff | lVar9 << 0x20;
      }
      else {
        uVar2 = FUN_180009e60(CONCAT44(fVar7 * fVar5 * fVar10 * fVar5 * fVar10 * fVar11,
                                       fVar6 * fVar12 * fVar12 * fVar4),uVar2);
        uVar8 = FUN_180009e60(uVar2,param_2);
        if (ABS((float)uVar8) <= (float)((uint)fVar4 & _DAT_18014ff10)) {
          fVar4 = (float)uVar8;
        }
        uVar3 = uVar8 >> 0x20;
        if ((float)((uint)fVar11 & _DAT_18014ff10) < ABS((float)(uVar8 >> 0x20))) {
          uVar3 = (ulonglong)(uint)fVar11;
        }
        uVar8 = (ulonglong)(uint)fVar4 | uVar3 << 0x20;
      }
      fVar4 = (float)uVar8;
      fVar11 = (float)(uVar8 >> 0x20);
      if (_DAT_1802e9020 != 2) {
        uVar2 = FUN_18000a050();
        fVar5 = (float)FUN_18000a510(0x1802f7c38,uVar2,_DAT_18014ff28);
        fVar11 = fVar11 + fVar5;
      }
      goto LAB_18002c0ba;
    }
  }
  uVar8 = (ulonglong)(uint)fVar4;
  if (DAT_1802e8fa8 == '\0') {
    fVar11 = 0.0;
  }
LAB_18002c0ba:
  if (DAT_1802e8fc8 == '\x01') {
    fVar5 = (float)(_DAT_1802f7c18 & _DAT_18014ff10);
    if ((float)(_DAT_1802f7c1c & _DAT_18014ff10) < (float)((uint)fVar11 & _DAT_18014ff10) &&
        fVar11 != 0.0) {
      fVar11 = fVar11 * ((float)(_DAT_1802f7c1c & _DAT_18014ff10) /
                        (float)((uint)fVar11 & _DAT_18014ff10));
    }
    _DAT_1802f7c18 = 0;
    uVar8 = uVar8 & 0xffffffff;
    if (fVar5 < (float)((uint)fVar4 & _DAT_18014ff10) && fVar4 != 0.0) {
      uVar8 = (ulonglong)(uint)((fVar5 / (float)((uint)fVar4 & _DAT_18014ff10)) * fVar4);
    }
  }
  _DAT_1802f7b58 =
       FUN_180009de0(_DAT_1802f7b58,uVar8 & 0xffffffff | (ulonglong)(uint)fVar11 << 0x20);
  _DAT_1802f7b60 = 0;
  return;
}

// CANDIDATE_LOCAL RVA 0x2c3b0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2c3b0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
FUN_18002c3b0(undefined8 *param_1,undefined8 param_2,double *param_3,undefined8 param_4,char param_5
             ,double *param_6,float *param_7,int *param_8,uint *param_9,float *param_10,
             double *param_11,undefined1 *param_12)

{
  double dVar1;
  double dVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined1 uVar9;
  float fVar10;
  float fVar11;
  uint uVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  double dStack_1c8;
  undefined8 uStack_1c0;
  undefined8 uStack_1b8;
  double dStack_1a8;
  undefined8 uStack_1a0;
  undefined4 uStack_198;
  undefined4 uStack_194;
  undefined4 uStack_190;
  undefined4 uStack_18c;
  undefined4 uStack_188;
  undefined4 uStack_184;
  undefined4 uStack_180;
  undefined4 uStack_17c;
  double dStack_178;
  double dStack_170;
  double dStack_168;
  double dStack_158;
  undefined8 uStack_150;
  undefined8 uStack_148;
  undefined4 uStack_140;
  undefined4 uStack_13c;
  double dStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  double dStack_108;
  double dStack_100;
  undefined8 uStack_f8;
  undefined4 uStack_f0;
  undefined4 uStack_ec;
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  undefined4 uStack_e0;
  undefined4 uStack_dc;
  undefined1 auStack_d8 [16];
  double dStack_c8;
  
  cVar3 = FUN_1800237b0(*param_1);
  if ((((cVar3 != '\0') || (cVar3 = FUN_1800240a0(*param_1,param_2), cVar3 != '\0')) ||
      ((DAT_1802e9288 == '\x01' &&
       (cVar3 = FUN_180023f60(*param_1,param_2,param_1[5]), cVar3 != '\0')))) ||
     (cVar3 = FUN_18002ace0(*param_1,param_2,7), cVar3 != '\0')) {
    return 0;
  }
  FUN_180023030(&dStack_128,*param_1,param_2);
  if (0.0 < _DAT_1802e91c0) {
    FUN_180024160(&dStack_1a8,*param_1,param_2);
    uStack_148 = uStack_118;
    dStack_158 = dStack_128;
    uStack_150 = uStack_120;
    FUN_180009460(&dStack_108,&dStack_158,auStack_d8,(double)_DAT_1802e91c0);
    dStack_128 = dStack_108;
    uStack_120 = dStack_100;
    uStack_118 = uStack_f8;
  }
  uVar8 = *param_1;
  uVar7 = FUN_180023670(uVar8,param_2);
  FUN_180025640(&dStack_1a8,uVar8,uVar7);
  uStack_148 = CONCAT44(uStack_194,uStack_198);
  uStack_140 = uStack_190;
  uStack_13c = uStack_18c;
  dStack_158 = dStack_1a8;
  uStack_150 = uStack_1a0;
  FUN_180009770(&dStack_108,&dStack_158,(int)_DAT_18014ff70);
  uStack_188 = uStack_e8;
  uStack_184 = uStack_e4;
  uStack_180 = uStack_e0;
  uStack_17c = uStack_dc;
  uStack_198 = (undefined4)uStack_f8;
  uStack_194 = uStack_f8._4_4_;
  uStack_190 = uStack_f0;
  uStack_18c = uStack_ec;
  dStack_1a8 = dStack_108;
  uStack_1a0 = dStack_100;
  dStack_c8 = param_3[2];
  auStack_d8._0_8_ = *param_3;
  auStack_d8._8_8_ = param_3[1];
  FUN_180009880(&dStack_158,&dStack_108,auStack_d8);
  uStack_f8 = param_3[2];
  dStack_108 = *param_3;
  dStack_100 = param_3[1];
  dStack_c8 = (double)uStack_148;
  auStack_d8._0_8_ = dStack_158;
  auStack_d8._8_8_ = uStack_150;
  dVar13 = (double)FUN_1800094f0(&dStack_108,auStack_d8);
  dVar14 = (double)_DAT_1802e90b0;
  if (*param_6 <= dVar13 && dVar13 != *param_6) {
    return 0;
  }
  dStack_c8 = (double)uStack_118;
  auStack_d8._8_8_ = uStack_120;
  auStack_d8._0_8_ = dStack_128;
  FUN_180009590(&dStack_108,auStack_d8);
  if (_DAT_1802e91f8 <= 0.0) {
    uVar4 = SUB84(dStack_108,0);
    uVar16 = (undefined4)((ulonglong)dStack_108 >> 0x20);
    uVar17 = SUB84(uStack_f8,0);
    uVar18 = (undefined4)((ulonglong)uStack_f8 >> 0x20);
  }
  else {
    fVar10 = _DAT_1802e91f8;
    if (dVar13 < _DAT_18014ff78) {
      fVar10 = (float)((double)_DAT_1802e91f8 * (dVar13 / _DAT_18014ff78));
    }
    dStack_168 = uStack_f8;
    dStack_178 = dStack_108;
    dStack_170 = dStack_100;
    uStack_1b8 = uStack_148;
    dStack_1c8 = dStack_158;
    uStack_1c0 = uStack_150;
    FUN_180009460(auStack_d8,&dStack_178,&dStack_1c8,(double)fVar10);
    uVar4 = auStack_d8._0_4_;
    uVar16 = auStack_d8._4_4_;
    uVar17 = SUB84(dStack_c8,0);
    uVar18 = (undefined4)((ulonglong)dStack_c8 >> 0x20);
  }
  dVar15 = (double)FUN_18000a2d0(dStack_100,(int)uStack_150,SUB84((double)_DAT_1802e9230,0));
  fVar10 = (float)FUN_180097c70((float)((*param_3 + param_3[1] + param_3[2] +
                                         (double)CONCAT44(uVar16,uVar4) + dVar15 +
                                        (double)CONCAT44(uVar18,uVar17)) * _DAT_18014ff80));
  fVar11 = (float)FUN_180097c70();
  dVar1 = (double)fVar10 * _DAT_18014ff90;
  dVar2 = (double)fVar11 * _UNK_18014ff98;
  fVar10 = (float)FUN_180097c70();
  dStack_c8 = (double)fVar10 * _DAT_18014ffa0;
  fVar10 = _DAT_1802e9268;
  if (dVar13 < _DAT_18014ff78) {
    fVar10 = (float)((double)_DAT_1802e9268 *
                    ((dVar13 / _DAT_18014ff78) * _DAT_18014ffa8 + _DAT_18014ff80));
  }
  auStack_d8._8_4_ = SUB84(dVar2,0);
  auStack_d8._0_8_ = dVar1;
  auStack_d8._12_4_ = (int)((ulonglong)dVar2 >> 0x20);
  FUN_180009430(&dStack_108,auStack_d8,SUB84((double)fVar10,0));
  auStack_d8._0_8_ = CONCAT44(uVar16,uVar4);
  dStack_c8 = (double)CONCAT44(uVar18,uVar17);
  dStack_178 = dStack_108;
  dStack_170 = dStack_100;
  dStack_168 = uStack_f8;
  auStack_d8._8_8_ = dVar15;
  FUN_180009400(&dStack_108,auStack_d8,&dStack_178);
  dVar15 = uStack_f8;
  dVar2 = dStack_100;
  dVar1 = dStack_108;
  auStack_d8._0_8_ = dStack_108;
  auStack_d8._8_8_ = dStack_100;
  dStack_c8 = uStack_f8;
  dStack_108 = *param_3;
  dStack_100 = param_3[1];
  uStack_f8 = param_3[2];
  uVar8 = FUN_180009f80(&dStack_108,auStack_d8);
  uVar4 = FUN_180009e20(uVar8,param_4);
  uVar12 = FUN_18000a210(uVar4);
  fVar10 = (float)(uVar12 & (uint)DAT_18014ffb0);
  uVar9 = dVar14 <= dVar13;
  if ((*param_10 <= fVar10 && fVar10 != *param_10) && (uVar9 = DAT_1802e92a8, param_5 == '\0')) {
    return 0;
  }
  fVar11 = (float)FUN_180023a40(*param_1,param_2);
  if (*param_7 <= fVar11 && fVar11 != *param_7) {
    return 0;
  }
  iVar5 = FUN_1800239f0(*param_1,param_2);
  if (*param_8 < iVar5) {
    return 0;
  }
  if (DAT_1802e92c8 == '\x01') {
    uStack_f8 = param_3[2];
    dStack_108 = *param_3;
    dStack_100 = param_3[1];
    auStack_d8._0_8_ = dVar1;
    auStack_d8._8_8_ = dVar2;
    dStack_c8 = dVar15;
    cVar3 = FUN_180029000(*param_1,param_1[4],&dStack_108,auStack_d8);
    if (cVar3 == '\0') {
      return 0;
    }
  }
  if (_DAT_1802e9180 == 0) {
LAB_18002c964:
    *param_10 = fVar10;
  }
  else {
    switch(_DAT_1802e9320) {
    case 0:
      *param_6 = dVar13;
      break;
    case 1:
      *param_7 = fVar11;
      break;
    case 2:
      iVar6 = FUN_180023720(*param_1,param_2);
      uVar12 = iVar6 + (int)lRam00000001802f7c80;
      uVar12 = (uVar12 >> 0x10 ^ uVar12) * 0x45d9f3b;
      uVar12 = (uVar12 >> 0x10 ^ uVar12) * 0x45d9f3b;
      uVar12 = uVar12 >> 0x10 ^ uVar12;
      lRam00000001802f7c80 = lRam00000001802f7c80 + 1;
      if ((iVar5 == *param_8) && (uVar12 < *param_9)) {
        return 0;
      }
      *param_8 = iVar5;
      *param_9 = uVar12;
      break;
    case 3:
      goto LAB_18002c964;
    }
  }
  *param_11 = dVar1;
  param_11[1] = dVar2;
  param_11[2] = dVar15;
  *param_12 = uVar9;
  return 1;
}

