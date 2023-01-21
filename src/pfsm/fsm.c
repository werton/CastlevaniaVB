#include <genesis.h>
#include "defs.h"
#include "debug.h"
#include "player.h"
#include "fsm.h"
#include "state.h"
#include "states/idle.h"
#include "states/walk.h"
#include "states/jump.h"
#include "states/fall.h"
#include "states/attack.h"
#include "states/air_attack.h"


void FsmInit()
{
    GetStateIdle();
    GetStateWalk();
    GetStateJump();
    GetStateFall();
    GetStateAttack();
    GetStateAirAttack();
}

StateId GetStateId(Player *context)
{
    return context->state->id;
}

void SetState(Player *context, State *newState)
{
    context->state = newState;
    kprintf("state set to: %d", context->state->id);
}

void TrySetState(Player *context, State *newState)
{
    if (NULL == newState)
        return;

    printEventCalled(newState);

    if (context->state->id != newState->id)
    {
        context->state->OnExit(context->state);
        SetState(context, newState);
    } else
        kprintf("ignored\n");
}

void SetStateIdle(Player *context)
{
    SetState(&player, GetStateIdle());
}

void TriggerGrounded(Player *context)
{
    TrySetState(context, context->state->event_ground(context->state));
}

void TriggerAttack(Player *context)
{
    TrySetState(context, context->state->event_attack(context->state));
}

void TriggerFall(Player *context)
{
    TrySetState(context, context->state->event_fall(context->state));
}

void TriggerJump(Player *context)
{
    TrySetState(context, context->state->event_jump(context->state));
}

void TriggerDown(Player *context)
{
    TrySetState(context, context->state->event_down(context->state));
}

void TriggerRight(Player *context)
{
    TrySetState(context, context->state->event_right(context->state));
}

void TriggerLeft(Player *context)
{
    TrySetState(context, context->state->event_left(context->state));
}

void TriggerIdle(Player *context)
{
    TrySetState(context, context->state->event_none(context->state));
}


