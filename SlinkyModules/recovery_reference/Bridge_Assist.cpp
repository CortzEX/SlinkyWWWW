// Recovered decompiler view: Bridge Assist
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x2de50, 0x2eb20); proximity does not prove ownership.

// CALLBACK RVA 0x2de50; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/bridge_events/bridge_events.c
// Differential report: analysis/module_behavior_recovery/bridge_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2de50; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18002de50(longlong param_1)

{
  undefined8 *puVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  
  if (((*(longlong *)(param_1 + 0x10) == 0x1802e9ac0) && (*(char *)(param_1 + 0x18) == '\0')) &&
     ((DAT_1802f7dc8 & 1) != 0)) {
    puVar1 = *(undefined8 **)(param_1 + 8);
    uVar3 = FUN_180022cf0(*puVar1,puVar1[3]);
    uVar3 = FUN_180025030(*puVar1,uVar3);
    uVar2 = FUN_180025490(*puVar1,uVar3);
    FUN_180025460(*puVar1,uVar3,uVar2);
    DAT_1802f7dc8 = 0;
  }
  return;
}

// CALLBACK RVA 0x2dec0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/bridge_events/bridge_events.c
// Differential report: analysis/module_behavior_recovery/bridge_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2dec0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002dec0(longlong param_1)

{
  undefined8 *puVar1;
  bool bVar2;
  bool bVar3;
  double dVar4;
  ulonglong uVar5;
  double dVar6;
  double dVar7;
  char cVar8;
  int iVar9;
  uint uVar10;
  float fVar11;
  longlong lVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  ulonglong uVar16;
  ulonglong uVar17;
  double dVar18;
  ulonglong uVar19;
  ulonglong uVar20;
  double dVar21;
  double dStack_e8;
  double dStack_e0;
  double dStack_d8;
  double dStack_d0;
  double dStack_c8;
  double dStack_c0;
  double dStack_b8;
  double dStack_b0;
  double dStack_a8;
  
  if ((*(char *)(param_1 + 0x10) == '\0') && (_DAT_1802f7dcc != 0x14)) {
    puVar1 = *(undefined8 **)(param_1 + 8);
    if (((DAT_1802f7dd0 == '\x01') &&
        (((lVar12 = FUN_180022e10(*puVar1,puVar1[3]), lVar12 != 0 &&
          (iVar9 = FUN_180024b50(*puVar1,lVar12), iVar9 == 1)) &&
         (uVar10 = FUN_180024b90(*puVar1,lVar12), 1 < uVar10)))) &&
       (cVar8 = FUN_180023780(*puVar1,puVar1[5]), cVar8 != '\0')) {
      uVar13 = FUN_180022cf0(*puVar1,puVar1[3]);
      uVar14 = FUN_180025120(*puVar1,uVar13);
      uVar15 = FUN_180025170(*puVar1,uVar13);
      uVar13 = FUN_1800251c0(*puVar1,uVar13);
      cVar8 = FUN_180025430(*puVar1,uVar14);
      if (((cVar8 != '\0') && (cVar8 = FUN_180025430(*puVar1,uVar15), cVar8 == '\0')) &&
         (cVar8 = FUN_180025430(*puVar1,uVar13), cVar8 == '\0')) {
        fVar11 = (float)FUN_180023170(*puVar1,puVar1[5]);
        dVar18 = (double)func_0x0001800b2170((double)fVar11,_DAT_180150760);
        if ((_DAT_180150780 <= (float)((uint)(float)dVar18 & _DAT_180150770)) &&
           ((float)((uint)(float)dVar18 & _DAT_180150770) <= _DAT_180150784)) {
          FUN_180023030(&dStack_b8,*puVar1,puVar1[5]);
          cVar8 = FUN_180023020(*puVar1);
          if (cVar8 != '\0') {
            dStack_d8 = dStack_a8;
            dStack_e8 = dStack_b8;
            dStack_e0 = dStack_b0;
            FUN_1800095c0(&dStack_d0,&dStack_e8);
            dStack_b8 = dStack_d0;
            dStack_b0 = dStack_c8;
            dStack_a8 = dStack_c0;
          }
          uVar13 = FUN_180024bf0(*puVar1,lVar12);
          FUN_180025540(&dStack_d0,*puVar1,uVar13);
          if (((((double)((ulonglong)(dStack_d0 - dStack_b8) & _DAT_180150790) <= _DAT_1801507a0) &&
               (_DAT_1801507a8 <= dStack_c8 - dStack_b0)) && (dStack_c8 - dStack_b0 <= 0.0)) &&
             ((double)((ulonglong)(dStack_c0 - dStack_a8) & _DAT_180150790) <= _DAT_1801507a0)) {
            FUN_180024d80(&dStack_e8,*puVar1,lVar12);
            dVar7 = dStack_b8;
            dVar6 = dStack_e8;
            dVar18 = _DAT_1801507a0;
            dVar21 = dStack_e8 + _DAT_1801507a0;
            bVar2 = dStack_a8 <= dStack_d8;
            bVar3 = dStack_d8 + _DAT_1801507a0 <= dStack_a8;
            uVar19 = func_0x0001800b2170(dStack_d0,_DAT_1801507a0);
            uVar5 = _DAT_180150790;
            dVar4 = (double)(uVar19 & _DAT_180150790);
            uVar20 = func_0x0001800b2170(dStack_c0,dVar18);
            uVar19 = _DAT_1801507b0;
            if (bVar3 || bVar2) {
              uVar19 = _DAT_1801507b8;
            }
            uVar16 = -(ulonglong)(dVar6 < dVar7);
            uVar17 = -(ulonglong)(dVar7 < dVar21);
            dVar21 = (double)(~uVar16 & _DAT_1801507b8 |
                             (~uVar17 & _DAT_1801507b8 | uVar19 & uVar17) & uVar16);
            dVar18 = dVar18 - dVar21;
            if ((dVar21 <= dVar4 && dVar4 <= dVar18) ||
               ((double)(uVar20 & uVar5) <= dVar18 && dVar21 <= (double)(uVar20 & uVar5))) {
              *(undefined1 *)(param_1 + 0x11) = 1;
              return;
            }
          }
        }
      }
    }
    uVar13 = FUN_180028a50(*puVar1,puVar1[5]);
    cVar8 = FUN_180028b00(*puVar1,uVar13);
    if (cVar8 != '\0') {
      _DAT_1802f7dcc = 0x14;
    }
  }
  return;
}

