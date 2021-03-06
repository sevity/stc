#include "stc.h"
#include <assert.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <vector>

int h = STC_HEIGHT;
int w = STC_WIDTH;
int center_x = w / 2;
int center_y = h / 2;
const int n = 100;

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
vector<int> cm;
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
		int color2 = 0xff0000;
		double ratio = 1.0 * v[i] / pixel_cnt;
		assert(ratio >= 0 && ratio <= 1.0);
		int r = (1.0 - ratio) * extract_r(color1) + ratio * extract_r(color2);
		int g = (1.0 - ratio) * extract_g(color1) + ratio * extract_g(color2);
		int b = (1.0 - ratio) * extract_b(color1) + ratio * extract_b(color2);

		int new_color = (r << 16) + (g << 8) + b;
		SetPixel(1.0*x1 + xprogress, 1.0*y1 + yprogress, new_color);
	}

}

int get_color(int color1, int color2, int c, int e)
{
	int i = e-c;
	double ratio = 1.0 * c / e;
	assert(ratio >= 0 && ratio <= 1.0);
	int r = (1.0 - ratio) * extract_r(color1) + ratio * extract_r(color2);
	int g = (1.0 - ratio) * extract_g(color1) + ratio * extract_g(color2);
	int b = (1.0 - ratio) * extract_b(color1) + ratio * extract_b(color2);

	return (r << 16) + (g << 8) + b;
}

vector<int> color_map(int size)
{
	vector<int> v(size, 0);
	assert(v.size() == size);
	int n = size / 3;
	for (int i = 0; i < n; i++)			v[i] = get_color(0xffff00, 0xff00ff, i, n);
	for (int i = n; i < n*2; i++)		v[i] = get_color(0xff00ff, 0xff00ff, i-n, n);
	for (int i = n*2; i < size; i++)	v[i] =  get_color(0xff00ff, 0x000000, i - n*2, n);
	return v;
}
void quick_inplace(vector<int>&v, int s, int e, int k)
{
	if (s >= e) return;
	int pivot = v[s];
	int j = s;
	for (int i = s + 1; i < e; i++)
	{
		if (v[i] < pivot)
		{
			swap(v[i], v[++j]);
		}
	}
	swap(v[j], v[s]);
	if (j > s)
	{
		
		return;
	}

	
	quick_inplace(v, s, j,k);
	quick_inplace(v, j + 1, e,k);
	
}

void shuffle(vector<int> v[])
{

	for (int i = 0; i < 100; i++)
	{
		for (int j = 1; j < 20; j++)
			for (int k = 0; k < 360 * 4; k++)
			{
				int a = rand() % (n - j);
				swap(v[k][a], v[k][a + j]);
				draw_line(v[k], center_y, center_x, n, (double)((k) % (360 * 4)) / 4, 0xffffff, n);
			}
	}
}

int main(void)
{
	
	
	cm = color_map(n);
	vector<int> v[360*4];
	for(int j=0;j<360*4;j++)
		for (int i = 0; i < n; i++) {
			v[j].push_back(i);
			//random_shuffle(v[j].begin(), v[j].end());
		}
	for (int y = 0; y < STC_HEIGHT; y++)for (int x = 0; x < STC_WIDTH; x++)SetPixel(x, y, 0xff0000);
	for (int k = 0; k < 360 * 4; k++)
	{
		draw_line(v[k], center_y, center_x, n, (double)((k) % (360 * 4)) / 4, 0xffffff, n);
	}
	Sleep(5000);

	shuffle(v);

	//Sleep(3000);
	for(int z=0;z<6;z++)
		for (int s = 0; s < n; s++)
		{
			for (int j = 0; j < n; j++)
			{
				for (int k = 0; k < 360 * 4; k++)
				{
					if (j < 0 || j >= n) continue;
					if (j + 1 < 0 || j + 1 >= n) continue;
					if (rand() % 3 == 0) continue;
					if (v[k][j + 1] < v[k][j])
					{
						swap(v[k][j + 1], v[k][j]);
						draw_line(v[k], center_y, center_x, n, (double)((k + s) % (360 * 4)) / 4, 0xffffff, n);
					}
					//else break;
				}
			}
			for (int k = 0; k < 360 * 4; k++)
			{
				draw_line(v[k], center_y, center_x, n, (double)((k + s) % (360 * 4)) / 4, 0xffffff, n);
			}
		}
	shuffle(v);
	//Sleep(3000);
	for (int z = 0; z < 20; z++)
		for (int sorted = 0; sorted < n - 1; sorted++)
		{
			for (int j = sorted + 1; j >= 1; j--)
			{
				for (int k = 0; k < 360 * 4; k++)
				{
					//if (j < 0 || j >= n) continue;
					//if (j + 1 < 0 || j + 1 >= n) continue;
					if (rand() % 2 != 0) continue;
					if (v[k][j - 1] > v[k][j])
					{
						swap(v[k][j - 1], v[k][j]);
						draw_line(v[k], center_y, center_x, n, (double)((k + sorted) % (360 * 4)) / 4, 0xffffff, n);
					}
					//else break;
				}
			}
			for (int k = 0; k < 360 * 4; k++)
			{
				draw_line(v[k], center_y, center_x, n, (double)((k + sorted) % (360 * 4)) / 4, 0xffffff, n);
			}
		}
	shuffle(v);
	//Sleep(3000);
	for (int z = 0; z < 35; z++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < 360 * 4; k++)
			{
				int mi = j;
				for (int i = j + 1; i < n; i++)
				{
					if (i < 0 || i >= n) continue;

					if (v[k][mi] > v[k][i])
					{
						if (rand() % 5 == 0) break;
						mi = i;
						draw_line(v[k], center_y, center_x, n, (double)((k + i) % (360 * 4)) / 4, 0xffffff, n);
					}
				}
				swap(v[k][mi], v[k][j]);
				draw_line(v[k], center_y, center_x, n, (double)((k + j) % (360 * 4)) / 4, 0xffffff, n);
			}
		}
	}
	shuffle(v);
	for (int z = 0; z < 3000; z++)
	{
		for (int k = 0; k < 360 * 4; k++)
		{
			if (rand() % 40 == 0)
				quick_inplace(v[k], 0, n, k);
			draw_line(v[k], center_y, center_x, n, (double)((k + z) % (360 * 4)) / 4, 0xffffff, n);
		}
	}


	return 0;
}