// Recovered decompiler view: Auto Rod
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x43d80, 0x44940); proximity does not prove ownership.

// CALLBACK RVA 0x43d80; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/connected_auto_rod_access/connected_auto_rod_access.c
// Differential report: analysis/module_behavior_recovery/connected_auto_rod_access/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x43d80; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * FUN_180043d80(longlong param_1)

{
  longlong lVar1;
  undefined8 *puVar2;
  int iVar3;
  int iVar4;
  code *pcVar5;
  undefined *in_RAX;
  undefined8 uVar6;
  longlong lVar7;
  undefined *puVar8;
  longlong *plVar9;
  ulonglong uVar10;
  undefined8 unaff_RSI;
  int iVar11;
  int iVar12;
  int iVar13;
  float extraout_XMM0_Da;
  float extraout_XMM0_Da_00;
  float extraout_XMM0_Da_01;
  float fVar14;
  undefined8 uStack_78;
  undefined8 uStack_70;
  ulonglong uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  
  fVar14 = _DAT_180154a98;
  puVar2 = *(undefined8 **)(param_1 + 8);
  if (*(char *)(puVar2 + 8) == '\x01') {
    if (DAT_180304400 == '\0') {
      iVar11 = 0;
      do {
        if (((DAT_1802f3750 == '\x01') && (lVar7 = FUN_180022e10(*puVar2,puVar2[3]), lVar7 != 0)) &&
           (iVar3 = FUN_180024b50(*puVar2,lVar7), iVar3 == 2)) {
          if (_DAT_1802f3730 != -1) {
            uVar6 = FUN_180023f40(*puVar2,puVar2[5]);
            FUN_180025a80(*puVar2,uVar6);
            _DAT_1802f3730 = -1;
          }
LAB_1800441b2:
          in_RAX = (undefined *)FUN_18002aab0(0x1802f3520);
          goto code_r0x0001800441be;
        }
        if (_DAT_180304404 == 7) {
          if (_DAT_1802f3730 != -1) {
            uVar6 = FUN_180023f40(*puVar2,puVar2[5]);
            FUN_180025a80(*puVar2,uVar6,_DAT_1802f3730);
            _DAT_1802f3730 = -1;
          }
          in_RAX = (undefined *)FUN_18002aab0(0x1802f3520);
          goto LAB_1800442ef;
        }
        if (_DAT_180304410 != 0) {
          _DAT_180304410 = _DAT_180304410 - 1;
        }
        in_RAX = (undefined *)(ulonglong)_DAT_180304410;
        if ((0.0 < _DAT_18030440c) &&
           (_DAT_18030440c = _DAT_18030440c + fVar14, 0.0 < _DAT_18030440c)) break;
        uVar6 = FUN_180023f40(*puVar2,puVar2[5]);
        iVar3 = FUN_180025a60(*puVar2,uVar6);
        in_RAX = (undefined *)(ulonglong)_DAT_180304404;
        if ((1 < _DAT_180304404) && (iVar3 != _DAT_180304408)) goto LAB_1800441b2;
        if (5 < _DAT_180304404) break;
        in_RAX = &UNK_180154a9c + *(int *)(&UNK_180154a9c + (ulonglong)_DAT_180304404 * 4);
        switch(_DAT_180304404) {
        case 0:
          cRam0000000180304414 = '\0';
          iVar12 = 0;
          iVar13 = -1;
          do {
            lVar7 = FUN_180026140(*puVar2,uVar6);
            in_RAX = (undefined *)0x0;
            if (lVar7 != 0) {
              lVar7 = FUN_180025d10(*puVar2,lVar7);
              in_RAX = (undefined *)0x0;
              if (lVar7 != 0) {
                in_RAX = (undefined *)FUN_180025c50(*puVar2,lVar7);
                iVar4 = (int)in_RAX;
                if ((iVar4 == 0x14c) || (iVar4 == 0x158)) {
                  if (cRam00000001802f3770 == '\x01') {
                    cRam0000000180304414 = '\0';
                    goto code_r0x0001800440a0;
                  }
                }
                else if ((iVar4 == 0x15a) &&
                        (cRam0000000180304414 = '\x01', iVar13 = iVar12,
                        cRam00000001802f3770 == '\0')) goto code_r0x0001800440a0;
              }
            }
            iVar12 = iVar12 + 1;
          } while (iVar12 != 9);
          iVar12 = iVar13;
          if (iVar13 != -1) {
code_r0x0001800440a0:
            in_RAX = (undefined *)FUN_18002aa80(0x1802f3520);
            if ((char)in_RAX == '\0') goto code_r0x0001800441be;
            _DAT_1802f3730 = iVar3;
            _DAT_180304408 = iVar12;
            if ((cRam00000001802f3790 == '\x01') &&
               (iVar3 = FUN_1800380c0(puVar2,uVar6), iVar3 != -1)) {
              _DAT_1802f3730 = iVar3;
            }
            _DAT_180304404 = (_DAT_180304408 == _DAT_1802f3730) + 1;
            in_RAX = (undefined *)(ulonglong)_DAT_180304404;
            goto code_r0x000180044105;
          }
code_r0x0001800441be:
          _DAT_180304404 = 6;
          goto LAB_1800442e6;
        case 1:
          FUN_180025a80(*puVar2,uVar6);
          _DAT_180304404 = 2;
          DAT_180304415 = 0;
          break;
        case 2:
          cRam0000000180304414 = '\0';
          iVar13 = 0;
          iVar12 = -1;
          do {
            lVar7 = FUN_180026140(*puVar2,uVar6);
            puVar8 = (undefined *)0x0;
            if (lVar7 != 0) {
              lVar7 = FUN_180025d10(*puVar2,lVar7);
              puVar8 = (undefined *)0x0;
              if (lVar7 != 0) {
                puVar8 = (undefined *)FUN_180025c50(*puVar2,lVar7);
                iVar4 = (int)puVar8;
                if ((iVar4 == 0x14c) || (iVar4 == 0x158)) {
                  if (cRam00000001802f3770 == '\x01') {
                    cRam0000000180304414 = '\0';
                    iVar12 = iVar13;
                    goto joined_r0x000180044125;
                  }
                }
                else if ((iVar4 == 0x15a) &&
                        (cRam0000000180304414 = '\x01', iVar12 = iVar13,
                        cRam00000001802f3770 == '\0')) goto joined_r0x000180044125;
              }
            }
            iVar13 = iVar13 + 1;
          } while (iVar13 != 9);
          if (iVar12 == -1) {
            _DAT_180304404 = 5;
            return puVar8;
          }
joined_r0x000180044125:
          if (iVar12 == iVar3) {
            uVar6 = FUN_180022cf0(*puVar2,puVar2[3]);
            uVar6 = FUN_180024f90(*puVar2,uVar6);
            FUN_1800253e0(*puVar2,uVar6);
            if (cRam0000000180304414 == '\x01') {
              _DAT_180304404 = 3;
              _DAT_180304410 = FUN_180044660(puVar2);
code_r0x0001800442c8:
              in_RAX = (undefined *)FUN_1800445a0();
              fVar14 = extraout_XMM0_Da_01;
            }
            else {
              if (DAT_1802f3540 != '\x01') {
                _DAT_180304404 = 5;
                goto code_r0x0001800442c8;
              }
              in_RAX = (undefined *)FUN_180044860();
              fVar14 = extraout_XMM0_Da_00;
            }
            _DAT_18030440c = fVar14 + _DAT_18030440c;
            goto LAB_1800442dd;
          }
          _DAT_180304404 = 1;
          _DAT_180304408 = iVar12;
          break;
        case 3:
          if (_DAT_180304410 != 0) goto LAB_1800442dd;
          _DAT_180304404 = _DAT_1802f3730 == _DAT_180304408 ^ 5;
          break;
        case 4:
          puVar8 = (undefined *)
                   FUN_180025a80(*puVar2,uVar6,_DAT_1802f3730 + ((_DAT_1802f3730 + 1) / 9) * -9 + 1)
          ;
          _DAT_180304404 = 5;
          return puVar8;
        case 5:
          _DAT_180304404 = 6;
          if (_DAT_1802f3730 != -1) {
            uVar6 = FUN_180023f40(*puVar2,puVar2[5]);
            FUN_180025a80(*puVar2,uVar6);
            _DAT_1802f3730 = -1;
          }
          FUN_18002aab0(0x1802f3520);
          goto code_r0x0001800442c8;
        }
        in_RAX = (undefined *)FUN_1800445a0();
        _DAT_18030440c = extraout_XMM0_Da + _DAT_18030440c;
code_r0x000180044105:
        iVar11 = iVar11 + 1;
      } while (iVar11 != 3);
LAB_1800442dd:
      if (_DAT_180304404 == 6) {
LAB_1800442e6:
        if (DAT_1802f3540 != '\x01') {
          lVar7 = puVar2[1];
          uVar10 = CONCAT71((int7)((ulonglong)unaff_RSI >> 8),1);
          if (cRam00000001802f3534 != '\0') {
            uStack_48 = 0;
            uStack_58 = 0;
            uStack_50 = 0;
            uStack_68 = 0;
            uStack_60 = 0;
            uStack_78 = 4;
            uStack_70 = 0x1802f3520;
            plVar9 = *(longlong **)(lVar7 + 0x230);
            pcVar5 = (code *)*plVar9;
            if (pcVar5 != (code *)0x0) {
              do {
                plVar9 = plVar9 + 1;
                (*pcVar5)(&uStack_78);
                pcVar5 = (code *)*plVar9;
              } while (pcVar5 != (code *)0x0);
              if ((uStack_68 & 1) != 0) {
                uVar10 = 0;
                goto LAB_1800285a1;
              }
            }
            lVar1 = *(longlong *)(lVar7 + 0x300);
            *(undefined8 *)(*(longlong *)(lVar7 + 0x2f8) + lVar1 * 8) = 0x1802f3520;
            *(longlong *)(lVar7 + 0x300) = lVar1 + 1;
          }
LAB_1800285a1:
          return (undefined *)(uVar10 & 0xffffffff);
        }
LAB_1800442ef:
        _DAT_180304404 = 0;
      }
    }
    else {
      if (_DAT_1802f3730 != -1) {
        uVar6 = FUN_180023f40(*puVar2,puVar2[5]);
        FUN_180025a80(*puVar2,uVar6,_DAT_1802f3730);
        _DAT_1802f3730 = -1;
      }
      FUN_18002aab0(0x1802f3520);
      in_RAX = (undefined *)FUN_1800284f0(puVar2[1],0x1802f3520,0);
      DAT_180304400 = '\0';
    }
  }
  return in_RAX;
}