// CALLBACK RVA 0x2e260; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/bridge_update/bridge_update.c
// Differential report: analysis/module_behavior_recovery/bridge_update/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2e260; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002e260(longlong param_1)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  int iVar4;
  char cVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  float extraout_var;
  undefined8 uVar9;
  float fVar10;
  float fVar11;
  undefined1 auStack_60 [8];
  double dStack_58;
  
  DAT_1802f7dd0 = 0;
  DAT_1802f7dd1 = 0;
  puVar1 = *(undefined8 **)(param_1 + 8);
  if (*(char *)(puVar1 + 8) != '\x01') {
    DAT_1802f7dd0 = 0;
    DAT_1802f7dd1 = 0;
    return;
  }
  uVar7 = FUN_180022cf0(*puVar1,puVar1[3]);
  if (0 < _DAT_1802f7dcc) {
    _DAT_1802f7dcc = _DAT_1802f7dcc + -1;
  }
  uVar8 = FUN_180025030(*puVar1,uVar7);
  uVar6 = FUN_180025490(*puVar1,uVar8);
  if (DAT_1802e9ce8 != (char)uVar6) {
LAB_18002e3d8:
    if (DAT_1802f7dc8 == '\x01') {
      FUN_180025460(*puVar1,uVar8,uVar6);
    }
    DAT_1802f7dc8 = 0;
    return;
  }
  uVar2 = *puVar1;
  uVar9 = puVar1[5];
  if (((DAT_1802e9d08 == '\x01') && (FUN_180023170(uVar2,uVar9), extraout_var < _DAT_1801507c0)) ||
     ((DAT_1802e9d28 == '\x01' && (fVar10 = (float)FUN_180023ac0(uVar2,uVar9), 0.0 < fVar10))))
  goto LAB_18002e3d8;
  DAT_1802f7dd1 = _DAT_1802e9d78 != 0;
  iVar4 = _DAT_1802f7dd8;
  if (DAT_1802e9da0 == '\x01') {
    uVar9 = FUN_180028a50(uVar2,uVar9);
    cVar5 = FUN_180028b00(uVar2,uVar9);
    iVar4 = 2;
    if (cVar5 == '\0') {
      if (_DAT_1802f7dd8 < 1) goto LAB_18002e3d8;
      iVar4 = _DAT_1802f7dd8 + -1;
    }
  }
  _DAT_1802f7dd8 = iVar4;
  DAT_1802f7dc8 = 1;
  cVar5 = FUN_180025430(*puVar1,uVar8);
  uVar2 = *puVar1;
  uVar9 = puVar1[4];
  uVar3 = puVar1[5];
  if (cVar5 == '\0') {
    cVar5 = FUN_180023780(uVar2,uVar3);
    if (cVar5 == '\0') {
      if (DAT_1802e9dc0 != '\x01') {
        return;
      }
      FUN_180023550(auStack_60,uVar2,uVar3);
      if (dStack_58 < 0.0) {
        return;
      }
    }
    cVar5 = FUN_18002e7b0(uVar2,uVar7,uVar9,uVar3);
    if (cVar5 != '\0') {
      FUN_180025460(*puVar1,uVar8,1);
      DAT_1802f7dd0 = DAT_1802e9e38;
      return;
    }
    return;
  }
  if (DAT_1802e9ce8 == '\x01') {
    fVar10 = (float)FUN_180023ac0(uVar2,uVar3);
    if (0.0 <= fVar10) {
      DAT_1802f7dd0 = DAT_1802e9e38;
      return;
    }
    if (_DAT_1802f7dcc < 1) {
      DAT_1802f7dd0 = DAT_1802e9e38;
      return;
    }
  }
  else {
    cVar5 = FUN_180023780(uVar2,uVar3);
    if ((cVar5 == '\0') &&
       ((DAT_1802e9dc0 != '\x01' || (FUN_180023550(auStack_60,uVar2,uVar3), dStack_58 < 0.0))))
    goto LAB_18002e4b2;
  }
  cVar5 = FUN_18002e7b0(uVar2,uVar7,uVar9,uVar3);
  if (cVar5 != '\0') {
    DAT_1802f7dd0 = DAT_1802e9e38;
    return;
  }
