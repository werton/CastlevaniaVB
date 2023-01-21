#ifndef PLAYER_INCLUDE_H
#define PLAYER_INCLUDE_H

#include <genesis.h>
#include "physics.h"
#include "types.h"
#include "camera.h"
#include "pfsm/state.h"

typedef struct pBody
{
    const SpriteDefinition *spriteDef[10];
    Sprite *sprite;
    State *state;
    const AABB_s16* aabb;

    s8 facingDirection;
    s16 coyoteCounter;
    s16 jumpBufferCounter;
    s16 lowJumpCounter;

    bool isGrounded;
    bool isDownJump;

    u8 spriteDefInd;

    Vect2D_f32 position;
    Vect2D_f32 globalPosition;
    Vect2D_f32 globalPositionPrev;
    Vect2D_u16 centerOffset;

    u8 frameTick;

    struct
    {
        fix16 fixX;
        fix32 x;
        fix16 fixY;
    } velocity;

    Vect2D_s16 input;
} Player;

extern struct pBody player;

void PlayerInit(void);

void PlayerUpdate(void);

void PlayerResetPosition(void);

Vect2D_f32 PlayerGetPosition(void);

BB_s16 PlayerGetBB(void);

s16 PlayerGetAABBWidth(void);

void PlayerSetPositionByBB(Vect2D_f32 position);

Vect2D_f32 PlayerGetBBPosition(void);

void PlayerSetPositionX(f32 x);

void PlayerSetPositionY(f32 y);

bool PlayerHorMovementUpdate();

void Player_SetAnim(u8 animInd);


#endif // PLAYER_INCLUDE_H