// CALLBACK RVA 0x44340; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/connected_auto_rod_access/connected_auto_rod_access.c
// Differential report: analysis/module_behavior_recovery/connected_auto_rod_access/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x44340; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180044340(longlong param_1)

{
  if ((DAT_180304400 == '\0') && (*(longlong *)(param_1 + 8) == 0x1802f3520)) {
    if (DAT_1802f3540 == '\x01') {
      DAT_180304400 = '\x01';
    }
    else {
      if (_DAT_180304404 == 6) {
        return;
      }
      if (_DAT_180304404 == 3) {
        _DAT_180304404 = 7;
      }
    }
    *(undefined1 *)(param_1 + 0x10) = 1;
    return;
  }
  return;
}

// CALLBACK RVA 0x44390; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/connected_auto_rod_access/connected_auto_rod_access.c
// Differential report: analysis/module_behavior_recovery/connected_auto_rod_access/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x44390; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180044390(longlong param_1)

{
  if ((*(longlong *)(param_1 + 0x10) == 0x1802f3520) && (*(char *)(param_1 + 0x18) == '\x01')) {
    _DAT_180304404 = 0;
    return;
  }
  return;
}

// CALLBACK RVA 0x443c0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/connected_auto_rod_access/connected_auto_rod_access.c
// Differential report: analysis/module_behavior_recovery/connected_auto_rod_access/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x443c0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_1800443c0(longlong param_1)

