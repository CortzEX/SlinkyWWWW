// Recovered decompiler view: Knockback Displace
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x4a520, 0x4abf0); proximity does not prove ownership.

// CALLBACK RVA 0x4a520; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/knockback_displace/knockback_displace.c
// Differential report: analysis/module_behavior_recovery/knockback_displace/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x4a520; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18004a520(longlong param_1)

{
  if ((DAT_180304af0 & 1) != 0) {
    *(undefined4 *)(param_1 + 0x24) = 1;
  }
  return;
}

// CALLBACK RVA 0x4a540; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/knockback_displace/knockback_displace.c
// Differential report: analysis/module_behavior_recovery/knockback_displace/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x4a540; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18004a540(longlong param_1)

{
  if ((DAT_180304af1 == '\0') && (DAT_180304af2 == '\0')) {
    return;
  }
  *(undefined1 *)(param_1 + 9) = 0;
  return;
}

// CALLBACK RVA 0x4a560; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/knockback_displace/knockback_displace.c
// Differential report: analysis/module_behavior_recovery/knockback_displace/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x4a560; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18004a560(longlong param_1)

{
  undefined8 *puVar1;
  undefined4 uVar2;
  float fVar3;
  char cVar4;
  int iVar5;
  longlong lVar6;
  undefined8 uVar7;
  float fVar8;
  ulonglong uVar9;
  byte abStack_5c [52];
  
  if (DAT_180304af1 == '\x01') {
    *(undefined1 *)(param_1 + 0x11) = 1;
  }
  else if (*(char *)(param_1 + 0x10) == '\x01') {
    puVar1 = *(undefined8 **)(param_1 + 8);
    lVar6 = FUN_180022e10(*puVar1,puVar1[3]);
    if ((lVar6 != 0) && (iVar5 = FUN_180024b50(*puVar1,lVar6), iVar5 == 2)) {
      uVar7 = FUN_180024e30(*puVar1,lVar6);
      lVar6 = FUN_180024120(*puVar1,uVar7);
      if ((((lVar6 != 0) &&
           ((((cVar4 = FUN_18002ace0(*puVar1,lVar6,7), cVar4 == '\0' &&
              (DAT_180304af3 = 1, DAT_180304af2 == '\0')) && (8 < _DAT_180304af4)) &&
            ((_DAT_1802f5fa0 <= (float)_DAT_180304af8 && (cVar4 = FUN_180042c30(), cVar4 == '\0'))))
           )) && ((DAT_1802f5ff8 != '\x01' || (*(char *)(puVar1[7] + 0x18) == '\0')))) &&
         ((cVar4 = FUN_180037e50(*puVar1,puVar1[5],abStack_5c), DAT_1802f6018 != '\x01' ||
          (cVar4 != '\0')))) {
        if ((abStack_5c[0] & 2) == 0) {
          if (DAT_1802f6038 != '\0') {
            return;
          }
          cVar4 = FUN_180023690(*puVar1,puVar1[5]);
          if (cVar4 == '\0') {
            return;
          }
        }
        _DAT_180304b00 = FUN_180023170(*puVar1,puVar1[5]);
        if ((DAT_1802f6058 == '\x01') &&
           (cVar4 = FUN_18004ab40(puVar1,_DAT_180304b00,lVar6), cVar4 == '\0')) {
          return;
        }
        iVar5 = FUN_18004ab90();
        if ((iVar5 != 0) && (cVar4 = FUN_180029800(200), cVar4 != '\0')) {
          FUN_180029d90(puVar1,1,0,0,_DAT_180304b00);
          DAT_180304af1 = '\x01';
          cVar4 = FUN_18000a460();
          fVar3 = _DAT_1802f5fd8;
          uVar2 = _DAT_180156684;
          uVar7 = FUN_18000a050();
          fVar8 = (float)FUN_18000a3e0(uVar7);
          uVar7 = FUN_18000a050(uVar2);
          uVar9 = FUN_18000a3e0(uVar7);
          if (cVar4 == '\0') {
            uVar9 = uVar9 ^ (ulonglong)DAT_180156690;
          }
          FUN_180029820((ulonglong)(uint)((fVar3 - fVar8) * (float)iVar5) | uVar9 << 0x20);
          FUN_180029950(*puVar1,puVar1[5],0);
          if (DAT_1802f60e0 == '\x01') {
            LOCK();
            DAT_180304af0 = 1;
            UNLOCK();
          }
          *(undefined1 *)(param_1 + 0x11) = 1;
          _DAT_180304af8 = 0;
        }
      }
    }
  }
  return;
}

// CALLBACK RVA 0x4a7d0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/knockback_displace/knockback_displace.c
// Differential report: analysis/module_behavior_recovery/knockback_displace/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x4a7d0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18004a7d0(longlong param_1)

{
  if (((*(char *)(param_1 + 0x10) == '\x01') && (9 < _DAT_180304af4)) && ((DAT_180304af3 & 1) != 0))
  {
    _DAT_180304af4 = 0;
  }
  return;
}

// CALLBACK RVA 0x4a800; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/knockback_displace/knockback_displace.c
// Differential report: analysis/module_behavior_recovery/knockback_displace/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x4a800; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_18004a800(longlong param_1)

