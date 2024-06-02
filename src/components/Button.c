#include <Button.h>

static void defaultOnClick(void *data)
{
	(void)data;
	printf("Button Clicked\n");
}

Button *createButtonSimple(char *text, Vector2 position, void (*onClick)(void *data), void *data)
{
	return createButtonEx(text, position, 
		BUTTON_BASE_SIZE, DEFAULT_STYLES, 
		onClick, data
	);
}

Button *createButtonEx(char *text, Vector2 position,
	Vector2 size, Styles styles,
	void (*onClick)(void *data), void *data)
{
	Button *button = (Button *)malloc(sizeof(Button));
	if (!button)
	{
		printf("Error: Could not allocate memory for Button\n");
		exit(EXIT_FAILURE);
	}
	button->text = text;
	button->base = createBaseComponent(position, size, styles);
	button->onClick = onClick ? onClick : defaultOnClick;
	button->data = data;
	return (button);
}

void	drawButton(Button *button)
{
	BaseComponentInfo info = BaseComponentGetInfo(&button->base);
	if (info.isPressed)
		button->onClick(button->data);
	DrawRectangleRoundedLines(INL_RECT_V2(info.position, button->base.size),
                          info.styles->roundRadius, STYLES_BASE_ROUND_SEGMENTS,
                          info.styles->borderWidth, info.styles->border);
	
	if (!button->base.transparent)
		DrawRectangleRounded(INL_RECT_V2(info.position, button->base.size), info.styles->roundRadius, STYLES_BASE_ROUND_SEGMENTS, info.styles->background);
	DrawText(button->text,
	         info.position.x + button->base.size.x / 2 - (float)MeasureText(button->text, 20) / 2,
	         info.position.y + button->base.size.y / 2 - 10,
	         20, info.styles->textColor);
}

