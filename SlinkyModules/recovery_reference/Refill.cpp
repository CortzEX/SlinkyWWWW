// Recovered decompiler view: Refill
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x384c0, 0x391c0); proximity does not prove ownership.

// CALLBACK RVA 0x384c0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/refill/refill.c
// Differential report: analysis/module_behavior_recovery/refill/verification_report.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x384c0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800384c0(longlong param_1)

{
  if ((*(longlong *)(param_1 + 0x10) == 0x1802eed90) && (*(char *)(param_1 + 0x18) == '\x01')) {
    _DAT_1802fc580 = 0;
    return;
  }
  return;
}

// CALLBACK RVA 0x384f0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/refill/refill.c
// Differential report: analysis/module_behavior_recovery/refill/verification_report.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x384f0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800384f0(longlong param_1)

{
  longlong *plVar1;
  undefined8 *puVar2;
  float fVar3;
  char cVar4;
  int iVar5;
  longlong lVar6;
  undefined8 uVar7;
  undefined8 unaff_R14;
  int iVar8;
  float fVar9;
  undefined4 uVar10;
  
  puVar2 = *(undefined8 **)(param_1 + 8);
  lVar6 = FUN_180022c90(*puVar2,puVar2[3]);
  uVar10 = (undefined4)((ulonglong)unaff_R14 >> 0x20);
  if (_DAT_1802fc580 != 0) {
    if (lVar6 == 0) goto LAB_1800389a5;
    cVar4 = FUN_180025b80(*puVar2,lVar6);
    uVar10 = (undefined4)((ulonglong)unaff_R14 >> 0x20);
    if (cVar4 == '\0') goto LAB_1800389a5;
    *(undefined1 *)(param_1 + 0x10) = 1;
  }
  uVar10 = (undefined4)((ulonglong)unaff_R14 >> 0x20);
  if (0.0 < _DAT_1802fc5d0) {
    _DAT_1802fc5d0 = _DAT_1802fc5d0 + _DAT_180152a7c;
    return;
  }
  if (0.0 < _DAT_1802fc5d0) {
    return;
  }
  if (_DAT_1802fc580 != 4) {
    if (puVar2[5] != 0) {
      uVar7 = FUN_180023f40(*puVar2);
      iVar8 = 0;
      do {
        lVar6 = FUN_180026140(*puVar2,uVar7,iVar8);
        if ((lVar6 == 0) || (lVar6 = FUN_180025d10(*puVar2,lVar6), lVar6 == 0)) {
LAB_180038730:
                    /* WARNING: Could not recover jumptable at 0x00018003873d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
          (*(code *)(&UNK_180152a80 + *(int *)(&UNK_180152a80 + (ulonglong)_DAT_1802fc580 * 4)))();
          return;
        }
        iVar5 = FUN_180025c50(*puVar2,lVar6);
        uVar10 = (undefined4)((ulonglong)unaff_R14 >> 0x20);
        if (iVar5 == 0) goto LAB_180038730;
        iVar8 = iVar8 + 1;
      } while (iVar8 != 9);
    }
    fVar3 = _DAT_1802eefd0;
    uVar7 = FUN_18000a050(0,_DAT_180152a70);
    fVar9 = (float)FUN_18000a510(0x1802fc598,uVar7,_DAT_180152a48);
    fVar3 = fVar3 - fVar9;
    if (fVar3 <= 0.0) {
      fVar3 = 0.0;
    }
    _DAT_1802fc5d0 = _DAT_1802fc5d0 + fVar3;
    _DAT_1802fc580 = 4;
    if (0.0 < _DAT_1802fc5d0) {
      _DAT_1802fc580 = 4;
      return;
    }
  }
LAB_1800389a5:
  FUN_1800284f0(puVar2[1],0x1802eed90,0);
  lVar6 = FUN_180022c90(*puVar2,puVar2[3]);
  if (lVar6 == 0) {
    return;
  }
  plVar1 = (longlong *)((longlong *)*puVar2)[1];
  (**(code **)(*plVar1 + 0x1e8))
            (plVar1,lVar6,*(undefined8 *)(*(longlong *)*puVar2 + 0xcb0),0,CONCAT44(uVar10,1));
  return;
}

// UI RVA 0x38bc0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x38bc0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180038bc0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180152bae);
  FUN_18000cef0(param_2,param_1,0x1802ef068);
  if (DAT_1802ef080 == '\x01') {
    FUN_18000cef0(param_2,param_1,0x1802ef088);
  }
  FUN_18000cef0(param_2,param_1,0x1802ef048);
  FUN_180013e90(param_1,param_2,&UNK_180152bb4);
  FUN_18000d040(param_2,param_1,0x1802ef0e8);
  FUN_18000cf30(param_2,param_1,0x1802eefd8);
  FUN_18000cf30(param_2,param_1,0x1802eefa0);
  FUN_18000cf30(param_2,param_1,0x1802ef010);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802ef0b8,0x1802ef0a8,0x1802ef0c0);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x38c90; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x38c90; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180038c90(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c3b0(param_1,&UNK_180152bbb,0x1802ef068);
  FUN_18000c3b0(param_1,&UNK_180152bc9,0x1802ef088);
  FUN_18000c3b0(param_1,&UNK_180152be2,0x1802ef048);
  FUN_18000c6f0(param_1,&UNK_180152bee,0x1802ef0e8);
  FUN_18000c450(param_1,&UNK_180152bfe,0x1802eefd8);
  FUN_18000c450(param_1,&UNK_180152c0f,0x1802eefa0);
  FUN_18000c450(param_1,&UNK_180152c22,0x1802ef010);
  uVar1 = uRam00000001802ef0c1;
  uVar2 = uRam00000001802ef0c0;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180152c28,uRam00000001802ef0c0);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = uRam00000001802ef0c0;
      break;
    case 2:
      uRam00000001802ef0c1 = uRam00000001802ef0c0;
      break;
    case 3:
      uVar2 = uRam00000001802ef0c1;
    }
  }
  uRam00000001802ef0c0 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x38d60; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x38d60; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180038d60(undefined8 *param_1)

{
  longlong *plVar1;
  longlong lVar2;
  
  FUN_1800284f0(param_1[1],0x1802eed90,0);
  lVar2 = FUN_180022c90(*param_1,param_1[3]);
  if (lVar2 != 0) {
    plVar1 = (longlong *)((longlong *)*param_1)[1];
    (**(code **)(*plVar1 + 0x1e8))(plVar1,lVar2,*(undefined8 *)(*(longlong *)*param_1 + 0xcb0),0,1);
    return;
  }
  return;
}

// CANDIDATE_LOCAL RVA 0x38dc0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x38dc0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180038dc0(undefined8 *param_1)

{
  undefined8 uVar1;
  int iVar2;
  uint uVar3;
  undefined8 uVar4;
  longlong lVar5;
  longlong lVar6;
  char cVar7;
  longlong lVar8;
  
  uVar4 = FUN_180023f40(*param_1,param_1[5]);
  lVar8 = 0;
  do {
    lVar5 = FUN_180026140(*param_1,uVar4,(int)lVar8 + 9);
    if (lVar5 == 0) {
LAB_180038e00:
      cVar7 = '\0';
    }
    else {
      uVar1 = *param_1;
      lVar6 = FUN_180025d10(uVar1,lVar5);
      if (lVar6 == 0) goto LAB_180038e00;
      iVar2 = FUN_180025c50(uVar1,lVar6);
      if (iVar2 == 0) goto LAB_180038e00;
      if (iVar2 == 0x175) {
        cVar7 = '\x01';
        if (DAT_1802ef080 == '\x01') {
          uVar3 = FUN_180025dc0(uVar1,lVar5);
          if (((uVar3 & 0x4000) != 0) && (cVar7 = '\x02', (uVar3 & 0xf) != 5)) {
            cVar7 = DAT_1802ef0a0 + '\x01';
          }
        }
      }
      else if (iVar2 == 0x11a) {
        cVar7 = DAT_1802ef060 + '\x01';
      }
      else {
        cVar7 = '\x01';
      }
    }
    *(char *)(lVar8 + 0x1802fc5e0) = cVar7;
    lVar8 = lVar8 + 1;
    if (lVar8 == 0x1b) {
      return;
    }
  } while( true );
}

// CANDIDATE_LOCAL RVA 0x38ed0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x38ed0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_180038ed0(int param_1,float param_2,float *param_3)

{
  uint uVar1;
  float fVar2;
  float fVar3;
  char cVar4;
  char cVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  ulonglong uVar8;
  ulonglong uVar9;
  ulonglong uVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  uint uVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  uint uStack_f0;
  float fStack_ec;
  
  uVar6 = FUN_180009dc0((float)(param_1 % 9),(float)(param_1 / 9));
  fVar3 = _DAT_180152ac0;
  fVar2 = _DAT_180152aa4;
  uVar10 = 0xffffffff;
  uVar9 = 0;
  uVar8 = 0xffffffff;
  fStack_ec = _DAT_180152aa0;
  fVar16 = 0.0;
  uStack_f0 = 0xffffffff;
  fVar18 = 0.0;
  fVar15 = _DAT_180152aa0;
  fVar17 = 0.0;
  fVar19 = _DAT_180152aa0;
  do {
    cVar5 = *(char *)(uVar9 + 0x1802fc5e0);
    fVar11 = fVar17;
    if ((cVar5 == '\x02') || ((cVar5 == '\0' && (cVar4 = FUN_18000a460(fVar2), cVar4 == '\0')))) {
      uVar1 = (uint)uVar9;
      uVar7 = FUN_180009dc0((float)(int)(char)((char)uVar9 + (char)((uVar1 & 0xff) / 9) * -9),
                            (float)((uVar1 & 0xff) / 9));
      fVar12 = (float)FUN_180009ee0(uVar6,uVar7);
      fVar13 = (float)FUN_180009f10(uVar6,uVar7);
      uVar14 = FUN_18000a210(fVar13 - param_2);
      fVar12 = fVar12 * fVar3 + (float)(uVar14 & _DAT_180152ab0) * fVar2;
      if (cVar5 == '\0') {
        fVar18 = (float)((uint)fVar18 & -(uint)(fVar19 < fVar12) |
                        ~-(uint)(fVar19 < fVar12) & (uint)fVar13);
        if (fVar12 <= fVar19) {
          fVar19 = fVar12;
          uStack_f0 = uVar1;
        }
      }
      else {
        if (fVar12 <= fVar15) {
          fVar11 = fVar13;
          uVar8 = uVar10;
          fStack_ec = fVar15;
        }
        fVar16 = (float)((uint)fVar16 & -(uint)(fVar15 < fVar12) |
                        ~-(uint)(fVar15 < fVar12) & (uint)fVar17);
        if (fVar12 <= fVar15) {
          uVar10 = uVar9 & 0xffffffff;
          fVar15 = fVar12;
        }
      }
    }
    uVar9 = uVar9 + 1;
    fVar17 = fVar11;
  } while (uVar9 != 0x1b);
  if (fVar19 < fVar15) {
    uVar6 = FUN_18000a050(_DAT_180152ac4,_DAT_180152ac8);
    cVar5 = FUN_18000aa30(0x1802fc620,uVar6,_DAT_180152ad0);
    if (cVar5 != '\0') goto LAB_180039166;
  }
  uStack_f0 = (uint)uVar10;
  fVar19 = fVar15;
  fVar18 = fVar11;
  if (((uint)uVar8 != 0xffffffff) && ((double)fStack_ec < (double)fVar15 * _DAT_180152ad8)) {
    uVar6 = FUN_18000a050(_DAT_180152ac4,_DAT_180152ac8);
    cVar5 = FUN_18000aa30(0x1802fc630,uVar6,_DAT_180152ae0);
    if (cVar5 != '\0') {
      fVar19 = fStack_ec;
      uStack_f0 = (uint)uVar8;
      fVar18 = fVar16;
    }
  }
LAB_180039166:
  *param_3 = fVar19;
  _DAT_1802fc600 = fVar18;
  return uStack_f0;
}

