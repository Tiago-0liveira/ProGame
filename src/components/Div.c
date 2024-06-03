#include <Div.h>

Div		*createDiv(Vector2 position, Vector2 size)
{
	return createDivEx(position, size, DEFAULT_STYLES);
}
Div		*createDivEx(Vector2 position, Vector2 size, Styles styles)
{
	Div *div = malloc(sizeof(Div));
	if (!div)
	{
		fprintf(stderr, "Error allocating memory for Div");
		exit(EXIT_FAILURE);
	}
	div->base = createBaseComponent(position, size, styles);
	for (int i = 0; i < MAX_CHILDREN; i++)
		div->children[i] = (Child){NULL, EMPTY_CHILD};
	return (div);
}
void	addChild(Div *parent, void *child, BaseComponent *base, childType type)
{
	if (type <= EMPTY_CHILD || type >= CHILD_TYPE_COUNT)
	{
		fprintf(stderr, "Error: Invalid child type %d\n", type);
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < MAX_CHILDREN; i++)
	{
		if (parent->children[i].type == EMPTY_CHILD)
		{
			parent->children[i] = (Child){child, type};
			BaseComponentSetBounds(base, BaseComponentGetPosition(&parent->base));
			return ;
		}
	}
	fprintf(stderr, "Error: Div is full. Try increasing MAX_CHILDREN macro!");
	exit(EXIT_FAILURE);
}

void	drawDiv(Div *div)
{
	BaseComponentInfo info = BaseComponentGetInfo(&div->base);
	if (!div->base.transparent)
		DrawRectangle(SPREAD_VEC2(info.position), SPREAD_VEC2(div->base.size), info.styles->background);
	//DrawRectangle(div->position.x, div->position.y, div->size.x, div->size.y, div->styles.styles.background);
	for (int i = 0; i < MAX_CHILDREN; i++)
	{
		Child child = div->children[i];
		if (child.type != EMPTY_CHILD)
		{
			switch(child.type)
			{
				case DIV:
					drawDiv((Div*)child.child);
					break;
				case TEXT:
					drawText((Text*)child.child);
					break;
				case BUTTON:
					drawButton((Button*)child.child);
					break;
				default:
					fprintf(stderr, "Error: Invalid child type %d\n\t(You are probably doing something very wrong with this library!!\n", child.type);
					exit(EXIT_FAILURE);
			}
		}
			
	}
}


/* TODO: define free for each component so it can be called here */
void	freeDiv(Div *div)
{
	(void)div;
}
