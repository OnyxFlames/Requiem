#include "Debug_Utils.hpp"

int randInt(int min, int max)
{
	return (rand() % (max - min) + min);
}

float randFloat(float min, float max)
{
	return (rand() / (max - min) + min);
}