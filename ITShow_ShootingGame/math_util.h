#pragma once

#include <d3dx9math.h>

bool IsCircleCollided(float ax, float ay, float ar, float bx, float by, float br)
{
	float x = bx - ax;
	float y = by - ay;
	float d = sqrt(x * x + y * y);

	if (ar + br < d)
	{
		return false;
	}
	return true;
}