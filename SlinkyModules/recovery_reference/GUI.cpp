// Recovered decompiler view: GUI
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x325c0, 0x328f0); proximity does not prove ownership.

// CALLBACK RVA 0x325c0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/gui/gui.c
// Differential report: analysis/module_behavior_recovery/gui/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x325c0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_1800325c0(longlong param_1)

{
  longlong lVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  char cVar4;
  undefined8 unaff_RBP;
  
  puVar2 = *(undefined8 **)(param_1 + 8);
  cVar4 = FUN_180025840(*puVar2);
  if (cVar4 != '\0') {
    plVar3 = (longlong *)*puVar2;
    lVar1 = *plVar3;
    plVar3 = (longlong *)plVar3[1];
    (**(code **)(*plVar3 + 0x468))
              (plVar3,*(undefined8 *)(lVar1 + 0x88),*(undefined8 *)(lVar1 + 0x98),0,unaff_RBP);
    return;
  }
  return;
}

// CALLBACK RVA 0x32600; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/gui/gui.c
// Differential report: analysis/module_behavior_recovery/gui/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x32600; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180032600(longlong param_1)

{
  undefined8 *puVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined8 uStack_68;
  ulonglong uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  
  if (*(longlong *)(param_1 + 0x10) == 0x1802eb740) {
    puVar1 = *(undefined8 **)(param_1 + 8);
    if (*(char *)(param_1 + 0x18) == '\x01') {
      cVar2 = FUN_180025840(*puVar1);
      if (cVar2 != '\0') {
        iVar3 = FUN_180027a60(*puVar1);
        iVar4 = FUN_180027a90(*puVar1);
        FUN_180025940(*puVar1,iVar3 / 2,iVar4 / 2);
        FUN_180025880(*puVar1,0);
      }
      uRam00000001802fa2c8 = FUN_18004c270();
      uRam00000001802fa2e8 = 0;
      return;
    }
    cVar2 = FUN_180022e60(*puVar1,puVar1[3]);
    if (cVar2 != '\0') {
      FUN_180025880(*puVar1,1);
    }
    FUN_180012a80(0x1802f9e30);
    FUN_180012a90(0x1802f9e30);
    if (DAT_1802fa300 == '\0') {
      uVar5 = FUN_18000bbd0(puVar1[1],puVar1[2]);
      if (uVar5 != 0) {
        uStack_38 = 0;
        uStack_30 = 0;
        uStack_48 = 0;
        uStack_40 = 0;
        uStack_58 = 0;
        uStack_50 = 0;
        uStack_28 = 0;
        uStack_68 = 0xc;
        uStack_60 = (ulonglong)uVar5;
        FUN_180028480(*(undefined8 *)(*(longlong *)(param_1 + 8) + 8),&uStack_68);
      }
    }
  }
  return;
}

// CALLBACK RVA 0x32730; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/gui/gui.c
// Differential report: analysis/module_behavior_recovery/gui/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x32730; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180032730(longlong param_1)

{
  *(byte *)(param_1 + 0x10) = *(byte *)(param_1 + 0x10) | 3;
  return;
}

// CALLBACK RVA 0x32740; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/gui/gui.c
// Differential report: analysis/module_behavior_recovery/gui/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x32740; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180032740(longlong param_1)

{
  longlong lVar1;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  
  lVar1 = *(longlong *)(param_1 + 8);
  FUN_180074130(&uStack_28,_DAT_1802eb728,_DAT_1802eb72c,_DAT_1802eb730);
  _DAT_1802fa190 = uStack_28;
  uRam00000001802fa194 = uStack_24;
  uRam00000001802fa198 = uStack_20;
  uRam00000001802fa19c = uStack_1c;
  DAT_1802fa2fc = DAT_1802eb9e8;
  DAT_1802fa2fd = DAT_1802eba08;
  FUN_180011820(0x1802f9e30,*(undefined8 *)(param_1 + 0x10),*(undefined8 *)(lVar1 + 8),
                *(undefined8 *)(lVar1 + 0x10));
  return;
}

// CALLBACK RVA 0x327c0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/gui/gui.c
// Differential report: analysis/module_behavior_recovery/gui/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x327c0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_1800327c0(void)

{
  DAT_1802fa300 = 1;
  return;
}

// UI RVA 0x327d0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x327d0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_1800327d0(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180151630);
  FUN_18000d040(param_2,param_1,0x1802eb970);
  FUN_18000d0a0(param_2,param_1,0x1802eb720);
  FUN_18000cef0(param_2,param_1,0x1802eb9b0);
  FUN_180013e90(param_1,param_2,&UNK_180151635);
  FUN_18000cef0(param_2,param_1,0x1802eb9d0);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802eba00,0x1802eb9f0,&DAT_1802eba08);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x32870; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x32870; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180032870(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c6f0(param_1,&UNK_18015163c,0x1802eb970);
  FUN_18000c7e0(param_1,&UNK_180151642,0x1802eb720);
  FUN_18000c3b0(param_1,&UNK_18015164f,0x1802eb9b0);
  FUN_18000c3b0(param_1,&UNK_18015165b,0x1802eb9d0);
  uVar1 = uRam00000001802eba09;
  uVar2 = DAT_1802eba08;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180151663,DAT_1802eba08);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802eba08;
      break;
    case 2:
      uRam00000001802eba09 = DAT_1802eba08;
      break;
    case 3:
      uVar2 = uRam00000001802eba09;
    }
  }
  DAT_1802eba08 = uVar2;
  return;
}

