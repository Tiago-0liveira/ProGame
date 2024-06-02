#include <screen.h>
#include <screens.h>
#include <utilities.h>

#include <screenManager.h>
#include <Button.h>
#include <Text.h>
#include <Div.h>

typedef struct s_MainMenuScreenData {
	Div				*buttonsDiv;
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
	Styles styles = DEFAULT_STYLES;
	setCenter(&styles, true);
	setBackgroundHover(&styles, styles.styles.background);
	setBackgroundActive(&styles, styles.styles.background);

	mainMenuScreenData->screenManager = (ScreenManager *)screenManager;
	Div *buttonsDiv = createDivEx((Vector2){100, 300}, (Vector2){200, 250}, styles);
	BaseComponentSetTransparent(&buttonsDiv->base, true);
	
	Styles buttonStyles = DEFAULT_STYLES;
	setCenter(&buttonStyles, true);
	Button *PlayButton = createButtonEx("Play", (Vector2){0, 0}, BUTTON_BASE_SIZE, buttonStyles, PlayButtonClick, mainMenuScreenData);
	Button *OptionsButton = createButtonEx("Options", (Vector2){0, 100}, BUTTON_BASE_SIZE, buttonStyles, OptionsButtonClick, mainMenuScreenData);
	Button *ExitButton = createButtonEx("Exit", (Vector2){0, 200}, BUTTON_BASE_SIZE, buttonStyles, ExitButtonClick, mainMenuScreenData);
	
	addChild(buttonsDiv, PlayButton, &PlayButton->base, BUTTON);
	addChild(buttonsDiv, OptionsButton, &OptionsButton->base, BUTTON);
	addChild(buttonsDiv, ExitButton, &ExitButton->base, BUTTON);
	
	mainMenuScreenData->buttonsDiv = buttonsDiv;

	mainMenuScreenData->title = createText("Pro Game", (Vector2){0, 100}, WHITE, 40);
	setCenter(&mainMenuScreenData->title->base.styles, true);
	
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

	drawDiv(mainMenuScreenData->buttonsDiv);
	/*drawButton(mainMenuScreenData->PlayButton);
	drawButton(mainMenuScreenData->OptionsButton);
	drawButton(mainMenuScreenData->ExitButton);*/
}

static void	MainMenuScreenUnload(void *data)
{
	MainMenuScreenData *mainMenuScreenData = (MainMenuScreenData *)data;
	printf("MainMenuScreen Unload\n");
	free(mainMenuScreenData->buttonsDiv);

	free(mainMenuScreenData->title);

	free(mainMenuScreenData);
}