// Recovered decompiler view: Notifications
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x35000, 0x35d50); proximity does not prove ownership.

// CALLBACK RVA 0x35000; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/notifications/notifications.c
// Differential report: analysis/module_behavior_recovery/notifications/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x35000; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong * FUN_180035000(longlong param_1)

{
  char cVar1;
  longlong lVar2;
  longlong lVar3;
  longlong *plVar4;
  undefined8 uVar5;
  longlong lVar6;
  longlong *plVar7;
  longlong lVar8;
  bool bVar9;
  
  lVar3 = _DAT_1802fc440;
  lVar2 = _DAT_1802fbfd8;
  plVar4 = *(longlong **)(param_1 + 0x10);
  if (plVar4 == (longlong *)0x1802ed320) {
    if (*(char *)(param_1 + 0x18) == '\0') {
      _DAT_1802fbfd8 = 0;
      return (longlong *)0x1802ed320;
    }
    plVar4 = (longlong *)0x0;
    LOCK();
    bVar9 = DAT_1802fbfb0 == 0;
    if (bVar9) {
      DAT_1802fbfb0 = 1;
    }
    else {
      plVar4 = (longlong *)(ulonglong)DAT_1802fbfb0;
    }
    UNLOCK();
    if (!bVar9) {
      return plVar4;
    }
    plVar4 = (longlong *)&DAT_1802fbfd8;
    lVar6 = (_DAT_1802fbfd8 + _DAT_1802fc440 +
            ((ulonglong)(_DAT_1802fbfd8 + _DAT_1802fc440) / 5 & 0xfffffffffffffffe) * -5) * 0x70;
    *(undefined4 *)(lVar6 + 0x1802fbfe0) = 1;
    lVar8 = lVar2;
    if (lVar2 == 10) {
      lVar8 = lVar3;
    }
    *(undefined4 *)(lVar6 + 0x1802fc04c) = 0;
    if (lVar2 == 10) {
      plVar4 = (longlong *)&DAT_1802fc440;
    }
    *plVar4 = lVar8 + 1;
    uVar5 = FUN_180009380(*(undefined4 *)(_DAT_18013e498 + 0x1c));
    plVar4 = (longlong *)FUN_1800ab710(lVar6 + 0x1802fbfe4,0x65,&UNK_180151f02,uVar5);
    return plVar4;
  }
  if ((*(uint *)(plVar4 + 3) & 0x10) != 0) {
    return plVar4;
  }
  if (((*(uint *)(plVar4 + 3) & 2) != 0) && (DAT_1802ed548 != '\0')) {
    return plVar4;
  }
  if (((char)plVar4[4] == '\x01') && (DAT_1802ed568 != '\0')) {
    return plVar4;
  }
  switch((int)plVar4[2]) {
  case 0:
    cVar1 = cRam00000001802ed588;
    break;
  case 1:
    cVar1 = cRam00000001802ed5a8;
    break;
  case 2:
    cVar1 = cRam00000001802ed5e8;
    break;
  case 3:
    cVar1 = cRam00000001802ed5c8;
    break;
  case 4:
    if (cRam00000001802ed608 != '\x01') {
      return plVar4;
    }
  default:
    goto LAB_18003516f;
  }
  if (cVar1 != '\0') {
LAB_18003516f:
    plVar7 = (longlong *)&DAT_1802fbfc8;
    if (*(char *)(param_1 + 0x18) != '\0') {
      plVar7 = (longlong *)&DAT_1802fbfb8;
    }
    plVar4 = (longlong *)*plVar4;
    *plVar7 = (longlong)plVar4;
    *(int *)(plVar7 + 1) = (int)plVar7[1] + 1;
  }
  return plVar4;
}

// CALLBACK RVA 0x351a0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/notifications/notifications.c
// Differential report: analysis/module_behavior_recovery/notifications/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x351a0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800351a0(longlong param_1)

