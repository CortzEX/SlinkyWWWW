// Recovered decompiler view: Mod Overlay
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x34080, 0x35000); proximity does not prove ownership.

// CALLBACK RVA 0x34080; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/mod_overlay_extended/mod_overlay.c
// Differential report: analysis/module_behavior_recovery/mod_overlay_extended/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x34080; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180034080(longlong param_1)

{
  char cVar1;
  undefined8 uVar2;
  code *pcVar3;
  undefined1 uVar4;
  longlong lVar5;
  byte bVar6;
  undefined8 *puVar7;
  longlong lVar8;
  uint uVar9;
  longlong lVar10;
  undefined8 *puVar11;
  char *pcVar12;
  ulonglong uVar13;
  longlong *plVar14;
  longlong lVar15;
  char *pcVar16;
  bool bVar17;
  undefined8 auStack_70 [5];
  ulonglong uStack_48;
  
  bVar6 = DAT_1802faff4;
  puVar7 = auStack_70 + 1;
  lVar15 = *(longlong *)(param_1 + 8);
  uVar9 = (uint)DAT_1802ed1b8 << 5 |
          (uint)DAT_1802ed198 << 4 |
          (uint)DAT_1802ed118 + (uint)DAT_1802ed138 * 2 + (uint)DAT_1802ed158 * 4 +
          (uint)DAT_1802ed178 * 8;
  if (_DAT_1802faff0 != uVar9 || (DAT_1802faff4 & 1) != 0) {
    FUN_180034ce0(*(undefined8 *)(lVar15 + 8));
    DAT_1802faff5 = 1;
    DAT_1802faff4 = 0;
    _DAT_1802faff0 = uVar9;
  }
  if (((bVar6 & 1) != 0) || (*(char *)(lVar15 + 0x40) == '\0')) {
    if (_DAT_1802faff8 != 0) {
      lVar15 = 0x1802fb008;
      pcVar16 = (char *)0x1802fb01c;
      uVar13 = 0;
      bVar6 = DAT_1802ed1d8;
      do {
        lVar10 = uVar13 * 0x50;
        puVar11 = (undefined8 *)(lVar10 + 0x1802fb000);
        if ((bVar6 & 1) == 0) {
          uVar2 = *(undefined8 *)*puVar11;
          puVar7[-1] = 0x1800341eb;
          FUN_1800ab710(lVar10 + 0x1802fb008,0x14,&UNK_180151cfc,uVar2);
          plVar14 = (longlong *)*puVar11;
          bVar6 = DAT_1802ed1d8;
        }
        else {
          plVar14 = (longlong *)*puVar11;
          lVar5 = *plVar14;
          uStack_48 = uVar13;
          puVar7[-1] = 0x18003418c;
          lVar5 = func_0x0001800ab840(lVar5);
          bVar17 = lVar5 == 0;
          pcVar3 = (code *)*puVar7;
          *puVar7 = 0x180034199;
          func_0x000180e6314d();
          if (!bVar17) {
            lVar8 = 0;
            do {
              cVar1 = *(char *)(*plVar14 + lVar8);
              *puVar7 = 0x1800341ab;
              uVar4 = (*pcVar3)((int)cVar1);
              *(undefined1 *)(lVar15 + lVar8) = uVar4;
              lVar8 = lVar8 + 1;
            } while (lVar5 != lVar8);
          }
          *(undefined1 *)(lVar10 + 0x1802fb008 + lVar5) = 0;
          puVar7 = puVar7 + 1;
          uVar13 = uStack_48;
          bVar6 = 1;
        }
        pcVar3 = (code *)plVar14[0x41];
        pcVar12 = (char *)(lVar10 + 0x1802fb01c);
        if ((pcVar3 == (code *)0x0) || (DAT_1802ed1f8 == '\0')) {
          *pcVar12 = '\0';
        }
        else {
          *(undefined8 *)((longlong)puVar7 + -8) = 0x18003421b;
          (*pcVar3)(pcVar12);
          if (DAT_1802ed1d8 == 1) {
            bVar6 = 1;
            if (*pcVar12 != '\0') {
              cVar1 = *pcVar16;
              *(undefined8 *)((longlong)puVar7 + -8) = 0x18003424a;
              func_0x000180e28595((int)cVar1);
                    /* WARNING: Bad instruction - Truncating control flow here */
              halt_baddata();
            }
          }
          else {
            bVar6 = 0;
          }
        }
        uVar13 = uVar13 + 1;
        lVar15 = lVar15 + 0x50;
        pcVar16 = pcVar16 + 0x50;
      } while (uVar13 < _DAT_1802faff8);
    }
    DAT_1802faff5 = 1;
  }
  return;
}

