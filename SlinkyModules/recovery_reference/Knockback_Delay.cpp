// Recovered decompiler view: Knockback Delay
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x46140, 0x466e0); proximity does not prove ownership.

// CALLBACK RVA 0x46140; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/knockback_delay_packet/knockback_delay_packet.c
// Differential report: analysis/module_behavior_recovery/knockback_delay_packet/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x46140; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180046140(longlong param_1)

{
  int iVar1;
  undefined4 uVar2;
  longlong lVar3;
  bool bVar4;
  
  if (*(int *)(param_1 + 0x24) != 0) {
    return;
  }
  lVar3 = FUN_1800266b0(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10));
  if (lVar3 == 0) {
    bVar4 = false;
  }
  else {
    iVar1 = FUN_1800266f0(*(undefined8 *)(param_1 + 8),lVar3);
    bVar4 = iVar1 == _DAT_1803049a4;
  }
  if ((DAT_1803049a0 & 1) == 0) {
    if ((DAT_1803049a1 & bVar4) != 0) {
      DAT_180304998 = 1;
    }
  }
  else if (*(longlong *)(param_1 + 0x18) == 0) {
    DAT_180304998 = DAT_1803049a1 & 1;
  }
  else {
    DAT_180304998 = 0;
  }
  if ((bVar4 & DAT_180304998) == 1) {
    iVar1 = *(int *)(param_1 + 0x20);
    if ((_DAT_18030499c != 0) &&
       (iVar1 = _DAT_18030499c, _DAT_18030499c != *(int *)(param_1 + 0x20))) goto LAB_180046203;
  }
  else {
    iVar1 = _DAT_18030499c;
    if (DAT_180304998 == 0) {
      return;
    }
  }
  _DAT_18030499c = iVar1;
  if (*(longlong *)(param_1 + 0x18) <= (longlong)(ulonglong)_DAT_1803049a2) {
    lVar3 = FUN_180026a30(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10));
    if (((lVar3 == 0) &&
        (lVar3 = FUN_180026ad0(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10)),
        lVar3 == 0)) &&
       (lVar3 = FUN_180026a90(*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x10)),
       lVar3 == 0)) {
      uVar2 = 1;
    }
    else {
      uVar2 = 3;
    }
    *(undefined4 *)(param_1 + 0x24) = uVar2;
    return;
  }
LAB_180046203:
  LOCK();
  UNLOCK();
  DAT_1803049a1 = 0;
  _DAT_18030499c = 0;
  DAT_180304998 = 0;
  return;
}

// CALLBACK RVA 0x46270; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/knockback_delay_update/knockback_delay_update.c
// Differential report: analysis/module_behavior_recovery/knockback_delay_update/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x46270; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180046270(longlong param_1)

