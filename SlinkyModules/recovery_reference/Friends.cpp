// Recovered decompiler view: Friends
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x3b3c0, 0x3c210); proximity does not prove ownership.

// CALLBACK RVA 0x3b3c0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/friends/friends.c
// Differential report: analysis/module_behavior_recovery/friends/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3b3c0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003b3c0(longlong param_1)

{
  longlong *plVar1;
  char cVar2;
  int iVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  longlong lVar8;
  int iVar9;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  
  plVar1 = *(longlong **)(param_1 + 8);
  if (plVar1[5] != 0) {
    iVar9 = 0;
    uVar4 = func_0x00018013d0d0(0);
    uVar5 = FUN_180024600(*plVar1,plVar1[4]);
    iVar3 = FUN_180024e50(*plVar1,uVar5);
    if (0 < iVar3) {
      do {
        uVar6 = FUN_180024e80(*plVar1,uVar5,iVar9);
        cVar2 = (**(code **)(**(longlong **)(*plVar1 + 8) + 0xc0))
                          (*(longlong **)(*plVar1 + 8),plVar1[5],uVar6);
        if (cVar2 == '\0') {
          uVar7 = FUN_180023740(*plVar1,uVar6);
          uStack_78 = FUN_180027dc0(*plVar1,uVar7);
          uStack_70 = FUN_180027d90(*plVar1,uVar7);
          uStack_68 = 0;
          uStack_60 = 0;
          lVar8 = FUN_18000df00(_DAT_1802fc8c0,0x20,0x1802fc8c8,&uStack_78,FUN_18003b380);
          if (lVar8 == 0) {
            FUN_18002ad80(*plVar1,uVar6,4);
          }
          else {
            FUN_18002ad20(*plVar1,uVar6,4);
            *(undefined8 *)(lVar8 + 0x10) = uVar4;
          }
        }
        iVar9 = iVar9 + 1;
        iVar3 = FUN_180024e50(*plVar1,uVar5);
      } while (iVar9 < iVar3);
    }
  }
  return;
}

// CALLBACK RVA 0x3b510; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/friends/friends.c
// Differential report: analysis/module_behavior_recovery/friends/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3b510; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003b510(longlong param_1)

{
  longlong *plVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  
  if ((*(longlong *)(param_1 + 0x10) == 0x1802f0038) && (*(char *)(param_1 + 0x18) == '\0')) {
    plVar1 = *(longlong **)(param_1 + 8);
    if (plVar1[4] != 0) {
      uVar5 = FUN_180024600(*plVar1);
      iVar3 = FUN_180024e50(*plVar1,uVar5);
      if (0 < iVar3) {
        iVar3 = 0;
        do {
          uVar6 = FUN_180024e80(*plVar1,uVar5,iVar3);
          cVar2 = (**(code **)(**(longlong **)(*plVar1 + 8) + 0xc0))
                            (*(longlong **)(*plVar1 + 8),plVar1[5],uVar6);
          if (cVar2 == '\0') {
            FUN_18002ad80(*plVar1,uVar6,4);
          }
          iVar3 = iVar3 + 1;
          iVar4 = FUN_180024e50(*plVar1,uVar5);
        } while (iVar3 < iVar4);
      }
    }
  }
  return;
}

// CALLBACK RVA 0x3b5d0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/friends/friends.c
// Differential report: analysis/module_behavior_recovery/friends/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3b5d0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003b5d0(void)

{
  func_0x00018013cf70(_DAT_1802fc8c0);
  _DAT_1802fc8c0 = 0;
  uRam00000001802fc8c8 = 0;
  return;
}

