// Recovered decompiler view: Anti Debuff
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x44940, 0x44c90); proximity does not prove ownership.

// CALLBACK RVA 0x44940; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/access_events/access_events.c
// Differential report: analysis/module_behavior_recovery/access_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x44940; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180044940(longlong param_1)

{
  longlong *plVar1;
  code *UNRECOVERED_JUMPTABLE;
  undefined8 *puVar2;
  undefined8 uVar3;
  longlong lVar4;
  
  puVar2 = *(undefined8 **)(param_1 + 8);
  if (DAT_1802f3a88 == '\x01') {
    uVar3 = FUN_180027960(*puVar2,0xf);
    lVar4 = FUN_180023c10(*puVar2,puVar2[5],uVar3);
    if (lVar4 != 0) {
      FUN_1800279c0(*puVar2,lVar4,0);
    }
  }
  if (DAT_1802f3aa8 == '\x01') {
    FUN_180023e60(*puVar2,puVar2[5],0);
    plVar1 = (longlong *)((longlong *)*puVar2)[1];
    UNRECOVERED_JUMPTABLE = *(code **)(*plVar1 + 0x378);
                    /* WARNING: Could not recover jumptable at 0x000180023eb0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE)
              (plVar1,puVar2[5],*(undefined8 *)(*(longlong *)*puVar2 + 0x8d8),UNRECOVERED_JUMPTABLE)
    ;
    return;
  }
  return;
}

// UI RVA 0x449c0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x449c0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_1800449c0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180154cb4);
  FUN_18000cef0(param_2,param_1,0x1802f3a70);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802f3aa0,0x1802f3a90,&DAT_1802f3aa8);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x44a10; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x44a10; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180044a10(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c3b0(param_1,&UNK_180154cbc,0x1802f3a70);
  uVar1 = uRam00000001802f3aa9;
  uVar2 = DAT_1802f3aa8;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180154cc6,DAT_1802f3aa8);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802f3aa8;
      break;
    case 2:
      uRam00000001802f3aa9 = DAT_1802f3aa8;
      break;
    case 3:
      uVar2 = uRam00000001802f3aa9;
    }
  }
  DAT_1802f3aa8 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x44a50; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x44a50; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_180044a50(undefined8 *param_1,undefined8 param_2,undefined8 param_3,char param_4)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  longlong lVar6;
  longlong lVar7;
  float fVar8;
  float fVar9;
  
  uVar2 = 2;
  if ((DAT_1802f3ac4 == '\x01') && ((param_4 != '\0' || (DAT_1802f3cd8 == '\0')))) {
    if ((DAT_1802f3cf8 == '\x01') && (cVar1 = FUN_1800380b0(*param_1,param_1[5]), cVar1 == '\0')) {
      uVar2 = 2;
    }
    else {
      lVar6 = FUN_180024120(*param_1,param_3);
      if (lVar6 == 0) {
        uVar2 = 2 - DAT_1802f3d18;
      }
      else {
        uVar2 = FUN_18002acb0(*param_1,lVar6);
        if (((DAT_1802f3d38 & (uVar2 & 5) != 0) == 0) &&
           ((DAT_1802f3d58 & (byte)((uVar2 & 2) >> 1)) == 0)) {
          lVar7 = FUN_180024120(*param_1,param_2);
          if (lVar7 == 0) {
            uVar2 = 0;
          }
          else {
            uVar2 = 2;
            if (DAT_1802f3d78 == '\x01') {
              if (_DAT_1802f3dc0 == 1) {
                fVar8 = (float)FUN_180023a40(*param_1,lVar7);
                fVar9 = (float)FUN_180023a40(*param_1,lVar6);
                if (fVar8 < fVar9) {
                  return 1;
                }
                if (fVar9 < fVar8) {
                  return 0;
                }
              }
              else if (_DAT_1802f3dc0 == 0) {
                iVar3 = FUN_1800239f0(*param_1,lVar7);
                iVar4 = FUN_1800239f0(*param_1,lVar6);
                if (iVar3 < iVar4) {
                  return 1;
                }
                if (iVar4 < iVar3) {
                  return 0;
                }
              }
              iVar3 = FUN_180023760(*param_1,lVar7);
              iVar4 = FUN_180023720(*param_1,lVar7);
              uVar2 = ((uint)(iVar4 + iVar3) >> 0x10 ^ iVar4 + iVar3) * 0x45d9f3b;
              uVar2 = (uVar2 >> 0x10 ^ uVar2) * 0x45d9f3b;
              iVar3 = FUN_180023760(*param_1,lVar6);
              iVar4 = FUN_180023720(*param_1,lVar6);
              uVar5 = ((uint)(iVar4 + iVar3) >> 0x10 ^ iVar4 + iVar3) * 0x45d9f3b;
              uVar5 = (uVar5 >> 0x10 ^ uVar5) * 0x45d9f3b;
              uVar2 = (uint)((int)(uVar5 >> 0x10 ^ uVar5) <= (int)(uVar2 >> 0x10 ^ uVar2));
            }
          }
        }
        else {
          uVar2 = 1;
        }
      }
    }
  }
  return uVar2;
}

// CANDIDATE_LOCAL RVA 0x44c40; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x44c40; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


undefined8 FUN_180044c40(undefined8 *param_1)

{
  char cVar1;
  undefined8 uVar2;
  
  uVar2 = 0;
  if ((DAT_1802f3ac4 == '\x01') && (DAT_1802f3de8 != '\0')) {
    if ((DAT_1802f3cf8 == '\x01') && (cVar1 = FUN_1800380b0(*param_1,param_1[5]), cVar1 == '\0')) {
      return 0;
    }
    uVar2 = 1;
  }
  return uVar2;
}

