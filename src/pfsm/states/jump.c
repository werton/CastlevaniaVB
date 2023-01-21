#include <genesis.h>
//#include "../fsm.h"
#include "../state.h"
#include "player.h"

/* Possible transition to the following state: */
#include "idle.h"
#include "walk.h"
#include "jump.h"
#include "fall.h"
#include "attack.h"
#include "air_attack.h"

static StatePtr TransitionToIdle(State *state)
{
    return GetStateIdle();
}

static StatePtr TransitionToFall(State *state)
{
    return GetStateFall();
}

static StatePtr TransitionToAirAttack(State *state)
{
    return GetStateAirAttack();
}

static void OnEnter(State *state)
{
//    SPR_setAnim(player.sprite, PL_ANIM_JUMP);
    Player_SetAnim(PL_ANIM_JUMP);
    player.velocity.fixY = -PLAYER_JUMP_SPEED;
    player.coyoteCounter = 0;
    player.lowJumpCounter = 0;
}

static void OnUpdate(State *state)
{
    PlayerHorMovementUpdate();
    PlayerGravityUpdate();
    player.lowJumpCounter ++;
}

static void OnExit(State *state)
{
    player.lowJumpCounter = 0;
}

StatePtr GetStateJump()
{
    static struct State state;
    static bool isInitialized = false;

    if (0 == isInitialized)
    {
        resetStateTransitions(&state);
        state.id = STATE_JUMP;
        state.OnExit = OnExit;
        state.OnUpdate = OnUpdate;

        state.event_attack = TransitionToAirAttack;
        state.event_ground = TransitionToIdle;
        state.event_fall = TransitionToFall;

        isInitialized = true;
    }
    else
        OnEnter(&state);

    return &state;
}
