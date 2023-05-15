#include "GUI.h"
#include <iostream>


GUI::GUI() {
	this->active = true;
	this->background = new Image({ 0,0,1000,600 }, "..\\Assets\\chess\\back.jpg");
}
GUI::~GUI() {
}

void GUI::renderBackground() {
	this->background->renderImage();
}
bool GUI::isActive() {
	return this->active;
}
void GUI::activate() {
	this->active = true;
}
void GUI::deactivate() {
	this->active = false;
}
TypeGUI GUI::getTypeGUI() const {
	return TypeGUI();
}
void GUI::clear() { //clear 
	SDL_RenderClear(Window::renderer);
}
// 
//TypeGUI MenuGUI::getTypeGUI() const {
//	return TypeGUI::MENU;
//}
//
//MenuGUI::MenuGUI() {
//}
//
//MenuGUI::~MenuGUI() {
//}
//
//void MenuGUI::init() {
//}
//
//void MenuGUI::render() {
//}
//
//SDL_Rect MenuGUI::getRectOfBtnVsCom() {
//	return SDL_Rect();
//}
//
//SDL_Rect MenuGUI::getRectOfBtnVsPlayer() {
//	return SDL_Rect();
//}
//
//SDL_Rect MenuGUI::getRectOfBtnVolumeOption() {
//	return SDL_Rect();
//}
//
//SDL_Rect MenuGUI::getRectOfBtnReplayRecentGame() {
//	return SDL_Rect();
//}
//
//SDL_Rect MenuGUI::getRectOfBtnExit() {
//	return SDL_Rect();
//}
//
//ModeOptionGUI::ModeOptionGUI() {
//}
//
//ModeOptionGUI::~ModeOptionGUI() {
//}
//
//void ModeOptionGUI::init() {
//}
//
//void ModeOptionGUI::render() {
//}
//
//TypeGUI ModeOptionGUI::getTypeGUI() const {
//	return TypeGUI();
//}
//
//SDL_Rect ModeOptionGUI::getRectOfBtnEasy() {
//	return SDL_Rect();
//}
//
//SDL_Rect ModeOptionGUI::getRectOfBtnHard() {
//	return SDL_Rect();
//}
//
//SDL_Rect ModeOptionGUI::getRectOfBtnBackToMenu() {
//	return SDL_Rect();
//}

//VolumeOptionGUI::VolumeOptionGUI() {
//}
//
//VolumeOptionGUI::~VolumeOptionGUI() {
//}
//
//void VolumeOptionGUI::init() {
//}
//
//void VolumeOptionGUI::render() {
//}
//
//TypeGUI VolumeOptionGUI::getTypeGUI() const {
//	return TypeGUI();
//}
//
//Slider* VolumeOptionGUI::getSliderThemeMusic() {
//	return nullptr;
//}
//
//Slider* VolumeOptionGUI::getSliderEventMusic() {
//	return nullptr;
//}
//
//SDL_Rect VolumeOptionGUI::getRectOfBtnBackToMenu() {
//	return SDL_Rect();
//}

// ------------------------------------------------------------------------------------------------------
// GamePlayGUI

