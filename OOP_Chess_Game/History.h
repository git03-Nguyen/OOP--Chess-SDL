#pragma once
#include <vector>
#include <string>
#include "Pieces.h"

class History {
private:
	std::vector<std::vector<Piece*>> history; // [0] initialState, [1] finalState, [2] capturedPiece
	Piece* initalState;
	Piece* finalState;
	Piece* capturedPiece;

public:
	History();
	virtual ~History();
	void read();
	void write() const;
	void setInitalState(const Piece* initalState); // allocation and deep copy
	void setFinalState(const Piece* finalState); // allocation and deep copy
	void setCapturedPiece(const Piece* piece); // allocation and deep copy
	void updateData(int turn); // copy to data and set initalState, finalState = null
	std::vector<Piece*> getData(int turn);
	int getLengthData();
};
