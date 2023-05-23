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
	this->btnSetting = new Image({ PIECESIZE * 8 + 30 + DISPLACE ,DISPLACE + PIECESIZE * 5,PIECESIZE,PIECESIZE }, "..\\Assets\\settings.png");
	this->btnUndo = new Image({ PIECESIZE * 8 + 30 + DISPLACE ,DISPLACE + PIECESIZE * 6,PIECESIZE,PIECESIZE }, "..\\Assets\\undo.png");
	this->btnRedo = new Image({ PIECESIZE * 8 + 30 + DISPLACE ,DISPLACE + PIECESIZE * 7,PIECESIZE,PIECESIZE }, "..\\Assets\\redo.png");
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
	//possible moves - possible capture - chosen

	
	if (this->chosenPiece != nullptr) {
		//chosen
		int x = this->chosenPiece->getPosition().getX() * PIECESIZE + DISPLACE;
		int y = this->chosenPiece->getPosition().getY() * PIECESIZE + DISPLACE;
		this->chosen->setRectangle({ x,y,PIECESIZE,PIECESIZE });
		this->chosen->renderImage();

		std::vector<std::vector<Coordinate>> moves = this->chosenPiece->getPossibleMoves(Board::piecesOnBoard);
		//possible moves
		for (int i = 0; i < moves[0].size(); i++) {
			x = moves[0][i].getX() * PIECESIZE + DISPLACE;
			y = moves[0][i].getY() * PIECESIZE + DISPLACE;
			this->possibleMove->setRectangle({ x,y,PIECESIZE,PIECESIZE });
			this->possibleMove->renderImage();
		}
		//possible capture
		for (int i = 0; i < moves[1].size(); i++) {
			x = moves[1][i].getX() * PIECESIZE + DISPLACE;
			y = moves[1][i].getY() * PIECESIZE + DISPLACE;
			this->possibleCapture->setRectangle({ x,y,PIECESIZE,PIECESIZE });
			this->possibleCapture->renderImage();
		}
	}
	//pieces and check promoted pawn
	for (int i = 0; i < Board::piecesList.size(); i++) {
		if (Board::piecesList[i]->getType() == PieceType::Pawn) {
			Pawn* pawn = (Pawn*)Board::piecesList[i];
			if (pawn->getPromotion()) {
				int plus = 0;
				if (pawn->getColor() == Color::Black) plus = 16;
				PieceType promotionType = pawn->getPromotion()->getType();
				//
				if (promotionType == PieceType::Queen) {
					this->piece[1 + plus]->setRectangle(this->piece[i]->getRectangle());
					this->piece[1 + plus]->renderImage();
				}
				if (promotionType == PieceType::Bishop) {
					this->piece[2 + plus]->setRectangle(this->piece[i]->getRectangle());
					this->piece[2 + plus]->renderImage();
				}
				if (promotionType == PieceType::Knight) {
					this->piece[4 + plus]->setRectangle(this->piece[i]->getRectangle());
					this->piece[4 + plus]->renderImage();
				}
				if (promotionType == PieceType::Rook) {
					this->piece[6 + plus]->setRectangle(this->piece[i]->getRectangle());
					this->piece[6 + plus]->renderImage();
				}
			}
			else this->piece[i]->renderImage();
		}
		else this->piece[i]->renderImage();
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
	//
	this->background->destroy();
	delete this->background;
	this->background = nullptr;
}
MatchResultGUI::MatchResultGUI() {
	this->background = new Image({ SUBDISPLACE,SUBDISPLACE,SUBSIZEX, SUBSIZEY }, "..\\Assets\\subback.png");
	this->blackWin = new Image({ SUBDISPLACE + 30,SUBDISPLACE + 20, 230, 80 }, "..\\Assets\\BlackWin.png");
	this->whiteWin = new Image({ SUBDISPLACE + 30,SUBDISPLACE + 20, 230, 80 }, "..\\Assets\\WhiteWin.png");
	this->draw = new Image({ SUBDISPLACE + 40,SUBDISPLACE + 20, 210, 70 }, "..\\Assets\\Draw.png");
	this->btnPlayAgain = new Image({ SUBDISPLACE + 20 + PIECESIZE, SUBDISPLACE + 120, PIECESIZE, PIECESIZE }, "..\\Assets\\undo.png");
	this->btnBackToMenu = new Image({ SUBDISPLACE + 30 + PIECESIZE * 2, SUBDISPLACE + 120, PIECESIZE, PIECESIZE }, "..\\Assets\\tomenu.png");
}

