#include "defs.h"
#include "debug.h"
#include "global.h"
#include "player.h"
#include "physics.h"
#include "tile.h"
#include "colmap.h"
#include "pfsm/fsm.h"
#include "sprites.h"

const u16 oneWayPlatformErrorCorrection = 5;

void CollisionsUpdate()
{
    // Create level limits
    AABB_s16 levelLimits = activeLevel.aabb;

    // Easy access to the bounds in global pos
    playerBounds = (AABB_s16) {
            fix32ToInt(player.globalPosition.x) + player.aabb->min.x,
            fix32ToInt(player.globalPosition.y) + player.aabb->min.y,
            fix32ToInt(player.globalPosition.x) + player.aabb->max.x,
            fix32ToInt(player.globalPosition.y) + player.aabb->max.y};

    // We can see these variables as a way to avoid thinking that a ground tile is a wall tile
    // Skin width (yIntVelocity) changes depending on the vertical velocity
    s16 yIntVelocity = fix16ToRoundedInt(player.velocity.fixY);
    s16 playerHeadPos = player.aabb->min.y - yIntVelocity + fix32ToInt(player.globalPosition.y);
    s16 playerFeetPos = player.aabb->max.y - yIntVelocity + fix32ToInt(player.globalPosition.y);

    // Positions in tiles
    Vect2D_u16 minTilePos = posToTile((Vect2D_s16) {playerBounds.min.x, playerBounds.min.y});
    Vect2D_u16 maxTilePos = posToTile((Vect2D_s16) {playerBounds.max.x, playerBounds.max.y});

    // Used to limit how many tiles we have to check for collision
    Vect2D_u16 tileBoundDifference = (Vect2D_u16) {maxTilePos.x - minTilePos.x, maxTilePos.y - minTilePos.y};

    // First we check for horizontal collisions
    for (u16 i = 0; i <= tileBoundDifference.y; i++)
    {
        // Height position constant as a helper
        const u16 y = minTilePos.y + i;

        // Right position constant as a helper
        const u16 rx = maxTilePos.x;

        u16 rTileValue = getTileValue(rx, y);

        // After getting the tile value, we check if that is one of whom we can collide/trigger with horizontally
        if (rTileValue == GROUND_TILE)
        {
            AABB_s16 tileBounds = getTileBounds(rx, y);

            // Before taking that tile as a wall, we have to check if that is within the player hitbox, e.g. not seeing ground as a wall
            if (tileBounds.min.x < levelLimits.max.x && tileBounds.min.y < playerFeetPos &&
                tileBounds.max.y > playerHeadPos)
            {
                levelLimits.max.x = tileBounds.min.x;
                break;
            }
        }

        // Left position constant as a helper
        const u16 lx = minTilePos.x;

        u16 lTileValue = getTileValue(lx, y);

        // We do the same here but for the left side
        if (lTileValue == GROUND_TILE)
        {
            AABB_s16 tileBounds = getTileBounds(lx, y);

            if (tileBounds.max.x > levelLimits.min.x && tileBounds.min.y < playerFeetPos &&
                tileBounds.max.y > playerHeadPos)
            {
                levelLimits.min.x = tileBounds.max.x;
                break;
            }
        }
    }

    // After checking for horizontal positions we can modify the positions if the player is colliding
    if (levelLimits.min.x > playerBounds.min.x)
    {
        PlayerSetPositionX(FIX32(levelLimits.min.x - player.aabb->min.x));
        player.velocity.x = 0;
    }

    if (levelLimits.max.x < playerBounds.max.x)
    {
        PlayerSetPositionX(FIX32(levelLimits.max.x - player.aabb->max.x));
        player.velocity.x = 0;
    }

    // Then, we modify the player position, so we can use them to check for vertical collisions
    playerBounds = (AABB_s16) {
            fix32ToInt(player.globalPosition.x) + player.aabb->min.x,
            fix32ToInt(player.globalPosition.y) + player.aabb->min.y,
            fix32ToInt(player.globalPosition.x) + player.aabb->max.x,
            fix32ToInt(player.globalPosition.y) + player.aabb->max.y};


    // And do the same to the variables that are used to check for them
    minTilePos = posToTile((Vect2D_s16) {playerBounds.min.x, playerBounds.min.y});
    maxTilePos = posToTile((Vect2D_s16) {playerBounds.max.x - 1, playerBounds.max.y});
    tileBoundDifference = (Vect2D_u16) {maxTilePos.x - minTilePos.x, maxTilePos.y - minTilePos.y};

    // To avoid having troubles with player snapping to ground ignoring the upward velocity, we separate top and bottom collisions depending on the velocity
    if (yIntVelocity >= 0)
    {
        for (u16 i = 0; i <= tileBoundDifference.x; i++)
        {
            s16 x = minTilePos.x + i;
            u16 y = maxTilePos.y;
            s16 skipTileY = -1;

            // This is the exact same method that we use for horizontal collisions
            u16 bottomTileValue = getTileValue(x, y);

            if (bottomTileValue == GROUND_TILE || bottomTileValue == ONE_WAY_PLATFORM_TILE)
            {
                if (getTileRightPosX(x) == levelLimits.min.x || getTileLeftPosX(x) == levelLimits.max.x)
                    continue;

                u16 bottomEdgePos = getTileTopPosY(y);

                // The error correction is used to add some extra width pixels in case the player isn't high enough by just some of them
                if (bottomEdgePos < levelLimits.max.y &&
                    bottomEdgePos >= (playerFeetPos - oneWayPlatformErrorCorrection))
                {
                    levelLimits.max.y = bottomEdgePos;

                    if (player.isDownJump == true && bottomTileValue == ONE_WAY_PLATFORM_TILE)
                    {
                        if (skipTileY == -1)
                            skipTileY = y;
                        player.isGrounded = false;
                        levelLimits.max.y = activeLevel.aabb.max.y;
                        return;
                    }
                }

                if (skipTileY != y)
                {
                    player.isDownJump = false;
                    skipTileY = -1;
                }
            }
        }
    }
    else
    {
        for (u16 i = 0; i <= tileBoundDifference.x; i++)
        {
            s16 x = minTilePos.x + i;
            u16 y = minTilePos.y;

            // And the same once again
            u16 topTileValue = getTileValue(x, y);

            if (topTileValue == GROUND_TILE)
            {
                if (getTileRightPosX(x) == levelLimits.min.x || getTileLeftPosX(x) == levelLimits.max.x)
                    continue;

                u16 upperEdgePos = getTileBottomPosY(y);

                if (upperEdgePos < levelLimits.max.y)
                {
                    levelLimits.min.y = upperEdgePos;
                    break;
                }
            }
        }
    }

    // Now we modify the player position and some properties if necessary
    if (levelLimits.min.y > playerBounds.min.y)
    {
        PlayerSetPositionY(FIX32(levelLimits.min.y - player.aabb->min.y));
        player.velocity.fixY = 0;
    }

    if (levelLimits.max.y <= playerBounds.max.y)
    {
        if (levelLimits.max.y == 768)
        {
            kprintf("died");
        }
        else
        {
            TriggerGrounded(&player);
            player.isGrounded = TRUE;
            PlayerSetPositionY(FIX32(levelLimits.max.y - player.aabb->max.y));
            player.velocity.fixY = 0;
        }
    }
    else
    {
        player.isGrounded = FALSE;
    }

    // This time we don't need to update the playerBounds as they will be updated at the beginning of the function the next frame
}