{
  undefined8 *puVar1;
  undefined1 uVar2;
  char cVar3;
  int iVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  ulonglong uVar7;
  float fVar8;
  
  _DAT_180304af4 = _DAT_180304af4 + 1;
  _DAT_180304af8 = _DAT_180304af8 + 1;
  DAT_180304af2 = DAT_180304af1;
  DAT_180304af3 = 0;
  puVar1 = *(undefined8 **)(param_1 + 8);
  if (*(char *)(puVar1 + 8) == '\x01') {
    fVar8 = (float)FUN_180023ae0(*puVar1,puVar1[5]);
    iVar4 = (uint)(0.0 < fVar8) - (uint)(fVar8 < 0.0);
    if ((DAT_1802f6100 != '\x01') || (iVar4 != 0)) {
      _DAT_180304b08 = iVar4;
    }
    if (DAT_180304af1 != '\x01') goto LAB_18004a90b;
    cVar3 = FUN_180029800(200);
    if (cVar3 != '\0') {
      uVar5 = FUN_180023170(*puVar1,puVar1[5]);
      uVar6 = FUN_180029850();
      uVar5 = FUN_180009de0(uVar5,uVar6);
      uVar5 = FUN_180009e20(_DAT_180304b00,uVar5);
      FUN_180029820(uVar5);
      FUN_180029950(*puVar1,puVar1[5],0);
      uVar5 = FUN_180022cf0(*puVar1,puVar1[3]);
      FUN_180022eb0(*puVar1,puVar1[3],0);
      uVar5 = FUN_180025270(*puVar1,uVar5);
      FUN_180025380(*puVar1,uVar5);
    }
  }
  DAT_180304af1 = '\0';
LAB_18004a90b:
  uVar2 = DAT_180304af0;
  uVar7 = 0;
  if (DAT_180304af2 != '\0') {
    uVar7 = (ulonglong)_DAT_1802f60e0;
  }
  LOCK();
  DAT_180304af0 = (char)uVar7;
  UNLOCK();
  return CONCAT71((int7)(uVar7 >> 8),uVar2);
}

// UI RVA 0x4a930; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x4a930; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18004a930(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_1801567e3);
  FUN_18000d040(param_2,param_1,0x1802f6088);
  if (_DAT_1802f60b8 - 3U < 2) {
    FUN_18000cef0(param_2,param_1,0x1802f60e8);
  }
  FUN_18000cf30(param_2,param_1,0x1802f5f70);
  FUN_18000cf30(param_2,param_1,0x1802f5fa8);
  FUN_18000cef0(param_2,param_1,0x1802f60c8);
  FUN_180013e90(param_1,param_2,&UNK_1801567e8);
  FUN_18000cef0(param_2,param_1,0x1802f5fe0);
  FUN_18000cef0(param_2,param_1,0x1802f6000);
  FUN_18000cef0(param_2,param_1,0x1802f6020);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802f6050,0x1802f6040,&DAT_1802f6058);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x4aa20; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x4aa20; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_18004aa20(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c6f0(param_1,&UNK_1801567f2,0x1802f6088);
  FUN_18000c3b0(param_1,&UNK_1801567fc,0x1802f60e8);
  FUN_18000c450(param_1,&UNK_18015680c,0x1802f5fa8);
  FUN_18000c450(param_1,&UNK_180156812,0x1802f5f70);
  FUN_18000c3b0(param_1,&UNK_18015681b,0x1802f60c8);
  FUN_18000c3b0(param_1,&UNK_180156829,0x1802f5fe0);
  FUN_18000c3b0(param_1,&UNK_180156837,0x1802f6000);
  FUN_18000c3b0(param_1,&UNK_180156846,0x1802f6020);
  uVar1 = uRam00000001802f6059;
  uVar2 = DAT_1802f6058;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_180156859,DAT_1802f6058);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802f6058;
      break;
    case 2:
      uRam00000001802f6059 = DAT_1802f6058;
      break;
    case 3:
      uVar2 = uRam00000001802f6059;
    }
  }
  DAT_1802f6058 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x4ab00; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x4ab00; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18004ab00(void)

{
  FUN_1800ab710(_DAT_1802f5fd8,0x20,&UNK_1801567a7,(double)_DAT_1802f5fd8);
  return;
}

// CANDIDATE_LOCAL RVA 0x4ab40; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x4ab40; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool FUN_18004ab40(undefined8 *param_1,float param_2,undefined8 param_3)

{
  double dVar1;
  uint uVar2;
  
  dVar1 = (double)FUN_180024220(*param_1,param_3);
  uVar2 = FUN_18000a210((float)dVar1 - param_2);
  return (float)(uVar2 & _DAT_1801566a0) < _DAT_1801566b0;
}

// CANDIDATE_LOCAL RVA 0x4ab90; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x4ab90; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_18004ab90(void)

{
                    /* WARNING: Could not recover jumptable at 0x00018004abae. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)(&UNK_1801566b8 + *(int *)(&UNK_1801566b8 + (ulonglong)_DAT_1802f60b8 * 4)))();
  return;
}

