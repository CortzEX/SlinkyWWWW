// Recovered decompiler view: Inv Manager
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x47090, 0x48600); proximity does not prove ownership.

// CALLBACK RVA 0x47090; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/inv_manager/inv_manager.c
// Differential report: analysis/module_behavior_recovery/inv_manager/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x47090; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180047090(longlong param_1)

{
  byte bVar1;
  undefined8 *puVar2;
  code *pcVar3;
  int iVar4;
  uint uVar5;
  undefined8 uVar6;
  undefined4 uVar7;
  char cVar8;
  byte bVar9;
  longlong lVar10;
  undefined8 uVar11;
  ulonglong uVar12;
  undefined8 uVar13;
  uint uVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  uint in_stack_ffffffffffffff80;
  undefined4 uStack_7c;
  
  puVar2 = *(undefined8 **)(param_1 + 8);
  lVar10 = FUN_180022c90(*puVar2,puVar2[3]);
  if ((lVar10 == 0) ||
     (cVar8 = FUN_180025b80(*puVar2,lVar10), uVar14 = _DAT_1803049e0, cVar8 == '\0')) {
    _DAT_1803049f0 = 0;
    uRam00000001803049f4 = 0;
    uRam00000001803049f8 = 0;
    _DAT_1803049e0 = 0;
    uRam00000001803049e4 = 0;
    uRam00000001803049e8 = 0;
    uRam00000001803049ec = 0;
    _DAT_180304a00 = _DAT_1802f4e80;
    if (DAT_1802f5228 == '\x01') {
      uVar11 = FUN_18000a050(_DAT_18015559c,_DAT_1801555a4);
      fVar15 = (float)FUN_18000a3e0(uVar11);
      _DAT_180304a00 = fVar15 * _DAT_180304a00;
    }
    _DAT_180304a08 = FUN_18002aad0(0xd);
    return;
  }
  if (_DAT_1803049e0 == 2) {
    return;
  }
  if ((0.0 < _DAT_180304a00) &&
     (_DAT_180304a00 = _DAT_180304a00 + _DAT_180155590, 0.0 < _DAT_180304a00)) {
    return;
  }
  *(undefined1 *)(param_1 + 0x10) = 1;
LAB_1800471d9:
  do {
    uVar5 = uRam00000001803049f4;
    iVar4 = _DAT_1803049f0;
    if (5 < uVar14) {
      return;
    }
    uVar12 = (ulonglong)uVar14;
    switch(uVar12) {
    default:
      if (**(char **)(&UNK_180155b40 + uVar12 * 8) == '\0') {
        uVar14 = uVar14 + 1;
        uRam00000001803049e4 = 0;
        uRam00000001803049e8 = 0;
        uRam00000001803049ec = 0;
        _DAT_1803049f0 = 0;
        uRam00000001803049f4 = 0;
        uRam00000001803049f8 = 0;
        _DAT_1803049e0 = uVar14;
      }
      else {
        bVar1 = (&UNK_180155b50)[uVar12];
        if (uRam00000001803049f8._4_1_ < bVar1) {
          pcVar3 = *(code **)(&UNK_180155b60 + uVar12 * 8);
          do {
            cVar8 = (*pcVar3)(puVar2,&DAT_1803049e0);
            if (cVar8 != '\0') {
              uVar11 = FUN_18002aad0(uRam00000001803049f8._5_1_);
              fVar17 = fRam00000001802f525c / fRam00000001802f5260;
              fVar15 = (float)FUN_180009ee0(uVar11,_DAT_180304a08);
              if (cRam00000001802f5280 == '\x01') {
                fVar18 = fVar15 * _UNK_180155598;
                if (fVar15 * _UNK_180155598 <= _DAT_18015559c) {
                  fVar18 = _DAT_18015559c;
                }
                fVar17 = fVar17 * fVar18;
              }
              if (DAT_1802f5228 == '\x01') {
                uVar13 = FUN_18000a050(_DAT_18015559c,_UNK_1801555a0);
                fVar15 = (float)FUN_18000a3e0(uVar13);
                fVar17 = fVar17 * fVar15;
              }
              uVar13 = uRam00000001803049f8;
              uRam00000001803049f8 = CONCAT44(uRam00000001803049f8._4_4_,uVar14);
              uVar6 = uRam00000001803049f8;
              uRam00000001803049f8._7_1_ = SUB81(uVar13,7);
              uRam00000001803049f8._0_6_ = (undefined6)uVar6;
              uRam00000001803049f8._0_7_ = CONCAT16(uVar14 != 1,(undefined6)uRam00000001803049f8);
              _DAT_1803049e0 = 3;
              _DAT_180304a00 = fVar17 + _DAT_180304a00;
              _DAT_180304a08 = uVar11;
              return;
            }
            bVar9 = uRam00000001803049f8._4_1_ + 1;
            uRam00000001803049f8._0_5_ = CONCAT14(bVar9,(uint)uRam00000001803049f8);
          } while (bVar9 < bVar1);
        }
        uVar14 = uVar14 + 1;
        uRam00000001803049e4 = 0;
        uRam00000001803049e8 = 0;
        uRam00000001803049ec = 0;
        _DAT_1803049f0 = 0;
        uRam00000001803049f4 = 0;
        uRam00000001803049f8 = 0;
        _DAT_1803049e0 = uVar14;
      }
      goto LAB_1800471d9;
    case 2:
      return;
    case 3:
      uVar14 = uRam00000001803049f4 & 0xff;
      if (_DAT_1803049f0 == 2) {
        in_stack_ffffffffffffff80 = 0;
        uStack_7c = 0;
      }
      else if (_DAT_1803049f0 == 1) {
        uStack_7c = 2;
        in_stack_ffffffffffffff80 = uVar14;
      }
      else if (_DAT_1803049f0 == 0) {
        uStack_7c = 1;
        in_stack_ffffffffffffff80 = 0;
      }
      FUN_180025be0(*puVar2,lVar10,uRam00000001803049f8._5_1_,in_stack_ffffffffffffff80,uStack_7c,
                    in_stack_ffffffffffffff80);
      uVar12 = CONCAT44(uRam00000001803049ec,uRam00000001803049e8) |
               (longlong)(1 << (uRam00000001803049f8._4_1_ & 0x1f));
      uRam00000001803049e8 = (undefined4)uVar12;
      uRam00000001803049ec = (undefined4)(uVar12 >> 0x20);
      if (uRam00000001803049f8._6_1_ == '\x01') {
        uRam00000001803049f8._0_5_ =
             CONCAT14(uRam00000001803049f8._4_1_ + 1,(uint)uRam00000001803049f8);
      }
      if (iVar4 == 2) {
        uVar11 = FUN_18002aad0(uVar14);
        fVar17 = fRam00000001802f525c / fRam00000001802f5260;
        fVar15 = (float)FUN_180009ee0(uVar11,_DAT_180304a08);
        if (cRam00000001802f5280 == '\x01') {
          fVar18 = fVar15 * _UNK_180155598;
          if (fVar15 * _UNK_180155598 <= _DAT_18015559c) {
            fVar18 = _DAT_18015559c;
          }
          fVar17 = fVar17 * fVar18;
        }
        if (DAT_1802f5228 == '\x01') {
          uVar13 = FUN_18000a050(_DAT_18015559c,_UNK_1801555a0);
          fVar15 = (float)FUN_18000a3e0(uVar13);
          fVar17 = fVar17 * fVar15;
        }
        uRam00000001803049f8._0_6_ = CONCAT15((char)uVar5,(undefined5)uRam00000001803049f8);
        _DAT_1803049e0 = 4;
        _DAT_180304a00 = fVar17 + _DAT_180304a00;
        _DAT_180304a08 = uVar11;
        return;
      }
      break;
    case 4:
      FUN_180025be0(*puVar2,lVar10,uRam00000001803049f8._5_1_,0,0);
      uVar7 = DAT_180304a08_4;
      fVar17 = _DAT_180304a08 + _UNK_180155594;
      fVar18 = fRam00000001802f525c / fRam00000001802f5260;
      fVar15 = (float)FUN_180009ee0(CONCAT44(DAT_180304a08_4,fVar17),_DAT_180304a08);
      if (cRam00000001802f5280 == '\x01') {
        fVar16 = fVar15 * _UNK_180155598;
        if (fVar15 * _UNK_180155598 <= _DAT_18015559c) {
          fVar16 = _DAT_18015559c;
        }
        fVar18 = fVar18 * fVar16;
      }
      if (DAT_1802f5228 == '\x01') {
        uVar11 = FUN_18000a050(_DAT_18015559c,_UNK_1801555a0);
        fVar15 = (float)FUN_18000a3e0(uVar11);
        fVar18 = fVar18 * fVar15;
      }
      _DAT_180304a08 = CONCAT44(uVar7,fVar17);
      _DAT_1803049e0 = 5;
      _DAT_180304a00 = fVar18 + _DAT_180304a00;
      return;
    case 5:
      FUN_180025be0(*puVar2,lVar10,0xfffffc19,0,0);
    }
    uVar14 = (uint)uRam00000001803049f8;
    _DAT_1803049e0 = (uint)uRam00000001803049f8;
  } while( true );
}

