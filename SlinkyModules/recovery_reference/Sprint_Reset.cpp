// Recovered decompiler view: Sprint Reset
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x3ad10, 0x3b3c0); proximity does not prove ownership.

// CALLBACK RVA 0x3ad10; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/sprint_reset/sprint_reset.c
// Differential report: analysis/module_behavior_recovery/sprint_reset/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3ad10; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Removing unreachable block (ram,0x00018003b1d0) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003ad10(longlong param_1,undefined8 param_2,ulonglong param_3)

{
  longlong *plVar1;
  undefined8 *puVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined7 uVar8;
  float fVar9;
  float fVar10;
  double dVar11;
  float fVar12;
  
  puVar2 = *(undefined8 **)(param_1 + 8);
  if (*(char *)(puVar2 + 8) == '\x01') {
    dVar11 = (double)FUN_18004c270();
    if (_DAT_180153060 <= dVar11 - _DAT_1802fc878) {
      iVar4 = FUN_180023760(*puVar2,puVar2[5]);
      iVar5 = FUN_1800239d0(*puVar2,puVar2[5]);
      if (iVar4 == iVar5) {
        DAT_1802fc880 = '\x01';
        _DAT_1802fc878 = dVar11;
      }
    }
    _DAT_1802fc884 = _DAT_1802fc884 + 1;
    uVar7 = puVar2[5];
    iVar4 = FUN_1800239f0(*puVar2,uVar7);
    fVar10 = _DAT_1802eff98;
    if (iVar4 == 10) {
      _DAT_1802fc884 = 0;
    }
    uVar8 = (undefined7)((ulonglong)uVar7 >> 8);
    if ((_DAT_1802fc874 <= 0.0) ||
       (_DAT_1802fc874 = _DAT_1802fc874 + _DAT_180153068, _DAT_1802fc874 <= 0.0)) {
      if (_DAT_1802fc870 == 2) {
        FUN_18003b150(puVar2,0);
        _DAT_1802fc870 = 0;
      }
      else if (_DAT_1802fc870 == 1) {
        FUN_18003b150(puVar2,CONCAT71(uVar8,1));
        fVar10 = _DAT_1802f0030;
        _DAT_1802fc870 = 2;
        DAT_1802fc880 = '\0';
        fVar12 = _DAT_1802f0030;
        if (DAT_1802effb8 == '\x01') {
          uVar6 = FUN_18000a050(0,_DAT_18015306c);
          uVar7 = _DAT_180153070;
          fVar9 = (float)FUN_18000a510(0x1802fc898,uVar6,_DAT_180153070);
          fVar12 = 0.0;
          if (0.0 <= fVar10 - fVar9) {
            fVar12 = fVar10 - fVar9;
          }
          uVar6 = FUN_18000a050(_DAT_180153078,_DAT_18015307c);
          cVar3 = FUN_18000aa30(0x1802fc8a8,uVar6,uVar7);
          if (cVar3 != '\0') {
            uVar7 = FUN_18000a050(_DAT_18015306c,_DAT_180153080);
            fVar10 = (float)FUN_18000a3e0(uVar7);
            fVar12 = fVar12 + fVar10;
          }
        }
        _DAT_1802fc874 = fVar12 + _DAT_1802fc874;
      }
      else {
        if (DAT_1802effb8 == '\x01') {
          uVar7 = FUN_18000a050(0,_DAT_180153080);
          fVar12 = (float)FUN_18000a510(0x1802fc888,uVar7,_DAT_180153088);
          fVar10 = fVar10 + fVar12;
        }
        if (((DAT_1802fc880 == '\x01') && ((DAT_1802effd8 != '\x01' || (_DAT_1802fc884 == 0)))) &&
           ((DAT_1802efff8 != '\x01' || (cVar3 = FUN_1800380b0(*puVar2,puVar2[5]), cVar3 != '\0'))))
        {
          _DAT_1802fc874 = fVar10 + _DAT_1802fc874;
          _DAT_1802fc870 = 1;
        }
      }
    }
    else if (_DAT_1802fc870 == 2) {
      uVar6 = FUN_180022cf0(*puVar2,puVar2[3]);
      uVar7 = *puVar2;
      if (_DAT_1802eff58 == 2) {
        uVar7 = FUN_180025210(uVar7,uVar6);
      }
      else if (_DAT_1802eff58 == 1) {
        uVar7 = FUN_180025030(uVar7,uVar6);
      }
      else {
        uVar7 = FUN_1800250d0(uVar7,uVar6);
      }
      if (_DAT_1802eff58 == 2) {
        param_3 = CONCAT71(uVar8,1) & 0xffffffff ^ 1;
        FUN_1800236c0(*puVar2,puVar2[5],param_3);
      }
      plVar1 = (longlong *)((longlong *)*puVar2)[1];
                    /* WARNING: Could not recover jumptable at 0x000180025480. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*plVar1 + 0x348))
                (plVar1,uVar7,*(undefined8 *)(*(longlong *)*puVar2 + 0x478),
                 CONCAT71((int7)(param_3 >> 8),_DAT_1802eff58 == 1) & 0xffffffff);
      return;
    }
  }
  else {
    if (_DAT_1802fc870 == 2) {
      FUN_18003b150(puVar2,0);
    }
    _DAT_1802fc870 = 0;
    DAT_1802fc880 = '\0';
    _DAT_1802fc874 = 0.0;
  }
  return;
}

// UI RVA 0x3afc0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3afc0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003afc0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180153122);
  FUN_18000d040(param_2,param_1,0x1802eff28);
  FUN_18000cf30(param_2,param_1,0x1802eff68);
  FUN_18000cf30(param_2,param_1,0x1802f0000);
  FUN_18000cef0(param_2,param_1,0x1802effa0);
  FUN_180013e90(param_1,param_2,&UNK_180153127);
  FUN_18000cef0(param_2,param_1,0x1802effc0);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802efff0,0x1802effe0,&DAT_1802efff8);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x3b070; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3b070; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003b070(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c6f0(param_1,&UNK_180153132,0x1802eff28);
  FUN_18000c450(param_1,&UNK_180153137,0x1802eff68);
  FUN_18000c450(param_1,&UNK_18015313d,0x1802f0000);
  FUN_18000c3b0(param_1,&UNK_180153146,0x1802effa0);
  FUN_18000c3b0(param_1,&UNK_180153150,0x1802effc0);
  uVar1 = uRam00000001802efff9;
  uVar2 = DAT_1802efff8;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180153160,DAT_1802efff8);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802efff8;
      break;
    case 2:
      uRam00000001802efff9 = DAT_1802efff8;
      break;
    case 3:
      uVar2 = uRam00000001802efff9;
    }
  }
  DAT_1802efff8 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x3b110; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3b110; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003b110(undefined8 param_1)

{
  FUN_1800ab710(param_1,0x20,&UNK_18015316f,
                *(undefined8 *)((ulonglong)_DAT_1802eff58 * 8 + 0x1802eff10));
  return;
}

// CANDIDATE_LOCAL RVA 0x3b150; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3b150; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003b150(undefined8 *param_1,uint param_2,ulonglong param_3)

{
  longlong *plVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  
  uVar3 = FUN_180022cf0(*param_1,param_1[3]);
  uVar4 = *param_1;
  if (_DAT_1802eff58 == 2) {
    uVar4 = FUN_180025210(uVar4,uVar3);
  }
  else if (_DAT_1802eff58 == 1) {
    uVar4 = FUN_180025030(uVar4,uVar3);
  }
  else {
    uVar4 = FUN_1800250d0(uVar4,uVar3);
  }
  if (_DAT_1802eff58 == 2) {
    param_3 = (ulonglong)param_2 ^ 1;
    FUN_1800236c0(*param_1,param_1[5],param_3);
  }
  plVar1 = (longlong *)*param_1;
  if ((char)param_2 == '\0') {
    uVar2 = FUN_180025490(plVar1,uVar4);
  }
  else {
    uVar2 = (undefined4)CONCAT71((int7)(param_3 >> 8),_DAT_1802eff58 == 1);
  }
                    /* WARNING: Could not recover jumptable at 0x000180025480. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(longlong *)plVar1[1] + 0x348))
            ((longlong *)plVar1[1],uVar4,*(undefined8 *)(*plVar1 + 0x478),uVar2);
  return;
}

// CANDIDATE_LOCAL RVA 0x3b200; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3b200; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003b200(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  longlong lVar2;
  undefined8 uVar3;
  longlong lVar4;
  undefined8 uStack_98;
  ulonglong uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  
  if (DAT_1802f0260 == '\x01') {
    uVar3 = FUN_180022c00();
    lVar2 = FUN_180022e10(param_1,uVar3);
    if (((lVar2 != 0) && (lVar2 = FUN_180024e30(param_1,lVar2), lVar2 != 0)) &&
       (lVar2 = FUN_180024120(param_1,lVar2), lVar2 != 0)) {
      uVar3 = FUN_180023740(param_1,lVar2);
      uStack_48 = FUN_180027dc0(param_1,uVar3);
      uStack_40 = FUN_180027d90(param_1,uVar3);
      uStack_38 = func_0x00018013d0d0(0);
      uStack_30 = 0;
      uStack_68 = 0;
      uStack_60 = 0;
      uStack_78 = 0;
      uStack_70 = 0;
      uStack_88 = 0;
      uStack_80 = 0;
      uStack_98 = 0;
      uStack_90 = 0;
      uStack_58 = 0;
      lVar4 = FUN_18000df00(_DAT_1802fc8c0,0x20,0x1802fc8c8,&uStack_48,FUN_18003b380);
      if (lVar4 == 0) {
        cVar1 = FUN_18002ace0(param_1,lVar2,2);
        if (cVar1 != '\0') {
          return;
        }
        uStack_98 = CONCAT44(uStack_98._4_4_,0x13);
        uStack_90 = CONCAT71(uStack_90._1_7_,1);
        FUN_18000df90(&DAT_1802fc8c0,0x20,0x1802fc8c8,&uStack_48,FUN_18003b380);
      }
      else {
        uStack_98 = CONCAT44(uStack_98._4_4_,0x13);
        uStack_90 = uStack_90 & 0xffffffffffffff00;
        FUN_18000e210(_DAT_1802fc8c0,0x20,0x1802fc8c8,lVar4);
      }
      FUN_180028480(param_2,&uStack_98);
    }
  }
  return;
}

// CANDIDATE_LOCAL RVA 0x3b380; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3b380; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


int FUN_18003b380(undefined8 param_1,ulonglong *param_2,ulonglong *param_3)

{
  ulonglong uVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  
  uVar3 = *param_2;
  uVar2 = uVar3 >> 0x38 | (uVar3 & 0xff000000000000) >> 0x28 | (uVar3 & 0xff0000000000) >> 0x18 |
          (uVar3 & 0xff00000000) >> 8 | (uVar3 & 0xff000000) << 8 | (uVar3 & 0xff0000) << 0x18 |
          (uVar3 & 0xff00) << 0x28 | uVar3 << 0x38;
  uVar3 = *param_3;
  uVar3 = uVar3 >> 0x38 | (uVar3 & 0xff000000000000) >> 0x28 | (uVar3 & 0xff0000000000) >> 0x18 |
          (uVar3 & 0xff00000000) >> 8 | (uVar3 & 0xff000000) << 8 | (uVar3 & 0xff0000) << 0x18 |
          (uVar3 & 0xff00) << 0x28 | uVar3 << 0x38;
  if (uVar2 == uVar3) {
    uVar3 = param_2[1];
    uVar1 = param_3[1];
    uVar2 = uVar3 >> 0x38 | (uVar3 & 0xff000000000000) >> 0x28 | (uVar3 & 0xff0000000000) >> 0x18 |
            (uVar3 & 0xff00000000) >> 8 | (uVar3 & 0xff000000) << 8 | (uVar3 & 0xff0000) << 0x18 |
            (uVar3 & 0xff00) << 0x28 | uVar3 << 0x38;
    uVar3 = uVar1 >> 0x38 | (uVar1 & 0xff000000000000) >> 0x28 | (uVar1 & 0xff0000000000) >> 0x18 |
            (uVar1 & 0xff00000000) >> 8 | (uVar1 & 0xff000000) << 8 | (uVar1 & 0xff0000) << 0x18 |
            (uVar1 & 0xff00) << 0x28 | uVar1 << 0x38;
    if (uVar2 == uVar3) {
      return 0;
    }
  }
  return (uint)(uVar3 <= uVar2) * 2 + -1;
}

