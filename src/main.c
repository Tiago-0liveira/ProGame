#include <game.h>
#include <screenManager.h>

int main(void)
{
	InitWindow(WIN_WIDTH, WIN_HEIGHT, GAME_NAME);
	SetTargetFPS(FPS);

	ScreenManager *screenManager = createScreenManager();
	registerAllScreens(screenManager);
	changeScreen(screenManager, MAIN_MENU_SCREEN);

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

