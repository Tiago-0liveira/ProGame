#ifndef BUTTON_H
#define BUTTON_H

#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <utilities.h>
#include <Styles.h>

#define BUTTON_BASE_SIZE INL_VEC2(100, 50)

typedef struct s_Button {
	char	*text;
	Vector2	position;
	Vector2	size;
	Styles	styles;
	void 	(*onClick)(void *data);
	void	*data;
} Button;

Button *createButtonSimple(char *text, Vector2 position, void (*onClick)(void *data), void *data);
Button *createButtonEx(char *text, Vector2 position,
	Vector2 size, Styles styles,
	void (*onClick)(void *data), void *data);
void	drawButton(Button *button);

#endif // BUTTON_H