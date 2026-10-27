// Recovered decompiler view: No Hit Delay
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x3e590, 0x3e6d0); proximity does not prove ownership.

// CALLBACK RVA 0x3e590; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/access_events/access_events.c
// Differential report: analysis/module_behavior_recovery/access_events/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3e590; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003e590(longlong param_1)

{
  longlong *plVar1;
  undefined8 *puVar2;
  char cVar3;
  int iVar4;
  longlong lVar5;
  undefined8 unaff_RBP;
  
  if (*(char *)(param_1 + 0x10) == '\x01') {
    puVar2 = *(undefined8 **)(param_1 + 8);
    if (**(int **)*puVar2 != 0) {
      iVar4 = FUN_180022e90((undefined8 *)*puVar2,puVar2[3]);
      if (0 < iVar4) {
        if (_DAT_1802f0dc0 != 1) {
FUN_180022eb0:
          plVar1 = (longlong *)((longlong *)*puVar2)[1];
                    /* WARNING: Could not recover jumptable at 0x000180022ed0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
          (**(code **)(*plVar1 + 0x368))
                    (plVar1,puVar2[3],*(undefined8 *)(*(longlong *)*puVar2 + 0x1b8),0);
          return;
        }
        lVar5 = FUN_180022e10(*puVar2,puVar2[3]);
        if (lVar5 != 0) {
          iVar4 = FUN_180024b50(*puVar2,lVar5);
          if (iVar4 != 0) goto FUN_180022eb0;
        }
        cVar3 = FUN_180023f90(*puVar2,puVar2[5]);
        if (cVar3 == '\0') {
          lVar5 = *(longlong *)*puVar2;
          plVar1 = (longlong *)((longlong *)*puVar2)[1];
          (**(code **)(*plVar1 + 0x2d8))
                    (plVar1,puVar2[5],*(undefined8 *)(lVar5 + 0x4f8),*(undefined8 *)(lVar5 + 0x520),
                     unaff_RBP);
          return;
        }
      }
    }
  }
  return;
}

// UI RVA 0x3e630; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3e630; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18003e630(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_180153ee0);
  cVar1 = FUN_180014d00(param_1,param_2,uRam00000001802f0da8,0x1802f0d90,uRam00000001802f0db0,
                        uRam00000001802f0db8,&DAT_1802f0dc0,uRam00000001802f0dc8);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x3e670; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3e670; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003e670(undefined8 *param_1)

{
  undefined8 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  longlong lVar5;
  longlong lVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  
  uVar2 = uRam00000001802f0dc4;
  uVar3 = _DAT_1802f0dc0;
  if (*(char *)((longlong)param_1 + 0xc) == '\0') {
    switch(*(undefined4 *)(param_1 + 1)) {
    case 0:
      lVar5 = FUN_18004e4d0(*param_1);
      iVar4 = FUN_18004d110(lVar5);
      lVar6 = lRam00000001802f0db8;
      uVar3 = uVar2;
      if ((iVar4 != 0) && (uVar7 = (ulonglong)uRam00000001802f0db0, uVar7 != 0)) {
        uVar1 = *(undefined8 *)(lVar5 + 0x20);
        uVar8 = 0;
        do {
          iVar4 = func_0x00018013d0a0(*(undefined8 *)(lVar6 + uVar8 * 8),uVar1);
          if (iVar4 == 0) {
            _DAT_1802f0dc0 = (int)uVar8;
            return;
          }
          uVar8 = uVar8 + 1;
        } while (uVar7 != uVar8);
      }
      break;
    case 1:
      lVar6 = FUN_18004f080(*param_1,&UNK_180153ee8,
                            *(undefined8 *)(lRam00000001802f0db8 + (ulonglong)_DAT_1802f0dc0 * 8));
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar6 == 0;
      uVar3 = _DAT_1802f0dc0;
      break;
    case 2:
      uRam00000001802f0dc4 = _DAT_1802f0dc0;
      break;
    case 3:
      uVar3 = uRam00000001802f0dc4;
    }
  }
  _DAT_1802f0dc0 = uVar3;
  return;
}

// CANDIDATE_LOCAL RVA 0x3e690; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x3e690; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18003e690(undefined8 param_1)

{
  FUN_1800ab710(param_1,0x20,&UNK_180153eed,
                *(undefined8 *)((ulonglong)_DAT_1802f0dc0 * 8 + 0x1802f0d80));
  return;
}

