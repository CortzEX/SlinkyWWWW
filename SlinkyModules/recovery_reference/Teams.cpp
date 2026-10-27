// Recovered decompiler view: Teams
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x31e10, 0x325c0); proximity does not prove ownership.

// CALLBACK RVA 0x31e10; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/teams/teams.c
// Differential report: analysis/module_behavior_recovery/teams/verification_report.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x31e10; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180031e10(longlong param_1)

{
  longlong *plVar1;
  char cVar2;
  short sVar3;
  short sVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  longlong lVar9;
  longlong lVar10;
  undefined8 *puVar11;
  char cStack_41;
  
  plVar1 = *(longlong **)(param_1 + 8);
  if (plVar1[5] == 0) {
    return;
  }
  puVar11 = (undefined8 *)*plVar1;
  if (*(int *)*puVar11 != 0) {
    uVar7 = FUN_180022d10(puVar11,plVar1[3]);
    uVar7 = FUN_180025eb0(*plVar1,uVar7);
    uVar8 = FUN_180023740(*plVar1,plVar1[5]);
    lVar9 = FUN_180024f40(*plVar1,uVar7,uVar8);
    puVar11 = (undefined8 *)*plVar1;
    if (lVar9 != 0) {
      lVar10 = FUN_180026010(puVar11,lVar9);
      if (lVar10 != 0) {
        uVar7 = FUN_180026090(*plVar1,lVar10);
        sVar3 = FUN_180028b40(*plVar1,uVar7);
        sVar4 = 0x72;
        if (sVar3 != 0) {
          sVar4 = sVar3;
        }
        goto LAB_180031edc;
      }
      lVar9 = FUN_180026030(*plVar1,lVar9);
      puVar11 = (undefined8 *)*plVar1;
      if (lVar9 != 0) {
        sVar4 = FUN_180028d20(puVar11,lVar9);
        goto LAB_180031edc;
      }
    }
  }
  sVar4 = FUN_180028e10(puVar11,plVar1[5]);
LAB_180031edc:
  uVar7 = FUN_180024600(*plVar1,plVar1[4]);
  iVar5 = FUN_180024e50(*plVar1,uVar7);
  if (0 < iVar5) {
    iVar5 = 0;
    do {
      uVar8 = FUN_180024e80(*plVar1,uVar7,iVar5);
      cVar2 = (**(code **)(**(longlong **)(*plVar1 + 8) + 0xc0))
                        (*(longlong **)(*plVar1 + 8),plVar1[5],uVar8);
      if (cVar2 == '\0') {
        sVar3 = FUN_180028e10(*plVar1,uVar8);
        if ((DAT_1802eb628 != '\x01') || (sVar3 != sVar4)) {
          cStack_41 = -0x30;
          if ('`' < (char)sVar3) {
            cStack_41 = -0x57;
          }
          cStack_41 = cStack_41 + (char)sVar3;
          lVar9 = FUN_18000df00(_DAT_1802f9e20,1,0x1802f9e28,&cStack_41,FUN_180032170);
          if (lVar9 == 0) {
            FUN_18002ad80(*plVar1,uVar8,1);
            goto LAB_180031f22;
          }
        }
        FUN_18002ad20(*plVar1,uVar8,1);
      }
LAB_180031f22:
      iVar5 = iVar5 + 1;
      iVar6 = FUN_180024e50(*plVar1,uVar7);
    } while (iVar5 < iVar6);
  }
  return;
}

// CALLBACK RVA 0x31ff0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/teams/teams.c
// Differential report: analysis/module_behavior_recovery/teams/verification_report.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x31ff0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180031ff0(longlong param_1)

{
  longlong *plVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  
  if ((*(longlong *)(param_1 + 0x10) == 0x1802eb400) && (*(char *)(param_1 + 0x18) == '\0')) {
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
            FUN_18002ad80(*plVar1,uVar6,1);
          }
          iVar3 = iVar3 + 1;
          iVar4 = FUN_180024e50(*plVar1,uVar5);
        } while (iVar3 < iVar4);
      }
    }
  }
  return;
}

