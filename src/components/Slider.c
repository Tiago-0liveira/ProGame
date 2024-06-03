#include <Slider.h>

Slider *createSlider(Vector2 position, Vector2 size, float defaultValue)
{
	return createSliderEx(position, size, DEFAULT_STYLES, defaultValue, 0, 1, 0.05f);
}

Slider *createSliderEx(Vector2 position, Vector2 size, Styles styles, float defaultValue, float minValue, float maxValue, float step)
{
	Slider *pSlider = (Slider*)malloc(sizeof(Slider));
	if (!pSlider)
	{
		printf("Error: Could not allocate memory for Slider\n");
		exit(EXIT_FAILURE);
	}
	pSlider->base = createBaseComponent(position, size, styles);
	pSlider->value = defaultValue;
	pSlider->minValue = minValue;
	pSlider->maxValue = maxValue;
	pSlider->step = step;
	return pSlider;
}

float  *getSliderValueAddress(Slider *slider)
{
	return &slider->value;
}
void	drawSlider(Slider *slider)
{
	BaseComponentInfo info = BaseComponentGetInfo(&slider->base);
	info.styles = &slider->base.styles.styles;
	
	if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){SPREAD_VEC2(info.position), SPREAD_VEC2(slider->base.size)}))
	{
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			float mousePosRatio = (GetMousePosition().x - info.position.x + 1) / slider->base.size.x;
			
			slider->value = mousePosRatio * (slider->maxValue - slider->minValue) + slider->minValue;
			slider->value = roundf(slider->value / slider->step) * slider->step;
			
			if (slider->value > slider->maxValue) slider->value = slider->maxValue;
			if (slider->value < slider->minValue) slider->value = slider->minValue;
		}
		float mouseWheelMove = GetMouseWheelMove();
		/* When hovering a slider you can change the values with mouseWheel(it will use step) */
		if (mouseWheelMove > 0)
		{
			slider->value += slider->step;
			if (slider->value > slider->maxValue)
				slider->value = slider->maxValue;
		}
		else if (mouseWheelMove < 0)
		{
			slider->value -= slider->step;
			if (slider->value < slider->minValue)
				slider->value = slider->minValue;
		}
	}
	
	Rectangle sliderRec = {SPREAD_VEC2(info.position), SPREAD_VEC2(slider->base.size)};
	DrawRectangleRounded(sliderRec, 0.25f, 20, info.styles->background);
	DrawCircle(SPREAD_VEC2(Vector2Add(info.position, (Vector2){slider->value * slider->base.size.x, slider->base.size.y / 2})), 7, BLUE);
}

