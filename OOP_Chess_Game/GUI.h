#pragma once
#include <SDL.h>
#include "Button.h"

enum class TypeGUI { MENU, MODE_OPTION, VOLUME_OPTION, REPLAY_RECENT_GAME, GAME_PLAY, RESULT_NOTICE, PROMOTION_NOTICE, SETTINGS};

class GUI {
protected:
	SDL_Rect* rect;
public:
	GUI();
	virtual ~GUI();

	virtual TypeGUI getTypeGUI() const;
	virtual void render();
	void renderButton();
};

class MenuGUI : public GUI {
private:
	static Button btnVsCom;
	static Button btnVsPlayer;
	static Button btnVolumeOption;
	static Button btnReplayRecentGame;
	static Button btnExit;

public:
	MenuGUI();
	virtual ~MenuGUI();

	void init();
	void render();
	TypeGUI getTypeGUI() const;

	static SDL_Rect getRectOfBtnVsCom();
	static SDL_Rect getRectOfBtnVsPlayer();
	static SDL_Rect getRectOfBtnVolumeOption();
	static SDL_Rect getRectOfBtnReplayRecentGame();
	static SDL_Rect getRectOfBtnExit();
};

// TODO: use full parameter constructor
//Button MenuGUI::btnVsCom;
//Button MenuGUI::btnVsPlayer;
//Button MenuGUI::btnVolumeOption;
//Button MenuGUI::btnReplayRecentGame;
//Button MenuGUI::btnExit;

class ModeOptionGUI : public GUI {
private:
	static Button btnEasy;
	static Button btnHard;
	static Button btnBackToMenu;
public:
	ModeOptionGUI();
	virtual ~ModeOptionGUI();

	void init();
	void render();
	TypeGUI getTypeGUI() const;

	static SDL_Rect getRectOfBtnEasy();
	static SDL_Rect getRectOfBtnHard();
	static SDL_Rect getRectOfBtnBackToMenu();
};

// TODO: use full parameter constructor
//Button ModeOptionGUI::btnEasy;
//Button ModeOptionGUI::btnHard;
//Button ModeOptionGUI::btnBackToMenu;

class VolumeOptionGUI : public GUI {
private:
	static Slider sliderThemeMusic;
	static Slider sliderEventMusic;
	static Button btnBackToMenu;
public:
	VolumeOptionGUI();
	virtual ~VolumeOptionGUI();

	void init();
	void render();
	TypeGUI getTypeGUI() const;

	static Slider* getSliderThemeMusic();
	static Slider* getSliderEventMusic();
	static SDL_Rect getRectOfBtnBackToMenu();
};

// TODO: use full parameter constructor
//Slider VolumeOptionGUI::sliderThemeMusic;
//Slider VolumeOptionGUI::sliderEventMusic;
//Button VolumeOptionGUI::btnBackToMenu;

//TODO: design class
class ReplayGameGUI : public GUI {
};

class GamePlayGUI : public GUI {
private:
	static Button btnSetting;
	static Button btnUndo;
	static Button btnRedo;
public:
	GamePlayGUI();
	virtual ~GamePlayGUI();

	void init();
	void render();
	TypeGUI getTypeGUI() const;

	static SDL_Rect getRectOfBtnSetting();
	static SDL_Rect getRectOfBtnUndo();
	static SDL_Rect getRectOfBtnRedo();
};

// TODO: use full parameter constructor
//Button GamePlayGUI::btnSetting;
//Button GamePlayGUI::btnUndo;
//Button GamePlayGUI::btnRedo;

class MatchResultGUI : public GUI {
private:
	TextObject text;
	static Button btnPlayAgain;
	static Button btnBackToMenu;
public:
	MatchResultGUI();
	virtual ~MatchResultGUI();

	void init();
	void render();
	TypeGUI getTypeGUI() const;
	void setText(const TextObject& text);

	static SDL_Rect getRectOfBtnPlayAgain();
	static SDL_Rect getRectOfBtnBackToMenu();
};

// TODO: use full parameter constructor
//static Button btnPlayAgain;
//static Button btnBackToMenu;

class PromotionNoticeGUI : public GUI {
private:
	int idOfPromotionPiece;
	static Button btnQueen;
	static Button btnBishop;
	static Button btnKnight;
	static Button btnRook;
public:
	PromotionNoticeGUI(int idOfPromotionPiece);
	virtual ~PromotionNoticeGUI();

	void init();
	void render();
	TypeGUI getTypeGUI() const;
	int getIdOfPromotionPiece() const;

	static SDL_Rect getRectOfBtnQueen();
	static SDL_Rect getRectOfBtnBishop();
	static SDL_Rect getRectOfBtnKnight();
	static SDL_Rect getRectOfBtnRook();
};

// TODO: use full parameter constructor
//static Button btnQueen;
//static Button btnBishop;
//static Button btnKnight;
//static Button btnRook;


class SettingGUI : public GUI {
private:
	static Button btnContinue;
	static Button btnVolumeOption;
	static Button btnBackToMenu;
public:
	SettingGUI();
	virtual ~SettingGUI();

	void init();
	void render();
	TypeGUI getTypeGUI() const;

	static SDL_Rect getRectOfBtnContinue();
	static SDL_Rect getRectOfBtnVolumeOption();
	static SDL_Rect getRectOfBtnBackToMenu();
};

//TODO: use full parameter constructor
//static Button btnContinue;
//static Button btnVolumeOption;
//static Button btnBackToMenu;
