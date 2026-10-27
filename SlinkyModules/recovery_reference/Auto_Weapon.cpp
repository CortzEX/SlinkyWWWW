// Recovered decompiler view: Auto Weapon
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x4a340, 0x4a520); proximity does not prove ownership.

// CALLBACK RVA 0x4a340; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/auto_weapon/auto_weapon.c
// Differential report: analysis/module_behavior_recovery/auto_weapon/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x4a340; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18004a340(longlong param_1)

{
  undefined8 *puVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  undefined8 uVar6;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  if ((((*(char *)(puVar1 + 8) == '\x01') &&
       (cVar2 = FUN_180023f90(*puVar1,puVar1[5]), cVar2 == '\0')) &&
      ((DAT_1802f5d58 != '\x01' || (cVar2 = FUN_180029080(puVar1), cVar2 != '\0')))) &&
     ((lVar5 = FUN_180022e10(*puVar1,puVar1[3]), lVar5 != 0 &&
      (iVar3 = FUN_180024b50(*puVar1,lVar5), iVar3 == 2)))) {
    uVar6 = FUN_180024e30(*puVar1,lVar5);
    lVar5 = FUN_180023f00(*puVar1,uVar6);
    if ((lVar5 != 0) &&
       ((cVar2 = FUN_18002ace0(*puVar1,lVar5,7), cVar2 == '\0' &&
        (cVar2 = FUN_1800380b0(*puVar1,puVar1[5]), cVar2 == '\0')))) {
      uVar6 = FUN_180023f40(*puVar1,puVar1[5]);
      iVar3 = FUN_180025a60(*puVar1,uVar6);
      iVar4 = FUN_1800380c0(puVar1,uVar6);
      if ((iVar4 != -1) && (iVar3 != iVar4)) {
        if ((float)_DAT_180304ae8 < _DAT_1802f5d38) {
          _DAT_180304ae8 = _DAT_180304ae8 + 1;
          return;
        }
        cVar2 = FUN_18002aa80(0x1802f5af8);
        if (cVar2 == '\0') {
          return;
        }
        FUN_180025a80(*puVar1,uVar6,iVar4);
        if (_DAT_1802f7ba8 == 0x1802f5af8) {
          _DAT_1802f7ba8 = 0;
          return;
        }
        return;
      }
    }
  }
  _DAT_180304ae8 = 0;
  return;
}

// UI RVA 0x4a480; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x4a480; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18004a480(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_18015663e);
  FUN_18000cf30(param_2,param_1,0x1802f5d08);
  FUN_180013e90(param_1,param_2,&UNK_180156643);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802f5d50,0x1802f5d40,&DAT_1802f5d58);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x4a4e0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x4a4e0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18004a4e0(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c450(param_1,&UNK_18015664e,0x1802f5d08);
  uVar1 = uRam00000001802f5d59;
  uVar2 = DAT_1802f5d58;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_18015665e,DAT_1802f5d58);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802f5d58;
      break;
    case 2:
      uRam00000001802f5d59 = DAT_1802f5d58;
      break;
    case 3:
      uVar2 = uRam00000001802f5d59;
    }
  }
  DAT_1802f5d58 = uVar2;
  return;
}