// CALLBACK RVA 0x34290; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/mod_overlay_extended/mod_overlay.c
// Differential report: analysis/module_behavior_recovery/mod_overlay_extended/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x34290; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180034290(longlong param_1)

{
  longlong lVar1;
  longlong *plVar2;
  char cVar3;
  ulonglong uVar4;
  undefined1 *puVar5;
  ulonglong uVar6;
  longlong lVar7;
  
  lVar1 = *(longlong *)(param_1 + 0x10);
  _DAT_1802fbfa0 = 0x3e4ccccd;
  if (lVar1 == 0x1802ecef0) {
    plVar2 = *(longlong **)(*(longlong *)(param_1 + 8) + 8);
    _DAT_1802faff8 = 0;
    if (*(char *)(param_1 + 0x18) != '\x01') {
      _DAT_1802faff8 = 0;
      _DAT_1802fbfa0 = 0x3e4ccccd;
      return;
    }
    uVar4 = plVar2[1];
    if (uVar4 != 0) {
      uVar6 = 0;
      do {
        lVar1 = *(longlong *)(*plVar2 + uVar6 * 8);
        if (((*(char *)(lVar1 + 0x14) != '\x01') || ((*(byte *)(lVar1 + 0x18) & 4) != 0)) ||
           ((DAT_1802ed1b8 == '\x01' && (*(int *)(lVar1 + 0x1c) == 0)))) goto LAB_180034390;
        switch(*(undefined4 *)(lVar1 + 0x10)) {
        case 0:
          cVar3 = DAT_1802ed118;
          break;
        case 1:
          cVar3 = DAT_1802ed138;
          break;
        case 2:
          cVar3 = DAT_1802ed178;
          break;
        case 3:
          cVar3 = DAT_1802ed158;
          break;
        case 4:
          if (DAT_1802ed198 != '\x01') goto LAB_180034390;
        default:
          goto LAB_180034381;
        }
        if (cVar3 != '\0') {
LAB_180034381:
          FUN_180034e90();
          uVar4 = plVar2[1];
        }
LAB_180034390:
        uVar6 = uVar6 + 1;
      } while (uVar6 < uVar4);
    }
    goto LAB_180034483;
  }
  if (_DAT_1802faff8 != 0) {
    puVar5 = (undefined1 *)0x1802fb048;
    lVar7 = _DAT_1802faff8;
LAB_1800342e0:
    if (*(longlong *)(puVar5 + -0x48) != lVar1) goto code_r0x0001800342ea;
    if (*(char *)(param_1 + 0x18) == '\0') {
      *puVar5 = 0;
      return;
    }
    if ((*(byte *)(lVar1 + 0x18) & 4) != 0) {
      _DAT_1802fbfa0 = 0x3e4ccccd;
      return;
    }
    if ((DAT_1802ed1b8 == '\x01') && (*(int *)(lVar1 + 0x1c) == 0)) {
      _DAT_1802fbfa0 = 0x3e4ccccd;
      return;
    }
    switch(*(undefined4 *)(lVar1 + 0x10)) {
    case 0:
      cVar3 = DAT_1802ed118;
      break;
    case 1:
      cVar3 = DAT_1802ed138;
      break;
    case 2:
      cVar3 = DAT_1802ed178;
      break;
    case 3:
      cVar3 = DAT_1802ed158;
      break;
    case 4:
      if (DAT_1802ed198 != '\x01') {
        _DAT_1802fbfa0 = 0x3e4ccccd;
        return;
      }
    default:
      goto LAB_1800344bd;
    }
    if (cVar3 == '\0') {
      _DAT_1802fbfa0 = 0x3e4ccccd;
      return;
    }
LAB_1800344bd:
    *puVar5 = 1;
    return;
  }
LAB_1800342f4:
  if (*(char *)(param_1 + 0x18) != '\x01') {
    _DAT_1802fbfa0 = 0x3e4ccccd;
    return;
  }
  if ((*(byte *)(lVar1 + 0x18) & 4) != 0) {
    _DAT_1802fbfa0 = 0x3e4ccccd;
    return;
  }
  if ((DAT_1802ed1b8 == '\x01') && (*(int *)(lVar1 + 0x1c) == 0)) {
    _DAT_1802fbfa0 = 0x3e4ccccd;
    return;
  }
  switch(*(undefined4 *)(lVar1 + 0x10)) {
  case 0:
    cVar3 = DAT_1802ed118;
    break;
  case 1:
    cVar3 = DAT_1802ed138;
    break;
  case 2:
    cVar3 = DAT_1802ed178;
    break;
  case 3:
    cVar3 = DAT_1802ed158;
    break;
  case 4:
    if (DAT_1802ed198 != '\x01') {
      _DAT_1802fbfa0 = 0x3e4ccccd;
      return;
    }
  default:
    goto LAB_18003447e;
  }
  if (cVar3 != '\0') {
LAB_18003447e:
    FUN_180034e90();
LAB_180034483:
    DAT_1802faff5 = 1;
  }
  return;
code_r0x0001800342ea:
  puVar5 = puVar5 + 0x50;
  lVar7 = lVar7 + -1;
  if (lVar7 == 0) goto LAB_1800342f4;
  goto LAB_1800342e0;
}

