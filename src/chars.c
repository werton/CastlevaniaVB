#include <genesis.h>
//#include "defs.h"
#include "debug.h"
//#include "global.h"
#include "chars.h"
#include "colmap.h"
#include "sprites.h"


const u8 bodyFrameDelay[CHARS_COUNT][MAX_ANIMS][MAX_ANIMS_FRAMES] = {
        [CHAR_MICE][PL_ANIM_IDLE] =     {15, 10, 15},
        [CHAR_MICE][PL_ANIM_WALK] =     {6, 6, 6, 6, 6, 6, 6, 6},
        [CHAR_MICE][PL_ANIM_JUMP] =     {4, 5, 5, 20},
        [CHAR_MICE][PL_ANIM_FALL] =     {5, 6, 20},
        [CHAR_MICE][PL_ANIM_SWORD1] =   {4, 4, 5, 4, 4, 4},
        [CHAR_MICE][PL_ANIM_SWORD2] =   {4, 5, 6, 5, 5, 4},
};