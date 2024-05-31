#include <Text.h>

Text *createText(char *text, Vector2 position, Color color, int fontSize)
{
	Styles styles = BASE_STYLES;

	setBackground(&styles, color);
	setTextSize(&styles, fontSize);

	return createTextEx(text, position, styles);
}

Text *createTextEx(char *text, Vector2 position, Styles styles)
{
	Text *pText = (Text*)malloc(sizeof(Text));
	if (!pText)
	{
		printf("Error: Could not allocate memory for Text\n");
		exit(EXIT_FAILURE);
	}
	pText->text = text;
	pText->position = position;
	pText->styles = styles;

	return pText;
}

void	drawText(Text *Text)
{
	if (Text->styles.styles.center)
		DrawText(Text->text, 
			GetScreenWidth() / 2 - MeasureText(Text->text, Text->styles.styles.textSize) / 2, 
			Text->position.y, 
			Text->styles.styles.textSize, Text->styles.styles.textColor);
	else
		DrawText(Text->text, SPREAD_VEC2(Text->position), 
			Text->styles.styles.textSize, Text->styles.styles.textColor);
}