GamePlayGUI::GamePlayGUI() { //LOAD ALL THE ESSENTIALS
	SDL_RenderClear(Window::renderer);
	this->active = true;
	this->background = new Image({ 0,0,1000,600 }, "..\\Assets\\chess\\back.jpg");
	this->chosenPiece = nullptr;
	//load board image
	this->board = new Image({ 0,0,560,560 }, "..\\Assets\\chess\\ChessBoard.png");
	//load possible move image
	this->possibleMove = new Image({ 0,0,0,0 }, "..\\Assets\\chess\\PossibleMove.png");
	//buttons
	this->btnSetting = new Image({ 800,20,100,100 }, "..\\Assets\\chess\\settings.png");
	this->btnUndo = new Image({ 800,140,100,100 }, "..\\Assets\\chess\\undo.png");
	this->btnRedo = new Image({ 800,260,100,100 }, "..\\Assets\\chess\\redo.png");
	this->btnQuit = new Image({ 800,380,100,100 }, "..\\Assets\\chess\\quit.png");
	//promotion buttons
	this->btnPromoteQueen = new Image({ 0,0,0,0 }, "..\\Assets\\chess\\ProQueen.png");
	this->btnPromoteBishop = new Image({ 0,0,0,0 }, "..\\Assets\\chess\\ProBishop.png");
	this->btnPromoteRook = new Image({ 0,0,0,0 }, "..\\Assets\\chess\\ProRook.png");
	this->btnPromoteKnight =new Image({ 0,0,0,0 }, "..\\Assets\\chess\\ProKnight.png");
	//LOAD PIECES IMAGEs
	for (int i = 0; i < Board::piecesList.size(); i++) {
		//get name
		std::string tempstring = "..\\Assets\\chess\\";
		Color color = Board::piecesList[i]->getColor();
		PieceType pt = Board::piecesList[i]->getType();
		if (color == Color::Black) {
			if (pt == PieceType::King) tempstring += "KingBlack.png";
			if (pt == PieceType::Queen) tempstring += "QueenBlack.png";
			if (pt == PieceType::Bishop) tempstring += "BishopBlack.png";
			if (pt == PieceType::Rook) tempstring += "RookBlack.png";
			if (pt == PieceType::Knight) tempstring += "KnightBlack.png";
			if (pt == PieceType::Pawn) tempstring += "PawnBlack.png";
			std::cout << tempstring << std::endl;
		}
		else {
			if (pt == PieceType::King) tempstring += "KingWhite.png";
			if (pt == PieceType::Queen) tempstring += "QueenWhite.png";
			if (pt == PieceType::Bishop) tempstring += "BishopWhite.png";
			if (pt == PieceType::Rook) tempstring += "RookWhite.png";
			if (pt == PieceType::Knight) tempstring += "KnightWhite.png";
			if (pt == PieceType::Pawn) tempstring += "PawnWhite.png";
			std::cout << tempstring << std::endl;
		}
		int x = Board::piecesList[i]->getPosition().getX() * 70;
		int y = Board::piecesList[i]->getPosition().getY() * 70;
		Image* temp = new Image({ x,y,70,70 }, tempstring);
		this->piece.push_back(temp);
	}
}

GamePlayGUI::~GamePlayGUI() {
	this->destroy();
}

void GamePlayGUI::set() {
	//set chosen one
	chosenPiece = nullptr;
	for (int i = 0; i < Board::piecesList.size(); i++) {
		if (!Board::piecesList[i]->getDead())
		if (Board::piecesList[i]->getChosen()) {
			this->chosenPiece = Board::piecesList[i];
			break;
		}
	}
	//set coor of pieces
	for (int i = 0; i < Board::piecesList.size(); i++) {
		if (Board::piecesList[i]->getDead()) {
			this->piece[i]->setRectangle({ 0,0,0,0 });
		}
		else {
			int x = Board::piecesList[i]->getPosition().getX() * 70;
			int y = Board::piecesList[i]->getPosition().getY() * 70;
			this->piece[i]->setRectangle({ x,y,70,70 });
		}
	}
}

void GamePlayGUI::render() {
	//set
	this->set();
	//background
	this->background->renderImage();
	//board
	this->board->renderImage();
	//BUTTONS
	this->btnUndo->renderImage();
	this->btnRedo->renderImage();
	this->btnSetting->renderImage();
	this->btnQuit->renderImage();
	//
	this->btnPromoteQueen->renderImage();
	this->btnPromoteBishop->renderImage();
	this->btnPromoteRook->renderImage();
	this->btnPromoteKnight->renderImage();
	//possible moves
	if (this->chosenPiece != nullptr) 
	for (int i = 0; i < this->chosenPiece->getPossibleMoves(Board::piecesOnBoard).size(); i++) {
		int x = this->chosenPiece->getPossibleMoves(Board::piecesOnBoard)[i].getX() * 70;
		int y = this->chosenPiece->getPossibleMoves(Board::piecesOnBoard)[i].getY() * 70;
		this->possibleMove->setRectangle({ x,y,70,70 });
		this->possibleMove->renderImage();
	}
	//pieces
	for (int i = 0; i < this->piece.size(); i++) {
		this->piece[i]->renderImage();
	}
}
void GamePlayGUI::initPromotionButtons() {
	this->btnPromoteQueen->setRectangle({ 570,300,70,70 });
	this->btnPromoteBishop->setRectangle({ 570,380,70,70 });
	this->btnPromoteRook->setRectangle({ 650,300,70,70 });
	this->btnPromoteKnight->setRectangle({ 650,380,70,70 });
}	 //call when needed
void GamePlayGUI::clearPromotionButtons() {
	this->btnPromoteQueen->setRectangle({ 0,0,0,0 });
	this->btnPromoteBishop->setRectangle({ 0,0,0,0 });
	this->btnPromoteRook->setRectangle({ 0,0,0,0 });
	this->btnPromoteKnight->setRectangle({ 0,0,0,0 });
}   //must call after use
//get rect
TypeGUI GamePlayGUI::getTypeGUI() const {
	return TypeGUI::GAME_PLAY;
}
SDL_Rect GamePlayGUI::getRectOfBtnUndo() {
	return this->btnUndo->getRectangle();
}

