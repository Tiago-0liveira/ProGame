#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <stdlib.h>
#include <stdbool.h>
#include <screen.h>

typedef enum e_ScreenType {
	MAIN_MENU_SCREEN,
	OPTIONS_SCREEN,
	GAMEPLAY_SCREEN,
	TEST_SCREEN,
	SCREEN_NUM
}	ScreenType;

typedef struct s_ScreenManager {
	Screen *currentScreen;
	Screen *screens[SCREEN_NUM];
	bool	keepRunning;
}	ScreenManager;

ScreenManager	*createScreenManager(void);
void			changeScreen(ScreenManager *screenManager, ScreenType screenType);
void			registerScreen(ScreenManager *screenManager, ScreenType screenType, Screen *screen);
void			updateScreen(ScreenManager *screenManager);
void			drawScreen(ScreenManager *screenManager);
void			unloadScreen(ScreenManager *screenManager);
void			unloadAllScreens(ScreenManager *screenManager);

// screenRegistry.c
void	registerAllScreens(ScreenManager *screenManager);
void	registryScreenCleanup(ScreenManager *screenManager);

#endif // SCREENMANAGER_H