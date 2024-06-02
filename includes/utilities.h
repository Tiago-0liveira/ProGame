#ifndef UTILITIES_H
#define UTILITIES_H

#include <raylib.h>

#define VEC2_NULL (Vector2){0, 0}
#define INL_VEC2(...) (Vector2){__VA_ARGS__}
#define SPREAD_VEC2(v) v.x, v.y
#define INL_RECT(x,y,w,h) (Rectangle){x, y, w, h}
#define INL_RECT_V2(pos, size) (Rectangle){pos.x, pos.y, size.x, size.y}

#define DEFAULT_BOUNDS (Rectangle){0, 0, WIN_WIDTH, WIN_HEIGHT}

#endif // UTILITIES_H