{
  float fVar1;
  uint uVar2;
  double dVar3;
  double dVar4;
  longlong lVar5;
  ulonglong uVar6;
  undefined *puVar7;
  ulonglong uVar8;
  longlong lVar9;
  bool bVar10;
  ulonglong uVar11;
  longlong *plVar12;
  float fVar13;
  double dVar14;
  
  uVar2 = _DAT_1802fbfc0;
  if ((DAT_1802ed628 == '\x01') && (*(char *)(_DAT_18013e498 + 0x14) == '\0')) {
    _DAT_1802fbfd8 = 0;
    _DAT_1802fbfc0 = 0;
    _DAT_1802fbfd0 = 0;
  }
  else {
    if (_DAT_1802fbfd8 != 0) {
      lVar9 = _DAT_1802fc440 * 0x70 + 0x1802fc04c;
      uVar6 = _DAT_1802fc440;
      do {
        uVar11 = _DAT_1802fc440 + 1;
        uVar8 = _DAT_1802fbfd8;
        if (*(float *)(lVar9 + (uVar6 / 10) * -0x460) <= _DAT_180151e48) goto LAB_18003526f;
        uVar6 = uVar6 + 1;
        lVar9 = lVar9 + 0x70;
        _DAT_1802fbfd8 = _DAT_1802fbfd8 - 1;
        _DAT_1802fc440 = uVar11;
      } while (_DAT_1802fbfd8 != 0);
    }
    uVar8 = 0;
LAB_18003526f:
    if (_DAT_1802fbfc0 != 0) {
      lVar9 = (uVar8 + _DAT_1802fc440 + ((uVar8 + _DAT_1802fc440) / 5 & 0xfffffffffffffffe) * -5) *
              0x70;
      uVar6 = uVar8;
      if (uVar8 == 10) {
        uVar6 = _DAT_1802fc440;
      }
      *(undefined4 *)(lVar9 + 0x1802fbfe0) = 1;
      plVar12 = (longlong *)&DAT_1802fbfd8;
      if (uVar8 == 10) {
        plVar12 = (longlong *)&DAT_1802fc440;
      }
      *(undefined4 *)(lVar9 + 0x1802fc04c) = 0;
      *plVar12 = uVar6 + 1;
      if (uVar2 == 1) {
        puVar7 = &UNK_180151f66;
        uVar6 = _DAT_1802fbfb8;
      }
      else {
        uVar6 = (ulonglong)uVar2;
        puVar7 = &UNK_180151f7d;
      }
      FUN_1800ab710(lVar9 + 0x1802fbfe4,0x65,puVar7,&UNK_180151f6c,uVar6);
      _DAT_1802fbfc0 = 0;
      uVar8 = _DAT_1802fbfd8;
    }
    uVar2 = _DAT_1802fbfd0;
    if (_DAT_1802fbfd0 != 0) {
      lVar9 = (uVar8 + _DAT_1802fc440 + ((uVar8 + _DAT_1802fc440) / 5 & 0xfffffffffffffffe) * -5) *
              0x70;
      uVar6 = uVar8;
      if (uVar8 == 10) {
        uVar6 = _DAT_1802fc440;
      }
      *(undefined4 *)(lVar9 + 0x1802fbfe0) = 1;
      plVar12 = (longlong *)&DAT_1802fbfd8;
      if (uVar8 == 10) {
        plVar12 = (longlong *)&DAT_1802fc440;
      }
      *(undefined4 *)(lVar9 + 0x1802fc04c) = 0;
      *plVar12 = uVar6 + 1;
      if (uVar2 == 1) {
        puVar7 = &UNK_180151f66;
        uVar6 = _DAT_1802fbfc8;
      }
      else {
        uVar6 = (ulonglong)uVar2;
        puVar7 = &UNK_180151f7d;
      }
      FUN_1800ab710(lVar9 + 0x1802fbfe4,0x65,puVar7,&UNK_180151f74,uVar6);
      _DAT_1802fbfd0 = 0;
      uVar8 = _DAT_1802fbfd8;
    }
    if (uVar8 != 0) {
      uVar2 = *(uint *)(param_1 + 0x10);
      *(uint *)(param_1 + 0x10) = uVar2 | 1;
      dVar4 = _DAT_180151e58;
      dVar3 = _DAT_180151e50;
      fVar1 = *(float *)(param_1 + 0x14);
      lVar9 = _DAT_1802fc440 * 0x70 + 0x1802fc04c;
      bVar10 = false;
      uVar6 = _DAT_1802fc440;
      do {
        lVar5 = (uVar6 / 10) * -0x460;
        fVar13 = *(float *)(lVar9 + lVar5) + fVar1;
        *(float *)(lVar9 + lVar5) = fVar13;
        dVar14 = (double)fVar13;
        bVar10 = (bool)(bVar10 | (dVar3 < dVar14 || dVar14 < dVar4));
        lVar9 = lVar9 + 0x70;
        uVar6 = uVar6 + 1;
        uVar8 = uVar8 - 1;
      } while (uVar8 != 0);
      if (bVar10) {
        *(uint *)(param_1 + 0x10) = uVar2 | 3;
      }
    }
  }
  return;
}