{
  longlong *plVar1;
  uint uVar2;
  float fVar3;
  char cVar4;
  undefined1 uVar5;
  float fVar6;
  int iVar7;
  int iVar8;
  float fVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  uint uVar12;
  double dVar13;
  double dVar14;
  undefined8 uStack_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  
  plVar1 = *(longlong **)(param_1 + 8);
  if (plVar1[5] == 0) {
    return;
  }
  _DAT_1803049a4 = FUN_180023720(*plVar1);
  LOCK();
  UNLOCK();
  if (DAT_1802f4358 == '\x01') {
    DAT_1803049a0 = FUN_180023780(*plVar1,plVar1[5]);
  }
  else {
    DAT_1803049a0 = 0;
  }
  LOCK();
  UNLOCK();
  if ((((*(longlong *)(plVar1[7] + 8) != 0) &&
       (*(double *)(plVar1[7] + 0x10) <= (double)(_DAT_1802f4390 * _DAT_1802f4390))) &&
      ((DAT_1802f43b0 != '\x01' || (cVar4 = FUN_1800380b0(*plVar1,plVar1[5]), cVar4 != '\0')))) &&
     ((DAT_1802f43d0 != '\x01' || (cVar4 = FUN_180029080(plVar1), cVar4 != '\0')))) {
    if (DAT_1802f43f0 != '\x01') {
LAB_1800464cd:
      dVar14 = (double)_DAT_1802f4428;
      uVar5 = 1;
      if (dVar14 <= _DAT_180154fc8) {
        uVar10 = FUN_18000a050(CONCAT44((int)((ulonglong)(_DAT_180154fd0 + dVar14) >> 0x20),
                                        (float)(_DAT_180154fd0 + dVar14)),
                               CONCAT44((int)((ulonglong)(dVar14 + _DAT_180154fd8) >> 0x20),
                                        (float)(dVar14 + _DAT_180154fd8)));
        uVar5 = FUN_18000aa30(0x1803049a8,uVar10,_DAT_180154fe0);
      }
      goto LAB_180046300;
    }
    FUN_180023030(&uStack_118,*plVar1,plVar1[5]);
    fVar6 = (float)FUN_180023170(*plVar1,plVar1[5]);
    uVar10 = FUN_180024600(*plVar1,plVar1[4]);
    iVar7 = FUN_180024e50(*plVar1,uVar10);
    fVar3 = _DAT_180154fc0;
    uVar2 = _DAT_180154fb0;
    dVar14 = _DAT_180154fa0;
    if (0 < iVar7) {
      iVar7 = 0;
      do {
        uVar11 = FUN_180024e80(*plVar1,uVar10,iVar7);
        cVar4 = (**(code **)(**(longlong **)(*plVar1 + 8) + 0xc0))
                          (*(longlong **)(*plVar1 + 8),plVar1[5],uVar11);
        if (cVar4 == '\0') {
          uStack_98 = uStack_108;
          uStack_a8 = uStack_118;
          uStack_a0 = uStack_110;
          FUN_180023030(&uStack_100,*plVar1,uVar11);
          uStack_d8 = uStack_98;
          uStack_e8 = uStack_a8;
          uStack_e0 = uStack_a0;
          uStack_b8 = uStack_f0;
          uStack_c8 = uStack_100;
          uStack_c0 = uStack_f8;
          dVar13 = (double)FUN_1800094b0(&uStack_e8,&uStack_c8);
          if (dVar13 <= dVar14) {
            uStack_d8 = uStack_98;
            uStack_e8 = uStack_a8;
            uStack_e0 = uStack_a0;
            uStack_b8 = uStack_f0;
            uStack_c8 = uStack_100;
            uStack_c0 = uStack_f8;
            fVar9 = (float)FUN_180009f80(&uStack_e8,&uStack_c8);
            uVar12 = FUN_18000a210(fVar9 - fVar6);
            if ((float)(uVar12 & uVar2) <= fVar3) goto LAB_1800464cd;
          }
        }
        iVar7 = iVar7 + 1;
        iVar8 = FUN_180024e50(*plVar1,uVar10);
      } while (iVar7 < iVar8);
    }
  }
  uVar5 = 0;
LAB_180046300:
  LOCK();
  UNLOCK();
  LOCK();
  UNLOCK();
  _DAT_1803049a2 = (short)(int)_DAT_1802f4338;
  DAT_1803049a1 = uVar5;
  return;
}

// UI RVA 0x46530; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x46530; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_180046530(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  
  FUN_180013e90(param_1,param_2,&UNK_18015509d);
  FUN_18000cf30(param_2,param_1,0x1802f4360);
  FUN_18000cf30(param_2,param_1,0x1802f43f8);
  FUN_18000cf30(param_2,param_1,0x1802f4308);
  FUN_180013e90(param_1,param_2,&UNK_1801550a2);
  FUN_18000cef0(param_2,param_1,0x1802f4340);
  FUN_18000cef0(param_2,param_1,0x1802f43d8);
  FUN_18000cef0(param_2,param_1,0x1802f43b8);
  cVar1 = FUN_180013d90(param_1,param_2,uRam00000001802f43a8,0x1802f4398,&DAT_1802f43b0);
  if (cVar1 != '\0') {
    DAT_1802f7338 = 1;
    return;
  }
  return;
}

// SETTINGS RVA 0x465f0; ownership: direct_reference
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x465f0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


void FUN_1800465f0(undefined8 *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  FUN_18000c450(param_1,&UNK_1801550ad,0x1802f4360);
  FUN_18000c450(param_1,&UNK_1801550b3,0x1802f43f8);
  FUN_18000c450(param_1,&UNK_1801550ba,0x1802f4308);
  FUN_18000c3b0(param_1,&UNK_1801550c4,0x1802f4340);
  FUN_18000c3b0(param_1,&UNK_1801550d0,0x1802f43d8);
  FUN_18000c3b0(param_1,&UNK_1801550df,0x1802f43b8);
  uVar1 = uRam00000001802f43b1;
  uVar2 = DAT_1802f43b0;
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
      lVar5 = FUN_18004ed40(*param_1,&UNK_1801550ed,DAT_1802f43b0);
      *(byte *)((longlong)param_1 + 0xc) = *(byte *)((longlong)param_1 + 0xc) | lVar5 == 0;
      uVar2 = DAT_1802f43b0;
      break;
    case 2:
      uRam00000001802f43b1 = DAT_1802f43b0;
      break;
    case 3:
      uVar2 = uRam00000001802f43b1;
    }
  }
  DAT_1802f43b0 = uVar2;
  return;
}

// CANDIDATE_LOCAL RVA 0x466a0; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x466a0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_1800466a0(void)

{
  FUN_1800ab710(_DAT_1802f4338,0x20,&UNK_1801550fc,(double)_DAT_1802f4338);
  return;
}

