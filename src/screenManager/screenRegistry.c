#include <screenManager.h>
#include <screens.h>

void	registerAllScreens(ScreenManager *screenManager)
{
	registerScreen(screenManager, MAIN_MENU_SCREEN, createMainMenuScreen());
	registerScreen(screenManager, OPTIONS_SCREEN, createOptionsScreen());
	// registerScreen(screenManager, GAMEPLAY_SCREEN, createGameplayScreen());
}

void	registryScreenCleanup(ScreenManager *screenManager)
{
	unloadAllScreens(screenManager);
}