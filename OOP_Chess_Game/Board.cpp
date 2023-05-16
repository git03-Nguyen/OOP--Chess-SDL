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
        if (!piecesList[i]) {
            delete piecesList[i];
            piecesList[i] = nullptr;
        }
  
    }

    piecesList.push_back(new King(Coordinate(3, 0), Color::White, pathToString(Path::kingWhite)));
    piecesList[0]->setID(0);
    piecesList.push_back(new Queen(Coordinate(4, 0), Color::White, pathToString(Path::queenWhite)));
    piecesList[1]->setID(1);
    piecesList.push_back(new Bishop(Coordinate(2, 0), Color::White, pathToString(Path::bishopWhite)));
    piecesList[2]->setID(2);
    piecesList.push_back(new Bishop(Coordinate(5, 0), Color::White, pathToString(Path::bishopWhite)));
    piecesList[3]->setID(3);
    piecesList.push_back(new Knight(Coordinate(1, 0), Color::White, pathToString(Path::knightWhite)));
    piecesList[4]->setID(4);
    piecesList.push_back(new Knight(Coordinate(6, 0), Color::White, pathToString(Path::knightWhite)));
    piecesList[5]->setID(5);
    piecesList.push_back(new Rook(Coordinate(0, 0), Color::White, pathToString(Path::rookWhite)));
    piecesList[6]->setID(6);
    piecesList.push_back(new Rook(Coordinate(7, 0), Color::White, pathToString(Path::rookWhite)));
    piecesList[7]->setID(7);

    for (int i = 0; i < 8; i++) {
        piecesList.push_back(new Pawn(Coordinate(i, 1), Color::White, pathToString(Path::pawnWhite)));
        piecesList[i + 8]->setID(i + 8);
    }

    piecesList.push_back(new King(Coordinate(3, 7), Color::Black, pathToString(Path::kingBlack)));
    piecesList[16]->setID(16);
    piecesList.push_back(new Queen(Coordinate(4, 7), Color::Black, pathToString(Path::queenBlack)));
    piecesList[17]->setID(17);
    piecesList.push_back(new Bishop(Coordinate(2, 7), Color::Black, pathToString(Path::bishopBlack)));
    piecesList[18]->setID(18);
    piecesList.push_back(new Bishop(Coordinate(5, 7), Color::Black, pathToString(Path::bishopBlack)));
    piecesList[19]->setID(19);
    piecesList.push_back(new Knight(Coordinate(1, 7), Color::Black, pathToString(Path::knightBlack)));
    piecesList[16]->setID(20);
    piecesList.push_back(new Knight(Coordinate(6, 7), Color::Black, pathToString(Path::knightBlack)));
    piecesList[16]->setID(21);
    piecesList.push_back(new Rook(Coordinate(0, 7), Color::Black, pathToString(Path::rookBlack)));
    piecesList[16]->setID(22);
    piecesList.push_back(new Rook(Coordinate(7, 7), Color::Black, pathToString(Path::rookBlack)));
    piecesList[16]->setID(23);

    for (int i = 0; i < 8; i++) {
        piecesList.push_back(new Pawn(Coordinate(i, 6), Color::Black, pathToString(Path::pawnBlack)));
        piecesList[i + 24]->setID(i + 24);
    }
}
