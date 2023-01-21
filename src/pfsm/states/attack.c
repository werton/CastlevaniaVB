#include <genesis.h>
#include "../fsm.h"

#include "idle.h"
#include "walk.h"
#include "jump.h"
#include "fall.h"
#include "attack.h"
#include "air_attack.h"

#include "player.h"

static u8 comboStartOffsetFrame = PLAYER_SWORD_COMBO_START_FRAME;
static u8 comboCounter = 0;

static StatePtr TransitionToIdle(State *state) {
    return GetStateIdle();
}

static StatePtr TransitionToFall(State *state) {
    return GetStateFall();
}

static StatePtr TransitionToAirAttack(State *state) {
    return GetStateAirAttack();
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

static void OnEnter(State *state)
{
    comboCounter = 0;
    SPR_setAnim(player.sprite, PL_ANIM_SWORD1);
}

static void OnUpdate(State *state)
{
    if (SPR_getAnimationDone(player.sprite))
    {
        if (player.isGrounded)
            TrySetState(&player, TransitionToIdle(state));
        else
            TrySetState(&player, TransitionToFall(state));
    }

    PlayerGravityUpdate();
}

static void OnExit(State *state)
{

}

State* GetStateAttack() {
    static struct State state;
    static bool isInitialized = false;

    if (0 == isInitialized) {
        resetStateTransitions(&state);
        state.id = STATE_ATTACK;
        state.OnExit = OnExit;
        state.OnUpdate = OnUpdate;

        state.event_attack = TryExecCombo;
        state.event_fall = TransitionToAirAttack;
//        state.event_none = TransitionToIdle;

        isInitialized = true;
    }
    else
        OnEnter(&state);

    return &state;
}


//void onEnter() {
//    GetStateJump();
//}
