#ifndef GLOBAL_INCLUDE_H
#define GLOBAL_INCLUDE_H

#include <genesis.h>
#include "defs.h"
#include "types.h"
#include "debug.h"
#include "physics.h"
#include "input.h"

extern const u8* music[1];


struct PlayerConfig
{
    AABB_s16 aabb;
};

extern Input joy[2];
extern AABB_s16 playerBounds;

extern u16 VDPTilesFilled;
extern ActiveLevel activeLevel;
extern u16 hudTilesIndex;
extern const struct PlayerConfig playerConfig;

#endif // GLOBAL_INCLUDE_H

