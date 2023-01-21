#ifndef STATE_INCLUDE_H
#define STATE_INCLUDE_H

#include <genesis.h>
#include "state.h"


/* An incomplete type for the state representation itself. */
typedef struct State* StatePtr;

void resetStateTransitions(StatePtr state);
void printEventCalled(StatePtr state);


/*
 We need a shared definition of our incomplete type
 exposed in the API. One strategy is to define it
 in an include file like this that we can share
 between the different translation units.
 The advantage is that we keep the definition out
 of the API.
*/

/* Simplify the code by using typedefs for the function pointers. */
typedef StatePtr (*EventFunctNone)(StatePtr);
typedef StatePtr (*EventFunctLeft)(StatePtr);
typedef StatePtr (*EventFunctRight)(StatePtr);
typedef StatePtr (*EventFunctUp)(StatePtr);
typedef StatePtr (*EventFunctDown)(StatePtr);
typedef StatePtr (*EventFunctAction)(StatePtr);
typedef StatePtr (*EventFunctJump)(StatePtr);
typedef StatePtr (*EventFunctAttack)(StatePtr);
typedef StatePtr (*EventFunctHurt)(StatePtr);
typedef StatePtr (*EventFunctFall)(StatePtr);
typedef StatePtr (*EventFunctGround)(StatePtr);

typedef void (*OnUpdateCallback)(StatePtr);
typedef void (*OnExitCallback)(StatePtr);

typedef enum
{
    STATE_IDLE = 0,
    STATE_WALK,
    STATE_JUMP,
    STATE_FALL,
    STATE_ATTACK,
    STATE_AIR_ATTACK,
} StateId;

typedef struct State
{
  EventFunctNone    event_none;
  EventFunctLeft    event_left;
  EventFunctRight   event_right;
  EventFunctUp      event_up;
  EventFunctDown    event_down;
  EventFunctAction  event_action;
  EventFunctJump    event_jump;
  EventFunctAttack  event_attack;
  EventFunctGround  event_ground;
  EventFunctFall    event_fall;
  EventFunctHurt    event_hurt;


  OnUpdateCallback OnUpdate;
  OnExitCallback OnExit;
//  char* name;
  StateId id;
} State;

void printState(State* state);

StatePtr defaultWalk(State* state);

#endif // STATE_INCLUDE_H

