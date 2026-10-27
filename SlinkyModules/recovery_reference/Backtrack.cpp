// Recovered decompiler view: Backtrack
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x35fd0, 0x37020); proximity does not prove ownership.

// CALLBACK RVA 0x35fd0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/backtrack_packet/backtrack_packet.c
// Differential report: analysis/module_behavior_recovery/backtrack_packet/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x35fd0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180035fd0(longlong param_1)

{
  undefined8 *puVar1;
  char cVar2;
  int iVar3;
  longlong lVar4;
  
  do {
    cVar2 = DAT_1802fc458;
    LOCK();
    DAT_1802fc458 = '\x01';
    UNLOCK();
  } while (cVar2 != '\0');
  if (DAT_1802fc470 != '\x01') {
    DAT_1802fc458 = 0;
    return;
  }
  lVar4 = FUN_180026a30(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10));
  if (lVar4 == 0) {
    lVar4 = FUN_180026ad0(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10));
    if ((lVar4 != 0) ||
       (lVar4 = FUN_180026a90(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10)),
       lVar4 != 0)) goto LAB_1800360b8;
  }
  else {
    iVar3 = FUN_180026a70(*(undefined8 *)(param_1 + 8),lVar4);
    if (iVar3 == _DAT_1802fc468) {
LAB_1800360b8:
      *(undefined4 *)(param_1 + 0x24) = 3;
      DAT_1802fc458 = 0;
      return;
    }
  }
  puVar1 = (undefined8 *)(param_1 + 8);
  lVar4 = FUN_1800266b0(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10));
  if (lVar4 == 0) {
    lVar4 = FUN_180026b10(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10));
    if (lVar4 != 0) {
      DAT_1802fc458 = 0;
      DAT_1802fc470 = 0;
      return;
    }
  }
  else if ((DAT_1802fc471 != '\0') &&
          (iVar3 = FUN_1800266f0(*puVar1,lVar4), iVar3 == _DAT_1802fc46c)) {
    DAT_1802fc458 = 0;
    DAT_1802fc470 = 0;
    return;
  }
  if (*(longlong *)(param_1 + 0x18) <= _DAT_1802fc460) {
    *(undefined4 *)(param_1 + 0x24) = 1;
    if (_DAT_1802fc450 < *(int *)(param_1 + 0x20)) {
      _DAT_1802fc450 = *(int *)(param_1 + 0x20);
      FUN_1800369d0(puVar1,0);
      DAT_1802fc458 = 0;
      return;
    }
    DAT_1802fc458 = 0;
    return;
  }
  if (*(int *)(param_1 + 0x24) == 0) {
    if (_DAT_1802fc454 < *(int *)(param_1 + 0x20)) {
      FUN_1800369d0(puVar1,1);
      _DAT_1802fc454 = *(undefined4 *)(param_1 + 0x20);
      DAT_1802fc458 = 0;
      return;
    }
    DAT_1802fc458 = 0;
    return;
  }
  DAT_1802fc458 = 0;
  return;
}

// CALLBACK RVA 0x36110; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/backtrack_render/backtrack_render.c
// Differential report: analysis/module_behavior_recovery/backtrack_render/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x36110; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180036110(longlong param_1)

