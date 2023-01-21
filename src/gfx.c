#include <genesis.h>
#include "types.h"
#include "debug.h"
#include "global.h"
#include "player.h"
#include "gfx.h"
#include "entities.h"

void fadeInBlue(u16 fromcol, u16 tocol, const u16 *pal, u16 numframeBlue, u16 numframeGreenRed)
{
    u16 palBlue[64];

    // Mask out non-blue part
    for (u16 i=0; i<(tocol-fromcol)+1; i++)
        palBlue[i] = pal[i] & 0xF00;

    // First fade in blue part, then green and red
    PAL_fadeIn(fromcol, tocol, palBlue, numframeBlue, FALSE);
    PAL_fadeTo(fromcol, tocol, pal, numframeGreenRed, FALSE);
}

void GFX_InitFade(u16 palIndex, u16 numFrame, u16 palSrc[64])
{
    u16 fromCol = palIndex * 16;
    u16 toCol = palIndex * 16 + 15;

    PAL_getColors(fromCol, palSrc, (toCol - fromCol) + 1);
    PAL_initFade(fromCol, toCol, palSrc, palette_black, numFrame);
}

void GFX_FadeOutPalettes(bool isPal0, bool isPal1, bool isPal2, bool isPal3)
{
//    u16 fromCol = 0;
//    u16 toCol = 31;
//    u16 numFrame = 30;
//    u16 palSrc[64];
//
//    PAL_getColors(fromCol, palSrc, (toCol - fromCol) + 1);
//    PAL_initFade(fromCol, toCol, palSrc, palette_black, numFrame);
//
//    fromCol = 48;
//    toCol = 63;
//    PAL_getColors(fromCol, palSrc, (toCol - fromCol) + 1);
//    PAL_initFade(fromCol, toCol, palSrc, palette_black, numFrame);

    u16 numFrame = 30;
    u16 palSrc[64];
    if (isPal0) GFX_InitFade(PAL0, numFrame, palSrc);
    if (isPal1) GFX_InitFade(PAL1, numFrame, palSrc);
    if (isPal2) GFX_InitFade(PAL2, numFrame, palSrc);
    if (isPal3) GFX_InitFade(PAL3, numFrame, palSrc);

    while (PAL_doFadeStep())
    {
        SYS_doVBlankProcess();
    };
}

void GFX_FadeOutScreen()
{
    u16 fromCol = 0;
    u16 toCol = 63;
    u16 numFrame = 15;
//    u16 palSrc[64];

//    SYS_disableInts();
//    PAL_getColors(0, palSrc, 64);
//    PAL_initFade(fromCol, toCol, palSrc, palette_black, numFrame);
//    SYS_enableInts();
//
//    while (PAL_doFadeStep())
//    {
//        SYS_doVBlankProcess();
//    };

    PAL_fadeOut(fromCol, toCol, numFrame, false);

}

void GFX_FadeInScreen()
{
    u16 palette[64];
    memcpy(&palette[0], activeLevel.lvlMap->layer[BG_A].palette->data, 16 * 2);
    memcpy(&palette[16], activeLevel.lvlMap->layer[BG_B].palette->data, 16 * 2);
    memcpy(&palette[32], player.sprite->definition->palette->data, 16 * 2);
    memcpy(&palette[48], spriteDef[LANTERN]->palette->data, 16 * 2);

    PAL_fadeIn(0, (4 * 16) - 1, palette, 8, false);
}

