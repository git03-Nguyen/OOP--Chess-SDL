#include "History.h"

History::History() {
}

History::~History() {
}

void History::read() {
}

void History::write() const {
}

void History::setInitalState(const Piece* initalState) {
}

void History::setFinalState(const Piece* finalState) {
}

void History::setCapturedPiece(const Piece* piece) {
}

void History::updateData(int turn) {
}

std::vector<Piece*> History::getData(int turn) {
    return std::vector<Piece*>();
}

int History::getLengthData() {
    return 0;
}
