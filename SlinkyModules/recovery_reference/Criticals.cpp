// Recovered decompiler view: Criticals
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x32f10, 0x334c0); proximity does not prove ownership.

// CALLBACK RVA 0x32f10; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/criticals/criticals.c
// Differential report: analysis/module_behavior_recovery/criticals/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x32f10; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong FUN_180032f10(longlong param_1)

{
  undefined8 *puVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  ulonglong uVar5;
  longlong lVar6;
  ulonglong uVar7;
  undefined1 auStack_30 [8];
  double dStack_28;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  if (*(char *)(puVar1 + 8) == '\x01') {
    if (_DAT_1802fa328 == 0) {
      _DAT_1802fa328 = 10;
      DAT_1802fa32c = FUN_18000a460(_DAT_1802ec288);
      _DAT_1802fa328 = _DAT_1802fa328 + -1;
      if (DAT_1802fa32c != '\0') goto LAB_180032f73;
    }
    else {
      _DAT_1802fa328 = _DAT_1802fa328 + -1;
      if (DAT_1802fa32c == '\x01') {
LAB_180032f73:
        if (((DAT_1802ec2a8 != '\x01') || (cVar2 = FUN_180029080(puVar1), cVar2 != '\0')) &&
           ((DAT_1802ec2c8 != '\x01' || (cVar2 = FUN_1800380b0(*puVar1), cVar2 != '\0')))) {
          iVar3 = FUN_1800239d0(*puVar1,puVar1[5]);
          iVar4 = FUN_180023760(*puVar1);
          uVar7 = (ulonglong)CONCAT31((int3)((uint)(iVar4 - iVar3) >> 8),iVar4 - iVar3 < 0xb);
          goto LAB_180032fc7;
        }
      }
    }
  }
  uVar7 = 0;
LAB_180032fc7:
  if (_DAT_1802ec310 == 1) {
    LOCK();
    DAT_1802fa320 = '\0';
    UNLOCK();
    if ((char)uVar7 == '\0') {
      DAT_1802fa320 = 0;
      DAT_1802fa324 = 0;
      return uVar7;
    }
    uVar5 = FUN_180023780(*puVar1,puVar1[5]);
    if ((((char)uVar5 == '\0') &&
        (uVar5 = FUN_180023550(auStack_30,*puVar1,puVar1[5]), dStack_28 < 0.0)) &&
       (uVar5 = FUN_1800239f0(*puVar1,puVar1[5]), (int)uVar5 != 10)) {
      lVar6 = FUN_180022e10(*puVar1,puVar1[3]);
      uVar5 = 0;
      if (lVar6 != 0) {
        uVar7 = FUN_180024b50(*puVar1,lVar6);
        DAT_1802fa324 = (int)uVar7 == 2;
        return uVar7;
      }
    }
  }
  else {
    if (_DAT_1802ec310 != 0) {
      return uVar7;
    }
    LOCK();
    UNLOCK();
    LOCK();
    uVar5 = (ulonglong)CONCAT22((short)((uint)(int)_DAT_1802ec250 >> 0x10),_DAT_1802fa322);
    UNLOCK();
    DAT_1802fa320 = (char)uVar7;
    _DAT_1802fa322 = (short)(int)_DAT_1802ec250;
  }
  DAT_1802fa324 = 0;
  return uVar5;
}

// CALLBACK RVA 0x33080; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/criticals/criticals.c
// Differential report: analysis/module_behavior_recovery/criticals/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x33080; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180033080(longlong param_1)

{
  undefined8 *puVar1;
  double dVar2;
  undefined8 uVar3;
  float fVar4;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  uVar3 = FUN_180022c70(*puVar1,puVar1[3]);
  dVar2 = _DAT_1802fa330;
  if (DAT_1802fa324 == '\x01') {
    FUN_1800259c0(*puVar1,uVar3,_DAT_1802ec350);
    DAT_1802fa32d = '\x01';
    _DAT_1802fa330 =
         (double)(_DAT_180151810 - _DAT_1802ec350) * *(double *)(param_1 + 0x18) * _DAT_180151818 +
         _DAT_1802fa330;
    if ((double)_DAT_1802ec388 < _DAT_1802fa330) {
      _DAT_1802fa330 = (double)_DAT_1802ec388;
    }
  }
  else {
    if (_DAT_180151808 < _DAT_1802fa330) {
      fVar4 = (float)FUN_1800259f0(*puVar1,uVar3);
      FUN_180025a10(*puVar1,uVar3,(float)(int)dVar2 + fVar4);
      _DAT_1802fa330 = _DAT_1802fa330 - (double)(int)dVar2;
    }
    if (DAT_1802fa32d == '\x01') {
      FUN_1800259c0(*puVar1,uVar3,_DAT_180151810);
      DAT_1802fa32d = '\0';
    }
  }
  return;
}

