// Recovered decompiler view: Auto Clicker
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x2ca10, 0x2d510); proximity does not prove ownership.

// CALLBACK RVA 0x2ca10; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/auto_clicker/auto_clicker.c
// Differential report: analysis/module_behavior_recovery/auto_clicker/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2ca10; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002ca10(longlong param_1)

{
  longlong *plVar1;
  undefined8 *puVar2;
  int iVar3;
  undefined8 uVar4;
  
  puVar2 = *(undefined8 **)(param_1 + 8);
  uVar4 = FUN_180022cf0(*puVar2,puVar2[3]);
  uVar4 = FUN_180025270(*puVar2,uVar4);
  iVar3 = FUN_180025410(*puVar2,uVar4);
  DAT_1802f7c90 = iVar3 == -99;
  if (*(char *)(puVar2 + 8) == '\x01') {
    _DAT_1802f7c88 = FUN_180023170(*puVar2,puVar2[5]);
    if (*(char *)(_DAT_1801505a0 + 0x14) == '\0') {
      plVar1 = (longlong *)((longlong *)*puVar2)[1];
                    /* WARNING: Could not recover jumptable at 0x000180022ed0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*plVar1 + 0x368))
                (plVar1,puVar2[3],*(undefined8 *)(*(longlong *)*puVar2 + 0x1b8),0);
      return;
    }
  }
  return;
}

// CALLBACK RVA 0x2ca90; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/auto_clicker/auto_clicker.c
// Differential report: analysis/module_behavior_recovery/auto_clicker/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2ca90; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002ca90(longlong param_1)

{
  undefined8 *puVar1;
  undefined4 uVar2;
  float fVar3;
  char cVar4;
  byte bVar5;
  int iVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  longlong lVar9;
  undefined8 uVar10;
  longlong lVar11;
  byte bVar12;
  byte bVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  undefined4 uVar20;
  float fVar21;
  double dVar22;
  undefined4 uVar23;
  undefined4 uVar24;
  float afStack_ec [43];
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  uVar7 = FUN_180022c70(*puVar1,puVar1[3]);
  dVar22 = *(double *)(param_1 + 0x18);
  fVar14 = (float)FUN_1800259a0(*puVar1,uVar7);
  fVar3 = _DAT_1801503a8;
  fVar21 = _DAT_1801503a0;
  uVar20 = _DAT_180150384;
  uVar7 = _DAT_180150378;
  dVar22 = _DAT_1802f7c98 - (double)fVar14 * dVar22;
  _DAT_1802f7c98 = _DAT_180150328;
  if (_DAT_180150328 <= dVar22) {
    _DAT_1802f7c98 = dVar22;
  }
  if (_DAT_1802f7c98 <= 0.0) {
    bVar13 = *(byte *)((ulonglong)DAT_1802f7c90 + 1 + puVar1[6]);
    bVar12 = (bVar13 & 2) >> 1;
    uVar23 = (undefined4)_DAT_180150330;
    uVar24 = (undefined4)((ulonglong)_DAT_180150330 >> 0x20);
    do {
      if (*(char *)(puVar1 + 8) == '\0') {
        if (bVar12 != 0) {
          FUN_18004c390(DAT_1802f7c90 ^ 1,~bVar13 & 1);
        }
        lVar9 = FUN_180022c90(*puVar1,puVar1[3]);
        if (lVar9 == 0) goto LAB_18002d0a6;
        lVar9 = puVar1[6];
        if ((*(char *)(lVar9 + 1) == '\x01') && (DAT_1802f7cb8 == '\x01')) {
          if ((DAT_1802e9560 != '\x01') ||
             (((*(byte *)(lVar9 + 0x62) & 1) == 0 && ((*(byte *)(lVar9 + 99) & 1) == 0))))
          goto LAB_18002d070;
          uVar7 = *puVar1;
          uVar8 = FUN_180022c90(uVar7,puVar1[3]);
          uVar10 = FUN_180023f40(uVar7,puVar1[5]);
          lVar9 = FUN_180025b60(uVar7,uVar8);
          if ((lVar9 == 0) ||
             ((lVar11 = FUN_180025ad0(uVar7,uVar10), lVar11 != 0 ||
              (iVar6 = FUN_180026190(uVar7,lVar9), iVar6 == _DAT_1802e9540)))) goto LAB_18002d070;
          _DAT_1802e9540 = iVar6;
          lVar9 = FUN_1800261b0(uVar7,lVar9);
          if (lVar9 == 0) {
            uVar7 = FUN_18000a050(_DAT_180150338,_DAT_18015033c);
            cVar4 = FUN_18000aa30(0x1802f7cc0,uVar7,_DAT_180150340);
            if (cVar4 != '\0') goto LAB_18002d070;
          }
          FUN_18004c390(1,1);
          if (DAT_1802e9580 == '\x01') {
            uVar7 = FUN_18000a050(_DAT_180150350,_DAT_180150354);
            cVar4 = FUN_18000aa30(0x1802f7ca8,uVar7,_DAT_180150340);
            uVar20 = _DAT_180150358;
            uVar23 = _DAT_18015035c;
            if (cVar4 != '\0') {
              uVar20 = _DAT_180150360;
              uVar23 = _DAT_180150364;
            }
            uVar7 = FUN_18000a050(uVar20,uVar23);
            fVar21 = (float)FUN_18000a3e0(uVar7);
            dVar22 = (double)fVar21;
            goto LAB_18002d105;
          }
        }
        else {
          DAT_1802f7cb8 = *(char *)(lVar9 + 1) == '\x01';
LAB_18002d070:
          dVar22 = _DAT_180150368;
          if (DAT_1802e9580 != '\0') goto LAB_18002d105;
        }
        dVar22 = _DAT_180150348;
LAB_18002d105:
        _DAT_1802f7c98 = dVar22 + _DAT_1802f7c98;
        return;
      }
      if ((bVar13 & 1) == 0 && bVar12 == 0) goto LAB_18002d0a6;
      if (((_DAT_1802f7cd0 == 1) && (DAT_1802e95a0 != '\0')) ||
         ((DAT_1802e95c0 == '\x01' && (cVar4 = FUN_1800380b0(*puVar1,puVar1[5]), cVar4 == '\0')))) {
LAB_18002cee3:
        uVar23 = 0;
        uVar24 = 0;
        if (bVar12 == 0) goto LAB_18002d0a6;
LAB_18002d08a:
        FUN_18004c390(DAT_1802f7c90 ^ 1,~bVar13 & 1);
        uVar23 = 0;
        uVar24 = 0;
LAB_18002d0a6:
        _DAT_1802e9540 = 0xffffffff;
        _DAT_1802f7c98 = (double)CONCAT44(uVar24,uVar23);
        return;
      }
      if (DAT_1802e95e0 == '\x01') {
        cVar4 = FUN_180023f90(*puVar1,puVar1[5]);
        if ((cVar4 != '\0') || ((bVar13 & bVar12) != 0)) goto LAB_18002cee3;
      }
      else if ((bVar13 & bVar12) != 0) {
        bVar13 = 1;
        goto LAB_18002d08a;
      }
      if ((bVar13 & 1) == 0) {
        FUN_18004c390(DAT_1802f7c90 ^ 1,1);
        fVar14 = _DAT_1802e9618;
        if (DAT_1802e9638 == '\x01') {
          uVar8 = FUN_18000a050(_DAT_180150370,_DAT_180150374);
          fVar15 = (float)FUN_18000a510(0x1802f7ce8,uVar8,uVar7);
          uVar2 = _DAT_180150380;
          uVar8 = FUN_18000a050(_DAT_180150380,uVar20);
          fVar16 = (float)FUN_18000a510(0x1802f7d08,uVar8,_DAT_180150388);
          uVar8 = FUN_18000a050(uVar2,uVar20);
          fVar17 = (float)FUN_18000a510(0x1802f7d18,uVar8,uVar7);
          uVar8 = FUN_18000a050(_DAT_180150390,_DAT_180150394);
          fVar18 = (float)FUN_18000a510(0x1802f7d28,uVar8,_DAT_180150398);
          fVar19 = (float)FUN_18000ab00(0x1802f7cf8);
          fVar14 = fVar14 * (fVar16 + fVar21 + fVar17 + fVar18) * (fVar19 * fVar15 + fVar21);
        }
        if (_DAT_1802e9680 == 1) {
          if (DAT_1802f7d00 == '\x01') {
            afStack_ec[0] = 0.014;
            DAT_1802f7d00 = '\0';
          }
          else {
            afStack_ec[0] = (float)(_DAT_1801503c0 / (double)fVar14 + _DAT_1801503c8);
            uVar8 = FUN_180023170(*puVar1,puVar1[5]);
            fVar14 = (float)FUN_180009ee0(uVar8);
            fVar14 = fVar14 / fVar3 + 0.0;
            if ((*(longlong *)(puVar1[7] + 8) == 0) ||
               (_DAT_1801503b0 < *(double *)(puVar1[7] + 0x10))) {
              fVar14 = (float)((double)fVar14 + _DAT_1801503b8);
            }
            cVar4 = FUN_18002d3b0(afStack_ec,fVar14);
            if (cVar4 == '\0') {
              uVar8 = FUN_18000a050(_DAT_1801503d0,_DAT_1801503d4);
              bVar5 = FUN_18000aa30(0x1802f7cd8,uVar8,uVar7);
              DAT_1802f7d00 = FUN_18000a460((float)bVar5);
            }
          }
        }
        else {
          afStack_ec[0] = _DAT_1801503a4 / fVar14;
          uVar8 = FUN_180023170(*puVar1,puVar1[5]);
          fVar14 = (float)FUN_180009ee0(uVar8);
          fVar14 = fVar14 / fVar3 + 0.0;
          if ((*(longlong *)(puVar1[7] + 8) == 0) ||
             (_DAT_1801503b0 < *(double *)(puVar1[7] + 0x10))) {
            fVar14 = (float)((double)fVar14 + _DAT_1801503b8);
          }
          FUN_18002d3b0(afStack_ec,fVar14);
        }
        _DAT_1802f7ca0 = (double)afStack_ec[0];
        _DAT_1802f7c98 = _DAT_1802f7c98 + _DAT_1802f7ca0;
      }
      else {
        FUN_18004c390(DAT_1802f7c90 ^ 1,0);
        _DAT_1802f7c98 = _DAT_1802f7ca0 + _DAT_1802f7c98;
      }
      bVar13 = bVar13 ^ 1;
      bVar12 = bVar12 ^ 1;
    } while (_DAT_1802f7c98 <= 0.0);
  }
  return;
}

// CALLBACK RVA 0x2d140; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/auto_clicker/auto_clicker.c
// Differential report: analysis/module_behavior_recovery/auto_clicker/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2d140; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002d140(longlong param_1)

{
  undefined8 *puVar1;
  longlong lVar2;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  if (*(char *)(puVar1 + 8) == '\x01') {
    lVar2 = FUN_180022e10(*puVar1,puVar1[3]);
    if (lVar2 == 0) {
      _DAT_1802f7cd0 = 0;
    }
    else {
      _DAT_1802f7cd0 = FUN_180024b50(*puVar1,lVar2);
    }
  }
  return;
}

// UI RVA 0x2d190; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2d190; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18002d190(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_1801504f8);
  FUN_18000d040(param_2,param_1,0x1802e9650);
  FUN_18000cf30(param_2,param_1,0x1802e95e8);
  FUN_18000cef0(param_2,param_1,0x1802e9620);
  FUN_18000cef0(param_2,param_1,0x1802e9690);
  FUN_18000cef0(param_2,param_1,0x1802e9588);
  FUN_180013e90(param_1,param_2,&UNK_180150500);
  FUN_18000cef0(param_2,param_1,0x1802e9548);
  if (DAT_1802e9560 == '\x01') {
    FUN_18000cef0(param_2,param_1,0x1802e9568);
  }
  FUN_180013e90(param_1,param_2,&UNK_18015050a);
  FUN_18000cef0(param_2,param_1,0x1802e95a8);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802e95d8,0x1802e95c8,&DAT_1802e95e0);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x2d290; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2d290; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18002d290(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c6f0(param_1,&UNK_180150515,0x1802e9650);
  FUN_18000c450(param_1,&UNK_18015051d,0x1802e95e8);
  FUN_18000c3b0(param_1,&UNK_180150528,0x1802e9620);
  FUN_18000c3b0(param_1,&UNK_180150536,0x1802e9690);
  FUN_18000c3b0(param_1,&UNK_18015053e,0x1802e9588);
  FUN_18000c3b0(param_1,&UNK_180150550,0x1802e9548);
  FUN_18000c3b0(param_1,&UNK_180150560,0x1802e9568);
  FUN_18000c3b0(param_1,&UNK_180150574,0x1802e95a8);
  uVar1 = uRam00000001802e95e1;
  uVar2 = DAT_1802e95e0;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180150583,DAT_1802e95e0);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802e95e0;
      break;
    case 2:
      uRam00000001802e95e1 = DAT_1802e95e0;
      break;
    case 3:
      uVar2 = uRam00000001802e95e1;
    }
  }
  DAT_1802e95e0 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x2d370; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2d370; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002d370(undefined8 param_1)

{
  FUN_1800ab710(param_1,0x20,&UNK_18015059a,
                *(undefined8 *)((ulonglong)_DAT_1802e9680 * 8 + 0x1802e9640));
  return;
}

// CANDIDATE_LOCAL RVA 0x2d3b0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2d3b0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_18002d3b0(float *param_1,float param_2)

{
  char cVar1;
  int iVar2;
  undefined8 uVar3;
  float extraout_XMM0_Da;
  float fVar4;
  float fVar5;
  
  iVar2 = _DAT_1802f7d60;
  if (_DAT_1802f7d60 < 1) {
    if (DAT_1802e96a8 == '\x01') {
      cVar1 = FUN_18000aa30(0x1802f7d38,
                            CONCAT44((float)((double)param_2 + _DAT_1801503e0),
                                     (float)(_DAT_1801503d8 + (double)param_2)),_DAT_1801503e8);
      if (cVar1 != '\0') {
        uVar3 = FUN_18000a050(0,_DAT_1801503f0);
        fVar4 = (float)FUN_18000a3e0(uVar3);
        uVar3 = FUN_18000a050(_DAT_1801503f4,_DAT_1801503f8);
        fVar5 = (float)FUN_18000a510(0x1802f7d48,uVar3,_DAT_180150400);
        iVar2 = 3;
        if (fVar5 <= fVar4) {
          uVar3 = FUN_18000a050(_DAT_180150408,_DAT_18015040c);
          fVar5 = (float)FUN_18000a510(0x1802f7d48,uVar3,_DAT_180150400);
          iVar2 = (fVar4 < fVar5) + 1;
        }
        goto LAB_18002d3cc;
      }
    }
    uVar3 = 0;
  }
  else {
LAB_18002d3cc:
    _DAT_1802f7d60 = iVar2 + -1;
    FUN_18000ab00(0x1802f7d58);
    *param_1 = (float)((double)*param_1 + (double)extraout_XMM0_Da * _DAT_180150410 + _DAT_1801503d8
                      );
    uVar3 = 1;
  }
  return uVar3;
}

