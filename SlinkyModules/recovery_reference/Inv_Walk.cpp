// Recovered decompiler view: Inv Walk
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x39790, 0x3a0f0); proximity does not prove ownership.

// CALLBACK RVA 0x39790; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/inv_walk_events/inv_walk_events.c
// Differential report: analysis/module_behavior_recovery/inv_walk_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x39790; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong FUN_180039790(longlong param_1)

{
  longlong lVar1;
  longlong *plVar2;
  undefined8 uVar3;
  ulonglong in_RAX;
  longlong lVar4;
  longlong lVar5;
  ulonglong uVar6;
  undefined8 *puVar7;
  ulonglong uVar8;
  
  if ((*(char *)(param_1 + 0x18) == '\0') &&
     (in_RAX = 0x1802ef3d0, *(longlong *)(param_1 + 0x10) == 0x1802ef3d0)) {
    lVar1 = **(longlong **)(param_1 + 8);
    if (_DAT_1802fc780 == 0) {
      uVar6 = 0;
    }
    else {
      plVar2 = *(longlong **)(lVar1 + 8);
      lVar4 = FUN_180022d10(lVar1,(*(longlong **)(param_1 + 8))[3]);
      lVar5 = FUN_180025ed0(lVar1,lVar4);
      uVar6 = CONCAT71((int7)((ulonglong)lVar4 >> 8),lVar5 != 0 && lVar4 != 0);
      if (lVar5 != 0 && lVar4 != 0) {
        if (_DAT_1802fc780 != 0) {
          puVar7 = (undefined8 *)0x1802fc680;
          uVar8 = 0;
          do {
            uVar3 = *puVar7;
            FUN_180025f80(lVar1,lVar5,uVar3);
            (**(code **)(*plVar2 + 0xb0))(plVar2,uVar3);
            uVar8 = uVar8 + 1;
            puVar7 = puVar7 + 1;
          } while (uVar8 < _DAT_1802fc780);
        }
      }
      else if (_DAT_1802fc780 != 0) {
        puVar7 = (undefined8 *)0x1802fc680;
        uVar8 = 0;
        do {
          (**(code **)(*plVar2 + 0xb0))(plVar2,*puVar7);
          uVar8 = uVar8 + 1;
          puVar7 = puVar7 + 1;
        } while (uVar8 < _DAT_1802fc780);
      }
      _DAT_1802fc780 = 0;
    }
    return uVar6 & 0xffffffff;
  }
  return in_RAX;
}

// CALLBACK RVA 0x397c0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/inv_walk_update/inv_walk_update.c
// Differential report: analysis/module_behavior_recovery/inv_walk_update/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x397c0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800397c0(longlong param_1)

