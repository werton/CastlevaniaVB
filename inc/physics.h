#ifndef INCLUDE_PHYSICS_H
#define INCLUDE_PHYSICS_H

#include <genesis.h>
#include "types.h"


void PlayerBufferJump();

void PlayerExecuteBufferedJump();

void PlayerCancelJumpExecution();

void PlayerJumpBufferUpdate();

void PlayerGravityUpdate();

void PlayerUpdateFacing();


#endif // INCLUDE_PHYSICS_H

