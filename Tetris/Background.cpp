#include "Background.h"

void Background::Update()
{
	time += 0.01f;
}

COLORREF Background::GetColor(int row, int c)
{
	int r = 50 + time * 10 + row * 10;
	return RGB((1 + sin(time)) * (30 + row * 5), (1 + cos(time* 0.5)) * (30 + c * 5), (1 + cos(time * 0.2)) * (30 + c * 5));
}
