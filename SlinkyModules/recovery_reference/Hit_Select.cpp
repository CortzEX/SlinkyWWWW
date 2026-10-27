// Recovered decompiler view: Hit Select
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x376c0, 0x38190); proximity does not prove ownership.

// CALLBACK RVA 0x376c0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/hit_select/hit_select.c
// Differential report: analysis/module_behavior_recovery/hit_select/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x376c0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800376c0(longlong param_1)

{
  undefined8 *puVar1;
  int iVar2;
  int iVar3;
  
  DAT_1802fc538 = 0;
  puVar1 = *(undefined8 **)(param_1 + 8);
  iVar3 = 0;
  if (*(char *)(puVar1 + 8) == '\x01') {
    iVar2 = FUN_1800239f0(*puVar1,puVar1[5]);
    iVar3 = 0;
    if (iVar2 == 0) {
      iVar3 = _DAT_1802fc53c + 1;
    }
  }
  _DAT_1802fc53c = iVar3;
  return;
}

// CALLBACK RVA 0x37710; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/hit_select/hit_select.c
// Differential report: analysis/module_behavior_recovery/hit_select/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x37710; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180037710(longlong param_1)

{
  undefined8 *puVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  char cVar5;
  byte bVar6;
  char cVar7;
  int iVar8;
  longlong lVar9;
  undefined8 uVar10;
  byte bVar11;
  uint uVar12;
  ulonglong uVar13;
  bool bVar14;
  uint uVar15;
  bool bVar16;
  float fVar17;
  undefined4 uVar18;
  undefined8 uStack_b0;
  double dStack_a8;
  undefined8 uStack_a0;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined8 uStack_88;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  
  if (*(char *)(param_1 + 0x10) != '\x01') {
    return;
  }
  puVar1 = *(undefined8 **)(param_1 + 8);
  if (DAT_1802fc538 == '\x01') {
joined_r0x00018003774e:
    if (DAT_1802fc540 == '\0') {
      DAT_1802fc538 = 1;
      return;
    }
LAB_180037754:
    DAT_1802fc538 = 1;
    *(undefined1 *)(param_1 + 0x11) = 1;
    if (((DAT_1802ee928 == '\x01') && (puVar1[5] != 0)) &&
       (cVar5 = FUN_180023f90(*puVar1), cVar5 == '\0')) {
      FUN_180023bb0(*puVar1,puVar1[5]);
    }
  }
  else {
    if (((DAT_1802ee830 != '\x01') || (cVar5 = FUN_180023690(*puVar1,puVar1[5]), cVar5 != '\0')) &&
       ((DAT_1802ee850 != '\x01' || (cVar5 = FUN_1800380b0(*puVar1,puVar1[5]), cVar5 != '\0')))) {
      lVar9 = FUN_180022e10(*puVar1,puVar1[3]);
      bVar14 = true;
      bVar16 = true;
      if (lVar9 != 0) {
        iVar8 = FUN_180024b50(*puVar1,lVar9);
        if (iVar8 == 2) {
          lVar9 = FUN_180024e30(*puVar1,lVar9);
          bVar16 = lVar9 == 0;
          goto LAB_180037840;
        }
        if (iVar8 == 1) goto LAB_180037ab5;
        if ((iVar8 != 0) || (cVar5 = FUN_18000a460(_DAT_1802ee730), cVar5 == '\0'))
        goto LAB_180037840;
LAB_180037818:
        DAT_1802fc540 = '\x01';
        goto LAB_180037754;
      }
LAB_180037840:
      uVar13 = (ulonglong)_DAT_1802ee768;
      bVar6 = FUN_18000a460(_DAT_1802ee768 - (float)(uVar13 & 0xffffffff));
      cVar5 = FUN_180023780(*puVar1,puVar1[5]);
      if (cVar5 != '\0') {
        FUN_180023550(&uStack_78,*puVar1,puVar1[5]);
        bVar14 = 0.0 < uStack_70;
      }
      uVar15 = (uint)bVar6 + (int)uVar13;
      bVar6 = bVar14 & *(byte *)(puVar1[7] + 0x18);
      if (_DAT_1802ee8a0 == 1) {
        bVar11 = _DAT_1802fc544 - 9 < 0xfffffff9 | DAT_1802ee8c8;
        if (cVar5 == '\0') {
          fVar17 = (float)FUN_1800237e0(*puVar1,puVar1[5]);
          bVar14 = 0.0 < fVar17;
          if ((bVar14 & bVar11) != 0) goto LAB_180037ab5;
        }
        else {
          bVar14 = false;
        }
        if ((bVar6 == 0) || ((bVar11 != 0 && (DAT_1802ee8e8 == '\0')))) {
          FUN_180023030(&uStack_78,*puVar1,puVar1[5]);
          cVar7 = FUN_180023020(*puVar1);
          if (cVar7 != '\0') {
            uStack_88 = uStack_68;
            uStack_98 = (undefined4)uStack_78;
            uStack_94 = uStack_78._4_4_;
            uStack_90 = (undefined4)uStack_70;
            uStack_8c = uStack_70._4_4_;
            FUN_1800095c0(&uStack_b0,&uStack_98);
            uStack_78 = uStack_b0;
            uStack_70 = dStack_a8;
            uStack_68 = uStack_a0;
          }
          uVar18 = SUB84(uStack_70,0);
          dVar2 = (double)func_0x0001800b29b0((int)uStack_78);
          dVar3 = (double)func_0x0001800b29b0(uVar18);
          dVar4 = (double)func_0x0001800b29b0((int)uStack_68);
          uVar10 = FUN_180024690(*puVar1,puVar1[4],(int)dVar2,(int)dVar3,(int)dVar4);
          iVar8 = FUN_180024280(*puVar1,uVar10);
          if (iVar8 == 0) {
            if ((cVar5 != '\0' || bVar14) ||
               ((DAT_1802ee908 == '\x01' && (iVar8 = FUN_1800239f0(*puVar1,puVar1[5]), iVar8 == 0)))
               ) goto LAB_180037a80;
            goto LAB_180037818;
          }
        }
      }
      else if ((_DAT_1802ee8a0 == 0) && (bVar6 == 0)) {
        if (_DAT_1802fc544 < 0xf) {
          _DAT_1802fc548 = 0;
        }
        else if (!bVar16) {
          uVar12 = _DAT_1802fc548 + 1;
          uVar13 = (ulonglong)_DAT_1802ee7a0;
          _DAT_1802fc548 = uVar12;
          bVar6 = FUN_18000a460(_DAT_1802ee7a0 - (float)(uVar13 & 0xffffffff));
          if (uVar12 <= (uint)bVar6 + (int)uVar13) goto LAB_180037818;
        }
        if (_DAT_1802fc53c < 10) {
          uVar13 = (ulonglong)_DAT_1802ee7d8;
          bVar6 = FUN_18000a460(_DAT_1802ee7d8 - (float)(uVar13 & 0xffffffff));
          uVar15 = uVar15 + (uint)bVar6 + (int)uVar13;
        }
        if (DAT_1802fc54c == '\x01') {
          DAT_1802fc54c = '\0';
        }
        else {
LAB_180037a80:
          if (_DAT_1802fc544 + 1 < uVar15) {
            DAT_1802fc540 = FUN_18000a460(_DAT_1802ee810);
            goto joined_r0x00018003774e;
          }
        }
      }
    }
LAB_180037ab5:
    DAT_1802fc540 = '\0';
    DAT_1802fc538 = 1;
  }
  return;
}

