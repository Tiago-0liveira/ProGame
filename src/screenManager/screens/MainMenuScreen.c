#include <screen.h>
#include <screens.h>
#include <utilities.h>

#include <screenManager.h>
#include <Button.h>
#include <Text.h>

typedef struct s_MainMenuScreenData {
	Button			*PlayButton;
	Button			*OptionsButton;
	Button			*ExitButton;
	Text			*title;
	ScreenManager	*screenManager;
}	MainMenuScreenData;

/* Screen Default functions */
static void	*MainMenuScreenInit(void *screenManager);
static void	MainMenuScreenUpdate(void *data);
static void	MainMenuScreenDraw(void *data);
static void	MainMenuScreenUnload(void *data);

/* Button Callbacks */
static void ExitButtonClick(void *data)
{
	MainMenuScreenData *mainMenuScreenData = (MainMenuScreenData *)data;
	printf("Exit Button Clicked\n");
	mainMenuScreenData->screenManager->keepRunning = false;
}
static void PlayButtonClick(void *data)
{
	(void)data;
	printf("Play Button Clicked\n");
}
static void OptionsButtonClick(void *data)
{
	MainMenuScreenData *mainMenuScreenData = (MainMenuScreenData *)data;
	printf("Options Button Clicked\n");
	changeScreen(mainMenuScreenData->screenManager, OPTIONS_SCREEN);
	printf("OptionsButtonClick:Changed to Options Screen\n");
}

Screen *createMainMenuScreen(void)
{
	Screen *screen = (Screen *)malloc(sizeof(Screen));
	if (screen == NULL)
	{
		printf("Error: Could not allocate memory for MainMenuScreen\n");
		exit(EXIT_FAILURE);
	}

	screen->Init = &MainMenuScreenInit;
	screen->Update = &MainMenuScreenUpdate;
	screen->Draw = &MainMenuScreenDraw;
	screen->Unload = &MainMenuScreenUnload;
	screen->hasInit = false;
	screen->data = NULL;
	return (screen);
}

static void	*MainMenuScreenInit(void *screenManager)
{
	printf("MainMenuScreen Init\n");
	MainMenuScreenData *mainMenuScreenData = (MainMenuScreenData *)malloc(sizeof(MainMenuScreenData));
	if (mainMenuScreenData == NULL)
	{
		printf("Error: Could not allocate memory for MainMenuScreenData\n");
		exit(EXIT_FAILURE);
	}
	Styles styles = BASE_STYLES;
	setBorderHover(&styles, styles.hoverStyles.border, styles.styles.borderWidth * 1.5);
	setCenter(&styles, true);

	mainMenuScreenData->screenManager = (ScreenManager *)screenManager;
	mainMenuScreenData->PlayButton = createButtonEx("Play", (Vector2){100, 300}, BUTTON_BASE_SIZE, styles, PlayButtonClick, mainMenuScreenData);
	mainMenuScreenData->OptionsButton = createButtonEx("Options", (Vector2){100, 400}, BUTTON_BASE_SIZE, styles, OptionsButtonClick, mainMenuScreenData);
	mainMenuScreenData->ExitButton = createButtonEx("Exit", (Vector2){100, 500}, BUTTON_BASE_SIZE, styles, ExitButtonClick, mainMenuScreenData);

	mainMenuScreenData->title = createText("Pro Game", (Vector2){0, 100}, WHITE, 40);
	setCenter(&mainMenuScreenData->title->styles, true);
	
	return mainMenuScreenData;
}

static void	MainMenuScreenUpdate(void *data)
{
	(void)data;
}

static void	MainMenuScreenDraw(void *data)
{
	MainMenuScreenData *mainMenuScreenData = (MainMenuScreenData *)data;
	
	// Gradient Background
	DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){ 0, 121, 241, 150 }, BLACK);
	
	drawText(mainMenuScreenData->title);

	drawButton(mainMenuScreenData->PlayButton);
	drawButton(mainMenuScreenData->OptionsButton);
	drawButton(mainMenuScreenData->ExitButton);
}

static void	MainMenuScreenUnload(void *data)
{
	MainMenuScreenData *mainMenuScreenData = (MainMenuScreenData *)data;
	printf("MainMenuScreen Unload\n");
	free(mainMenuScreenData->PlayButton);
	free(mainMenuScreenData->OptionsButton);
	free(mainMenuScreenData->ExitButton);

	free(mainMenuScreenData->title);

	free(mainMenuScreenData);
}