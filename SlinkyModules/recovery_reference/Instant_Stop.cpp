// Recovered decompiler view: Instant Stop
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x42650, 0x42a20); proximity does not prove ownership.

// CALLBACK RVA 0x42650; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/instant_stop/instant_stop.c
// Differential report: analysis/module_behavior_recovery/instant_stop/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x42650; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180042650(longlong param_1)

{
  undefined8 *puVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  char cVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  float fVar15;
  double dStack_128;
  undefined8 uStack_120;
  double dStack_118;
  double dStack_110;
  undefined8 uStack_108;
  double dStack_100;
  double dStack_f8;
  undefined8 uStack_f0;
  double dStack_e8;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  double dStack_c8;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  double dStack_a8;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  cVar5 = FUN_180022e60(*puVar1,puVar1[3]);
  uVar12 = 0;
  if (cVar5 != '\0') {
    uVar7 = FUN_180022cf0(*puVar1,puVar1[3]);
    uVar8 = FUN_1800250d0(*puVar1,uVar7);
    uVar9 = FUN_180025120(*puVar1,uVar7);
    uVar10 = FUN_180025170(*puVar1,uVar7);
    uVar11 = FUN_1800251c0(*puVar1,uVar7);
    uVar7 = *puVar1;
    if (_DAT_1803043d0 == 2) {
      uVar6 = FUN_180025490(uVar7,uVar9);
      FUN_180025460(uVar7,uVar9,uVar6);
      uVar7 = *puVar1;
      uVar6 = FUN_180025490(uVar7,uVar10);
      FUN_180025460(uVar7,uVar10,uVar6);
      uVar7 = *puVar1;
      uVar6 = FUN_180025490(uVar7,uVar11);
      FUN_180025460(uVar7,uVar11,uVar6);
    }
    else if (_DAT_1803043d0 == 1) {
      cVar5 = FUN_180025430(uVar7,uVar8);
      if (cVar5 != '\0') {
        return;
      }
      cVar5 = FUN_180023780(*puVar1,puVar1[5]);
      if (cVar5 == '\0') {
        return;
      }
      FUN_180023550(&dStack_110,*puVar1,puVar1[5]);
      uVar7 = FUN_180023170(*puVar1,puVar1[5]);
      fVar15 = (float)FUN_180023b40(*puVar1,puVar1[5]);
      cVar5 = FUN_180023690(*puVar1,puVar1[5]);
      dVar4 = dStack_100;
      dVar3 = dStack_110;
      uVar6 = _DAT_1801547b0;
      if (cVar5 != '\0') {
        fVar15 = (float)((double)fVar15 / _DAT_1801547a8);
      }
      FUN_180029290(&uStack_b8,uVar7,_DAT_1801547b0,_DAT_1801547b0,fVar15);
      dStack_e8 = dStack_100;
      dStack_f8 = dStack_110;
      uStack_f0 = uStack_108;
      dStack_c8 = dStack_a8;
      uStack_d8 = (undefined4)uStack_b8;
      uStack_d4 = uStack_b8._4_4_;
      uStack_d0 = (undefined4)uStack_b0;
      uStack_cc = uStack_b0._4_4_;
      FUN_180009400(&dStack_128,&dStack_f8,&uStack_d8);
      dStack_a8 = dStack_118;
      uStack_b8 = dStack_128;
      uStack_b0 = uStack_120;
      dVar2 = dStack_128 * dStack_128 + dStack_118 * dStack_118;
      dVar3 = dVar3 * dVar3 + dVar4 * dVar4;
      dVar4 = dVar2;
      if (dVar3 <= dVar2) {
        dVar4 = dVar3;
      }
      uVar13 = -(uint)(dVar2 < dVar3) | 999;
      FUN_180029290(&uStack_b8,uVar7,uVar6,0,fVar15);
      dStack_e8 = dStack_100;
      dStack_f8 = dStack_110;
      uStack_f0 = uStack_108;
      dStack_c8 = dStack_a8;
      uStack_d8 = (undefined4)uStack_b8;
      uStack_d4 = uStack_b8._4_4_;
      uStack_d0 = (undefined4)uStack_b0;
      uStack_cc = uStack_b0._4_4_;
      FUN_180009400(&dStack_128,&dStack_f8,&uStack_d8);
      dStack_a8 = dStack_118;
      uStack_b8 = dStack_128;
      uStack_b0 = uStack_120;
      dVar3 = dStack_128 * dStack_128 + dStack_118 * dStack_118;
      uVar12 = 0;
      if (dVar3 < dVar4) {
        uVar13 = uVar12;
        dVar4 = dVar3;
      }
      FUN_180029290(&uStack_b8,uVar7,uVar6,_DAT_1801547b4,fVar15);
      dStack_e8 = dStack_100;
      dStack_f8 = dStack_110;
      uStack_f0 = uStack_108;
      dStack_c8 = dStack_a8;
      uStack_d8 = (undefined4)uStack_b8;
      uStack_d4 = uStack_b8._4_4_;
      uStack_d0 = (undefined4)uStack_b0;
      uStack_cc = uStack_b0._4_4_;
      FUN_180009400(&dStack_128,&dStack_f8,&uStack_d8);
      dStack_a8 = dStack_118;
      uStack_b8 = dStack_128;
      uStack_b0 = uStack_120;
      dVar3 = dStack_128 * dStack_128 + dStack_118 * dStack_118;
      uVar14 = 1;
      if (dVar4 <= dVar3) {
        uVar14 = uVar13;
      }
      if (uVar14 != 999) {
        FUN_180025460(*puVar1,uVar9,1);
        FUN_180025460(*puVar1,uVar10,dVar3 < dVar4);
        FUN_180025460(*puVar1,uVar11,uVar14 == 0xffffffff);
        uVar12 = 2;
      }
    }
    else {
      cVar5 = FUN_180025430(uVar7,uVar8);
      uVar12 = 1;
      if (cVar5 == '\0') {
        return;
      }
    }
  }
  _DAT_1803043d0 = uVar12;
  return;
}