// CALLBACK RVA 0x37ae0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/hit_select/hit_select.c
// Differential report: analysis/module_behavior_recovery/hit_select/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x37ae0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180037ae0(longlong param_1)

{
  undefined8 *puVar1;
  int iVar2;
  int iVar3;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  if (DAT_1802ee8c8 == '\x01') {
    if ((*(longlong *)(puVar1[7] + 8) != 0) && (iVar2 = FUN_1800239f0(*puVar1), iVar2 == 10)) {
      _DAT_1802fc544 = 0;
      DAT_1802fc54c = 1;
      return;
    }
    _DAT_1802fc544 = _DAT_1802fc544 + 1;
    return;
  }
  if (*(longlong *)(puVar1[7] + 8) == 0) {
    iVar2 = 0;
    if (_DAT_1802fc550 != 0) goto LAB_180037b64;
  }
  else {
    iVar2 = FUN_180023720(*puVar1);
    if (iVar2 != _DAT_1802fc550) {
LAB_180037b64:
      _DAT_1802fc544 = 0x3e9;
      _DAT_1802fc550 = iVar2;
      goto LAB_180037b74;
    }
  }
  _DAT_1802fc544 = _DAT_1802fc544 + 1;
  if (_DAT_1802fc544 < 10) {
    return;
  }
LAB_180037b74:
  iVar2 = FUN_180023760(*puVar1,puVar1[5]);
  iVar3 = FUN_1800239d0(*puVar1,puVar1[5]);
  if (iVar2 == iVar3) {
    _DAT_1802fc544 = 0;
  }
  return;
}

