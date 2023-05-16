#include "GameManager.h"

// init static attribute
//* GameManager::window = nullptr;
//SDL_Renderer* GameManager::renderer = nullptr;

GameManager::GameManager(const char* title, int xPos, int yPos, int width, int height) {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) throw SDL_GetError();

	std::cout << "Subsystems Initialized! ... " << std::endl;

	Window::window = SDL_CreateWindow(title, xPos, yPos, width, height, 0);
	if (!Window::window) throw SDL_GetError();
	std::cout << "Window created!" << std::endl;

	Window::renderer = SDL_CreateRenderer(Window::window, -1, 0);
	if (!Window::renderer) throw SDL_GetError();
	std::cout << "Renderer created!" << std::endl;

	Window::SCREEN_HEIGHT = height;
	Window::SCREEN_WIDTH = width;

	soundManager = new SoundManager();
	board = new Board();
	computer = new Computer();
	history = new History();
	mainGui = new GamePlayGUI();

	opponent = Opponent::HUMAN; // default
	turn = 0; // start game, player1: 0 -> white; palyer2: 1->black
	result = MatchResult::PLAYING; // The game is currently taking place
	isRunning = true;

}

GameManager::~GameManager() {
	delete board, soundManager, computer, history, mainGui, subGui;
	board = nullptr; soundManager = nullptr; computer = nullptr;  history = nullptr; mainGui = nullptr; subGui = nullptr;
	SDL_DestroyRenderer(Window::renderer);
	SDL_DestroyWindow(Window::window);
	SDL_Quit();
}

