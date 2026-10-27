// Recovered decompiler view: Chams
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x3e880, 0x3e8e0); proximity does not prove ownership.

// DIRECT_BEHAVIOR RVA 0x3e730; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3e730; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003e730(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4,
                  undefined8 param_5,undefined8 param_6,undefined4 param_7,undefined4 param_8)

{
  char cVar1;
  
  if (DAT_1802f0ff4 == '\x01') {
    cVar1 = FUN_18002ace0(param_1,param_3,(uint)DAT_1802f1208 * 5 + 2);
    if (cVar1 == '\0') {
      (*(code *)*_DAT_18013e458)(0x8037);
      (*(code *)*_DAT_180153f78)(_DAT_180153f24,_DAT_180153f28);
      FUN_1800274f0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
                    /* WARNING: Could not recover jumptable at 0x00018003e874. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*(code *)*_DAT_18013e450)(0x8037);
      return;
    }
  }
  FUN_1800274f0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}

// UI RVA 0x3e880; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3e880; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003e880(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180153f61);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802f1200,0x1802f11f0,&DAT_1802f1208);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x3e8c0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3e8c0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003e8c0(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  uVar1 = uRam00000001802f1209;
  uVar2 = DAT_1802f1208;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180153f66,DAT_1802f1208);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802f1208;
      break;
    case 2:
      uRam00000001802f1209 = DAT_1802f1208;
      break;
    case 3:
      uVar2 = uRam00000001802f1209;
    }
  }
  DAT_1802f1208 = uVar2;
  return;
}