{
  undefined8 *puVar1;
  int iVar2;
  longlong lVar3;
  
  if (*(char *)(param_1 + 0x10) == '\0') {
    puVar1 = *(undefined8 **)(param_1 + 8);
    lVar3 = FUN_180028a50(*puVar1,puVar1[5]);
    if (lVar3 != 0) {
      iVar2 = FUN_180025c50(*puVar1,lVar3);
      if (iVar2 == 0x15a) {
        if (DAT_180304415 == '\0') {
          DAT_180304415 = '\x01';
        }
        else {
          *(undefined1 *)(param_1 + 0x11) = 1;
        }
      }
    }
  }
  return;
}

// UI RVA 0x44420; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x44420; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180044420(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180154bf5);
  FUN_18000cf30(param_2,param_1,0x1802f37f0);
  FUN_18000cf30(param_2,param_1,0x1802f3798);
  FUN_18000cef0(param_2,param_1,0x1802f37d0);
  FUN_18000cef0(param_2,param_1,0x1802f3778);
  FUN_180013e90(param_1,param_2,&UNK_180154bfa);
  FUN_18000cef0(param_2,param_1,0x1802f3758);
  FUN_18000cf30(param_2,param_1,0x1802f3828);
  FUN_180013e90(param_1,param_2,&UNK_180154bf5);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802f3748,0x1802f3738,&DAT_1802f3750);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x444f0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x444f0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_1800444f0(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c450(param_1,&UNK_180154c05,0x1802f37f0);
  FUN_18000c450(param_1,&UNK_180154c13,0x1802f3798);
  FUN_18000c3b0(param_1,&UNK_180154c19,0x1802f37d0);
  FUN_18000c3b0(param_1,&UNK_180154c2a,0x1802f3778);
  FUN_18000c3b0(param_1,&UNK_180154c42,0x1802f3758);
  FUN_18000c450(param_1,&UNK_180154c53,0x1802f3828);
  uVar1 = uRam00000001802f3751;
  uVar2 = DAT_1802f3750;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180154c5f,DAT_1802f3750);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802f3750;
      break;
    case 2:
      uRam00000001802f3751 = DAT_1802f3750;
      break;
    case 3:
      uVar2 = uRam00000001802f3751;
    }
  }
  DAT_1802f3750 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x445a0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x445a0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float FUN_1800445a0(void)