// UI RVA 0x3b600; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3b600; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003b600(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180153673);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802f0258,0x1802f0248,&DAT_1802f0260);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x3b640; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3b640; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003b640(undefined8 *param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  code *pcVar3;
  int iVar4;
  longlong lVar5;
  longlong lVar6;
  ulonglong uVar7;
  undefined8 uVar8;
  longlong lVar9;
  float *pfVar10;
  longlong lVar11;
  undefined8 uVar12;
  ulonglong uVar13;
  longlong *plVar14;
  bool bVar15;
  undefined8 uStack_7c;
  undefined4 uStack_74;
  undefined8 uStack_70;
  undefined4 uStack_68;
  longlong lStack_60;
  
  FUN_18000c3b0(param_1,&UNK_180153678,0x1802f0248);
  if (*(char *)((longlong)param_1 + 0xc) == '\0') {
    iVar4 = *(int *)(param_1 + 1);
    if (iVar4 == 0) {
      (*pcRam00000001802f02b8)(uRam00000001802f0288);
      lVar5 = FUN_18004e4d0(*param_1,&UNK_180153689);
      iVar4 = FUN_180050920(lVar5);
      uVar8 = _DAT_18013ebf0;
      if ((lVar5 != 0 && iVar4 != 0) &&
         (plVar14 = *(longlong **)(lVar5 + 0x10), plVar14 != (longlong *)0x0)) {
        do {
          if (iRam00000001802f0280 == 1) {
            iVar4 = FUN_180050940(plVar14);
            if (iVar4 != 0) {
              lVar5 = FUN_18004e4d0(plVar14,&UNK_18013ec47);
              iVar4 = FUN_18004d110(lVar5);
              if (iVar4 != 0) {
                uVar12 = FUN_18004e4d0(plVar14,&UNK_18013ec4c);
                pcVar3 = pcRam00000001802f02a8;
                uVar2 = uRam00000001802f0288;
                uVar1 = *(undefined8 *)(lVar5 + 0x20);
                uStack_70 = uVar8;
                uStack_68 = 0x3f800000;
                FUN_18000c910(&uStack_7c,uVar12,&uStack_70);
                uStack_68 = uStack_74;
                uStack_70 = uStack_7c;
                (*pcVar3)(uVar2,uVar1,&uStack_70);
              }
            }
          }
          else if ((iRam00000001802f0280 == 0) && (iVar4 = FUN_18004d110(plVar14), iVar4 != 0)) {
            uStack_68 = 0;
            uStack_70 = 0;
            (*pcRam00000001802f02a8)(uRam00000001802f0288,plVar14[4],&uStack_70);
          }
          plVar14 = (longlong *)*plVar14;
        } while (plVar14 != (longlong *)0x0);
      }
    }
    else if (iVar4 == 1) {
      lVar5 = FUN_18004f5d0(*param_1);
      if (lVar5 == 0) {
        *(undefined1 *)((longlong)param_1 + 0xc) = 1;
      }
      else {
        lVar6 = (*pcRam00000001802f0290)(uRam00000001802f0288);
        if (lVar6 != 0) {
          uVar13 = 0;
          lStack_60 = lVar5;
          do {
            if (iRam00000001802f0280 == 1) {
              lVar6 = FUN_18004f590();
              bVar15 = true;
              if (lVar6 != 0) {
                uVar8 = (*pcRam00000001802f0298)(uRam00000001802f0288,uVar13);
                lVar9 = FUN_18004f080(lVar6,&UNK_18013ec47,uVar8);
                if ((lVar9 != 0) &&
                   (lVar9 = FUN_18004f480(lVar6,&UNK_18013ec4c), lVar5 = lStack_60, lVar9 != 0)) {
                  pfVar10 = (float *)(*pcRam00000001802f02a0)(uRam00000001802f0288,uVar13);
                  lVar11 = FUN_18004eeb0(lVar9,&UNK_18013ec41,(double)*pfVar10);
                  lVar5 = lStack_60;
                  if ((lVar11 != 0) &&
                     ((lVar11 = FUN_18004eeb0(lVar9,&UNK_18013ec43,(double)pfVar10[1]),
                      lVar5 = lStack_60, lVar11 != 0 &&
                      (lVar9 = FUN_18004eeb0(lVar9,&UNK_18013ec45,(double)pfVar10[2]),
                      lVar5 = lStack_60, lVar9 != 0)))) goto LAB_18000caa0;
                }
              }
LAB_18000cab1:
              *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | bVar15;
            }
            else if (iRam00000001802f0280 == 0) {
              uVar8 = (*pcRam00000001802f0298)(uRam00000001802f0288,uVar13);
              lVar6 = FUN_18004f1e0(uVar8);
              if (lVar6 == 0) {
                bVar15 = true;
              }
              else {
LAB_18000caa0:
                iVar4 = FUN_18004e560(lVar5,lVar6);
                bVar15 = iVar4 == 0;
              }
              goto LAB_18000cab1;
            }
            uVar13 = uVar13 + 1;
            uVar7 = (*pcRam00000001802f0290)(uRam00000001802f0288);
          } while (uVar13 < uVar7);
        }
      }
    }
    else if (iVar4 == 3) {
                    /* WARNING: Could not recover jumptable at 0x00018000ca67. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*pcRam00000001802f02b8)(uRam00000001802f0288);
      return;
    }
  }
  return;
}

// CANDIDATE_LOCAL RVA 0x3b680; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3b680; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


ulonglong FUN_18003b680(undefined8 *param_1,undefined4 *param_2)

{
  ulonglong uVar1;
  undefined1 auStack_68 [32];
  undefined1 auStack_48 [32];
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  
  uStack_28 = *param_2;
  uStack_24 = param_2[1];
  uStack_20 = param_2[2];
  uStack_1c = param_2[3];
  uVar1 = FUN_18003ba20(uStack_28,&uStack_28,auStack_68,auStack_48);
  if ((char)uVar1 != '\0') {
    uVar1 = uVar1 & 0xffffffff;
    FUN_18000e0b0(&DAT_1802fc8c0,0x20,0x1802fc8c8,auStack_68,FUN_18003b380);
    FUN_1800291f0(*param_1,&UNK_180153590,auStack_48);
  }
  return uVar1;
}

// CANDIDATE_LOCAL RVA 0x3b700; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3b700; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong FUN_18003b700(undefined8 *param_1,undefined4 *param_2)

{
  ulonglong uVar1;
  longlong lVar2;
  undefined1 auStack_68 [32];
  undefined1 auStack_48 [32];
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  
  uStack_28 = *param_2;
  uStack_24 = param_2[1];
  uStack_20 = param_2[2];
  uStack_1c = param_2[3];
  uVar1 = FUN_18003ba20(uStack_28,&uStack_28,auStack_68,auStack_48);
  if ((char)uVar1 != '\0') {
    uVar1 = uVar1 & 0xffffffff;
    lVar2 = FUN_18000df00(_DAT_1802fc8c0,0x20,0x1802fc8c8,auStack_68,FUN_18003b380);
    if (lVar2 != 0) {
      FUN_18000e210(_DAT_1802fc8c0,0x20,0x1802fc8c8,lVar2);
    }
    FUN_1800291f0(*param_1,&UNK_180153603,auStack_48);
  }
  return uVar1;
}

// CANDIDATE_LOCAL RVA 0x3b7a0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3b7a0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_18003b7a0(longlong *param_1,undefined8 *param_2)

{
  double dVar1;
  char cVar2;
  int iVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  int iVar10;
  double dVar11;
  undefined1 auVar12 [16];
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined *puStack_78;
  char cStack_69;
  
  uVar5 = *param_2;
  cStack_69 = *(char *)(param_2 + 2);
  puStack_78 = (undefined *)(ulonglong)_DAT_1802fc8cc;
  if (cStack_69 == '\x01') {
    _DAT_1802fc8cc = 0;
  }
  FUN_180023030(&uStack_e8,*param_1,param_1[5]);
  uVar4 = FUN_180024600(*param_1,param_1[4]);
  iVar3 = FUN_180024e50(*param_1,uVar4);
  iVar10 = 0;
  if (iVar3 < 1) {
    puVar9 = (undefined *)0x0;
  }
  else {
    auVar12._8_4_ = (int)((ulonglong)uVar5 >> 0x20);
    auVar12._0_8_ = uVar5;
    auVar12._12_4_ = _UNK_180153184;
    dVar1 = (auVar12._8_8_ - _UNK_180153198) +
            ((double)CONCAT44(_DAT_180153180,(int)uVar5) - _DAT_180153190);
    puVar9 = (undefined *)0x0;
    do {
      uVar5 = FUN_180024e80(*param_1,uVar4,iVar10);
      cVar2 = (**(code **)(**(longlong **)(*param_1 + 8) + 0xc0))
                        (*(longlong **)(*param_1 + 8),uVar5,param_1[5]);
      if (cVar2 == '\0') {
        cVar2 = FUN_18002ace0(*param_1,uVar5,2);
        if (cVar2 == '\0') {
          FUN_180023030(&uStack_d0,*param_1,uVar5);
          uStack_88 = uStack_d8;
          uStack_98 = uStack_e8;
          uStack_90 = uStack_e0;
          uStack_a8 = uStack_c0;
          uStack_b8 = uStack_d0;
          uStack_b0 = uStack_c8;
          dVar11 = (double)FUN_1800094b0(&uStack_98,&uStack_b8);
          if (dVar11 <= dVar1 * dVar1) {
            uVar5 = FUN_180023740(*param_1,uVar5);
            uStack_98 = FUN_180027dc0(*param_1,uVar5);
            uStack_90 = FUN_180027d90(*param_1,uVar5);
            uStack_88 = 0;
            uStack_80 = 0;
            FUN_18000e0b0(&DAT_1802fc8c0,0x20,0x1802fc8c8,&uStack_98,FUN_18003b380);
            puVar9 = puVar9 + 1;
          }
        }
      }
      iVar10 = iVar10 + 1;
      iVar3 = FUN_180024e50(*param_1,uVar4);
    } while (iVar10 < iVar3);
  }
  puVar8 = &UNK_180153641;
  if (puVar9 == (undefined *)0x1) {
    puVar8 = &UNK_180153640;
  }
  if (cStack_69 == '\0') {
    puVar6 = &UNK_180153643;
    puVar7 = puVar9;
  }
  else {
    puVar6 = &UNK_18015361c;
    puVar7 = puStack_78;
    puVar8 = puVar9;
  }
  FUN_1800291f0(*param_1,puVar6,puVar7,puVar8);
  return 1;
}

// CANDIDATE_LOCAL RVA 0x3b9d0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3b9d0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_18003b9d0(undefined8 *param_1)

{
  undefined *puVar1;
  
  puVar1 = &UNK_180153641;
  if (_DAT_1802fc8cc == 1) {
    puVar1 = &UNK_180153640;
  }
  FUN_1800291f0(*param_1,&UNK_18015365a,_DAT_1802fc8cc,puVar1);
  _DAT_1802fc8cc = 0;
  return 1;
}

// CANDIDATE_LOCAL RVA 0x3ba20; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3ba20; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


undefined8 FUN_18003ba20(longlong *param_1,longlong *param_2,undefined8 *param_3,longlong param_4)

{
  longlong *plVar1;
  longlong lVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  longlong lVar9;
  ulonglong uVar10;
  undefined *puVar11;
  ulonglong uVar12;
  undefined1 auStack_98 [32];
  undefined8 uStack_78;
  longlong lStack_70;
  undefined8 *puStack_68;
  undefined8 uStack_60;
  longlong *plStack_58;
  longlong lStack_50;
  longlong lStack_48;
  
  uVar12 = param_2[1];
  lVar6 = *param_1;
  if (uVar12 < 0x11) {
    lStack_50 = *param_2;
    plVar1 = *(longlong **)(lVar6 + 8);
    puStack_68 = param_3;
    func_0x0001800abbf0(auStack_98,lStack_50,uVar12);
    auStack_98[uVar12] = 0;
    plStack_58 = plVar1;
    lVar6 = (**(code **)(*plVar1 + 0x538))(plVar1,auStack_98);
    if (lVar6 == 0) {
      return 0;
    }
    uVar7 = FUN_180024600(*param_1,param_1[4]);
    iVar4 = FUN_180024e50(*param_1,uVar7);
    if (0 < iVar4) {
      lStack_48 = 0;
      iVar4 = 0;
      uStack_78 = uVar7;
      lStack_70 = param_4;
      do {
        lVar6 = FUN_180024e80(*param_1,uVar7,iVar4);
        cVar3 = (**(code **)(**(longlong **)(*param_1 + 8) + 0xc0))
                          (*(longlong **)(*param_1 + 8),lVar6,param_1[5]);
        if (cVar3 == '\0') {
          uVar8 = FUN_180023830(*param_1,lVar6);
          iVar5 = (**(code **)(*plStack_58 + 0x540))(plStack_58,uVar8);
          if (uVar12 <= (ulonglong)(longlong)iVar5) {
            uStack_60 = uVar8;
            lVar9 = (**(code **)(*plStack_58 + 0x548))(plStack_58,uVar8,0);
            lVar2 = lStack_70;
            if (uVar12 == 0) {
              if (lStack_48 != 0) {
                lVar6 = *param_1;
                uVar12 = 0;
                goto LAB_18003bc8d;
              }
            }
            else {
              uVar10 = 0;
              do {
                if ((char)(((byte)(*(char *)(lStack_50 + uVar10) + 0xbfU) < 0x1a) * ' ' +
                          *(char *)(lStack_50 + uVar10)) !=
                    (char)(((byte)(*(char *)(lVar9 + uVar10) + 0xbfU) < 0x1a) * ' ' +
                          *(char *)(lVar9 + uVar10))) goto LAB_18003bb04;
                uVar10 = uVar10 + 1;
              } while (uVar12 != uVar10);
              if (lStack_48 != 0) {
                lVar6 = *param_1;
                uVar12 = uVar12 & 0xffffffff;
LAB_18003bc8d:
                FUN_1800291f0(lVar6,&UNK_1801535c0,uVar12,lStack_50);
                return 0;
              }
            }
            if (0xf < iVar5) {
              iVar5 = 0x10;
            }
            func_0x0001800abbf0(lStack_70,lVar9,(longlong)iVar5);
            *(undefined1 *)(lVar2 + iVar5) = 0;
            lStack_48 = lVar6;
LAB_18003bb04:
            (**(code **)(*plStack_58 + 0x550))(plStack_58,uStack_60,lVar9);
            uVar7 = uStack_78;
          }
        }
        iVar4 = iVar4 + 1;
        iVar5 = FUN_180024e50(*param_1,uVar7);
      } while (iVar4 < iVar5);
      if (lStack_48 != 0) {
        uVar7 = FUN_180023740(*param_1);
        uVar8 = FUN_180027dc0(*param_1,uVar7);
        uVar7 = FUN_180027d90(*param_1,uVar7);
        *puStack_68 = uVar8;
        puStack_68[1] = uVar7;
        puStack_68[2] = 0;
        puStack_68[3] = 0;
        return 1;
      }
    }
    lVar6 = *param_1;
    puVar11 = &UNK_1801535ee;
  }
  else {
    puVar11 = &UNK_1801535a7;
  }
  FUN_1800291f0(lVar6,puVar11);
  return 0;
}

// CANDIDATE_LOCAL RVA 0x3bca0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3bca0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_18003bca0(void)

{
  return _DAT_1802fc8cc;
}

// CANDIDATE_LOCAL RVA 0x3bcb0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3bcb0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_18003bcb0(undefined8 param_1,undefined8 param_2)

{
  longlong lVar1;
  longlong lVar2;
  
  lVar1 = FUN_18000ddc0(_DAT_1802fc8c0,0x20,0x1802fc8c8,param_2);
  lVar2 = 1;
  do {
    *(undefined *)(lVar2 * 2 + 0x1802fc8ce) = (&UNK_1801536b0)[*(byte *)(lVar1 + -1 + lVar2) >> 4];
    *(undefined *)(lVar2 * 2 + 0x1802fc8cf) = (&UNK_1801536b0)[*(byte *)(lVar1 + -1 + lVar2) & 0xf];
    *(undefined *)(lVar2 * 2 + 0x1802fc8d0) = (&UNK_1801536b0)[*(byte *)(lVar1 + lVar2) >> 4];
    *(undefined *)(lVar2 * 2 + 0x1802fc8d1) = (&UNK_1801536b0)[*(byte *)(lVar1 + lVar2) & 0xf];
    lVar2 = lVar2 + 2;
  } while (lVar2 != 0x11);
  DAT_1802fc8f0 = (&UNK_1801536b0)[*(byte *)(lVar1 + 0x10) >> 4];
  DAT_1802fc8f1 = (&UNK_1801536b0)[*(byte *)(lVar1 + 0x10) & 0xf];
  DAT_1802fc8f2 = (&UNK_1801536b0)[*(byte *)(lVar1 + 0x11) >> 4];
  DAT_1802fc8f3 = (&UNK_1801536b0)[*(byte *)(lVar1 + 0x11) & 0xf];
  DAT_1802fc8f4 = (&UNK_1801536b0)[*(byte *)(lVar1 + 0x12) >> 4];
  DAT_1802fc8f5 = (&UNK_1801536b0)[*(byte *)(lVar1 + 0x12) & 0xf];
  DAT_1802fc8f6 = (&UNK_1801536b0)[*(byte *)(lVar1 + 0x13) >> 4];
  DAT_1802fc8f7 = (&UNK_1801536b0)[*(byte *)(lVar1 + 0x13) & 0xf];
  DAT_1802fc8f8 = (&UNK_1801536b0)[*(byte *)(lVar1 + 0x14) >> 4];
  DAT_1802fc8f9 = (&UNK_1801536b0)[*(byte *)(lVar1 + 0x14) & 0xf];
  DAT_1802fc8fa = (&UNK_1801536b0)[*(byte *)(lVar1 + 0x15) >> 4];
  DAT_1802fc8fb = (&UNK_1801536b0)[*(byte *)(lVar1 + 0x15) & 0xf];
  DAT_1802fc8fc = (&UNK_1801536b0)[*(byte *)(lVar1 + 0x16) >> 4];
  DAT_1802fc8fd = (&UNK_1801536b0)[*(byte *)(lVar1 + 0x16) & 0xf];
  DAT_1802fc8fe = (&UNK_1801536b0)[*(byte *)(lVar1 + 0x17) >> 4];
  DAT_1802fc8ff = (&UNK_1801536b0)[*(byte *)(lVar1 + 0x17) & 0xf];
  DAT_1802fc900 = 0;
  return 0x1802fc8d0;
}

// CANDIDATE_LOCAL RVA 0x3beb0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3beb0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


bool FUN_18003beb0(undefined8 param_1,longlong param_2)

{
  char cVar1;
  undefined8 uVar2;
  ulonglong uVar3;
  longlong lVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte abStack_38 [32];
  
  abStack_38[0x10] = 0;
  abStack_38[0x11] = 0;
  abStack_38[0x12] = 0;
  abStack_38[0x13] = 0;
  abStack_38[0x14] = 0;
  abStack_38[0x15] = 0;
  abStack_38[0x16] = 0;
  abStack_38[0x17] = 0;
  abStack_38[0x18] = 0;
  abStack_38[0x19] = 0;
  abStack_38[0x1a] = 0;
  abStack_38[0x1b] = 0;
  abStack_38[0x1c] = 0;
  abStack_38[0x1d] = 0;
  abStack_38[0x1e] = 0;
  abStack_38[0x1f] = 0;
  abStack_38[0] = 0;
  abStack_38[1] = 0;
  abStack_38[2] = 0;
  abStack_38[3] = 0;
  abStack_38[4] = 0;
  abStack_38[5] = 0;
  abStack_38[6] = 0;
  abStack_38[7] = 0;
  abStack_38[8] = 0;
  abStack_38[9] = 0;
  abStack_38[10] = 0;
  abStack_38[0xb] = 0;
  abStack_38[0xc] = 0;
  abStack_38[0xd] = 0;
  abStack_38[0xe] = 0;
  abStack_38[0xf] = 0;
  uVar3 = func_0x0001800ab840(param_2);
  uVar2 = abStack_38._16_8_;
  if (uVar3 < 0x30) goto LAB_18003c152;
  lVar4 = 0;
  do {
    cVar1 = *(char *)(param_2 + lVar4 * 2);
    bVar6 = cVar1 - 0x30;
    if (9 < bVar6) {
      if (0x19 < (byte)(cVar1 + 0x9fU)) break;
      bVar6 = cVar1 + 0xa9;
    }
    cVar1 = *(char *)(param_2 + 1 + lVar4 * 2);
    bVar7 = cVar1 - 0x30;
    if (9 < bVar7) {
      if (0x19 < (byte)(cVar1 + 0x9fU)) break;
      bVar7 = cVar1 + 0xa9;
    }
    abStack_38[lVar4] = bVar6 << 4 | bVar7;
    lVar4 = lVar4 + 1;
  } while (lVar4 != 0x10);
  cVar1 = *(char *)(param_2 + 0x20);
  bVar6 = cVar1 - 0x30;
  if (bVar6 < 10) {
LAB_18003bf59:
    cVar1 = *(char *)(param_2 + 0x21);
    bVar7 = cVar1 - 0x30;
    if (9 < bVar7) {
      if (0x19 < (byte)(cVar1 + 0x9fU)) goto LAB_18003c12a;
      bVar7 = cVar1 + 0xa9;
    }
    bVar7 = bVar6 << 4 | bVar7;
    abStack_38[0x10] = bVar7;
    cVar1 = *(char *)(param_2 + 0x22);
    bVar6 = cVar1 - 0x30;
    if (9 < bVar6) {
      if (0x19 < (byte)(cVar1 + 0x9fU)) goto LAB_18003c12a;
      bVar6 = cVar1 + 0xa9;
    }
    cVar1 = *(char *)(param_2 + 0x23);
    bVar5 = cVar1 - 0x30;
    if (9 < bVar5) {
      if (0x19 < (byte)(cVar1 + 0x9fU)) goto LAB_18003c12a;
      bVar5 = cVar1 + 0xa9;
    }
    abStack_38._18_6_ = SUB86(uVar2,2);
    abStack_38[0x11] = bVar6 << 4 | bVar5;
    cVar1 = *(char *)(param_2 + 0x24);
    bVar6 = cVar1 - 0x30;
    if (9 < bVar6) {
      if (0x19 < (byte)(cVar1 + 0x9fU)) goto LAB_18003c12a;
      bVar6 = cVar1 + 0xa9;
    }
    cVar1 = *(char *)(param_2 + 0x25);
    bVar7 = cVar1 - 0x30;
    if (9 < bVar7) {
      if (0x19 < (byte)(cVar1 + 0x9fU)) goto LAB_18003c12a;
      bVar7 = cVar1 + 0xa9;
    }
    abStack_38._19_5_ = SUB85(uVar2,3);
    abStack_38[0x12] = bVar6 << 4 | bVar7;
    cVar1 = *(char *)(param_2 + 0x26);
    bVar6 = cVar1 - 0x30;
    if (9 < bVar6) {
      if (0x19 < (byte)(cVar1 + 0x9fU)) goto LAB_18003c12a;
      bVar6 = cVar1 + 0xa9;
    }
    cVar1 = *(char *)(param_2 + 0x27);
    bVar7 = cVar1 - 0x30;
    if (9 < bVar7) {
      if (0x19 < (byte)(cVar1 + 0x9fU)) goto LAB_18003c12a;
      bVar7 = cVar1 + 0xa9;
    }
    abStack_38._20_4_ = SUB84(uVar2,4);
    abStack_38[0x13] = bVar6 << 4 | bVar7;
    cVar1 = *(char *)(param_2 + 0x28);
    bVar6 = cVar1 - 0x30;
    if (9 < bVar6) {
      if (0x19 < (byte)(cVar1 + 0x9fU)) goto LAB_18003c12a;
      bVar6 = cVar1 + 0xa9;
    }
    cVar1 = *(char *)(param_2 + 0x29);
    bVar7 = cVar1 - 0x30;
    if (9 < bVar7) {
      if (0x19 < (byte)(cVar1 + 0x9fU)) goto LAB_18003c12a;
      bVar7 = cVar1 + 0xa9;
    }
    abStack_38._21_3_ = SUB83(uVar2,5);
    abStack_38[0x14] = bVar6 << 4 | bVar7;
    cVar1 = *(char *)(param_2 + 0x2a);
    bVar6 = cVar1 - 0x30;
    if (9 < bVar6) {
      if (0x19 < (byte)(cVar1 + 0x9fU)) goto LAB_18003c12a;
      bVar6 = cVar1 + 0xa9;
    }
    cVar1 = *(char *)(param_2 + 0x2b);
    bVar7 = cVar1 - 0x30;
    if (9 < bVar7) {
      if (0x19 < (byte)(cVar1 + 0x9fU)) goto LAB_18003c12a;
      bVar7 = cVar1 + 0xa9;
    }
    abStack_38._22_2_ = SUB82(uVar2,6);
    abStack_38[0x15] = bVar6 << 4 | bVar7;
    cVar1 = *(char *)(param_2 + 0x2c);
    bVar6 = cVar1 - 0x30;
    if (9 < bVar6) {
      if (0x19 < (byte)(cVar1 + 0x9fU)) goto LAB_18003c12a;
      bVar6 = cVar1 + 0xa9;
    }
    cVar1 = *(char *)(param_2 + 0x2d);
    bVar7 = cVar1 - 0x30;
    if (9 < bVar7) {
      if (0x19 < (byte)(cVar1 + 0x9fU)) goto LAB_18003c12a;
      bVar7 = cVar1 + 0xa9;
    }
    abStack_38[0x17] = SUB81(uVar2,7);
    abStack_38[0x16] = bVar6 << 4 | bVar7;
    cVar1 = *(char *)(param_2 + 0x2e);
    bVar6 = cVar1 - 0x30;
    if (9 < bVar6) {
      if (0x19 < (byte)(cVar1 + 0x9fU)) goto LAB_18003c12a;
      bVar6 = cVar1 + 0xa9;
    }
    cVar1 = *(char *)(param_2 + 0x2f);
    bVar7 = cVar1 - 0x30;
    if (9 < bVar7) {
      if (0x19 < (byte)(cVar1 + 0x9fU)) goto LAB_18003c12a;
      bVar7 = cVar1 + 0xa9;
    }
    abStack_38[0x17] = bVar6 << 4 | bVar7;
  }
  else if ((byte)(cVar1 + 0x9fU) < 0x1a) {
    bVar6 = cVar1 + 0xa9;
    goto LAB_18003bf59;
  }
LAB_18003c12a:
  FUN_18000e0b0(&DAT_1802fc8c0,0x20,0x1802fc8c8,abStack_38,FUN_18003b380);
LAB_18003c152:
  return 0x2f < uVar3;
}

// CANDIDATE_LOCAL RVA 0x3c170; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3c170; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003c170(undefined8 param_1,int param_2)

{
  undefined8 *puVar1;
  longlong lVar2;
  undefined8 *puVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  uint uVar16;
  ulonglong uVar17;
  ulonglong uVar18;
  longlong lVar19;
  undefined8 *puVar20;
  undefined8 *puVar21;
  longlong lVar22;
  ulonglong uVar23;
  ulonglong uVar24;
  
  _DAT_1802fc8cc = _DAT_1802fc8cc + -1;
  uVar16 = _DAT_1802fc8cc - param_2;
  puVar21 = (undefined8 *)((ulonglong)(uint)(param_2 * 0x20) + _DAT_1802fc8c0);
  puVar20 = (undefined8 *)((ulonglong)(uint)((param_2 + 1) * 0x20) + _DAT_1802fc8c0);
  uVar17 = (ulonglong)(uVar16 * 0x20);
  if (uVar17 < 0x10) {
    if (uVar17 < 4) {
      if (uVar17 != 0) {
        uVar18 = (ulonglong)((uVar16 & 0x7ffffff) << 4);
        uVar4 = *(undefined1 *)((longlong)puVar20 + uVar18);
        uVar5 = *(undefined1 *)((longlong)puVar20 + (uVar17 - 1));
        *(undefined1 *)puVar21 = *(undefined1 *)puVar20;
        *(undefined1 *)((longlong)puVar21 + uVar18) = uVar4;
        *(undefined1 *)((longlong)puVar21 + (uVar17 - 1)) = uVar5;
      }
    }
    else {
      uVar6 = *(undefined4 *)puVar20;
      uVar7 = *(undefined4 *)((longlong)puVar20 + (uVar17 - 4));
      uVar8 = *(undefined4 *)((longlong)puVar20 + (uVar17 - 4));
      *(undefined4 *)puVar21 = *(undefined4 *)puVar20;
      *(undefined4 *)puVar21 = uVar6;
      *(undefined4 *)((longlong)puVar21 + (uVar17 - 4)) = uVar7;
      *(undefined4 *)((longlong)puVar21 + (uVar17 - 4)) = uVar8;
    }
  }
  else if (uVar17 < 0x40) {
    uVar18 = (ulonglong)((uVar16 & 1) << 4);
    lVar22 = (uVar17 - 0x10) - uVar18;
    uVar9 = puVar20[1];
    uVar10 = *(undefined8 *)((longlong)puVar20 + uVar18);
    uVar11 = ((undefined8 *)((longlong)puVar20 + uVar18))[1];
    puVar1 = (undefined8 *)((longlong)puVar20 + lVar22);
    uVar12 = *puVar1;
    uVar13 = puVar1[1];
    puVar1 = (undefined8 *)((longlong)puVar20 + (uVar17 - 0x10));
    uVar14 = *puVar1;
    uVar15 = puVar1[1];
    *puVar21 = *puVar20;
    puVar21[1] = uVar9;
    *(undefined8 *)((longlong)puVar21 + uVar18) = uVar10;
    ((undefined8 *)((longlong)puVar21 + uVar18))[1] = uVar11;
    puVar20 = (undefined8 *)((longlong)puVar21 + lVar22);
    *puVar20 = uVar12;
    puVar20[1] = uVar13;
    puVar21 = (undefined8 *)((longlong)puVar21 + (uVar17 - 0x10));
    *puVar21 = uVar14;
    puVar21[1] = uVar15;
  }
  else if (puVar20 < puVar21) {
    puVar1 = (undefined8 *)((longlong)puVar20 + (uVar17 - 0x10));
    uVar9 = *puVar1;
    uVar10 = puVar1[1];
    uVar11 = *puVar20;
    uVar12 = puVar20[1];
    uVar18 = (ulonglong)(uVar17 + (longlong)puVar21) & 0xfffffffffffffff0;
    uVar23 = uVar18 - (longlong)puVar21;
    if (0xf < uVar23) {
      uVar24 = uVar23 >> 4;
      lVar22 = 1;
      if (2 < uVar24 - 1) {
        lVar19 = -0x10;
        do {
          puVar1 = (undefined8 *)((longlong)puVar20 + lVar19 + uVar23);
          uVar13 = puVar1[1];
          *(undefined8 *)(uVar18 + lVar19) = *puVar1;
          ((undefined8 *)(uVar18 + lVar19))[1] = uVar13;
          puVar1 = (undefined8 *)((longlong)puVar20 + lVar19 + (uVar23 - 0x10));
          uVar13 = puVar1[1];
          puVar3 = (undefined8 *)((uVar18 - 0x10) + lVar19);
          *puVar3 = *puVar1;
          puVar3[1] = uVar13;
          puVar1 = (undefined8 *)((longlong)puVar20 + lVar19 + (uVar23 - 0x20));
          uVar13 = puVar1[1];
          puVar3 = (undefined8 *)((uVar18 - 0x20) + lVar19);
          *puVar3 = *puVar1;
          puVar3[1] = uVar13;
          puVar1 = (undefined8 *)((longlong)puVar20 + lVar19 + (uVar23 - 0x30));
          uVar13 = puVar1[1];
          puVar3 = (undefined8 *)((uVar18 - 0x30) + lVar19);
          *puVar3 = *puVar1;
          puVar3[1] = uVar13;
          lVar19 = lVar19 + -0x40;
          lVar2 = lVar22 - (uVar24 & 0xfffffffffffffffc);
          lVar22 = lVar22 + 4;
        } while (lVar2 != -3);
      }
      if ((uVar24 & 3) != 0) {
        lVar19 = 0;
        do {
          puVar1 = (undefined8 *)((longlong)puVar20 + lVar19 + uVar23 + lVar22 * -0x10);
          uVar13 = puVar1[1];
          puVar3 = (undefined8 *)(uVar18 + lVar22 * -0x10 + lVar19);
          *puVar3 = *puVar1;
          puVar3[1] = uVar13;
          lVar19 = lVar19 + -0x10;
        } while ((ulonglong)(((uint)uVar24 & 3) << 4) + lVar19 != 0);
      }
    }
    *puVar21 = uVar11;
    puVar21[1] = uVar12;
    puVar21 = (undefined8 *)((longlong)puVar21 + (uVar17 - 0x10));
    *puVar21 = uVar9;
    puVar21[1] = uVar10;
  }
  else {
    uVar9 = *puVar20;
    uVar10 = puVar20[1];
    puVar1 = (undefined8 *)((longlong)puVar20 + (uVar17 - 0x10));
    uVar11 = *puVar1;
    uVar12 = puVar1[1];
    uVar18 = (ulonglong)((uint)puVar20 & 0xf);
    uVar23 = (uVar17 + uVar18) - 0x10 >> 4;
    if (uVar23 - 1 < 3) {
      uVar24 = 0;
    }
    else {
      uVar24 = 0;
      lVar22 = -uVar18;
      do {
        lVar19 = lVar22 + 0x40;
        puVar1 = (undefined8 *)((longlong)puVar20 + lVar22 + 0x10);
        uVar13 = puVar1[1];
        puVar3 = (undefined8 *)((longlong)puVar21 + lVar22 + 0x10);
        *puVar3 = *puVar1;
        puVar3[1] = uVar13;
        puVar1 = (undefined8 *)((longlong)puVar20 + lVar22 + 0x20);
        uVar13 = puVar1[1];
        puVar3 = (undefined8 *)((longlong)puVar21 + lVar22 + 0x20);
        *puVar3 = *puVar1;
        puVar3[1] = uVar13;
        puVar1 = (undefined8 *)((longlong)puVar20 + lVar22 + 0x30);
        uVar13 = puVar1[1];
        puVar3 = (undefined8 *)((longlong)puVar21 + lVar22 + 0x30);
        *puVar3 = *puVar1;
        puVar3[1] = uVar13;
        uVar13 = ((undefined8 *)((longlong)puVar20 + lVar19))[1];
        *(undefined8 *)((longlong)puVar21 + lVar19) = *(undefined8 *)((longlong)puVar20 + lVar19);
        ((undefined8 *)((longlong)puVar21 + lVar19))[1] = uVar13;
        uVar24 = uVar24 + 4;
        lVar22 = lVar19;
      } while ((uVar23 & 0xfffffffffffffffc) != uVar24);
    }
    if ((uVar23 & 3) != 0) {
      lVar22 = uVar24 * 0x10 - uVar18;
      uVar18 = 0;
      do {
        puVar1 = (undefined8 *)((longlong)puVar20 + uVar18 + lVar22 + 0x10);
        uVar13 = puVar1[1];
        puVar3 = (undefined8 *)((longlong)puVar21 + uVar18 + lVar22 + 0x10);
        *puVar3 = *puVar1;
        puVar3[1] = uVar13;
        uVar18 = uVar18 + 0x10;
      } while (((uint)uVar23 & 3) << 4 != uVar18);
    }
    puVar20 = (undefined8 *)((longlong)puVar21 + (uVar17 - 0x10));
    *puVar20 = uVar11;
    puVar20[1] = uVar12;
    *puVar21 = uVar9;
    puVar21[1] = uVar10;
  }
  return;
}

// CANDIDATE_LOCAL RVA 0x3c190; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3c190; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003c190(void)

{
  _DAT_1802fc8cc = 0;
  return;
}

// CANDIDATE_LOCAL RVA 0x3c1a0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3c1a0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


undefined8 FUN_18003c1a0(longlong *param_1,undefined8 param_2,undefined8 param_3)

{
  char cVar1;
  undefined8 uVar2;
  longlong lVar3;
  undefined8 unaff_RBP;
  
  if (DAT_1802f02e4 == '\x01') {
    lVar3 = FUN_180023f00(param_1,param_3);
    if (lVar3 != 0) {
      cVar1 = FUN_18002ace0(param_1,param_3,2);
      if (cVar1 == '\0') {
        return 0;
      }
    }
  }
  uVar2 = (**(code **)(*(longlong *)param_1[1] + 0x128))
                    ((longlong *)param_1[1],param_2,*(undefined8 *)(*param_1 + 0x978),param_3,
                     unaff_RBP);
  return uVar2;
}

