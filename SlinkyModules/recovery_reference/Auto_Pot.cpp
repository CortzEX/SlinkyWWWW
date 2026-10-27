// Recovered decompiler view: Auto Pot
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x391c0, 0x39790); proximity does not prove ownership.

// CALLBACK RVA 0x391c0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/auto_pot/auto_pot.c
// Differential report: analysis/module_behavior_recovery/auto_pot/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x391c0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong FUN_1800391c0(longlong param_1)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  ulonglong uVar4;
  longlong *plVar5;
  undefined8 unaff_RSI;
  undefined8 uStack_78;
  undefined8 uStack_70;
  ulonglong uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  
  if (0.0 < _DAT_1802fc650) {
    _DAT_1802fc650 = _DAT_1802fc650 + _DAT_180152c3c;
    if (_DAT_1802fc640 != 4) {
      return (ulonglong)_DAT_1802fc640;
    }
  }
  else {
    if (*(char *)(*(longlong *)(param_1 + 8) + 0x40) != '\0') {
                    /* WARNING: Could not recover jumptable at 0x000180039248. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar4 = (*(code *)(&UNK_180152c40 + *(int *)(&UNK_180152c40 + (ulonglong)_DAT_1802fc640 * 4)))
                        ();
      return uVar4;
    }
    DAT_1802fc64c = 0;
    _DAT_1802fc640 = 4;
  }
  lVar2 = *(longlong *)(*(longlong *)(param_1 + 8) + 8);
  uVar4 = CONCAT71((int7)((ulonglong)unaff_RSI >> 8),1);
  if (cRam00000001802ef13c != '\0') {
    uStack_48 = 0;
    uStack_58 = 0;
    uStack_50 = 0;
    uStack_68 = 0;
    uStack_60 = 0;
    uStack_78 = 4;
    uStack_70 = 0x1802ef128;
    plVar5 = *(longlong **)(lVar2 + 0x230);
    pcVar3 = (code *)*plVar5;
    if (pcVar3 != (code *)0x0) {
      do {
        plVar5 = plVar5 + 1;
        (*pcVar3)(&uStack_78);
        pcVar3 = (code *)*plVar5;
      } while (pcVar3 != (code *)0x0);
      if ((uStack_68 & 1) != 0) {
        uVar4 = 0;
        goto LAB_1800285a1;
      }
    }
    lVar1 = *(longlong *)(lVar2 + 0x300);
    *(undefined8 *)(*(longlong *)(lVar2 + 0x2f8) + lVar1 * 8) = 0x1802ef128;
    *(longlong *)(lVar2 + 0x300) = lVar1 + 1;
  }
LAB_1800285a1:
  return uVar4 & 0xffffffff;
}

// CALLBACK RVA 0x394d0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/auto_pot/auto_pot.c
// Differential report: analysis/module_behavior_recovery/auto_pot/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x394d0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800394d0(longlong param_1)

{
  if (0 < _DAT_1802fc678 && (_DAT_1802fc640 != 4 && *(longlong *)(param_1 + 8) == 0x1802ef128)) {
    *(undefined1 *)(param_1 + 0x10) = 1;
    _DAT_1802fc654 = _DAT_1802fc654 + 1;
    _DAT_1802fc678 = _DAT_1802fc678 + -1;
  }
  return;
}

// CALLBACK RVA 0x39520; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/auto_pot/auto_pot.c
// Differential report: analysis/module_behavior_recovery/auto_pot/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x39520; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180039520(longlong param_1)

{
  undefined8 *puVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  
  if (*(longlong *)(param_1 + 0x10) == 0x1802ef128) {
    if (*(char *)(param_1 + 0x18) == '\x01') {
      puVar1 = *(undefined8 **)(param_1 + 8);
      if (*(char *)(puVar1 + 8) == '\x01') {
        fVar3 = (float)FUN_180023a40(*puVar1,puVar1[5]);
        fVar4 = (float)FUN_180023a80(*puVar1,puVar1[5]);
        iVar2 = (int)(((double)(fVar4 - fVar3) + _DAT_180152c58) * _DAT_180152c60);
        if ((iVar2 == 0) && (iVar2 = 1, DAT_1802ef3a8 == '\x01')) {
          _DAT_1802fc640 = 4;
        }
        else if (DAT_1802ef3c8 == '\x01') {
          _DAT_1802fc678 = 0;
          _DAT_1802fc654 = iVar2;
        }
        else {
          _DAT_1802fc654 = 1;
          _DAT_1802fc678 = 5;
          if (DAT_1802ef3a8 != '\0') {
            _DAT_1802fc678 = iVar2 + -1;
          }
        }
      }
    }
    else {
      _DAT_1802fc640 = 0;
      _DAT_1802fc654 = 0;
    }
  }
  return;
}

// UI RVA 0x39600; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x39600; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180039600(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180152d22);
  FUN_18000cf30(param_2,param_1,0x1802ef358);
  FUN_18000cef0(param_2,param_1,0x1802ef390);
  FUN_18000cef0(param_2,param_1,0x1802ef3b0);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802ef348,0x1802ef338,0x1802ef350);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x39670; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x39670; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180039670(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c450(param_1,&UNK_180152d27,0x1802ef358);
  FUN_18000c3b0(param_1,&UNK_180152d2d,0x1802ef390);
  FUN_18000c3b0(param_1,&UNK_180152d3b,0x1802ef3b0);
  uVar1 = uRam00000001802ef351;
  uVar2 = uRam00000001802ef350;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180152d49,uRam00000001802ef350);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = uRam00000001802ef350;
      break;
    case 2:
      uRam00000001802ef351 = uRam00000001802ef350;
      break;
    case 3:
      uVar2 = uRam00000001802ef351;
    }
  }
  uRam00000001802ef350 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x396e0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x396e0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float FUN_1800396e0(void)

{
  undefined8 uVar1;
  char cVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar4 = _DAT_1802ef388;
  uVar1 = FUN_18000a050(0,_DAT_180152c68);
  fVar3 = (float)FUN_18000a510(0x1802fc658,uVar1,_DAT_180152c70);
  fVar5 = 0.0;
  if (0.0 <= fVar4 - fVar3) {
    fVar5 = fVar4 - fVar3;
  }
  uVar1 = FUN_18000a050(_DAT_180152c78,_DAT_180152c7c);
  cVar2 = FUN_18000aa30(0x1802fc668,uVar1,_DAT_180152c80);
  if (cVar2 != '\0') {
    uVar1 = FUN_18000a050(_DAT_180152c68,_DAT_180152c88);
    fVar4 = (float)FUN_18000a3e0(uVar1);
    fVar5 = fVar5 + fVar4;
  }
  return fVar5;
}

