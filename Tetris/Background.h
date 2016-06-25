#pragma once
#include <Windows.h>
#include <math.h>

class Background
{
private:
	float time = 0;
public:
	void Update();
	COLORREF GetColor(int r, int c);
};
