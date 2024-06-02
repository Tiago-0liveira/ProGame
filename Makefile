NAME = ProGame.exe
CC = @gcc
FLAGS = -Wall -Wextra -Werror -g $(INCLUDES)

# Libraries
LIBS_DIR = .\\libs\\

# RAYLIB
RAYLIB_DIR = raylib-5.0\\
RAYLIB_LIB = $(LIBS_DIR)$(RAYLIB_DIR)\\lib\\libraylib.a
RAYLIB_INCLUDE_DIR = $(LIBS_DIR)$(RAYLIB_DIR)\\include\\

INCLUDES = $(addprefix -I , $(includefolders)) -I $(RAYLIB_INCLUDE_DIR)
LINK_FLAGS = -lm -lpthread -lgdi32 -lwinmm -lopengl32

SRC_FOLDER = src\\
OBJ_DIR = obj\\

# Include Folders
includefolder = includes\\
INCLUDE_SCREEN_MANAGER = screenManager\\
INCLUDE_COMPONENTS = components\\
includefolders = $(includefolder) $(RAYLIB_INCLUDE_DIR) \
	$(addprefix $(includefolder), \
		$(INCLUDE_SCREEN_MANAGER) $(INCLUDE_COMPONENTS) \
	) \

INCLUDE_HEADERS = $(addprefix $(includefolder), \
	game.h utilities.h \
	$(addprefix $(INCLUDE_SCREEN_MANAGER), \
		screenManager.h screen.h screens.h \
	) \
	$(addprefix $(INCLUDE_COMPONENTS), \
		Button.h Div.h Text.h Styles.h BaseComponent.h \
	) \
)

SRC_ROOT_FILES = main.c

FILES = \
	$(SRC_ROOT_FILES) \
	$(addprefix screenManager\\, \
		Screen.c screenManager.c screenRegistry.c \
		$(addprefix screens\\, \
			MainMenuScreen.c OptionsScreen.c \
		) \
	) \
	$(addprefix components\\, \
		Button.c Div.c Text.c Styles.c BaseComponent.c \
	) \


OBJS = $(addprefix $(OBJ_DIR), $(FILES:%.c=%.o))

# Reset
Color_Off='[0m'       # Text Reset

IRed='[0;91m'         # Red
IGreen='[0;92m'       # Green
IYellow='[0;93m'      # Yellow
ICyan='[0;96m'        # Cyan

MSG1 = @echo ${IGreen}"Compiled Successfully ✔︎"${Color_Off}
MSG2 = @echo ${IYellow}"Cleaned Successfully ✔︎"${Color_Off}
MSG3 = @echo ${ICyan}"Cleaned ${NAME} Successfully ✔︎"${Color_Off}

all: $(NAME)

$(NAME): $(OBJS)
	@echo $(RAYLIB_FILES_DIR)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(RAYLIB_LIB) $(LINK_FLAGS)
	$(MSG1)

$(OBJS): $(OBJ_DIR)%.o: $(SRC_FOLDER)%.c $(INCLUDE_HEADERS)
	@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	@$(CC) $(FLAGS) -o $@ -c $<

run: all
	$(NAME)

clean:
	rmdir /s /q $(OBJ_DIR)
	$(MSG2)

fclean: clean
	@del $(NAME)
	$(MSG3)

re: fclean all