// CALLBACK RVA 0x320b0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/teams/teams.c
// Differential report: analysis/module_behavior_recovery/teams/verification_report.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x320b0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800320b0(void)

{
  func_0x00018013cf70(_DAT_1802f9e20);
  _DAT_1802f9e20 = 0;
  uRam00000001802f9e28 = 0;
  return;
}

// UI RVA 0x320e0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x320e0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_1800320e0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  undefined8 uStack_30;
  undefined8 uStack_28;
  
  FUN_180013e90(param_1,param_2,&UNK_18015141a);
  FUN_18000cef0(param_2,param_1,0x1802eb610);
  uStack_30 = 0;
  uStack_28 = 0;
  if (pcRam00000001802eb688 != (code *)0x0) {
    (*pcRam00000001802eb688)(&uStack_30,&uStack_28);
  }
  cVar1 = FUN_1800158e0(param_1,param_2,uRam00000001802eb630,uRam00000001802eb638,
                        uRam00000001802eb640,uRam00000001802eb648,0x1802eb650,uStack_30,uStack_28);
  if (cVar1 != '\0') {
    uRam00000001802eb690 = 1;
    FUN_18000c210(1);
  }
  return;
}

// SETTINGS RVA 0x32130; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x32130; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180032130(undefined8 *param_1)

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
  
  FUN_18000c3b0(param_1,&UNK_1801514cd,0x1802eb610);
  if (*(char *)((longlong)param_1 + 0xc) == '\0') {
    iVar4 = *(int *)(param_1 + 1);
    if (iVar4 == 0) {
      (*pcRam00000001802eb680)(uRam00000001802eb650);
      lVar5 = FUN_18004e4d0(*param_1,&UNK_1801514de);
      iVar4 = FUN_180050920(lVar5);
      uVar8 = _DAT_18013ebf0;
      if ((lVar5 != 0 && iVar4 != 0) &&
         (plVar14 = *(longlong **)(lVar5 + 0x10), plVar14 != (longlong *)0x0)) {
        do {
          if (iRam00000001802eb648 == 1) {
            iVar4 = FUN_180050940(plVar14);
            if (iVar4 != 0) {
              lVar5 = FUN_18004e4d0(plVar14,&UNK_18013ec47);
              iVar4 = FUN_18004d110(lVar5);
              if (iVar4 != 0) {
                uVar12 = FUN_18004e4d0(plVar14,&UNK_18013ec4c);
                pcVar3 = pcRam00000001802eb670;
                uVar2 = uRam00000001802eb650;
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
          else if ((iRam00000001802eb648 == 0) && (iVar4 = FUN_18004d110(plVar14), iVar4 != 0)) {
            uStack_68 = 0;
            uStack_70 = 0;
            (*pcRam00000001802eb670)(uRam00000001802eb650,plVar14[4],&uStack_70);
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
        lVar6 = (*pcRam00000001802eb658)(uRam00000001802eb650);
        if (lVar6 != 0) {
          uVar13 = 0;
          lStack_60 = lVar5;
          do {
            if (iRam00000001802eb648 == 1) {
              lVar6 = FUN_18004f590();
              bVar15 = true;
              if (lVar6 != 0) {
                uVar8 = (*pcRam00000001802eb660)(uRam00000001802eb650,uVar13);
                lVar9 = FUN_18004f080(lVar6,&UNK_18013ec47,uVar8);
                if ((lVar9 != 0) &&
                   (lVar9 = FUN_18004f480(lVar6,&UNK_18013ec4c), lVar5 = lStack_60, lVar9 != 0)) {
                  pfVar10 = (float *)(*pcRam00000001802eb668)(uRam00000001802eb650,uVar13);
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
            else if (iRam00000001802eb648 == 0) {
              uVar8 = (*pcRam00000001802eb660)(uRam00000001802eb650,uVar13);
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
            uVar7 = (*pcRam00000001802eb658)(uRam00000001802eb650);
          } while (uVar13 < uVar7);
        }
      }
    }
    else if (iVar4 == 3) {
                    /* WARNING: Could not recover jumptable at 0x00018000ca67. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*pcRam00000001802eb680)(uRam00000001802eb650);
      return;
    }
  }
  return;
}

// CANDIDATE_LOCAL RVA 0x32170; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x32170; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


int FUN_180032170(undefined8 param_1,char *param_2,char *param_3)

{
  return (int)*param_2 - (int)*param_3;
}

// CANDIDATE_LOCAL RVA 0x32180; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x32180; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180032180(longlong param_1,char param_2)

{
  ulonglong uVar1;
  
  uVar1 = func_0x0001800ab840();
  if ((uVar1 < 100) &&
     (((byte)(param_2 + 0x9fU) < 0x1a || (param_2 == ' ' || (byte)(param_2 + 0xbfU) < 0x1a)))) {
    *(char *)(param_1 + uVar1) = param_2;
  }
  return;
}

// CANDIDATE_LOCAL RVA 0x321d0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x321d0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_1800321d0(void)

{
  return _DAT_1802f9e2c;
}

// CANDIDATE_LOCAL RVA 0x321e0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x321e0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_1800321e0(undefined8 param_1,undefined8 param_2)

{
  char *pcVar1;
  
  pcVar1 = (char *)FUN_18000ddc0(_DAT_1802f9e20,1,0x1802f9e28,param_2);
  return *(undefined8 *)(&DAT_1802eb6a0 + (longlong)*pcVar1 * 8);
}

// CANDIDATE_LOCAL RVA 0x32220; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x32220; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_180032220(undefined8 param_1,undefined8 param_2)

{
  int iVar1;
  undefined1 uStack_11;
  
  iVar1 = func_0x00018013d0a0(param_2,_DAT_1802eb6a0);
  if (iVar1 == 0) {
    uStack_11 = 0;
  }
  else {
    iVar1 = func_0x00018013d0a0(param_2,_DAT_1802eb6a8);
    if (iVar1 == 0) {
      uStack_11 = 1;
    }
    else {
      iVar1 = func_0x00018013d0a0(param_2,_DAT_1802eb6b0);
      if (iVar1 == 0) {
        uStack_11 = 2;
      }
      else {
        iVar1 = func_0x00018013d0a0(param_2,_DAT_1802eb6b8);
        if (iVar1 == 0) {
          uStack_11 = 3;
        }
        else {
          iVar1 = func_0x00018013d0a0(param_2,_DAT_1802eb6c0);
          if (iVar1 == 0) {
            uStack_11 = 4;
          }
          else {
            iVar1 = func_0x00018013d0a0(param_2,_DAT_1802eb6c8);
            if (iVar1 == 0) {
              uStack_11 = 5;
            }
            else {
              iVar1 = func_0x00018013d0a0(param_2,_DAT_1802eb6d0);
              if (iVar1 == 0) {
                uStack_11 = 6;
              }
              else {
                iVar1 = func_0x00018013d0a0(param_2,_DAT_1802eb6d8);
                if (iVar1 == 0) {
                  uStack_11 = 7;
                }
                else {
                  iVar1 = func_0x00018013d0a0(param_2,_DAT_1802eb6e0);
                  if (iVar1 == 0) {
                    uStack_11 = 8;
                  }
                  else {
                    iVar1 = func_0x00018013d0a0(param_2,_DAT_1802eb6e8);
                    if (iVar1 == 0) {
                      uStack_11 = 9;
                    }
                    else {
                      iVar1 = func_0x00018013d0a0(param_2,_DAT_1802eb6f0);
                      if (iVar1 == 0) {
                        uStack_11 = 10;
                      }
                      else {
                        iVar1 = func_0x00018013d0a0(param_2,_DAT_1802eb6f8);
                        if (iVar1 == 0) {
                          uStack_11 = 0xb;
                        }
                        else {
                          iVar1 = func_0x00018013d0a0(param_2,_DAT_1802eb700);
                          if (iVar1 == 0) {
                            uStack_11 = 0xc;
                          }
                          else {
                            iVar1 = func_0x00018013d0a0(param_2,_DAT_1802eb708);
                            if (iVar1 == 0) {
                              uStack_11 = 0xd;
                            }
                            else {
                              iVar1 = func_0x00018013d0a0(param_2,_DAT_1802eb710);
                              if (iVar1 == 0) {
                                uStack_11 = 0xe;
                              }
                              else {
                                iVar1 = func_0x00018013d0a0(param_2,_DAT_1802eb718);
                                if (iVar1 != 0) {
                                  return 0;
                                }
                                uStack_11 = 0xf;
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  FUN_18000e0b0(&DAT_1802f9e20,1,0x1802f9e28,&uStack_11,FUN_180032170);
  return 1;
}

// CANDIDATE_LOCAL RVA 0x32400; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x32400; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180032400(undefined8 param_1,uint param_2)

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
  longlong lVar18;
  undefined8 *puVar19;
  ulonglong uVar20;
  undefined8 *puVar21;
  longlong lVar22;
  ulonglong uVar23;
  ulonglong uVar24;
  
  _DAT_1802f9e2c = _DAT_1802f9e2c + -1;
  uVar16 = _DAT_1802f9e2c - param_2;
  puVar21 = (undefined8 *)((ulonglong)param_2 + _DAT_1802f9e20);
  puVar19 = (undefined8 *)((ulonglong)(param_2 + 1) + _DAT_1802f9e20);
  uVar17 = (ulonglong)uVar16;
  if (uVar17 < 0x10) {
    if (uVar17 < 4) {
      if (uVar17 != 0) {
        uVar4 = *(undefined1 *)((longlong)puVar19 + (ulonglong)(uVar16 >> 1));
        uVar5 = *(undefined1 *)((longlong)puVar19 + (uVar17 - 1));
        *(undefined1 *)puVar21 = *(undefined1 *)puVar19;
        *(undefined1 *)((longlong)puVar21 + (ulonglong)(uVar16 >> 1)) = uVar4;
        *(undefined1 *)((longlong)puVar21 + (uVar17 - 1)) = uVar5;
      }
    }
    else {
      uVar20 = (ulonglong)(uVar16 >> 1 & 4);
      lVar22 = (uVar17 - 4) - uVar20;
      uVar6 = *(undefined4 *)((longlong)puVar19 + uVar20);
      uVar7 = *(undefined4 *)((longlong)puVar19 + lVar22);
      uVar8 = *(undefined4 *)((longlong)puVar19 + (uVar17 - 4));
      *(undefined4 *)puVar21 = *(undefined4 *)puVar19;
      *(undefined4 *)((longlong)puVar21 + uVar20) = uVar6;
      *(undefined4 *)((longlong)puVar21 + lVar22) = uVar7;
      *(undefined4 *)((longlong)puVar21 + (uVar17 - 4)) = uVar8;
    }
  }
  else if (uVar17 < 0x40) {
    uVar20 = (ulonglong)(uVar16 >> 1 & 0x10);
    lVar22 = (uVar17 - 0x10) - uVar20;
    uVar9 = puVar19[1];
    uVar10 = *(undefined8 *)((longlong)puVar19 + uVar20);
    uVar11 = ((undefined8 *)((longlong)puVar19 + uVar20))[1];
    puVar1 = (undefined8 *)((longlong)puVar19 + lVar22);
    uVar12 = *puVar1;
    uVar13 = puVar1[1];
    puVar1 = (undefined8 *)((longlong)puVar19 + (uVar17 - 0x10));
    uVar14 = *puVar1;
    uVar15 = puVar1[1];
    *puVar21 = *puVar19;
    puVar21[1] = uVar9;
    *(undefined8 *)((longlong)puVar21 + uVar20) = uVar10;
    ((undefined8 *)((longlong)puVar21 + uVar20))[1] = uVar11;
    puVar19 = (undefined8 *)((longlong)puVar21 + lVar22);
    *puVar19 = uVar12;
    puVar19[1] = uVar13;
    puVar21 = (undefined8 *)((longlong)puVar21 + (uVar17 - 0x10));
    *puVar21 = uVar14;
    puVar21[1] = uVar15;
  }
  else if (puVar19 < puVar21) {
    puVar1 = (undefined8 *)((longlong)puVar19 + (uVar17 - 0x10));
    uVar9 = *puVar1;
    uVar10 = puVar1[1];
    uVar11 = *puVar19;
    uVar12 = puVar19[1];
    uVar20 = (ulonglong)(uVar17 + (longlong)puVar21) & 0xfffffffffffffff0;
    uVar23 = uVar20 - (longlong)puVar21;
    if (0xf < uVar23) {
      uVar24 = uVar23 >> 4;
      lVar22 = 1;
      if (2 < uVar24 - 1) {
        lVar18 = -0x10;
        do {
          puVar1 = (undefined8 *)((longlong)puVar19 + lVar18 + uVar23);
          uVar13 = puVar1[1];
          *(undefined8 *)(uVar20 + lVar18) = *puVar1;
          ((undefined8 *)(uVar20 + lVar18))[1] = uVar13;
          puVar1 = (undefined8 *)((longlong)puVar19 + lVar18 + (uVar23 - 0x10));
          uVar13 = puVar1[1];
          puVar3 = (undefined8 *)((uVar20 - 0x10) + lVar18);
          *puVar3 = *puVar1;
          puVar3[1] = uVar13;
          puVar1 = (undefined8 *)((longlong)puVar19 + lVar18 + (uVar23 - 0x20));
          uVar13 = puVar1[1];
          puVar3 = (undefined8 *)((uVar20 - 0x20) + lVar18);
          *puVar3 = *puVar1;
          puVar3[1] = uVar13;
          puVar1 = (undefined8 *)((longlong)puVar19 + lVar18 + (uVar23 - 0x30));
          uVar13 = puVar1[1];
          puVar3 = (undefined8 *)((uVar20 - 0x30) + lVar18);
          *puVar3 = *puVar1;
          puVar3[1] = uVar13;
          lVar18 = lVar18 + -0x40;
          lVar2 = lVar22 - (uVar24 & 0xfffffffffffffffc);
          lVar22 = lVar22 + 4;
        } while (lVar2 != -3);
      }
      if ((uVar24 & 3) != 0) {
        lVar18 = 0;
        do {
          puVar1 = (undefined8 *)((longlong)puVar19 + lVar18 + uVar23 + lVar22 * -0x10);
          uVar13 = puVar1[1];
          puVar3 = (undefined8 *)(uVar20 + lVar22 * -0x10 + lVar18);
          *puVar3 = *puVar1;
          puVar3[1] = uVar13;
          lVar18 = lVar18 + -0x10;
        } while ((ulonglong)(((uint)uVar24 & 3) << 4) + lVar18 != 0);
      }
    }
    *puVar21 = uVar11;
    puVar21[1] = uVar12;
    puVar21 = (undefined8 *)((longlong)puVar21 + (uVar17 - 0x10));
    *puVar21 = uVar9;
    puVar21[1] = uVar10;
  }
  else {
    uVar9 = *puVar19;
    uVar10 = puVar19[1];
    puVar1 = (undefined8 *)((longlong)puVar19 + (uVar17 - 0x10));
    uVar11 = *puVar1;
    uVar12 = puVar1[1];
    uVar20 = (ulonglong)((uint)puVar19 & 0xf);
    uVar23 = (uVar17 + uVar20) - 0x10 >> 4;
    if (uVar23 - 1 < 3) {
      uVar24 = 0;
    }
    else {
      uVar24 = 0;
      lVar22 = -uVar20;
      do {
        lVar18 = lVar22 + 0x40;
        puVar1 = (undefined8 *)((longlong)puVar19 + lVar22 + 0x10);
        uVar13 = puVar1[1];
        puVar3 = (undefined8 *)((longlong)puVar21 + lVar22 + 0x10);
        *puVar3 = *puVar1;
        puVar3[1] = uVar13;
        puVar1 = (undefined8 *)((longlong)puVar19 + lVar22 + 0x20);
        uVar13 = puVar1[1];
        puVar3 = (undefined8 *)((longlong)puVar21 + lVar22 + 0x20);
        *puVar3 = *puVar1;
        puVar3[1] = uVar13;
        puVar1 = (undefined8 *)((longlong)puVar19 + lVar22 + 0x30);
        uVar13 = puVar1[1];
        puVar3 = (undefined8 *)((longlong)puVar21 + lVar22 + 0x30);
        *puVar3 = *puVar1;
        puVar3[1] = uVar13;
        uVar13 = ((undefined8 *)((longlong)puVar19 + lVar18))[1];
        *(undefined8 *)((longlong)puVar21 + lVar18) = *(undefined8 *)((longlong)puVar19 + lVar18);
        ((undefined8 *)((longlong)puVar21 + lVar18))[1] = uVar13;
        uVar24 = uVar24 + 4;
        lVar22 = lVar18;
      } while ((uVar23 & 0xfffffffffffffffc) != uVar24);
    }
    if ((uVar23 & 3) != 0) {
      lVar22 = uVar24 * 0x10 - uVar20;
      uVar20 = 0;
      do {
        puVar1 = (undefined8 *)((longlong)puVar19 + uVar20 + lVar22 + 0x10);
        uVar13 = puVar1[1];
        puVar3 = (undefined8 *)((longlong)puVar21 + uVar20 + lVar22 + 0x10);
        *puVar3 = *puVar1;
        puVar3[1] = uVar13;
        uVar20 = uVar20 + 0x10;
      } while (((uint)uVar23 & 3) << 4 != uVar20);
    }
    puVar19 = (undefined8 *)((longlong)puVar21 + (uVar17 - 0x10));
    *puVar19 = uVar11;
    puVar19[1] = uVar12;
    *puVar21 = uVar9;
    puVar21[1] = uVar10;
  }
  return;
}

// CANDIDATE_LOCAL RVA 0x32420; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x32420; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180032420(void)

{
  _DAT_1802f9e2c = 0;
  return;
}

// CANDIDATE_LOCAL RVA 0x32430; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x32430; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180032430(undefined8 *param_1,undefined8 *param_2)

{
  *param_1 = &DAT_1802eb6a0;
  *param_2 = 0x10;
  return;
}

// CANDIDATE_LOCAL RVA 0x32450; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x32450; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180032450(void)

{
  func_0x000181040a38();
  return;
}

// CANDIDATE_LOCAL RVA 0x32470; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x32470; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


undefined1 FUN_180032470(void)

{
  return uRam00000001802fa2fb;
}

// CANDIDATE_LOCAL RVA 0x32490; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x32490; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_180032490(void)

{
  return *(undefined4 *)(&UNK_1801514f0 + (ulonglong)_DAT_1802eb9a0 * 4);
}

// CANDIDATE_LOCAL RVA 0x324b0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x324b0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800324b0(undefined8 *param_1)

{
  *(undefined4 *)(param_1 + 1) = _DAT_1802eb730;
  *param_1 = _DAT_1802eb728;
  return;
}

// CANDIDATE_LOCAL RVA 0x324d0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x324d0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_1800324d0(int *param_1,char param_2,undefined8 param_3)

{
  int iVar1;
  char cVar2;
  byte bVar3;
  
  if (DAT_1802eb754 == 1) {
    cVar2 = FUN_180010f30(0x1802f9e30,param_1);
    if (cVar2 != '\0') {
      return 1;
    }
  }
  if (((*param_1 == 2) && ((char)param_1[3] == '\x01')) && (iVar1 = param_1[1], iVar1 != 0)) {
    if ((param_2 == '\0') && (iVar1 == _DAT_1802eb75c)) {
      bVar3 = DAT_1802eb754 ^ 1;
    }
    else {
      if (iVar1 != 0x57 || DAT_1802eb754 != 1) goto LAB_180032556;
      bVar3 = 0;
    }
    FUN_1800284f0(param_3,0x1802eb740,bVar3);
  }
  else {
LAB_180032556:
    if ((DAT_1802eb754 != 1) ||
       (((*param_1 == 2 && (DAT_1802eb9c8 != '\0')) && (5 < (uint)param_1[1])))) {
      return 0;
    }
  }
  return 1;
}

// CANDIDATE_LOCAL RVA 0x32590; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x32590; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


undefined1 FUN_180032590(longlong param_1)

{
  FUN_1800284f0(*(undefined8 *)(param_1 + 8),0x1802eb740,1);
  return 1;
}

