// Recovered decompiler view: Chest ESP
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x33990, 0x33fc0); proximity does not prove ownership.

// CALLBACK RVA 0x33990; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/chest_esp/chest_esp.c
// Differential report: analysis/module_behavior_recovery/chest_esp/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x33990; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180033990(longlong param_1)

{
  undefined8 *puVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  longlong lVar7;
  longlong lVar8;
  double dVar9;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined8 uStack_a0;
  undefined1 auStack_98 [16];
  undefined8 uStack_88;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined8 uStack_68;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined8 uStack_48;
  
  _DAT_1802fa360 = 0;
  puVar1 = *(undefined8 **)(param_1 + 8);
  if (puVar1[4] != 0) {
    FUN_180023030(&uStack_b0,*puVar1,puVar1[5]);
    uVar5 = FUN_180024640(*puVar1,puVar1[4]);
    iVar3 = FUN_180024e50(*puVar1,uVar5);
    if (0 < iVar3) {
      iVar3 = 0;
      do {
        uVar6 = FUN_180024e80(*puVar1,uVar5,iVar3);
        lVar7 = FUN_1800244f0(*puVar1,uVar6);
        if (lVar7 != 0) {
          iVar4 = FUN_180024280(*puVar1,lVar7);
          if (iVar4 < 0x8a) {
            cVar2 = DAT_1802ecb68;
            if ((iVar4 == 0x36) || (cVar2 = DAT_1802ecb88, iVar4 == 0x82)) {
joined_r0x000180033a95:
              if (cVar2 != '\0') {
LAB_180033ab9:
                FUN_180024510(&uStack_58,*puVar1,uVar6);
                uStack_88 = uStack_48;
                uStack_68 = uStack_a0;
                uStack_78 = uStack_b0;
                uStack_74 = uStack_ac;
                uStack_70 = uStack_a8;
                uStack_6c = uStack_a4;
                dVar9 = (double)FUN_1800094b0(auStack_98,&uStack_78);
                if (dVar9 <= (double)(_DAT_1802ecb48 * _DAT_1802ecb48)) {
                  lVar7 = _DAT_1802fa360 + 1;
                  lVar8 = _DAT_1802fa360 * 0x20;
                  _DAT_1802fa360 = lVar7;
                  *(undefined4 *)(lVar8 + 0x1802fa370) = uStack_58;
                  *(undefined4 *)(lVar8 + 0x1802fa374) = uStack_54;
                  *(undefined4 *)(lVar8 + 0x1802fa378) = uStack_50;
                  *(undefined4 *)(lVar8 + 0x1802fa37c) = uStack_4c;
                  *(undefined8 *)(lVar8 + 0x1802fa380) = uStack_48;
                  *(int *)(lVar8 + 0x1802fa388) = iVar4;
                  if (lVar7 == 100) {
                    return;
                  }
                }
              }
            }
          }
          else if (iVar4 == 0x8a) {
            if (DAT_1802ecbc8 == '\x01') goto LAB_180033ab9;
          }
          else {
            cVar2 = DAT_1802ecba8;
            if (iVar4 == 0x92) goto joined_r0x000180033a95;
          }
        }
        iVar3 = iVar3 + 1;
        iVar4 = FUN_180024e50(*puVar1,uVar5);
      } while (iVar3 < iVar4);
    }
  }
  return;
}

