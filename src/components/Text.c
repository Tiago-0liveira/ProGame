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

void	drawText(Text *text)
{
	BaseComponentInfo info = BaseComponentGetInfo(&text->base);
	
	text->base.size.x = (float) MeasureText(text->text, (int) info.styles->textSize);
	DrawText(text->text, SPREAD_VEC2(info.position), (int) info.styles->textSize, info.styles->textColor);
}