#include "defs.h"
#include "debug.h"
#include "global.h"
#include "colmap.h"
#include "input.h"
#include "player.h"
#include "pfsm/fsm.h"


void OnInputCallback(u16 joypad, u16 changed, u16 state)
{
    const u16 ind = (joypad == JOY_1) ? 0 : 1;

    if (ind == 1)
        return;

    if (state & BUTTON_RIGHT)
        joy[ind].dpad.Right = true;
    else if (changed & BUTTON_RIGHT)
        joy[ind].dpad.Right = false;

    if (state & BUTTON_LEFT)
        joy[ind].dpad.Left = true;
    else if (changed & BUTTON_LEFT)
        joy[ind].dpad.Left = false;

    if (state & BUTTON_UP)
        joy[ind].dpad.Up = true;
    else if (changed & BUTTON_UP)
        joy[ind].dpad.Up = false;

    if (state & BUTTON_DOWN)
        joy[ind].dpad.Down = true;
    else if (changed & BUTTON_DOWN)
        joy[ind].dpad.Down = false;

    if (state & changed & BUTTON_A)
        joy[ind].button.A = true;
    else if (BUTTON_A)
        joy[ind].button.A = false;

    if (state & changed & BUTTON_B)
        joy[ind].button.B = true;
    else if (BUTTON_B)
        joy[ind].button.B = false;

    if (state & changed & BUTTON_C)
        joy[ind].button.C = true;
    else if (BUTTON_C)
        joy[ind].button.C = false;

    if (state & changed & BUTTON_X)
        joy[ind].button.X = true;
    else if (BUTTON_X)
        joy[ind].button.X = false;

    if (state & changed & BUTTON_Y)
        joy[ind].button.Y = true;
    else if (BUTTON_Y)
        joy[ind].button.Y = false;

    if (state & changed & BUTTON_Z)
        joy[ind].button.Z = true;
    else if (BUTTON_Z)
        joy[ind].button.Z = false;

    if (state & changed & BUTTON_START)
        joy[ind].button.Start = true;
    else if (BUTTON_START)
        joy[ind].button.Start = false;

    if (state & changed & BUTTON_MODE)
        joy[ind].button.Mode = true;
    else if (BUTTON_MODE)
        joy[ind].button.Mode = false;


    if (joy[ind].button.C)
    {
        PlayerBufferJump();
    }
    else if (changed & BUTTON_C && (player.state->id == STATE_JUMP || player.state->id == STATE_AIR_ATTACK)
    && player.lowJumpCounter <= PLAYER_LOW_JUMP_FRAMES && player.velocity.fixY < 0)     //FIXME: low jump costil
    {
        PlayerCancelJumpExecution();
    }

    if (joy[ind].button.B)
    {
        TriggerAttack(&player);
    }

    // NOTE: Up direction is -1 and down direction is 1, this is because the Mega Drive draws the screen from top to bottom
    player.input.x = 0;
    player.input.y = 0;

    if (joy[ind].dpad.Up)
    {
        player.input.y --;
    }

    if (joy[ind].dpad.Down)
    {
        player.input.y ++;
        player.isDownJump = true;
    }

    if (joy[ind].dpad.Right)
        player.input.x ++;
    if (joy[ind].dpad.Left)
        player.input.x --;

}
