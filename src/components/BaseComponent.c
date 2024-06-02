#include <BaseComponent.h>

void BaseComponentSetBounds(BaseComponent *component, Vector2 bounds)
{
	if (!Vector2Equals(component->bounds, bounds))
		component->bounds = bounds;
}

Vector2 BaseComponentGetPosition(BaseComponent *component)
{
	Vector2 position = Vector2Add(component->position, component->bounds);
	
	if (component->styles.styles.center)
	{/*TODO: maybe in the future check what styles is on
 *      and then check if it has center on (currently just checking on the base styles)
 *      */
		if (Vector2Equals(component->bounds, VEC2_NULL))
		{
			position.x = GetScreenWidth() / 2 - component->size.x / 2;
			position.y = position.y;
		} else
		{
			position.x = component->bounds.x + component->size.x / 2;
			position.y = position.y;
		}
	}
	
	return position;
}

BaseComponentInfo BaseComponentGetInfo(BaseComponent *component)
{
	BaseComponentInfo info = {
		.position = BaseComponentGetPosition(component),
		.isHovering = false,
		.isActive = false,
		.isPressed = false,
		.styles = &component->styles.styles
	};
	
	if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){SPREAD_VEC2(info.position), SPREAD_VEC2(component->size)}))
	{
		info.isHovering = true;
		info.styles = &component->styles.hoverStyles;
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			info.isActive = true;
			info.styles = &component->styles.activeStyles;
		}
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			info.isPressed = true;
	}
	return info;
}

BaseComponent createBaseComponent(Vector2 position, Vector2 size, Styles styles)
{
	BaseComponent component = {
		.position = position,
		.size = size,
		.styles = styles,
		.bounds = VEC2_NULL,
		.transparent = false
	};

	return component;
}

void    BaseComponentSetTransparent(BaseComponent *component, bool transparent)
{
	component->transparent = transparent;
}