// Recovered decompiler view: Anti Bot
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x30e70, 0x31570); proximity does not prove ownership.

// CALLBACK RVA 0x30e70; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/anti_bot/anti_bot.c
// Differential report: analysis/module_behavior_recovery/anti_bot/verification_report.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x30e70; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180030e70(longlong param_1)

{
  ushort uVar1;
  longlong *plVar2;
  longlong *plVar3;
  double dVar4;
  double dVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  uint *puVar14;
  longlong lVar15;
  longlong lVar16;
  double adStack_d8 [2];
  double dStack_c8;
  double adStack_c0 [2];
  double dStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  longlong *plStack_88;
  undefined8 uStack_80;
  
  plVar2 = *(longlong **)(param_1 + 8);
  if (plVar2[4] == 0) {
    iVar7 = 0;
    if (_DAT_1802f9de8 == 0) goto LAB_180030edc;
  }
  else {
    iVar7 = FUN_180026060(*plVar2);
    if (iVar7 == _DAT_1802f9de8) goto LAB_180030edc;
  }
  func_0x00018013cf70(_DAT_1802f9df0);
  _DAT_1802f9df0 = 0;
  uRam00000001802f9df8 = 0;
  _DAT_1802f9de8 = iVar7;
LAB_180030edc:
  if (plVar2[4] != 0) {
    uVar10 = FUN_180024600(*plVar2);
    iVar7 = FUN_180024e50(*plVar2,uVar10);
    dVar5 = _DAT_1801510c8;
    if (0 < iVar7) {
      iVar7 = 0;
      do {
        uVar11 = FUN_180024e80(*plVar2,uVar10,iVar7);
        cVar6 = (**(code **)(**(longlong **)(*plVar2 + 8) + 0xc0))
                          (*(longlong **)(*plVar2 + 8),plVar2[5],uVar11);
        if (cVar6 == '\0') {
          uVar12 = FUN_180023740(*plVar2,uVar11);
          uVar13 = FUN_180027dc0(*plVar2,uVar12);
          uStack_a0 = FUN_180027d90(*plVar2,uVar12);
          uStack_98 = 0;
          uStack_90 = 0;
          uStack_a8 = uVar13;
          puVar14 = (uint *)FUN_18000e0b0(&DAT_1802f9df0,0x20,0x1802f9df8,&uStack_a8,FUN_180031530);
          FUN_1800230d0(adStack_d8,*plVar2,uVar11);
          FUN_180023030(adStack_c0,*plVar2,uVar11);
          dVar4 = (adStack_d8[0] - adStack_c0[0]) * (adStack_d8[0] - adStack_c0[0]) +
                  (dStack_c8 - dStack_b0) * (dStack_c8 - dStack_b0) + *(double *)(puVar14 + 4);
          *(double *)(puVar14 + 4) = dVar4;
          if ((DAT_1802eaf30 != '\x01') || (dVar5 <= dVar4)) {
            if (_DAT_1802eaf88 != 0) {
              if (((*puVar14 & 0xf000) == 0x2000) && (_DAT_1802eaf88 == 2 || dVar4 < dVar5))
              goto LAB_180030f20;
            }
            if ((DAT_1802eafb0 != '\x01') || (cVar6 = FUN_1800240a0(*plVar2,uVar11), cVar6 == '\0'))
            {
              iVar8 = FUN_180023760(*plVar2,uVar11);
              if ((DAT_1802eafd0 == '\x01') && (*(char *)((longlong)puVar14 + 0x19) == '\0')) {
                lVar16 = *plVar2;
                cVar6 = FUN_180023f60(lVar16,uVar11,plVar2[5]);
                if (cVar6 != '\0') {
                  uStack_80 = FUN_180023f40(lVar16,uVar11);
                  lVar15 = FUN_180026140(lVar16,uStack_80,0x24);
                  if ((((((lVar15 == 0) || (lVar15 = FUN_180025d10(lVar16,lVar15), lVar15 == 0)) ||
                        (iVar9 = FUN_180025c50(lVar16,lVar15), iVar9 == 0)) &&
                       (((lVar15 = FUN_180026140(lVar16,uStack_80,0x25), lVar15 == 0 ||
                         (lVar15 = FUN_180025d10(lVar16,lVar15), lVar15 == 0)) ||
                        (iVar9 = FUN_180025c50(lVar16,lVar15), iVar9 == 0)))) &&
                      (((lVar15 = FUN_180026140(lVar16,uStack_80,0x26), lVar15 == 0 ||
                        (lVar15 = FUN_180025d10(lVar16,lVar15), lVar15 == 0)) ||
                       (iVar9 = FUN_180025c50(lVar16,lVar15), iVar9 == 0)))) &&
                     (((lVar15 = FUN_180026140(lVar16,uStack_80,0x27), lVar15 == 0 ||
                       (lVar15 = FUN_180025d10(lVar16,lVar15), lVar15 == 0)) ||
                      (iVar9 = FUN_180025c50(lVar16,lVar15), iVar9 == 0)))) goto LAB_180030f20;
                }
                if (0x14 < iVar8) {
                  *(undefined1 *)((longlong)puVar14 + 0x19) = 1;
                }
              }
              if ((0.0 < _DAT_1802eaf10) && ((char)puVar14[6] == '\0')) {
                if ((float)iVar8 < _DAT_1802eaf10) goto LAB_180030f20;
                *(undefined1 *)(puVar14 + 6) = 1;
              }
              if ((DAT_1802eaff0 == '\x01') && (*(char *)((longlong)puVar14 + 0x1a) == '\0')) {
                plVar3 = *(longlong **)(*plVar2 + 8);
                uStack_80 = FUN_180023830(*plVar2,uVar11);
                iVar8 = (**(code **)(*plVar3 + 0x520))(plVar3,uStack_80);
                plStack_88 = plVar3;
                lVar16 = (**(code **)(*plVar3 + 0x700))(plVar3,uStack_80,0);
                if (0 < iVar8) {
                  iVar9 = 0;
                  do {
                    uVar1 = *(ushort *)(lVar16 + (longlong)iVar9 * 2);
                    if (uVar1 == 0xa7) {
                      iVar9 = iVar9 + 1;
                    }
                    else if ((((ushort)((uVar1 & 0xffdf) - 0x41) < 0x1a) || (uVar1 == 0x5f)) ||
                            ((ushort)(uVar1 - 0x30) < 10)) {
                      *(undefined1 *)((longlong)puVar14 + 0x1a) = 1;
                      break;
                    }
                    iVar9 = iVar9 + 1;
                  } while (iVar9 < iVar8);
                }
                (**(code **)(*plStack_88 + 0x708))(plStack_88,uStack_80,lVar16);
                if (*(char *)((longlong)puVar14 + 0x1a) == '\0') goto LAB_180030f20;
              }
              FUN_18002ad80(*plVar2,uVar11,2);
              goto LAB_180030f32;
            }
          }
LAB_180030f20:
          FUN_18002ad20(*plVar2,uVar11,2);
        }
LAB_180030f32:
        iVar7 = iVar7 + 1;
        iVar8 = FUN_180024e50(*plVar2,uVar10);
      } while (iVar7 < iVar8);
    }
  }
  return;
}

