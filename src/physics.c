#include <genesis.h>
#include "debug.h"
#include "defs.h"
#include "global.h"
#include "types.h"
#include "player.h"
#include "pfsm/fsm.h"


void PlayerBufferJump()
{
    player.jumpBufferCounter = PLAYER_JUMP_BUFFER_FRAMES;
}

void PlayerExecuteBufferedJump()
{
    if (player.jumpBufferCounter > 0)
        TriggerJump(&player);
}

void PlayerCancelJumpExecution()
{
    // If the button is released we remove half of the velocity
    player.velocity.fixY = fix16Mul(player.velocity.fixY, PLAYER_LOW_JUMP_SCALE);
}

void PlayerJumpBufferUpdate()
{
    player.jumpBufferCounter = clamp((player.jumpBufferCounter - 1), 0, PLAYER_JUMP_BUFFER_FRAMES);
}

void PlayerUpdateFacing()
{
    if (player.facingDirection > 0)
        SPR_setHFlip(player.sprite, FALSE);
    else if (player.facingDirection < 0)
        SPR_setHFlip(player.sprite, TRUE);
}

void PlayerTryFall()
{
    if (player.velocity.fixY > 0)
        TriggerFall(&player);
}

void PlayerGravityUpdate()
{
    // Apply gravity with a terminal velocity
    PlayerTryFall();

    if (fix16ToInt(player.velocity.fixY) <= PLAYER_FALL_MAX_SPEED)
    {
        player.velocity.fixY = fix16Add(player.velocity.fixY, GRAVITY_SCALE);
    } else
    {
        player.velocity.fixY = FIX16(PLAYER_FALL_MAX_SPEED);
    }
}