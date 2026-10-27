// Recovered decompiler view: Fake Lag
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x32b30, 0x32f10); proximity does not prove ownership.

// CALLBACK RVA 0x32b30; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/fake_lag/fake_lag.c
// Differential report: analysis/module_behavior_recovery/fake_lag/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x32b30; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_180032b30(longlong param_1)

{
  undefined8 *puVar1;
  bool bVar2;
  uint uVar3;
  char cVar4;
  byte bVar5;
  int iVar6;
  uint uVar7;
  
  uVar3 = _DAT_1802fa310;
  uVar7 = _DAT_1802fa30c;
  if (0 < _DAT_1802fa308) {
    _DAT_1802fa308 = _DAT_1802fa308 + -1;
  }
  DAT_1802fa314 = DAT_1802ebf58;
  LOCK();
  UNLOCK();
  if (_DAT_1802ebfa0 == 1) {
    bVar2 = (int)_DAT_1802fa30c < 1;
    if (bVar2) {
      _DAT_1802fa30c = (uint)((float)(int)_DAT_1802fa30c + _DAT_1802ebf00);
    }
    else {
      _DAT_1802fa30c = _DAT_1802fa30c - 0x32;
    }
    DAT_1802fa315 = !bVar2 && uVar7 < 0x33;
    LOCK();
    UNLOCK();
    bVar2 = (int)_DAT_1802fa310 < 1;
    if (bVar2) {
      _DAT_1802fa310 = (uint)((float)(int)_DAT_1802fa310 + _DAT_1802ebf38);
    }
    else {
      _DAT_1802fa310 = _DAT_1802fa310 - 0x32;
    }
    DAT_1802fa316 = !bVar2 && uVar3 < 0x33;
    LOCK();
    UNLOCK();
  }
  puVar1 = *(undefined8 **)(param_1 + 8);
  if ((puVar1[4] == 0) || ((DAT_1802ebfc8 == '\x01' && (*(char *)(puVar1 + 8) == '\0')))) {
    _DAT_1802fa308 = 0;
  }
  else {
    iVar6 = FUN_1800239d0(*puVar1,puVar1[5]);
    if ((DAT_1802ebfe8 == '\x01') && (cVar4 = FUN_1800380b0(*puVar1,puVar1[5]), cVar4 == '\0')) {
      _DAT_1802fa308 = 0;
      bVar5 = 0;
    }
    else {
      bVar5 = DAT_1802ec008 ^ 1 | _DAT_1802fa308 != 0;
    }
    if (iVar6 != _DAT_1802fa304) {
      _DAT_1802fa308 = 0x14;
    }
    _DAT_1802fa304 = iVar6;
    if (bVar5 != 0) {
      LOCK();
      UNLOCK();
      LOCK();
      uVar7 = CONCAT22((short)((uint)(int)_DAT_1802ebf38 >> 0x10),_DAT_1802fa31a);
      UNLOCK();
      _DAT_1802fa318 = (short)(int)_DAT_1802ebf00;
      _DAT_1802fa31a = (short)(int)_DAT_1802ebf38;
      return uVar7;
    }
  }
  LOCK();
  UNLOCK();
  LOCK();
  uVar7 = (uint)_DAT_1802fa318;
  UNLOCK();
  _DAT_1802fa31a = 0;
  _DAT_1802fa318 = 0;
  return uVar7;
}

// CALLBACK RVA 0x32cb0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/fake_lag/fake_lag.c
// Differential report: analysis/module_behavior_recovery/fake_lag/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x32cb0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180032cb0(int *param_1)

{
  longlong *plVar1;
  ushort uVar2;
  byte bVar3;
  longlong lVar4;
  int iVar5;
  
  uVar2 = _DAT_1802fa31a;
  bVar3 = DAT_1802fa316;
  if ((*param_1 == 2) && (uVar2 = _DAT_1802fa318, bVar3 = DAT_1802fa315, (DAT_1802fa314 & 1) != 0))
  {
    lVar4 = FUN_180026a30(*(undefined8 *)(param_1 + 2),*(undefined8 *)(param_1 + 4));
    iVar5 = 3;
    if ((lVar4 != 0) ||
       ((lVar4 = FUN_180026ad0(*(undefined8 *)(param_1 + 2),*(undefined8 *)(param_1 + 4)),
        lVar4 != 0 ||
        (lVar4 = FUN_180026a90(*(undefined8 *)(param_1 + 2),*(undefined8 *)(param_1 + 4)),
        uVar2 = _DAT_1802fa318, bVar3 = DAT_1802fa315, lVar4 != 0)))) goto LAB_180032d46;
  }
  if ((bVar3 & 1) != 0) {
    return;
  }
  plVar1 = (longlong *)(param_1 + 6);
  *plVar1 = *plVar1 - (ulonglong)uVar2;
  if (-1 < *plVar1) {
    return;
  }
  param_1[6] = 0;
  param_1[7] = 0;
  iVar5 = 1;
LAB_180032d46:
  param_1[9] = iVar5;
  return;
}

// UI RVA 0x32d60; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x32d60; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180032d60(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_18015179c);
  FUN_18000d040(param_2,param_1,0x1802ebf70);
  FUN_18000cf30(param_2,param_1,0x1802ebed0);
  FUN_18000cf30(param_2,param_1,0x1802ebf08);
  FUN_18000cef0(param_2,param_1,0x1802ebf40);
  FUN_180013e90(param_1,param_2,&UNK_1801517a2);
  FUN_18000cef0(param_2,param_1,0x1802ebfd0);
  FUN_18000cef0(param_2,param_1,0x1802ebff0);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802ebfc0,0x1802ebfb0,&DAT_1802ebfc8);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x32e20; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x32e20; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180032e20(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c6f0(param_1,&UNK_1801517ad,0x1802ebf70);
  FUN_18000c450(param_1,&UNK_1801517b2,0x1802ebed0);
  FUN_18000c450(param_1,&UNK_1801517ba,0x1802ebf08);
  FUN_18000c3b0(param_1,&UNK_1801517c3,0x1802ebf40);
  FUN_18000c3b0(param_1,&UNK_1801517d3,0x1802ebfd0);
  FUN_18000c3b0(param_1,&UNK_1801517e2,0x1802ebff0);
  uVar1 = uRam00000001802ebfc9;
  uVar2 = DAT_1802ebfc8;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_1801517f1,DAT_1802ebfc8);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802ebfc8;
      break;
    case 2:
      uRam00000001802ebfc9 = DAT_1802ebfc8;
      break;
    case 3:
      uVar2 = uRam00000001802ebfc9;
    }
  }
  DAT_1802ebfc8 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x32ed0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x32ed0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180032ed0(undefined8 param_1)

{
  FUN_1800ab710(param_1,0x20,&UNK_180151800,
                *(undefined8 *)((ulonglong)_DAT_1802ebfa0 * 8 + 0x1802ebf60));
  return;
}

