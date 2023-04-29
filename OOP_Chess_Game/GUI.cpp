#include "GUI.h"

GUI::GUI() {
}

GUI::~GUI() {
}

void GUI::renderButton() {
}

void GUI::render() {
}

TypeGUI GUI::getTypeGUI() const {
	return TypeGUI();
}

TypeGUI MenuGUI::getTypeGUI() const {
	return TypeGUI::MENU;
}

MenuGUI::MenuGUI() {
}

MenuGUI::~MenuGUI() {
}

void MenuGUI::init() {
}

void MenuGUI::render() {
}

SDL_Rect MenuGUI::getRectOfBtnVsCom() {
	return SDL_Rect();
}

SDL_Rect MenuGUI::getRectOfBtnVsPlayer() {
	return SDL_Rect();
}

SDL_Rect MenuGUI::getRectOfBtnVolumeOption() {
	return SDL_Rect();
}

SDL_Rect MenuGUI::getRectOfBtnReplayRecentGame() {
	return SDL_Rect();
}

SDL_Rect MenuGUI::getRectOfBtnExit() {
	return SDL_Rect();
}

ModeOptionGUI::ModeOptionGUI() {
}

ModeOptionGUI::~ModeOptionGUI() {
}

void ModeOptionGUI::init() {
}

void ModeOptionGUI::render() {
}

TypeGUI ModeOptionGUI::getTypeGUI() const {
	return TypeGUI();
}

SDL_Rect ModeOptionGUI::getRectOfBtnEasy() {
	return SDL_Rect();
}

SDL_Rect ModeOptionGUI::getRectOfBtnHard() {
	return SDL_Rect();
}

SDL_Rect ModeOptionGUI::getRectOfBtnBackToMenu() {
	return SDL_Rect();
}

VolumeOptionGUI::VolumeOptionGUI() {
}

VolumeOptionGUI::~VolumeOptionGUI() {
}

void VolumeOptionGUI::init() {
}

void VolumeOptionGUI::render() {
}

TypeGUI VolumeOptionGUI::getTypeGUI() const {
	return TypeGUI();
}

Slider* VolumeOptionGUI::getSliderThemeMusic() {
	return nullptr;
}

Slider* VolumeOptionGUI::getSliderEventMusic() {
	return nullptr;
}

SDL_Rect VolumeOptionGUI::getRectOfBtnBackToMenu() {
	return SDL_Rect();
}

GamePlayGUI::GamePlayGUI() {
}

GamePlayGUI::~GamePlayGUI() {
}

void GamePlayGUI::init() {
}

void GamePlayGUI::render() {
}

TypeGUI GamePlayGUI::getTypeGUI() const {
	return TypeGUI();
}

SDL_Rect GamePlayGUI::getRectOfBtnUndo() {
	return SDL_Rect();
}

SDL_Rect GamePlayGUI::getRectOfBtnSetting() {
	return SDL_Rect();
}

SDL_Rect GamePlayGUI::getRectOfBtnRedo() {
	return SDL_Rect();
}

MatchResultGUI::MatchResultGUI() {
}

MatchResultGUI::~MatchResultGUI() {
}

void MatchResultGUI::init() {
}

void MatchResultGUI::render() {
}

TypeGUI MatchResultGUI::getTypeGUI() const {
	return TypeGUI();
}

void MatchResultGUI::setText(const TextObject& text) {
}

PromotionNoticeGUI::PromotionNoticeGUI(int idOfPromotionPiece) {
}

PromotionNoticeGUI::~PromotionNoticeGUI() {
}

void PromotionNoticeGUI::init() {
}

void PromotionNoticeGUI::render() {
}

TypeGUI PromotionNoticeGUI::getTypeGUI() const {
	return TypeGUI();
}

int PromotionNoticeGUI::getIdOfPromotionPiece() const {
	return 0;
}

SDL_Rect PromotionNoticeGUI::getRectOfBtnQueen() {
	return SDL_Rect();
}

SDL_Rect PromotionNoticeGUI::getRectOfBtnBishop() {
	return SDL_Rect();
}

SettingGUI::SettingGUI() {
}

SettingGUI::~SettingGUI() {
}

void SettingGUI::init() {
}

void SettingGUI::render() {
}

TypeGUI SettingGUI::getTypeGUI() const {
	return TypeGUI();
}

SDL_Rect SettingGUI::getRectOfBtnContinue() {
	return SDL_Rect();
}
