#pragma once
#include "Pieces.h"
#include <vector>
#include <SDL.h>

class Board {
private:
	static Board* _instance;
	static std::vector<std::vector<Piece*>> board;
	SDL_Rect rect;

public:
	Board();
	~Board();
	//static std::vector<Piece*> pieces;
	static const int XBOXES = 8;
	static const int YBOXES = 8;

	static Board* getInstance();

	void setRectangle();
	SDL_Rect getRectangle();
	static void updateBoard();
	static Piece* getPieceAt(const Coordinate& c);
	static void resetPieces(); // call when init GamePlayGUI
};

//Board* Board::_instance = nullptr;
//std::vector<Piece*> Board::pieces;