// CALLBACK RVA 0x31310; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/anti_bot/anti_bot.c
// Differential report: analysis/module_behavior_recovery/anti_bot/verification_report.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x31310; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180031310(longlong param_1)

{
  longlong *plVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  
  if ((*(longlong *)(param_1 + 0x10) == 0x1802eacd0) && (*(char *)(param_1 + 0x18) == '\0')) {
    func_0x00018013cf70(_DAT_1802f9df0);
    _DAT_1802f9df0 = 0;
    uRam00000001802f9df8 = 0;
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
            FUN_18002ad80(*plVar1,uVar6,2);
          }
          iVar3 = iVar3 + 1;
          iVar4 = FUN_180024e50(*plVar1,uVar5);
        } while (iVar3 < iVar4);
      }
    }
  }
  return;
}

// UI RVA 0x313f0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x313f0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_1800313f0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  undefined8 unaff_RBP;
  undefined8 unaff_RDI;
  undefined4 uVar2;
  
  uVar2 = (undefined4)((ulonglong)unaff_RDI >> 0x20);
  FUN_180013e90(param_1,param_2,&UNK_18015117b);
  FUN_18000d040(param_2,param_1,0x1802eaf58);
  FUN_18000cef0(param_2,param_1,0x1802eafd8);
  FUN_18000cef0(param_2,param_1,0x1802eafb8);
  FUN_18000cef0(param_2,param_1,0x1802eaf18);
  FUN_18000cef0(param_2,param_1,0x1802eaf98);
  cVar1 = FUN_180013f40(param_1,param_2,uRam00000001802eaef0,uRam00000001802eaef8,0x1802eaee0,
                        uRam00000001802eaf08,uRam00000001802eaf0c,uRam00000001802eaf00,
                        CONCAT44(uVar2,uRam00000001802eaf04),&DAT_1802eaf10,unaff_RBP);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x31490; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x31490; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180031490(undefined8 *param_1)

