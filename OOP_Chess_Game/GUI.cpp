#include "GUI.h"
#include <iostream>


GUI::GUI() {
	this->active = true;
	this->background = new Image({ 0,0,640,560 }, "..\\Assets\\back.png");
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
SDL_Rect GUI::getGUIRect() {
	return this->background->getRectangle();
}
GUIType GUI::getGUIType() const {
	return GUIType();
}
// 
//GUIType MenuGUI::getGUIType() const {
//	return GUIType::MENU;
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
//GUIType ModeOptionGUI::getGUIType() const {
//	return GUIType();
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
//GUIType VolumeOptionGUI::getGUIType() const {
//	return GUIType();
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
	this->background = new Image({ 0,0,640,560 }, "..\\Assets\\back.png");
	this->chosenPiece = nullptr;
	//load board image
	this->board = new Image({ DISPLACE,DISPLACE,PIECESIZE*8,PIECESIZE*8 }, "..\\Assets\\board.png");
	//load chosen
	this->chosen = new Image({ 0,0,0,0 }, "..\\Assets\\chosen.png");
	//load possible move/ possible capture image
	this->possibleMove = new Image({ 0,0,0,0 }, "..\\Assets\\PossibleMove.png");
	this->possibleCapture = new Image({ 0,0,0,0 }, "..\\Assets\\PossibleCapture.png");
	//make chosen-move-capture blending
	this->chosen->makeBlend(100);
	this->possibleMove->makeBlend(100);
	this->possibleCapture->makeBlend(100);
	//buttons
	this->btnSetting = new Image({ PIECESIZE * 8 + 30 + DISPLACE ,DISPLACE + PIECESIZE * 4,PIECESIZE,PIECESIZE }, "..\\Assets\\settings.png");
	this->btnUndo = new Image({ PIECESIZE * 8 + 30 + DISPLACE ,DISPLACE + PIECESIZE * 5,PIECESIZE,PIECESIZE }, "..\\Assets\\undo.png");
	this->btnRedo = new Image({ PIECESIZE * 8 + 30 + DISPLACE ,DISPLACE + PIECESIZE * 6,PIECESIZE,PIECESIZE }, "..\\Assets\\redo.png");
	this->btnQuit = new Image({ PIECESIZE * 8 + 30 + DISPLACE ,DISPLACE + PIECESIZE * 7,PIECESIZE,PIECESIZE }, "..\\Assets\\quit.png");
	//TURN
	this->whiteMove = new Image({ DISPLACE + PIECESIZE * 8, DISPLACE + 15, 120, 210 }, "..\\Assets\\white_move.png");
	this->blackMove = new Image({ DISPLACE + PIECESIZE * 8, DISPLACE + 15, 120, 210 }, "..\\Assets\\black_move.png");
	//
	////promotion buttons
	//this->btnPromoteQueen = new Image({ 0,0,0,0 }, "..\\Assets\\ProQueen.png");
	//this->btnPromoteBishop = new Image({ 0,0,0,0 }, "..\\Assets\\ProBishop.png");
	//this->btnPromoteRook = new Image({ 0,0,0,0 }, "..\\Assets\\ProRook.png");
	//this->btnPromoteKnight = new Image({ 0,0,0,0 }, "..\\Assets\\ProKnight.png");
	//LOAD PIECES IMAGEs
	for (int i = 0; i < Board::piecesList.size(); i++) {
		//get name
		std::string tempstring = "..\\Assets\\";
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
		int x = Board::piecesList[i]->getPosition().getX() * PIECESIZE + DISPLACE;
		int y = Board::piecesList[i]->getPosition().getY() * PIECESIZE + DISPLACE;
		Image* temp = new Image({ x,y,PIECESIZE,PIECESIZE }, tempstring);
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
			int x = Board::piecesList[i]->getPosition().getX() * PIECESIZE + DISPLACE;
			int y = Board::piecesList[i]->getPosition().getY() * PIECESIZE + DISPLACE;
			this->piece[i]->setRectangle({ x,y,PIECESIZE,PIECESIZE });
		}
	}
	//check promoted pawns
	for (int i = 0; i < Board::piecesList.size(); i++) {
		if (Board::piecesList[i]->getType() == PieceType::Pawn && Board::piecesList[i]->getColor() == Color::White && Board::piecesList[i]->getPromotion()) {
			if (Board::piecesList[i]->getPromotion()->getType() == PieceType::Queen) this->piece[i]->setTexture(this->piece[1]->getTexture());
			if (Board::piecesList[i]->getPromotion()->getType() == PieceType::Bishop) this->piece[i]->setTexture(this->piece[2]->getTexture());
			if (Board::piecesList[i]->getPromotion()->getType() == PieceType::Knight) this->piece[i]->setTexture(this->piece[4]->getTexture());
			if (Board::piecesList[i]->getPromotion()->getType() == PieceType::Rook) this->piece[i]->setTexture(this->piece[6]->getTexture());
		}
		if (Board::piecesList[i]->getType() == PieceType::Pawn && Board::piecesList[i]->getColor() == Color::Black && Board::piecesList[i]->getPromotion()) {
			if (Board::piecesList[i]->getPromotion()->getType() == PieceType::Queen) this->piece[i]->setTexture(this->piece[17]->getTexture());
			if (Board::piecesList[i]->getPromotion()->getType() == PieceType::Bishop) this->piece[i]->setTexture(this->piece[18]->getTexture());
			if (Board::piecesList[i]->getPromotion()->getType() == PieceType::Knight) this->piece[i]->setTexture(this->piece[20]->getTexture());
			if (Board::piecesList[i]->getPromotion()->getType() == PieceType::Rook) this->piece[i]->setTexture(this->piece[22]->getTexture());
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
	//this->btnPromoteQueen->renderImage();
	//this->btnPromoteBishop->renderImage();
	//this->btnPromoteRook->renderImage();
	//this->btnPromoteKnight->renderImage();
	//possible moves - possible capture - chosen
	if (this->chosenPiece != nullptr) {
		//chosen
		int x = this->chosenPiece->getPosition().getX() * PIECESIZE + DISPLACE;
		int y = this->chosenPiece->getPosition().getY() * PIECESIZE + DISPLACE;
		this->chosen->setRectangle({ x,y,PIECESIZE,PIECESIZE });
		this->chosen->renderImage();
		//possible moves
		for (int i = 0; i < this->chosenPiece->getPossibleMoves(Board::piecesOnBoard)[0].size(); i++) {
			x = this->chosenPiece->getPossibleMoves(Board::piecesOnBoard)[0][i].getX() * PIECESIZE + DISPLACE;
			y = this->chosenPiece->getPossibleMoves(Board::piecesOnBoard)[0][i].getY() * PIECESIZE + DISPLACE;
			this->possibleMove->setRectangle({ x,y,PIECESIZE,PIECESIZE });
			this->possibleMove->renderImage();
		}
		//possible capture
		for (int i = 0; i < this->chosenPiece->getPossibleMoves(Board::piecesOnBoard)[1].size(); i++) {
			x = this->chosenPiece->getPossibleMoves(Board::piecesOnBoard)[1][i].getX() * PIECESIZE + DISPLACE;
			y = this->chosenPiece->getPossibleMoves(Board::piecesOnBoard)[1][i].getY() * PIECESIZE + DISPLACE;
			this->possibleCapture->setRectangle({ x,y,PIECESIZE,PIECESIZE });
			this->possibleCapture->renderImage();
		}
	}
	//pieces
	for (int i = 0; i < this->piece.size(); i++) {
		this->piece[i]->renderImage();
	}
}
//void GamePlayGUI::initPromotionButtons() {
//	this->btnPromoteQueen->setRectangle({ 570,300,70,70 });
//	this->btnPromoteBishop->setRectangle({ 570,380,70,70 });
//	this->btnPromoteRook->setRectangle({ 600,300,70,70 });
//	this->btnPromoteKnight->setRectangle({ 600,380,70,70 });
//}	 //call when needed
//void GamePlayGUI::clearPromotionButtons() {
//	this->btnPromoteQueen->setRectangle({ 0,0,0,0 });
//	this->btnPromoteBishop->setRectangle({ 0,0,0,0 });
//	this->btnPromoteRook->setRectangle({ 0,0,0,0 });
//	this->btnPromoteKnight->setRectangle({ 0,0,0,0 });
//}   //must call after use
void GamePlayGUI::renderTurn(int turn) {
	if (turn % 2 == 0) {//white
		this->whiteMove->renderImage();
	}
	else {
		this->blackMove->renderImage();
	}
}
//get rect
GUIType GamePlayGUI::getGUIType() const {
	return GUIType::GAME_PLAY;
}
SDL_Rect GamePlayGUI::getRectOfBtnUndo() {
	return this->btnUndo->getRectangle();
}

SDL_Rect GamePlayGUI::getRectOfBoard() {
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
//SDL_Rect GamePlayGUI::getRectOfBtnPromoteQueen() {
//	return this->btnPromoteQueen->getRectangle();
//}
//SDL_Rect GamePlayGUI::getRectOfBtnPromoteRook() {
//	return this->btnPromoteRook->getRectangle();
//}
//SDL_Rect GamePlayGUI::getRectOfBtnPromoteBishop() {
//	return this->btnPromoteBishop->getRectangle();
//}
//SDL_Rect GamePlayGUI::getRectOfBtnPromoteKnight() {
//	return this->btnPromoteKnight->getRectangle();
//}
void GamePlayGUI::destroy() {
	for (int i = 0; i < this->piece.size(); i++) {
		this->piece[i]->destroy();
		delete this->piece[i]; 
		this->piece[i] = nullptr;
	}
	this->piece.clear();
	//
	//this->btnPromoteQueen->destroy();
	//delete this->btnPromoteQueen;
	//this->btnPromoteQueen = nullptr;
	////
	//this->btnPromoteRook->destroy();
	//delete this->btnPromoteRook;
	//this->btnPromoteRook = nullptr;
	////
	//this->btnPromoteBishop->destroy();
	//delete this->btnPromoteBishop;
	//this->btnPromoteBishop = nullptr;
	////
	//this->btnPromoteKnight->destroy();
	//delete this->btnPromoteKnight;
	//this->btnPromoteKnight = nullptr;
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
	this->possibleCapture->destroy();
	delete this->possibleCapture;
	this->possibleCapture = nullptr;
	//
	this->chosen->destroy();
	delete this->chosen;
	this->chosen = nullptr;
	//
	this->board->destroy();
	delete this->board;
	this->board = nullptr;
	//
	this->whiteMove->destroy();
	delete this->whiteMove;
	this->whiteMove = nullptr;
	//
	this->blackMove->destroy();
	delete this->blackMove;
	this->blackMove = nullptr;
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
//GUIType MatchResultGUI::getGUIType() const {
//	return GUIType();
//}
//
//void MatchResultGUI::setText(const TextObject& text) {
//}


PromotionGUI::PromotionGUI() {
	this->up = new Image({ SUBDISPLACE + 110, WINDOWSIZEY - 360, 70, 70 }, "..\\Assets\\ProNotice.png");
	this->background = new Image({ SUBDISPLACE,SUBDISPLACE,SUBSIZEX, SUBSIZEY }, "..\\Assets\\subback.png");
	this->btnQueen = new Image({ SUBDISPLACE + 10, WINDOWSIZEY - 280, PIECESIZE, PIECESIZE }, "..\\Assets\\ProQueen.png");
	this->btnRook = new Image({ SUBDISPLACE + 20 + PIECESIZE, WINDOWSIZEY - 280, PIECESIZE, PIECESIZE }, "..\\Assets\\ProRook.png");
	this->btnKnight = new Image({ SUBDISPLACE + 30 + PIECESIZE * 2, WINDOWSIZEY - 280, PIECESIZE, PIECESIZE }, "..\\Assets\\ProKnight.png");
	this->btnBishop = new Image({ SUBDISPLACE + 40 + PIECESIZE * 3, WINDOWSIZEY - 280, PIECESIZE, PIECESIZE }, "..\\Assets\\ProBishop.png");
}

PromotionGUI::~PromotionGUI() {
	this->destroy();
}

void PromotionGUI::render() {
	this->background->renderImage();
	this->up->renderImage();
	this->btnBishop->renderImage();
	this->btnKnight->renderImage();
	this->btnQueen->renderImage();
	this->btnRook->renderImage();
}

GUIType PromotionGUI::getGUIType() const {
	return GUIType::PROMOTION_NOTICE;
}

SDL_Rect PromotionGUI::getRectOfBtnQueen() {
	return this->btnQueen->getRectangle();
}
SDL_Rect PromotionGUI::getRectOfBtnBishop() {
	return this->btnBishop->getRectangle();
}
SDL_Rect PromotionGUI::getRectOfBtnRook() {
	return this->btnRook->getRectangle();
}
SDL_Rect PromotionGUI::getRectOfBtnKnight() {
	return this->btnKnight->getRectangle();
}
void PromotionGUI::destroy() {
	//
	this->background->destroy();
	delete this->background;
	this->background = nullptr;
	//
	this->up->destroy();
	delete this->up;
	this->up = nullptr;
	//
	this->btnQueen->destroy();
	delete this->btnQueen;
	this->btnQueen = nullptr;
	//
	this->btnRook->destroy();
	delete this->btnRook;
	this->btnRook = nullptr;
	//
	this->btnBishop->destroy();
	delete this->btnBishop;
	this->btnBishop = nullptr;
	//
	this->btnKnight->destroy();
	delete this->btnKnight;
	this->btnKnight = nullptr;
}

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
//GUIType SettingGUI::getGUIType() const {
//	return GUIType();
//}
//
//SDL_Rect SettingGUI::getRectOfBtnContinue() {
//	return SDL_Rect();
//}