void GameManager::gameLoop(int fps) {

	int frameDelay = 1000 / fps;
	Uint32 frameStart = 0;
	int frameTime = 0;

	while (isRunning) {
		frameStart = SDL_GetTicks();
		handelEvents();
		render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

}

void GameManager::render() {
	SDL_RenderClear(Window::renderer);
	mainGui->render();
	SDL_RenderPresent(Window::renderer);
}

// TODO: try-catch
void GameManager::handelEvents() {
	SDL_Event e;

	//// 1 loop => perform 1 event
	//while (SDL_WaitEvent(&e)) { //=> Khac biet giua SDL_PollEvent va SDL_WaitEvent
	//	switch (e.type) {
	//	case SDL_QUIT:
	//		isRunning = false;
	//		return;
	//	
	//	default:
	//		break;
	//	}

	//}

	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			isRunning = false; break;
		case SDL_MOUSEBUTTONDOWN:
			Coordinate c = getClickedBox(e);
			std::cout << c.getX() << " " << c.getY() << std::endl;
			handleClickedPiece(e);
			handleClickedHightlightBox(e);
		}
	}

	/*while (SDL_PollEvent(&e)) {
	//	switch (e.type) {
	//	case SDL_QUIT:
	//		isRunning = false;
	//		break;
	//	case SDL_MOUSEBUTTONDOWN:
	//		handleClickedPiece(e);
	//		handleClickedHightlightBox(e);

	//		if (gui->getTypeGUI() == TypeGUI::MENU) {
	//			// TODO: add more handles

	//			if (checkFocus(e, MenuGUI::getRectOfBtnVsCom())) {
	//				opponent = Opponent::COMPUTER;
	//				delete gui;
	//				gui = new ModeOptionGUI();
	//				return;
	//			}

	//			if (checkFocus(e, MenuGUI::getRectOfBtnVsPlayer())) {
	//				opponent = Opponent::HUMAN;
	//				delete gui;
	//				gui = new GamePlayGUI();
	//				Board::resetPieces();
	//				return;
	//			}

	//			if (checkFocus(e, MenuGUI::getRectOfBtnVolumeOption())) {
	//				delete gui;
	//				gui = new VolumeOptionGUI();
	//				return;
	//			}

	//			if (checkFocus(e, MenuGUI::getRectOfBtnReplayRecentGame())) {
	//				delete gui;
	//				gui = new ReplayGameGUI();
	//				return;
	//			}

	//			if (checkFocus(e, MenuGUI::getRectOfBtnExit())) {
	//				isRunning = false;
	//				return;
	//			}
	//		}

	//		if (gui->getTypeGUI() == TypeGUI::MODE_OPTION) {
	//			if (checkFocus(e, ModeOptionGUI::getRectOfBtnEasy())) {
	//				computer->setMode(Mode::EASY);
	//				delete gui;
	//				gui = new GamePlayGUI();
	//				Board::resetPieces();
	//				return;
	//			}

	//			if (checkFocus(e, ModeOptionGUI::getRectOfBtnHard())) {
	//				computer->setMode(Mode::HARD);
	//				delete gui;
	//				gui = new GamePlayGUI();
	//				Board::resetPieces();
	//				return;
	//			}

	//			if (checkFocus(e, ModeOptionGUI::getRectOfBtnBackToMenu())) {
	//				backToMenu();
	//				return;
	//			}
	//		}

	//		if (gui->getTypeGUI() == TypeGUI::VOLUME_OPTION) {
	//			Slider* sliderThemeMusic = VolumeOptionGUI::getSliderThemeMusic();
	//			Slider* sliderEventMusic = VolumeOptionGUI::getSliderEventMusic();

	//			if (checkFocus(e, sliderThemeMusic->getButtonRect())) {
	//				handleDragButtonOfSlider(e, sliderThemeMusic);
	//				soundManager->setThemeMusicVolume(sliderThemeMusic->getValueFromSlider());
	//				return;
	//			}

	//			if (checkFocus(e, sliderEventMusic->getButtonRect())) {
	//				handleDragButtonOfSlider(e, sliderEventMusic);
	//				soundManager->setEventMusicVolume(sliderEventMusic->getValueFromSlider());
	//				return;
	//			}

	//			if (checkFocus(e, VolumeOptionGUI::getRectOfBtnBackToMenu())) {
	//				backToMenu();
	//				return;
	//			}
	//		}

	//		if (gui->getTypeGUI() == TypeGUI::REPLAY_RECENT_GAME) {

	//		}

	//		if (gui->getTypeGUI() == TypeGUI::GAME_PLAY) {
	//			if (checkFocus(e, GamePlayGUI::getRectOfBtnSetting())) {
	//				delete gui;
	//				gui = new SettingGUI();
	//				return;
	//			}

	//			if (checkFocus(e, GamePlayGUI::getRectOfBtnUndo())) {
	//				undo();
	//				return;
	//			}

	//			if (checkFocus(e, GamePlayGUI::getRectOfBtnRedo())) {
	//				redo();
	//				return;
	//			}
	//		}

	//		if (gui->getTypeGUI() == TypeGUI::RESULT_NOTICE) {
	//			if (checkFocus(e, MatchResultGUI::getRectOfBtnPlayAgain())) {
	//				delete gui;
	//				gui = new GamePlayGUI();
	//				Board::resetPieces();
	//				return;
	//			}

	//			if (checkFocus(e, MatchResultGUI::getRectOfBtnBackToMenu())) {
	//				backToMenu();
	//				return;
	//			}
	//		}

	//		if (gui->getTypeGUI() == TypeGUI::PROMOTION_NOTICE) {
	//			Pawn* pawn = dynamic_cast<Pawn*>(Board::pieces[dynamic_cast<PromotionNoticeGUI*>(gui)->getIdOfPromotionPiece()]);

	//			if (checkFocus(e, PromotionNoticeGUI::getRectOfBtnQueen()) && pawn) {
	//				// TODO: Promote Queen
	//				delete gui;
	//				gui = new GamePlayGUI();
	//				return;
	//			}

	//			if (checkFocus(e, PromotionNoticeGUI::getRectOfBtnBishop()) && pawn) {
	//				// TODO: Promote Bishop
	//				delete gui;
	//				gui = new GamePlayGUI();
	//				return;
	//			}

	//			if (checkFocus(e, PromotionNoticeGUI::getRectOfBtnKnight()) && pawn) {
	//				// TODO: Promote Knight
	//				delete gui;
	//				gui = new GamePlayGUI();
	//				return;
	//			}

	//			if (checkFocus(e, PromotionNoticeGUI::getRectOfBtnRook()) && pawn) {
	//				// TODO: Promote Rook
	//				delete gui;
	//				gui = new GamePlayGUI();
	//				return;
	//			}
	//		}

	//		if (gui->getTypeGUI() == TypeGUI::SETTINGS) {
	//			if (checkFocus(e, SettingGUI::getRectOfBtnContinue())) {
	//				delete gui;
	//				gui = new GamePlayGUI();
	//				return;
	//			}

	//			if (checkFocus(e, SettingGUI::getRectOfBtnVolumeOption())) {
	//				//TODO:
	//			}

	//			if (checkFocus(e, SettingGUI::getRectOfBtnBackToMenu())) {
	//				backToMenu();
	//				return;
	//			}
	//		}

	//		// TODO:
	//		break;
	//	case SDL_KEYDOWN:
	//		// TODO:
	//		break;
	//	default:
	//		break;
	//	}
	//}*/
}

Coordinate GameManager::getClickedBox(const SDL_Event& e) const {
	int x = e.motion.x;
	int y = e.motion.y;
	GamePlayGUI* gplay = dynamic_cast<GamePlayGUI*>(mainGui);
	if (!gplay) return Coordinate(-1, -1);
	SDL_Rect boardRect = gplay->getRectOfBoard();

	if (x < boardRect.x || y < boardRect.y || x > boardRect.x + boardRect.w || y > boardRect.y + boardRect.h) return Coordinate(-1, -1);

	double widthBox = boardRect.w / Board::XBOXES;
	double heightBox = boardRect.h / Board::YBOXES;

	Coordinate res;
	res.setX((x - boardRect.x) / widthBox);
	res.setY((y - boardRect.y) / heightBox);

	return res;
}

