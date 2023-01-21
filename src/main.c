#include <genesis.h>
#include "defs.h"
#include "debug.h"
#include "types.h"
#include "input.h"
#include "entities.h"
#include "defs.h"
#include "level.h"
#include "camera.h"
#include "player.h"
#include "hud.h"
#include "gfx.h"
#include "sounds.h"


void DrawFPS(s16 x, s16 y, u16 asFloat);

int main(bool hardReset)
{

	if (!hardReset)
	{
		SYS_hardReset();
	}



    SYS_disableInts();

    PAL_setColors(0, (u16*) palette_black, 64, CPU);

	// Initialize joypad and sprite engine in order to use them
	JOY_init();
	SPR_init();

	VDP_setHilightShadow(TRUE);

	HUDInit();

    PlayerInit();

//    CameraInit((Vect2D_u16) {160, 112}, 50, 20);
    CameraInit((Vect2D_u16) {160, 112}, 50, 0);



    LoadLevelAndStartAt(3, 0, 1, 64-(player.aabb->max.y-player.aabb->min.y));

    // We have to set up always after the player, it directly depends on player's data
//    setupCamera((Vect2D_u16) {160, 112}, 50, 20);


    // Set up a callback when a button is pressed, we could call it a "pseudo parallel" joypad handler
	JOY_setEventHandler(OnInputCallback);


    VDP_setWindowHPos(FALSE, 0);
    VDP_setWindowVPos(false, 4);
    // VDP_setWindowVPos(true, 22);

    VDP_setTextPalette(PAL0);
    VDP_setTextPlane(WINDOW);
    VDP_setTextPriority(1);



    LOGX("allocated mem: ", MEM_getAllocated());

	LOGX("free mem: ", MEM_getFree());
    kprintf("Free VRAM %04d tiles", TILE_USER_MAX_INDEX);
	LOGX("free tiles: ", TILE_USER_LENGTH);

    SYS_enableInts();


//    XGM_startPlay(music[0]);
	while (TRUE)
	{


		// First we update all the things that have to be updated each frame
        PlayerUpdate();
		// PlayerDrawHUD();
        DrawFPS(0, 0, 0);
//        VDP_showFPS(FIX32(2));

		// WarpUpdate(&player.position);
		WarpUpdate(&playerBounds);


        CameraUpdate();
		DecorUpdate();

		// Then we update sprites and after that we tell the Mega Drive that we have finished processing all the frame data
		SPR_update();

//		waitTick (50);

		SYS_doVBlankProcess();

	}

	return 0;
}


void DrawFPS(s16 x, s16 y, u16 asFloat)
{
    char str[16];

    if (asFloat)
    {
        fix32ToStr(SYS_getFPSAsFloat(), str, 1);
        VDP_clearText(x, y, 5);
    }
    else
    {
        uintToStr(SYS_getFPS(), str, 1);
        VDP_clearText(x, y, 2);
    }

    VDP_drawText(str, x, y);
}


