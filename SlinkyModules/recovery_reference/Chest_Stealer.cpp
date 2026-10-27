// Recovered decompiler view: Chest Stealer
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x48600, 0x488f0); proximity does not prove ownership.

// CANDIDATE_LOCAL RVA 0x48600; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x48600; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Removing unreachable block (ram,0x00018002aad9) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_180048600(longlong param_1)

{
  undefined8 *puVar1;
  longlong lVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  float fVar5;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  lVar2 = FUN_180022c90(*puVar1,puVar1[3]);
  if ((lVar2 != 0) && (uVar3 = FUN_180025bb0(*puVar1,lVar2), (char)uVar3 != '\0')) {
    if (DAT_1802f54e8 != '\x01') {
      return uVar3;
    }
    uVar3 = *puVar1;
    uVar4 = FUN_180025c30(uVar3,lVar2);
    lVar2 = FUN_1800261e0(uVar3,uVar4);
    if (lVar2 != 0) {
      uVar3 = FUN_180026220(*puVar1,lVar2);
      uVar4 = FUN_180048810(*puVar1,uVar3,&UNK_180155f9a);
      if ((char)uVar4 != '\0') {
        return uVar4;
      }
      uVar3 = FUN_180048810(*puVar1,uVar3,&UNK_180155faa);
      if ((char)uVar3 != '\0') {
        return uVar3;
      }
    }
  }
  _DAT_180304a10 = _DAT_1802f54c8;
  uVar3 = FUN_18000a050(_DAT_180155f60,_DAT_180155f64);
  fVar5 = (float)FUN_18000a3e0(uVar3);
  _DAT_180304a10 = fVar5 * _DAT_180304a10;
  return 0x4080000040800000;
}

// UI RVA 0x486f0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x486f0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_1800486f0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180155fee);
  FUN_18000cf30(param_2,param_1,0x1802f5498);
  FUN_18000cf30(param_2,param_1,0x1802f54f0);
  FUN_18000cf30(param_2,param_1,0x1802f5528);
  FUN_18000cef0(param_2,param_1,0x1802f5560);
  FUN_180013e90(param_1,param_2,&UNK_180155fee);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802f54e0,0x1802f54d0,&DAT_1802f54e8);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x48790; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x48790; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180048790(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c450(param_1,&UNK_18015601e,0x1802f5498);
  FUN_18000c450(param_1,&UNK_18015602f,0x1802f54f0);
  FUN_18000c450(param_1,&UNK_180156042,0x1802f5528);
  FUN_18000c3b0(param_1,&UNK_180156048,0x1802f5560);
  uVar1 = uRam00000001802f54e9;
  uVar2 = DAT_1802f54e8;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180156054,DAT_1802f54e8);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802f54e8;
      break;
    case 2:
      uRam00000001802f54e9 = DAT_1802f54e8;
      break;
    case 3:
      uVar2 = uRam00000001802f54e9;
    }
  }
  DAT_1802f54e8 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x48810; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x48810; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


bool FUN_180048810(longlong param_1,undefined8 param_2,undefined8 param_3)

{
  longlong *plVar1;
  int iVar2;
  int iVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  bool bVar7;
  
  plVar1 = *(longlong **)(param_1 + 8);
  uVar4 = (**(code **)(*plVar1 + 0x538))(plVar1,param_3);
  uVar4 = FUN_180027fc0(param_1,uVar4);
  iVar2 = (**(code **)(*plVar1 + 0x520))(plVar1,param_2);
  iVar3 = (**(code **)(*plVar1 + 0x520))(plVar1,uVar4);
  if (iVar3 == iVar2) {
    uVar5 = (**(code **)(*plVar1 + 0x700))(plVar1,param_2,0);
    uVar6 = (**(code **)(*plVar1 + 0x700))(plVar1,uVar4,0);
    iVar2 = func_0x0001800ab860(uVar5,uVar6,(longlong)iVar2 * 2);
    bVar7 = iVar2 == 0;
    (**(code **)(*plVar1 + 0x708))(plVar1,param_2,uVar5);
    (**(code **)(*plVar1 + 0x708))(plVar1,uVar4,uVar6);
  }
  else {
    bVar7 = false;
  }
  return bVar7;
}

