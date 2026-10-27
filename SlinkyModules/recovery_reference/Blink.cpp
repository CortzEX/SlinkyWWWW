// Recovered decompiler view: Blink
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x33660, 0x33990); proximity does not prove ownership.

// CALLBACK RVA 0x33660; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/blink/blink.c
// Differential report: analysis/module_behavior_recovery/blink/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x33660; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong FUN_180033660(longlong param_1)

{
  longlong lVar1;
  undefined8 *puVar2;
  longlong lVar3;
  bool bVar4;
  int iVar5;
  code *pcVar6;
  ulonglong in_RAX;
  longlong *plVar7;
  ulonglong uVar8;
  undefined8 unaff_RSI;
  undefined8 uStack_78;
  undefined8 uStack_70;
  ulonglong uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  
  puVar2 = *(undefined8 **)(param_1 + 8);
  if (*(char *)(puVar2 + 8) == '\x01') {
    uStack_40 = 0x180033681;
    in_RAX = FUN_1800239d0(*puVar2,puVar2[5]);
    iVar5 = (int)in_RAX;
    bVar4 = _DAT_1802fa354 < iVar5;
    _DAT_1802fa358 = _DAT_1802fa358 + -1;
    _DAT_1802fa354 = iVar5;
    if ((_DAT_1802fa358 == 0) || ((bVar4 & DAT_1802ec828) != 0)) {
      lVar3 = puVar2[1];
      uVar8 = CONCAT71((int7)((ulonglong)unaff_RSI >> 8),1);
      if (cRam00000001802ec614 != '\0') {
        uStack_48 = 0;
        uStack_40 = 0;
        uStack_58 = 0;
        uStack_50 = 0;
        uStack_68 = 0;
        uStack_60 = 0;
        uStack_38 = 0;
        uStack_78 = 4;
        uStack_70 = 0x1802ec600;
        plVar7 = *(longlong **)(lVar3 + 0x230);
        pcVar6 = (code *)*plVar7;
        if (pcVar6 != (code *)0x0) {
          do {
            plVar7 = plVar7 + 1;
            (*pcVar6)(&uStack_78);
            pcVar6 = (code *)*plVar7;
          } while (pcVar6 != (code *)0x0);
          if ((uStack_68 & 1) != 0) {
            uVar8 = 0;
            goto LAB_1800285a1;
          }
        }
        lVar1 = *(longlong *)(lVar3 + 0x300);
        *(undefined8 *)(*(longlong *)(lVar3 + 0x2f8) + lVar1 * 8) = 0x1802ec600;
        *(longlong *)(lVar3 + 0x300) = lVar1 + 1;
      }
LAB_1800285a1:
      return uVar8 & 0xffffffff;
    }
  }
  return in_RAX;
}

// CALLBACK RVA 0x336d0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/blink/blink.c
// Differential report: analysis/module_behavior_recovery/blink/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x336d0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_1800336d0(longlong param_1)

{
  longlong lVar1;
  int iVar2;
  
  if (DAT_1802fa35c != '\x01') {
    lVar1 = FUN_180026a30(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10));
    iVar2 = 3;
    if (lVar1 == 0) {
      lVar1 = FUN_180026ad0(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10));
      if (lVar1 == 0) {
        lVar1 = FUN_180026a90(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10));
        if (lVar1 == 0) {
          lVar1 = FUN_180027160(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10));
          iVar2 = (uint)(lVar1 != 0) * 2 + 1;
        }
      }
    }
    *(int *)(param_1 + 0x24) = iVar2;
  }
  return;
}

// CALLBACK RVA 0x33750; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/blink/blink.c
// Differential report: analysis/module_behavior_recovery/blink/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x33750; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180033750(longlong param_1)

{
  if (DAT_1802fa35c != '\0') {
    *(undefined4 *)(param_1 + 0x24) = 1;
  }
  return;
}

// CALLBACK RVA 0x33770; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/blink/blink.c
// Differential report: analysis/module_behavior_recovery/blink/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x33770; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong FUN_180033770(longlong param_1)

{
  byte bVar1;
  
  bVar1 = DAT_1802fa35c;
  if ((*(longlong *)(param_1 + 0x10) == 0x1802ec600) && (*(char *)(param_1 + 0x18) == '\x01')) {
    _DAT_1802fa358 = (int)(longlong)_DAT_1802ec860;
    _DAT_1802fa354 = 0x7fffffff;
    LOCK();
    DAT_1802fa35c = DAT_1802ec8b8;
    UNLOCK();
    return (ulonglong)bVar1;
  }
  return 0x1802ec600;
}

