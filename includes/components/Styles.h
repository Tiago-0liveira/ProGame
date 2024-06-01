#ifndef STYLES_H
#define STYLES_H

#include <raylib.h>
#include <stddef.h>
#include <stdbool.h>

#define STYLES_BASE_BG_COLOR BLACK
#define STYLES_BASE_TEXT_COLOR RAYWHITE
#define STYLES_BASE_BORDER_COLOR LIGHTGRAY
#define STYLES_BASE_BORDER_WIDTH 2
#define STYLES_BASE_TEXT_SIZE 20
#define STYLES_BASE_ROUND_RADIUS 0.1f
#define STYLES_BASE_ROUND_SEGMENTS 20
#define STYLES_BASE_CENTER_TEXT false

#define STYLES_BASE_HOVER_BG_COLOR (Color){ 60,60,60, 255 }
#define STYLES_BASE_TEXT_HOVER_COLOR BLACK

#define STYLES_BASE_ACTIVE_BG_COLOR (Color){ 30,30,30, 255 }

#define DEFAULT_STYLES (Styles){\
	{/* NORMAL STYLES */\
		STYLES_BASE_BG_COLOR,/* BACKGROUND */\
		STYLES_BASE_TEXT_SIZE, STYLES_BASE_TEXT_COLOR,/* TEXT */\
		STYLES_BASE_BORDER_COLOR, STYLES_BASE_BORDER_WIDTH,/* BORDER */\
		STYLES_BASE_ROUND_RADIUS, \
		STYLES_BASE_CENTER_TEXT \
	},\
	{/* HOVER STYLES */\
		STYLES_BASE_HOVER_BG_COLOR,/* BACKGROUND */\
		STYLES_BASE_TEXT_SIZE, STYLES_BASE_TEXT_COLOR,/* TEXT */\
		STYLES_BASE_BORDER_COLOR, STYLES_BASE_BORDER_WIDTH,/* BORDER */\
		STYLES_BASE_ROUND_RADIUS, \
		STYLES_BASE_CENTER_TEXT \
	},\
	{ \
		STYLES_BASE_ACTIVE_BG_COLOR,/* BACKGROUND */\
		STYLES_BASE_TEXT_SIZE, STYLES_BASE_TEXT_COLOR,/* TEXT */\
		STYLES_BASE_BORDER_COLOR, STYLES_BASE_BORDER_WIDTH,/* BORDER */\
		STYLES_BASE_ROUND_RADIUS, \
		STYLES_BASE_CENTER_TEXT \
	} \
}

typedef struct s_styles
{
	Color	background;

	size_t	textSize;
	Color	textColor;

	Color	border;
	size_t	borderWidth;

	float	roundRadius;

	bool	center;
}	StyleSheet;

typedef struct s_style
{
	StyleSheet styles;
	StyleSheet hoverStyles;
	StyleSheet activeStyles;
}	Styles;

	
#define CREATE_STYLE_SETTER_PROTOTYPE_FOR_PROPERTY(baseName, ...)  \
    void baseName(Styles *styles, __VA_ARGS__); \
    void baseName##Hover(Styles *styles, __VA_ARGS__); \
    void baseName##Active(Styles *styles, __VA_ARGS__);

#define ASSIGN_PROPERTY(style, prop) styles->style.prop = prop;

// Macro to help with variadic arguments
#define ASSIGN_PROPERTYS_1(style, _type1, prop1) ASSIGN_PROPERTY(style, prop1)
#define ASSIGN_PROPERTYS_2(style, _type1, prop1, ...) \
    ASSIGN_PROPERTY(style, prop1) \
    ASSIGN_PROPERTYS_1(style, ##__VA_ARGS__)
#define ASSIGN_PROPERTYS_3(style, _type1, prop1, ...) \
    ASSIGN_PROPERTY(style, prop1) \
    ASSIGN_PROPERTYS_2(style, ##__VA_ARGS__)
#define ASSIGN_PROPERTYS_4(style, _type1, prop1, ...) \
    ASSIGN_PROPERTY(style, prop1) \
    ASSIGN_PROPERTYS_3(style, ##__VA_ARGS__)

// Macro to choose the correct helper based on number of arguments
#define GET_MACRO(_1,_2,_3,_4,_5,_6,_7,_8,NAME,...) NAME
#define ASSIGN_PROPERTYS(style, ...) \
    GET_MACRO(__VA_ARGS__, ASSIGN_PROPERTYS_4, "",ASSIGN_PROPERTYS_3,"", ASSIGN_PROPERTYS_2,"", ASSIGN_PROPERTYS_1,"")(style, __VA_ARGS__)

#define JOIN_ARGS_1(type1, name1) type1 name1
#define JOIN_ARGS_2(type1, name1, type2, name2) type1 name1, type2 name2
#define JOIN_ARGS_3(type1, name1, type2, name2, type3, name3) type1 name1, type2 name2, type3 name3
#define JOIN_ARGS_4(type1, name1, type2, name2, type3, name3, type4, name4) type1 name1, type2 name2, type3 name3, type4 name4

#define JOIN_ARGS(...) \
	GET_MACRO(__VA_ARGS__, JOIN_ARGS_4, "", JOIN_ARGS_3,"", JOIN_ARGS_2,"", JOIN_ARGS_1,"")(__VA_ARGS__)

#define CREATE_STYLE_SETTER_IMPLEMENTATION_FOR_PROPERTY(baseName, ...) \
    void baseName(Styles *styles, JOIN_ARGS(__VA_ARGS__)) { \
        ASSIGN_PROPERTYS(styles, __VA_ARGS__) \
    } \
    void baseName##Hover(Styles *styles, JOIN_ARGS(__VA_ARGS__)) { \
        ASSIGN_PROPERTYS(hoverStyles, __VA_ARGS__) \
    } \
    void baseName##Active(Styles *styles, JOIN_ARGS(__VA_ARGS__)) { \
        ASSIGN_PROPERTYS(activeStyles, __VA_ARGS__) \
    }

CREATE_STYLE_SETTER_PROTOTYPE_FOR_PROPERTY(setBackground, Color color);
CREATE_STYLE_SETTER_PROTOTYPE_FOR_PROPERTY(setTextSize, size_t size);
CREATE_STYLE_SETTER_PROTOTYPE_FOR_PROPERTY(setTextColor, Color color);
CREATE_STYLE_SETTER_PROTOTYPE_FOR_PROPERTY(setBorder, Color color, size_t width);
CREATE_STYLE_SETTER_PROTOTYPE_FOR_PROPERTY(setRoundRadius, float radius);
CREATE_STYLE_SETTER_PROTOTYPE_FOR_PROPERTY(setCenter, bool center);


#endif // STYLES_H