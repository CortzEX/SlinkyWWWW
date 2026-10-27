// Recovered decompiler view: Auto Soup
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x2d510, 0x2de50); proximity does not prove ownership.

// CALLBACK RVA 0x2d510; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/auto_soup/auto_soup.c
// Differential report: analysis/module_behavior_recovery/auto_soup/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2d510; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong FUN_18002d510(longlong param_1)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  ulonglong uVar4;
  longlong *plVar5;
  undefined8 unaff_RSI;
  undefined8 uStack_78;
  undefined8 uStack_70;
  ulonglong uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  
  uVar4 = *(ulonglong *)(param_1 + 8);
  if ((DAT_1802f7d68 != '\x01') || ((_DAT_1802f7d6c != 6 && (_DAT_1802f7d6c != 0)))) {
    if (*(char *)(uVar4 + 0x40) == '\x01') {
      if (_DAT_1802f7d80 <= 0.0) {
                    /* WARNING: Could not recover jumptable at 0x00018002d65b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        uVar4 = (*(code *)(&UNK_1801505c4 + *(int *)(&UNK_1801505c4 + (ulonglong)_DAT_1802f7d6c * 4)
                          ))();
        return uVar4;
      }
      _DAT_1802f7d80 = _DAT_1802f7d80 + _DAT_1801505c0;
    }
    else {
      DAT_1802f7d70 = 0;
      _DAT_1802f7d6c = 0;
    }
    return uVar4;
  }
  lVar2 = *(longlong *)(uVar4 + 8);
  uVar4 = CONCAT71((int7)((ulonglong)unaff_RSI >> 8),1);
  if (cRam00000001802e96c4 != '\0') {
    uStack_48 = 0;
    uStack_58 = 0;
    uStack_50 = 0;
    uStack_68 = 0;
    uStack_60 = 0;
    uStack_78 = 4;
    uStack_70 = 0x1802e96b0;
    plVar5 = *(longlong **)(lVar2 + 0x230);
    pcVar3 = (code *)*plVar5;
    if (pcVar3 != (code *)0x0) {
      do {
        plVar5 = plVar5 + 1;
        (*pcVar3)(&uStack_78);
        pcVar3 = (code *)*plVar5;
      } while (pcVar3 != (code *)0x0);
      if ((uStack_68 & 1) != 0) {
        uVar4 = 0;
        goto LAB_1800285a1;
      }
    }
    lVar1 = *(longlong *)(lVar2 + 0x300);
    *(undefined8 *)(*(longlong *)(lVar2 + 0x2f8) + lVar1 * 8) = 0x1802e96b0;
    *(longlong *)(lVar2 + 0x300) = lVar1 + 1;
  }
LAB_1800285a1:
  return uVar4 & 0xffffffff;
}

// CALLBACK RVA 0x2dae0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/auto_soup/auto_soup.c
// Differential report: analysis/module_behavior_recovery/auto_soup/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2dae0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002dae0(longlong param_1)

{
  if (((*(longlong *)(param_1 + 8) == 0x1802e96b0) && (_DAT_1802f7d6c != 0)) &&
     (_DAT_1802f7d6c != 6)) {
    *(undefined1 *)(param_1 + 0x10) = 1;
    DAT_1802f7d68 = 1;
    return;
  }
  return;
}

// CALLBACK RVA 0x2db10; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/auto_soup/auto_soup.c
// Differential report: analysis/module_behavior_recovery/auto_soup/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2db10; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002db10(longlong param_1)

{
  if ((*(longlong *)(param_1 + 0x10) == 0x1802e96b0) && (*(char *)(param_1 + 0x18) == '\x01')) {
    _DAT_1802f7d6c = 0;
    DAT_1802f7d70 = 0;
    _DAT_1802f7d80 = 0;
    DAT_1802f7d68 = 0;
    return;
  }
  return;
}

// UI RVA 0x2db50; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2db50; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002db50(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  undefined8 uStack_30;
  undefined8 uStack_28;
  
  FUN_180013e90(param_1,param_2,&UNK_1801506ab);
  FUN_18000cf30(param_2,param_1,0x1802e98c0);
  if (_DAT_1802e98f0 < _DAT_1802e9960) {
    _DAT_1802e9960 = _DAT_1802e98f0;
  }
  FUN_18000cf30(param_2,param_1,0x1802e9930);
  FUN_180013e90(param_1,param_2,&UNK_1801506ba);
  FUN_18000cf30(param_2,param_1,0x1802e99d8);
  FUN_18000cf30(param_2,param_1,0x1802e98f8);
  FUN_18000cf30(param_2,param_1,0x1802e9968);
  FUN_18000cf30(param_2,param_1,0x1802e99a0);
  FUN_180013e90(param_1,param_2,&UNK_1801506c1);
  FUN_18000cef0(param_2,param_1,0x1802e9a30);
  FUN_18000cef0(param_2,param_1,0x1802e9a10);
  if (DAT_1802e9a28 != '\x01') {
    return;
  }
  uStack_30 = 0;
  uStack_28 = 0;
  if (pcRam00000001802e9aa8 != (code *)0x0) {
    (*pcRam00000001802e9aa8)(&uStack_30,&uStack_28);
  }
  cVar1 = FUN_1800158e0(param_1,param_2,uRam00000001802e9a50,uRam00000001802e9a58,
                        uRam00000001802e9a60,uRam00000001802e9a68,0x1802e9a70,uStack_30,uStack_28);
  if (cVar1 != '\0') {
    uRam00000001802e9ab0 = 1;
    FUN_18000c210(1);
  }
  return;
}

// SETTINGS RVA 0x2dc70; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2dc70; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002dc70(undefined8 *param_1)

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
  
  FUN_18000c450(param_1,&UNK_1801506d9,0x1802e98c0);
  FUN_18000c450(param_1,&UNK_1801506ec,0x1802e9930);
  FUN_18000c450(param_1,&UNK_1801506ff,0x1802e99d8);
  FUN_18000c450(param_1,&UNK_18015070d,0x1802e98f8);
  FUN_18000c450(param_1,&UNK_18015071a,0x1802e9968);
  FUN_18000c450(param_1,&UNK_180150728,0x1802e99a0);
  FUN_18000c3b0(param_1,&UNK_180150734,0x1802e9a30);
  FUN_18000c3b0(param_1,&UNK_18015073f,0x1802e9a10);
  if (*(char *)((longlong)param_1 + 0xc) == '\0') {
    iVar4 = *(int *)(param_1 + 1);
    if (iVar4 == 0) {
      (*pcRam00000001802e9aa0)(uRam00000001802e9a70);
      lVar5 = FUN_18004e4d0(*param_1,&UNK_18015074d);
      iVar4 = FUN_180050920(lVar5);
      uVar8 = _DAT_18013ebf0;
      if ((lVar5 != 0 && iVar4 != 0) &&
         (plVar14 = *(longlong **)(lVar5 + 0x10), plVar14 != (longlong *)0x0)) {
        do {
          if (iRam00000001802e9a68 == 1) {
            iVar4 = FUN_180050940(plVar14);
            if (iVar4 != 0) {
              lVar5 = FUN_18004e4d0(plVar14,&UNK_18013ec47);
              iVar4 = FUN_18004d110(lVar5);
              if (iVar4 != 0) {
                uVar12 = FUN_18004e4d0(plVar14,&UNK_18013ec4c);
                pcVar3 = pcRam00000001802e9a90;
                uVar2 = uRam00000001802e9a70;
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
          else if ((iRam00000001802e9a68 == 0) && (iVar4 = FUN_18004d110(plVar14), iVar4 != 0)) {
            uStack_68 = 0;
            uStack_70 = 0;
            (*pcRam00000001802e9a90)(uRam00000001802e9a70,plVar14[4],&uStack_70);
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
        lVar6 = (*pcRam00000001802e9a78)(uRam00000001802e9a70);
        if (lVar6 != 0) {
          uVar13 = 0;
          lStack_60 = lVar5;
          do {
            if (iRam00000001802e9a68 == 1) {
              lVar6 = FUN_18004f590();
              bVar15 = true;
              if (lVar6 != 0) {
                uVar8 = (*pcRam00000001802e9a80)(uRam00000001802e9a70,uVar13);
                lVar9 = FUN_18004f080(lVar6,&UNK_18013ec47,uVar8);
                if ((lVar9 != 0) &&
                   (lVar9 = FUN_18004f480(lVar6,&UNK_18013ec4c), lVar5 = lStack_60, lVar9 != 0)) {
                  pfVar10 = (float *)(*pcRam00000001802e9a88)(uRam00000001802e9a70,uVar13);
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
            else if (iRam00000001802e9a68 == 0) {
              uVar8 = (*pcRam00000001802e9a80)(uRam00000001802e9a70,uVar13);
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
            uVar7 = (*pcRam00000001802e9a78)(uRam00000001802e9a70);
          } while (uVar13 < uVar7);
        }
      }
    }
    else if (iVar4 == 3) {
                    /* WARNING: Could not recover jumptable at 0x00018000ca67. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*pcRam00000001802e9aa0)(uRam00000001802e9a70);
      return;
    }
  }
  return;
}

// CANDIDATE_LOCAL RVA 0x2dd50; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2dd50; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float FUN_18002dd50(float param_1)

{
  undefined8 uVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  char cVar4;
  float fVar5;
  float fVar6;
  
  uVar2 = _DAT_1801505e0;
  uVar1 = FUN_18000a050(0,_DAT_1801505e0);
  uVar3 = _DAT_1801505e8;
  fVar5 = (float)FUN_18000a510(0x1802f7d88,uVar1,_DAT_1801505e8);
  uVar1 = FUN_18000a050(0,uVar2);
  fVar6 = (float)FUN_18000a510(0x1802f7d88,uVar1,_DAT_1801505f0);
  fVar6 = fVar6 + fVar5;
  uVar1 = FUN_18000a050(_DAT_1801505f8,_DAT_1801505fc);
  cVar4 = FUN_18000aa30(0x1802f7d98,uVar1,uVar3);
  if (cVar4 != '\0') {
    uVar1 = FUN_18000a050(_DAT_1801505e0,_DAT_180150600);
    fVar5 = (float)FUN_18000a3e0(uVar1);
    fVar6 = fVar6 + fVar5;
  }
  return fVar6 * _DAT_1802e9a08 + param_1;
}

