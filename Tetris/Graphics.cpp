#include "Graphics.h"

Graphics::Graphics(HWND handle, int leftMargin, int upperMargin, int width, int height) :
	handle { handle },
	upperMargin { upperMargin },
	leftMargin { leftMargin },
	width{ width },
	height{ height }
{
	bounds = { 0, 0, width, height };

	auto hdc = GetDC(handle);
	bitmap = CreateCompatibleBitmap(hdc, width, height);
	hdcBuffer = CreateCompatibleDC(hdc);
	SelectObject(hdcBuffer, bitmap);
	ReleaseDC(handle, hdc);
}

void Graphics::DrawToScreen()
{
	auto hdc = BeginPaint(handle, &ps);
	BitBlt(hdc, leftMargin, upperMargin, width, height, hdcBuffer, 0, 0, SRCCOPY);
	EndPaint(handle, &ps);
}

void Graphics::FillRectangle(int x, int y, int w, int h, HBRUSH brush)
{
	RECT rect = { x, y, x + w, y + h };
	FillRectangle(rect, brush);
}

void Graphics::FillRectangle(RECT rect, HBRUSH brush)
{
	FillRect(hdcBuffer, &rect, brush);
}

void Graphics::DrawString(const char * str)
{
	RECT rect = GetBounds();
	DrawText(hdcBuffer, str, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

RECT Graphics::GetBounds()
{
	return bounds;
}

Graphics::~Graphics()
{
	DeleteDC(hdcBuffer);
	DeleteObject(bitmap);
}