// UI RVA 0x47560; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x47560; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180047560(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180155df9);
  FUN_18000cf30(param_2,param_1,0x1802f4e50);
  FUN_18000cf30(param_2,param_1,0x1802f5230);
  FUN_18000cef0(param_2,param_1,0x1802f5268);
  FUN_18000cef0(param_2,param_1,0x1802f5210);
  FUN_180013e90(param_1,param_2,&UNK_180155dfe);
  FUN_18000cef0(param_2,param_1,0x1802f4e88);
  FUN_180013e90(param_1,param_2,&UNK_180155e0a);
  FUN_18000cef0(param_2,param_1,0x1802f4ea8);
  if (DAT_1802f4ec0 != '\x01') {
    return;
  }
  FUN_18000cef0(param_2,param_1,0x1802f51f0);
  FUN_18000d040(param_2,param_1,0x1802f4fb0);
  FUN_18000d040(param_2,param_1,0x1802f4ff0);
  FUN_18000d040(param_2,param_1,0x1802f5030);
  FUN_18000d040(param_2,param_1,0x1802f5070);
  FUN_18000d040(param_2,param_1,0x1802f50b0);
  FUN_18000d040(param_2,param_1,0x1802f50f0);
  FUN_18000d040(param_2,param_1,0x1802f5130);
  FUN_18000d040(param_2,param_1,0x1802f5170);
  cVar1 = FUN_180014d00(param_1,param_2,uRam00000001802f51c8,0x1802f51b0,uRam00000001802f51d0,
                        uRam00000001802f51d8,0x1802f51e0,uRam00000001802f51e8);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x476e0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x476e0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_1800476e0(undefined8 param_1)

