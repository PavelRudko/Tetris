#include "Piece.h"

Piece::Piece(bool* shape)
{
	for (int y = 0; y < PIECE_SIZE; y++) {
		for (int x = 0; x < PIECE_SIZE; x++) {
			cells[y][x] = shape[y * PIECE_SIZE + x];
		}
	}
	Reset();
}

void Piece::Draw(Graphics & g, int cellSize, COLORREF color)
{
	auto brush = CreateSolidBrush(color);
	for (int x = 0; x < PIECE_SIZE; x++) {
		for (int y = 0; y < PIECE_SIZE; y++) {
			if (GetCell(x, y)) {
				g.FillRectangle((x + offsetX) * cellSize, (y + offsetY) * cellSize, cellSize, cellSize, brush);
			}
		}
	}
	DeleteObject(brush);
}

bool Piece::GetCell(int x, int y)
{
	switch (rotation) {
	case 1:
		return cells[PIECE_SIZE - x - 1][y];
	case 2:
		return cells[PIECE_SIZE - y - 1][PIECE_SIZE - x - 1];
	case 3:
		return cells[x][PIECE_SIZE - y - 1];
	}
	return cells[y][x];
}

int Piece::GetOffsetX()
{
	return offsetX;
}

int Piece::GetOffsetY()
{
	return offsetY;
}

void Piece::SetOffsetX(int value)
{
	offsetX = value;
}

void Piece::Rotate()
{
	rotation = (rotation + 1) % 4;
}

void Piece::RotateBack()
{
	if (--rotation < 0) {
		rotation = 3;
	}
}

void Piece::Reset()
{
	offsetY = -1;
	rotation = 0;
}

void Piece::MoveDown()
{
	offsetY++;
}

void Piece::MoveLeft()
{
	offsetX--;
}

void Piece::MoveRight()
{
	offsetX++;
}
