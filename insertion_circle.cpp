#include "stc.h"
#include <assert.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <vector>
int extract_r(int color)
{
	return (color >> 16) & 0xff;
}
int extract_g(int color)
{
	return (color >> 8) & 0xff;
}
int extract_b(int color)
{
	return (color >> 0) & 0xff;
}

void draw_line(vector<int>&v, int y1, int x1, int len, double angle, int color, int pixel_cnt)
{
	for (int i = 0; i < pixel_cnt; i++)
	{
		double x2 = x1 + cos(1.0*angle * M_PI / 180) * len;
		double y2 = y1 + sin(1.0*angle * M_PI / 180) * len;
		double xlen = x2 - x1;
		double xprogress = 1.0*i / pixel_cnt * xlen;
		double ylen = y2 - y1;
		double yprogress = 1.0*i / pixel_cnt * ylen;
		double progress = sqrt(xprogress*xprogress + yprogress * yprogress);
		//SetPixel(1.0*x1 + xprogress, 1.0*y1 + yprogress,color);

		int color1 = 0xffff00;
		int color2 = 0xff00ff;
		double ratio = 1.0 * v[i] / pixel_cnt;
		assert(ratio >= 0 && ratio <= 1.0);
		int r = (1.0 - ratio) * extract_r(color1) + ratio * extract_r(color2);
		int g = (1.0 - ratio) * extract_g(color1) + ratio * extract_g(color2);
		int b = (1.0 - ratio) * extract_b(color1) + ratio * extract_b(color2);

		int new_color = (r << 16) + (g << 8) + b;
		SetPixel(1.0*x1 + xprogress, 1.0*y1 + yprogress, new_color);
	}

}

int main(void)
{
	for (int y = 0; y < STC_HEIGHT; y++)for (int x = 0; x < STC_WIDTH; x++)SetPixel(x, y, 0xff00ff);
	const int n = 100;
	vector<int> v[360*4];
	for(int j=0;j<360*4;j++)
		for (int i = 0; i < n; i++) {
			v[j].push_back(i);
			random_shuffle(v[j].begin(), v[j].end());
		}
	for(int z=0;z<120;z++)
	for (int sorted = 0; sorted < n-1; sorted++)
		for (int j = sorted+1; j >= 1; j--)
		{
			for (int k = 0; k < 360 * 4; k++)
			{
				//if (j < 0 || j >= n) continue;
				//if (j + 1 < 0 || j + 1 >= n) continue;
				if (rand() % 10 != 0) continue;
				if (v[k][j-1] > v[k][j])
				{
					swap(v[k][j-1], v[k][j]);
					int h = STC_HEIGHT;
					int w = STC_WIDTH;
					int center_x = w / 2;
					int center_y = h / 2;
					draw_line(v[k], center_y, center_x, n, (double)k / 4.0, 0xffffff, n);

				}
				//else break;
			}
		}

	return 0;
}