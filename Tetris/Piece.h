#pragma once
#include "Graphics.h"

#define PIECE_SIZE 4

class Piece
{
private:
	int offsetX, offsetY, rotation;
	bool cells[PIECE_SIZE][PIECE_SIZE];
public:
	Piece(bool* shape);
	void Draw(Graphics& g, int cellSize, COLORREF color);
	bool GetCell(int x, int y);
	int GetOffsetX();
	int GetOffsetY();
	void SetOffsetX(int value);
	void Rotate();
	void RotateBack();
	void Reset();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
};