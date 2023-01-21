#include "global.h"
#include "camera.h"
#include "tilemaps.h"
#include "sprites.h"
#include "sounds.h"

AABB_s16 cameraDeadzone;
Vect2D_f32 cameraPosition;

Vect2D_f32 GetCameraPositionFix();


void CameraInit(Vect2D_u16 deadZoneCenter, u16 deadZoneWidth, u16 deadZoneHeight)
{
    //Calculates the bounds of the deadZone
    cameraDeadzone.min.x = deadZoneCenter.x - (deadZoneWidth >> 1);
    cameraDeadzone.max.x = deadZoneCenter.x + (deadZoneWidth >> 1);
    cameraDeadzone.min.y = deadZoneCenter.y - (deadZoneHeight >> 1);
    cameraDeadzone.max.y = deadZoneCenter.y + (deadZoneHeight >> 1);
}

void setupCamera(Vect2D_u16 deadZoneCenter, u16 deadZoneWidth, u16 deadZoneHeight)
{
    //Calculates the bounds of the deadZone
    cameraDeadzone.min.x = deadZoneCenter.x - (deadZoneWidth >> 1);
    cameraDeadzone.max.x = deadZoneCenter.x + (deadZoneWidth >> 1);
    cameraDeadzone.min.y = deadZoneCenter.y - (deadZoneHeight >> 1);
    cameraDeadzone.max.y = deadZoneCenter.y + (deadZoneHeight >> 1);

    CameraUpdate();
    //We force to update the whole layer in order to prevent wrong tile being loaded depending on the position
    MAP_scrollToEx(activeLevel.map[BG_A], fix32ToInt(cameraPosition.x), fix32ToInt(cameraPosition.y), TRUE);
    //WARNING: first MAP_scrollTo(..) call will do a full plane update, for a 64x32 sized plane this represents 4KB of data.
    //That means you can't initialize 2 MAPs in the same frame (limited to 7.2 KB of data per frame) so take care of calling SYS_doVBlankProcess() in between.
    SYS_doVBlankProcess();
    MAP_scrollToEx(activeLevel.map[BG_B], activeLevel.map[BG_B]->posX, activeLevel.map[BG_B]->posY, TRUE);
}

void CameraUpdate()
{
    //Update camera only if the center of the player is outside the deadZone of the camera
    if (player.globalPosition.x + FIX32(player.centerOffset.x) > cameraPosition.x + FIX32(cameraDeadzone.max.x))
    {
        cameraPosition.x = player.globalPosition.x + FIX32(player.centerOffset.x - cameraDeadzone.max.x);
    }
    else if (player.globalPosition.x + FIX32(player.centerOffset.x) < cameraPosition.x + FIX32(cameraDeadzone.min.x))
    {
        cameraPosition.x = player.globalPosition.x + FIX32(player.centerOffset.x - cameraDeadzone.min.x);
    }

    if (player.globalPosition.y + FIX32(player.centerOffset.y) > cameraPosition.y + FIX32(cameraDeadzone.max.y))
    {
        cameraPosition.y = player.globalPosition.y + FIX32(player.centerOffset.y - cameraDeadzone.max.y);
    }
    else if (player.globalPosition.y + FIX32(player.centerOffset.y) < cameraPosition.y + FIX32(cameraDeadzone.min.y))
    {
        cameraPosition.y = player.globalPosition.y + FIX32(player.centerOffset.y - cameraDeadzone.min.y);
    }

    //Clamp camera to the limits of the level
    cameraPosition.x = clamp(cameraPosition.x, 0,
                             FIX32(activeLevel.sizePixels.x - 320)); // 768 - 320 = 448 (level width - screen width)
    cameraPosition.y = clamp(cameraPosition.y, 0,
                             FIX32(activeLevel.sizePixels.y - 240)); // 768 - 224 = 544 (level height - screen height)
    // cameraPosition.y = clamp(cameraPosition.y, 0, currentMap.sizePixels.y - 176); // 768 - 224 = 544 (level height - screen height)
    // cameraPosition.y = clamp(cameraPosition.y, 0, currentMap.sizePixels.y - 240); // 768 - 224 = 544 (level height - screen height)

    //Finally we update the position of the camera
    MAP_scrollTo(activeLevel.map[BG_A],
                 fix32ToInt(cameraPosition.x), fix32ToInt(cameraPosition.y));
//	SYS_doVBlankProcess();
//    MAP_scrollTo(activeLevel.map[BG_B], fix32ToInt(fix32Mul(cameraPosition.x, activeLevel.BGOffsetScale)), activeLevel.map[BG_B]->posY);
    MAP_scrollTo(activeLevel.map[BG_B],
                 fix32ToInt(fix32Mul(cameraPosition.x, activeLevel.BGOffsetScale)),
                 fix32ToInt(fix32Mul(cameraPosition.y, activeLevel.BGOffsetScale)));
}

Vect2D_f32 GetCameraPositionFix()
{
    return cameraPosition;
}

Vect2D_s16 GetCameraPositionInt()
{
    return (Vect2D_s16) {fix32ToInt(cameraPosition.x), fix32ToInt(cameraPosition.y)};
}