{
  float fVar1;
  double dVar2;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined8 uStack_78;
  undefined8 uStack_68;
  undefined8 uStack_60;
  double dStack_58;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined8 uStack_38;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  double dStack_18;
  
  if (DAT_1802fc4a0 == '\x01') {
    dStack_58 = _DAT_1802fc4b8;
    uStack_68 = _DAT_1802fc4a8;
    uStack_60 = uRam00000001802fc4b0;
    uStack_38 = _DAT_1802fc4d0;
    _uStack_48 = CONCAT44(uRam00000001802fc4c4,_DAT_1802fc4c0);
    _uStack_40 = CONCAT44(uRam00000001802fc4cc,uRam00000001802fc4c8);
    FUN_180009460(&uStack_28,&uStack_68,&uStack_48,(double)*(float *)(param_1 + 0x28));
    uStack_38 = dStack_18;
    uStack_78 = *(undefined8 *)(param_1 + 0x18);
    uStack_88 = *(undefined4 *)(param_1 + 8);
    uStack_84 = *(undefined4 *)(param_1 + 0xc);
    uStack_80 = *(undefined4 *)(param_1 + 0x10);
    uStack_7c = *(undefined4 *)(param_1 + 0x14);
    FUN_1800093d0(&uStack_68,&uStack_48,&uStack_88);
    uStack_28 = (undefined4)uStack_68;
    uStack_24 = uStack_68._4_4_;
    uStack_20 = (undefined4)uStack_60;
    uStack_1c = uStack_60._4_4_;
    dStack_18 = dStack_58;
    FUN_1800293c0();
    (*(code *)*_DAT_180150cb0)(_DAT_1802edd10);
    (*(code *)*_DAT_180150cc0)();
    dVar2 = (double)CONCAT44(uStack_1c,uStack_20) + _DAT_180152178;
    (*(code *)*_DAT_180150cd8)
              ((float)(double)CONCAT44(uStack_24,uStack_28),
               CONCAT44((int)((ulonglong)dVar2 >> 0x20),(float)dVar2),(float)dStack_18);
    (*(code *)*_DAT_180150cd0)(_DAT_180152184,_DAT_180152180,_DAT_180152184);
    if (DAT_1802edd50 == '\x01') {
      fVar1 = (float)FUN_18000a2b0(_DAT_1802fc4d8,_DAT_1802fc4dc,*(undefined4 *)(param_1 + 0x28));
      (*(code *)*_DAT_180150cc8)(_DAT_180152188 - fVar1,0,_DAT_180152180,0);
    }
    if (DAT_1802edd70 == '\x01') {
      (*(code *)*_DAT_18013e448)(_DAT_1802edd20,_DAT_1802edd24,_DAT_1802edd28,_DAT_18015218c);
      FUN_180029400();
    }
    (*(code *)*_DAT_180150ca0)(_DAT_1802edd20,_DAT_1802edd24,_DAT_1802edd28);
    FUN_180029430();
    (*(code *)*_DAT_180150cb8)();
    FUN_1800295a0();
  }
  return;
}

// CALLBACK RVA 0x362e0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/backtrack_update/backtrack_update.c
// Differential report: analysis/module_behavior_recovery/backtrack_update/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x362e0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800362e0(longlong param_1)

