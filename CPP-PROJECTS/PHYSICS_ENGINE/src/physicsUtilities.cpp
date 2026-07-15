#include "physicsUtilities.h"

float ConvertPixelToMeter(float pixel)
{
	return pixel * PIXEL_TO_METER;
}

float ConvertMeterToPixel(float meter)
{
	return meter * METER_TO_PIXEL;
}