// CALLBACK RVA 0x331a0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/criticals/criticals.c
// Differential report: analysis/module_behavior_recovery/criticals/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x331a0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800331a0(longlong param_1)

{
  char cVar1;
  byte bVar2;
  uint uVar3;
  longlong lVar4;
  double dVar5;
  
  lVar4 = FUN_180026350(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10));
  if (((lVar4 != 0) && (cVar1 = FUN_180026390(*(undefined8 *)(param_1 + 8),lVar4), cVar1 != '\0'))
     && (_DAT_1802fa348 < *(int *)(param_1 + 0x20))) {
    dVar5 = (double)FUN_180026410(*(undefined8 *)(param_1 + 8),lVar4);
    bVar2 = FUN_1800263c0(*(undefined8 *)(param_1 + 8),lVar4);
    if ((bVar2 != 0) || (dVar5 < _DAT_1802fa340)) {
      DAT_1802fa34c = bVar2 ^ 1;
    }
    uVar3 = 0;
    if ((((DAT_1802fa320 & 1) != 0) && (uVar3 = 0, (DAT_1802fa34c & 1) != 0)) &&
       (uVar3 = _DAT_1802fa322 / 5 + _DAT_1802fa338, (int)(uint)_DAT_1802fa322 < (int)uVar3)) {
      uVar3 = (uint)_DAT_1802fa322;
    }
    _DAT_1802fa338 = uVar3;
    _DAT_1802fa348 = *(int *)(param_1 + 0x20);
    _DAT_1802fa340 = dVar5;
  }
  if (*(longlong *)(param_1 + 0x18) < (longlong)(int)_DAT_1802fa338) {
    *(undefined4 *)(param_1 + 0x24) = 1;
  }
  return;
}

// CALLBACK RVA 0x332b0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/criticals/criticals.c
// Differential report: analysis/module_behavior_recovery/criticals/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x332b0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800332b0(longlong param_1)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  
  if (((*(longlong *)(param_1 + 0x10) == 0x1802ec010) && (*(char *)(param_1 + 0x18) == '\0')) &&
     ((DAT_1802fa32d & 1) != 0)) {
    puVar1 = *(undefined8 **)(param_1 + 8);
    uVar2 = FUN_180022c70(*puVar1,puVar1[3]);
    FUN_1800259c0(*puVar1,uVar2,_DAT_180151820);
    DAT_1802fa32d = 0;
  }
  return;
}

// UI RVA 0x33310; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x33310; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180033310(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  undefined8 uVar2;
  
  FUN_180013e90(param_1,param_2,&UNK_1801518c4);
  FUN_18000d040(param_2,param_1,0x1802ec2e0);
  FUN_18000cf30(param_2,param_1,0x1802ec258);
  if (_DAT_1802ec310 == 0) {
    uVar2 = 0x1802ec220;
  }
  else {
    FUN_18000cf30(param_2,param_1,0x1802ec320);
    uVar2 = 0x1802ec358;
  }
  FUN_18000cf30(param_2,param_1,uVar2);
  FUN_180013e90(param_1,param_2,&UNK_1801518c9);
  FUN_18000cef0(param_2,param_1,0x1802ec2b0);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802ec2a0,0x1802ec290,&DAT_1802ec2a8);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x333d0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x333d0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_1800333d0(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c6f0(param_1,&UNK_1801518d4,0x1802ec2e0);
  FUN_18000c450(param_1,&UNK_1801518d9,0x1802ec258);
  FUN_18000c450(param_1,&UNK_1801518e0,0x1802ec220);
  FUN_18000c450(param_1,&UNK_1801518ea,0x1802ec320);
  FUN_18000c450(param_1,&UNK_1801518f6,0x1802ec358);
  FUN_18000c3b0(param_1,&UNK_1801518fc,0x1802ec2b0);
  uVar1 = uRam00000001802ec2a9;
  uVar2 = DAT_1802ec2a8;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_18015190b,DAT_1802ec2a8);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802ec2a8;
      break;
    case 2:
      uRam00000001802ec2a9 = DAT_1802ec2a8;
      break;
    case 3:
      uVar2 = uRam00000001802ec2a9;
    }
  }
  DAT_1802ec2a8 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x33480; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x33480; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180033480(undefined8 param_1)

{
  FUN_1800ab710(param_1,0x20,&UNK_180151921,
                *(undefined8 *)((ulonglong)_DAT_1802ec310 * 8 + 0x1802ec2d0));
  return;
}

