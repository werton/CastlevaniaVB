#include <genesis.h>
#include "../fsm.h"

/* Possible transition to the following state: */
#include "idle.h"
#include "walk.h"
#include "jump.h"
#include "fall.h"
#include "attack.h"

#include "player.h"

static StatePtr TransitionToIdle(State *state)
{
    return GetStateIdle();
}

static StatePtr TransitionToJump(State *state)
{
    return GetStateJump();
}

static StatePtr TransitionToFall(State *state)
{
    player.coyoteCounter = PLAYER_COYOTE_FRAMES;
    kprintf("reset coyote");
    return GetStateFall();
}

static StatePtr TransitionToAttack(State *state)
{
    return GetStateAttack();
}

static void OnEnter(State *state)
{
    kprintf("enter walk state, anim id: %d", PL_ANIM_WALK);
    Player_SetAnim(PL_ANIM_WALK);
    player.coyoteCounter = 0;
}

static void OnUpdate(State *state)
{
    if (PlayerHorMovementUpdate())
    {

    }
    else if (player.isGrounded)
    {
        player.velocity.x = 0;
        SetState(&player, GetStateIdle());
    }

    PlayerGravityUpdate();
}

static void OnExit(State *state)
{
    player.velocity.x = 0;
}

StatePtr GetStateWalk() {
    static struct State state;
    static bool isInitialized = false;

    if (0 == isInitialized)
    {
        resetStateTransitions(&state);
        state.id = STATE_WALK;
        state.OnExit = OnExit;
        state.OnUpdate = OnUpdate;
        state.event_jump = TransitionToJump;
        state.event_fall = TransitionToFall;
        state.event_attack = TransitionToAttack;
        state.event_none = TransitionToIdle;
        isInitialized = true;
    }
    else
        OnEnter(&state);

    return &state;
}
