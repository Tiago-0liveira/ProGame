#include <game.h>
#include <screenManager.h>

#define DEBUG_TEST_SCREEN

int main(void)
{
	InitWindow(WIN_WIDTH, WIN_HEIGHT, GAME_NAME);
	SetTargetFPS(FPS);

	ScreenManager *screenManager = createScreenManager();
	registerAllScreens(screenManager);
	
	// Starting screen
	#ifdef DEBUG_TEST_SCREEN
		changeScreen(screenManager, TEST_SCREEN);
	#else
		changeScreen(screenManager, MAIN_MENU_SCREEN);
	#endif
	
	while (!WindowShouldClose() && screenManager->keepRunning)
	{
		updateScreen(screenManager);
		BeginDrawing();
			ClearBackground(BLACK);
			drawScreen(screenManager);
		EndDrawing();
	}

	CloseWindow();
	registryScreenCleanup(screenManager);
	free(screenManager);

	return 0;
}