{
  undefined2 uStack_1a;
  
  FUN_18000c450(param_1,&UNK_180155e16,0x1802f4e50);
  FUN_18000c450(param_1,&UNK_180155e27,0x1802f5230);
  FUN_18000c3b0(param_1,&UNK_180155e2d,0x1802f5268);
  FUN_18000c3b0(param_1,&UNK_180155e39,0x1802f5210);
  FUN_18000c3b0(param_1,&UNK_180155e43,0x1802f4e88);
  FUN_18000c3b0(param_1,&UNK_180155e4f,0x1802f4ea8);
  FUN_18000c3b0(param_1,&UNK_180155e5b,0x1802f51f0);
  uStack_1a = 0x31;
  FUN_18000c6f0(param_1,&uStack_1a,0x1802f4fb0);
  uStack_1a = 0x32;
  FUN_18000c6f0(param_1,&uStack_1a,0x1802f4ff0);
  uStack_1a = 0x33;
  FUN_18000c6f0(param_1,&uStack_1a,0x1802f5030);
  uStack_1a = 0x34;
  FUN_18000c6f0(param_1,&uStack_1a,0x1802f5070);
  uStack_1a = 0x35;
  FUN_18000c6f0(param_1,&uStack_1a,0x1802f50b0);
  uStack_1a = 0x36;
  FUN_18000c6f0(param_1,&uStack_1a,0x1802f50f0);
  uStack_1a = 0x37;
  FUN_18000c6f0(param_1,&uStack_1a,0x1802f5130);
  uStack_1a = 0x38;
  FUN_18000c6f0(param_1,&uStack_1a,0x1802f5170);
  uStack_1a = 0x39;
  FUN_18000c6f0(param_1,&uStack_1a,0x1802f51b0);
  return;
}

// CANDIDATE_LOCAL RVA 0x47870; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x47870; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


bool FUN_180047870(longlong *param_1,longlong param_2)

