#ifndef TEXT_H
#define TEXT_H

#include "../headers/window.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

extern GLuint textVBO, textVAO;

void displayTexts();
void initFonts(int cWidth, int cHeight);

#endif //TEXT_H