{
  undefined8 *puVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  char cVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  longlong lVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  byte bVar17;
  byte bVar18;
  bool bVar19;
  int iVar20;
  bool bVar21;
  bool bVar22;
  bool bVar23;
  bool bVar24;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  lVar8 = FUN_180022c90(*puVar1,puVar1[3]);
  uVar9 = FUN_180022cf0(*puVar1,puVar1[3]);
  uVar10 = FUN_180025120(*puVar1,uVar9);
  uVar11 = FUN_180025170(*puVar1,uVar9);
  uVar12 = FUN_1800251c0(*puVar1,uVar9);
  uVar13 = FUN_1800250d0(*puVar1,uVar9);
  uVar14 = FUN_180025080(*puVar1,uVar9);
  uVar6 = FUN_180025490(*puVar1,uVar10);
  uVar7 = FUN_180025490(*puVar1,uVar11);
  bVar2 = FUN_180025490(*puVar1,uVar12);
  bVar3 = FUN_180025490(*puVar1,uVar13);
  bVar4 = FUN_180025490(*puVar1,uVar14);
  bVar21 = _DAT_1802ef620 == 1;
  bVar22 = _DAT_1802ef678 != 2;
  bVar23 = _DAT_1802fc780 != 0;
  bVar17 = (bVar22 && bVar21) && bVar23;
  bVar24 = _DAT_1802ef678 == 0;
  bVar19 = bVar24 && (bool)bVar17;
  _DAT_1802fc78c = _DAT_1802fc78c + 1;
  if (lVar8 == 0) {
    if (_DAT_1802fc790 != 0) {
      FUN_180025460(*puVar1,uVar10,uVar6);
      FUN_180025460(*puVar1,uVar11,uVar7);
      FUN_180025460(*puVar1,uVar12,bVar2);
      FUN_180025460(*puVar1,uVar13,bVar3);
      FUN_180025460(*puVar1,uVar14,bVar4);
    }
    _DAT_1802fc790 = 0;
    if (*(char *)(puVar1 + 8) == '\0') {
      _DAT_1802fc790 = 0;
      return;
    }
    bVar21 = false;
LAB_180039c24:
    if ((!bVar21 && (DAT_1802fc788 & 1) == 0) && bVar19 == false) goto LAB_180039c87;
    uVar15 = *puVar1;
    if (bVar19 == false) goto LAB_180039a89;
  }
  else {
    bVar18 = bVar2 | bVar3 | (byte)uVar6 | (byte)uVar7 | bVar4;
    cVar5 = FUN_180025b80(*puVar1,lVar8);
    if (cVar5 != '\0') {
      if (_DAT_1802ef620 == 1) {
        uVar15 = FUN_180023f40(*puVar1,puVar1[5]);
        uVar16 = FUN_180022d10(*puVar1,puVar1[3]);
        uVar16 = FUN_180025ed0(*puVar1,uVar16);
        lVar8 = FUN_180025ad0(*puVar1,uVar15);
        bVar19 = true;
        if (lVar8 == 0) {
          if (_DAT_1802fc790 != 1) {
            uVar15 = FUN_180024080(*puVar1,puVar1[5]);
            uVar15 = FUN_180026170(*puVar1,uVar15);
            lVar8 = FUN_180026140(*puVar1,uVar15,0);
            if ((((lVar8 != 0) || (lVar8 = FUN_180026140(*puVar1,uVar15,1), lVar8 != 0)) ||
                (lVar8 = FUN_180026140(*puVar1,uVar15,2), lVar8 != 0)) ||
               (lVar8 = FUN_180026140(*puVar1,uVar15,3), lVar8 != 0)) goto LAB_180039b51;
          }
          bVar19 = (bool)bVar17;
        }
LAB_180039b51:
        bVar18 = bVar18 & (bVar19 ^ 1U);
        if (_DAT_1802fc790 == 2 && bVar18 == 0) {
          uVar15 = FUN_180026f40(*puVar1);
          uVar15 = FUN_180026f70(*puVar1,uVar15);
          iVar20 = 3;
LAB_180039be4:
          FUN_180025f80(*puVar1,uVar16,uVar15);
          _DAT_1802fc790 = iVar20;
        }
        else {
          iVar20 = _DAT_1802fc790;
          if (((bVar18 & (_DAT_1802fc790 == 3 && _DAT_1802fc780 == 0)) == 1) &&
             ((_DAT_1802ef678 == 2 ||
              (iVar20 = 3, (uint)(longlong)_DAT_1802ef6b8 <= (uint)(_DAT_1802fc78c - _DAT_1802fc794)
              )))) {
            uVar15 = FUN_180027030(*puVar1,0);
            iVar20 = 2;
            goto LAB_180039be4;
          }
        }
        bVar18 = bVar19 | iVar20 == 3;
        bVar21 = iVar20 != 0;
      }
      else {
        _DAT_1802fc790 = 3;
        bVar21 = true;
        bVar18 = 0;
      }
      bVar17 = bVar17 | _DAT_1802ef678 != 2 & bVar18;
      bVar19 = (bool)(_DAT_1802ef678 == 0 & bVar17);
      goto LAB_180039c24;
    }
    _DAT_1802fc790 = 1;
    if (_DAT_1802ef620 == 1) {
      bVar19 = false;
      if (_DAT_1802ef678 != 2) {
        bVar19 = (uint)(_DAT_1802fc78c - _DAT_1802fc794) < (uint)(longlong)_DAT_1802ef6b8;
      }
      bVar18 = bVar17 | bVar18 ^ 1 | bVar19;
      bVar17 = _DAT_1802ef6f0 != 2 | bVar18;
      uVar15 = *puVar1;
      if (((_DAT_1802ef678 == 0 & bVar18) != 0) || ((_DAT_1802ef6f0 == 0 & bVar17) != 0))
      goto LAB_180039c3d;
LAB_180039a89:
      FUN_180025460(uVar15,uVar10,uVar6);
      FUN_180025460(*puVar1,uVar11,uVar7);
      FUN_180025460(*puVar1,uVar12,bVar2);
      FUN_180025460(*puVar1,uVar13,bVar3);
      FUN_180025460(*puVar1,uVar14,bVar4);
      bVar19 = false;
      goto LAB_180039c87;
    }
    uVar15 = *puVar1;
    if (!bVar24 || ((!bVar22 || !bVar21) || !bVar23)) goto LAB_180039a89;
  }
LAB_180039c3d:
  FUN_180025460(uVar15,uVar10,0);
  FUN_180025460(*puVar1,uVar11,0);
  FUN_180025460(*puVar1,uVar12,0);
  FUN_180025460(*puVar1,uVar13,0);
  FUN_180025460(*puVar1,uVar14,0);
  bVar19 = true;
LAB_180039c87:
  if (bVar17 != 0) {
    FUN_1800236c0(*puVar1,puVar1[5],0);
    uVar10 = *puVar1;
    uVar9 = FUN_180025210(uVar10,uVar9);
    FUN_180025460(uVar10,uVar9,0);
  }
  DAT_1802fc798 = 0;
  DAT_1802fc788 = bVar19;
  return;
}

