#include "debug.h"
#include "obj_debug.h"
#include "global.h"
#include "entities.h"


void PrintWarp(s16 targetLevelId, s16 targetWarpId)
{
    kprintf("target lvl: %d, warp: %d", targetLevelId, targetWarpId);
}

void LogMapWarpEntity(MapWarpEntity *entity)
{
    LOG("--------MapWarpEntity---------");
    kprintf("name: %s", entity->name);
    LOGX("x: ", entity->x);
    LOGX("y: ", entity->y);
    LOGX("width: ", entity->width);
    LOGX("height: ", entity->height);
    LOGX("id: ", entity->id);
    LOGX("type: ", entity->type);
    LOGX("group: ", entity->group);
    LOGX("enabled: ", entity->enabled);
    LOGX("targetLevel: ", entity->targetLevel);
    LOGX("targetWarp: ", entity->targetWarp);
    LOG("-----------------");
}

void LogMapDecorEntity(MapDecorEntity *entity)
{
    LOG("--------MapDecorEntity---------");
    kprintf("name: %s", entity->name);
    LOGX("x: ", entity->x);
    LOGX("y: ", entity->y);
    LOGX("width: ", entity->width);
    LOGX("height: ", entity->height);
    LOGX("id: ", entity->id);
    LOGX("type: ", entity->type);
    LOGX("group: ", entity->group);
    LOGX("enabled: ", entity->enabled);
    LOGX("priority: ", entity->priority);
    LOG("-----------------");
}

void LogWarpEntity(WarpEntity *entity)
{
    LOG("--------WarpEntity---------");
    kprintf("name: %s", entity->name);
    LOGX("x: ", entity->pos.x);
    LOGX("y: ", entity->pos.y);
    LOGX("width: ", entity->size.x);
    LOGX("height: ", entity->size.y);
    LOGX("id: ", entity->id);
    LOGX("type: ", entity->type);
    LOGX("group: ", entity->group);
    LOGX("enabled: ", entity->enabled);
    LOGX("homeRoom: ", entity->homeRoom);
    LOGX("targetLevel: ", entity->targetLevel);
    LOGX("targetWarp: ", entity->targetWarp);
    LOG("-----------------");
}

void LogDecorEntity(DecorEntity *entity)
{
    LOG("--------DecorEntity---------");
    kprintf("name: %s", entity->name);
    LOGX("x: ", entity->pos.x);
    LOGX("y: ", entity->pos.y);
    LOGX("width: ", entity->size.x);
    LOGX("height: ", entity->size.y);
    LOGX("id: ", entity->id);
    LOGX("type: ", entity->type);
    LOGX("group: ", entity->group);
    LOGX("enabled: ", entity->enabled);
    LOGX("homeRoom: ", entity->homeRoom);
    LOGX("priority: ", entity->priority);
    LOG("-----------------");
}
