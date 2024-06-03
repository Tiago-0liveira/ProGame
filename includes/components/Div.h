#ifndef DIV_H
#define DIV_H

#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <Styles.h>

#include <Text.h>
#include <Button.h>
#include <BaseComponent.h>

#define MAX_CHILDREN 10

typedef enum e_childType {
	EMPTY_CHILD = -1,

	DIV,
	TEXT,
	BUTTON,

	CHILD_TYPE_COUNT
}	childType;

typedef struct s_Child {
	void *child;
	childType type;
}	Child;

typedef struct s_Div {
	BaseComponent base;
	Child	children[MAX_CHILDREN];
} Div;


Div		*createDiv(Vector2 position, Vector2 size);
Div		*createDivEx(Vector2 position, Vector2 size, Styles styles);
void	addChild(Div *parent, void *child, BaseComponent *base, childType type);
void	drawDiv(Div *Div);
void	freeDiv(Div *div);

#endif // DIV_H