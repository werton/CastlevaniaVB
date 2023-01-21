#ifndef INPUT_INCLUDE_H
#define INPUT_INCLUDE_H

#include <genesis.h>
#include "defs.h"

void OnInputCallback(u16 joy, u16 changed, u16 state);

struct Dpad
{
    u8 Left, Right, Up, Down;
};

struct Button
{
    bool A, B, C, X, Y, Z, Mode, Start;
};

typedef struct
{
    struct Dpad dpad;
    struct Button button;
} Input;

#endif // INPUT_INCLUDE_H