SDL_Rect GamePlayGUI::getRectOfBoard(){
	return this->board->getRectangle();
}

SDL_Rect GamePlayGUI::getRectOfBtnSetting() {
	return this->btnSetting->getRectangle();
}
SDL_Rect GamePlayGUI::getRectOfBtnRedo() {
	return this->btnRedo->getRectangle();
}
SDL_Rect GamePlayGUI::getRectOfBtnQuit() {
	return this->btnQuit->getRectangle();
}
SDL_Rect GamePlayGUI::getRectOfBtnPromoteQueen() {
	return this->btnPromoteQueen->getRectangle();
}
SDL_Rect GamePlayGUI::getRectOfBtnPromoteRook() {
	return this->btnPromoteRook->getRectangle();
}
SDL_Rect GamePlayGUI::getRectOfBtnPromoteBishop() {
	return this->btnPromoteBishop->getRectangle();
}
SDL_Rect GamePlayGUI::getRectOfBtnPromoteKnight() {
	return this->btnPromoteKnight->getRectangle();
}
void GamePlayGUI::destroy() {
	for (int i = 0; i < this->piece.size(); i++) {
		this->piece[i]->destroy();
		delete this->piece[i];
		this->piece[i] = nullptr;
	}
	this->piece.clear();
	//
	this->btnPromoteQueen->destroy();
	delete this->btnPromoteQueen;
	this->btnPromoteQueen = nullptr;
	//
	this->btnPromoteRook->destroy();
	delete this->btnPromoteRook;
	this->btnPromoteRook = nullptr;
	//
	this->btnPromoteBishop->destroy();
	delete this->btnPromoteBishop;
	this->btnPromoteBishop= nullptr;
	//
	this->btnPromoteKnight->destroy();
	delete this->btnPromoteKnight;
	this->btnPromoteKnight = nullptr;
	//
	this->btnQuit->destroy();
	delete this->btnQuit;
	this->btnQuit = nullptr;
	//
	this->btnUndo->destroy();
	delete this->btnUndo;
	this->btnUndo = nullptr;
	//
	this->btnRedo->destroy();
	delete this->btnRedo;
	this->btnRedo = nullptr;
	//
	this->btnSetting->destroy();
	delete this->btnSetting;
	this->btnSetting = nullptr;
	//
	this->possibleMove->destroy();
	delete this->possibleMove;
	this->possibleMove = nullptr;
	//
	this->board->destroy();
	delete this->board;
	this->board = nullptr;
	//
}
//MatchResultGUI::MatchResultGUI() {
//}
//
//MatchResultGUI::~MatchResultGUI() {
//}
//
//void MatchResultGUI::init() {
//}
//
//void MatchResultGUI::render() {
//}
//
//TypeGUI MatchResultGUI::getTypeGUI() const {
//	return TypeGUI();
//}
//
//void MatchResultGUI::setText(const TextObject& text) {
//}

//PromotionNoticeGUI::PromotionNoticeGUI(int idOfPromotionPiece) {
//}
//
//PromotionNoticeGUI::~PromotionNoticeGUI() {
//}
//
//void PromotionNoticeGUI::init() {
//}
//
//void PromotionNoticeGUI::render() {
//}
//
//TypeGUI PromotionNoticeGUI::getTypeGUI() const {
//	return TypeGUI();
//}
//
//int PromotionNoticeGUI::getIdOfPromotionPiece() const {
//	return 0;
//}
//
//SDL_Rect PromotionNoticeGUI::getRectOfBtnQueen() {
//	return SDL_Rect();
//}
//
//SDL_Rect PromotionNoticeGUI::getRectOfBtnBishop() {
//	return SDL_Rect();
//}

//SettingGUI::SettingGUI() {
//}
//
//SettingGUI::~SettingGUI() {
//}
//
//void SettingGUI::init() {
//}
//
//void SettingGUI::render() {
//}
//
//TypeGUI SettingGUI::getTypeGUI() const {
//	return TypeGUI();
//}
//
//SDL_Rect SettingGUI::getRectOfBtnContinue() {
//	return SDL_Rect();
//}