LAB_18002e4b2:
  _DAT_1802f7dd4 = _DAT_1802f7dd4 + _DAT_1801507c4;
  if (0.0 < _DAT_1802f7dd4) {
    DAT_1802f7dd0 = DAT_1802e9e38;
    return;
  }
  FUN_180025460(*puVar1,uVar8,0);
  fVar10 = _DAT_1802e9e70;
  if (DAT_1802e9e18 == '\x01') {
    uVar7 = FUN_18000a050();
    fVar11 = (float)FUN_18000a510(0x1802f7df0,uVar7,_DAT_1801507d0);
    fVar10 = fVar10 + fVar11;
    uVar7 = FUN_18000a050();
    cVar5 = FUN_18000aa30(0x1802f7e00,uVar7,_DAT_1801507e0);
    if (cVar5 != '\0') {
      uVar7 = FUN_18000a050();
      fVar11 = (float)FUN_18000a3e0(uVar7);
      fVar10 = fVar10 + fVar11;
    }
  }
  _DAT_1802f7dd4 = fVar10 + _DAT_1802f7dd4;
  return;
}

// CALLBACK RVA 0x2e5a0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/bridge_events/bridge_events.c
// Differential report: analysis/module_behavior_recovery/bridge_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2e5a0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002e5a0(longlong param_1)

