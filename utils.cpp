#include "stdafx.h"
#include "utils.h"

namespace TTYONE_UTIL
{
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}

	float getAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float distance = sqrtf(x * x + y * y);

		float angle = acosf(x / distance);

		if (y2 > y1)
		{
			// 360도에서 계산된 각도를 뺀다
			angle = PI2 - angle;
			// 혹시 각도가 360도를 넘어갈경우 360도 뺀다
			if (angle >= PI2) angle -= PI2;
		}

		return angle;
	}
}