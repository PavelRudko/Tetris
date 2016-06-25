#include "GameWindow.h"
#include <time.h>

#define TITLE "Tetris"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand(time(NULL));

	GameWindow window(hInstance, TITLE, 200, 150, 316, 469);
	window.Show();
	window.RunGame();

	MSG message;
	while (GetMessage(&message, NULL, 0, 0) > 0) {
		//TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return 0;
}