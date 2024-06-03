#ifndef TEXT_H
#define TEXT_H

#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <utilities.h>
#include <Styles.h>
#include <BaseComponent.h>

typedef struct s_Text {
	BaseComponent base;
	char	*text;
} Text;

Text	*createText(char *text, Vector2 position, Color color, int fontSize);
Text	*createTextEx(char *text, Vector2 position, Styles styles);
void	drawText(Text *text);

#endif // TEXT_H