// CALLBACK RVA 0x337c0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/blink/blink.c
// Differential report: analysis/module_behavior_recovery/blink/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x337c0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


ulonglong FUN_1800337c0(longlong param_1)

{
  longlong lVar1;
  undefined8 *puVar2;
  char cVar3;
  code *pcVar4;
  ulonglong in_RAX;
  longlong lVar5;
  longlong *plVar6;
  ulonglong uVar7;
  undefined8 unaff_RSI;
  undefined8 uStack_78;
  undefined8 uStack_70;
  ulonglong uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  
  puVar2 = *(undefined8 **)(param_1 + 8);
  cVar3 = DAT_1802ec900;
  if (*(char *)(param_1 + 0x10) == '\x01') {
    cVar3 = DAT_1802ec8e0;
  }
  if (cVar3 == '\x01') {
    uStack_40 = 0x1800337f5;
    lVar5 = FUN_180022e10(*puVar2,puVar2[3]);
    in_RAX = 0;
    if (lVar5 != 0) {
      uStack_40 = 0x180033805;
      in_RAX = FUN_180024b50(*puVar2,lVar5);
      if ((int)in_RAX == 1) {
        lVar5 = puVar2[1];
        uVar7 = CONCAT71((int7)((ulonglong)unaff_RSI >> 8),1);
        if (cRam00000001802ec614 != '\0') {
          uStack_48 = 0;
          uStack_40 = 0;
          uStack_58 = 0;
          uStack_50 = 0;
          uStack_68 = 0;
          uStack_60 = 0;
          uStack_38 = 0;
          uStack_78 = 4;
          uStack_70 = 0x1802ec600;
          plVar6 = *(longlong **)(lVar5 + 0x230);
          pcVar4 = (code *)*plVar6;
          if (pcVar4 != (code *)0x0) {
            do {
              plVar6 = plVar6 + 1;
              (*pcVar4)(&uStack_78);
              pcVar4 = (code *)*plVar6;
            } while (pcVar4 != (code *)0x0);
            if ((uStack_68 & 1) != 0) {
              uVar7 = 0;
              goto LAB_1800285a1;
            }
          }
          lVar1 = *(longlong *)(lVar5 + 0x300);
          *(undefined8 *)(*(longlong *)(lVar5 + 0x2f8) + lVar1 * 8) = 0x1802ec600;
          *(longlong *)(lVar5 + 0x300) = lVar1 + 1;
        }
LAB_1800285a1:
        return uVar7 & 0xffffffff;
      }
    }
  }
  return in_RAX;
}

// UI RVA 0x33830; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x33830; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180033830(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_1801519f0);
  FUN_18000d040(param_2,param_1,0x1802ec888);
  FUN_18000cf30(param_2,param_1,0x1802ec830);
  FUN_180013e90(param_1,param_2,&UNK_1801519f5);
  FUN_18000cef0(param_2,param_1,0x1802ec810);
  FUN_18000cef0(param_2,param_1,0x1802ec8e8);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802ec8d8,0x1802ec8c8,&DAT_1802ec8e0);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x338d0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x338d0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_1800338d0(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c6f0(param_1,&UNK_180151a00,0x1802ec888);
  FUN_18000c450(param_1,&UNK_180151a0a,0x1802ec830);
  FUN_18000c3b0(param_1,&UNK_180151a17,0x1802ec810);
  FUN_18000c3b0(param_1,&UNK_180151a29,0x1802ec8e8);
  uVar1 = uRam00000001802ec8e1;
  uVar2 = DAT_1802ec8e0;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180151a43,DAT_1802ec8e0);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802ec8e0;
      break;
    case 2:
      uRam00000001802ec8e1 = DAT_1802ec8e0;
      break;
    case 3:
      uVar2 = uRam00000001802ec8e1;
    }
  }
  DAT_1802ec8e0 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x33950; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x33950; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180033950(undefined8 param_1)

{
  FUN_1800ab710(param_1,0x20,&UNK_180151a58,
                *(undefined8 *)((ulonglong)_DAT_1802ec8b8 * 8 + 0x1802ec870));
  return;
}

