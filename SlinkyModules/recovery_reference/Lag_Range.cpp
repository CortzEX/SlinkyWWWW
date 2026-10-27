// Recovered decompiler view: Lag Range
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x3a3c0, 0x3ad10); proximity does not prove ownership.

// CALLBACK RVA 0x3a3c0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/lag_range_packet/lag_range_packet.c
// Differential report: analysis/module_behavior_recovery/lag_range_packet/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3a3c0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003a3c0(longlong param_1)

{
  char cVar1;
  int iVar2;
  longlong lVar3;
  double dVar4;
  double dVar5;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined8 uStack_38;
  undefined1 uStack_29;
  
  do {
    cVar1 = DAT_1802fc7c8;
    LOCK();
    DAT_1802fc7c8 = '\x01';
    UNLOCK();
    uStack_29 = cVar1 != '\0';
  } while ((bool)uStack_29);
  if (_DAT_1802fc7c0 < *(int *)(param_1 + 0x20)) {
    if (((DAT_1802fc7f8 != '\0') &&
        (lVar3 = FUN_180026350(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10)),
        lVar3 != 0)) && (cVar1 = FUN_180026390(*(undefined8 *)(param_1 + 8),lVar3), cVar1 != '\0'))
    {
      FUN_180026450(&uStack_80,*(undefined8 *)(param_1 + 8),lVar3);
      uStack_58 = _DAT_1802fc7f0;
      uStack_68 = _DAT_1802fc7e0;
      uStack_60 = uRam00000001802fc7e8;
      uStack_38 = _DAT_1802fc818;
      uStack_48 = _DAT_1802fc808;
      uStack_44 = DAT_1802fc808_4;
      uStack_40 = (undefined4)uRam00000001802fc810;
      uStack_3c = uRam00000001802fc810._4_4_;
      dVar4 = (double)FUN_1800094b0(&uStack_68,&uStack_48);
      uStack_58 = _DAT_1802fc7f0;
      uStack_68 = _DAT_1802fc7e0;
      uStack_60 = uRam00000001802fc7e8;
      uStack_38 = uStack_70;
      uStack_48 = uStack_80;
      uStack_44 = uStack_7c;
      uStack_40 = uStack_78;
      uStack_3c = uStack_74;
      dVar5 = (double)FUN_1800094b0(&uStack_68,&uStack_48);
      DAT_1802fc7d8 = dVar5 < dVar4;
    }
    _DAT_1802fc7c0 = *(int *)(param_1 + 0x20);
  }
  if ((((DAT_1802fc7f8 == '\0') || (DAT_1802fc7d8 == '\0')) ||
      ((DAT_1802fc7d9 != '\0' || ((DAT_1802fc7db != '\0' || (DAT_1802fc7da != '\0')))))) ||
     (_DAT_1802fc7d0 <= *(longlong *)(param_1 + 0x18))) {
    if (*(int *)(param_1 + 0x24) == 0) {
      lVar3 = FUN_180026350(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10));
      if (lVar3 == 0) {
        lVar3 = FUN_1800265e0(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10));
        if ((lVar3 == 0) || (DAT_1802fc7d9 == '\0')) {
          if ((lVar3 == 0) &&
             (((lVar3 = FUN_180026620(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10)),
               lVar3 != 0 && (DAT_1802fc7da != '\0')) &&
              (iVar2 = FUN_180026660(*(undefined8 *)(param_1 + 8),lVar3), iVar2 == 4)))) {
            _DAT_1802fc7da = 0x100;
          }
        }
        else {
          DAT_1802fc7d9 = '\0';
          _DAT_1802fc7da = CONCAT11(1,DAT_1802fc7da);
        }
      }
      else {
        _DAT_1802fc7da = _DAT_1802fc7da & 0xff;
        cVar1 = FUN_180026390(*(undefined8 *)(param_1 + 8),lVar3);
        if (cVar1 != '\0') {
          FUN_180026450(&uStack_80,*(undefined8 *)(param_1 + 8),lVar3);
          _DAT_1802fc818 = uStack_70;
          _DAT_1802fc808 = CONCAT44(uStack_7c,uStack_80);
          uRam00000001802fc810 = CONCAT44(uStack_74,uStack_78);
        }
      }
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x24) = 1;
  }
  DAT_1802fc7c8 = 0;
  return;
}

