#include <genesis.h>
#include "state.h"

void printEventCalled(State* state)
{
    kprintf("called: %d", state->id);
}

void printState(State *state)
{
    kprintf("state is: %d", state->id);
}

void missingEvent(State* state)
{
    kprintf("unsuccessful attempt to transit in: %d, do default action", state->id);
}

StatePtr NoneTransition(State* state)
{
//    kprintf("unsuccessful attempt to transit in: %s state, ignored\n");
//    printState(state);
    return NULL;
}

StatePtr NoneTransitionIdle(State* state)
{
//    kprintf("unsuccessful attempt to transit in: %s state, do default action\n", "idle");
//    printState(state);
    return NULL;
}

StatePtr NoneTransitionWalk(State* state)
{
    kprintf("unsuccessful attempt to transit in: %s state, do default action\n", "walk");
    printState(state);
    return NULL;
}

StatePtr NoneTransitionJump(State* state)
{
    kprintf("unsuccessful attempt to transit in: %s state, do default action\n", "jump");
    printState(state);
    return NULL;
}

StatePtr NoneTransitionAttack(State* state)
{
    kprintf("unsuccessful attempt to transit in: %s state, do default action\n", "attack");
    printState(state);
    return NULL;
}

StatePtr NoneTransitionAction(State* state)
{
    kprintf("unsuccessful attempt to transit in: %s state, do default action\n", "action");
    printState(state);
    return NULL;
}

void resetStateTransitions(State* state)
{
    state->event_none = NoneTransitionIdle;
    state->event_left = NoneTransition;
    state->event_right = NoneTransition;
    state->event_up = NoneTransition;
    state->event_down = NoneTransition;
    state->event_jump = NoneTransitionJump;
    state->event_fall = NoneTransitionJump;
    state->event_attack = NoneTransitionAttack;
    state->event_action = NoneTransitionAction;
    state->event_ground = NoneTransition;
    state->event_hurt = NoneTransition;
}
