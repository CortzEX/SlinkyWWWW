// Recovered decompiler view: Null Move
// Generated from the supplied lib_win; names and types are inferred.
// This Ghidra pseudocode is not original or buildable C++.
// Candidate code interval: [0x46ac0, 0x46e30); proximity does not prove ownership.

// CALLBACK RVA 0x46ac0; ownership: direct_reference
// Verified C implementation: analysis/module_behavior_recovery/null_move/null_move.c
// Differential report: analysis/module_behavior_recovery/null_move/verification.json
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x46ac0; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_180046ac0(longlong param_1)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  int iVar3;
  char cVar4;
  byte bVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined4 uVar11;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  cVar4 = FUN_180022e60(*puVar1,puVar1[3]);
  if (cVar4 == '\0') {
    return;
  }
  uVar6 = FUN_180023760(*puVar1,puVar1[5]);
  uVar7 = FUN_180022cf0(*puVar1,puVar1[3]);
  uVar10 = FUN_1800250d0(*puVar1,uVar7);
  uVar2 = FUN_180025170(*puVar1,uVar7);
  uVar9 = FUN_180025120(*puVar1,uVar7);
  uVar7 = FUN_1800251c0(*puVar1,uVar7);
  iVar3 = _DAT_1803049d0;
  cVar4 = FUN_180025430(*puVar1,uVar10);
  bVar5 = FUN_180025430(*puVar1,uVar9);
  if (cVar4 == '\0') {
    if (iVar3 == 0) {
      uVar11 = 0;
    }
    else {
      cVar4 = FUN_180025490(*puVar1,uVar9);
      uVar11 = 0;
      uVar8 = 1;
      if (cVar4 != '\0') goto LAB_180046b9e;
    }
  }
  else {
    uVar11 = uVar6;
    if ((iVar3 == 0 & bVar5) != 0) {
      uVar8 = 0;
LAB_180046b9e:
      FUN_180025460(*puVar1,uVar9,uVar8);
    }
  }
  iVar3 = _DAT_1803049d4;
  _DAT_1803049d0 = uVar11;
  cVar4 = FUN_180025430(*puVar1,uVar2);
  bVar5 = FUN_180025430(*puVar1,uVar7);
  if (cVar4 == '\0') {
    if (iVar3 == 0) {
      uVar11 = 0;
    }
    else {
      cVar4 = FUN_180025490(*puVar1,uVar7);
      uVar11 = 0;
      uVar8 = 1;
      if (cVar4 != '\0') goto LAB_180046c0e;
    }
  }
  else {
    uVar11 = uVar6;
    if ((iVar3 == 0 & bVar5) == 1) {
      uVar8 = 0;
LAB_180046c0e:
      FUN_180025460(*puVar1,uVar7,uVar8);
    }
  }
  iVar3 = _DAT_1803049d8;
  _DAT_1803049d4 = uVar11;
  cVar4 = FUN_180025430(*puVar1,uVar9);
  bVar5 = FUN_180025430(*puVar1,uVar10);
  if (cVar4 == '\0') {
    if (iVar3 == 0) {
      uVar11 = 0;
      goto LAB_180046c8e;
    }
    cVar4 = FUN_180025490(*puVar1,uVar10);
    uVar11 = 0;
    uVar9 = 1;
    if (cVar4 == '\0') goto LAB_180046c8e;
  }
  else {
    uVar11 = uVar6;
    if ((iVar3 == 0 & bVar5) != 1) goto LAB_180046c8e;
    uVar9 = 0;
  }
  FUN_180025460(*puVar1,uVar10,uVar9);
LAB_180046c8e:
  iVar3 = _DAT_1803049dc;
  _DAT_1803049d8 = uVar11;
  cVar4 = FUN_180025430(*puVar1,uVar7);
  bVar5 = FUN_180025430(*puVar1,uVar2);
  if (cVar4 == '\0') {
    if (iVar3 == 0) {
      _DAT_1803049dc = 0;
      return;
    }
    cVar4 = FUN_180025490(*puVar1,uVar2);
    uVar6 = 0;
    uVar10 = 1;
    if (cVar4 == '\0') {
      _DAT_1803049dc = 0;
      return;
    }
  }
  else {
    if ((iVar3 == 0 & bVar5) != 1) {
      _DAT_1803049dc = uVar6;
      return;
    }
    uVar10 = 0;
  }
  FUN_180025460(*puVar1,uVar2,uVar10);
  _DAT_1803049dc = uVar6;
  return;
}

