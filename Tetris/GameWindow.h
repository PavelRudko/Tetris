#pragma once
#include <Windows.h>
#include "Game.h"
#include "Graphics.h"

#define RESTART_BUTTON 101
#define GAME_TIMER 102
#define RESTART "Restart"
#define WINDOW_CLASS_NAME "GameWindow"
#define UPPER_MARGIN 30

class GameWindow
{
private:
	HINSTANCE instance;
	HWND handle;
	Game *game;
	Graphics *graphics;

	void OnKeyDown(char code);
	void OnKeyUp(char code);
	void OnRestart();
	void OnCreate();
	void OnTick();
	void MessageProc(UINT message, WPARAM w, LPARAM l);
	static LRESULT CALLBACK GlobalMessageProc(HWND handle, UINT message, WPARAM w, LPARAM l);
public:
	GameWindow(HINSTANCE instance, char* title, int x, int y, int w, int h);
	void Show();
	void RunGame();
	~GameWindow();
};