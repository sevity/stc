#include "stc.h"
#include <assert.h>

int extract_r(int color)
{
	return (color >> 16) & 0xff;
}
int extract_g(int color)
{
	return (color >> 8)&0xff;
}
int extract_b(int color)
{
	return (color >> 0) & 0xff;
}



int main(void)
{
	const int h = STC_HEIGHT;
	const int w = STC_WIDTH;

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int color1 = 0xffff00;
			int color2 = 0xff00ff;
			double ratio = 1.0 * x / w;
			assert(ratio >= 0 && ratio <= 1.0);
			int r = (1.0 - ratio) * extract_r(color1) + ratio * extract_r(color2);
			int g = (1.0 - ratio) * extract_g(color1) + ratio * extract_g(color2);
			int b = (1.0 - ratio) * extract_b(color1) + ratio * extract_b(color2);

			int new_color = (r << 16) + (g << 8) + b;
			SetPixel(x, y, new_color);
		}
	}

	return 0;
}