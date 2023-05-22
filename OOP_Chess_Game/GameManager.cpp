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
	subGui = nullptr;

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
		handelEvents(); // not here
		render();
		frameTime = SDL_GetTicks() - frameStart;
		std::cout << "FrameTime: " << frameTime << std::endl;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
}

void GameManager::render() {
	SDL_RenderClear(Window::renderer);
	mainGui->render();
	if (mainGui->getGUIType() == GUIType::GAME_PLAY) {
		GamePlayGUI* tempGui = (GamePlayGUI*)mainGui;
		tempGui->renderTurn(turn);
	}
	if (subGui) {
		subGui->render();
		if (subGui->getGUIType() == GUIType::RESULT_NOTICE) {
			MatchResultGUI* temp = (MatchResultGUI*)subGui;
			temp->renderMatchResult(checkWinner());
		}
	}
	SDL_RenderPresent(Window::renderer);
}

// TODO: try-catch
void GameManager::handelEvents() {
	SDL_Event e;

	//check winner
	MatchState matchState = checkWinner();
	if (matchState != MatchState::IN_PLAY) {
		subGui = new MatchResultGUI();
	}

	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			isRunning = false; break;
		case SDL_MOUSEBUTTONDOWN:
			/*
			WHILE ALWAYS FIRST, BLACK SECOND.
			COMPUTER: EVEN TURN => WHITE; ODD TURN => BLACK; IF PLAYER CHOOSE WHITE => COMPUTER CHOOSE FALSE; AND ...
			MAYBE: ADD NEW ATTRIBUTE ""
			if(opponent == Opponent::COMPUTER)
				// CALL API FROM CLASS COMPUTER => CONSIDER TURN IS EVEN OR ODD; CALCULATE MOVE=> COORDINATE, INCREASE TURN, SAVE HISTORY.
			*/
			Coordinate c = getClickedBox(e);
			std::cout << c.getX() << " " << c.getY() << std::endl;
	
			if (subGui) {
				if (subGui->getGUIType() == GUIType::PROMOTION_NOTICE) {
					PromotionGUI* temp = (PromotionGUI*)subGui;
					bool flag = false;
					Pawn* pawn = nullptr;
					for (int i = 0; i < 32; i++) {
						if (checkPromotion(Board::piecesList[i])) {
							pawn =(Pawn*) Board::piecesList[i];
							break;
						}
					}
					
					if (checkFocus(e, temp->getRectOfBtnQueen())) {
						std::cout << "Promote Queen!!!" << std::endl;
						flag = true;
						pawn->promote(PieceType::Queen);
					}
					if (checkFocus(e, temp->getRectOfBtnRook())) {
						std::cout << "Promote Rook!!!" << std::endl;
						flag = true;
						pawn->promote(PieceType::Rook);
					}
					if (checkFocus(e, temp->getRectOfBtnKnight())) {
						std::cout << "Promote Knight!!!" << std::endl;
						flag = true;
						pawn->promote(PieceType::Knight);
					}
					if (checkFocus(e, temp->getRectOfBtnBishop())) {
						std::cout << "Promote Bishop!!!" << std::endl;
						flag = true;
						pawn->promote(PieceType::Bishop);
					}
					if (flag) {
						delete subGui;
						subGui = nullptr;
					}

					std::vector<Piece*> data = history->getData(turn - 1);
					history->setInitalState(data[0]);
					history->setFinalState(pawn);
					history->setCapturedPiece(nullptr);
					history->updateData(turn -1);
				}
				return;
			}

			if (mainGui->getGUIType() == GUIType::GAME_PLAY) {
				handleClickedPiece(e);
				handleClickedHightlightBox(e);

				GamePlayGUI* temp = dynamic_cast<GamePlayGUI*>(mainGui);
				if (checkFocus(e, temp->getRectOfBtnSetting())) {
					std::cout << "Setting button clicked!" << std::endl;
					history->write("history1.bin");
				}
				if (checkFocus(e, temp->getRectOfBtnUndo())) {
					std::cout << "Undo button clicked!" << std::endl;
					undo();
				}
				if (checkFocus(e, temp->getRectOfBtnRedo())) {
					std::cout << "Redo button clicked!" << std::endl;
					redo();
				}
				if (checkFocus(e, temp->getRectOfBtnQuit())) {
					std::cout << "Quit button clicked!" << std::endl;
					history->read("history1.bin");
				}
			}
		}
	}
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
			history->setInitalState(chosenPiece);
			capturedPiece = chosenPiece->move(c, Board::piecesOnBoard);
			chosenPiece->setChosen(false);
			history->setFinalState(chosenPiece);
			history->setCapturedPiece(capturedPiece);
			history->updateData(turn);
			turn++;
			Board::updateBoard();
			break;
		}
	}
	// TODO - check promotion
	if (checkPromotion(chosenPiece)) {
		std::cout << "Promotion!!!" << std::endl;
		subGui = new PromotionGUI();
	}

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