// CALLBACK RVA 0x33b60; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/chest_esp/chest_esp.c
// Differential report: analysis/module_behavior_recovery/chest_esp/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x33b60; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180033b60(longlong param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  ulonglong uVar6;
  undefined4 *puVar7;
  double *pdVar8;
  undefined1 auStack_d0 [24];
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  double dStack_98;
  double dStack_90;
  double dStack_88;
  
  FUN_1800293c0();
  (*(code *)*_DAT_180150cb0)(_DAT_1802ecc00);
  uVar5 = _UNK_180151ad8;
  uVar4 = _DAT_180151ad0;
  uVar3 = _DAT_180151a64;
  uVar2 = _DAT_180151a60;
  if (_DAT_1802fa360 != 0) {
    pdVar8 = (double *)0x1802fa370;
    uVar6 = 0;
    do {
      iVar1 = *(int *)(pdVar8 + 3);
      puVar7 = (undefined4 *)0x1802ecc10;
      if (iVar1 != 0x82) {
        if (iVar1 == 0x8a) {
          puVar7 = (undefined4 *)0x1802ecc50;
        }
        else if (iVar1 == 0x92) {
          puVar7 = (undefined4 *)0x1802ecc30;
        }
        else {
          puVar7 = (undefined4 *)0x1802ecc70;
        }
      }
      dStack_88 = pdVar8[2];
      dStack_98 = *pdVar8;
      dStack_90 = pdVar8[1];
      uStack_a8 = *(undefined8 *)(param_1 + 0x18);
      uStack_b8 = *(undefined8 *)(param_1 + 8);
      uStack_b0 = *(undefined8 *)(param_1 + 0x10);
      FUN_1800093d0(auStack_d0,&dStack_98,&uStack_b8);
      uStack_b8 = uVar4;
      uStack_b0 = uVar5;
      uStack_a8 = 0x3fe0000000000000;
      FUN_180009400(&dStack_98,auStack_d0,&uStack_b8);
      (*(code *)*_DAT_180150cc0)();
      (*(code *)*_DAT_180150cd8)((float)dStack_98,(float)dStack_90,(float)dStack_88);
      (*(code *)*_DAT_180150cd0)(uVar2,uVar2,uVar2);
      if (DAT_1802ecca0 == '\x01') {
        (*(code *)*_DAT_18013e448)(*puVar7,puVar7[1],puVar7[2],uVar3);
        FUN_180029400();
      }
      (*(code *)*_DAT_180150ca0)(*puVar7,puVar7[1],puVar7[2]);
      FUN_180029430();
      (*(code *)*_DAT_180150cb8)();
      uVar6 = uVar6 + 1;
      pdVar8 = pdVar8 + 4;
    } while (uVar6 < _DAT_1802fa360);
  }
  FUN_1800295a0();
  return;
}

// UI RVA 0x33d60; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x33d60; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180033d60(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180151b03);
  FUN_18000cf30(param_2,param_1,0x1802ecb18);
  FUN_180013e90(param_1,param_2,&UNK_180151b08);
  FUN_18000cef0(param_2,param_1,0x1802ecb50);
  FUN_18000cef0(param_2,param_1,0x1802ecb70);
  FUN_18000cef0(param_2,param_1,0x1802ecb90);
  FUN_18000cef0(param_2,param_1,0x1802ecbb0);
  FUN_180013e90(param_1,param_2,&UNK_180151b0f);
  FUN_18000cf30(param_2,param_1,0x1802ecbd0);
  if (DAT_1802ecb68 == '\x01') {
    FUN_18000d0a0(param_2,param_1,0x1802ecc68);
  }
  if (DAT_1802ecb88 == '\x01') {
    FUN_18000d0a0(param_2,param_1,0x1802ecc08);
  }
  if (DAT_1802ecba8 == '\x01') {
    FUN_18000d0a0(param_2,param_1,0x1802ecc28);
  }
  if (DAT_1802ecbc8 == '\x01') {
    FUN_18000d0a0(param_2,param_1,0x1802ecc48);
  }
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802ecc98,0x1802ecc88,&DAT_1802ecca0);
  if (cVar1 == '\0') {
    return;
  }
  DAT_1802f7338 = 1;
  return;
}

// SETTINGS RVA 0x33eb0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x33eb0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180033eb0(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c450(param_1,&UNK_180151b1d,0x1802ecb18);
  FUN_18000c3b0(param_1,&UNK_180151b23,0x1802ecb50);
  FUN_18000c3b0(param_1,&UNK_180151b30,0x1802ecb70);
  FUN_18000c3b0(param_1,&UNK_180151b43,0x1802ecb90);
  FUN_18000c3b0(param_1,&UNK_180151b58,0x1802ecbb0);
  FUN_18000c450(param_1,&UNK_180151b66,0x1802ecbd0);
  FUN_18000c7e0(param_1,&UNK_180151b71,0x1802ecc68);
  FUN_18000c7e0(param_1,&UNK_180151b7d,0x1802ecc08);
  FUN_18000c7e0(param_1,&UNK_180151b8f,0x1802ecc28);
  FUN_18000c7e0(param_1,&UNK_180151ba3,0x1802ecc48);
  uVar1 = uRam00000001802ecca1;
  uVar2 = DAT_1802ecca0;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180151bb0,DAT_1802ecca0);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802ecca0;
      break;
    case 2:
      uRam00000001802ecca1 = DAT_1802ecca0;
      break;
    case 3:
      uVar2 = uRam00000001802ecca1;
    }
  }
  DAT_1802ecca0 = uVar2;
  return;
}