// CANDIDATE_LOCAL RVA 0x46d10; ownership: contiguous_code_interval
/* Decompiled from supplied lib_win after offline LZMA extraction.
 * RVA 0x46d10; names/types inferred; not original or buildable source.
 * Runtime fixups/import resolution not replayed. Preserve decompiler warnings. */


undefined1 FUN_180046d10(undefined8 *param_1,undefined8 param_2)

{
  char cVar1;
  int iVar2;
  longlong lVar3;
  char *pcVar4;
  ulonglong uVar5;
  undefined1 *puVar6;
  longlong lVar7;
  
  if (DAT_1802f48c4 != '\x01') {
    return 0;
  }
  if ((DAT_1802f4ad8 == '\x01') && (cVar1 = FUN_180029080(param_1), cVar1 == '\0')) {
    return 0;
  }
  lVar3 = FUN_180028a50(*param_1,param_1[5]);
  if (lVar3 == 0) {
    pcVar4 = (char *)0x1802f4af8;
  }
  else {
    iVar2 = FUN_180025c50(*param_1,lVar3);
    switch(iVar2) {
    case 0x100:
    case 0x101:
    case 0x102:
    case 0x10d:
    case 0x10e:
    case 0x10f:
    case 0x111:
    case 0x112:
    case 0x113:
    case 0x115:
    case 0x116:
    case 0x117:
    case 0x11c:
    case 0x11d:
    case 0x11e:
    case 0x167:
      pcVar4 = (char *)0x1802f4b38;
      break;
    case 0x103:
      pcVar4 = (char *)0x1802f4b78;
      break;
    case 0x10b:
    case 0x10c:
    case 0x110:
    case 0x114:
    case 0x11b:
      pcVar4 = (char *)0x1802f4b18;
      break;
    case 0x145:
    case 0x146:
    case 0x147:
      pcVar4 = (char *)0x1802f4b58;
      break;
    default:
      if (iVar2 == 0x1e) {
        pcVar4 = (char *)0x1802f4b98;
        break;
      }
    case 0x104:
    case 0x105:
    case 0x106:
    case 0x107:
    case 0x108:
    case 0x109:
    case 0x10a:
    case 0x118:
    case 0x119:
    case 0x11a:
    case 0x11f:
    case 0x120:
    case 0x121:
    case 0x122:
    case 0x123:
    case 0x124:
    case 0x125:
    case 0x126:
    case 0x127:
    case 0x128:
    case 0x129:
    case 0x12a:
    case 299:
    case 300:
    case 0x12d:
    case 0x12e:
    case 0x12f:
    case 0x130:
    case 0x131:
    case 0x132:
    case 0x133:
    case 0x134:
    case 0x135:
    case 0x136:
    case 0x137:
    case 0x138:
    case 0x139:
    case 0x13a:
    case 0x13b:
    case 0x13c:
    case 0x13d:
    case 0x13e:
    case 0x13f:
    case 0x140:
    case 0x141:
    case 0x142:
    case 0x143:
    case 0x144:
    case 0x148:
    case 0x149:
    case 0x14a:
    case 0x14b:
    case 0x14c:
    case 0x14d:
    case 0x14e:
    case 0x14f:
    case 0x150:
    case 0x151:
    case 0x152:
    case 0x153:
    case 0x154:
    case 0x155:
    case 0x156:
    case 0x157:
    case 0x158:
    case 0x159:
    case 0x15a:
    case 0x15b:
    case 0x15c:
    case 0x15d:
    case 0x15e:
    case 0x15f:
    case 0x160:
    case 0x161:
    case 0x162:
    case 0x163:
    case 0x164:
    case 0x165:
    case 0x166:
      pcVar4 = (char *)0x1802f4bb8;
    }
  }
  if (*pcVar4 != '\x01') {
    return 0;
  }
  lVar3 = FUN_180024120(*param_1,param_2);
  if (lVar3 == 0) {
    puVar6 = (undefined1 *)0x1802f4bd8;
  }
  else {
    uVar5 = FUN_18002acb0(*param_1,lVar3);
    lVar3 = 0x1802f4c00;
    if ((uVar5 & 5) == 0) {
      lVar3 = 0x1802f4c20;
    }
    lVar7 = 0x1802f4be0;
    if ((uVar5 & 2) == 0) {
      lVar7 = lVar3;
    }
    puVar6 = (undefined1 *)(lVar7 + 0x18);
  }
  return *puVar6;
}

