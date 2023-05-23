#pragma once
#include <iostream>
#include <string>
#include <SDL.h>

#include "SoundManager.h"
#include "GUI.h" // TODO: check
#include "Board.h"
#include "History.h"
#include "Computer.h"
#include "Coordinate.h"
#include "Window.h"

enum class MatchResult { PLAYING, PLAYER1_WIN, PLAYER2_WIN, DRAW };
enum class Opponent { HUMAN, COMPUTER };

class GameManager {
private:
	// control model
	Board* board;
	SoundManager* soundManager;
	Computer* computer;
	History* history;

	// control view
	// TODO: create subGui (display on gui)
	GUI* mainGui;
	GUI* subGui;

	// flags
	bool isRunning;
	Opponent opponent;
	int turn;
	MatchResult result;

public:


	GameManager(const char* title, int xPos, int yPos, int width, int height);
	~GameManager();

	void gameLoop(int fps);

	void handelEvents();

	void render();

	Coordinate getClickedBox(const SDL_Event& e) const;

	void handleClickedPiece(const SDL_Event& e);

	void handleClickedHightlightBox(const SDL_Event& e);

	//void handleDragButtonOfSlider(const SDL_Event& e, Slider* slider);

	bool checkFocus(const SDL_Event& e, const SDL_Rect& rect) const;

	bool checkPromotion(Piece* piece);

	void backToMenu();

	int getValueFromSlider(const SDL_Rect* buttonRect, const SDL_Rect* trackerRect);

	void undo();

	void redo();

	MatchState checkWinner();
};