{
  byte bVar1;
  longlong *plVar2;
  uint uVar3;
  uint uVar4;
  undefined8 uVar5;
  longlong lVar6;
  undefined8 uVar7;
  uint uVar8;
  uint uVar9;
  
  bVar1 = *(byte *)(param_2 + 0x1c);
  uVar5 = FUN_180023f40(*param_1,param_1[5]);
  lVar6 = FUN_180026140(*param_1,uVar5,0x27 - (uint)bVar1);
  uVar5 = FUN_180025ab0(*param_1,uVar5);
  plVar2 = *(longlong **)(*param_1 + 8);
  uVar3 = FUN_180047cf0(param_1,lVar6,(uint)bVar1);
  uVar9 = 0;
  uVar8 = 0xffffffff;
  do {
    uVar7 = (**(code **)(*plVar2 + 0x568))(plVar2,uVar5,uVar9);
    uVar4 = FUN_180047cf0(param_1,uVar7,bVar1);
    if (uVar3 < uVar4) {
      uVar3 = uVar4;
      uVar8 = uVar9;
    }
    uVar9 = uVar9 + 1;
  } while (uVar9 != 0x24);
  if (uVar8 != 0xffffffff) {
    if (lVar6 == 0) {
      uVar3 = uVar8 + 0x24 & 0xff;
      if (8 < (int)uVar8) {
        uVar3 = uVar8;
      }
      *(undefined8 *)(param_2 + 0x10) = 0;
      *(char *)(param_2 + 0x1d) = (char)uVar3;
    }
    else if ((int)uVar8 < 9) {
      *(undefined4 *)(param_2 + 0x10) = 1;
      *(char *)(param_2 + 0x14) = (char)uVar8;
      *(undefined2 *)(param_2 + 0x15) = 0;
      *(undefined1 *)(param_2 + 0x17) = 0;
      *(char *)(param_2 + 0x1d) = *(char *)(param_2 + 0x1c) + '\x05';
    }
    else {
      *(undefined4 *)(param_2 + 0x10) = 2;
      *(char *)(param_2 + 0x14) = *(char *)(param_2 + 0x1c) + '\x05';
      *(undefined2 *)(param_2 + 0x15) = 0;
      *(undefined1 *)(param_2 + 0x17) = 0;
      *(char *)(param_2 + 0x1d) = (char)uVar8;
    }
  }
  return uVar8 != 0xffffffff;
}

// CANDIDATE_LOCAL RVA 0x479c0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x479c0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