{
  longlong *plVar1;
  longlong *plVar2;
  int iVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  longlong lVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  int iStack_44;
  
  if (DAT_1802f7dd1 != '\x01') {
    return;
  }
  plVar2 = *(longlong **)(param_1 + 8);
  if ((_DAT_1802f7bb0 == 0) && ((_DAT_1802e9d78 == 2 || (_DAT_1802f7bb8 != 0)))) {
    uVar7 = FUN_180023f40(*plVar2,plVar2[5]);
    iVar3 = _DAT_1802f7bb8;
    iVar5 = FUN_180025a60(*plVar2,uVar7);
    uVar11 = (uint)DAT_1802f7bc0;
    uVar8 = FUN_180025ab0(*plVar2,uVar7);
    plVar1 = *(longlong **)(*plVar2 + 8);
    iVar10 = 0;
    iStack_44 = -1;
    iVar13 = -1;
    do {
      iVar12 = (int)(uVar11 + iVar5 + iVar10) % 9;
      lVar9 = (**(code **)(*plVar1 + 0x568))(plVar1,uVar8,iVar12);
      if ((lVar9 != 0) && (lVar9 = FUN_180025d10(*plVar2,lVar9), lVar9 != 0)) {
        iVar6 = FUN_180025c50(*plVar2,lVar9);
        if ((iVar3 != 0) && (iVar6 == iVar3)) break;
        iVar6 = FUN_18002af70(iVar6);
        if (iVar13 < iVar6) {
          iVar13 = iVar6;
          iStack_44 = iVar12;
        }
      }
      iVar10 = iVar10 + 1;
      iVar12 = iStack_44;
    } while (iVar10 != 9);
    iStack_44 = iVar12;
    if ((iStack_44 != -1) && (cVar4 = FUN_18002aa80(0x1802e9ac0), cVar4 != '\0')) {
      FUN_180025a80(*plVar2,uVar7,iStack_44);
      _DAT_1802f7bb0 = 0x1802e9ac0;
    }
  }
  return;
}

// UI RVA 0x2e5d0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2e5d0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18002e5d0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180150914);
  FUN_18000cf30(param_2,param_1,0x1802e9dc8);
  FUN_18000cf30(param_2,param_1,0x1802e9e40);
  FUN_18000d040(param_2,param_1,0x1802e9d48);
  FUN_18000cef0(param_2,param_1,0x1802e9e00);
  FUN_18000cef0(param_2,param_1,0x1802e9da8);
  FUN_18000cef0(param_2,param_1,0x1802e9e20);
  FUN_180013e90(param_1,param_2,&UNK_180150919);
  FUN_18000cef0(param_2,param_1,0x1802e9cd0);
  FUN_18000cef0(param_2,param_1,0x1802e9d88);
  FUN_18000cef0(param_2,param_1,0x1802e9cf0);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802e9d20,0x1802e9d10,&DAT_1802e9d28);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x2e6c0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2e6c0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18002e6c0(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c450(param_1,&UNK_180150924,0x1802e9dc8);
  FUN_18000c450(param_1,&UNK_180150930,0x1802e9e40);
  FUN_18000c6f0(param_1,&UNK_18015093e,0x1802e9d48);
  FUN_18000c3b0(param_1,&UNK_18015094c,0x1802e9e00);
  FUN_18000c3b0(param_1,&UNK_180150956,0x1802e9da8);
  FUN_18000c3b0(param_1,&UNK_180150964,0x1802e9e20);
  FUN_18000c3b0(param_1,&UNK_180150977,0x1802e9cd0);
  FUN_18000c3b0(param_1,&UNK_180150985,0x1802e9d88);
  FUN_18000c3b0(param_1,&UNK_18015099c,0x1802e9cf0);
  uVar1 = uRam00000001802e9d29;
  uVar2 = DAT_1802e9d28;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_1801509b1,DAT_1802e9d28);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802e9d28;
      break;
    case 2:
      uRam00000001802e9d29 = DAT_1802e9d28;
      break;
    case 3:
      uVar2 = uRam00000001802e9d29;
    }
  }
  DAT_1802e9d28 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x2e7b0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2e7b0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
