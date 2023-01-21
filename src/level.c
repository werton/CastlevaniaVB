#include "debug.h"
#include "types.h"
#include "global.h"
#include "lvl_gen.h"
#include "level.h"
#include "colmap.h"
#include "entities.h"
#include "hud.h"
#include "gfx.h"

#include "sprites.h"
#include "sounds.h"
#include "tilemaps.h"


void LoadLayer(s16 roomIndex, u8 BG, bool priority);

// Dynamic 2D array where we store the collision map data
// We could read that directly from ROM but in the long term it's cleaner and/or more performant
u8 **currentCollisionMap;

// Downlscaled size of the map in order to match the collision map size
Vect2D_u16 roomSizeTiles;


void LoadLevel(s16 roomIndex)
{
    activeLevel.filledTilesId = VDPTilesFilled;



//        PAL_setPalette(PAL_PLAN_A, palette_black, DMA);

        VDP_clearPlane(BG_A, true);
        VDP_clearPlane(BG_B, true);
//        VDP_clearPlane(WINDOW, true);


        // release maps
        MEM_free(activeLevel.map[BG_A]);
        MEM_free(activeLevel.map[BG_B]);



        LoadLayer(roomIndex, BG_A, false);
        LoadLayer(roomIndex, BG_B, false);

        VDP_setBackgroundColor(16);


        activeLevel.BGOffsetScale = BG_SCROLL_SPEED_SCALE;
        // CameraUpdate();

        HUDUpdate();
//        BindCurrentLevelEntities();

//    SPR_logSprites();

}

void LoadLayer(s16 roomIndex, u8 BG, bool priority)
{
    activeLevel.lvlMap = &(romLevel[roomIndex].lvlMap);

    const LevelMap *lvlMap = activeLevel.lvlMap;

    u8 vdpPalette;

    if (BG == BG_A)
    {
        vdpPalette = PAL_PLAN_A;
        FreeCollisionMap();
        GenerateCollisionMap(lvlMap->sizeTiles.x, lvlMap->sizeTiles.y, lvlMap->collisionMap);
    }
    else
    {
        vdpPalette = PAL_PLAN_B;
    }

//    PAL_setPalette(vdpPalette, lvlMap->layer[BG].palette->data, DMA_QUEUE);

    VDP_loadTileSet(lvlMap->layer[BG].tileset, activeLevel.filledTilesId, DMA_QUEUE);

    activeLevel.map[BG] = MAP_create(lvlMap->layer[BG].mapDef, BG, TILE_ATTR_FULL(vdpPalette, priority, FALSE, FALSE, activeLevel.filledTilesId));

    activeLevel.filledTilesId += lvlMap->layer[BG].tileset->numTile;
}

void FreeCollisionMap()
{
    // We have to free the collision map data in this way in order to avoid memory leaks
    for (u16 i = 0; i < roomSizeTiles.y; i++)
    {
        MEM_free(currentCollisionMap[i]);
    }

    MEM_free(currentCollisionMap);
}

void GenerateCollisionMap(u8 mapWidth, u8 mapHeight, const u8 map[][mapWidth])
{
//    roomSizePixels = newAABB_s16(0, mapWidth << 4, 0, mapHeight << 4);
    activeLevel.aabb = (AABB_s16) {0, 0, mapWidth << 4, mapHeight << 4};

    // Each tile is 16x16px, so we divide 768(size of the room in pixels) / 16, we use bitshifts because it is more performant than divisions
    roomSizeTiles = (Vect2D_u16) {mapWidth, mapHeight};
    // To store a 2D array with pointers we have to do it in that way
    currentCollisionMap = (u8 **)MEM_alloc(roomSizeTiles.y * sizeof(u8 *));

    for (u16 i = 0; i < roomSizeTiles.y; i++)
    {
        currentCollisionMap[i] = (u8 *)MEM_alloc(roomSizeTiles.x);
        memcpy(currentCollisionMap[i], map[i], roomSizeTiles.x);
    }

    activeLevel.sizeTiles = roomSizeTiles;
    activeLevel.sizePixels = (Vect2D_u16) {mapWidth << 4, mapHeight << 4};
    //    LOGX("", currentMap.sizePixels.x);
}

u16 getTileValue(s16 x, s16 y)
{
    if (x >= roomSizeTiles.x || x < 0 || y < 0 || y >= roomSizeTiles.y)
        return 0;

    // If the position is inside the collision map return the value of the tile from it
    return currentCollisionMap[y][x];
}
