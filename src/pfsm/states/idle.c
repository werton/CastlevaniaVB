#include <genesis.h>
//#include "../fsm.h"
#include "player.h"

/* Possible transition to the following state: */
#include "idle.h"
#include "walk.h"
#include "jump.h"
#include "fall.h"
#include "attack.h"


static StatePtr TransitionToWalk(State *state)
{
    if (player.isGrounded)
        return GetStateWalk();
    return GetStateFall();
}

static StatePtr TransitionToJump(State *state)
{
    return GetStateJump();
}

static StatePtr TransitionToFall(State *state)
{
    return GetStateFall();
}

static StatePtr TransitionToAttack(State *state)
{
    return GetStateAttack();
}

static void OnEnter(State *state)
{
    player.velocity.x = 0;
    PlayerGravityUpdate();
//    SPR_setAnim(player.sprite, PL_ANIM_IDLE);
    Player_SetAnim(PL_ANIM_IDLE);
}

static void OnUpdate(State *state)
{
    PlayerGravityUpdate();
}

static void OnExit(State *state)
{

}

StatePtr GetStateIdle() {
    static struct State state;
    static bool isInitialized = 0;

    if (0 == isInitialized)
    {
        resetStateTransitions(&state);
        state.id = STATE_IDLE;
        state.OnExit = OnExit;
        state.OnUpdate = OnUpdate;
        state.event_left = TransitionToWalk;
        state.event_right = TransitionToWalk;
        state.event_jump = TransitionToJump;
        state.event_fall = TransitionToFall;
        state.event_attack = TransitionToAttack;
        isInitialized = 1;
    }
    else
        OnEnter(&state);

    return &state;
}

