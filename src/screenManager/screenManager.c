#include <screenManager.h>

ScreenManager	*createScreenManager(void)
{
	ScreenManager *screenManager = (ScreenManager *)malloc(sizeof(ScreenManager));

	if (screenManager == NULL)
	{
		printf("Error: Could not allocate memory for ScreenManager\n");
		exit(EXIT_FAILURE);
	}
	screenManager->currentScreen = NULL;
	for (int i = 0; i < SCREEN_NUM; i++)
	{
		screenManager->screens[i] = NULL;
	}
	screenManager->keepRunning = true;
	return (screenManager);
}

void	changeScreen(ScreenManager *screenManager, ScreenType screenType)
{
	screenManager->currentScreen = screenManager->screens[screenType];
	if (screenManager->currentScreen == NULL)
	{
		fprintf(stderr, "Error: Screen %d not registered\n", screenType);
		exit(EXIT_FAILURE);
	}
	printf("Screen changed to %d\n", screenType);
	Screen *screen = screenManager->currentScreen;
	if (screen->hasInit == false)
	{
		printf("Screen Init\n");
		screen->data = screen->Init(screenManager);
		printf("Screen Init Complete, datap:%p\n", screen->data);
		screen->hasInit = true;
	}
}

void	registerScreen(ScreenManager *screenManager, ScreenType screenType, Screen *screen)
{
	if (screenType >= SCREEN_NUM)
	{
		printf("Error: Screen type out of range\n");
		exit(EXIT_FAILURE);
	}
	screenManager->screens[screenType] = screen;
}

void	updateScreen(ScreenManager *screenManager)
{
	if (screenManager->currentScreen == NULL)
	{
		printf("Error: No screen to update\n");
		exit(EXIT_FAILURE);
	}
	Screen *screen = screenManager->currentScreen;
	screen->Update((void*)screen->data);
}

void	drawScreen(ScreenManager *screenManager)
{
	if (screenManager->currentScreen == NULL)
	{
		printf("Error: No screen to draw\n");
		exit(EXIT_FAILURE);
	}
	Screen *screen = screenManager->currentScreen;
	screen->Draw((void*)screen->data);
}

void	unloadScreen(ScreenManager *screenManager)
{
	if (screenManager->currentScreen == NULL)
	{
		printf("Error: No screen to unload\n");
		exit(EXIT_FAILURE);
	}
	Screen *screen = screenManager->currentScreen;
	screen->Unload((void*)screen->data);
}

void	unloadAllScreens(ScreenManager *screenManager)
{
	for (int i = 0; i < SCREEN_NUM; i++)
	{
		if (screenManager->screens[i] != NULL && screenManager->screens[i]->hasInit == true && screenManager->screens[i]->data != NULL)
		{
			screenManager->screens[i]->Unload((void*)screenManager->screens[i]->data);
			free(screenManager->screens[i]);
		}
	}
}