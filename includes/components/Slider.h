#ifndef SLIDER_H
#define SLIDER_H

#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <stdio.h>

#include <Styles.h>
#include <BaseComponent.h>


typedef struct s_Slider {
	BaseComponent   base;
	float           value;
	float           minValue;
	float           maxValue;
	float   	    step;
} Slider;

Slider *createSlider(Vector2 position, Vector2 size, float defaultValue);
Slider *createSliderEx(Vector2 position, Vector2 size, Styles styles, float defaultValue, float minValue, float maxValue, float step);

float  *getSliderValueAddress(Slider *slider);
void	drawSlider(Slider *slider);


#endif // SLIDER_H