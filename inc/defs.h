#ifndef DEF_INCLUDE_H
#define DEF_INCLUDE_H

//===========   APP VERSION   =============

#define DEBUG_LOGGER                1

//===========   GAME CONFIG   =============
#define PLAYER_SWORD_COMBO_START_FRAME  2
#define PLAYER_JUMP_BUFFER_FRAMES       10
#define PLAYER_COYOTE_FRAMES            10
#define PLAYER_FALL_MAX_SPEED           5
#define PLAYER_JUMP_SPEED               FIX16(6.0)
#define PLAYER_WALK_SPEED               FIX16(1.3)
#define PLAYER_LOW_JUMP_FRAMES          7
#define PLAYER_LOW_JUMP_SCALE           FIX16(0.20)


#define BG_SCROLL_SPEED_SCALE           FIX32(0.45)
#define GRAVITY_SCALE                   FIX16(0.25)


//===========   LANGUAGE ADDITIONS   =============
#define true                            TRUE
#define false                           FALSE
#define POSITIVE                        1
#define NEGATIVE                        (-1)
#define NONE                            0

#define clamp01(X)   (min(max((X), (0)), (1)))
#define CONCAT_(a, b) a##b
#define CONCAT(a, b) CONCAT_(a, b)

#define SIZEOFARRAY(arr) 		        (sizeof((arr)) / sizeof((*arr)))
#define SIZEOF2DARRAY(arr) 		        (sizeof((arr)) / sizeof((arr[0][0])))
#define WIDTHOF2DARRAY(arr) 	        (sizeof((arr[0])) / sizeof((arr[0][0])))
#define HEIGHTOF2DARRAY(arr) 	        (sizeof((arr)) / sizeof((arr[0])))

#define SIGN(value)                     (((value) > 0) ? 1 : (((value) < 0) ? -1 : 0))

//===========   ENGINE   =============
#define MAX_BG_LAYERS 		            2

#define PAL_PLAN_A 		                PAL0
#define PAL_PLAN_B 		                PAL1
#define PAL_PLAYER 		                PAL2
#define PAL_ENTITY 		                PAL3

#define MAX_ANIMS                       8
#define MAX_ANIMS_FRAMES                8
#define CHARS_COUNT                     1

#define CHAR_MICE                       0
#define MICE_MAX_ANIMS                  10
#define MICE_ANIM_MAX_FRAMES            8

#define GROUND_TILE                     1
#define ONE_WAY_PLATFORM_TILE           3
#define MAX_LEVELS                      10
#define MAX_WARPS_PER_LEVEL             4
#define MAX_ENTITIES_PER_LEVEL          30
#define PLAYER_WARP_SHIFT_X             6
#define MAX_SPRITE_DEFS                 20

#define PLAYER_SPRITE_DEPTH             0

#define PL_ANIM_IDLE                    0
#define PL_ANIM_WALK                    1
#define PL_ANIM_JUMP                    2
#define PL_ANIM_FALL                    3
#define PL_ANIM_SWORD1                  4
#define PL_ANIM_SWORD2                  5


#define CONTROL_JUMP_BUTTON BUTTON_UP




#endif // DEF_INCLUDE_H