{
  undefined8 *puVar1;
  longlong lVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  bool bVar7;
  double dVar8;
  undefined4 uVar9;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  undefined4 uStack_e0;
  undefined4 uStack_dc;
  undefined8 uStack_d8;
  undefined1 auStack_d0 [16];
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined1 auStack_98 [16];
  undefined8 uStack_88;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined8 uStack_68;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined1 uStack_32;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  if ((_DAT_1802fc4e0 < 1) ||
     (iVar4 = _DAT_1802fc4e0 + -1, bVar7 = _DAT_1802fc4e0 == 1, _DAT_1802fc4e0 = iVar4, bVar7)) {
    if (((*(char *)(puVar1 + 8) == '\x01') &&
        ((DAT_1802ede88 != '\x01' || (cVar3 = FUN_180029080(puVar1), cVar3 != '\0')))) &&
       ((DAT_1802edea8 != '\x01' || (cVar3 = FUN_1800380b0(*puVar1,puVar1[5]), cVar3 != '\0')))) {
      iVar4 = FUN_1800239d0(*puVar1,puVar1[5]);
      iVar5 = FUN_180023760(*puVar1,puVar1[5]);
      if ((((iVar5 - iVar4 < 0x15) && (lVar2 = puVar1[7], *(longlong *)(lVar2 + 8) != 0)) &&
          (iVar4 = FUN_1800239f0(*puVar1), (float)iVar4 <= _DAT_1802edda8)) &&
         (((double)(_DAT_1802eddf0 * _DAT_1802eddf0) <= *(double *)(lVar2 + 0x10) &&
          (*(double *)(lVar2 + 0x10) <= (double)(_DAT_1802eddf4 * _DAT_1802eddf4))))) {
        FUN_180023030(&uStack_78,*puVar1,puVar1[5]);
        cVar3 = FUN_180023020(*puVar1);
        if (cVar3 != '\0') {
          uStack_88 = uStack_68;
          FUN_1800095c0(&uStack_58,auStack_98);
          uStack_78 = (undefined4)uStack_58;
          uStack_74 = uStack_58._4_4_;
          uStack_70 = (undefined4)uStack_50;
          uStack_6c = uStack_50._4_4_;
          uStack_68 = uStack_48;
        }
        FUN_180024160(auStack_d0,*puVar1,*(undefined8 *)(lVar2 + 8));
        uVar6 = FUN_180023170(*puVar1,*(undefined8 *)(lVar2 + 8));
        iVar5 = FUN_180023720(*puVar1,*(undefined8 *)(lVar2 + 8));
        _DAT_1802fc46c = FUN_180023720(*puVar1,puVar1[5]);
        iVar4 = _DAT_1802fc468;
        do {
          cVar3 = DAT_1802fc458;
          LOCK();
          DAT_1802fc458 = '\x01';
          UNLOCK();
          uStack_32 = cVar3 != '\0';
        } while ((bool)uStack_32);
        _DAT_1802fc460 = (longlong)_DAT_1802ede30;
        DAT_1802fc471 = DAT_1802edec8;
        _DAT_1802fc468 = iVar5;
        if (DAT_1802fc470 != '\x01') {
          uStack_48 = uStack_68;
          uStack_58._0_4_ = uStack_78;
          uStack_58._4_4_ = uStack_74;
          uStack_50._0_4_ = uStack_70;
          uStack_50._4_4_ = uStack_6c;
          cVar3 = FUN_180036f60(puVar1,*(undefined8 *)(lVar2 + 8),&uStack_58);
          if (cVar3 != '\0') {
            DAT_1802fc470 = 1;
            FUN_1800093b0(&uStack_58);
            _DAT_1802fc488 = uStack_48;
            _DAT_1802fc478 = CONCAT44(uStack_58._4_4_,(undefined4)uStack_58);
            uRam00000001802fc480 = CONCAT44(uStack_50._4_4_,(undefined4)uStack_50);
            DAT_1802fc490 = 0;
            DAT_1802fc498 = 0;
            FUN_180023030(&uStack_100,*puVar1,*(undefined8 *)(lVar2 + 8));
            DAT_1802fc458 = 0;
            DAT_1802fc4a0 = DAT_1802edee8;
            _DAT_1802fc4a8 = uStack_100;
            uRam00000001802fc4b0 = uStack_f8;
            _DAT_1802fc4b8 = uStack_f0;
            _DAT_1802fc4c0 = uStack_100;
            uRam00000001802fc4c8 = uStack_f8;
            _DAT_1802fc4d0 = uStack_f0;
            _DAT_1802fc4d8 = uVar6;
            _DAT_1802fc4dc = uVar6;
            _DAT_1802fc4e8 = uStack_100;
            uRam00000001802fc4f0 = uStack_f8;
            _DAT_1802fc4f8 = uStack_f0;
            _DAT_1802fc500 = uVar6;
            return;
          }
          DAT_1802fc458 = 0;
          DAT_1802fc4a0 = 0;
          return;
        }
        if (DAT_1802fc490 == '\x01') {
          uStack_a8 = _DAT_1802fc488;
          uStack_b8 = _DAT_1802fc478;
          uStack_b0 = uRam00000001802fc480;
        }
        else {
          uStack_48 = _DAT_1802fc488;
          uStack_58 = _DAT_1802fc478;
          uStack_50 = uRam00000001802fc480;
          uStack_88 = uStack_c0;
          FUN_180009400(&uStack_b8,&uStack_58,auStack_98);
        }
        uStack_48 = uStack_68;
        uStack_58 = CONCAT44(uStack_74,uStack_78);
        uStack_50 = CONCAT44(uStack_6c,uStack_70);
        uStack_88 = uStack_c0;
        uStack_d8 = uStack_a8;
        uStack_e8 = (undefined4)uStack_b8;
        uStack_e4 = uStack_b8._4_4_;
        uStack_e0 = (undefined4)uStack_b0;
        uStack_dc = uStack_b0._4_4_;
        dVar8 = (double)FUN_180036cf0(&uStack_58,auStack_98,&uStack_e8);
        if ((_DAT_180152190 <= dVar8) && (iVar4 == iVar5)) {
          uVar9 = _DAT_1802fc494;
          if (DAT_1802fc498 == '\0') {
            uVar9 = uVar6;
          }
          uStack_48 = uStack_a8;
          uStack_58 = uStack_b8;
          uStack_50 = uStack_b0;
          FUN_180036d80(&uStack_58,uVar9);
          DAT_1802fc458 = 0;
          return;
        }
        FUN_1800093b0(&uStack_58,0,0,0);
        DAT_1802fc458 = 0;
        DAT_1802fc470 = 0;
        _DAT_1802fc478 = uStack_58;
        uRam00000001802fc480 = uStack_50;
        _DAT_1802fc488 = uStack_48;
        DAT_1802fc490 = 0;
        DAT_1802fc498 = 0;
        DAT_1802fc4a0 = 0;
        _DAT_1802fc4e0 = (int)_DAT_1802ede68;
        return;
      }
    }
    do {
      cVar3 = DAT_1802fc458;
      LOCK();
      DAT_1802fc458 = '\x01';
      UNLOCK();
    } while (cVar3 != '\0');
    if (DAT_1802fc470 == '\x01') {
      _DAT_1802fc4e0 = (int)_DAT_1802ede68;
      DAT_1802fc470 = '\0';
    }
    DAT_1802fc458 = '\0';
    DAT_1802fc4a0 = 0;
  }
  return;
}