// TODO: return enum; unfinished game, win game, lose game and draw game
MatchResult GameManager::checkMatchStatus() const {
	/*if (board->pieces[0]->getDead()) return MatchResult::PLAYER2_WIN;

	if (board->pieces[16]->getDead()) return MatchResult::PLAYER1_WIN;
	*/
	return MatchResult::PLAYING;
}

// TODO: (current default, white -> first: turn even, black: second -> turn odd;) make it flexible; add music;
void GameManager::handleClickedPiece(const SDL_Event& e) {
	Coordinate c = getClickedBox(e);
	if (c.getX() < 0 && c.getY() < 0) return;

	Piece* piece = Board::getPieceAt(c);
	if (!piece) return;
	std::cout << "Turn:" << turn << std::endl;
	if (piece->getColor() == Color::White && turn % 2 == 1 || piece->getColor() == Color::Black && turn % 2 == 0) return;

	for (int i = 0; i < 32; i++) Board::piecesList[i]->setChosen(false);

	piece->setChosen(true);
	std::cout << "here" << std::endl;
	if (piece->getType() == PieceType::Pawn) std::cout << "right" << std::endl;
}

//TODO: add music
void GameManager::handleClickedHightlightBox(const SDL_Event& e) {
	std::vector<Coordinate> possibleMoves;
	Coordinate c = getClickedBox(e);
	if (c.getX() < 0 && c.getY() < 0) return;

	Piece* chosenPiece = nullptr;
	for (int i = 0; i < 32; i++) {
		if (Board::piecesList[i]->getChosen()) {
			chosenPiece = Board::piecesList[i];
			//history->setInitalState(chosenPiece);
			break;
		}
	}
	std::vector<std::vector<Coordinate>> temp;

	if (!chosenPiece) return;
	temp = chosenPiece->getPossibleMoves(Board::piecesOnBoard);
	possibleMoves.reserve(temp[0].size() + temp[1].size());
	std::copy(temp[0].begin(), temp[0].end(), std::back_inserter(possibleMoves));
	std::copy(temp[1].begin(), temp[1].end(), std::back_inserter(possibleMoves));


	for (auto& move : possibleMoves) {
		if (c == move) {
			Piece* capturedPiece = nullptr;
			capturedPiece = chosenPiece->move(c, Board::piecesOnBoard);
			//history->setCapturedPiece(capturedPiece);
			//capturedPiece->setDead(true);
			chosenPiece->setChosen(false);
			turn++;
			Board::updateBoard();

			break;
		}
	}

	//history->setFinalState(chosenPiece);
	//history->updateData(turn);

	// TODO - check promotion
	//if (checkPromotion(chosenPiece)) {
	//	delete gui;
	//	gui = new PromotionNoticeGUI(chosenPiece->getId());
	//}

	chosenPiece = nullptr;
}

/*
void GameManager::handleDragButtonOfSlider(const SDL_Event& e, Slider* slider) {
	int x = e.motion.x;
	slider->setButtonRectX(x);
}
*/

bool GameManager::checkFocus(const SDL_Event& e, const SDL_Rect& rect) const {
	int x = e.motion.x;
	int y = e.motion.y;

	if (x < rect.x || y < rect.y || x > rect.x + rect.w || y > rect.y + rect.h) return false;

	return true;
}

bool GameManager::checkPromotion(Piece* piece) {
	if (piece->getType() != PieceType::Pawn) return false;

	Coordinate c = piece->getPosition();
	if ((c.getY() == 0 || c.getY() == 7) && !(dynamic_cast<Pawn*>(piece)->getPromotion())) return true;

	return false;
}

/*
// TODO: try catch(maybe in main)
void GameManager::backToMenu() {
	delete mainGui;
	mainGui = new MenuGUI();
}
*/

int GameManager::getValueFromSlider(const SDL_Rect* buttonRect, const SDL_Rect* trackerRect) {
	return (trackerRect->x - buttonRect->x) * 100 / trackerRect->w;
}

void GameManager::undo() {
	/*if (turn <= 0) return;
	turn--;
	std::vector<Piece*> temp = history->getData(turn);
	*(Board::pieces[temp[0]->getId()]) = *temp[0];
	if (temp[2]) *(Board::pieces[temp[2]->getId()]) = *temp[2];*/
}

void GameManager::redo() {
	/*if (turn >= history->getLengthData() - 1) return;
	turn++;
	std::vector<Piece*> temp = history->getData(turn);
	*(Board::pieces[temp[1]->getId()]) = *temp[1];
	if (temp[2]) *(Board::pieces[temp[2]->getId()]) = *temp[2];*/
}


