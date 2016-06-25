#pragma once
#include "Graphics.h"
#include "Piece.h"
#include "Background.h"
#include <fstream>

#define DEFAULT_TIMER_VALUE 15
#define PIECES_TYPES_COUNT 7
#define PIECES_FILENAME "pieces.txt"
#define COLORS_COUNT 5

class Game 
{
private:
	bool isGameOver;
	COLORREF colors[COLORS_COUNT] = { RGB(255, 50, 255), RGB(255, 255, 50), RGB(50, 255, 50), RGB(50, 50, 255), RGB(50, 255, 255) };
	int rowCount, columnCount, cellSize, timer, speed;
	COLORREF** cells, currentColor;
	Piece *pieces[PIECES_TYPES_COUNT], *currentPiece;
	Background background;
	void ReadPieces();
	void GeneratePiece();
	bool HasLanded();
	void PlacePiece();
	bool CheckCollisions();
	void ShiftDown(int r);
	bool IsRowFilled(int r);
public:
	Game(int rowCount, int columnCount, int cellSize);
	void Initialize();
	void Update();
	void Draw(Graphics& g);
	void OnKeyPress(char code);
	void OnKeyUp(char code);
	~Game();
};