// CALLBACK RVA 0x344d0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/mod_overlay_extended/mod_overlay.c
// Differential report: analysis/module_behavior_recovery/mod_overlay_extended/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x344d0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800344d0(longlong param_1)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_1 + 0x10);
  *(uint *)(param_1 + 0x10) = uVar1 | 1;
  if ((DAT_1802faff5 == '\0') && (_DAT_1802fbfa0 <= 0.0)) {
    return;
  }
  *(uint *)(param_1 + 0x10) = uVar1 | 3;
  return;
}

// CALLBACK RVA 0x34510; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/mod_overlay_render/mod_overlay_render.c
// Differential report: analysis/module_behavior_recovery/mod_overlay_render/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x34510; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180034510(longlong param_1)

{
  float fVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  double dVar4;
  double dVar5;
  float fVar6;
  longlong lVar7;
  char *pcVar8;
  longlong lVar9;
  ulonglong uVar10;
  ulonglong uVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  undefined8 in_stack_fffffffffffffee8;
  undefined4 uVar18;
  undefined8 uVar17;
  undefined4 *in_stack_fffffffffffffef0;
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  undefined4 uStack_e0;
  undefined4 uStack_dc;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  float fStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  float fStack_b0;
  undefined4 uStack_ac;
  
  puVar2 = *(undefined8 **)(param_1 + 0x10);
  uVar3 = *puVar2;
  FUN_180079610(uVar3);
  FUN_180010340(puVar2,0);
  fVar6 = _DAT_180151c68;
  uVar18 = (undefined4)((ulonglong)in_stack_fffffffffffffee8 >> 0x20);
  if (0.0 < _DAT_1802fbfa0) {
    _DAT_1802fbfa0 = _DAT_1802fbfa0 - *(float *)(param_1 + 0x18);
  }
  if (_DAT_1802faff8 != 0) {
    dVar4 = (double)*(float *)(param_1 + 0x18);
    lVar9 = -1;
    lVar7 = 0x1802fb050;
    uVar10 = 0;
    dVar5 = dVar4 * _DAT_180151c60;
    dVar4 = (double)CONCAT44(_UNK_180151c54 ^ (uint)((ulonglong)dVar4 >> 0x20),
                             _DAT_180151c50 ^ SUB84(dVar4,0)) * _DAT_180151c60;
    uVar11 = _DAT_1802faff8;
    do {
      fVar12 = *(float *)(lVar7 + -0xc);
      if (*(char *)(lVar7 + -8) == '\x01') {
        if ((fVar12 != fVar6) || (NAN(fVar12) || NAN(fVar6))) {
          fVar15 = (float)((double)fVar12 + dVar5);
          fVar12 = fVar6;
          if (fVar15 <= fVar6) {
            fVar12 = fVar15;
          }
          *(float *)(lVar7 + -0xc) = fVar12;
        }
      }
      else {
        fVar12 = (float)((double)fVar12 + dVar4);
        *(float *)(lVar7 + -0xc) = fVar12;
        if (fVar12 <= 0.0) {
          _DAT_1802faff8 = uVar11 - 1;
          func_0x0001800ab910(lVar7 + -0x50,lVar7,(uVar11 + lVar9) * 0x50);
          uVar11 = uVar11 - 1;
        }
      }
      uVar18 = (undefined4)((ulonglong)in_stack_fffffffffffffee8 >> 0x20);
      uVar10 = uVar10 + 1;
      lVar9 = lVar9 + -1;
      lVar7 = lVar7 + 0x50;
    } while (uVar10 < uVar11);
  }
  if (DAT_1802faff5 == '\x01') {
    FUN_180079690(uVar3,9);
    fVar6 = _DAT_180151c6c;
    if (_DAT_1802faff8 == 0) {
      uVar11 = 0;
    }
    else {
      pcVar8 = (char *)0x1802fb01c;
      lVar7 = 0x1802fb008;
      uVar10 = 0;
      do {
        uVar18 = 0;
        in_stack_fffffffffffffef0 = &uStack_b8;
        FUN_18007ae90(uVar3,0,0,lVar7,0,&uStack_b8);
        *(ulonglong *)(pcVar8 + 0x20) = CONCAT44(uStack_ac,fStack_b0);
        if (*pcVar8 != '\0') {
          uVar18 = 0;
          in_stack_fffffffffffffef0 = &uStack_b8;
          FUN_18007ae90(uVar3,0,0,pcVar8,0,&uStack_b8);
          *(float *)(pcVar8 + 0x20) = fStack_b0 + fVar6 + *(float *)(pcVar8 + 0x20);
        }
        uVar10 = uVar10 + 1;
        pcVar8 = pcVar8 + 0x50;
        lVar7 = lVar7 + 0x50;
        uVar11 = _DAT_1802faff8;
      } while (uVar10 < _DAT_1802faff8);
    }
    func_0x00018013d0f0(0x1802fb000,uVar11,0x50,FUN_180034fb0);
    DAT_1802faff5 = '\0';
  }
  FUN_180079690(uVar3,9);
  uVar17 = CONCAT44(uVar18,0x3f333333);
  fVar15 = 0.0;
  FUN_180074150(&uStack_b8,0,0,0,uVar17);
  FUN_180074130(&uStack_e8,_DAT_1802ed240,_DAT_1802ed244,_DAT_1802ed248);
  FUN_180074130(&uStack_d8,_DAT_1802ed260,_DAT_1802ed264,_DAT_1802ed268);
  fVar12 = _DAT_180151c6c;
  fVar6 = _DAT_180151c68;
  if (_DAT_1802faff8 != 0) {
    fVar1 = *(float *)(puVar2 + 3);
    pcVar8 = (char *)0x1802fb01c;
    lVar7 = 0x1802fb008;
    uVar11 = 0;
    do {
      uVar18 = (undefined4)((ulonglong)uVar17 >> 0x20);
      if ((*(float *)(pcVar8 + 0x28) != fVar6) ||
         (fVar13 = fVar6, NAN(*(float *)(pcVar8 + 0x28)) || NAN(fVar6))) {
        fVar13 = (float)FUN_18000a280();
      }
      FUN_180074a60(uVar3,fVar13);
      uVar11 = uVar11 + 1;
      fVar14 = _DAT_1802ed2a8;
      if ((uVar11 < _DAT_1802faff8) &&
         (fVar14 = *(float *)(pcVar8 + 0x20) - *(float *)(pcVar8 + 0x70),
         _DAT_1802ed2a8 <= *(float *)(pcVar8 + 0x20) - *(float *)(pcVar8 + 0x70))) {
        fVar14 = _DAT_1802ed2a8;
      }
      uStack_c8 = uStack_b8;
      uStack_c4 = uStack_b4;
      fStack_c0 = fStack_b0;
      uStack_bc = uStack_ac;
      FUN_180074ef0(uVar3,&uStack_c8);
      FUN_180075bc0(uVar3);
      in_stack_fffffffffffffef0 =
           (undefined4 *)((ulonglong)in_stack_fffffffffffffef0 & 0xffffffff00000000);
      FUN_180076a10(uVar3,(fVar1 - (_DAT_1802ed2e0 + _DAT_1802ed2e0)) -
                          *(float *)(pcVar8 + 0x20) * fVar13,fVar15,
                    _DAT_1802ed2e0 + _DAT_1802ed2e0 + *(float *)(pcVar8 + 0x20),
                    CONCAT44(uVar18,_DAT_1802ed318 + _DAT_1802ed318 + *(float *)(pcVar8 + 0x24)),
                    in_stack_fffffffffffffef0,0,0,fVar14);
      FUN_180077210(uVar3);
      uStack_c8 = uStack_e8;
      uStack_c4 = uStack_e4;
      fStack_c0 = (float)uStack_e0;
      uStack_bc = uStack_dc;
      FUN_180074ef0(uVar3,&uStack_c8);
      fVar16 = _DAT_1802ed318 + fVar15;
      uVar17 = 0;
      fVar14 = (float)FUN_180079770(uVar3,(fVar1 - _DAT_1802ed2e0) -
                                          *(float *)(pcVar8 + 0x20) * fVar13,fVar16,lVar7,0);
      if (*pcVar8 != '\0') {
        uStack_c8 = uStack_d8;
        uStack_c4 = uStack_d4;
        fStack_c0 = (float)uStack_d0;
        uStack_bc = uStack_cc;
        FUN_180074ef0(uVar3,&uStack_c8);
        uVar17 = 0;
        FUN_180079770(uVar3,fVar14 + fVar12,fVar16,pcVar8,0);
      }
      fVar15 = fVar15 + fVar13 * (_DAT_1802ed318 + _DAT_1802ed318 + *(float *)(pcVar8 + 0x24));
      pcVar8 = pcVar8 + 0x50;
      lVar7 = lVar7 + 0x50;
    } while (uVar11 < _DAT_1802faff8);
  }
  FUN_180074a60(uVar3,_DAT_180151c68);
  return;
}