// UI RVA 0x37bb0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x37bb0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180037bb0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_18015282d);
  FUN_18000d040(param_2,param_1,0x1802ee870);
  FUN_18000cf30(param_2,param_1,0x1802ee738);
  if (_DAT_1802ee8a0 == 0) {
    FUN_18000cf30(param_2,param_1,0x1802ee770);
    FUN_18000cf30(param_2,param_1,0x1802ee7a8);
  }
  FUN_18000cef0(param_2,param_1,0x1802ee8b0);
  FUN_18000cef0(param_2,param_1,0x1802ee910);
  if (_DAT_1802ee8a0 == 1) {
    FUN_18000cef0(param_2,param_1,0x1802ee8d0);
    FUN_18000cef0(param_2,param_1,0x1802ee8f0);
  }
  FUN_180013e90(param_1,param_2,&UNK_180152832);
  FUN_18000cf30(param_2,param_1,0x1802ee7e0);
  FUN_18000cf30(param_2,param_1,0x1802ee700);
  FUN_180013e90(param_1,param_2,&UNK_18015283e);
  FUN_18000cef0(param_2,param_1,0x1802ee818);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802ee848,0x1802ee838,&DAT_1802ee850);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x37cf0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x37cf0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180037cf0(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c6f0(param_1,&UNK_180152849,0x1802ee870);
  FUN_18000c450(param_1,&UNK_18015284e,0x1802ee7e0);
  FUN_18000c450(param_1,&UNK_18015285a,0x1802ee700);
  FUN_18000c450(param_1,&UNK_18015286a,0x1802ee738);
  FUN_18000c450(param_1,&UNK_180152874,0x1802ee770);
  FUN_18000c450(param_1,&UNK_180152888,0x1802ee7a8);
  FUN_18000c3b0(param_1,&UNK_180152895,0x1802ee8b0);
  FUN_18000c3b0(param_1,&UNK_1801528a5,0x1802ee910);
  FUN_18000c3b0(param_1,&UNK_1801528b0,0x1802ee8d0);
  FUN_18000c3b0(param_1,&UNK_1801528c3,0x1802ee8f0);
  FUN_18000c3b0(param_1,&UNK_1801528d2,0x1802ee818);
  uVar1 = uRam00000001802ee851;
  uVar2 = DAT_1802ee850;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_1801528e1,DAT_1802ee850);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802ee850;
      break;
    case 2:
      uRam00000001802ee851 = DAT_1802ee850;
      break;
    case 3:
      uVar2 = uRam00000001802ee851;
    }
  }
  DAT_1802ee850 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x37e10; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x37e10; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180037e10(undefined8 param_1)

