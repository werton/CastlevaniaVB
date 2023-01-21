#ifndef TILE_PHYSICS_H
#define TILE_PHYSICS_H

#include <genesis.h>
#include "types.h"

u16 getTileLeftPosX(u16 x);
u16 getTileRightPosX(u16 x);
u16 getTileTopPosY(u16 y);
u16 getTileBottomPosY(u16 y);
AABB_s16 getTileBounds(s16 x, s16 y);
Vect2D_u16 posToTile(Vect2D_s16 position);

#endif // TILE_PHYSICS_H