// CALLBACK RVA 0x349f0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/mod_overlay_extended/mod_overlay.c
// Differential report: analysis/module_behavior_recovery/mod_overlay_extended/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x349f0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_1800349f0(longlong param_1)

{
  if (*(int *)(param_1 + 0x10) != 0) {
    return;
  }
  DAT_1802faff4 = 1;
  return;
}

// CALLBACK RVA 0x34a10; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/mod_overlay_extended/mod_overlay.c
// Differential report: analysis/module_behavior_recovery/mod_overlay_extended/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x34a10; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180034a10(longlong param_1)

{
  if (DAT_1802ed1b8 == '\x01') {
    FUN_180034ce0(*(undefined8 *)(param_1 + 8));
    DAT_1802faff5 = 1;
  }
  return;
}

// UI RVA 0x34a40; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x34a40; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180034a40(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180151d5e);
  FUN_18000cef0(param_2,param_1,0x1802ed100);
  FUN_18000cef0(param_2,param_1,0x1802ed120);
  FUN_18000cef0(param_2,param_1,0x1802ed140);
  FUN_18000cef0(param_2,param_1,0x1802ed160);
  FUN_18000cef0(param_2,param_1,0x1802ed180);
  FUN_180013e90(param_1,param_2,&UNK_180151d71);
  FUN_18000cf30(param_2,param_1,0x1802ed200);
  FUN_18000cf30(param_2,param_1,0x1802ed2b0);
  FUN_18000cf30(param_2,param_1,0x1802ed2e8);
  FUN_18000cf30(param_2,param_1,0x1802ed278);
  FUN_18000d0a0(param_2,param_1,0x1802ed238);
  FUN_18000d0a0(param_2,param_1,0x1802ed258);
  FUN_18000cef0(param_2,param_1,0x1802ed1c0);
  FUN_18000cef0(param_2,param_1,0x1802ed1e0);
  FUN_180013e90(param_1,param_2,&UNK_180151d7f);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802ed1b0,0x1802ed1a0,&DAT_1802ed1b8);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x34b90; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x34b90; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180034b90(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c3b0(param_1,&UNK_180151d8a,0x1802ed100);
  FUN_18000c3b0(param_1,&UNK_180151d96,0x1802ed120);
  FUN_18000c3b0(param_1,&UNK_180151da0,0x1802ed140);
  FUN_18000c3b0(param_1,&UNK_180151dab,0x1802ed160);
  FUN_18000c3b0(param_1,&UNK_180151db7,0x1802ed180);
  FUN_18000c450(param_1,&UNK_180151dc4,0x1802ed200);
  FUN_18000c450(param_1,&UNK_180151dce,0x1802ed2b0);
  FUN_18000c450(param_1,&UNK_180151dd8,0x1802ed2e8);
  FUN_18000c450(param_1,&UNK_180151de2,0x1802ed278);
  FUN_18000c7e0(param_1,&UNK_180151dee,0x1802ed238);
  FUN_18000c7e0(param_1,&UNK_180151df9,0x1802ed258);
  FUN_18000c3b0(param_1,&UNK_180151e07,0x1802ed1c0);
  FUN_18000c3b0(param_1,&UNK_180151e11,0x1802ed1e0);
  uVar1 = uRam00000001802ed1b9;
  uVar2 = DAT_1802ed1b8;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180151e1e,DAT_1802ed1b8);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802ed1b8;
      break;
    case 2:
      uRam00000001802ed1b9 = DAT_1802ed1b8;
      break;
    case 3:
      uVar2 = uRam00000001802ed1b9;
    }
  }
  DAT_1802ed1b8 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x34ce0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x34ce0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180034ce0(longlong *param_1)

