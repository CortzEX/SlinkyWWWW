// Recovered decompiler view: Auto Tool
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x37180, 0x376c0); proximity does not prove ownership.

// CALLBACK RVA 0x37180; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/auto_tool/auto_tool.c
// Differential report: analysis/module_behavior_recovery/auto_tool/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x37180; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180037180(longlong param_1)

{
  undefined8 *puVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  longlong lVar9;
  int iVar10;
  int iVar11;
  float fVar12;
  float fVar13;
  double dStack_78;
  double dStack_70;
  double dStack_68;
  longlong lStack_60;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  if (*(char *)(puVar1 + 8) != '\x01') {
    return;
  }
  uVar6 = FUN_180023f40(*puVar1,puVar1[5]);
  iVar3 = FUN_180025a60(*puVar1,uVar6);
  if ((_DAT_1802ee368 != -1) && (_DAT_1802ee36c != iVar3)) {
    _DAT_1802ee368 = -1;
    goto LAB_180037389;
  }
  if (_DAT_1802ee368 == -1) {
    lVar9 = FUN_180028a50(*puVar1,puVar1[5]);
    cVar2 = cRam00000001802ee3c0;
    if (lVar9 != 0) {
      uVar5 = FUN_180025c50(*puVar1,lVar9);
      switch(uVar5) {
      case 0x100:
      case 0x101:
      case 0x102:
      case 0x10d:
      case 0x10e:
      case 0x10f:
      case 0x111:
      case 0x112:
      case 0x113:
      case 0x115:
      case 0x116:
      case 0x117:
      case 0x11c:
      case 0x11d:
      case 0x11e:
      case 0x167:
        cVar2 = cRam00000001802ee400;
        break;
      default:
        cVar2 = cRam00000001802ee420;
        break;
      case 0x10b:
      case 0x10c:
      case 0x110:
      case 0x114:
      case 0x11b:
        cVar2 = cRam00000001802ee3e0;
      }
    }
    if (cVar2 == '\x01') goto LAB_1800371f1;
  }
  else {
LAB_1800371f1:
    uVar7 = FUN_180022cf0(*puVar1,puVar1[3]);
    cVar2 = FUN_180023f90(*puVar1,puVar1[5]);
    if (cVar2 == '\0') {
      uVar8 = FUN_180025270(*puVar1,uVar7);
      cVar2 = FUN_180025490(*puVar1,uVar8);
      if (cVar2 != '\0') {
        if (DAT_1802ee440 == '\x01') {
          uVar7 = FUN_180025030(*puVar1,uVar7);
          cVar2 = FUN_180025430(*puVar1,uVar7);
          if (cVar2 == '\0') goto LAB_18003737b;
        }
        lVar9 = FUN_180022e10(*puVar1,puVar1[3]);
        if ((lVar9 != 0) && (iVar4 = FUN_180024b50(*puVar1,lVar9), iVar4 == 1)) {
          FUN_180024c10(&dStack_78,*puVar1,lVar9);
          lStack_60 = FUN_180024690(*puVar1,puVar1[4],(int)dStack_78,(int)dStack_70,(int)dStack_68);
          if (lStack_60 != 0) {
            if (DAT_1802ee460 == '\x01') {
              uVar5 = FUN_180024280(*puVar1,lStack_60);
              cVar2 = FUN_18002ac60(&DAT_1802fc528,uVar5);
              if (cVar2 == '\0') goto LAB_18003737b;
            }
            if (_DAT_1802fc520 < 1) {
              uVar7 = *puVar1;
              iVar10 = 0;
              fVar13 = _DAT_180152420;
              iVar4 = iVar3;
              do {
                iVar11 = (iVar3 + iVar10) % 9;
                lVar9 = FUN_180026140(uVar7,uVar6,iVar11);
                if ((lVar9 != 0) &&
                   (fVar12 = (float)FUN_180025d40(uVar7,lVar9,lStack_60), fVar13 < fVar12)) {
                  fVar13 = fVar12;
                  iVar4 = iVar11;
                }
                iVar10 = iVar10 + 1;
              } while (iVar10 != 9);
              if (iVar3 == iVar4) {
                return;
              }
              cVar2 = FUN_18002aa80(0x1802ee158);
              if (((cVar2 != '\0') &&
                  (FUN_180025a80(*puVar1,uVar6,iVar4), _DAT_1802ee36c = iVar4, _DAT_1802ee368 == -1)
                  ) && (DAT_1802ee480 != '\0')) {
                _DAT_1802ee368 = iVar3;
              }
              if (iVar4 != -1) {
                return;
              }
            }
            else {
              _DAT_1802fc520 = _DAT_1802fc520 + -1;
            }
            goto LAB_180037389;
          }
        }
      }
    }
  }
LAB_18003737b:
  _DAT_1802fc520 = (int)_DAT_1802ee3a0;
LAB_180037389:
  FUN_18002aab0(0x1802ee158);
  if (_DAT_1802ee368 != -1) {
    FUN_180025a80(*puVar1,uVar6);
    _DAT_1802ee368 = -1;
  }
  return;
}

// CALLBACK RVA 0x374b0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/auto_tool/auto_tool.c
// Differential report: analysis/module_behavior_recovery/auto_tool/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x374b0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800374b0(void)

{
  func_0x00018013cf70(_DAT_1802fc528);
  _DAT_1802fc528 = 0;
  uRam00000001802fc530 = 0;
  return;
}

