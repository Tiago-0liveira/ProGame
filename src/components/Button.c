#include <Button.h>

static void defaultOnClick(void *data)
{
	(void)data;
	printf("Button Clicked\n");
}

Button *createButtonSimple(char *text, Vector2 position, void (*onClick)(void *data), void *data)
{
	return createButtonEx(text, position, 
		BUTTON_BASE_SIZE, BASE_STYLES, 
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
	button->position = position;
	button->size = size;
	button->styles = styles;
	button->onClick = onClick ? onClick : defaultOnClick;
	button->data = data;
	return (button);
}

void	drawButton(Button *button)
{
	StyleSheet styles = button->styles.styles;
	if (button->styles.styles.center)
	{
		button->position.x = GetScreenWidth() / 2 - button->size.x / 2;
	}
	if (CheckCollisionPointRec(GetMousePosition(), INL_RECT_V2(button->position, button->size)))
	{/* On Hover */
		styles = button->styles.hoverStyles;
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			styles = button->styles.activeStyles;
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))/* On Click */
		{
			button->onClick(button->data);
		}
	}
	DrawRectangleRoundedLines(INL_RECT_V2(button->position, button->size), 
		styles.roundRadius, STYLES_BASE_ROUND_SEGMENTS, 
		styles.borderWidth, styles.border);

	DrawRectangleRounded(INL_RECT_V2(button->position, button->size), styles.roundRadius, STYLES_BASE_ROUND_SEGMENTS, styles.background);
	DrawText(button->text, button->position.x + button->size.x / 2 - MeasureText(button->text, 20) / 2, button->position.y + button->size.y / 2 - 10, 20, styles.textColor);
}