{
  undefined8 uVar1;
  char cVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar4 = _DAT_1802f37c8;
  fVar5 = _DAT_1802f37c8;
  if (DAT_1802f37e8 == '\x01') {
    uVar1 = FUN_18000a050(0,_DAT_180154ab8);
    fVar3 = (float)FUN_18000a510(0x180304418,uVar1,_DAT_180154ac0);
    fVar5 = 0.0;
    if (0.0 <= fVar4 - fVar3) {
      fVar5 = fVar4 - fVar3;
    }
    uVar1 = FUN_18000a050(_DAT_180154ac8,_DAT_180154acc);
    cVar2 = FUN_18000aa30(0x180304428,uVar1,_DAT_180154ad0);
    if (cVar2 != '\0') {
      uVar1 = FUN_18000a050(_DAT_180154ab8,_DAT_180154ad8);
      fVar4 = (float)FUN_18000a3e0(uVar1);
      fVar5 = fVar5 + fVar4;
    }
  }
  return fVar5;
}

// CANDIDATE_LOCAL RVA 0x44660; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x44660; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_180044660(undefined8 *param_1)

{
  longlong lVar1;
  double dVar2;
  char cVar3;
  float fVar4;
  undefined4 uVar5;
  undefined1 auStack_168 [24];
  undefined1 auStack_150 [24];
  undefined1 auStack_138 [24];
  undefined1 auStack_120 [24];
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined8 uStack_f8;
  undefined4 uStack_f0;
  undefined4 uStack_ec;
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined8 uStack_98;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined8 uStack_78;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined8 uStack_48;
  
  lVar1 = *(longlong *)(param_1[7] + 8);
  if (lVar1 == 0) {
    fVar4 = _DAT_180154af0 / _DAT_1802f3820;
  }
  else {
    FUN_180023030(&uStack_58,*param_1,param_1[5]);
    cVar3 = FUN_180023020(*param_1);
    if (cVar3 == '\0') {
      uStack_c8 = uStack_48;
      FUN_180009590(&uStack_88,&uStack_d8);
      uStack_58 = uStack_88;
      uStack_54 = uStack_84;
      uStack_50 = uStack_80;
      uStack_4c = uStack_7c;
      uStack_48 = uStack_78;
    }
    FUN_180024160(&uStack_f0,*param_1,lVar1);
    uVar5 = (undefined4)_DAT_180154ae0;
    FUN_1800093b0(auStack_150,uVar5,0,uVar5);
    uStack_78 = uStack_e0;
    uStack_88 = uStack_f0;
    uStack_84 = uStack_ec;
    uStack_80 = uStack_e8;
    uStack_7c = uStack_e4;
    FUN_1800093d0(auStack_168,&uStack_88,auStack_150);
    FUN_1800093b0(auStack_120,uVar5,(int)_DAT_180154ae8,uVar5);
    uStack_78 = uStack_e0;
    uStack_88 = uStack_f0;
    uStack_84 = uStack_ec;
    uStack_80 = uStack_e8;
    uStack_7c = uStack_e4;
    FUN_180009400(auStack_138,&uStack_88,auStack_120);
    FUN_1800096b0(&uStack_88,auStack_168,auStack_138);
    uStack_d8 = CONCAT44(uStack_84,uStack_88);
    uStack_d0 = CONCAT44(uStack_7c,uStack_80);
    uStack_b8 = uStack_68;
    uStack_b4 = uStack_64;
    uStack_b0 = uStack_60;
    uStack_ac = uStack_5c;
    uStack_c8 = uStack_78;
    uStack_c0 = uStack_70;
    uStack_bc = uStack_6c;
    uStack_98 = uStack_48;
    uStack_a8 = uStack_58;
    uStack_a4 = uStack_54;
    uStack_a0 = uStack_50;
    uStack_9c = uStack_4c;
    FUN_180009880(&uStack_108,&uStack_d8,&uStack_a8);
    uStack_c8 = uStack_48;
    uStack_d8 = CONCAT44(uStack_54,uStack_58);
    uStack_d0 = CONCAT44(uStack_4c,uStack_50);
    uStack_98 = uStack_f8;
    uStack_a8 = uStack_108;
    uStack_a4 = uStack_104;
    uStack_a0 = uStack_100;
    uStack_9c = uStack_fc;
    dVar2 = (double)FUN_1800094f0(&uStack_d8,&uStack_a8);
    fVar4 = (float)(dVar2 / (double)_DAT_1802f3820);
  }
  fVar4 = (float)func_0x0001800b2920(fVar4);
  return (int)fVar4;
}

// CANDIDATE_LOCAL RVA 0x44860; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x44860; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float FUN_180044860(void)

{
  undefined8 uVar1;
  char cVar2;
  float fVar3;
  float fVar4;
  
  fVar4 = _DAT_1802f3858;
  if (DAT_1802f37e8 == '\0') {
    fVar4 = _DAT_180154af8 / _DAT_1802f3858;
  }
  else {
    uVar1 = FUN_18000a050(_DAT_180154afc,_DAT_180154b00);
    fVar3 = (float)FUN_18000a510(0x180304438,uVar1,_DAT_180154b08);
    fVar4 = _DAT_180154af8 / (fVar4 * fVar3);
    uVar1 = FUN_18000a050(_DAT_180154b10,_DAT_180154b14);
    cVar2 = FUN_18000aa30(0x180304448,uVar1,_DAT_180154b18);
    if (cVar2 != '\0') {
      uVar1 = FUN_18000a050(_DAT_180154b00,_DAT_180154b20);
      fVar3 = (float)FUN_18000a3e0(uVar1);
      fVar4 = fVar4 + fVar3;
    }
  }
  return fVar4;
}

