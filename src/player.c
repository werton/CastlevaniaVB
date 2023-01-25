#include "defs.h"
#include "debug.h"
#include "global.h"
#include "player.h"
#include "chars.h"
#include "collision.h"
#include "physics.h"
#include "colmap.h"
#include "pfsm/fsm.h"
#include "sprites.h"

const Vect2D_f32 levelStartPos = {FIX32(50), FIX32(50)};

struct pBody player;

Vect2D_f32 PlayerGetPosition(void);
BB_s16 PlayerGetBB(void);
s16 PlayerGetAABBWidth(void);
Vect2D_f32 PlayerGetBBPosition(void);
void PlayerSetPositionByBB(Vect2D_f32 position);
void PlayerSetPosition(Vect2D_f32 position);
void Player_OnFrameChangeCallback(Sprite *sprite);


void PlayerInit()
{
    // Create the sprite and palette for the player

    player.spriteDef[0] = &player_sprite_idle;
    player.spriteDef[1] = &player_sprite_walk;
    player.spriteDef[2] = &player_sprite_jump;
    player.spriteDef[3] = &player_sprite_fall;

    player.sprite = SPR_addSprite(&player_sprite_idle, levelStartPos.x, levelStartPos.y,
                                  TILE_ATTR(PAL_PLAYER, TRUE, FALSE, FALSE));
//    player.sprites[1] = SPR_addSprite(&player_sprite_walk, levelStartPos.x, levelStartPos.y,
//                                      TILE_ATTR(PAL_PLAYER, TRUE, FALSE, FALSE));

    PAL_setPalette(PAL_PLAYER, player_sprite_idle.palette->data, DMA);
    SPR_setDepth(player.sprite, PLAYER_SPRITE_DEPTH);

    // Set the global position of the player, the local position will be updated once we are in the main loop
    PlayerSetPosition(levelStartPos);

    SPR_setFrameChangeCallback(player.sprite,Player_OnFrameChangeCallback);


    // We set collider size of the player
    player.aabb = &playerConfig.aabb;

    // Calculate where's the center point of the player
    player.centerOffset.x = ((player.aabb->min.x + player.aabb->max.x) >> 1);
    player.centerOffset.y = ((player.aabb->min.y + player.aabb->max.y) >> 1);

    // Default movement values
    player.facingDirection = POSITIVE;

    FsmInit();

    SetStateIdle(&player);

    printState(player.state);
}

void Player_SetAnim(u8 animInd)
{
    SPR_setDefinition(player.sprite, player.spriteDef[animInd]);
    SPR_setAnimAndFrame(player.sprite, 0, 0);
    player.spriteDefInd = animInd;
}

void Player_OnFrameChangeCallback(Sprite *sprite)
{
    player.frameTick = 0;
}

void Player_OnAnimationEnd()
{

}

void Player_OnFrameEnd()
{

}

void Player_OnLastFrameStart()
{

}

void Player_OnNextFrameStart()
{

}

void Player_NextFrame()
{
    SPR_nextFrame (player.sprite);
    player.frameTick = 0;

    s16 frameInd = player.sprite->frameInd;

    Player_OnNextFrameStart();

//    if (frameInd == player.sprite->animation->numFrame - 1)
//        Player_OnLastFrameStart();
}

void Player_SwitchFrame()
{
    if (player.sprite->frameInd == player.sprite->animation->numFrame - 1)
        Player_OnAnimationEnd();

    Player_NextFrame();
}

void Player_NextFrameByTimer()
{
//    s16 animInd = player.sprite->animInd;
    s16 animInd = player.spriteDefInd;
    s16 frameInd = player.sprite->frameInd;
    u8 frameDelay = bodyFrameDelay[CHAR_MICE][animInd][frameInd];


    player.frameTick ++;

    if (frameDelay == 0)
        frameDelay = 15;

    if (player.frameTick == frameDelay)
    {
        Player_OnFrameEnd();
        Player_SwitchFrame();
    }

}


void PlayerUpdate()
{
    player.state->OnUpdate(player.state);
    Player_NextFrameByTimer();

    // apply horizontal movement
    if (player.input.x > 0)
        TriggerRight(&player);
    else if (player.input.x < 0)
        TriggerLeft(&player);

    PlayerUpdateFacing();
    PlayerJumpBufferUpdate();
    PlayerExecuteBufferedJump();

    // Once all the input-related have been calculated, we apply the velocities to the global positions
    PlayerSetPositionX(player.globalPosition.x + fix16ToFix32(player.velocity.x));
    PlayerSetPositionY(player.globalPosition.y + fix16ToFix32(player.velocity.fixY));

    // Now we can check for collisions and correct those positions
    CollisionsUpdate();

    // Once the positions are correct, we position the player taking into account the camera position
    player.position.x = player.globalPosition.x - GetCameraPositionFix().x;
    player.position.y = player.globalPosition.y - GetCameraPositionFix().y;
    SPR_setPosition(player.sprite, fix32ToInt(player.position.x), fix32ToInt(player.position.y));

}

bool PlayerHorMovementUpdate()
{
    if (player.input.x > 0)
    {
        player.facingDirection = POSITIVE;
        player.velocity.x =  PLAYER_WALK_SPEED;
        return true;
    }
    else if (player.input.x < 0)
    {
        player.facingDirection = NEGATIVE;
        player.velocity.x = -PLAYER_WALK_SPEED;
        return true;
    }

    return false;
}

void PlayerResetPosition()
{
    PlayerSetPosition(levelStartPos);
}

void PlayerSetPosition(Vect2D_f32 position)
{
    player.globalPositionPrev = player.globalPosition;
    player.globalPosition = position;
}

void PlayerSetPositionByBB(Vect2D_f32 position)
{
    player.globalPositionPrev = player.globalPosition;
    player.globalPosition = (Vect2D_f32) {position.x - FIX32(player.aabb->min.x),
                                          position.y - FIX32(player.aabb->min.y)};
}

void PlayerSetPositionX(f32 x)
{
    PlayerSetPosition((Vect2D_f32) {x, player.globalPosition.y});
}

void PlayerSetPositionY(f32 y)
{
    PlayerSetPosition((Vect2D_f32) {player.globalPosition.x, y});
}

Vect2D_f32 PlayerGetBBPosition()
{
    return (Vect2D_f32) {player.globalPosition.x + FIX32(player.aabb->min.x),
                         player.globalPosition.y + FIX32(player.aabb->min.y)};
}

Vect2D_f32 PlayerGetPosition()
{
    return player.globalPosition;
}

u16 PlayerGetSpriteWidth()
{
    return player.sprite->definition->w;
}

BB_s16 PlayerGetBB()
{
    return (BB_s16) {player.aabb->min.x, player.aabb->min.y, player.aabb->max.x, player.aabb->max.y};
}

s16 PlayerGetAABBWidth()
{
    return player.aabb->max.x - player.aabb->min.x;
}

s16 PlayerGetAABBHeight()
{
    return player.aabb->max.y - player.aabb->min.y;
}

s8 PlayerGetMoveDirectionX()
{
    s16 dir = fix32ToInt(player.globalPosition.x - player.globalPositionPrev.x);
    return (dir > 0) ? 1 : ((dir < 0) ? -1 : 0);
}

void PlayerPrintPosition()
{
    kprintf("PL prev x: %ld, PL prev y: %ld", fix32ToInt(player.globalPositionPrev.x),
            fix32ToInt(player.globalPositionPrev.y));
    kprintf("PL x: %ld, PL y: %ld", fix32ToInt(player.globalPosition.x), fix32ToInt(player.globalPosition.y));
}