// CALLBACK RVA 0x354b0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/notifications_render/notifications_render.c
// Differential report: analysis/module_behavior_recovery/notifications_render/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x354b0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800354b0(longlong param_1)

{
  int iVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  float fVar4;
  double dVar5;
  float fVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  float fVar9;
  float fVar10;
  ulonglong uVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  double dVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  float fVar18;
  float fVar19;
  longlong in_stack_fffffffffffffe78;
  undefined4 uVar21;
  undefined8 uVar20;
  undefined1 auStack_178 [16];
  undefined1 auStack_168 [16];
  undefined1 auStack_158 [16];
  float fStack_148;
  float fStack_144;
  float fStack_140;
  float fStack_13c;
  float fStack_130;
  undefined4 uStack_12c;
  undefined4 uStack_128;
  undefined4 uStack_124;
  undefined8 uStack_120;
  float fStack_118;
  float fStack_114;
  float fStack_110;
  float fStack_10c;
  float fStack_108;
  float fStack_104;
  float fStack_100;
  float fStack_fc;
  float fStack_f8;
  float fStack_f4;
  float fStack_f0;
  float fStack_ec;
  
  if ((_DAT_1802fbfd8 != 0) &&
     ((DAT_1802ed628 != '\x01' || (*(char *)(_DAT_18013e498 + 0x14) != '\0')))) {
    puVar2 = *(undefined8 **)(param_1 + 0x10);
    uStack_120 = *puVar2;
    FUN_180079610(uStack_120,_DAT_180151e60);
    fVar10 = _DAT_180151eb0;
    fVar9 = _DAT_180151eac;
    uVar8 = _DAT_180151ea4;
    uVar7 = _DAT_180151e8c;
    fVar6 = _DAT_180151e70;
    dVar5 = _DAT_180151e68;
    fVar4 = _DAT_180151e64;
    if (_DAT_1802fbfd8 != 0) {
      uVar11 = 0;
      fVar18 = _DAT_180151e64;
      do {
        uVar21 = (undefined4)((ulonglong)in_stack_fffffffffffffe78 >> 0x20);
        in_stack_fffffffffffffe78 =
             (_DAT_1802fc440 + ((_DAT_1802fc440 + uVar11) / 5 & 0xfffffffffffffffe) * -5 + uVar11) *
             0x70;
        dVar15 = (double)*(float *)(in_stack_fffffffffffffe78 + 0x1802fc04c);
        if (dVar15 < dVar5) {
LAB_180035810:
          fVar13 = (float)FUN_18000a280((float)(dVar15 / dVar5));
        }
        else {
          fVar13 = fVar6;
          if (_DAT_180151e78 < dVar15) {
            dVar15 = _DAT_180151e80 - dVar15;
            goto LAB_180035810;
          }
        }
        fVar19 = fVar6;
        if (fVar13 <= fVar6) {
          fVar19 = fVar13;
        }
        FUN_180074a60(uStack_120,fVar19);
        fVar13 = (fVar6 - fVar19) * _DAT_180151e88;
        uVar3 = *puVar2;
        iVar1 = *(int *)(in_stack_fffffffffffffe78 + 0x1802fbfe0);
        uVar16 = _DAT_180151e90;
        uVar17 = _DAT_180151e90;
        uVar14 = uVar7;
        if (iVar1 == 2) {
LAB_1800355ca:
          FUN_180074150(&fStack_130,uVar14,uVar16,uVar17,CONCAT44(uVar21,0x3f800000));
        }
        else {
          if (iVar1 != 1) {
            uVar16 = uVar7;
            uVar17 = uVar7;
            if (iVar1 == 0) {
              uVar16 = _DAT_180151e98;
              uVar17 = _DAT_180151e9c;
              uVar14 = _DAT_180151e94;
            }
            goto LAB_1800355ca;
          }
          FUN_1800324b0(&fStack_f8);
          FUN_180074130(&fStack_130,fStack_f8,fStack_f4,fStack_f0);
        }
        in_stack_fffffffffffffe78 = in_stack_fffffffffffffe78 + 0x1802fbfe4;
        uVar21 = 0;
        fVar12 = (float)FUN_18007ae90(uVar3,0,0,in_stack_fffffffffffffe78,0,0);
        uVar20 = CONCAT44(uVar21,0x42280000);
        FUN_18000a070(&fStack_f8,fVar13 + fVar4,fVar18,fVar12 + _DAT_180151ea0,uVar20);
        uVar20 = CONCAT44((int)((ulonglong)uVar20 >> 0x20),0x3f800000);
        FUN_180074150(auStack_178,uVar8,uVar8,uVar8,uVar20);
        uVar21 = (undefined4)((ulonglong)uVar20 >> 0x20);
        FUN_180074ef0(uVar3,auStack_178);
        fStack_118 = fStack_f8;
        fStack_114 = fStack_f4;
        fStack_110 = fStack_f0;
        fStack_10c = fStack_ec;
        FUN_180010a60(puVar2,&fStack_118,_DAT_180151ea8);
        FUN_18000a070(&fStack_118,fStack_f8 + fVar9,fStack_f4 + fVar9,_DAT_180151eb4,
                      CONCAT44(uVar21,fStack_ec + fVar10));
        fStack_108 = fStack_130;
        fStack_104 = (float)uStack_12c;
        fStack_100 = (float)uStack_128;
        fStack_fc = (float)uStack_124;
        FUN_1800741b0(auStack_168,&fStack_108,_DAT_180151eb8);
        FUN_180074ef0(uVar3,auStack_168);
        fStack_108 = fStack_118;
        fStack_104 = fStack_114;
        fStack_100 = fStack_110;
        fStack_fc = fStack_10c;
        FUN_180010a60(puVar2,&fStack_108,_DAT_180151ebc);
        fStack_108 = fStack_130;
        fStack_104 = (float)uStack_12c;
        fStack_100 = (float)uStack_128;
        fStack_fc = (float)uStack_124;
        FUN_180074ef0(uVar3,&fStack_108);
        fStack_108 = fStack_118;
        fStack_104 = fStack_114;
        fStack_100 = fStack_110;
        fStack_fc = fStack_10c;
        uVar21 = 1;
        FUN_180010cb0(puVar2,&fStack_108,1,0,&UNK_180151f88);
        FUN_18000a070(&fStack_108,fStack_118 + fStack_110 + fVar9,fStack_f4,
                      (fStack_f0 - fStack_110) + fVar10,CONCAT44(uVar21,fStack_ec));
        FUN_180074150(auStack_158,uVar7,uVar7,uVar7,0x3f800000);
        FUN_180074ef0(uVar3,auStack_158);
        fStack_148 = fStack_108;
        fStack_144 = fStack_104;
        fStack_140 = fStack_100;
        fStack_13c = fStack_fc;
        FUN_180010cb0(puVar2,&fStack_148,0,0,in_stack_fffffffffffffe78);
        fVar18 = fVar18 + fVar19 * _DAT_180151ec0;
        uVar11 = uVar11 + 1;
      } while (uVar11 < _DAT_1802fbfd8);
    }
    FUN_180074a60(uStack_120,_DAT_180151e70);
  }
  return;
}

