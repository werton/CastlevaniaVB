#include "debug.h"
#include "global.h"
#include "entities.h"
#include "lvl_gen.h"
#include "level.h"
#include "player.h"
#include "colmap.h"
#include "gfx.h"
#include "obj_debug.h"

#include "tilemaps.h"
#include "sprites.h"
#include "hud.h"
#include "colchar.h"




static WarpEntity warpEntity[MAX_WARPS_PER_LEVEL];
static DecorEntity decorEntity[MAX_ENTITIES_PER_LEVEL];

void DecorReleaseSprites(s16 index);
void DecorInitSprite(DecorEntity *entity, u16 spriteDefIndex, s16 depth);
void BindWarpEntities(s16 levelId, MapWarpEntity *mapWarpEntity[]);
void BindDecorEntities(s16 levelId, MapDecorEntity *mapDecorEntity[]);
void InitDecorEntity(s16 levelId, DecorEntity *entity, MapDecorEntity *mapEntity);
void InitWarpEntity(s16 levelId, WarpEntity *warpEntity, MapWarpEntity *mapWarpEntity);

const SpriteDefinition *spriteDef[MAX_SPRITE_DEFS] = {
    [LANTERN] = &sprite_lantern_idle,
    [FIREWOOD] = &sprite_firewood,
    [MUSHROOM_BIG] = &sprite_mushroom_big,
    [MUSHROOM_MID] = &sprite_mushroom_mid,
    [MUSHROOM_SMALL] = &sprite_mushroom_small,
    [WEBS_SMALL] = &sprite_web_small,
};

void BindCurrentLevelWarps()
{
    s16 levelId = activeLevel.lvlMap->index;
    BindWarpEntities(levelId, romLevel[levelId].mapWarpEntities);
}

void BindCurrentLevelEntities()
{
    s16 levelId = activeLevel.lvlMap->index;
//    BindWarpEntities(levelId, romLevel[levelId].mapWarpEntities);
    BindDecorEntities(levelId, romLevel[levelId].mapDecorEntities);
}

void BindWarpEntities(s16 levelId, MapWarpEntity *mapWarpEntity[])
{
    kprintf("||||||||||||||| warp count: %d", romLevel[levelId].warpCount);

    for (u16 i = 0; i < romLevel[levelId].warpCount; i++)
    {
        InitWarpEntity(levelId, &warpEntity[i], mapWarpEntity[i]);
        LogWarpEntity(&warpEntity[i]);
    }
}

void BindDecorEntities(s16 levelId, MapDecorEntity *mapDecorEntity[])
{
    kprintf("||||||||||||||| decor count: %d", romLevel[levelId].decorCount);

    for (u16 i = 0; i < romLevel[levelId].decorCount; i++)
    {
        // LogMapDecorEntity(mapDecorEntity[i]);
        InitDecorEntity(levelId, &decorEntity[i], mapDecorEntity[i]);
        LogDecorEntity(&decorEntity[i]);
    }
//    SYS_doVBlankProcess();
}


void InitWarpEntity(s16 levelId, WarpEntity *warpEntity, MapWarpEntity *mapWarpEntity)
{
//    InitBasePartEntity(levelId, warpEntity, mapWarpEntity);
    warpEntity->name = mapWarpEntity->name;
    warpEntity->pos.x = mapWarpEntity->x;
    warpEntity->pos.y = mapWarpEntity->y;
    warpEntity->size.x = mapWarpEntity->width;
    warpEntity->size.y = mapWarpEntity->height;
    warpEntity->id = mapWarpEntity->id;
    warpEntity->type = mapWarpEntity->type;
    warpEntity->group = mapWarpEntity->group;
    warpEntity->enabled = mapWarpEntity->enabled;
    warpEntity->homeRoom = levelId;

    warpEntity->size.x = 1;
    warpEntity->targetLevel = mapWarpEntity->targetLevel;
    warpEntity->targetWarp = mapWarpEntity->targetWarp;
}

void InitDecorEntity(s16 levelId, DecorEntity *entity, MapDecorEntity *mapEntity)
{
//    InitBasePartEntity(levelId, entity, mapEntity);
    entity->name = mapEntity->name;
    entity->pos.x = mapEntity->x;
    entity->pos.y = mapEntity->y;
    entity->size.x = mapEntity->width;
    entity->size.y = mapEntity->height;
    entity->id = mapEntity->id;
    entity->type = mapEntity->type;
    entity->group = mapEntity->group;
    entity->enabled = mapEntity->enabled;
    entity->homeRoom = levelId;

    entity->priority = mapEntity->priority;

    switch (entity->type)
    {
    case 2:
        DecorInitSprite(entity, MUSHROOM_BIG, 1);
        break;
    case 1:
        DecorInitSprite(entity, MUSHROOM_MID, -1);
        break;
    case 0:
        DecorInitSprite(entity, MUSHROOM_SMALL, 1);
        break;
    case 4:
        DecorInitSprite(entity, FIREWOOD, 1);
        break;
    case 5:
        DecorInitSprite(entity, WEBS_SMALL, 1);
        break;
    case 10:
//        PAL_setPalette(PAL_ENTITY, spriteDef[LANTERN]->palette->data, DMA);
        DecorInitSprite(entity, LANTERN, 1);
        entity->sprite->animation->frames[0]->collision->hit.box = lanternHitbox[0][0];
        break;
    default:
        kprintf("unregistred entity type: %d", entity->type);
        break;
    }
}

