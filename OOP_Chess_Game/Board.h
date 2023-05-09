#pragma once
#include "Pieces.h"
#include <vector>
#include <SDL.h>

class Board {
private:
	static Board* _instance;
	static std::vector<Piece*> piecesList;
	SDL_Rect rect;
	static void setStartBoard();
public:
	static std::vector<std::vector<Piece*>> piecesOnBoard;

	Board();
	Board(const Board& obj) = delete;
	~Board();
	static const int XBOXES = 8;
	static const int YBOXES = 8;

	static Board* getInstance();

	void setRectangle();
	SDL_Rect getRectangle();
	bool movePiece(Piece* piece, Coordinate& newPos); // move a piece to new position
	static void updateBoard(Piece* piece); // update table after a move
	static Piece* getPieceAt(const Coordinate& c); // call when want to get Piece at specific coordinate
	static void resetPieces(); // call when reinit board
};

//Board* Board::_instance = nullptr;
//std::vector<Piece*> Board::pieces;