// TODO - Carefully pointer to texture (I call slow change state)
void GameManager::undo() {
	if (turn <= 0) return;

	turn--;
	std::vector<Piece*> temp = history->getData(turn);
	delete Board::piecesList[temp[0]->getID()];
	Board::piecesList[temp[0]->getID()] = temp[0]->clone();
	if (temp[2]) {
		delete Board::piecesList[temp[2]->getID()];
		Board::piecesList[temp[2]->getID()] = temp[2]->clone();
		Board::piecesList[temp[2]->getID()]->setDead(false);
	}

	// case: king performed castling
	if (temp[0]->getType() == PieceType::King && abs(temp[0]->getPosition().getX() - temp[1]->getPosition().getX()) == 2) {
		if (temp[0]->getPosition().getX() > temp[1]->getPosition().getX()) {
			Board::piecesList[temp[0]->getID() + 6]->setPosition(Coordinate(0, temp[0]->getPosition().getY()));
			((Rook*)(Board::piecesList[temp[0]->getID() + 6]))->setFirstMove(true);
		}
		else {
			Board::piecesList[temp[0]->getID() + 7]->setPosition(Coordinate(7, temp[0]->getPosition().getY()));
			((Rook*)(Board::piecesList[temp[0]->getID() + 7]))->setFirstMove(true);
		}
	}
	for (auto& e : Board::piecesList) e->setChosen(false);
	Board::updateBoard();
}

// TODO - Carefully pointer to texture (I call quick change state)
void GameManager::redo() {
	if (turn >= history->getLengthData()) return;

	std::vector<Piece*> temp = history->getData(turn);
	delete Board::piecesList[temp[1]->getID()];
	Board::piecesList[temp[1]->getID()] = temp[1]->clone();
	if (temp[2]) {
		delete Board::piecesList[temp[2]->getID()];
		Board::piecesList[temp[2]->getID()] = temp[2]->clone();
	}

	// case: king performed castling
	if (temp[0]->getType() == PieceType::King && abs(temp[0]->getPosition().getX() - temp[1]->getPosition().getX()) == 2) {
		if (temp[0]->getPosition().getX() > temp[1]->getPosition().getX()) {
			Board::piecesList[temp[1]->getID() + 6]->setPosition(Coordinate(2, temp[1]->getPosition().getY()));
			((Rook*)(Board::piecesList[temp[1]->getID() + 6]))->setFirstMove(false);
		}
		else {
			Board::piecesList[temp[1]->getID() + 7]->setPosition(Coordinate(4, temp[1]->getPosition().getY()));
			((Rook*)(Board::piecesList[temp[1]->getID() + 7]))->setFirstMove(false);
		}
	}

	turn++;
	for (auto& e : Board::piecesList) e->setChosen(false);
	Board::updateBoard();
}

MatchState GameManager::checkWinner() {
	if (turn % 2 == 0) {
		// this is turn of white pieces	
		King* king = (King*)(Board::piecesList[0]);
		bool kingChosen = king->getChosen();
		int cnt = 0;
		for (int i = 0; i < 16; i++) {
			if (Board::piecesList[i]->getDead()) continue;
			bool pieceChosen = Board::piecesList[i]->getChosen();
			Board::piecesList[i]->setChosen(true);
			std::vector<std::vector<Coordinate>> temp = Board::piecesList[i]->getPossibleMoves(Board::piecesOnBoard);
			cnt += temp[0].size() + temp[1].size();
			Board::piecesList[i]->setChosen(pieceChosen);
		}
		
		king->setChosen(true);
		if (cnt == 0) {
			if (king->checkmate(king->getPosition(), Board::piecesOnBoard)) return MatchState::BLACK_WIN;
			else return MatchState::DRAW;
		}
		king->setChosen(kingChosen);
	}
	else {
		// this is turn of black pieces	
		King* king = (King*)(Board::piecesList[16]);
		bool kingChosen = king->getChosen();
		int cnt = 0;
		for (int i = 16; i < 32; i++) {
			if (Board::piecesList[i]->getDead()) continue;
			bool pieceChosen = Board::piecesList[i]->getChosen();
			Board::piecesList[i]->setChosen(true);
			std::vector<std::vector<Coordinate>> temp = Board::piecesList[i]->getPossibleMoves(Board::piecesOnBoard);
			cnt += temp[0].size() + temp[1].size();
			Board::piecesList[i]->setChosen(pieceChosen);
		}

		king->setChosen(true);
		if (cnt == 0) {
			if (king->checkmate(king->getPosition(), Board::piecesOnBoard)) return MatchState::WHITE_WIN;
			else return MatchState::DRAW;
		}
		king->setChosen(kingChosen);
	}

	return MatchState::IN_PLAY;
}

