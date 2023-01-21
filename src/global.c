#include "global.h"
#include "input.h"
#include "sounds.h"

const u8* music[1] = {
        [0] = vgm_01,
};

Input joy[2];

//Player collider bounds position
AABB_s16 playerBounds;

//Index of the last tile that has been placed, useful to avoid overlapping
u16 VDPTilesFilled = TILE_USER_INDEX;
u16 hudTilesIndex;

ActiveLevel activeLevel;


const struct PlayerConfig playerConfig = {
    .aabb = (AABB_s16) {12, 5,24,  47},
};