{
  FUN_1800ab710(param_1,0x20,&UNK_1801528f0,
                *(undefined8 *)((ulonglong)_DAT_1802ee8a0 * 8 + 0x1802ee860));
  return;
}

// CANDIDATE_LOCAL RVA 0x37e50; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x37e50; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 FUN_180037e50(undefined8 param_1,undefined8 param_2,uint *param_3)

{
  undefined1 uVar1;
  int iVar2;
  undefined8 uVar3;
  longlong lVar4;
  
  iVar2 = FUN_180023760();
  uVar1 = DAT_1802fc55c;
  if (iVar2 != _DAT_1802fc558) {
    _DAT_1802fc560 = 0;
    _DAT_1802fc558 = iVar2;
    uVar3 = FUN_180023f40(param_1,param_2);
    iVar2 = FUN_180025a60(param_1,uVar3);
    lVar4 = FUN_180026140(param_1,uVar3,iVar2);
    uVar1 = DAT_1802eeb58;
    if (lVar4 != 0) {
      _DAT_1802fc560 = FUN_180037f60(param_1,lVar4);
      uVar1 = 1;
      if ((((*(char *)((longlong)iVar2 * 0x20 + 0x1802eeb78) == '\0') &&
           (((_DAT_1802fc560 & 1) == 0 || (DAT_1802eec98 == '\0')))) &&
          (((_DAT_1802fc560 & 2) == 0 || (DAT_1802eecb8 == '\0')))) &&
         ((_DAT_1802fc560 < 4 || (DAT_1802eecd8 == '\0')))) {
        uVar3 = FUN_180025d10(param_1,lVar4);
        uVar1 = FUN_180038040(param_1,uVar3);
      }
    }
  }
  DAT_1802fc55c = uVar1;
  if (param_3 != (uint *)0x0) {
    *param_3 = _DAT_1802fc560;
  }
  return DAT_1802fc55c;
}

// CANDIDATE_LOCAL RVA 0x37f60; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x37f60; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


uint FUN_180037f60(longlong param_1)

{
  longlong *plVar1;
  short sVar2;
  int iVar3;
  longlong lVar4;
  longlong lVar5;
  longlong lVar6;
  undefined8 uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  
  lVar4 = FUN_180025de0();
  uVar8 = 0;
  uVar9 = 0;
  if (lVar4 != 0) {
    plVar1 = *(longlong **)(param_1 + 8);
    lVar5 = (**(code **)(*plVar1 + 0x538))(plVar1,&UNK_18015292e);
    uVar9 = uVar8;
    if (lVar5 != 0) {
      lVar6 = (**(code **)(*plVar1 + 0x538))(plVar1,&UNK_180152931);
      if (lVar6 != 0) {
        iVar3 = FUN_180027f10(param_1,lVar4);
        if (0 < iVar3) {
          iVar10 = 0;
          uVar9 = 0;
          do {
            uVar7 = FUN_180027f40(param_1,lVar4,iVar10);
            sVar2 = FUN_180027f70(param_1,uVar7,lVar5);
            if (sVar2 == 0x14) {
              uVar9 = uVar9 | 4;
            }
            else if (sVar2 == 0x13) {
              uVar9 = uVar9 | 2;
            }
            else if (sVar2 == 0x10) {
              uVar9 = uVar9 | 1;
            }
            iVar10 = iVar10 + 1;
          } while (iVar3 != iVar10);
        }
      }
    }
  }
  return uVar9;
}

// CANDIDATE_LOCAL RVA 0x38040; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x38040; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 FUN_180038040(undefined8 param_1,longlong param_2)