{
  double dVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  undefined8 uVar6;
  longlong lVar7;
  float fVar8;
  
  FUN_18000c6f0(param_1,&UNK_180151180,0x1802eaf58);
  FUN_18000c3b0(param_1,&UNK_18015118d,0x1802eafd8);
  FUN_18000c3b0(param_1,&UNK_18015119e,0x1802eafb8);
  FUN_18000c3b0(param_1,&UNK_1801511ab,0x1802eaf18);
  FUN_18000c3b0(param_1,&UNK_1801511bd,0x1802eaf98);
  fVar4 = _DAT_1802eaf10;
  if (*(char *)((longlong)param_1 + 0xc) == '\0') {
    switch(*(undefined4 *)(param_1 + 1)) {
    case 0:
      uVar6 = FUN_18004e4d0(*param_1);
      fVar4 = fRam00000001802eaf14;
      fVar3 = fRam00000001802eaf0c;
      fVar2 = fRam00000001802eaf08;
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
      lVar7 = FUN_18004eeb0(*param_1,&UNK_1801511c6,(double)_DAT_1802eaf10);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar7 == 0;
      fVar4 = _DAT_1802eaf10;
      break;
    case 2:
      fRam00000001802eaf14 = _DAT_1802eaf10;
      break;
    case 3:
      fVar4 = fRam00000001802eaf14;
    }
  }
  _DAT_1802eaf10 = fVar4;
  return;
}

// CANDIDATE_LOCAL RVA 0x31530; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x31530; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


int FUN_180031530(undefined8 param_1,ulonglong *param_2,ulonglong *param_3)

{
  ulonglong uVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  
  uVar3 = *param_2;
  uVar2 = uVar3 >> 0x38 | (uVar3 & 0xff000000000000) >> 0x28 | (uVar3 & 0xff0000000000) >> 0x18 |
          (uVar3 & 0xff00000000) >> 8 | (uVar3 & 0xff000000) << 8 | (uVar3 & 0xff0000) << 0x18 |
          (uVar3 & 0xff00) << 0x28 | uVar3 << 0x38;
  uVar3 = *param_3;
  uVar3 = uVar3 >> 0x38 | (uVar3 & 0xff000000000000) >> 0x28 | (uVar3 & 0xff0000000000) >> 0x18 |
          (uVar3 & 0xff00000000) >> 8 | (uVar3 & 0xff000000) << 8 | (uVar3 & 0xff0000) << 0x18 |
          (uVar3 & 0xff00) << 0x28 | uVar3 << 0x38;
  if (uVar2 == uVar3) {
    uVar3 = param_2[1];
    uVar1 = param_3[1];
    uVar2 = uVar3 >> 0x38 | (uVar3 & 0xff000000000000) >> 0x28 | (uVar3 & 0xff0000000000) >> 0x18 |
            (uVar3 & 0xff00000000) >> 8 | (uVar3 & 0xff000000) << 8 | (uVar3 & 0xff0000) << 0x18 |
            (uVar3 & 0xff00) << 0x28 | uVar3 << 0x38;
    uVar3 = uVar1 >> 0x38 | (uVar1 & 0xff000000000000) >> 0x28 | (uVar1 & 0xff0000000000) >> 0x18 |
            (uVar1 & 0xff00000000) >> 8 | (uVar1 & 0xff000000) << 8 | (uVar1 & 0xff0000) << 0x18 |
            (uVar1 & 0xff00) << 0x28 | uVar1 << 0x38;
    if (uVar2 == uVar3) {
      return 0;
    }
  }
  return (uint)(uVar3 <= uVar2) * 2 + -1;
}

