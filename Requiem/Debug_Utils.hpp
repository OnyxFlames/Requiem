#pragma once

#define DEBUG

// EXIT CODES

#define GAME_EXIT_SUCCESS 0
#define GAME_EXIT_FAILURE -1
#define ENGINE_INIT_FAIL -2
#define TEXTURE_LOAD_FAIL -3

#include <random>
#include <ctime>
#include <iostream>

int randInt(int min, int max);

float randFloat(float min, float max);