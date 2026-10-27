// Recovered decompiler view: Fast Place
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x2fbc0, 0x2ffb0); proximity does not prove ownership.

// CALLBACK RVA 0x2fbc0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/fast_place/fast_place.c
// Differential report: analysis/module_behavior_recovery/fast_place/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2fbc0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002fbc0(longlong param_1)

{
  undefined8 *puVar1;
  double dVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  byte bVar5;
  char cVar6;
  int iVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  longlong lVar10;
  longlong lVar11;
  undefined8 uVar12;
  byte bVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined1 auStack_1a8 [24];
  undefined1 auStack_190 [24];
  undefined8 uStack_178;
  undefined8 uStack_170;
  undefined8 uStack_168;
  undefined8 uStack_160;
  undefined8 uStack_158;
  undefined8 uStack_150;
  undefined4 uStack_148;
  undefined4 uStack_144;
  undefined4 uStack_140;
  undefined4 uStack_13c;
  undefined4 uStack_138;
  undefined4 uStack_134;
  undefined4 uStack_130;
  undefined4 uStack_12c;
  undefined4 uStack_128;
  undefined4 uStack_124;
  undefined4 uStack_120;
  undefined4 uStack_11c;
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  undefined4 uStack_e0;
  undefined4 uStack_dc;
  undefined8 uStack_d8;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined8 uStack_a0;
  
  if (((_DAT_1802f9d60 <= 0.0) ||
      (_DAT_1802f9d60 = _DAT_1802f9d60 + _DAT_180150ce8, _DAT_1802f9d60 <= 0.0)) &&
     (puVar1 = *(undefined8 **)(param_1 + 8), *(char *)(puVar1 + 8) == '\x01')) {
    uVar8 = FUN_180022cf0(*puVar1,puVar1[3]);
    uVar8 = FUN_180024f90(*puVar1,uVar8);
    bVar5 = FUN_180025490(*puVar1,uVar8);
    bVar13 = DAT_1802f9d64;
    DAT_1802f9d64 = bVar5;
    if (bVar5 == 0) {
      _DAT_1802f9d68 = (int)_DAT_1802ea548;
    }
    else if (_DAT_1802f9d68 < 1) {
      iVar7 = FUN_180025360(*puVar1,uVar8);
      uVar4 = _DAT_180150d04;
      uVar3 = _DAT_180150d00;
      dVar2 = _DAT_180150cf0;
      if ((iVar7 < 1) && (_DAT_1802f9d60 <= 0.0)) {
        bVar13 = bVar13 ^ 1;
        uVar14 = SUB84(_DAT_180150cf0,0);
        uVar15 = (undefined4)_DAT_180150cf8;
        do {
          _DAT_1802f9d60 = (float)((double)_DAT_1802f9d60 + dVar2 / (double)_DAT_1802ea510);
          if ((bVar13 & 1) == 0) {
            uVar12 = *puVar1;
            uVar9 = FUN_180028a50(uVar12,puVar1[5]);
            cVar6 = FUN_180028b00(uVar12,uVar9);
            if (cVar6 != '\0') {
              lVar10 = FUN_180022e10(*puVar1,puVar1[3]);
              if ((lVar10 == 0) || (iVar7 = FUN_180024b50(*puVar1,lVar10), iVar7 != 1)) {
LAB_18002fead:
                uVar12 = FUN_18000a050(uVar3,uVar4);
                cVar6 = FUN_18000aa30(0x1802f9d70,uVar12,uVar14);
                if (cVar6 == '\0') goto LAB_18002fd2d;
              }
              else {
                lVar11 = FUN_180028a50(*puVar1,puVar1[5]);
                if ((lVar11 == 0) || (iVar7 = FUN_180025c50(*puVar1,lVar11), iVar7 != 0x41)) {
                  FUN_180024d80(&uStack_b0,*puVar1,lVar10);
                  FUN_1800093b0(auStack_190,uVar15,uVar15,uVar15);
                  uStack_108 = uStack_a0;
                  uStack_118 = uStack_b0;
                  uStack_114 = uStack_ac;
                  uStack_110 = uStack_a8;
                  uStack_10c = uStack_a4;
                  FUN_180009400(auStack_1a8,&uStack_118,auStack_190);
                  uStack_d8 = uStack_a0;
                  uStack_e8 = uStack_b0;
                  uStack_e4 = uStack_ac;
                  uStack_e0 = uStack_a8;
                  uStack_dc = uStack_a4;
                  FUN_1800096b0(&uStack_118,&uStack_e8,auStack_1a8);
                  uVar12 = *puVar1;
                  uVar9 = FUN_180023670(uVar12,puVar1[5]);
                  FUN_180025640(&uStack_e8,uVar12,uVar9);
                  uStack_178 = CONCAT44(uStack_114,uStack_118);
                  uStack_170 = CONCAT44(uStack_10c,uStack_110);
                  uStack_158 = uStack_f8;
                  uStack_150 = uStack_f0;
                  uStack_168 = uStack_108;
                  uStack_160 = uStack_100;
                  uStack_128 = uStack_c8;
                  uStack_124 = uStack_c4;
                  uStack_120 = uStack_c0;
                  uStack_11c = uStack_bc;
                  uStack_138 = (undefined4)uStack_d8;
                  uStack_134 = uStack_d8._4_4_;
                  uStack_130 = uStack_d0;
                  uStack_12c = uStack_cc;
                  uStack_148 = uStack_e8;
                  uStack_144 = uStack_e4;
                  uStack_140 = uStack_e0;
                  uStack_13c = uStack_dc;
                  cVar6 = FUN_1800097d0(&uStack_178,&uStack_148);
                  if (cVar6 != '\0') goto LAB_18002fead;
                }
              }
              FUN_180025380(*puVar1,uVar8);
            }
          }
LAB_18002fd2d:
          bVar13 = 0;
        } while (_DAT_1802f9d60 <= 0.0);
      }
    }
    else {
      _DAT_1802f9d68 = _DAT_1802f9d68 + -1;
    }
  }
  return;
}

