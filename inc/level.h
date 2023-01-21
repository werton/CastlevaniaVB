#ifndef LEVEL_INCLUDE_H
#define LEVEL_INCLUDE_H

#include <genesis.h>

#include "global.h"
#include "types.h"
#include "player.h"


extern void LoadLevel(s16 roomIndex);
extern void FreeCollisionMap();
extern void GenerateCollisionMap(u8 mapWidth, u8 mapHeight, const u8 lvlMap[][mapWidth]);


u16 getTileValue(s16 x, s16 y);

extern u16 currentCurrencySpawnerEntity;
const LevelMap rooms[10];

#endif // LEVEL_INCLUDE_H