// CALLBACK RVA 0x39ce0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/inv_walk_events/inv_walk_events.c
// Differential report: analysis/module_behavior_recovery/inv_walk_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x39ce0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180039ce0(longlong param_1)

{
  longlong *plVar1;
  int iVar2;
  longlong lVar3;
  undefined8 uVar4;
  
  if (_DAT_1802ef620 != 1) {
    return;
  }
  lVar3 = FUN_180026f00(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x18));
  if (lVar3 != 0) {
    iVar2 = FUN_180026fb0(*(undefined8 *)(param_1 + 8),lVar3);
    if (iVar2 != 2) {
      return;
    }
    *(undefined1 *)(param_1 + 0x20) = 1;
    _DAT_1802fc790 = 2;
    return;
  }
  lVar3 = FUN_180026ec0(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x18));
  if (lVar3 == 0) {
    lVar3 = FUN_180026ff0(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x18));
    if (lVar3 == 0) {
      return;
    }
    if (_DAT_1802fc790 == 2) goto LAB_180039e09;
    if (_DAT_1802fc780 == 0) {
      return;
    }
  }
  else if (_DAT_1802fc790 == 2) {
    uVar4 = FUN_180026f40(*(undefined8 *)(param_1 + 8));
    uVar4 = FUN_180026f70(*(undefined8 *)(param_1 + 8),uVar4);
    FUN_180025f80(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10),uVar4);
    _DAT_1802fc790 = 3;
    DAT_1802fc798 = 1;
  }
  else if (_DAT_1802fc780 == 0 && (DAT_1802fc798 & 1) == 0) {
    _DAT_1802fc794 = _DAT_1802fc78c;
    return;
  }
  if ((_DAT_1802fc780 != 0x20) &&
     (plVar1 = *(longlong **)(*(longlong *)(param_1 + 8) + 8),
     lVar3 = (**(code **)(*plVar1 + 0xa8))(plVar1,*(undefined8 *)(param_1 + 0x18)), lVar3 != 0)) {
    *(longlong *)(_DAT_1802fc780 * 8 + 0x1802fc680) = lVar3;
    _DAT_1802fc780 = _DAT_1802fc780 + 1;
  }
LAB_180039e09:
  *(undefined1 *)(param_1 + 0x20) = 1;
  return;
}

// CALLBACK RVA 0x39e30; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/inv_walk_events/inv_walk_events.c
// Differential report: analysis/module_behavior_recovery/inv_walk_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x39e30; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180039e30(longlong param_1)

{
  undefined8 *puVar1;
  char cVar2;
  
  if (DAT_1802fc798 == '\0') {
    puVar1 = *(undefined8 **)(param_1 + 8);
    cVar2 = FUN_180039ff0(*puVar1,puVar1[3]);
    if ((cVar2 != '\0') && (_DAT_1802fc794 = _DAT_1802fc78c, *(char *)(puVar1 + 8) == '\x01')) {
      do {
        cVar2 = FUN_180025900(*puVar1);
      } while (cVar2 != '\0');
      do {
        cVar2 = FUN_1800257a0(*puVar1);
      } while (cVar2 != '\0');
    }
  }
  return;
}