{
  char cVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  char cVar5;
  char cVar6;
  char cVar7;
  longlong lVar8;
  ulonglong uVar9;
  longlong lVar10;
  ulonglong uVar11;
  longlong *plVar12;
  
  cVar7 = DAT_1802ed1b8;
  cVar6 = DAT_1802ed198;
  cVar5 = DAT_1802ed178;
  cVar4 = DAT_1802ed158;
  cVar3 = DAT_1802ed138;
  cVar2 = DAT_1802ed118;
  if (_DAT_1802faff8 != 0) {
    plVar12 = (longlong *)0x1802fb000;
    lVar8 = _DAT_1802faff8;
    do {
      lVar10 = *plVar12;
      if (((*(byte *)(lVar10 + 0x18) & 4) == 0) &&
         ((cVar7 == '\0' || (*(int *)(lVar10 + 0x1c) != 0)))) {
        switch(*(undefined4 *)(lVar10 + 0x10)) {
        case 0:
          cVar1 = cVar2;
          break;
        case 1:
          cVar1 = cVar3;
          break;
        case 2:
          cVar1 = cVar5;
          break;
        case 3:
          cVar1 = cVar4;
          break;
        case 4:
          cVar1 = cVar6;
          break;
        default:
          goto LAB_180034d45;
        }
        if (cVar1 == '\0') goto LAB_180034d40;
      }
      else {
LAB_180034d40:
        *(undefined1 *)(plVar12 + 9) = 0;
      }
LAB_180034d45:
      plVar12 = plVar12 + 10;
      lVar8 = lVar8 + -1;
    } while (lVar8 != 0);
  }
  uVar9 = param_1[1];
  if (uVar9 != 0) {
    uVar11 = 0;
    do {
      lVar8 = *(longlong *)(*param_1 + uVar11 * 8);
      if (((*(char *)(lVar8 + 0x14) != '\x01') || ((*(byte *)(lVar8 + 0x18) & 4) != 0)) ||
         ((DAT_1802ed1b8 == '\x01' && (*(int *)(lVar8 + 0x1c) == 0)))) goto LAB_180034dd0;
      switch(*(undefined4 *)(lVar8 + 0x10)) {
      case 0:
        cVar2 = DAT_1802ed118;
        break;
      case 1:
        cVar2 = DAT_1802ed138;
        break;
      case 2:
        cVar2 = DAT_1802ed178;
        break;
      case 3:
        cVar2 = DAT_1802ed158;
        break;
      case 4:
        if (DAT_1802ed198 != '\x01') goto LAB_180034dd0;
      default:
        goto LAB_180034e46;
      }
      if (cVar2 != '\0') {
LAB_180034e46:
        if (_DAT_1802faff8 != 0) {
          plVar12 = (longlong *)0x1802fb000;
          lVar10 = _DAT_1802faff8;
          do {
            if (*plVar12 == lVar8) {
              *(undefined1 *)(plVar12 + 9) = 1;
              goto LAB_180034dd0;
            }
            plVar12 = plVar12 + 10;
            lVar10 = lVar10 + -1;
          } while (lVar10 != 0);
        }
        FUN_180034e90();
        uVar9 = param_1[1];
      }
LAB_180034dd0:
      uVar11 = uVar11 + 1;
    } while (uVar11 < uVar9);
  }
  return;
}

