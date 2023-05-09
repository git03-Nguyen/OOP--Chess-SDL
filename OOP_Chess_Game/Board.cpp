#include "Board.h"

//TODO: check try catch
Board* Board::getInstance() {
    if (_instance == nullptr) {
        _instance = new Board();
        return _instance;
    }
    return _instance;
}
void Board::setStartBoard() {
    for (auto& row : piecesOnBoard) {
        for (auto& piece : row) {
            piece = nullptr;
        }
    }
    int index = 0;
    for (int y = 0; y < 2; y++) {
        for (int x = 0; x < 8; x++) {
            piecesOnBoard[x][y] = piecesList[index++];
        }
    }
    for (int y = 6; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            piecesOnBoard[x][y] = piecesList[index++];
        }
    }
    for (auto& piece : piecesList) {
        updateBoard(piece);
    }
}

Board::Board() {
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
    piecesList.push_back(new Rook(Coordinate(7, 0), Color::Black, pathToString(Path::rookBlack)));

    for (int i = 0; i < 8; i++) { 
        piecesList.push_back(new Pawn(Coordinate(i, 6), Color::Black, pathToString(Path::pawnBlack)));
    }

    piecesOnBoard.resize(8);
    for (auto& row : piecesOnBoard) {
        row.resize(8);
    }
    setStartBoard();
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
        delete piecesList[i];
        piecesList[i] = nullptr;
    }
    piecesList.clear();
    delete _instance;
}

Board* Board::getInstance() {
    return _instance;
}

void Board::setRectangle() {
    rect.h = YBOXES;
    rect.w = XBOXES;
}

SDL_Rect Board::getRectangle() {
    return rect;
}

bool Board::movePiece(Piece* piece, Coordinate& newPos) {
    if (piece->getPosition() == newPos) {
        return false;
    }
    if (Piece* destPiece = piecesOnBoard[newPos.getX()][newPos.getY()]) {
        destPiece->setDead(true);
    }
    piecesOnBoard[piece->getPosition().getX()][piece->getPosition().getY()] = nullptr;
    piece->setPosition(newPos);
    piecesOnBoard[piece->getPosition().getX()][piece->getPosition().getY()] = piece;
    for (auto& p : piecesList) {
        updateBoard(piece);
    }
    return true;
}


void Board::updateBoard(Piece* piece) {
    piece->tableMove.clear();
    if (piece->getDead()) {
        return;
    }
    if (piece->getType() == PieceType::Pawn) {
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                Piece* destPiece = piecesOnBoard[x][y];

                if (!destPiece || destPiece->getColor() != piece->getColor()) {
                    piece->tableMove.push_back(x);
                    piece->tableMove.push_back(y);
                }
            }
        }
    }
}

Piece* Board::getPieceAt(const Coordinate& c) {
    return piecesOnBoard[c.getX()][c.getY()];
}

void Board::resetPieces() {
    for (auto& row : piecesOnBoard) {
        for (auto& piece : row) {
            if (piece) delete piece;
            piece = nullptr;
        }
    }
    for (int i = 0; i < 8; i++) {
        if (piecesList[i]->getType() == PieceType::King) {
            piecesList[i] = new King(Coordinate(i, 0), Color::White, pathToString(Path::kingWhite));
        }
        else {
            piecesList[i]->setPosition(Coordinate(i, 0));
            piecesList[i]->setDead(false);
        }
    }
    for (int i = 8; i < 16; i++) {
        piecesList[i] = new Pawn(Coordinate(i - 8, 1), Color::White, pathToString(Path::pawnWhite));
    }
    for (int i = 16; i < 24; i++) {
        if (piecesList[i]->getType() == PieceType::King) {
            piecesList[i] = new King(Coordinate(i, 0), Color::Black, pathToString(Path::kingBlack));
        }
        else {
            piecesList[i]->setPosition(Coordinate(i - 16, 0));
            piecesList[i]->setDead(false);
        }
    }
    for (int i = 24; i < 32; i++) {
        piecesList[i] = new Pawn(Coordinate(i - 24, 1), Color::Black, pathToString(Path::pawnBlack));
    }
    setStartBoard();
}
