#include "physicsUtilities.h"

float ConvertPixelToMeter(float pixel)
{
	return pixel * PIXEL_TO_METER / SCALING;
}

float ConvertMeterToPixel(float meter)
{
	return meter * METER_TO_PIXEL * SCALING;
}
