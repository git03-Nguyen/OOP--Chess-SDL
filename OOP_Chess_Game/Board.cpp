#include "Board.h"

// init static attribute
Board* Board::_instance = nullptr;
std::vector<Piece*> Board::piecesList;
std::vector<std::vector<Piece*>> Board::piecesOnBoard;

//TODO: check try catch
Board* Board::getInstance() {
    if (_instance == nullptr) {
        _instance = new Board();
        return _instance;
    }
    return _instance;
}
Board::Board() {
    resetPiecesList();

    piecesOnBoard.resize(8);
    for (auto& row : piecesOnBoard) {
        row.resize(8);
    }
    updateBoard();
    rect = {};
}

Board::~Board() {
    for (auto& row : piecesOnBoard) {
        for (auto& piece : row) {
            if (piece) delete piece;
        }
    }
    piecesOnBoard.clear();
    for (int i = 0; i < piecesList.size(); i++) {
        if (!piecesList[i]) {
            delete piecesList[i];
            piecesList[i] = nullptr;
        }   
    }
    piecesList.clear();
    delete _instance;
}
void Board::updateBoard() {
    for (auto& vpPieces : piecesOnBoard) {
        for (auto& pPiece : vpPieces) pPiece = nullptr;
    }
    for (auto piece : piecesList) {
        if (piece->getDead()) continue;
        Coordinate c = piece->getPosition();
        piecesOnBoard[c.getX()][c.getY()] = piece;
    }
}
Piece* Board::getPieceAt(const Coordinate& c) {
    return piecesOnBoard[c.getX()][c.getY()];
}
void Board::resetPiecesList() {
    for (int i = 0; i < piecesList.size(); i++) {
        if (piecesList[i]) {
            delete piecesList[i];
            piecesList[i] = nullptr;
        }
  
    }

    piecesList.push_back(new King(Coordinate(3, 0), Color::White, pathToString(Path::kingWhite)));
    piecesList.push_back(new Queen(Coordinate(4, 0), Color::White, pathToString(Path::queenWhite)));
    piecesList.push_back(new Bishop(Coordinate(2, 0), Color::White, pathToString(Path::bishopWhite)));
    piecesList.push_back(new Bishop(Coordinate(5, 0), Color::White, pathToString(Path::bishopWhite)));
    piecesList.push_back(new Knight(Coordinate(1, 0), Color::White, pathToString(Path::knightWhite)));
    piecesList.push_back(new Knight(Coordinate(6, 0), Color::White, pathToString(Path::knightWhite)));
    piecesList.push_back(new Rook(Coordinate(0, 0), Color::White, pathToString(Path::rookWhite)));
    piecesList.push_back(new Rook(Coordinate(7, 0), Color::White, pathToString(Path::rookWhite)));

    for (int i = 0; i < 8; i++) {
        piecesList.push_back(new Pawn(Coordinate(i, 1), Color::White, pathToString(Path::pawnWhite)));
    }

    piecesList.push_back(new King(Coordinate(3, 7), Color::Black, pathToString(Path::kingBlack)));
    piecesList.push_back(new Queen(Coordinate(4, 7), Color::Black, pathToString(Path::queenBlack)));
    piecesList.push_back(new Bishop(Coordinate(2, 7), Color::Black, pathToString(Path::bishopBlack)));
    piecesList.push_back(new Bishop(Coordinate(5, 7), Color::Black, pathToString(Path::bishopBlack)));
    piecesList.push_back(new Knight(Coordinate(1, 7), Color::Black, pathToString(Path::knightBlack)));
    piecesList.push_back(new Knight(Coordinate(6, 7), Color::Black, pathToString(Path::knightBlack)));
    piecesList.push_back(new Rook(Coordinate(0, 7), Color::Black, pathToString(Path::rookBlack)));
    piecesList.push_back(new Rook(Coordinate(7, 7), Color::Black, pathToString(Path::rookBlack)));

    for (int i = 0; i < 8; i++) {
        piecesList.push_back(new Pawn(Coordinate(i, 6), Color::Black, pathToString(Path::pawnBlack)));
    }
}
