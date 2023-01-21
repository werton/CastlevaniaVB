#include "debug.h"
#include "defs.h"
#include "lvl_gen.h"
#include "global.h"
#include "entities.h"
#include "level.h"
#include "colmap.h"
#include "tilemaps.h"


const RomLevel romLevel[MAX_LEVELS] = {
    [0] = {
        .lvlMap =
        {
            .layer[BG_A] = {
                .palette = &level_0_layer_a_palette,
                .tileset = &level_0_layer_a_tileset,
                .mapDef =  &level_0_layer_a_map,
            },

            .layer[BG_B] = {
                .palette = &level_0_layer_b_palette,
                .tileset = &level_0_layer_b_tileset,
                .mapDef =  &level_0_layer_b_map,

            },

            .index = 0,
            .collisionMap = collisionMap0,
            .sizeTiles = {WIDTHOF2DARRAY(collisionMap0), HEIGHTOF2DARRAY(collisionMap0)},

         },
        .mapWarpEntities = mapWarpEntities0,
        .mapDecorEntities = mapDecorEntities0,
        .warpCount = SIZEOFARRAY(mapWarpEntities0),
        .decorCount = SIZEOFARRAY(mapDecorEntities0),
    },
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
            .collisionMap = collisionMap1,
            .sizeTiles = {WIDTHOF2DARRAY(collisionMap1), HEIGHTOF2DARRAY(collisionMap1)},

         },
        .mapWarpEntities = mapWarpEntities1,
        .mapDecorEntities = mapDecorEntities1,
        .warpCount = SIZEOFARRAY(mapWarpEntities1),
        .decorCount = SIZEOFARRAY(mapDecorEntities1),
    },

    [2] = {
        .lvlMap =
        {
            .layer[BG_A] = {
                .palette = &level_2_layer_a_palette,
                .tileset = &level_2_layer_a_tileset,
                .mapDef = &level_2_layer_a_map,
            },

            .layer[BG_B] = {
                .palette = &level_2_layer_b_palette,
                .tileset = &level_2_layer_b_tileset,
                .mapDef = &level_2_layer_b_map,
            },

            .index = 2,
            .collisionMap = collisionMap2,
            .sizeTiles = {WIDTHOF2DARRAY(collisionMap2), HEIGHTOF2DARRAY(collisionMap2)},
        },
        .mapWarpEntities = mapWarpEntities2,
        .mapDecorEntities = mapDecorEntities2,
        .warpCount = SIZEOFARRAY(mapWarpEntities2),
        .decorCount = SIZEOFARRAY(mapDecorEntities2),
    },

    [3] = {
        .lvlMap =
        {
            .layer[BG_A] = {
                .palette = &level_3_layer_a_palette,
                .tileset = &level_3_layer_a_tileset,
                .mapDef = &level_3_layer_a_map,
            },

            .layer[BG_B] = {
                .palette = &level_3_layer_b_palette,
                .tileset = &level_3_layer_b_tileset,
                .mapDef = &level_3_layer_b_map,
            },
            .index = 3,
            .collisionMap = collisionMap3,
            .sizeTiles = {WIDTHOF2DARRAY(collisionMap3), HEIGHTOF2DARRAY(collisionMap3)},
        },
        .mapWarpEntities = mapWarpEntities3,
        .mapDecorEntities = mapDecorEntities3,
        .warpCount = SIZEOFARRAY(mapWarpEntities3),
        .decorCount = SIZEOFARRAY(mapDecorEntities3),
    },

    [4] = {
        .lvlMap =
        {
            .layer[BG_A] = {
                .palette = &level_4_layer_a_palette,
                .tileset = &level_4_layer_a_tileset,
                .mapDef = &level_4_layer_a_map,
            },

            .layer[BG_B] = {
                .palette = &level_4_layer_b_palette,
                .tileset = &level_4_layer_b_tileset,
                .mapDef = &level_4_layer_b_map,
            },
            .index = 4,
            .collisionMap = &collisionMap4,
            .sizeTiles = {WIDTHOF2DARRAY(collisionMap4), HEIGHTOF2DARRAY(collisionMap4)},
        },
        .mapWarpEntities = mapWarpEntities4,
        .mapDecorEntities = mapDecorEntities4,
        .warpCount = SIZEOFARRAY(mapWarpEntities4),
        .decorCount = SIZEOFARRAY(mapDecorEntities4),
    },
};