// UI RVA 0x39ea0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x39ea0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180039ea0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180152dd3);
  FUN_18000d040(param_2,param_1,0x1802ef5f0);
  if (_DAT_1802ef620 == 0) {
    return;
  }
  FUN_18000d040(param_2,param_1,0x1802ef648);
  if (_DAT_1802ef678 != 2) {
    FUN_18000cf30(param_2,param_1,0x1802ef688);
  }
  FUN_180013e90(param_1,param_2,&UNK_180152dd8);
  cVar1 = FUN_180014d00(param_1,param_2,uRam00000001802ef6d8,0x1802ef6c0,uRam00000001802ef6e0,
                        uRam00000001802ef6e8,&DAT_1802ef6f0,uRam00000001802ef6f8);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x39f40; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x39f40; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180039f40(undefined8 *param_1)

{
  undefined8 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  longlong lVar5;
  longlong lVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  
  FUN_18000c6f0(param_1,&UNK_180152de9,0x1802ef5f0);
  FUN_18000c6f0(param_1,&UNK_180152dee,0x1802ef648);
  FUN_18000c450(param_1,&UNK_180152dfc,0x1802ef688);
  uVar2 = uRam00000001802ef6f4;
  uVar3 = _DAT_1802ef6f0;
  if (*(char *)((longlong)param_1 + 0xc) == '\0') {
    switch(*(undefined4 *)(param_1 + 1)) {
    case 0:
      lVar5 = FUN_18004e4d0(*param_1);
      iVar4 = FUN_18004d110(lVar5);
      lVar6 = lRam00000001802ef6e8;
      uVar3 = uVar2;
      if ((iVar4 != 0) && (uVar7 = (ulonglong)uRam00000001802ef6e0, uVar7 != 0)) {
        uVar1 = *(undefined8 *)(lVar5 + 0x20);
        uVar8 = 0;
        do {
          iVar4 = func_0x00018013d0a0(*(undefined8 *)(lVar6 + uVar8 * 8),uVar1);
          if (iVar4 == 0) {
            _DAT_1802ef6f0 = (int)uVar8;
            return;
          }
          uVar8 = uVar8 + 1;
        } while (uVar7 != uVar8);
      }
      break;
    case 1:
      lVar6 = FUN_18004f080(*param_1,&UNK_180152e0a,
                            *(undefined8 *)(lRam00000001802ef6e8 + (ulonglong)_DAT_1802ef6f0 * 8));
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar6 == 0;
      uVar3 = _DAT_1802ef6f0;
      break;
    case 2:
      uRam00000001802ef6f4 = _DAT_1802ef6f0;
      break;
    case 3:
      uVar3 = uRam00000001802ef6f4;
    }
  }
  _DAT_1802ef6f0 = uVar3;
  return;
}

// CANDIDATE_LOCAL RVA 0x39fb0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x39fb0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180039fb0(undefined8 param_1)

{
  FUN_1800ab710(param_1,0x20,&UNK_180152e17,
                *(undefined8 *)((ulonglong)_DAT_1802ef620 * 8 + 0x1802ef5e0));
  return;
}

// CANDIDATE_LOCAL RVA 0x39ff0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x39ff0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong FUN_180039ff0(longlong param_1)

{
  longlong *plVar1;
  undefined8 uVar2;
  longlong lVar3;
  longlong lVar4;
  ulonglong uVar5;
  undefined8 *puVar6;
  ulonglong uVar7;
  
  if (_DAT_1802fc780 == 0) {
    uVar5 = 0;
  }
  else {
    plVar1 = *(longlong **)(param_1 + 8);
    lVar3 = FUN_180022d10();
    lVar4 = FUN_180025ed0(param_1,lVar3);
    uVar5 = CONCAT71((int7)((ulonglong)lVar3 >> 8),lVar4 != 0 && lVar3 != 0);
    if (lVar4 != 0 && lVar3 != 0) {
      if (_DAT_1802fc780 != 0) {
        puVar6 = (undefined8 *)0x1802fc680;
        uVar7 = 0;
        do {
          uVar2 = *puVar6;
          FUN_180025f80(param_1,lVar4,uVar2);
          (**(code **)(*plVar1 + 0xb0))(plVar1,uVar2);
          uVar7 = uVar7 + 1;
          puVar6 = puVar6 + 1;
        } while (uVar7 < _DAT_1802fc780);
      }
    }
    else if (_DAT_1802fc780 != 0) {
      puVar6 = (undefined8 *)0x1802fc680;
      uVar7 = 0;
      do {
        (**(code **)(*plVar1 + 0xb0))(plVar1,*puVar6);
        uVar7 = uVar7 + 1;
        puVar6 = puVar6 + 1;
      } while (uVar7 < _DAT_1802fc780);
    }
    _DAT_1802fc780 = 0;
  }
  return uVar5 & 0xffffffff;
}