// CALLBACK RVA 0x35960; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/notifications/notifications.c
// Differential report: analysis/module_behavior_recovery/notifications/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x35960; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180035960(longlong param_1)

{
  undefined8 uVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined *puVar6;
  
  lVar3 = _DAT_1802fc440;
  lVar2 = _DAT_1802fbfd8;
  if ((ulonglong)*(uint *)(param_1 + 0x10) != 2) {
    uVar1 = *(undefined8 *)(&UNK_180151f90 + (ulonglong)*(uint *)(param_1 + 0x10) * 8);
    puVar6 = &UNK_180151fb0;
    if (*(undefined **)(param_1 + 8) != (undefined *)0x0) {
      puVar6 = *(undefined **)(param_1 + 8);
    }
    plVar5 = (longlong *)&DAT_1802fbfd8;
    lVar4 = (_DAT_1802fbfd8 + _DAT_1802fc440 +
            ((ulonglong)(_DAT_1802fbfd8 + _DAT_1802fc440) / 5 & 0xfffffffffffffffe) * -5) * 0x70;
    *(undefined4 *)(lVar4 + 0x1802fbfe0) = 0;
    if (lVar2 == 10) {
      plVar5 = (longlong *)&DAT_1802fc440;
      lVar2 = lVar3;
    }
    *(undefined4 *)(lVar4 + 0x1802fc04c) = 0;
    *plVar5 = lVar2 + 1;
    FUN_1800ab710(lVar4 + 0x1802fbfe4,0x65,&UNK_180151f66,uVar1,puVar6);
  }
  return;
}

// CALLBACK RVA 0x35a30; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/notifications/notifications.c
// Differential report: analysis/module_behavior_recovery/notifications/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x35a30; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180035a30(longlong param_1)

