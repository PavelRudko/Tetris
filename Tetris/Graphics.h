#pragma once
#include <windows.h>

class Graphics
{
private:
	HWND handle;
	PAINTSTRUCT ps;
	HDC hdcBuffer;
	int upperMargin, leftMargin, width, height;
	HBITMAP bitmap;
	RECT bounds;
public:
	Graphics(HWND handle, int leftMargin, int upperMargin, int width, int height);
	void DrawToScreen();
	void FillRectangle(int x, int y, int w, int h, HBRUSH brush);
	void FillRectangle(RECT rect, HBRUSH brush);
	void DrawString(const char* str);
	RECT GetBounds();
	~Graphics();
};
