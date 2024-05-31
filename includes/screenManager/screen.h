#ifndef SCREEN_H
#define SCREEN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_Screen {
	/* screenManager can be casted to ScreenManager* */
	void *(*Init)(void *screenManager);
	void (*Update)(void *data);
	void (*Draw)(void *data);
	void (*Unload)(void *data);
	bool hasInit;
	void *data;
}	Screen;


#endif // SCREEN_H