{
  longlong lVar1;
  longlong lVar2;
  longlong lVar3;
  longlong *plVar4;
  
  lVar2 = _DAT_1802fc440;
  lVar1 = _DAT_1802fbfd8;
  plVar4 = (longlong *)&DAT_1802fbfd8;
  lVar3 = (_DAT_1802fbfd8 + _DAT_1802fc440 +
          ((ulonglong)(_DAT_1802fbfd8 + _DAT_1802fc440) / 5 & 0xfffffffffffffffe) * -5) * 0x70;
  *(undefined4 *)(lVar3 + 0x1802fbfe0) = 2;
  *(undefined4 *)(lVar3 + 0x1802fc04c) = 0;
  if (lVar1 == 10) {
    plVar4 = (longlong *)&DAT_1802fc440;
    lVar1 = lVar2;
  }
  *plVar4 = lVar1 + 1;
  if (*(longlong *)(param_1 + 0x10) == 0) {
    FUN_1800ab710(lVar3 + 0x1802fbfe4,0x65,&UNK_180151fe8,*(undefined4 *)(param_1 + 8));
  }
  else {
    FUN_1800ab710(lVar3 + 0x1802fbfe4,0x65,&UNK_180151fe5);
  }
  return;
}

// CALLBACK RVA 0x35af0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/notifications/notifications.c
// Differential report: analysis/module_behavior_recovery/notifications/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x35af0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180035af0(longlong param_1)

{
  longlong lVar1;
  longlong lVar2;
  longlong *plVar3;
  undefined8 uVar4;
  longlong lVar5;
  longlong lVar6;
  
  lVar2 = _DAT_1802fc440;
  lVar1 = _DAT_1802fbfd8;
  plVar3 = (longlong *)&DAT_1802fbfd8;
  lVar5 = (_DAT_1802fbfd8 + _DAT_1802fc440 +
          ((ulonglong)(_DAT_1802fbfd8 + _DAT_1802fc440) / 5 & 0xfffffffffffffffe) * -5) * 0x70;
  *(undefined4 *)(lVar5 + 0x1802fbfe0) = 1;
  lVar6 = lVar1;
  if (lVar1 == 10) {
    lVar6 = lVar2;
  }
  *(undefined4 *)(lVar5 + 0x1802fc04c) = 0;
  if (lVar1 == 10) {
    plVar3 = (longlong *)&DAT_1802fc440;
  }
  *plVar3 = lVar6 + 1;
  if (*(char *)(param_1 + 8) == '\x01') {
    *(undefined8 *)(lVar5 + 0x1802fbfe9) = 0x64656464612064;
    uVar4 = 0x6120646e65697246;
  }
  else {
    *(undefined8 *)(lVar5 + 0x1802fbfeb) = 0x6465766f6d6572;
    uVar4 = 0x7220646e65697246;
  }
  *(undefined8 *)(lVar5 + 0x1802fbfe4) = uVar4;
  return;
}

// UI RVA 0x35bb0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x35bb0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180035bb0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180152012);
  FUN_18000cef0(param_2,param_1,0x1802ed610);
  FUN_18000cef0(param_2,param_1,0x1802ed550);
  FUN_18000cef0(param_2,param_1,0x1802ed530);
  FUN_180013e90(param_1,param_2,&UNK_18015201a);
  FUN_18000cef0(param_2,param_1,0x1802ed570);
  FUN_18000cef0(param_2,param_1,0x1802ed590);
  FUN_18000cef0(param_2,param_1,0x1802ed5b0);
  FUN_18000cef0(param_2,param_1,0x1802ed5d0);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802ed600,0x1802ed5f0,0x1802ed608);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x35c80; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x35c80; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180035c80(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c3b0(param_1,&UNK_180152031,0x1802ed610);
  FUN_18000c3b0(param_1,&UNK_18015203d,0x1802ed550);
  FUN_18000c3b0(param_1,&UNK_18015204e,0x1802ed530);
  FUN_18000c3b0(param_1,&UNK_18015205d,0x1802ed570);
  FUN_18000c3b0(param_1,&UNK_180152069,0x1802ed590);
  FUN_18000c3b0(param_1,&UNK_180152073,0x1802ed5b0);
  FUN_18000c3b0(param_1,&UNK_18015207e,0x1802ed5d0);
  uVar1 = uRam00000001802ed609;
  uVar2 = uRam00000001802ed608;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_18015208a,uRam00000001802ed608);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = uRam00000001802ed608;
      break;
    case 2:
      uRam00000001802ed609 = uRam00000001802ed608;
      break;
    case 3:
      uVar2 = uRam00000001802ed609;
    }
  }
  uRam00000001802ed608 = uVar2;
  return;
}