undefined8 FUN_1800479c0(longlong *param_1,longlong param_2)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  longlong *plVar4;
  uint uVar5;
  char cVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  undefined8 uVar12;
  longlong lVar13;
  longlong lVar14;
  longlong lVar15;
  longlong lVar16;
  byte bVar17;
  ulonglong uVar18;
  ulonglong uVar19;
  ulonglong uVar20;
  bool bVar21;
  ulonglong uStack_78;
  ulonglong uStack_70;
  int iStack_68;
  ulonglong uStack_50;
  int iStack_48;
  uint uStack_44;
  
  bVar2 = *(byte *)(param_2 + 0x1c);
  uVar18 = (ulonglong)bVar2;
  iVar3 = *(int *)((ulonglong)bVar2 * 0x40 + 0x1802f4fe0);
  uVar12 = 0;
  if (iVar3 != 0) {
    uVar12 = FUN_180023f40(*param_1,param_1[5]);
    uVar12 = FUN_180025ab0(*param_1,uVar12);
    plVar4 = *(longlong **)(*param_1 + 8);
    lVar13 = (**(code **)(*plVar4 + 0x568))(plVar4,uVar12,bVar2);
    if (lVar13 == 0) {
      iStack_68 = 0;
      uStack_70 = 0;
      iStack_48 = 0;
      uStack_50 = 0;
    }
    else {
      uStack_50 = FUN_180025d70(*param_1,lVar13);
      iStack_48 = FUN_180025e10(*param_1,lVar13);
      lVar14 = FUN_180025d10(*param_1,lVar13);
      if (lVar14 == 0) {
        uStack_70 = 0;
      }
      else {
        uVar7 = FUN_180025c50(*param_1,lVar14);
        iVar8 = FUN_180025dc0(*param_1,lVar13);
        uStack_70 = (ulonglong)uVar7 << 0x20 | (longlong)iVar8;
      }
      iStack_68 = FUN_180047f90(param_1,lVar13,iVar3);
    }
    uVar7 = 9;
    do {
      lVar14 = (**(code **)(*plVar4 + 0x568))(plVar4,uVar12,uVar7);
      uStack_44 = 0;
      if (lVar14 == 0) break;
      bVar21 = uVar7 != 0x23;
      uVar7 = uVar7 + 1;
      uStack_44 = uVar7;
    } while (bVar21);
    uVar20 = 0;
    uVar19 = uStack_50 & 0xffffffff;
    if ((int)uStack_50 < 1) {
      uVar19 = uVar20;
    }
    iVar8 = (int)uVar19;
    uVar7 = iVar8 * iStack_68;
    uVar19 = uVar18;
    uStack_78 = uVar18;
    do {
      if ((uVar18 != uVar20) &&
         (uVar19 = *(ulonglong *)(param_2 + 8), (uVar19 >> (uVar20 & 0x3f) & 1) == 0)) {
        lVar15 = (**(code **)(*plVar4 + 0x568))(plVar4,uVar12,uVar20 & 0xffffffff);
        if (lVar15 == 0) {
          uVar19 = 0;
        }
        else {
          iVar9 = FUN_180025d70(*param_1,lVar15);
          lVar16 = FUN_180025d10(*param_1,lVar15);
          if (lVar16 == 0) {
            uVar19 = 0;
          }
          else {
            uVar10 = FUN_180025c50(*param_1,lVar16);
            iVar11 = FUN_180025dc0(*param_1,lVar15);
            uVar19 = (ulonglong)uVar10 << 0x20 | (longlong)iVar11;
          }
          uVar10 = 0;
          if ((((iVar8 < iStack_48) && (iVar9 < iStack_48)) && (uVar19 == uStack_70)) &&
             (cVar6 = FUN_180025e40(*param_1,lVar13,lVar15), uVar10 = 0, cVar6 != '\0')) {
            iVar11 = iVar9 + iVar8;
            if (iStack_48 <= iVar9 + iVar8) {
              iVar11 = iStack_48;
            }
            uVar10 = iVar11 * iStack_68;
          }
          iVar11 = FUN_180047f90(param_1,lVar15,iVar3);
          uVar1 = iVar11 * iVar9 - 1;
          uVar5 = iVar11 * iVar9;
          if (uVar1 < uVar10) {
            uVar5 = uVar10;
          }
          uVar19 = (ulonglong)uVar5;
          if (uVar7 < uVar5) {
            bVar21 = uVar1 < uVar10;
            if ((8 < uVar20 || lVar14 == 0) || !bVar21) {
              uStack_78 = uVar20;
              uVar7 = uVar5;
            }
            uStack_78 = uStack_78 & 0xffffffff;
            uVar19 = (ulonglong)(uStack_44 & 0xff);
            if ((8 < uVar20 || lVar14 == 0) || !bVar21) {
              uVar19 = (ulonglong)bVar21;
            }
            uStack_44 = (uint)uVar19;
          }
        }
      }
      uVar20 = uVar20 + 1;
    } while (uVar20 != 0x24);
    uVar10 = (uint)uStack_78;
    uVar12 = CONCAT71((int7)(uVar19 >> 8),uVar10 != bVar2);
    if (uVar10 == bVar2) {
      if (uVar7 == 0) {
        return 0;
      }
    }
    else {
      *(undefined1 *)(param_2 + 0x17) = 0;
      *(undefined2 *)(param_2 + 0x15) = 0;
      bVar17 = 0;
      if ((uStack_44 & 1) == 0) {
        bVar17 = bVar2;
      }
      *(uint *)(param_2 + 0x10) = (byte)~(byte)uStack_44 & 1;
      *(byte *)(param_2 + 0x14) = bVar17;
      cVar6 = (char)uStack_78 + '$';
      if (8 < (int)uVar10) {
        cVar6 = (char)uStack_78;
      }
      *(char *)(param_2 + 0x1d) = cVar6;
    }
    *(ulonglong *)(param_2 + 8) = *(ulonglong *)(param_2 + 8) | (longlong)(1 << (bVar2 & 0x1f));
  }
  return uVar12;
}

// CANDIDATE_LOCAL RVA 0x47cf0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x47cf0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong FUN_180047cf0(longlong *param_1,longlong param_2,uint param_3)

