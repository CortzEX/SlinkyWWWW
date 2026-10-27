// Recovered decompiler view: Speed
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x4bbc0, 0x4bc60); proximity does not prove ownership.

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

