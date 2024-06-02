#ifndef BASE_COMPONENT_H
#define BASE_COMPONENT_H

#include <raylib.h>
#include <raymath.h>
#include <Styles.h>
#include <utilities.h>
#include <stdbool.h>

/* Every Custom Component created should have this inside of it
 *  Otherwise it won't work with basic things inside the library
 * */
typedef struct s_BaseComponent {
	Vector2 position;
	Vector2 size;
	Vector2 bounds;/* just x and y starting pos (basically is offset) */
	Styles  styles;
	bool	transparent;
}	BaseComponent;

typedef struct s_BaseComponentInfo {
	Vector2 position;
	bool    isHovering;
	bool    isActive;
	bool    isPressed;
	StyleSheet *styles;
}   BaseComponentInfo;

void                BaseComponentSetBounds(BaseComponent *component, Vector2 bounds);
Vector2             BaseComponentGetPosition(BaseComponent *component);
BaseComponentInfo   BaseComponentGetInfo(BaseComponent *component);
void                BaseComponentSetTransparent(BaseComponent *component, bool transparent);
BaseComponent       createBaseComponent(Vector2 position, Vector2 size, Styles styles);

#endif // BASE_COMPONENT_H