// CALLBACK RVA 0x3a610; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/lag_range_render/lag_range_render.c
// Differential report: analysis/module_behavior_recovery/lag_range_render/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3a610; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003a610(longlong param_1)

{
  undefined1 auStack_70 [24];
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined8 uStack_48;
  double dStack_38;
  double dStack_30;
  double dStack_28;
  
  if (DAT_1802fc820 == '\x01') {
    dStack_28 = _DAT_1802fc838;
    dStack_38 = _DAT_1802fc828;
    dStack_30 = dRam00000001802fc830;
    uStack_48 = _DAT_1802fc850;
    uStack_58 = _DAT_1802fc840;
    uStack_54 = uRam00000001802fc844;
    uStack_50 = uRam00000001802fc848;
    uStack_4c = uRam00000001802fc84c;
    FUN_180009460(auStack_70,&dStack_38,&uStack_58,(double)*(float *)(param_1 + 0x28));
    uStack_48 = *(undefined8 *)(param_1 + 0x18);
    uStack_58 = *(undefined4 *)(param_1 + 8);
    uStack_54 = *(undefined4 *)(param_1 + 0xc);
    uStack_50 = *(undefined4 *)(param_1 + 0x10);
    uStack_4c = *(undefined4 *)(param_1 + 0x14);
    FUN_1800093d0(&dStack_38,auStack_70,&uStack_58);
    FUN_1800293c0();
    (*(code *)*_DAT_180150cb0)(_DAT_1802efc00);
    (*(code *)*_DAT_180150cc0)();
    (*(code *)*_DAT_180150cd8)
              ((float)dStack_38,
               CONCAT44((int)((ulonglong)(dStack_30 + _DAT_180152ed8) >> 0x20),
                        (float)(dStack_30 + _DAT_180152ed8)),(float)dStack_28);
    (*(code *)*_DAT_180150cd0)(_DAT_180152ee4,_DAT_180152ee0,_DAT_180152ee4);
    if (DAT_1802efc40 == '\x01') {
      (*(code *)*_DAT_18013e448)(_DAT_1802efc10,_DAT_1802efc14,_DAT_1802efc18,_DAT_180152ee8);
      FUN_180029400();
    }
    (*(code *)*_DAT_180150ca0)(_DAT_1802efc10,_DAT_1802efc14,_DAT_1802efc18);
    FUN_180029430();
    (*(code *)*_DAT_180150cb8)();
    FUN_1800295a0();
  }
  return;
}

// CALLBACK RVA 0x3a780; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/lag_range_packet/lag_range_packet.c
// Differential report: analysis/module_behavior_recovery/lag_range_packet/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3a780; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003a780(longlong param_1)

{
  undefined8 *puVar1;
  int iVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x10) == '\x01') {
    puVar1 = *(undefined8 **)(param_1 + 8);
    iVar2 = FUN_180023760(*puVar1,puVar1[5]);
    iVar3 = FUN_1800239d0(*puVar1,puVar1[5]);
    DAT_1802fc858 = iVar2 == iVar3;
  }
  return;
}

// CALLBACK RVA 0x3a7d0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/lag_range_update/lag_range_update.c
// Differential report: analysis/module_behavior_recovery/lag_range_update/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3a7d0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003a7d0(longlong param_1)

