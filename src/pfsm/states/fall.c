#include <genesis.h>
//#include "../fsm.h"
#include "../state.h"
#include "player.h"

#include "idle.h"
#include "walk.h"
#include "fall.h"
#include "jump.h"
#include "attack.h"
#include "air_attack.h"

static StatePtr TransitionToIdle(State *state)
{
    return GetStateIdle();
}

static StatePtr TransitionToJump(State *state)
{
    if (player.coyoteCounter > 0)
        return GetStateJump();
    else
        return state;
}

static StatePtr TransitionToAirAttack(State *state)
{
    return GetStateAirAttack();
}

static void OnEnter(State *state)
{
    Player_SetAnim(PL_ANIM_FALL);
}

static void OnUpdate(State *state)
{
    PlayerHorMovementUpdate();
    PlayerGravityUpdate();

    player.coyoteCounter --;
}

static void OnExit(State *state)
{
}

StatePtr GetStateFall()
{
    static struct State state;
    static bool isInitialized = false;

    if (0 == isInitialized)
    {
        resetStateTransitions(&state);
        state.id = STATE_FALL;
        state.OnExit = OnExit;
        state.OnUpdate = OnUpdate;

        state.event_attack = TransitionToAirAttack;
        state.event_ground = TransitionToIdle;
        state.event_jump = TransitionToJump;

        isInitialized = true;
    }
    else
        OnEnter(&state);

    return &state;
}