// UI RVA 0x36740; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x36740; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180036740(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_1801522bc);
  FUN_18000cfb0(param_2,param_1,0x1802eddb0);
  FUN_18000cf30(param_2,param_1,0x1802ede00);
  FUN_18000cf30(param_2,param_1,0x1802edd78);
  FUN_18000cf30(param_2,param_1,0x1802ede38);
  FUN_18000cef0(param_2,param_1,0x1802edeb0);
  FUN_180013e90(param_1,param_2,&UNK_1801522c1);
  FUN_18000cef0(param_2,param_1,0x1802eded0);
  if (DAT_1802edee8 == '\x01') {
    FUN_18000d0a0(param_2,param_1,0x1802edd18);
    FUN_18000cf30(param_2,param_1,0x1802edce0);
    FUN_18000cef0(param_2,param_1,0x1802edd58);
    FUN_18000cef0(param_2,param_1,0x1802edd38);
  }
  FUN_180013e90(param_1,param_2,&UNK_1801522d9);
  FUN_18000cef0(param_2,param_1,0x1802ede70);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802edea0,0x1802ede90,&DAT_1802edea8);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x36870; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x36870; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180036870(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c550(param_1,&UNK_1801522e4,0x1802eddb0);
  FUN_18000c450(param_1,&UNK_1801522f0,0x1802ede00);
  FUN_18000c450(param_1,&UNK_1801522f6,0x1802edd78);
  FUN_18000c450(param_1,&UNK_180152304,0x1802ede38);
  FUN_18000c3b0(param_1,&UNK_18015230d,0x1802edeb0);
  FUN_18000c3b0(param_1,&UNK_18015231c,0x1802eded0);
  FUN_18000c7e0(param_1,&UNK_18015232e,0x1802edd18);
  FUN_18000c450(param_1,&UNK_18015233e,0x1802edce0);
  FUN_18000c3b0(param_1,&UNK_180152353,0x1802edd58);
  FUN_18000c3b0(param_1,&UNK_180152364,0x1802edd38);
  FUN_18000c3b0(param_1,&UNK_180152375,0x1802ede70);
  uVar1 = uRam00000001802edea9;
  uVar2 = DAT_1802edea8;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_18015238b,DAT_1802edea8);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802edea8;
      break;
    case 2:
      uRam00000001802edea9 = DAT_1802edea8;
      break;
    case 3:
      uVar2 = uRam00000001802edea9;
    }
  }
  DAT_1802edea8 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x36990; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x36990; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180036990(void)