// UI RVA 0x374e0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x374e0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_1800374e0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  undefined8 uStack_30;
  undefined8 uStack_28;
  
  FUN_180013e90(param_1,param_2,&UNK_180152658);
  FUN_18000cf30(param_2,param_1,0x1802ee370);
  FUN_18000cef0(param_2,param_1,0x1802ee468);
  FUN_180013e90(param_1,param_2,&UNK_18015265d);
  FUN_18000cef0(param_2,param_1,0x1802ee3c8);
  FUN_18000cef0(param_2,param_1,0x1802ee3e8);
  FUN_18000cef0(param_2,param_1,0x1802ee3a8);
  FUN_18000cef0(param_2,param_1,0x1802ee408);
  FUN_180013e90(param_1,param_2,&UNK_18015266f);
  FUN_18000cef0(param_2,param_1,0x1802ee428);
  FUN_18000cef0(param_2,param_1,0x1802ee448);
  if (DAT_1802ee460 != '\x01') {
    return;
  }
  uStack_30 = 0;
  uStack_28 = 0;
  if (pcRam00000001802ee4e0 != (code *)0x0) {
    (*pcRam00000001802ee4e0)(&uStack_30,&uStack_28);
  }
  cVar1 = FUN_1800158e0(param_1,param_2,uRam00000001802ee488,uRam00000001802ee490,
                        uRam00000001802ee498,uRam00000001802ee4a0,0x1802ee4a8,uStack_30,uStack_28);
  if (cVar1 != '\0') {
    uRam00000001802ee4e8 = 1;
    FUN_18000c210(1);
  }
  return;
}

// SETTINGS RVA 0x375e0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x375e0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800375e0(undefined8 *param_1)

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
  
  FUN_18000c450(param_1,&UNK_180152695,0x1802ee370);
  FUN_18000c3b0(param_1,&UNK_1801526a5,0x1802ee468);
  FUN_18000c3b0(param_1,&UNK_1801526b1,0x1802ee3c8);
  FUN_18000c3b0(param_1,&UNK_1801526c3,0x1802ee3e8);
  FUN_18000c3b0(param_1,&UNK_1801526d5,0x1802ee3a8);
  FUN_18000c3b0(param_1,&UNK_1801526e7,0x1802ee408);
  FUN_18000c3b0(param_1,&UNK_1801526f9,0x1802ee428);
  FUN_18000c3b0(param_1,&UNK_180152707,0x1802ee448);
  if (*(char *)((longlong)param_1 + 0xc) == '\0') {
    iVar4 = *(int *)(param_1 + 1);
    if (iVar4 == 0) {
      (*pcRam00000001802ee4d8)(uRam00000001802ee4a8);
      lVar5 = FUN_18004e4d0(*param_1,&UNK_18015271f);
      iVar4 = FUN_180050920(lVar5);
      uVar8 = _DAT_18013ebf0;
      if ((lVar5 != 0 && iVar4 != 0) &&
         (plVar14 = *(longlong **)(lVar5 + 0x10), plVar14 != (longlong *)0x0)) {
        do {
          if (iRam00000001802ee4a0 == 1) {
            iVar4 = FUN_180050940(plVar14);
            if (iVar4 != 0) {
              lVar5 = FUN_18004e4d0(plVar14,&UNK_18013ec47);
              iVar4 = FUN_18004d110(lVar5);
              if (iVar4 != 0) {
                uVar12 = FUN_18004e4d0(plVar14,&UNK_18013ec4c);
                pcVar3 = pcRam00000001802ee4c8;
                uVar2 = uRam00000001802ee4a8;
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
          else if ((iRam00000001802ee4a0 == 0) && (iVar4 = FUN_18004d110(plVar14), iVar4 != 0)) {
            uStack_68 = 0;
            uStack_70 = 0;
            (*pcRam00000001802ee4c8)(uRam00000001802ee4a8,plVar14[4],&uStack_70);
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
        lVar6 = (*pcRam00000001802ee4b0)(uRam00000001802ee4a8);
        if (lVar6 != 0) {
          uVar13 = 0;
          lStack_60 = lVar5;
          do {
            if (iRam00000001802ee4a0 == 1) {
              lVar6 = FUN_18004f590();
              bVar15 = true;
              if (lVar6 != 0) {
                uVar8 = (*pcRam00000001802ee4b8)(uRam00000001802ee4a8,uVar13);
                lVar9 = FUN_18004f080(lVar6,&UNK_18013ec47,uVar8);
                if ((lVar9 != 0) &&
                   (lVar9 = FUN_18004f480(lVar6,&UNK_18013ec4c), lVar5 = lStack_60, lVar9 != 0)) {
                  pfVar10 = (float *)(*pcRam00000001802ee4c0)(uRam00000001802ee4a8,uVar13);
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
            else if (iRam00000001802ee4a0 == 0) {
              uVar8 = (*pcRam00000001802ee4b8)(uRam00000001802ee4a8,uVar13);
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
            uVar7 = (*pcRam00000001802ee4b0)(uRam00000001802ee4a8);
          } while (uVar13 < uVar7);
        }
      }
    }
    else if (iVar4 == 3) {
                    /* WARNING: Could not recover jumptable at 0x00018000ca67. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*pcRam00000001802ee4d8)(uRam00000001802ee4a8);
      return;
    }
  }
  return;
}

