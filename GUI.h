#pragma once
#include <vector>
#include <String>
#include <SDL.h>
#include "Button.h"
#include "Board.h"
#include "Pieces.h"

enum class TypeGUI { MENU, MODE_OPTION, VOLUME_OPTION, REPLAY_RECENT_GAME, GAME_PLAY, RESULT_NOTICE, PROMOTION_NOTICE, SETTINGS };

class GUI {
protected:
	Image* background;
	bool active;
public:
	GUI();
	virtual ~GUI();
	virtual TypeGUI getTypeGUI() const;
	void renderBackground();
	void clear();
	virtual void render() = 0;
	virtual void destroy() = 0;
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
//	TypeGUI getTypeGUI() const;
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
//	TypeGUI getTypeGUI() const;
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
//	TypeGUI getTypeGUI() const;
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
	Piece* chosenPiece;
	//
	Image* possibleMove;
	Image* board;
	Image* btnSetting;
	Image* btnUndo;
	Image* btnRedo;
	Image* btnQuit;
	//at first, rect all {0,0,0,0}
	Image* btnPromoteQueen;
	Image* btnPromoteRook;
	Image* btnPromoteBishop;
	Image* btnPromoteKnight;
public:
	GamePlayGUI();
	//
	~GamePlayGUI();
	//
	TypeGUI getTypeGUI() const;
	//
	void set();
	void render();
	//
	void initPromotionButtons();	 //call when needed
	void clearPromotionButtons();    //must call after use
	//
	SDL_Rect getRectOfBoard();
	SDL_Rect getRectOfBtnSetting();
	SDL_Rect getRectOfBtnUndo();
	SDL_Rect getRectOfBtnRedo();
	SDL_Rect getRectOfBtnQuit();
	//
	SDL_Rect getRectOfBtnPromoteQueen();
	SDL_Rect getRectOfBtnPromoteRook();
	SDL_Rect getRectOfBtnPromoteBishop();
	SDL_Rect getRectOfBtnPromoteKnight();
	//
	void destroy();
	//
};

// TODO: use full parameter constructor
//Button GamePlayGUI::btnSetting;
//Button GamePlayGUI::btnUndo;
//Button GamePlayGUI::btnRedo;

//class MatchResultGUI : public GUI {
//private:
//	TextObject text;
//	static Button btnPlayAgain;
//	static Button btnBackToMenu;
//public:
//	MatchResultGUI();
//	virtual ~MatchResultGUI();
//
//	void init();
//	void render();
//	TypeGUI getTypeGUI() const;
//	void setText(const TextObject& text);
//
//	static SDL_Rect getRectOfBtnPlayAgain();
//	static SDL_Rect getRectOfBtnBackToMenu();
//};

// TODO: use full parameter constructor
//static Button btnPlayAgain;
//static Button btnBackToMenu;

//class PromotionNoticeGUI : public GUI {
//private:
//	int idOfPromotionPiece;
//	static Button btnQueen;
//	static Button btnBishop;
//	static Button btnKnight;
//	static Button btnRook;
//public:
//	PromotionNoticeGUI(int idOfPromotionPiece);
//	virtual ~PromotionNoticeGUI();
//
//	void init();
//	void render();
//	TypeGUI getTypeGUI() const;
//	int getIdOfPromotionPiece() const;
//
//	static SDL_Rect getRectOfBtnQueen();
//	static SDL_Rect getRectOfBtnBishop();
//	static SDL_Rect getRectOfBtnKnight();
//	static SDL_Rect getRectOfBtnRook();
//};

// TODO: use full parameter constructor
//static Button btnQueen;
//static Button btnBishop;
//static Button btnKnight;
//static Button btnRook;


//class SettingGUI : public GUI {
//private:
//	static Button btnContinue;
//	static Button btnVolumeOption;
//	static Button btnBackToMenu;
//public:
//	SettingGUI();
//	virtual ~SettingGUI();
//
//	void init();
//	void render();
//	TypeGUI getTypeGUI() const;
//
//	static SDL_Rect getRectOfBtnContinue();
//	static SDL_Rect getRectOfBtnVolumeOption();
//	static SDL_Rect getRectOfBtnBackToMenu();
//};

//TODO: use full parameter constructor
//static Button btnContinue;
//static Button btnVolumeOption;
//static Button btnBackToMenu;
