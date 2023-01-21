#include "defs.h"
#include "debug.h"
#include "hud.h"
#include "global.h"
#include "sprites.h"

Sprite* hudMask1;
Sprite* hudMask2;

void HUDInit()
{

    hudMask1 = SPR_addSprite(&hud_mask, -127, 0, TILE_ATTR(PAL_PLAYER, TRUE, FALSE, FALSE));
    hudMask2 = SPR_addSprite(&hud_mask, -128, 0, TILE_ATTR(PAL_PLAYER, TRUE, FALSE, FALSE));

    SPR_setVRAMTileIndex(hudMask1, 1);
    SPR_setDepth(hudMask1, -200);
    SPR_setVRAMTileIndex(hudMask2, 2);
    SPR_setDepth(hudMask2, -199);

    SPR_update();
}

void HUDUpdate()
{
    hudTilesIndex = activeLevel.filledTilesId;
    VDP_drawImageEx(WINDOW, &hud_window, TILE_ATTR_FULL(PAL_PLAYER, TRUE, FALSE, FALSE, hudTilesIndex), 0, 0, FALSE, TRUE);
    // VDP_drawImageEx(WINDOW, &healthBar, TILE_ATTR_FULL(PAL_PLAYER, TRUE, FALSE, FALSE, hudTilesIndex), 0, 22, FALSE, TRUE);
    hudTilesIndex += hud_window.tileset->numTile;
//    SYS_doVBlankProcess();
}