{
  FUN_1800ab710(_DAT_1802ede30,0x20,&UNK_18015239a,(double)_DAT_1802ede30);
  return;
}

// CANDIDATE_LOCAL RVA 0x369d0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x369d0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800369d0(undefined8 *param_1,char param_2)

{
  double dVar1;
  double dVar2;
  char cVar3;
  int iVar4;
  longlong lVar5;
  double dVar6;
  undefined1 auStack_b8 [24];
  undefined1 auStack_a0 [24];
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined8 uStack_78;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined8 uStack_60;
  
  if ((param_2 == '\0') || (_DAT_1802fc49c <= *(int *)(param_1 + 3))) {
    lVar5 = FUN_180026800(*param_1,param_1[1]);
    if (lVar5 == 0) {
      lVar5 = FUN_180026930(*param_1,param_1[1]);
      if (lVar5 != 0) {
        iVar4 = FUN_180026970(*param_1,lVar5);
        if (iVar4 == _DAT_1802fc468) {
          iVar4 = FUN_180026990(*param_1,lVar5);
          dVar6 = _DAT_180152198;
          dVar1 = (double)iVar4 * _DAT_180152198;
          iVar4 = FUN_1800269b0(*param_1,lVar5);
          dVar2 = (double)iVar4 * dVar6;
          iVar4 = FUN_1800269d0(*param_1,lVar5);
          dVar6 = (double)iVar4 * dVar6;
          if (param_2 == '\0') {
            FUN_1800093b0(&uStack_70,dVar1,dVar2,dVar6);
            _DAT_1802fc488 = uStack_60;
            _DAT_1802fc478 = CONCAT44(uStack_6c,uStack_70);
            uRam00000001802fc480 = CONCAT44(uStack_64,uStack_68);
            DAT_1802fc490 = 1;
            cVar3 = FUN_1800269f0(*param_1,lVar5);
            _DAT_1802fc494 = (float)(int)cVar3 * _DAT_1801521a0 * _DAT_1801521a4;
            DAT_1802fc498 = 1;
            _DAT_1802fc49c = *(int *)(param_1 + 3);
          }
          else {
            FUN_1800093b0(auStack_a0,dVar1,dVar2,dVar6);
            uStack_78 = _DAT_1802fc488;
            uStack_88 = _DAT_1802fc478;
            uStack_84 = DAT_1802fc478_4;
            uStack_80 = (undefined4)uRam00000001802fc480;
            uStack_7c = uRam00000001802fc480._4_4_;
            FUN_1800093d0(&uStack_70,&uStack_88,auStack_a0);
            _DAT_1802fc478 = CONCAT44(uStack_6c,uStack_70);
            uRam00000001802fc480 = CONCAT44(uStack_64,uStack_68);
            _DAT_1802fc488 = uStack_60;
            DAT_1802fc490 = 0;
          }
        }
      }
    }
    else {
      iVar4 = FUN_180026840(*param_1,lVar5);
      if (iVar4 == _DAT_1802fc468) {
        cVar3 = FUN_180026860(*param_1,lVar5);
        dVar6 = _DAT_180152198;
        dVar1 = (double)(int)cVar3 * _DAT_180152198;
        cVar3 = FUN_180026880(*param_1,lVar5);
        dVar2 = (double)(int)cVar3 * dVar6;
        cVar3 = FUN_1800268a0(*param_1,lVar5);
        dVar6 = (double)(int)cVar3 * dVar6;
        if (param_2 == '\0') {
          FUN_1800093b0(auStack_b8,dVar1,dVar2,dVar6);
          uStack_78 = _DAT_1802fc488;
          uStack_88 = _DAT_1802fc478;
          uStack_84 = DAT_1802fc478_4;
          uStack_80 = (undefined4)uRam00000001802fc480;
          uStack_7c = uRam00000001802fc480._4_4_;
          FUN_180009400(&uStack_70,&uStack_88,auStack_b8);
          _DAT_1802fc478 = CONCAT44(uStack_6c,uStack_70);
          uRam00000001802fc480 = CONCAT44(uStack_64,uStack_68);
          _DAT_1802fc488 = uStack_60;
          cVar3 = FUN_180026900(*param_1,lVar5);
          if (cVar3 != '\0') {
            cVar3 = FUN_1800268c0(*param_1,lVar5);
            _DAT_1802fc494 = (float)(int)cVar3 * _DAT_1801521a0 * _DAT_1801521a4;
            DAT_1802fc498 = 1;
          }
        }
        else {
          FUN_1800093b0(auStack_a0,dVar1,dVar2,dVar6);
          uStack_78 = _DAT_1802fc488;
          uStack_88 = _DAT_1802fc478;
          uStack_84 = DAT_1802fc478_4;
          uStack_80 = (undefined4)uRam00000001802fc480;
          uStack_7c = uRam00000001802fc480._4_4_;
          FUN_1800093d0(&uStack_70,&uStack_88,auStack_a0);
          _DAT_1802fc478 = CONCAT44(uStack_6c,uStack_70);
          uRam00000001802fc480 = CONCAT44(uStack_64,uStack_68);
          _DAT_1802fc488 = uStack_60;
        }
      }
    }
  }
  return;
}

