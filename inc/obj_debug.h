#ifndef OBJ_DEBUG_INCLUDE_H
#define OBJ_DEBUG_INCLUDE_H

#include "types.h"

void PrintWarp(s16 targetLevelId, s16 targetWarpId);
void LogMapWarpEntity(MapWarpEntity *entity);
void LogMapDecorEntity(MapDecorEntity *entity);
void LogBaseEntity(BaseEntityPart *entity);
void LogWarpEntity(WarpEntity *entity);
void LogDecorEntity(DecorEntity *entity);

#endif // OBJ_DEBUG_INCLUDE_H

