#pragma once
#include <vector>
#include <String>
#include <SDL.h>
#include "Button.h"
#include "Board.h"
#include "Pieces.h"

#define PIECESIZE 60
#define DISPLACE 40
#define WINDOWSIZEX 640
#define WINDOWSIZEY 560
//
#define SUBDISPLACE 175
#define SUBSIZEX WINDOWSIZEX-SUBDISPLACE*2
#define SUBSIZEY WINDOWSIZEY-SUBDISPLACE*2

enum class GUIType { MENU, MODE_OPTION, VOLUME_OPTION, REPLAY_RECENT_GAME, GAME_PLAY, RESULT_NOTICE, PROMOTION_NOTICE, SETTINGS };
enum class MatchState { BLACK_WIN, WHITE_WIN, DRAW, IN_PLAY};

class GUI {
protected:
	Image* background;
	bool active;
public:
	GUI();
	virtual ~GUI();
	virtual GUIType getGUIType() const;
	void renderBackground();
	virtual void render() = 0;
	virtual void destroy() = 0;
	SDL_Rect getGUIRect();
	bool isActive();
	void activate();
	void deactivate();
};
//
//class MenuGUI : public GUI {
//private:
//	static Button btnVsCom;
//	static Button btnVsPlayer;
//	static Button btnVolumeOption;
//	static Button btnReplayRecentGame;
//	static Button btnExit;
//public:
//	MenuGUI();
//	virtual ~MenuGUI();
//
//	void init();
//	void render();
//	GUIType getGUIType() const;
//
//	static SDL_Rect getRectOfBtnVsCom();
//	static SDL_Rect getRectOfBtnVsPlayer();
//	static SDL_Rect getRectOfBtnVolumeOption();
//	static SDL_Rect getRectOfBtnReplayRecentGame();
//	static SDL_Rect getRectOfBtnExit();
//};

// TODO: use full parameter constructor
//Button MenuGUI::btnVsCom;
//Button MenuGUI::btnVsPlayer;
//Button MenuGUI::btnVolumeOption;
//Button MenuGUI::btnReplayRecentGame;
//Button MenuGUI::btnExit;

//class ModeOptionGUI : public GUI {
//private:
//	static Button btnEasy;
//	static Button btnHard;
//	static Button btnBackToMenu;
//public:
//	ModeOptionGUI();
//	virtual ~ModeOptionGUI();
//
//	void init();
//	void render();
//	GUIType getGUIType() const;
//
//	static SDL_Rect getRectOfBtnEasy();
//	static SDL_Rect getRectOfBtnHard();
//	static SDL_Rect getRectOfBtnBackToMenu();
//};

//class VolumeOptionGUI : public GUI {
//private:
//	static Slider sliderThemeMusic;
//	static Slider sliderEventMusic;
//	static Button btnBackToMenu;
//public:
//	VolumeOptionGUI();
//	virtual ~VolumeOptionGUI();
//
//	void init();
//	void render();
//	GUIType getGUIType() const;
//
//	static Slider* getSliderThemeMusic();
//	static Slider* getSliderEventMusic();
//	static SDL_Rect getRectOfBtnBackToMenu();
//};

//class ReplayGameGUI : public GUI {
//};

class GamePlayGUI : public GUI {
protected:
	std::vector<Image*> piece;
	//
	Piece* chosenPiece;
	//
	Image* chosen;
	Image* possibleMove;
	Image* possibleCapture;
	//
	Image* board;
	Image* btnSetting;
	Image* btnUndo;
	Image* btnRedo;
	//
	Image* whiteMove;
	Image* blackMove;
	//
public:
	GamePlayGUI();
	//
	~GamePlayGUI();
	//
	GUIType getGUIType() const;
	//
	void set();
	void render();
	void renderTurn(int turn);
	//
	SDL_Rect getRectOfBoard();
	SDL_Rect getRectOfBtnSetting();
	SDL_Rect getRectOfBtnUndo();
	SDL_Rect getRectOfBtnRedo();
	SDL_Rect getRectOfBtnQuit() {
		return { 0,0,0,0 };
	}
	//
	void destroy();
	//
};

class MatchResultGUI : public GUI {
private:
	Image* result;
	Image* btnPlayAgain;
	Image* btnBackToMenu;
	Image* btnSave;
public:
	MatchResultGUI();
	MatchResultGUI(MatchState ms);
	~MatchResultGUI();

	void render();
	GUIType getGUIType() const;
	void destroy();

	SDL_Rect getRectOfBtnPlayAgain();
	SDL_Rect getRectOfBtnBackToMenu();
	SDL_Rect getRectOfBtnSave();
};

class PromotionGUI : public GUI {
private:
	Image* btnQueen;
	Image* btnBishop;
	Image* btnKnight;
	Image* btnRook;
	Image* up;
public:
	PromotionGUI();
	~PromotionGUI();

	void render();
	GUIType getGUIType() const;
	void destroy();

	SDL_Rect getRectOfBtnQueen();
	SDL_Rect getRectOfBtnBishop();
	SDL_Rect getRectOfBtnKnight();
	SDL_Rect getRectOfBtnRook();
};

class SettingGUI : public GUI {
private:
	Image* symbol;
	Image* btnResume;
	//
	Image* btnMute;
	Image* btnUnMute;
	//
	Image* btnBackToMenu;
	Image* btnSave;
	//
	bool mute;
public:
	SettingGUI();
	~SettingGUI();

	void render();
	GUIType getGUIType() const;
	void destroy();

	SDL_Rect getRectOfBtnResume();
	SDL_Rect getRectOfBtnVolume();
	SDL_Rect getRectOfBtnBackToMenu();
	SDL_Rect getRectOfBtnSave();
};

//TODO: use full parameter constructor
//static Button btnContinue;
//static Button btnVolumeOption;
//static Button btnBackToMenu;
