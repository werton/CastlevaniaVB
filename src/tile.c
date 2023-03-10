#include "tile.h"

//Used to get the left edge of a tile by inputting the tile position
u16 getTileLeftPosX(u16 x) {
	return (x * 8);
}
//Used to get the right edge of a tile by inputting the tile position
u16 getTileRightPosX(u16 x) {
	return (x * 8) + 16;
}
//Used to get the top edge of a tile by inputting the tile position
u16 getTileTopPosY(u16 y) {
	return (y * 8);
}
//Used to get the bottom edge of a tile by inputting the tile position
u16 getTileBottomPosY(u16 y) {
	return (y * 8) + 16;
}
//Used to get the bounds of a tile by inputting the tile position
AABB_s16 getTileBounds(s16 x, s16 y) {
	return (AABB_s16) {(x * 8), (y * 8), (x * 8) + 16, (y * 8) + 16};
}

//Used to get the tile position out of a pixel position
Vect2D_u16 posToTile(Vect2D_s16 position) {
	return (Vect2D_u16) {(position.x / 8), (position.y / 8)};
}