// CANDIDATE_LOCAL RVA 0x36cf0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x36cf0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


double FUN_180036cf0(undefined8 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  double dVar1;
  double dVar2;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined8 uStack_38;
  
  uStack_58 = param_1[2];
  uStack_68 = *param_1;
  uStack_60 = param_1[1];
  uStack_38 = *(undefined8 *)(param_2 + 4);
  uStack_48 = *param_2;
  uStack_44 = param_2[1];
  uStack_40 = param_2[2];
  uStack_3c = param_2[3];
  dVar2 = (double)FUN_1800094f0(&uStack_68,&uStack_48);
  uStack_58 = param_1[2];
  uStack_68 = *param_1;
  uStack_60 = param_1[1];
  uStack_38 = *(undefined8 *)(param_3 + 4);
  uStack_48 = *param_3;
  uStack_44 = param_3[1];
  uStack_40 = param_3[2];
  uStack_3c = param_3[3];
  dVar1 = (double)FUN_1800094f0(&uStack_68,&uStack_48);
  return dVar1 - dVar2;
}

// CANDIDATE_LOCAL RVA 0x36d80; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x36d80; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180036d80(char *param_1,float param_2)

{
  undefined8 uVar1;
  double dVar2;
  float fVar3;
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  
  auVar4[0] = -(DAT_1802fc4e8 == *param_1);
  auVar4[1] = -(DAT_1802fc4e8_1 == param_1[1]);
  auVar4[2] = -(cRam00000001802fc4ea == param_1[2]);
  auVar4[3] = -(cRam00000001802fc4eb == param_1[3]);
  auVar4[4] = -(cRam00000001802fc4ec == param_1[4]);
  auVar4[5] = -(cRam00000001802fc4ed == param_1[5]);
  auVar4[6] = -(cRam00000001802fc4ee == param_1[6]);
  auVar4[7] = -(cRam00000001802fc4ef == param_1[7]);
  auVar4[8] = -((char)uRam00000001802fc4f0 == param_1[8]);
  auVar4[9] = -(uRam00000001802fc4f0._1_1_ == param_1[9]);
  auVar4[10] = -(cRam00000001802fc4f2 == param_1[10]);
  auVar4[0xb] = -(cRam00000001802fc4f3 == param_1[0xb]);
  auVar4[0xc] = -(cRam00000001802fc4f4 == param_1[0xc]);
  auVar4[0xd] = -(cRam00000001802fc4f5 == param_1[0xd]);
  auVar4[0xe] = -(cRam00000001802fc4f6 == param_1[0xe]);
  auVar4[0xf] = -(cRam00000001802fc4f7 == param_1[0xf]);
  uVar1 = *(undefined8 *)(param_1 + 0x10);
  auVar5[0] = -(DAT_1802fc4f8 == (char)uVar1);
  auVar5[1] = -(DAT_1802fc4f8_1 == (char)((ulonglong)uVar1 >> 8));
  auVar5[2] = -(cRam00000001802fc4fa == (char)((ulonglong)uVar1 >> 0x10));
  auVar5[3] = -(cRam00000001802fc4fb == (char)((ulonglong)uVar1 >> 0x18));
  auVar5[4] = -(cRam00000001802fc4fc == (char)((ulonglong)uVar1 >> 0x20));
  auVar5[5] = -(cRam00000001802fc4fd == (char)((ulonglong)uVar1 >> 0x28));
  auVar5[6] = -(cRam00000001802fc4fe == (char)((ulonglong)uVar1 >> 0x30));
  auVar5[7] = -(cRam00000001802fc4ff == (char)((ulonglong)uVar1 >> 0x38));
  auVar5[8] = 0xff;
  auVar5[9] = 0xff;
  auVar5[10] = 0xff;
  auVar5[0xb] = 0xff;
  auVar5[0xc] = 0xff;
  auVar5[0xd] = 0xff;
  auVar5[0xe] = 0xff;
  auVar5[0xf] = 0xff;
  auVar5 = auVar5 & auVar4;
  if ((((ushort)((ushort)(SUB161(auVar5 >> 7,0) & 1) | (ushort)(SUB161(auVar5 >> 0xf,0) & 1) << 1 |
                 (ushort)(SUB161(auVar5 >> 0x17,0) & 1) << 2 |
                 (ushort)(SUB161(auVar5 >> 0x1f,0) & 1) << 3 |
                 (ushort)(SUB161(auVar5 >> 0x27,0) & 1) << 4 |
                 (ushort)(SUB161(auVar5 >> 0x2f,0) & 1) << 5 |
                 (ushort)(SUB161(auVar5 >> 0x37,0) & 1) << 6 |
                 (ushort)(SUB161(auVar5 >> 0x3f,0) & 1) << 7 |
                 (ushort)(SUB161(auVar5 >> 0x47,0) & 1) << 8 |
                 (ushort)(SUB161(auVar5 >> 0x4f,0) & 1) << 9 |
                 (ushort)(SUB161(auVar5 >> 0x57,0) & 1) << 10 |
                 (ushort)(SUB161(auVar5 >> 0x5f,0) & 1) << 0xb |
                 (ushort)(SUB161(auVar5 >> 0x67,0) & 1) << 0xc |
                 (ushort)(SUB161(auVar5 >> 0x6f,0) & 1) << 0xd |
                 (ushort)(SUB161(auVar5 >> 0x77,0) & 1) << 0xe |
                (ushort)(byte)(auVar5[0xf] >> 7) << 0xf) != 0xffff) || (param_2 != _DAT_1802fc500))
     || (NAN(param_2) || NAN(_DAT_1802fc500))) {
    _DAT_1802fc504 = 3;
  }
  _DAT_1802fc4f8 = *(undefined8 *)(param_1 + 0x10);
  _DAT_1802fc4e8 = *(undefined8 *)param_1;
  _uRam00000001802fc4f0 = *(undefined8 *)(param_1 + 8);
  _DAT_1802fc4a8 = _DAT_1802fc4c0;
  uRam00000001802fc4b0 = uRam00000001802fc4c8;
  _DAT_1802fc4b8 = _DAT_1802fc4d0;
  _DAT_1802fc4d8 = _DAT_1802fc4dc;
  _DAT_1802fc500 = param_2;
  if (_DAT_1802fc504 < 1) {
    _DAT_1802fc4d0 = *(undefined8 *)(param_1 + 0x10);
    _DAT_1802fc4c0 = *(undefined8 *)param_1;
    uRam00000001802fc4c8 = *(undefined8 *)(param_1 + 8);
  }
  else {
    dVar2 = _DAT_1801521a8 / (double)_DAT_1802fc504;
    uStack_48 = *(undefined8 *)(param_1 + 0x10);
    uStack_58 = *(undefined8 *)param_1;
    uStack_50 = *(undefined8 *)(param_1 + 8);
    uStack_28 = _DAT_1802fc4d0;
    uStack_38 = _DAT_1802fc4c0;
    uStack_30 = uRam00000001802fc4c8;
    FUN_1800093d0(&uStack_78,&uStack_58,&uStack_38);
    uStack_28 = uStack_68;
    uStack_38 = uStack_78;
    uStack_30 = uStack_70;
    FUN_180009430(&uStack_58,&uStack_38,dVar2);
    uStack_68 = uStack_48;
    uStack_78 = uStack_58;
    uStack_70 = uStack_50;
    uStack_28 = _DAT_1802fc4d0;
    uStack_38 = _DAT_1802fc4c0;
    uStack_30 = uRam00000001802fc4c8;
    uStack_88 = uStack_48;
    uStack_98 = uStack_58;
    uStack_90 = uStack_50;
    FUN_180009400(&uStack_58,&uStack_38,&uStack_98);
    _DAT_1802fc4c0 = uStack_58;
    uRam00000001802fc4c8 = uStack_50;
    _DAT_1802fc4d0 = uStack_48;
    fVar3 = (float)FUN_18000a210(_DAT_1802fc500 - _DAT_1802fc4dc);
    param_2 = (float)((double)fVar3 * dVar2) + _DAT_1802fc4dc;
    _DAT_1802fc504 = _DAT_1802fc504 + -1;
  }
  _DAT_1802fc4dc = param_2;
  return;
}

