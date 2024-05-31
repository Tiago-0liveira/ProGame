#ifndef TEXT_H
#define TEXT_H

#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <utilities.h>
#include <Styles.h>

typedef struct s_Text {
	char	*text;
	Vector2	position;
	Styles	styles;
} Text;


Text	*createText(char *text, Vector2 position, Color color, int fontSize);
Text	*createTextEx(char *text, Vector2 position, Styles styles);
void	drawText(Text *Text);

#endif // TEXT_H