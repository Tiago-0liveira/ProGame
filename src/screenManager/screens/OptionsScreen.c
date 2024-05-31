#include <screen.h>
#include <screens.h>
#include <utilities.h>

#include <screenManager.h>
#include <Button.h>
#include <Text.h>

typedef struct s_OptionsScreenData {
	Text			*title;
	Button			*backButton;
	ScreenManager	*screenManager;
}	OptionsScreenData;

/* Screen Default functions */
static void	*OptionsScreenInit(void *screenManager);
static void	OptionsScreenUpdate(void *data);
static void	OptionsScreenDraw(void *data);
static void	OptionsScreenUnload(void *data);

/* Button Callbacks */
static void BackButtonClick(void *data)
{
	OptionsScreenData *optionsScreenData = (OptionsScreenData *)data;
	changeScreen(optionsScreenData->screenManager, MAIN_MENU_SCREEN);
	printf("BackButtonClick:Changed to Main Menu Screen\n");
}

Screen *createOptionsScreen(void)
{
	Screen *screen = (Screen *)malloc(sizeof(Screen));
	if (screen == NULL)
	{
		printf("Error: Could not allocate memory for OptionsScreen\n");
		exit(EXIT_FAILURE);
	}

	screen->Init = &OptionsScreenInit;
	screen->Update = &OptionsScreenUpdate;
	screen->Draw = &OptionsScreenDraw;
	screen->Unload = &OptionsScreenUnload;
	screen->hasInit = false;
	screen->data = NULL;
	return (screen);
}

static void	*OptionsScreenInit(void *screenManager)
{
	printf("OptionsScreen Init\n");
	OptionsScreenData *optionsScreenData = (OptionsScreenData *)malloc(sizeof(OptionsScreenData));
	if (optionsScreenData == NULL)
	{
		printf("Error: Could not allocate memory for OptionsScreenData\n");
		exit(EXIT_FAILURE);
	}
	optionsScreenData->screenManager = (ScreenManager *)screenManager;

	optionsScreenData->backButton = createButtonSimple("Back", (Vector2){0, 400}, &BackButtonClick, optionsScreenData);
	setCenter(&optionsScreenData->backButton->styles, true);
	optionsScreenData->title = createText("Options", (Vector2){0, 100}, WHITE, 40);
	setCenter(&optionsScreenData->title->styles, true);
	
	return optionsScreenData;
}

static void	OptionsScreenUpdate(void *data)
{
	(void)data;
}

static void	OptionsScreenDraw(void *data)
{
	OptionsScreenData *optionsScreenData = (OptionsScreenData *)data;
	
	// Gradient Background
	DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){ 0, 121, 241, 150 }, BLACK);

	drawText(optionsScreenData->title);
	drawButton(optionsScreenData->backButton);
}

static void	OptionsScreenUnload(void *data)
{
	OptionsScreenData *optionsScreenData = (OptionsScreenData *)data;
	printf("OptionsScreen Unload\n");

	free(optionsScreenData->title);
	free(optionsScreenData->backButton);

	free(optionsScreenData);
}