{
  double dVar1;
  undefined8 *puVar2;
  uint uVar3;
  byte bVar4;
  char cVar5;
  byte bVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  undefined8 uVar10;
  longlong lVar11;
  longlong lVar12;
  ulonglong uVar13;
  undefined1 uVar14;
  bool bVar15;
  float fVar16;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined8 uStack_78;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  
  bVar4 = DAT_1802fc858;
  DAT_1802fc858 = 0;
  puVar2 = *(undefined8 **)(param_1 + 8);
  iVar8 = _DAT_1802fc85c;
  if ((*(char *)(puVar2 + 8) == '\x01') &&
     ((DAT_1802efc98 != '\x01' ||
      (cVar5 = FUN_1800380b0(*puVar2,puVar2[5]), iVar8 = _DAT_1802fc85c, cVar5 != '\0')))) {
    if (DAT_1802efcb8 == '\x01') {
      uVar10 = FUN_180023f40(*puVar2,puVar2[5]);
      uVar7 = FUN_180025a60(*puVar2,uVar10);
      lVar11 = FUN_180026140(*puVar2,uVar10,uVar7);
      if (((lVar11 != 0) && (lVar12 = FUN_180028a50(*puVar2,puVar2[5]), lVar12 != 0)) &&
         (iVar8 = FUN_180025c50(*puVar2,lVar12), iVar8 == 0x175)) {
        uVar13 = FUN_180025dc0(*puVar2,lVar11);
        iVar8 = 0xf;
        if ((uVar13 & 0x4000) != 0) goto LAB_18003a9c2;
      }
      if (0 < _DAT_1802fc85c) {
        iVar8 = _DAT_1802fc85c + -1;
        goto LAB_18003a9c2;
      }
    }
    bVar6 = FUN_180023690(*puVar2,puVar2[5]);
    uVar7 = 0;
    if ((DAT_1802fc859 & 1) != 0) {
      uVar7 = _DAT_1802efcd8;
    }
    uVar14 = (undefined1)uVar7;
    if (bVar6 != 0) {
      uVar14 = 0;
    }
    DAT_1802fc859 = bVar6;
    FUN_180023030(&uStack_68,*puVar2,puVar2[5]);
    cVar5 = FUN_180023020(*puVar2);
    if (cVar5 != '\0') {
      uStack_78 = uStack_58;
      uStack_88 = (undefined4)uStack_68;
      uStack_84 = uStack_68._4_4_;
      uStack_80 = (undefined4)uStack_60;
      uStack_7c = uStack_60._4_4_;
      FUN_1800095c0(&uStack_b8,&uStack_88);
      uStack_68 = uStack_b8;
      uStack_60 = uStack_b0;
      uStack_58 = uStack_a8;
    }
    lVar11 = puVar2[7];
    iVar8 = _DAT_1802fc85c;
    if (*(longlong *)(lVar11 + 8) != 0) {
      dVar1 = *(double *)(lVar11 + 0x10);
      uVar10 = FUN_18000a050(_DAT_180152ef0,_DAT_180152ef4);
      fVar16 = (float)FUN_18000a510(0x1802fc860,uVar10,_DAT_180152ef8);
      iVar8 = _DAT_1802fc85c;
      if (dVar1 <= (double)fVar16 * (double)fVar16) {
        iVar8 = FUN_1800239f0(*puVar2,*(undefined8 *)(lVar11 + 8));
        if (DAT_1802efcf8 == '\x01') {
          uVar10 = FUN_180022cf0(*puVar2,puVar2[3]);
          iVar9 = FUN_180025310(*puVar2,uVar10);
          bVar15 = iVar9 != 0;
        }
        else {
          bVar15 = false;
        }
        FUN_180024160(&uStack_a0,*puVar2,*(undefined8 *)(lVar11 + 8));
        uVar3 = _DAT_1802fc7d8;
        do {
          cVar5 = DAT_1802fc7c8;
          LOCK();
          DAT_1802fc7c8 = '\x01';
          UNLOCK();
        } while (cVar5 != '\0');
        DAT_1802fc7db = SUB41(uVar3,3);
        _DAT_1802fc7d8 = CONCAT12(uVar14,CONCAT11(bVar4 & iVar8 < 5,DAT_1802fc7d8));
        if (DAT_1802fc820 == '\x01') {
          _DAT_1802fc838 = _DAT_1802fc850;
        }
        else {
          _DAT_1802fc838 = _DAT_1802fc818;
          _DAT_1802fc840 = _DAT_1802fc808;
          DAT_1802fc840_4 = uRam00000001802fc80c;
          uRam00000001802fc848._0_4_ = uRam00000001802fc810;
          uRam00000001802fc848._4_4_ = uRam00000001802fc814;
        }
        if (!bVar15) {
          DAT_1802fc7c8 = 0;
          _DAT_1802fc7d0 = (longlong)_DAT_1802efc78;
          _DAT_1802fc7e0 = uStack_a0;
          uRam00000001802fc7e8 = uStack_98;
          _DAT_1802fc7f0 = uStack_90;
          DAT_1802fc7f8 = 1;
          DAT_1802fc820 = 0;
          _DAT_1802fc828 = _DAT_1802fc840;
          uRam00000001802fc82c = DAT_1802fc840_4;
          uRam00000001802fc830 = (undefined4)uRam00000001802fc848;
          uRam00000001802fc834 = uRam00000001802fc848._4_4_;
          _DAT_1802fc840 = CONCAT44(uRam00000001802fc80c,_DAT_1802fc808);
          uRam00000001802fc848 = CONCAT44(uRam00000001802fc814,uRam00000001802fc810);
          _DAT_1802fc850 = _DAT_1802fc818;
          return;
        }
        DAT_1802fc7c8 = 0;
        _DAT_1802fc7d0 = (longlong)_DAT_1802efc78;
        _DAT_1802fc7e0 = uStack_a0;
        uRam00000001802fc7e8 = uStack_98;
        _DAT_1802fc7f0 = uStack_90;
        DAT_1802fc7f8 = 1;
        DAT_1802fc820 = DAT_1802fc7d8;
        _DAT_1802fc828 = _DAT_1802fc840;
        uRam00000001802fc82c = DAT_1802fc840_4;
        uRam00000001802fc830 = (undefined4)uRam00000001802fc848;
        uRam00000001802fc834 = uRam00000001802fc848._4_4_;
        _DAT_1802fc840 = CONCAT44(uRam00000001802fc80c,_DAT_1802fc808);
        uRam00000001802fc848 = CONCAT44(uRam00000001802fc814,uRam00000001802fc810);
        _DAT_1802fc850 = _DAT_1802fc818;
        return;
      }
    }
  }
LAB_18003a9c2:
  do {
    _DAT_1802fc85c = iVar8;
    cVar5 = DAT_1802fc7c8;
    LOCK();
    DAT_1802fc7c8 = '\x01';
    UNLOCK();
    iVar8 = _DAT_1802fc85c;
  } while (cVar5 != '\0');
  _DAT_1802fc7d8 = _DAT_1802fc7d8 & 0xff;
  DAT_1802fc820 = 0;
  DAT_1802fc7f8 = 0;
  DAT_1802fc7c8 = 0;
  return;
}