MatchResultGUI::~MatchResultGUI() {
	this->destroy();
}


void MatchResultGUI::render() {
	this->background->renderImage();
	this->btnBackToMenu->renderImage();
	this->btnPlayAgain->renderImage();
}

void MatchResultGUI::renderMatchResult(MatchState ms) {
	if (ms == MatchState::BLACK_WIN) {
		this->blackWin->renderImage();
		return;
	}
	if (ms == MatchState::WHITE_WIN) {
		this->whiteWin->renderImage();
		return;
	}
	if (ms == MatchState::DRAW) {
		this->draw->renderImage();
		return;
	}
}


GUIType MatchResultGUI::getGUIType() const {
	return GUIType::RESULT_NOTICE;
}

void MatchResultGUI::destroy() {
	this->background->destroy();
	delete this->background;
	this->background = nullptr;
	//
	this->blackWin->destroy();
	delete this->blackWin;
	this->blackWin = nullptr;
	//
	this->whiteWin->destroy();
	delete this->whiteWin;
	this->whiteWin = nullptr;
	//
	this->btnPlayAgain->destroy();
	delete this->btnPlayAgain;
	this->btnPlayAgain = nullptr;
	//
	this->btnBackToMenu->destroy();
	delete this->btnBackToMenu;
	this->btnBackToMenu = nullptr;
}
SDL_Rect MatchResultGUI::getRectOfBtnBackToMenu() {
	return this->btnBackToMenu->getRectangle();
}
SDL_Rect MatchResultGUI::getRectOfBtnPlayAgain() {
	return this->btnPlayAgain->getRectangle();
}


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

SettingGUI::SettingGUI() {
	this->symbol = new Image({ SUBDISPLACE + 110, WINDOWSIZEY - 360, 70, 70 }, "..\\Assets\\settingSymbol.png");
	this->background = new Image({ SUBDISPLACE,SUBDISPLACE,SUBSIZEX, SUBSIZEY }, "..\\Assets\\subback.png");
	this->btnResume = new Image({ SUBDISPLACE + 10, WINDOWSIZEY - 280, PIECESIZE, PIECESIZE }, "..\\Assets\\resume.png");
	this->btnVolumeOption = new Image({ SUBDISPLACE + 20 + PIECESIZE, WINDOWSIZEY - 280, PIECESIZE, PIECESIZE }, "..\\Assets\\volume.png");
	this->btnSave = new Image({ SUBDISPLACE + 30 + PIECESIZE * 2, WINDOWSIZEY - 280, PIECESIZE, PIECESIZE }, "..\\Assets\\save.png");
	this->btnBackToMenu = new Image({ SUBDISPLACE + 40 + PIECESIZE * 3, WINDOWSIZEY - 280, PIECESIZE, PIECESIZE }, "..\\Assets\\tomenu.png");
}

SettingGUI::~SettingGUI() {
	this->destroy();
}


void SettingGUI::render() {
	this->background->renderImage();
	this->symbol->renderImage();
	this->btnResume->renderImage();
	this->btnVolumeOption->renderImage();
	this->btnSave->renderImage();
	this->btnBackToMenu->renderImage();
}

GUIType SettingGUI::getGUIType() const {
	return GUIType::SETTINGS;
}


void SettingGUI::destroy() {
	//
	this->background->destroy();
	delete this->background;
	this->background = nullptr;
	//
	this->symbol->destroy();
	delete this->symbol;
	this->symbol = nullptr;
	//
	this->btnResume->destroy();
	delete this->btnResume;
	this->btnResume = nullptr;
	//
	this->btnSave->destroy();
	delete this->btnSave;
	this->btnSave = nullptr;
	//
	this->btnBackToMenu->destroy();
	delete this->btnBackToMenu;
	this->btnBackToMenu = nullptr;
}

SDL_Rect SettingGUI::getRectOfBtnResume() {
	return this->btnResume->getRectangle();
}
SDL_Rect SettingGUI::getRectOfBtnVolumeOption() {
	return this->btnVolumeOption->getRectangle();
}
SDL_Rect SettingGUI::getRectOfBtnBackToMenu() {
	return this->btnBackToMenu->getRectangle();
}
SDL_Rect SettingGUI::getRectOfBtnSave() {
	return this->btnSave->getRectangle();
}
