#include "History.h"

History::History() {
    initalState = nullptr;
    finalState = nullptr;
    capturedPiece = nullptr;
}

History::~History() {
}

void History::read() {
}

void History::write() const {
}

void History::setInitalState(const Piece* initalState) {
    PieceType type = initalState->getType();
    switch (type) {
    case PieceType::King: this->initalState = new King();
    case PieceType::Queen: this->initalState = new Queen();
    case PieceType::Bishop: this->initalState = new Bishop();
    case PieceType::Knight: this->initalState = new Knight();
    case PieceType::Rook: this->initalState = new Rook();
    case PieceType::Pawn: this->initalState = new Pawn();
    }

    *this->initalState = *initalState;
}

void History::setFinalState(const Piece* finalState) {
    PieceType type = finalState->getType();
    switch (type) {
    case PieceType::King: this->finalState = new King();
    case PieceType::Queen: this->finalState = new Queen();
    case PieceType::Bishop: this->finalState = new Bishop();
    case PieceType::Knight: this->finalState = new Knight();
    case PieceType::Rook: this->finalState = new Rook();
    case PieceType::Pawn: this->finalState = new Pawn();
    }

    *this->finalState = *finalState;
}

void History::setCapturedPiece(const Piece* piece) {
    PieceType type = capturedPiece->getType();
    switch (type) {
    case PieceType::King: this->capturedPiece = new King();
    case PieceType::Queen: this->capturedPiece = new Queen();
    case PieceType::Bishop: this->capturedPiece = new Bishop();
    case PieceType::Knight: this->capturedPiece = new Knight();
    case PieceType::Rook: this->capturedPiece = new Rook();
    case PieceType::Pawn: this->capturedPiece = new Pawn();
    }

    *this->capturedPiece = *capturedPiece;
}

void History::updateData(int turn) {
    if (turn < history.size()) history[turn] = std::vector<Piece*>{ initalState, finalState, capturedPiece };
    else history.push_back(std::vector<Piece*>{ initalState, finalState, capturedPiece });
}

std::vector<Piece*> History::getData(int turn) {
    return history[turn];
}

int History::getLengthData() {
    return history.size();
}
