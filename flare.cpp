#include "stc.h"
#define _USE_MATH_DEFINES
#include "math.h"
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
void draw_line(int cx, int cy, double line_length, double angle, int color)
{
	for (int i = 0; i < line_length; i++)
	{
		double degree_angle = angle / 180 * M_PI;
		int x = cx + cos(degree_angle) * i;
		int y = cy + sin(degree_angle) * i;
		SetPixel(x, y, color);
	}
}

void blur_screen()
{
	int buffer[STC_HEIGHT][STC_WIDTH] = { 0 };
	//for (int i = 0; i < STC_HEIGHT; i++)for (int j = 0; j < STC_WIDTH; j++)buffer[i][j] = GetPixel(j, i);
	int surround = 3;
	for (int i = 0; i < STC_HEIGHT; i++)
	{
		for (int j = 0; j < STC_WIDTH; j++)
		{
			int cnt = 0;
			double avg_r = 0, avg_g = 0, avg_b = 0;
			if (i == 99 && j == 160)
			{
				int sfd = 1;
			}

			for (int y = i - surround; y < i + surround + 1; y++)
			{
				for (int x = j - surround; x < j + surround + 1; x++)
				{
					if (i == 99 && j == 160 && y == 100)
					{
						int sfd = 1;
					}

					if (x < 0 || x >= STC_WIDTH || y < 0 || y >= STC_HEIGHT) continue;
					cnt++;
					int color = GetPixel(x, y);
					if (color > 0)
					{
						int s = 111;
					}
					avg_r += extract_r(color);
					avg_g += extract_g(color);
					avg_b += extract_b(color);
				}
			}

			int avg_color = (int(avg_r / cnt) << 16) + (int(avg_g / cnt) << 8) + int(avg_b / cnt);
			buffer[i][j] = avg_color;

		}
	}
	for (int i = 0; i < STC_HEIGHT; i++)for (int j = 0; j < STC_WIDTH; j++)
		SetPixel(j, i, buffer[i][j]);
}

int main(void)
{
	for (int i = 0; i < STC_HEIGHT; i++)for (int j = 0; j < STC_WIDTH; j++)
		SetPixel(j, i, 0);
	//return 0;
	int h = STC_HEIGHT;
	int w = STC_WIDTH;
	int cy = h / 2;  // center y
	int cx = w / 2;  // center x

	int ll = 50;  // line length


	for (int i = 0; i < 1000; i++)
	{
		BeginUpdate();

		for (int j = 0; j < 20; j++)
		{
			double angle = (rand() % 3600) / 10.0;
			angle /= 10; angle *= 10;
			int len = rand() % 100 + 200;
			draw_line(cx, cy, len, angle, 0xffffff);
		}
		blur_screen();
		blur_screen();
		blur_screen();
		blur_screen();
		blur_screen();
		//draw_line(cx, cy, ll, angle, 0xffffff);
		EndUpdate();

	}
	for (int i = 0; i < 10000; i++)
	{
		BeginUpdate();
		blur_screen();
		EndUpdate();

	}
	//for(double i=0;i<360;i+=0.5)

	//

	return 0;
}