{
  byte bVar1;
  longlong *plVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  float fVar7;
  short sVar8;
  int iVar9;
  int iVar10;
  longlong lVar11;
  longlong lVar12;
  longlong lVar13;
  undefined8 uVar14;
  uint uVar15;
  ulonglong uVar16;
  int iVar17;
  float fVar18;
  float fVar19;
  
  uVar16 = 0;
  if (param_2 != 0) {
    lVar11 = FUN_180025d10(*param_1);
    if (lVar11 != 0) {
      iVar9 = FUN_180025c50(*param_1,lVar11);
      uVar15 = iVar9 - 0x12a;
      if ((uVar15 < 0x14) &&
         (uVar16 = 0, iVar9 + *(int *)(&UNK_180155e70 + (ulonglong)uVar15 * 4) == param_3)) {
        lVar11 = *(longlong *)(&UNK_180155ec0 + (ulonglong)uVar15 * 8);
        lVar12 = FUN_180025de0(*param_1,param_2);
        bVar1 = (&UNK_180155b80)[(ulonglong)param_3 + lVar11 * 4];
        dVar3 = 0.0;
        if (lVar12 != 0) {
          plVar2 = *(longlong **)(*param_1 + 8);
          lVar11 = (**(code **)(*plVar2 + 0x538))(plVar2,&UNK_180155b94);
          dVar3 = 0.0;
          if (lVar11 != 0) {
            lVar13 = (**(code **)(*plVar2 + 0x538))(plVar2,&UNK_180155b97);
            dVar3 = 0.0;
            if (lVar13 != 0) {
              iVar9 = FUN_180027f10(*param_1,lVar12);
              fVar7 = _DAT_1801555d8;
              dVar6 = _DAT_1801555d0;
              dVar5 = _DAT_1801555c8;
              dVar4 = _DAT_1801555c0;
              dVar3 = 0.0;
              if (0 < iVar9) {
                iVar17 = 0;
                fVar19 = 0.0;
                fVar18 = 0.0;
                do {
                  uVar14 = FUN_180027f40(*param_1,lVar12,iVar17);
                  uVar15 = FUN_180027f70(*param_1,uVar14,lVar11);
                  sVar8 = FUN_180027f70(*param_1,uVar14,lVar13);
                  if (-1 < sVar8) {
                    iVar10 = (int)sVar8;
                    if ((uVar15 & 0xffff) - 1 < 4) {
                      fVar18 = (float)((double)iVar10 * dVar4 + (double)fVar18);
                    }
                    else if ((uVar15 & 0xffff) == 0) {
                      uVar15 = (uint)(longlong)(((double)(iVar10 * iVar10 + 6) * dVar5) / dVar6);
                      if (0x18 < uVar15) {
                        uVar15 = 0x19;
                      }
                      fVar19 = (float)(int)((uVar15 >> 1) + (uVar15 + 1 & 0x3e)) * fVar7;
                    }
                  }
                  iVar17 = iVar17 + 1;
                } while (iVar9 != iVar17);
                dVar3 = (double)(fVar18 + fVar19);
              }
            }
          }
        }
        uVar16 = (ulonglong)
                 ((float)(_DAT_1801555e8 -
                         (_DAT_1801555e8 - dVar3 * _DAT_1801555e0) *
                         (_DAT_1801555e8 - (double)bVar1 * _DAT_1801555e0)) * _DAT_1801555f0);
      }
    }
  }
  return uVar16 & 0xffffffff;
}

// CANDIDATE_LOCAL RVA 0x47f90; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x47f90; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


ulonglong FUN_180047f90(undefined8 *param_1,undefined8 param_2,int param_3)

{
  undefined1 uVar1;
  ushort uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  longlong lVar5;
  ulonglong uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  
  lVar5 = FUN_180025d10(*param_1);
  uVar6 = 0;
  if (lVar5 != 0) {
    uVar3 = FUN_180025c50(*param_1);
    uVar4 = FUN_180025dc0(*param_1,param_2);
    uVar7 = FUN_180025de0(*param_1,param_2);
    uVar1 = FUN_180025e80(*param_1,param_2);
    uVar2 = FUN_180048080(param_1,param_3,uVar3,uVar4,uVar7,uVar1);
    uVar6 = (ulonglong)uVar2;
    if (DAT_1802f5208 == '\x01') {
      if (uVar2 == 0) {
        if (param_3 == 0x16) {
          uVar8 = 0x19;
        }
        else if (param_3 == 0x11) {
          uVar8 = 7;
        }
        else {
          if (param_3 != 7) {
            return 0;
          }
          uVar8 = 0x11;
        }
        uVar2 = FUN_180048080(param_1,uVar8,uVar3,uVar4,uVar7,uVar1);
        uVar6 = (ulonglong)uVar2;
      }
      else {
        uVar6 = (ulonglong)uVar2 << 0x10;
      }
    }
  }
  return uVar6;
}

// CANDIDATE_LOCAL RVA 0x48080; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x48080; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