{
  longlong lVar1;
  uint uVar2;
  undefined8 uStack_18;
  int iStack_10;
  undefined4 uStack_c;
  
  if (param_2 != 0) {
    iStack_10 = FUN_180025c50();
    uVar2 = iStack_10 - 0x102;
    if (uVar2 < 0x1d) {
      if ((0x2044600U >> (uVar2 & 0x1f) & 1) != 0) {
        return DAT_1802eed18;
      }
      if ((0x10222001U >> (uVar2 & 0x1f) & 1) != 0) {
        return DAT_1802eecf8;
      }
    }
    if (iStack_10 != 0) {
      uStack_18 = 0;
      uStack_c = 0;
      lVar1 = FUN_18000df00(_DAT_1802fc568,0x10,0x1802fc570,&uStack_18,FUN_18002ac20);
      return lVar1 != 0;
    }
  }
  return DAT_1802eeb58;
}

// CANDIDATE_LOCAL RVA 0x380b0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x380b0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Removing unreachable block (ram,0x000180037f3a) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 FUN_1800380b0(undefined8 param_1,undefined8 param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined8 uVar3;
  longlong lVar4;
  
  iVar2 = FUN_180023760();
  uVar1 = DAT_1802fc55c;
  if (iVar2 != _DAT_1802fc558) {
    _DAT_1802fc560 = 0;
    _DAT_1802fc558 = iVar2;
    uVar3 = FUN_180023f40(param_1,param_2);
    iVar2 = FUN_180025a60(param_1,uVar3);
    lVar4 = FUN_180026140(param_1,uVar3,iVar2);
    uVar1 = DAT_1802eeb58;
    if (lVar4 != 0) {
      _DAT_1802fc560 = FUN_180037f60(param_1,lVar4);
      uVar1 = 1;
      if ((((*(char *)((longlong)iVar2 * 0x20 + 0x1802eeb78) == '\0') &&
           (((_DAT_1802fc560 & 1) == 0 || (DAT_1802eec98 == '\0')))) &&
          (((_DAT_1802fc560 & 2) == 0 || (DAT_1802eecb8 == '\0')))) &&
         ((_DAT_1802fc560 < 4 || (DAT_1802eecd8 == '\0')))) {
        uVar3 = FUN_180025d10(param_1,lVar4);
        uVar1 = FUN_180038040(param_1,uVar3);
      }
    }
  }
  DAT_1802fc55c = uVar1;
  return DAT_1802fc55c;
}

// CANDIDATE_LOCAL RVA 0x380c0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x380c0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


ulonglong FUN_1800380c0(undefined8 *param_1,undefined8 param_2)

{
  undefined8 uVar1;
  char cVar2;
  uint uVar3;
  undefined8 uVar4;
  longlong lVar5;
  ulonglong uVar6;
  char *pcVar7;
  
  pcVar7 = (char *)0x1802eeb78;
  uVar6 = 0;
  do {
    if (*pcVar7 != '\0') goto LAB_180038172;
    lVar5 = FUN_180026140(*param_1,param_2,uVar6 & 0xffffffff);
    if (lVar5 != 0) {
      uVar1 = *param_1;
      uVar3 = FUN_180037f60(uVar1,lVar5);
      if (((((uVar3 & 1) != 0) && (DAT_1802eec98 != '\0')) ||
          (((uVar3 & 2) != 0 && (DAT_1802eecb8 != '\0')))) ||
         ((3 < uVar3 && (DAT_1802eecd8 != '\0')))) goto LAB_180038172;
      uVar4 = FUN_180025d10(uVar1,lVar5);
      cVar2 = FUN_180038040(uVar1,uVar4);
      if (cVar2 != '\0') goto LAB_180038172;
    }
    uVar6 = uVar6 + 1;
    pcVar7 = pcVar7 + 0x20;
  } while (uVar6 != 9);
  uVar6 = 0xffffffff;
LAB_180038172:
  return uVar6 & 0xffffffff;
}

