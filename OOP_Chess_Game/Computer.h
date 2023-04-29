#pragma once
#include "Board.h"

enum class Mode { EASY, HARD };

class Computer {
private:
	Mode mode;
public:
	Computer();
	// don't need destructor

	void setMode(Mode mode);
	void playWithEasyMode();
	void playWithHardMode();
};