FUN_18002e7b0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  double dVar1;
  double dVar2;
  double dVar3;
  float fVar4;
  double dVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  float fVar16;
  undefined4 uVar17;
  float fVar18;
  undefined1 auStack_160 [24];
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined4 uStack_130;
  undefined4 uStack_12c;
  undefined4 uStack_128;
  undefined4 uStack_124;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined4 uStack_f0;
  undefined4 uStack_ec;
  undefined8 uStack_e8;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  double dStack_c8;
  double dStack_c0;
  double dStack_b0;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  double dStack_98;
  
  uVar9 = FUN_180023670(param_1,param_4);
  FUN_180025640(&uStack_d8,param_1,uVar9);
  FUN_1800093b0(&uStack_148,((double)CONCAT44(uStack_d4,uStack_d8) + dStack_c0) * _DAT_1801507f0,
                (double)CONCAT44(uStack_cc,uStack_d0) + _DAT_1801507f8,
                (dStack_c8 + dStack_b0) * _DAT_1801507f0);
  FUN_180023550(&uStack_d8,param_1,param_4);
  dVar2 = (double)_DAT_1802e9df8;
  if (DAT_1802e9e18 == '\x01') {
    uVar9 = FUN_18000a050(0,_DAT_180150800);
    fVar16 = (float)FUN_18000a510(0x1802f7de0,uVar9,_DAT_180150808);
    dVar2 = dVar2 - (double)fVar16;
    if (dVar2 < 0.0) {
      dVar2 = 0.0;
    }
  }
  uVar9 = FUN_1800250d0(param_1,param_2);
  uVar10 = FUN_180025120(param_1,param_2);
  uVar11 = FUN_180025170(param_1,param_2);
  uVar12 = FUN_1800251c0(param_1,param_2);
  cVar6 = FUN_180025430(param_1,uVar9);
  fVar16 = _DAT_180150810;
  fVar18 = _DAT_180150810;
  if (cVar6 == '\0') {
    fVar18 = 0.0;
  }
  cVar6 = FUN_180025430(param_1,uVar10);
  fVar4 = _DAT_180150814;
  if (cVar6 != '\0') {
    fVar18 = fVar18 + _DAT_180150814;
  }
  cVar6 = FUN_180025430(param_1,uVar11);
  if (cVar6 == '\0') {
    fVar16 = 0.0;
  }
  cVar6 = FUN_180025430(param_1,uVar12);
  if (cVar6 != '\0') {
    fVar16 = fVar16 + fVar4;
  }
  uVar9 = FUN_180023170(param_1,param_4);
  uVar17 = FUN_180023b40(param_1,param_4);
  FUN_180029290(auStack_160,uVar9,fVar18,fVar16,uVar17);
  dStack_98 = dStack_c8;
  uStack_a8 = uStack_d8;
  uStack_a4 = uStack_d4;
  uStack_a0 = uStack_d0;
  uStack_9c = uStack_cc;
  FUN_180009400(&uStack_130,&uStack_a8,auStack_160);
  uStack_108 = uStack_138;
  uStack_118 = uStack_148;
  uStack_110 = uStack_140;
  uStack_e8 = uStack_120;
  uStack_f8 = uStack_130;
  uStack_f4 = uStack_12c;
  uStack_f0 = uStack_128;
  uStack_ec = uStack_124;
  FUN_180009400(&uStack_a8,&uStack_118,&uStack_f8);
  dVar5 = dStack_98;
  uVar17 = uStack_a0;
  dVar3 = (double)CONCAT44(uStack_a4,uStack_a8);
  dVar1 = (double)func_0x0001800b29b0(SUB84(dVar3 - dVar2,0));
  iVar15 = (int)dVar1;
  dVar1 = (double)func_0x0001800b29b0(SUB84(dVar5 - dVar2,0));
  iVar14 = (int)dVar1;
  dVar1 = (double)func_0x0001800b29b0(uVar17);
  iVar13 = (int)dVar1;
  dVar1 = (double)func_0x0001800b29b0(SUB84(dVar3 + dVar2,0));
  dVar2 = (double)func_0x0001800b29b0(SUB84(dVar2 + dVar5,0));
  uVar9 = FUN_180024690(param_1,param_3,iVar15,iVar13,iVar14);
  iVar7 = FUN_180024280(param_1,uVar9);
  if (iVar7 == 0) {
    iVar7 = (int)dVar2;
    if (iVar14 != iVar7) {
      uVar9 = FUN_180024690(param_1,param_3,iVar15,iVar13,iVar7);
      iVar8 = FUN_180024280(param_1,uVar9);
      if (iVar8 != 0) goto LAB_18002ea56;
    }
    iVar8 = (int)dVar1;
    if (iVar15 != iVar8) {
      uVar9 = FUN_180024690(param_1,param_3,iVar8,iVar13,iVar14);
      iVar15 = FUN_180024280(param_1,uVar9);
      if (iVar15 != 0) goto LAB_18002ea56;
      if (iVar14 != iVar7) {
        uVar9 = FUN_180024690(param_1,param_3,iVar8,iVar13,iVar7);
        iVar7 = FUN_180024280(param_1,uVar9);
        if (iVar7 != 0) goto LAB_18002ea56;
      }
    }
    uVar9 = 1;
  }
  else {
LAB_18002ea56:
    uVar9 = 0;
  }
  return uVar9;
}

