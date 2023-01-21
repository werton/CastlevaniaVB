#ifndef ENTITIES_INCLUDE_H
#define ENTITIES_INCLUDE_H

#include <genesis.h>
#include "../inc/types.h"



void WarpUpdate(AABB_s16* bodyBound);
void DecorReleaseSprites(s16 index);
void DecorUpdate();
void BindCurrentLevelEntities();
void BindCurrentLevelWarps();
void LoadLevelAndStartAt(s16 targetLevelId, s16 targetWarpId, s8 collisionDirection, s16 playerShiftY);

extern const SpriteDefinition *spriteDef[MAX_SPRITE_DEFS];

typedef enum
{
    LANTERN = 0,
    FIREWOOD,
    MUSHROOM_SMALL,
    MUSHROOM_MID,
    MUSHROOM_BIG,
    WEBS_SMALL,
    WEB_MID,
    WEB_BIG,
} SpriteDefInd;

#endif // ENTITIES_INCLUDE_H

