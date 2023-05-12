#include "GUI.h"
#include <iostream>

//void SDL_Delay(Uint32 ms);
//
GUI::GUI() {
	this->active = true;
}

GUI::~GUI() {
}

void GUI::renderBackground(SDL_Renderer* renderer) {
	SDL_Surface* image = IMG_Load(this->pathImageBackground.c_str());
	if (image) {
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
		SDL_FreeSurface(image);
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		SDL_RenderPresent(renderer);
	}
	else std::cout << "can't load";
}
void GUI::clear(SDL_Renderer* renderer) {
	SDL_RenderClear(renderer);
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

GamePlayGUI::GamePlayGUI() {

	this->active = true;
	this->piece.clear();
	this->possibleMove.clear();
	//
	this->board = Image({ 0,0,560,560 }, "..\\Assets\\Chess\\ChessBoard.png");
	//buttons
	this->btnSetting = Image({ 800,20,100,100 }, "..\\Assets\\Chess\\settings.png");
	this->btnUndo = Image({ 800,140,100,100 }, "..\\Assets\\Chess\\undo.png");
	this->btnRedo = Image({ 800,260,100,100 }, "..\\Assets\\Chess\\redo.png");
	this->btnQuit = Image({ 800,380,100,100 }, "..\\Assets\\Chess\\quit.png");
	//promotion buttons
	this->btnPromoteQueen = Image({ 0,0,0,0 }, "..\\Assets\\Chess\\ProQueen.png");
	this->btnPromoteBishop = Image({ 0,0,0,0 }, "..\\Assets\\Chess\\ProBishop.png");
	this->btnPromoteRook = Image({ 0,0,0,0 }, "..\\Assets\\Chess\\ProRook.png");
	this->btnPromoteKnight = Image({ 0,0,0,0 }, "..\\Assets\\Chess\\ProKnight.png");
}

GamePlayGUI::~GamePlayGUI() {

}

void GamePlayGUI::init(Board* board) {
	//get image of pieces
	for (int i = 0; i < board->piecesOnBoard.size(); i++) {
		for (int j = 0; j < board->piecesOnBoard[i].size(); j++) {
			Piece* temppiece = board->piecesOnBoard[i][j];
			if (temppiece) {
				//get rect
				int x = temppiece->getPosition().getX() * 70;
				int y = temppiece->getPosition().getY() * 70;
				//
				std::cout << x << y << std::endl;
				//
				SDL_Rect temprect = { x,y,70,70 };
				//get name
				std::string tempstring = "..\\Assets\\Chess\\";
				Color color = temppiece->getColor();
				PieceType pt = temppiece->getType();
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
				Image temp = Image(temprect, tempstring);
				this->piece.push_back(temp);
			}
		}
	}
	//get image of possible moves
	Piece* temppiece = nullptr;
	for (int i = 0; i < board->piecesOnBoard.size(); i++) {
		for (int j = 0; j < board->piecesOnBoard[i].size(); j++) {
			temppiece = board->piecesOnBoard[i][j];
			if (temppiece) if (temppiece->getChosen()) break;
		}
		if (temppiece) if (temppiece->getChosen()) break;
	}
	if (!temppiece || !temppiece->getChosen()) return;
	for (int i = 0; i < temppiece->getPossibleMoves().size(); i++) {
		int x = temppiece->getPossibleMoves()[i].getX() * 70;
		int y = temppiece->getPossibleMoves()[i].getY() * 70;
		Image temp = Image({ x,y,70,70 }, "..\\Assets\\Chess\\PossibleMove.png");
		this->piece.push_back(temp);
	}
}

void GamePlayGUI::render(SDL_Renderer* renderer) {
	this->renderBackground(renderer);
	//
	this->board.renderImage(renderer);
	//
	for (int i = 0; i < this->possibleMove.size(); i++) {
		this->possibleMove[i].renderImage(renderer);
	}
	for (int i = 0; i < this->piece.size(); i++) {
		this->piece[i].renderImage(renderer);
	}
	//
	this->btnUndo.renderImage(renderer);
	this->btnRedo.renderImage(renderer);
	this->btnSetting.renderImage(renderer);
	this->btnQuit.renderImage(renderer);
	//
	this->btnPromoteQueen.renderImage(renderer);
	this->btnPromoteBishop.renderImage(renderer);
	this->btnPromoteRook.renderImage(renderer);
	this->btnPromoteKnight.renderImage(renderer);
}
void GamePlayGUI::initPromotionButtons() {
	this->btnPromoteQueen = Image({ 570,300,70,70 }, "..\\Assets\\Chess\\ProQueen.png");
	this->btnPromoteBishop = Image({ 570,380,70,70 }, "..\\Assets\\Chess\\ProBishop.png");
	this->btnPromoteRook = Image({ 650,300,70,70 }, "..\\Assets\\Chess\\ProRook.png");
	this->btnPromoteKnight = Image({ 650,380,70,70 }, "..\\Assets\\Chess\\ProKnight.png");
}	 //call when needed
void GamePlayGUI::clearPromotionButtons() {
	this->btnPromoteQueen = Image({ 0,0,0,0 }, "..\\Assets\\Chess\\ProQueen.png");
	this->btnPromoteBishop = Image({ 0,0,0,0 }, "..\\Assets\\Chess\\ProBishop.png");
	this->btnPromoteRook = Image({ 0,0,0,0 }, "..\\Assets\\Chess\\ProRook.png");
	this->btnPromoteKnight = Image({ 0,0,0,0 }, "..\\Assets\\Chess\\ProKnight.png");
}   //must call after use
//get rect
TypeGUI GamePlayGUI::getTypeGUI() const {
	return TypeGUI::GAME_PLAY;
}

SDL_Rect GamePlayGUI::getRectOfBtnUndo() {
	return this->btnUndo.getRectangle();
}

SDL_Rect GamePlayGUI::getRectOfBtnSetting() {
	return this->btnSetting.getRectangle();
}

SDL_Rect GamePlayGUI::getRectOfBtnRedo() {
	return this->btnRedo.getRectangle();
}
void GamePlayGUI::clear(SDL_Renderer* renderer) {
	GUI::clear(renderer);
	this->piece.clear();
	this->possibleMove.clear();
}
SDL_Rect GamePlayGUI::getRectOfBtnPromoteQueen() {
	return this->btnPromoteQueen.getRectangle();
}
SDL_Rect GamePlayGUI::getRectOfBtnPromoteRook() {
	return this->btnPromoteRook.getRectangle();
}
SDL_Rect GamePlayGUI::getRectOfBtnPromoteBishop() {
	return this->btnPromoteBishop.getRectangle();
}
SDL_Rect GamePlayGUI::getRectOfBtnPromoteKnight() {
	return this->btnPromoteKnight.getRectangle();
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
