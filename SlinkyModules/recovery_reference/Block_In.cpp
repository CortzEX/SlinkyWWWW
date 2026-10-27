// Recovered decompiler view: Block In
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x4abf0, 0x4bbc0); proximity does not prove ownership.

// CALLBACK RVA 0x4abf0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/block_in_events/block_in_events.c
// Differential report: analysis/module_behavior_recovery/block_in_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x4abf0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18004abf0(void)

{
  return;
}

// CALLBACK RVA 0x4ac00; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/block_in_events/block_in_events.c
// Differential report: analysis/module_behavior_recovery/block_in_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x4ac00; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18004ac00(longlong param_1)

{
  undefined8 *puVar1;
  longlong *plVar2;
  float fVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  
  if (*(longlong *)(param_1 + 0x10) == 0x1802f6108) {
    puVar1 = *(undefined8 **)(param_1 + 8);
    if (*(char *)(param_1 + 0x18) != '\x01') {
      uVar5 = FUN_180022cf0(*puVar1,puVar1[3]);
      uVar6 = FUN_1800250d0(*puVar1,uVar5);
      uVar7 = FUN_180025120(*puVar1,uVar5);
      uVar8 = FUN_180025170(*puVar1,uVar5);
      uVar9 = FUN_1800251c0(*puVar1,uVar5);
      uVar5 = *puVar1;
      uVar4 = FUN_180025490(uVar5,uVar6);
      FUN_180025460(uVar5,uVar6,uVar4);
      uVar5 = *puVar1;
      uVar4 = FUN_180025490(uVar5,uVar7);
      FUN_180025460(uVar5,uVar7,uVar4);
      uVar5 = *puVar1;
      uVar4 = FUN_180025490(uVar5,uVar8);
      FUN_180025460(uVar5,uVar8,uVar4);
      plVar2 = (longlong *)*puVar1;
      uVar4 = FUN_180025490(plVar2,uVar9);
                    /* WARNING: Could not recover jumptable at 0x000180025480. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*(longlong *)plVar2[1] + 0x348))
                ((longlong *)plVar2[1],uVar9,*(undefined8 *)(*plVar2 + 0x478),uVar4);
      return;
    }
    _DAT_180304b10 = 0;
    fVar3 = (float)FUN_180023170(*puVar1,puVar1[5]);
    fVar3 = (float)func_0x0001800b1fb0(fVar3 / _DAT_180156870);
    _DAT_180304b18 = (int)fVar3 % 4;
  }
  return;
}

// CALLBACK RVA 0x4ad50; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/block_in_events/block_in_events.c
// Differential report: analysis/module_behavior_recovery/block_in_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x4ad50; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18004ad50(longlong param_1)

{
  if ((DAT_180304b1c == '\x01') && (*(undefined2 *)(param_1 + 8) = 0x101, _DAT_180304b20 == 1)) {
    *(undefined8 *)(param_1 + 0xc) = _DAT_180304b28;
  }
  return;
}

// CALLBACK RVA 0x4ad80; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/block_in_events/block_in_events.c
// Differential report: analysis/module_behavior_recovery/block_in_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x4ad80; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18004ad80(longlong param_1)

{
  longlong *plVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  
  if (_DAT_180304b20 != 0) {
    puVar2 = *(undefined8 **)(param_1 + 8);
    uVar3 = FUN_180022cf0(*puVar2,puVar2[3]);
    uVar4 = FUN_1800250d0(*puVar2,uVar3);
    uVar5 = FUN_180025120(*puVar2,uVar3);
    uVar6 = FUN_180025170(*puVar2,uVar3);
    uVar3 = FUN_1800251c0(*puVar2,uVar3);
    FUN_180025460(*puVar2,uVar4,_DAT_180304b20 == 1);
    FUN_180025460(*puVar2,uVar5,0);
    FUN_180025460(*puVar2,uVar6,0);
    plVar1 = (longlong *)((longlong *)*puVar2)[1];
                    /* WARNING: Could not recover jumptable at 0x000180025480. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar1 + 0x348))(plVar1,uVar3,*(undefined8 *)(*(longlong *)*puVar2 + 0x478),0);
    return;
  }
  return;
}

// CALLBACK RVA 0x4ae50; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/block_in_update/block_in_update.c
// Differential report: analysis/module_behavior_recovery/block_in_update/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x4ae50; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18004ae50(longlong param_1)

{
  char cVar1;
  int iVar2;
  byte bVar3;
  char cVar4;
  uint uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  ulonglong uVar10;
  sbyte sVar11;
  undefined8 *puVar12;
  int iVar13;
  char *pcVar14;
  int iVar15;
  longlong lVar16;
  int iVar17;
  float fVar18;
  float fVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  ulonglong uVar23;
  double dVar24;
  undefined4 uVar25;
  uint uVar26;
  undefined1 auStack_210 [24];
  undefined8 uStack_1f8;
  double dStack_1f0;
  undefined8 uStack_1e8;
  undefined4 uStack_1e0;
  undefined4 uStack_1dc;
  undefined8 uStack_1d8;
  undefined8 uStack_1d0;
  undefined8 uStack_1c0;
  double dStack_1b8;
  undefined8 uStack_1b0;
  undefined8 uStack_1a8;
  undefined8 uStack_1a0;
  undefined8 uStack_198;
  longlong lStack_190;
  ulonglong uStack_188;
  ulonglong uStack_180;
  ulonglong uStack_178;
  ulonglong uStack_170;
  undefined8 uStack_168;
  double dStack_160;
  undefined8 uStack_158;
  undefined4 uStack_150;
  undefined4 uStack_14c;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined1 auStack_138 [16];
  double dStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 *puStack_100;
  int iStack_f8;
  int iStack_f4;
  ulonglong uStack_f0;
  undefined8 uStack_e8;
  double dStack_e0;
  undefined8 uStack_d8;
  int iStack_cc;
  undefined8 uStack_c8;
  byte bStack_b9;
  
  DAT_180304b1c = 0;
  _DAT_180304b20 = 0;
  puVar12 = *(undefined8 **)(param_1 + 8);
  if ((*(char *)(puVar12 + 8) == '\x01') &&
     (bVar3 = FUN_180023780(*puVar12,puVar12[5]), ((~DAT_1802f6330 | bVar3) & 1) != 0)) {
    bStack_b9 = bVar3;
    FUN_180023030(&uStack_e8,*puVar12,puVar12[5]);
    cVar4 = FUN_180023020(*puVar12);
    if (cVar4 != '\0') {
      uStack_158 = uStack_d8;
      uStack_168 = uStack_e8;
      dStack_160 = dStack_e0;
      FUN_1800095c0(&uStack_1c0,&uStack_168);
      uStack_e8 = uStack_1c0;
      dStack_e0 = dStack_1b8;
      uStack_d8 = uStack_1b0;
    }
    dVar24 = dStack_e0;
    dVar20 = (double)func_0x0001800b29b0(uStack_e8);
    dVar21 = (double)func_0x0001800b29b0(dVar24);
    dVar21 = dVar21 + _DAT_180156880;
    dVar22 = (double)func_0x0001800b29b0(uStack_d8);
    if (_DAT_1801568a0 < (double)((ulonglong)(dVar24 - _DAT_180304b30) & _DAT_180156890)) {
      _DAT_180304b10 = 0;
    }
    uVar26 = (uint)dVar21;
    _DAT_180304b30 = dVar24;
    if (**(int **)*puVar12 == 0) {
      uStack_c8 = 0;
    }
    else {
      uStack_c8 = FUN_1800242c0((undefined8 *)*puVar12,0,0,0);
    }
    pcVar14 = "";
    lVar16 = 0;
    do {
      if (((_DAT_180304b10 >> ((byte)lVar16 & 0x3f)) >> 0x20 & 1) != 0) {
LAB_18004b41c:
        if ((lVar16 - 1U < 4) || (lVar16 != 0)) {
                    /* WARNING: Could not recover jumptable at 0x00018004b43a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
          (*(code *)(&UNK_180156944 + *(int *)(&UNK_180156944 + (lVar16 - 1U) * 4)))();
          return;
        }
        break;
      }
      uVar6 = FUN_180024720(*puVar12,puVar12[4],uStack_c8,(int)pcVar14[-2] + (int)dVar20,
                            (int)pcVar14[-1] + uVar26,(int)*pcVar14 + (int)dVar22);
      uVar5 = FUN_180024280(*puVar12,uVar6);
      if ((0x1f < uVar5) || ((0x80000301U >> (uVar5 & 0x1f) & 1) == 0)) goto LAB_18004b41c;
      lVar16 = lVar16 + 1;
      pcVar14 = pcVar14 + 3;
    } while (lVar16 != 10);
    uVar9 = _UNK_180156bb0;
    uVar6 = _DAT_180156ba8;
    iStack_f4 = uVar26 - 1;
    iStack_cc = uVar26 + 1;
    iStack_f8 = uVar26 + 2;
    lVar16 = 0;
    uStack_188 = (ulonglong)(uint)(int)dVar22;
    uStack_180 = (ulonglong)(uint)(int)dVar20;
    puStack_100 = puVar12;
    uStack_f0 = (ulonglong)uVar26;
    do {
      uVar23 = uStack_180;
      uVar10 = uStack_188;
      uVar5 = _DAT_180304b18 + (int)lVar16 & 3;
      cVar4 = (&UNK_180156b9e)[(ulonglong)uVar5 * 2];
      cVar1 = (&UNK_180156b9f)[(ulonglong)uVar5 * 2];
      uVar8 = *puVar12;
      lStack_190 = lVar16;
      uVar7 = FUN_180023670(uVar8,puVar12[5]);
      FUN_180025640(&uStack_1c0,uVar8,uVar7);
      iVar15 = (int)uVar23 + (int)cVar4;
      dVar20 = (double)iVar15;
      iVar13 = (int)cVar1 + (int)uVar10;
      dVar24 = (double)iVar13;
      uStack_1f8 = uVar6;
      dStack_1f0 = (double)uVar9;
      uStack_1e8 = 0x3ff0000000000000;
      uStack_178 = (ulonglong)(uint)(int)cVar1;
      uStack_170 = (ulonglong)(uint)(int)cVar4;
      dStack_128 = dVar24;
      auStack_138._0_8_ = dVar20;
      auStack_138._8_8_ = (double)(int)uVar26;
      FUN_180009400(auStack_210,auStack_138,&uStack_1f8);
      dStack_128 = dVar24;
      auStack_138._0_8_ = dVar20;
      auStack_138._8_8_ = (double)(int)uVar26;
      FUN_1800096b0(&uStack_168,auStack_138,auStack_210);
      uStack_118 = uStack_1a0;
      uStack_110 = uStack_198;
      dStack_128 = (double)uStack_1b0;
      uStack_120 = uStack_1a8;
      uStack_1d8 = uStack_148;
      uStack_1d0 = uStack_140;
      uStack_1e8 = uStack_158;
      uStack_1e0 = uStack_150;
      uStack_1dc = uStack_14c;
      uStack_1f8 = uStack_168;
      dStack_1f0 = dStack_160;
      cVar4 = FUN_1800097d0(auStack_138,&uStack_1f8);
      if (cVar4 == '\0') {
        iVar2 = uVar5 * 3;
        sVar11 = (sbyte)iVar2;
        if ((_DAT_180304b10 >> iVar2 & 1) == 0) {
          uVar8 = FUN_180024720(*puVar12,puVar12[4],uStack_c8,iVar15,(int)uStack_f0,iVar13);
          uVar5 = FUN_180024280(*puVar12,uVar8);
          if ((0x1f < uVar5) || ((0x80000301U >> (uVar5 & 0x1f) & 1) == 0)) goto LAB_18004b2b8;
          uVar8 = FUN_180024720(*puVar12,puVar12[4],uStack_c8,iVar15,iStack_f4,iVar13);
          uVar5 = FUN_180024280(*puVar12,uVar8);
          if ((uVar5 < 0x20) && ((0x80000301U >> (uVar5 & 0x1f) & 1) != 0)) goto LAB_18004b2b8;
          uVar6 = FUN_18000a050();
          iVar17 = 0;
        }
        else {
LAB_18004b2b8:
          sVar11 = (sbyte)(iVar2 + 1);
          if ((_DAT_180304b10 >> iVar2 + 1 & 1) != 0) {
LAB_18004b35b:
            sVar11 = (sbyte)(iVar2 + 2);
            if ((_DAT_180304b10 >> iVar2 + 2 & 1) == 0) {
              uVar8 = FUN_180024720(*puVar12,puVar12[4],uStack_c8,iVar15,iStack_f8,iVar13);
              uVar5 = FUN_180024280(*puVar12,uVar8);
              if ((uVar5 < 0x20) && ((0x80000301U >> (uVar5 & 0x1f) & 1) != 0)) {
                uVar8 = FUN_180024720(*puVar12,puVar12[4],uStack_c8,iVar15,iStack_cc,iVar13);
                uVar5 = FUN_180024280(*puVar12,uVar8);
                iVar17 = 2;
                if ((0x1f < uVar5) || ((0x80000301U >> (uVar5 & 0x1f) & 1) == 0))
                goto LAB_18004b3ff;
              }
            }
            goto LAB_18004b0e0;
          }
          uVar8 = FUN_180024720(*puVar12,puVar12[4],uStack_c8,iVar15,iStack_cc,iVar13);
          uVar5 = FUN_180024280(*puVar12,uVar8);
          if ((0x1f < uVar5) || ((0x80000301U >> (uVar5 & 0x1f) & 1) == 0)) goto LAB_18004b35b;
          uVar8 = FUN_180024720(*puVar12,puVar12[4],uStack_c8,iVar15,(int)uStack_f0,iVar13);
          uVar5 = FUN_180024280(*puVar12,uVar8);
          iVar17 = 1;
          if ((uVar5 < 0x20) && ((0x80000301U >> (uVar5 & 0x1f) & 1) != 0)) goto LAB_18004b35b;
LAB_18004b3ff:
          uVar6 = FUN_18000a050();
        }
        dVar21 = _DAT_1801568b8;
        iVar13 = (int)(char)uStack_170;
        fVar18 = (float)FUN_18000a510(0x180304b58,uVar6,_DAT_1801568b8);
        iVar15 = (int)(char)uStack_178;
        fVar19 = (float)FUN_18000a510(0x180304b68,uVar6,dVar21);
        iVar17 = iVar17 + (int)uStack_f0;
        cVar4 = FUN_180029800(500);
        if (cVar4 != '\0') {
          FUN_18002ade0(puVar12,0x1802f6108,1,FUN_18004bc60);
          uVar6 = FUN_180028a50(*puVar12,puVar12[5]);
          cVar4 = FUN_180028b00(*puVar12,uVar6);
          if (cVar4 != '\0') {
            uVar6 = FUN_180023170(*puVar12,puVar12[5]);
            uVar9 = FUN_180029850();
            uVar6 = FUN_180009de0(uVar6,uVar9);
            uVar9 = FUN_180023990(*puVar12,puVar12[5]);
            FUN_180025540(&uStack_1c0,*puVar12,uVar9);
            uStack_158 = uStack_1b0;
            uStack_168 = uStack_1c0;
            dStack_160 = dStack_1b8;
            auStack_138._8_4_ = SUB84((double)iVar17,0);
            auStack_138._0_8_ = (dVar21 - (double)(fVar18 * (float)iVar13)) + dVar20;
            auStack_138._12_4_ = (int)((ulonglong)(double)iVar17 >> 0x20);
            dStack_128 = (dVar21 - (double)(fVar19 * (float)iVar15)) + dVar24;
            uVar9 = FUN_180009f80(&uStack_168,auStack_138);
            uVar10 = FUN_180009e20(uVar9,uVar6);
            fVar18 = (float)FUN_18000a210(uVar10 & 0xffffffff);
            dVar24 = _DAT_1801568b8;
            uVar6 = FUN_180009e60((ulonglong)(uint)fVar18 | uVar10 & 0xffffffff00000000,
                                  (float)((double)_DAT_1802f6368 * _DAT_1801568b8 + _DAT_1801568b8))
            ;
            uVar9 = FUN_18000a050();
            FUN_18000a510(0x180304b78,uVar9);
            uVar9 = FUN_18000a050();
            FUN_18000a510(0x180304b88,uVar9);
            uVar23 = FUN_18000a1f0();
            lVar16 = FUN_18000a1f0();
            uVar6 = FUN_180009e90(uVar6,uVar23 & 0xffffffff | lVar16 << 0x20);
            FUN_180029820(uVar6);
            if ((float)((uint)((float)(uVar10 >> 0x20) - (float)((ulonglong)uVar6 >> 0x20)) &
                       _UNK_180156934) + (float)((uint)(fVar18 - (float)uVar6) & _DAT_180156930) <
                _DAT_180156940) {
              uVar6 = FUN_180022cf0(*puVar12,puVar12[3]);
              uVar6 = FUN_180024f90(*puVar12,uVar6);
              FUN_180025380(*puVar12,uVar6);
              _DAT_180304b10 = _DAT_180304b10 | 1L << sVar11;
            }
            uVar9 = uStack_d8;
            uVar6 = uStack_e8;
            DAT_180304b1c = 1;
            uVar25 = (undefined4)_DAT_1801568c0;
            uVar23 = func_0x0001800b2170(uStack_e8,uVar25);
            uVar10 = _DAT_180156890;
            dVar20 = (double)(uVar23 & _DAT_180156890);
            uVar23 = func_0x0001800b2170(uVar9,uVar25);
            if ((((dVar20 <= _DAT_1801568c8) && (_DAT_1801568d0 <= dVar20)) &&
                (_DAT_1801568d0 <= (double)(uVar23 & uVar10))) &&
               ((double)(uVar23 & uVar10) <= _DAT_1801568c8)) {
              _DAT_180304b20 = 2;
              return;
            }
            dVar21 = (double)func_0x0001800b29b0(uVar6);
            dVar20 = dStack_e0;
            dStack_128 = (double)func_0x0001800b29b0(uVar9);
            dStack_128 = dStack_128 + dVar24;
            _DAT_180304b20 = 1;
            uStack_158 = uStack_d8;
            uStack_168 = uStack_e8;
            dStack_160 = dStack_e0;
            auStack_138._8_8_ = dVar20;
            auStack_138._0_8_ = dVar21 + dVar24;
            _DAT_180304b28 = FUN_180009f80(&uStack_168,auStack_138);
            return;
          }
        }
        goto LAB_18004b9b1;
      }
LAB_18004b0e0:
      uVar8 = uStack_d8;
      lVar16 = lStack_190 + 1;
    } while (lVar16 != 4);
    if ((bStack_b9 & 1) == 0) {
      return;
    }
    uVar25 = (undefined4)_DAT_1801568c0;
    uVar23 = func_0x0001800b2170(uStack_e8,uVar25);
    uVar10 = _DAT_180156890;
    dVar24 = (double)(uVar23 & _DAT_180156890);
    uVar23 = func_0x0001800b2170(uVar8,uVar25);
    if (_DAT_1801568c8 < dVar24) {
      return;
    }
    if (dVar24 < _DAT_1801568d0) {
      return;
    }
    if ((double)(uVar23 & uVar10) < _DAT_1801568d0) {
      return;
    }
    puVar12 = puStack_100;
    if (_DAT_1801568c8 < (double)(uVar23 & uVar10)) {
      return;
    }
  }
LAB_18004b9b1:
  FUN_1800284f0(puVar12[1],0x1802f6108,0);
  return;
}

// UI RVA 0x4bbc0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x4bbc0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18004bbc0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180156bcd);
  FUN_18000cf30(param_2,param_1,0x1802f6338);
  FUN_180013e90(param_1,param_2,&UNK_180156bd2);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802f6328,0x1802f6318,&DAT_1802f6330);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x4bc20; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x4bc20; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18004bc20(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c450(param_1,&UNK_180156bdd,0x1802f6338);
  uVar1 = uRam00000001802f6331;
  uVar2 = DAT_1802f6330;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180156be3,DAT_1802f6330);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802f6330;
      break;
    case 2:
      uRam00000001802f6331 = DAT_1802f6330;
      break;
    case 3:
      uVar2 = uRam00000001802f6331;
    }
  }
  DAT_1802f6330 = uVar2;
  return;
}

