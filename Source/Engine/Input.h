#pragma once
#include <stdio.h>
#include <string>

extern float Pointer_X;
extern float Pointer_Y;

extern float Prev_Pointer_X;
extern float Prev_Pointer_Y;

extern float Pointer_prev_X;
extern float Pointer_prev_Y;

extern float Pointer_X_motion;
extern float Pointer_Y_motion;

void Update_Input();

bool Pointer_Left_pressed();
bool Pointer_Middle_pressed();
bool Pointer_Right_pressed();

bool Pointer_Left_held();
bool Pointer_Middle_held();
bool Pointer_Right_held();

bool Pointer_Left_released();
bool Pointer_Middle_released();
bool Pointer_Right_released();