ulonglong FUN_180048080(undefined8 param_1,int param_2,int param_3,uint param_4,undefined8 param_5,
                       byte param_6)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  ulonglong uVar6;
  short sVar7;
  ushort uVar8;
  undefined *puVar9;
  bool bVar10;
  bool bVar11;
  
  if (0x19 < param_2 - 1U) {
    return 0;
  }
  switch(param_2) {
  default:
    uVar5 = FUN_180048360(param_3);
    if (param_2 != (int)uVar5) {
      return 0;
    }
    iVar3 = (int)((ulonglong)uVar5 >> 0x20) * 100;
    puVar9 = &UNK_180155d70;
    goto code_r0x00018004833e;
  case 2:
    if (0xa1 < param_3 - 1U) {
      return 0;
    }
    uVar6 = CONCAT62((int6)((ulonglong)
                            (&UNK_1801555f4 +
                            *(int *)(&UNK_1801555f4 + (ulonglong)(param_2 - 1U) * 4)) >> 0x10),1);
    switch(param_3) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 0x11:
    case 0x12:
    case 0x14:
    case 0x18:
    case 0x23:
    case 0x2d:
    case 0x31:
    case 0x4e:
    case 0x57:
    case 0x5f:
    case 0x62:
    case 0x79:
    case 0x7d:
    case 0x85:
    case 0x9b:
    case 0x9f:
    case 0xa2:
      goto LAB_180048348;
    default:
      return 0;
    }
  case 3:
    if (param_3 != 0x105) {
      return 0;
    }
    iVar3 = FUN_1800484d0(param_1,param_5,&UNK_180155d30);
    return (ulonglong)(iVar3 + 1);
  case 4:
    bVar10 = param_3 == 0x36;
    break;
  case 5:
    uVar2 = 0;
    if (param_3 == 0x170) {
      uVar2 = 2 - param_6;
    }
    return (ulonglong)uVar2;
  case 6:
    bVar10 = param_3 == 0x181;
    break;
  case 7:
    bVar10 = param_3 == 0x15a;
    break;
  case 8:
    bVar10 = param_3 == 0x103;
    break;
  case 9:
    if (param_3 == 0x142) {
      return (ulonglong)((param_4 == 1) + 1);
    }
    return 0;
  case 10:
  case 0xb:
  case 0x13:
  case 0x15:
    if (param_3 != 0x175) {
      return 0;
    }
    uVar6 = 0;
    switch(param_4 & 0xf) {
    case 1:
      sVar7 = 1;
      goto joined_r0x0001800482cd;
    case 2:
      sVar7 = 1;
      if (param_2 != 0x13) {
        return 0;
      }
      break;
    default:
      goto LAB_180048348;
    case 5:
      sVar7 = 2;
joined_r0x0001800482cd:
      if (param_2 != 10) {
        return 0;
      }
      break;
    case 9:
      sVar7 = 1;
      if (param_2 != 0x15) {
        return 0;
      }
      break;
    case 0xb:
      sVar7 = 1;
      if (param_2 != 0xb) {
        return 0;
      }
    }
    return (ulonglong)
           (ushort)(((ushort)(param_4 >> 6) & 1) + sVar7 + (ushort)((param_4 >> 5 & 1) != 0));
  case 0xc:
    bVar10 = param_3 == 0x41;
    break;
  case 0xd:
    bVar10 = param_3 == 0x147;
    break;
  case 0x11:
    bVar10 = param_3 == 0x14c;
    bVar11 = param_3 == 0x158;
    goto code_r0x0001800482a8;
  case 0x12:
    bVar10 = param_3 == 0x19d;
    bVar11 = param_3 == 0x11a;
code_r0x0001800482a8:
    return (ulonglong)(byte)(bVar11 | bVar10);
  case 0x14:
    bVar10 = param_3 == 0x118;
    break;
  case 0x16:
    uVar6 = FUN_180048360(param_3);
    if ((int)uVar6 != 0x16) {
      return 0;
    }
    bVar1 = (&UNK_180155d1e)[uVar6 >> 0x20];
    iVar3 = FUN_1800484d0(param_1,param_5,&UNK_180155ce0);
    return (ulonglong)(iVar3 + (uint)bVar1 * 0x28 + 0xa0);
  case 0x17:
    bVar10 = param_3 == 0x2e;
    break;
  case 0x18:
    bVar10 = param_3 == 0x146;
    break;
  case 0x19:
    uVar6 = FUN_180048360(param_3);
    switch((int)uVar6) {
    case 1:
      uVar8 = 3;
      break;
    default:
      uVar8 = 0;
      break;
    case 0xe:
      uVar8 = 2;
      break;
    case 0x10:
      uVar8 = 1;
      break;
    case 0x16:
      uVar8 = 4;
    }
    iVar3 = ((uint)uVar8 + (uint)(byte)(&UNK_180155d1e)[uVar6 >> 0x20]) * 0x28;
    puVar9 = &UNK_180155ce0;
