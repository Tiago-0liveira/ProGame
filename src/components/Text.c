#include <Text.h>

Text *createText(char *text, Vector2 position, Color color, int fontSize)
{
	Styles styles = DEFAULT_STYLES;

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
	pText->base = createBaseComponent(position, VEC2_NULL, styles);
	return pText;
}

Vector2 getTextPosition(Text *text)
{
	/* TODO: Needs to take in count the text measure */
	return text->base.position;
}

void	drawText(Text *Text)
{
	BaseComponentInfo info = BaseComponentGetInfo(&Text->base);
	//TODO: Calculate text position
	//info.position = getTextPosition(Text);
	DrawText(Text->text, SPREAD_VEC2(info.position), info.styles->textSize, info.styles->textColor);
	/*if (Text->styles.styles.center)
		DrawText(Text->text, 
			GetScreenWidth() / 2 - MeasureText(Text->text, Text->styles.styles.textSize) / 2, 
			Text->position.y, 
			Text->styles.styles.textSize, Text->styles.styles.textColor);
	else
		DrawText(Text->text, SPREAD_VEC2(Text->position), 
			Text->styles.styles.textSize, Text->styles.styles.textColor);*/
}