// UI RVA 0x3ab00; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3ab00; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003ab00(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180152f9e);
  FUN_18000cf30(param_2,param_1,0x1802efc48);
  FUN_180013e90(param_1,param_2,&UNK_180152fa3);
  FUN_18000cef0(param_2,param_1,0x1802efcc0);
  FUN_18000cef0(param_2,param_1,0x1802efca0);
  FUN_180013e90(param_1,param_2,&UNK_180152fac);
  FUN_18000cef0(param_2,param_1,0x1802efce0);
  if (DAT_1802efcf8 == '\x01') {
    FUN_18000d0a0(param_2,param_1,0x1802efc08);
    FUN_18000cf30(param_2,param_1,0x1802efbd0);
    FUN_18000cef0(param_2,param_1,0x1802efc28);
  }
  FUN_180013e90(param_1,param_2,&UNK_180152fc4);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802efc90,0x1802efc80,&DAT_1802efc98);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x3ac00; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3ac00; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003ac00(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c450(param_1,&UNK_180152fcf,0x1802efc48);
  FUN_18000c3b0(param_1,&UNK_180152fd5,0x1802efcc0);
  FUN_18000c3b0(param_1,&UNK_180152fe8,0x1802efca0);
  FUN_18000c3b0(param_1,&UNK_180152ffc,0x1802efce0);
  FUN_18000c7e0(param_1,&UNK_18015300e,0x1802efc08);
  FUN_18000c450(param_1,&UNK_18015301e,0x1802efbd0);
  FUN_18000c3b0(param_1,&UNK_180153033,0x1802efc28);
  uVar1 = uRam00000001802efc99;
  uVar2 = DAT_1802efc98;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180153044,DAT_1802efc98);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802efc98;
      break;
    case 2:
      uRam00000001802efc99 = DAT_1802efc98;
      break;
    case 3:
      uVar2 = uRam00000001802efc99;
    }
  }
  DAT_1802efc98 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x3acd0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3acd0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003acd0(void)

{
  FUN_1800ab710(_DAT_1802efc78,0x20,&UNK_180153053,(double)_DAT_1802efc78);
  return;
}

