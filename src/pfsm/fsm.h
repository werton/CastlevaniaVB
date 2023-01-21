#ifndef FSM_INCLUDE_H
#define FSM_INCLUDE_H

#include "state.h"
#include "player.h"

void FsmInit();

void TrySetState(Player *context, State *newState);

void SetState(Player *context, State *newState);

StateId GetStateId(Player *context);

void TriggerIdle(Player *context);

void TriggerLeft(Player *context);

void TriggerRight(Player *context);

void TriggerDown(Player *context);

void TriggerJump(Player *context);

void TriggerFall(Player *context);

void TriggerAttack(Player *context);

void TriggerGrounded(Player *context);

void SetStateIdle(Player *context);


#endif // FSM_INCLUDE_H
