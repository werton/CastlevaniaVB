#ifndef TYPES_INCLUDE_H
#define TYPES_INCLUDE_H

#include <genesis.h>
#include "defs.h"

// ===================== BASE TYPES ======================
typedef struct
{
    u8 x;
    u8 y;
} Vect2D_u8;

typedef struct
{
    s8 x;
    s8 y;
} Vect2D_s8;

typedef struct
{
    Vect2D_s16 min;
    Vect2D_s16 max;
} AABB_s16;

typedef struct
{
    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;
} BB_s16;

typedef struct
{
    char *name;
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    u16 id;
    u8 type;
    u8 group;
    u8 enabled;

    s16 targetLevel;
    s16 targetWarp;
} MapWarpEntity;

typedef struct
{
    char *name;
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    u16 id;
    u8 type;
    u8 group;
    u8 enabled;
    u8 priority;
} MapDecorEntity;

typedef struct
{
    char *name;
    Vect2D_s16 pos;
    Vect2D_s16 size;
    u16 id;
    u8 type;
    u8 group;
    u8 enabled;
    s16 homeRoom;
    s16 state;
} BaseEntityPart;

typedef struct
{
    char *name;
    Vect2D_s16 pos;
    Vect2D_s16 size;
    u16 id;
    u8 type;
    u8 group;
    u8 enabled;
    s16 homeRoom;
    s16 state;

    s16 targetLevel;
    s16 targetWarp;
} WarpEntity;


typedef struct
{
    char *name;
    Vect2D_s16 pos;
    Vect2D_s16 size;
    u16 id;
    u8 type;
    u8 group;
    u8 enabled;
    s16 homeRoom;
    s16 state;

    u8 priority;

    Sprite *sprite;
} DecorEntity;


// ===================== LEVEL TYPES ======================
typedef struct
{
    const Palette *palette;
    const TileSet *tileset;
    const MapDefinition *mapDef;
    const f16 scrollSpeed;
} LayerData;

typedef struct
{
    const s16 index;
    const u8 (*collisionMap)[];
    const LayerData layer[MAX_BG_LAYERS];
    const Vect2D_u16 sizeTiles;
} LevelMap;


typedef struct
{
    const LevelMap lvlMap;
    const MapWarpEntity *mapWarpEntities;
    const MapDecorEntity *mapDecorEntities;
    const WarpEntity warpEntity;
    const DecorEntity decorEntity;
    const s16 warpCount;
    const s16 decorCount;
} RomLevel;

typedef struct
{
    const RomLevel *romLevel;
    const LevelMap *lvlMap;
    const LayerData *layer[MAX_BG_LAYERS];
    const WarpEntity warpEntity[MAX_WARPS_PER_LEVEL];
    const DecorEntity decorEntity[MAX_WARPS_PER_LEVEL];
    Map *map[MAX_BG_LAYERS];
    Vect2D_u16 sizeTiles;
    Vect2D_u16 sizePixels;
    AABB_s16 aabb;
    u16 filledTilesId;
    f32 BGOffsetScale;
} ActiveLevel;

#endif // TYPES_INCLUDE_H