// UI RVA 0x2fee0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2fee0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18002fee0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  undefined8 unaff_RBP;
  undefined8 unaff_RDI;
  undefined4 uVar2;
  
  uVar2 = (undefined4)((ulonglong)unaff_RDI >> 0x20);
  FUN_180013e90(param_1,param_2,&UNK_180150d5f);
  FUN_18000cf30(param_2,param_1,0x1802ea4e0);
  cVar1 = FUN_180013f40(param_1,param_2,uRam00000001802ea528,uRam00000001802ea530,0x1802ea518,
                        uRam00000001802ea540,uRam00000001802ea544,uRam00000001802ea538,
                        CONCAT44(uVar2,uRam00000001802ea53c),&DAT_1802ea548,unaff_RBP);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x2ff30; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2ff30; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002ff30(undefined8 *param_1)

{
  double dVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  undefined8 uVar6;
  longlong lVar7;
  float fVar8;
  
  FUN_18000c450(param_1,&UNK_180150d64,0x1802ea4e0);
  fVar4 = _DAT_1802ea548;
  if (*(char *)((longlong)param_1 + 0xc) == '\0') {
    switch(*(undefined4 *)(param_1 + 1)) {
    case 0:
      uVar6 = FUN_18004e4d0(*param_1);
      fVar4 = fRam00000001802ea54c;
      fVar3 = fRam00000001802ea544;
      fVar2 = fRam00000001802ea540;
      iVar5 = FUN_18004d150(uVar6);
      if (iVar5 != 0) {
        dVar1 = (double)FUN_18004d130(uVar6);
        fVar8 = (float)dVar1;
        fVar4 = fVar2;
        if ((fVar2 <= fVar8) && (fVar4 = fVar8, fVar3 < fVar8)) {
          fVar4 = fVar3;
        }
      }
      break;
    case 1:
      lVar7 = FUN_18004eeb0(*param_1,&UNK_180150d6c,(double)_DAT_1802ea548);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar7 == 0;
      fVar4 = _DAT_1802ea548;
      break;
    case 2:
      fRam00000001802ea54c = _DAT_1802ea548;
      break;
    case 3:
      fVar4 = fRam00000001802ea54c;
    }
  }
  _DAT_1802ea548 = fVar4;
  return;
}

// CANDIDATE_LOCAL RVA 0x2ff70; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x2ff70; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18002ff70(void)

{
  FUN_1800ab710(_DAT_1802ea510,0x20,&UNK_180150d7b,(double)_DAT_1802ea510);
  return;
}