code_r0x00018004833e:
    iVar4 = FUN_1800484d0(param_1,param_5,puVar9);
    return (ulonglong)(uint)(iVar4 + iVar3);
  case 0x1a:
    bVar10 = param_3 == 0x23;
  }
  uVar6 = (ulonglong)bVar10;
LAB_180048348:
  return uVar6;
}

// CANDIDATE_LOCAL RVA 0x48360; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x48360; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


ulonglong FUN_180048360(undefined4 param_1)

{
  ulonglong uVar1;
  ulonglong uVar2;
  
  uVar1 = 1;
  uVar2 = 0x100000000;
  switch(param_1) {
  case 0x100:
    uVar1 = 0x10;
    uVar2 = 0x300000000;
    break;
  case 0x101:
    uVar1 = 0xe;
    uVar2 = 0x300000000;
    break;
  case 0x102:
    uVar2 = 0x300000000;
    break;
  default:
    uVar1 = 0;
    uVar2 = 0;
    break;
  case 0x10b:
    uVar1 = 0x16;
    uVar2 = 0x300000000;
    break;
  case 0x10c:
    uVar1 = 0x16;
    break;
  case 0x10d:
    uVar1 = 0x10;
    break;
  case 0x10e:
    uVar1 = 0xe;
    break;
  case 0x10f:
    break;
  case 0x110:
    uVar1 = 0x16;
    uVar2 = 0x200000000;
    break;
  case 0x111:
    uVar1 = 0x10;
    uVar2 = 0x200000000;
    break;
  case 0x112:
    uVar1 = 0xe;
    uVar2 = 0x200000000;
    break;
  case 0x113:
    uVar2 = 0x200000000;
    break;
  case 0x114:
    uVar1 = 0x16;
    uVar2 = 0x500000000;
    break;
  case 0x115:
    uVar1 = 0x10;
    uVar2 = 0x500000000;
    break;
  case 0x116:
    uVar1 = 0xe;
  case 0x117:
    uVar2 = 0x500000000;
    break;
  case 0x11b:
    uVar1 = 0x16;
    uVar2 = 0x400000000;
    break;
  case 0x11c:
    uVar1 = 0x10;
    uVar2 = 0x400000000;
    break;
  case 0x11d:
    uVar1 = 0xe;
    uVar2 = 0x400000000;
    break;
  case 0x11e:
    uVar2 = 0x400000000;
    break;
  case 0x167:
    uVar1 = 0xf;
  }
  return uVar1 | uVar2;
}

// CANDIDATE_LOCAL RVA 0x484d0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x484d0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


int FUN_1800484d0(longlong *param_1,longlong param_2,longlong param_3)

{
  byte bVar1;
  longlong *plVar2;
  int iVar3;
  ushort uVar4;
  int iVar5;
  int iVar6;
  longlong lVar7;
  longlong lVar8;
  undefined8 uVar9;
  int iVar10;
  int iVar11;
  
  if (param_2 != 0) {
    plVar2 = *(longlong **)(*param_1 + 8);
    lVar7 = (**(code **)(*plVar2 + 0x538))(plVar2,&UNK_180155b94);
    if (((lVar7 != 0) && (lVar8 = (**(code **)(*plVar2 + 0x538))(plVar2,&UNK_180155b97), lVar8 != 0)
        ) && (iVar5 = FUN_180027f10(*param_1,param_2), 0 < iVar5)) {
      iVar10 = 0;
      iVar11 = 0;
      do {
        uVar9 = FUN_180027f40(*param_1,param_2,iVar11);
        uVar4 = FUN_180027f70(*param_1,uVar9,lVar7);
        if ((uVar4 < 0x3f) && (bVar1 = *(byte *)(param_3 + (ulonglong)uVar4), bVar1 != 0)) {
          iVar6 = FUN_180027f70(*param_1,uVar9,lVar8);
          iVar3 = (uint)bVar1 * iVar6;
          if ((short)iVar6 < 0) {
            iVar3 = 0;
          }
          iVar10 = iVar10 + iVar3;
        }
        iVar11 = iVar11 + 1;
      } while (iVar5 != iVar11);
      return iVar10;
    }
  }
  return 0;
}