void DecorReleaseSprites(s16 index)
{
    for (u16 i = 0; i < romLevel[index].decorCount; i++)
    {
        DecorEntity *entity = &decorEntity[i];
        if (entity->sprite != NULL) SPR_releaseSprite(entity->sprite);
    }
}

bool IsPositionCollideEntity(AABB_s16 *bodyBound, WarpEntity *entity)
{
    if ((bodyBound->max.x < entity->pos.x) || (bodyBound->min.x > entity->pos.x + entity->size.x))
        return false;

    if ((bodyBound->max.y >= entity->pos.y) && (bodyBound->min.y <= entity->pos.y + entity->size.y))
    {
        return true;
    }
    return false;
}

s8 GetDirectionOfEntityCollision(AABB_s16 *bodyBound, WarpEntity *entity)
{
    if (!IsPositionCollideEntity(bodyBound, entity))
        return NULL;

    if (bodyBound->max.x > entity->pos.x + entity->size.x)
        return -1;
    else
        return 1;
}

Vect2D_s16 WarpGetExitPosition(s16 targetWarpId, s8 collisionDirection, s16 playerShiftY)
{
    WarpEntity *exitWarp = &warpEntity[targetWarpId];

    s16 posX = 0;

    if (collisionDirection == 1)
        posX = exitWarp->pos.x + exitWarp->size.x + PLAYER_WARP_SHIFT_X;
    else if (collisionDirection == -1)
        posX = exitWarp->pos.x - PlayerGetAABBWidth() - PLAYER_WARP_SHIFT_X;

    return (Vect2D_s16){
        posX,
        exitWarp->pos.y + playerShiftY};
}

void LoadLevelAndStartAt(s16 targetLevelId, s16 targetWarpId, s8 collisionDirection, s16 playerShiftY)
{
//    KDebug_Halt();
    GFX_FadeOutScreen();

    SYS_disableInts();


    DecorReleaseSprites(activeLevel.lvlMap->index);


    LoadLevel(targetLevelId);

    BindCurrentLevelWarps();

    Vect2D_s16 warpPos = WarpGetExitPosition(targetWarpId, collisionDirection, playerShiftY);
    PlayerSetPositionByBB((Vect2D_f32) {FIX32(warpPos.x), FIX32(warpPos.y)});

    PlayerUpdate();

    CameraUpdate();


    BindCurrentLevelEntities();
    SYS_doVBlankProcess();


    DecorUpdate();
    PlayerUpdate();


    SPR_update();
    SYS_doVBlankProcess();

    SYS_enableInts();

    GFX_FadeInScreen();

    SPR_update();
    SYS_doVBlankProcess();
}


void WarpUpdate(AABB_s16 *bodyBound)
{
    for (u16 i = 0; i < romLevel[activeLevel.lvlMap->index].warpCount; i++)
    {
        WarpEntity *sourceWarp = &warpEntity[i];

        s8 collisionDirection = GetDirectionOfEntityCollision(bodyBound, sourceWarp);

        if (collisionDirection != NULL)
        {
            s16 targetLevelId = sourceWarp->targetLevel;
            s16 targetWarpId = sourceWarp->targetWarp;
            s16 playerShiftY = fix32ToInt(PlayerGetBBPosition().y) - sourceWarp->pos.y;


            LoadLevelAndStartAt(targetLevelId, targetWarpId, collisionDirection, playerShiftY);
        }
    }
}


void DecorInitSprite(DecorEntity *entity, u16 spriteDefIndex, s16 depth)
{
    entity->sprite = SPR_addSprite(spriteDef[spriteDefIndex], entity->pos.x, entity->pos.y,
                                   TILE_ATTR(PAL_ENTITY, TRUE, FALSE, FALSE));
    SPR_setVisibility(entity->sprite, AUTO_FAST);
    SPR_setDepth(entity->sprite, depth);
//    SPR_update();
//    SYS_doVBlankProcess();
}

void DecorUpdate()
{
    for (u16 i = 0; i < romLevel[activeLevel.lvlMap->index].decorCount; i++)
    {
        DecorEntity *entity = &decorEntity[i];
        SPR_setPosition(entity->sprite, entity->pos.x - fix32ToInt(GetCameraPositionFix().x), entity->pos.y - fix32ToInt(GetCameraPositionFix().y));
    }
}
