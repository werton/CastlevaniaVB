#include "debug.h"
#include "defs.h"
#include "lvl_gen.h"
#include "global.h"
#include "entities.h"
#include "level.h"
#include "colmap.h"
#include "tilemaps.h"


const RomLevel romLevel[MAX_LEVELS] = {

    [1] = {
        .lvlMap =
        {
            .layer[BG_A] = {
                .palette = &level_1_layer_a_palette,
                .tileset = &level_1_layer_a_tileset,
                .mapDef = &level_1_layer_a_map,
            },

            .layer[BG_B] = {
                .palette = &level_1_layer_b_palette,
                .tileset = &level_1_layer_b_tileset,
                .mapDef = &level_1_layer_b_map,

            },

            .index = 1,
            .collisionMap = collisionMap0,
            .sizeTiles = {WIDTHOF2DARRAY(collisionMap0), HEIGHTOF2DARRAY(collisionMap0)},

         },
        .mapWarpEntities = mapWarpEntities1,
        .mapDecorEntities = mapDecorEntities1,
        .warpCount = SIZEOFARRAY(mapWarpEntities1),
        .decorCount = SIZEOFARRAY(mapDecorEntities1),
    },

};

