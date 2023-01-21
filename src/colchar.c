#include "colchar.h"
#include "defs.h"


const BoxCollision playerHitbox[MICE_MAX_ANIMS][MICE_ANIM_MAX_FRAMES] = { // indexes: anim_id, frame_id, coord
    [PL_ANIM_IDLE][0]              = (BoxCollision) {17, 6, 29, 30},
    [PL_ANIM_IDLE][1]              = (BoxCollision) {17, 6, 29, 30},
    [PL_ANIM_IDLE][2]              = (BoxCollision) {17, 6, 29, 30},
    [PL_ANIM_IDLE][3]              = (BoxCollision) {17, 6, 29, 30},
    [PL_ANIM_IDLE][4]              = (BoxCollision) {17, 6, 29, 30},
    [PL_ANIM_IDLE][5]              = (BoxCollision) {17, 6, 29, 30},
    [PL_ANIM_IDLE][6]              = (BoxCollision) {17, 6, 29, 30},
    [PL_ANIM_IDLE][7]              = (BoxCollision) {17, 6, 29, 30},
};

//const BoxCollision playerAttackBox[MICE_MAX_ANIMS][MICE_ANIM_MAX_FRAMES] = { // indexes: anim_id, frame_id, coord
//        [PL_ANIM_IDLE][0]              = (BoxCollision) {17, 6, 29, 30},
//        [PL_ANIM_IDLE][1]              = (BoxCollision) {17, 6, 29, 30},
//        [PL_ANIM_IDLE][2]              = (BoxCollision) {17, 6, 29, 30},
//        [PL_ANIM_IDLE][3]              = (BoxCollision) {17, 6, 29, 30},
//        [PL_ANIM_IDLE][4]              = (BoxCollision) {17, 6, 29, 30},
//        [PL_ANIM_IDLE][5]              = (BoxCollision) {17, 6, 29, 30},
//        [PL_ANIM_IDLE][6]              = (BoxCollision) {17, 6, 29, 30},
//        [PL_ANIM_IDLE][7]              = (BoxCollision) {17, 6, 29, 30},
//};

const BoxCollision lanternHitbox[1][1] = { // indexes: anim_id, frame_id, coord
        [0][0]              = (BoxCollision) {24, 12, 9, 28},
};