#include "Board.h"

// TODO: check try catch
//Board* Board::getInstance() {
//	if (_instance) return _instance;
//	return _instance = new Board();
//}

Board::Board() {
}

Board::~Board() {
}

Board* Board::getInstance() {
    return nullptr;
}

void Board::setRectangle() {
}

SDL_Rect Board::getRectangle() {
    return SDL_Rect();
}

void Board::updateBoard() {
}

Piece* Board::getPieceAt(const Coordinate& c) {
    return nullptr;
}

void Board::resetPieces() {
}
