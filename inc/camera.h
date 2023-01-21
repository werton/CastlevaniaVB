#ifndef CAMERA_INCLUDE_H
#define CAMERA_INCLUDE_H

#include <genesis.h>
#include "types.h"
#include "player.h"
#include "physics.h"
#include "level.h"


void setupCamera(Vect2D_u16 deadZoneCenter, u16 deadZoneWidth, u16 deadZoneHeight);
void CameraUpdate(void);
void CameraInit(Vect2D_u16 deadZoneCenter, u16 deadZoneWidth, u16 deadZoneHeight);

Vect2D_f32 GetCameraPositionFix(void);
Vect2D_s16 GetCameraPositionInt(void);

#endif // CAMERA_INCLUDE_H

