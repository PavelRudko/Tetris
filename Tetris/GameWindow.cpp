#include "GameWindow.h"

GameWindow::GameWindow(HINSTANCE instance, char * title, int x, int y, int w, int h)
{
	instance = instance;
	WNDCLASS wndclass = {};
	wndclass.lpfnWndProc = &GlobalMessageProc;
	wndclass.style = CS_VREDRAW | CS_VREDRAW;
	wndclass.hInstance = instance;
	wndclass.lpszClassName = WINDOW_CLASS_NAME;
	!RegisterClass(&wndclass);
	CreateWindow(WINDOW_CLASS_NAME, title, WS_OVERLAPPEDWINDOW, x, y, w, h, NULL, NULL, instance, this);
	game = new Game(20, 15, 20);
}

void GameWindow::Show()
{
	ShowWindow(handle, SW_SHOW);
	UpdateWindow(handle);
}

void GameWindow::RunGame()
{
	SetTimer(handle, GAME_TIMER, 15, NULL);
}

void GameWindow::OnKeyDown(char code)
{
	game->OnKeyPress(code);
}

void GameWindow::OnKeyUp(char code)
{
	game->OnKeyUp(code);
}

void GameWindow::OnRestart()
{
	game->Initialize();
	SetFocus(handle);
}

void GameWindow::OnCreate()
{
	CreateWindow("BUTTON", RESTART, WS_VISIBLE | WS_CHILD, 6, 4, 75, 20, handle, (HMENU)RESTART_BUTTON, instance, NULL);
	graphics = new Graphics(handle, 0, UPPER_MARGIN, 300, 400);
}

void GameWindow::OnTick()
{
	game->Update();
	game->Draw(*graphics);
	RECT r;
	GetClientRect(handle, &r);
	r.top += UPPER_MARGIN;
	InvalidateRect(handle, &r, FALSE);
}

void GameWindow::MessageProc(UINT message, WPARAM w, LPARAM l)
{
	switch (message) {
	case WM_CREATE:
		OnCreate();
		break;
	case WM_COMMAND:
		if (LOWORD(w) == RESTART_BUTTON) {
			OnRestart();
		}
		break;
	case WM_KEYDOWN:
		OnKeyDown(w);
		break;
	case WM_KEYUP:
		OnKeyUp(w);
		break;
	case WM_DESTROY:
		KillTimer(handle, GAME_TIMER);
		PostQuitMessage(0);
		break;
	case WM_TIMER:
		if (w == GAME_TIMER) {
			OnTick();
		}
		break;
	case WM_PAINT:
		graphics->DrawToScreen();
		break;
	}
}

LRESULT CALLBACK GameWindow::GlobalMessageProc(HWND handle, UINT message, WPARAM w, LPARAM l)
{
	GameWindow* window;
	if (message == WM_NCCREATE) {
		auto createStruct = reinterpret_cast<CREATESTRUCT*>(l);
		window = reinterpret_cast<GameWindow*>(createStruct->lpCreateParams);
		SetWindowLongPtr(handle, GWLP_USERDATA, (LONG)window);
		window->handle = handle;
	}
	else {
		window = reinterpret_cast<GameWindow*>(GetWindowLongPtr(handle, GWLP_USERDATA));
	}

	if (window != nullptr) {
		window->MessageProc(message, w, l);
	}

	return DefWindowProc(handle, message, w, l);
}

GameWindow::~GameWindow()
{
	delete graphics;
	delete game;
}