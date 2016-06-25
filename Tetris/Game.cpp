#include "Game.h"

Game::Game(int rowCount, int columnCount, int cellSize) : rowCount{rowCount}, columnCount{columnCount}, cellSize{cellSize}
{
	cells = new COLORREF*[rowCount];
	for (int r = 0; r < rowCount; r++) {
		cells[r] = new COLORREF[columnCount];
	}
	ReadPieces();
	Initialize();
}

void Game::Initialize()
{
	for (int r = 0; r < rowCount; r++) {
		for (int c = 0; c < columnCount; c++) {
			cells[r][c] = RGB(0, 0, 0);
		}
	}
	speed = 1;
	isGameOver = false;
	timer = DEFAULT_TIMER_VALUE;
	GeneratePiece();
}

void Game::Update()
{
	background.Update();
	if (isGameOver) {
		return;
	}
	timer -= speed;
	if (timer <= 0) {
		timer = DEFAULT_TIMER_VALUE;
		currentPiece->MoveDown();
		if (HasLanded()) {
			PlacePiece();
			GeneratePiece();
		}
	}
}

void Game::Draw(Graphics& g)
{
	for (int r = 0; r < rowCount; r++) {
		for (int c = 0; c < columnCount; c++) {
			auto color = cells[r][c] > 0 ? cells[r][c] : background.GetColor(r, c);
			auto brush = CreateSolidBrush(color);
			g.FillRectangle(c * cellSize, r * cellSize, cellSize, cellSize, brush);
			DeleteObject(brush);
		}
	}

	currentPiece->Draw(g, cellSize, currentColor);

	if (isGameOver) {
		g.DrawString("You lose");
	}
}

void Game::OnKeyPress(char code)
{
	if (isGameOver) {
		return;
	}
	switch (code) {
	case VK_LEFT:
		currentPiece->MoveLeft();
		if (CheckCollisions()) {
			currentPiece->MoveRight();
		}
		break;
	case VK_RIGHT:
		currentPiece->MoveRight();
		if (CheckCollisions()) {
			currentPiece->MoveLeft();
		}
		break;
	case VK_DOWN:
		speed = 5;
		break;
	case VK_UP:
		currentPiece->Rotate();
		if (CheckCollisions()) {
			currentPiece->RotateBack();
		}
		break;
	}
}

void Game::OnKeyUp(char code)
{
	if (code == VK_DOWN) {
		speed = 1;
	}
}

void Game::ReadPieces()
{
	bool shape[PIECE_SIZE * PIECE_SIZE];
	std::ifstream in("pieces.txt");
	for (int i = 0; i < PIECES_TYPES_COUNT; i++) {
		for (int j = 0; j < PIECE_SIZE * PIECE_SIZE; j++) {
			in >> shape[j];
		}
		pieces[i] = new Piece(shape);
	}
	in.close();
}

void Game::GeneratePiece()
{
	currentPiece = pieces[rand() % PIECES_TYPES_COUNT];
	currentColor = colors[rand() % COLORS_COUNT];
	currentPiece->Reset();
	currentPiece->SetOffsetX((columnCount - PIECE_SIZE) / 2);
}

bool Game::HasLanded()
{
	int offsetY = currentPiece->GetOffsetY();
	int offsetX = currentPiece->GetOffsetX();
	for (int x = 0; x < PIECE_SIZE; x++) {
		for (int y = 0; y < PIECE_SIZE; y++) {
			if (currentPiece->GetCell(x, y) && (y + offsetY >= rowCount || cells[y + offsetY][x + offsetX] > 0)) {
				return true;
			}
		}
	}
	return false;
}

void Game::PlacePiece()
{
	int offsetY = currentPiece->GetOffsetY();
	int offsetX = currentPiece->GetOffsetX();
	for (int x = 0; x < PIECE_SIZE; x++) {
		for (int y = 0; y < PIECE_SIZE; y++) {
			if (currentPiece->GetCell(x, y)) {
				if (y + offsetY - 1 <= 0) {
					isGameOver = true;
					return;
				}
				cells[y + offsetY - 1][x + offsetX] = currentColor;
			}
		}
	}
	for (int y = 0; y < PIECE_SIZE; y++) {
		int r = y + offsetY - 1;
		if (r > 0 && r < rowCount && IsRowFilled(r)) {
			ShiftDown(r);
		}
	}
}

bool Game::CheckCollisions()
{
	int offsetY = currentPiece->GetOffsetY();
	int offsetX = currentPiece->GetOffsetX();
	for (int x = 0; x < PIECE_SIZE; x++) {
		for (int y = 0; y < PIECE_SIZE; y++) {
			int c = x + offsetX;
			int r = y + offsetY;
			if (currentPiece->GetCell(x, y) && (c < 0 || c >= columnCount || cells[r][c] > 0)) {
				return true;
			}
		}
	}
	return false;
}

void Game::ShiftDown(int r)
{
	for (int i = r - 1; i >= 0; i--) {
		for (int j = 0; j < columnCount; j++) {
			cells[i + 1][j] = cells[i][j];
		}
	}
	for (int j = 0; j < columnCount; j++) {
		cells[0][j] = 0;
	}
}

bool Game::IsRowFilled(int r)
{
	for (int c = 0; c < columnCount; c++) {
		if (cells[r][c] == 0) {
			return false;
		}
	}
	return true;
}

Game::~Game()
{
	for (int i = 0; i < PIECES_TYPES_COUNT; i++) {
		delete pieces[i];
	}
	for (int r = 0; r < rowCount; r++) {
		delete[] cells[r];
	}
	delete[] cells;
}
