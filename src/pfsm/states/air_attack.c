#include <genesis.h>
#include "../fsm.h"

#include "idle.h"
#include "walk.h"
#include "jump.h"
#include "fall.h"
#include "air_attack.h"

#include "player.h"

static bool grounded = false;
static u8 comboStartOffsetFrame = PLAYER_SWORD_COMBO_START_FRAME;
static u8 comboCounter = 0;

static StatePtr TransitionToIdle(State *state) {
    return GetStateIdle();
}

static StatePtr TransitionToJump(State *state) {
    return GetStateJump();
}

static StatePtr TransitionToFall(State *state) {

    if (SPR_getAnimationDone(player.sprite))
    {
        return GetStateFall();
    }
    return NULL;
}

static StatePtr TryExecCombo(State *state)
{
    comboCounter++;

//    if (comboCounter <= 1)
//        return state;

    if (player.sprite->frameInd >= comboStartOffsetFrame)
    {
        SPR_setAnim(player.sprite, PL_ANIM_SWORD2);
    }

    return state;
}

static StatePtr OnGrounded(State *state)
{
    grounded = true;
    return state;
}

static void OnEnter(State *state)
{
    grounded = false;
    comboCounter = 0;
    SPR_setAnim(player.sprite, PL_ANIM_SWORD1);
}

static void OnUpdate(State *state)
{
    if (!grounded)
    {
        PlayerHorMovementUpdate();
        kprintf("aired");
    }
    else
    {
        player.velocity.x = 0;
        kprintf("grounded");
    }

    PlayerGravityUpdate();

    if (SPR_getAnimationDone(player.sprite))
    {
        TrySetState(&player, TransitionToFall(state));
    }
}

static void OnExit(State *state)
{

}

State* GetStateAirAttack() {
    static struct State state;
    static bool isInitialized = false;

    if (0 == isInitialized) {
        resetStateTransitions(&state);
        state.id = STATE_AIR_ATTACK;
        state.OnExit = OnExit;
        state.OnUpdate = OnUpdate;

//        state.event_none = TransitionToJump;
        state.event_attack = TryExecCombo;
        state.event_ground = OnGrounded;
        state.event_fall = TransitionToFall;

        isInitialized = true;
    }
    else
        OnEnter(&state);

    return &state;
}


//void onEnter() {
//    GetStateJump();
//}
