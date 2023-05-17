#include "History.h"

History::History() {
    initialState = nullptr;
    finalState = nullptr;
    capturedPiece = nullptr;
}

History::~History() {
    clear();
    initialState = nullptr;
    finalState = nullptr;
    capturedPiece = nullptr;
}

void History::read() {
}

void History::write() const {
}

void History::setInitalState(const Piece* initialState) {
    if (!initialState) {
        this->initialState = nullptr;
        return;
    }
 
    this->initialState = initialState->clone();
}

void History::setFinalState(const Piece* finalState) {
    if (!finalState) {
        this->finalState = nullptr;
        return;
    }

    this->finalState = finalState->clone();
}

void History::setCapturedPiece(const Piece* capturedPiece) {
    if (!capturedPiece) {
        this->capturedPiece = nullptr;
        return;
    }

    this->capturedPiece = capturedPiece->clone();
}

void History::updateData(int turn) {
    // bug logic
    /*
    if (turn < history.size()) {
        for (int i = 0; i < 3; i++) {
            if (history[turn][i]) {
                delete history[turn][i];
                history[turn][i] = nullptr;
            }
        }
        history[turn] = std::vector<Piece*>{ initialState, finalState, capturedPiece };
    }
    else history.push_back(std::vector<Piece*>{ initialState, finalState, capturedPiece });
    */
    
    // fix bug
    for (int i = turn; i < history.size(); i++) {
        for (int j = 0; j < 3; j++) {
            if (history[i][j]) {
                delete history[i][j];
                history[i][j] = nullptr;
            }
        }
    }
    if (turn < history.size()) history.erase(history.begin() + turn, history.end());
    history.push_back(std::vector<Piece*>{ initialState, finalState, capturedPiece });
}

std::vector<Piece*> History::getData(int turn) {
    return history[turn];
}

int History::getLengthData() {
    return history.size();
}


void History::clear() {
    for (auto& v : history) {
        for (auto& u : v) {
            if (u) {
                delete u;
                u = nullptr;
            }
        }
    }
    history.clear();
}