// CANDIDATE_LOCAL RVA 0x34e90; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x34e90; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180034e90(undefined8 *param_1)

{
  longlong lVar1;
  longlong lVar2;
  char *pcVar3;
  
  lVar1 = _DAT_1802faff8 * 0x50;
  *(undefined8 **)(lVar1 + 0x1802fb000) = param_1;
  *(undefined4 *)(lVar1 + 0x1802fb044) = 0;
  *(undefined1 *)(lVar1 + 0x1802fb048) = 1;
  if (DAT_1802ed1d8 == '\0') {
    FUN_1800ab710(lVar1 + 0x1802fb008,0x14,&UNK_180151cfc,*param_1);
    param_1 = *(undefined8 **)(lVar1 + 0x1802fb000);
  }
  else {
    lVar2 = func_0x0001800ab840(*param_1);
    if (lVar2 != 0) {
      func_0x00018032ecfb();
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    *(undefined1 *)(lVar1 + 0x1802fb008) = 0;
  }
  pcVar3 = (char *)(lVar1 + 0x1802fb01c);
  if (((code *)param_1[0x41] == (code *)0x0) || (DAT_1802ed1f8 == '\0')) {
    *pcVar3 = '\0';
  }
  else {
    (*(code *)param_1[0x41])(pcVar3);
    if ((DAT_1802ed1d8 == '\x01') && (*pcVar3 != '\0')) {
      func_0x000180bb8f39();
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
  }
  _DAT_1802faff8 = _DAT_1802faff8 + 1;
  return;
}

// CANDIDATE_LOCAL RVA 0x34fb0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x34fb0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


undefined8 FUN_180034fb0(longlong param_1,longlong param_2)

{
  code *pcVar1;
  undefined8 uVar2;
  
  uVar2 = 1;
  if ((*(float *)(param_2 + 0x3c) <= *(float *)(param_1 + 0x3c)) &&
     (uVar2 = 0xffffffff, *(float *)(param_1 + 0x3c) <= *(float *)(param_2 + 0x3c))) {
    func_0x000180002538(param_1 + 8,param_2 + 8);
    pcVar1 = (code *)swi(3);
    uVar2 = (*pcVar1)();
    return uVar2;
  }
  return uVar2;
}

// CANDIDATE_LOCAL RVA 0x34ff0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x34ff0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


undefined1 FUN_180034ff0(void)

{
  undefined1 uVar1;
  
  uVar1 = DAT_1802fbfb0;
  LOCK();
  DAT_1802fbfb0 = 0;
  UNLOCK();
  return uVar1;
}