// CANDIDATE_LOCAL RVA 0x36f60; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x36f60; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool FUN_180036f60(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  double dVar1;
  undefined4 extraout_XMM0_Da;
  undefined4 extraout_XMM0_Db;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined8 uStack_a8;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  
  FUN_180023030(&uStack_e8,*param_1,param_2);
  FUN_180024160(&uStack_d0,*param_1,param_2);
  uStack_68 = param_3[2];
  uStack_78 = *param_3;
  uStack_70 = param_3[1];
  uStack_88 = uStack_d8;
  uStack_98 = uStack_e8;
  uStack_90 = uStack_e0;
  uStack_48 = uStack_c0;
  uStack_58 = uStack_d0;
  uStack_50 = uStack_c8;
  uStack_a8 = param_3[2];
  uStack_b8 = *(undefined4 *)param_3;
  uStack_b4 = *(undefined4 *)((longlong)param_3 + 4);
  uStack_b0 = *(undefined4 *)(param_3 + 1);
  uStack_ac = *(undefined4 *)((longlong)param_3 + 0xc);
  dVar1 = (double)FUN_1800094f0(&uStack_b8,&uStack_98);
  FUN_1800094f0(&uStack_78,&uStack_58);
  return _DAT_1801521b0 < (double)CONCAT44(extraout_XMM0_Db,extraout_XMM0_Da) - dVar1;
}

