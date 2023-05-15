#include "Pieces.h"

Piece::Piece() {
	Coordinate::Coordinate();
	color = {};
	dead = false;
	chosen = false; 
	imagePath = "";
	texture = nullptr;
	type = {};
}
Piece::Piece(const Piece& pieces) {
	this->position = pieces.position;
	this->color = pieces.color;
	this->dead = pieces.dead;
	this->chosen = pieces.chosen;
	this->imagePath = pieces.imagePath;
	this->texture = pieces.texture;
	this->type = pieces.type;
	this->tableMove = pieces.tableMove;
}
Piece::Piece(const Coordinate& position, Color color, const std::string& imagePath) {
	this->position = position;
	this->color = color;
	this->imagePath = imagePath;

	SDL_Surface* img = IMG_Load(this->imagePath.c_str());
	if (!img) {
		throw std::string("Can't load ") + imagePath;
	}
	SDL_Texture* gTexture = SDL_CreateTextureFromSurface(Window::renderer, img);
	this->texture = gTexture;
	SDL_FreeSurface(img);
}
Piece::~Piece() {
	SDL_DestroyTexture(texture);
	texture = nullptr;
	tableMove.clear();
}

void Piece::setPosition(Coordinate position) {
	this->position = position;
}
void Piece::setColor(Color color) {
	this->color = color;
}
void Piece::setDead(bool dead) {
	this->dead = dead;
}
void Piece::setChosen(bool chosen) {
	this->chosen = chosen;
}

Coordinate Piece::getPosition() const {
	return this->position;
}
Color Piece::getColor() const {
	return this->color;
}
bool Piece::getDead() const {
	return this->dead;
}
bool Piece::getChosen() const {
	return this->chosen;
}
PieceType Piece::getType() const {
	return this->type;
}
SDL_Texture* Piece::getTexture() {
	return this->texture;
}
void Piece::loadImage(SDL_Renderer* renderer) {
	SDL_Surface* img = IMG_Load(this->imagePath.c_str());
	if (!img) {
		throw std::string("Can't load ") + imagePath;
	}
	SDL_Texture* gTexture = SDL_CreateTextureFromSurface(renderer, img);
	this->texture = gTexture;
	SDL_FreeSurface(img);
}

Piece& Piece::operator=(const Piece& piece) {
	if (this == &piece) return *this;
	this->position = piece.position;
	this->color = piece.color;
	this->dead = piece.dead;
	this->chosen = piece.chosen;
	this->imagePath = piece.imagePath;
	this->texture = piece.texture;
	this->type = piece.type;
	return *this;
}

//--------------------------------------------------------------------------------------------------
King::King() {
	castling = false;
}
King::King(const King& king) : Piece(king) {
	if (this->color == Color::White) {
		this->imagePath = pathToString(Path::kingWhite);
	}
	else {
		this->imagePath = pathToString(Path::kingBlack);
	}
	this->type = PieceType::King;
	this->castling = king.castling;
}
King::King(const Coordinate& position, Color color, const std::string& pathImage) : Piece(position, color, pathImage) {
	if (this->color == Color::White) {
		this->imagePath = pathToString(Path::kingWhite);
	}
	else {
		this->imagePath = pathToString(Path::kingBlack);
	}
	this->type = PieceType::King;
	this->dead = false;
	this->chosen = false;
	this->castling = false;
}
King::~King() {
	
}

void King::setCastling() {
	this->castling = !this->castling;
}
bool King::getCastling() const {
	return this->castling;
}
Piece* King::move(const Coordinate& c, std::vector<std::vector<Piece*>> board) {
	if (!board[c.getX()][c.getY()]) {
		this->setPosition(c);
	}
	else {
		if (this->getColor() != board[c.getX()][c.getY()]->getColor()) {
			this->setPosition(c);
			board[c.getX()][c.getY()]->setDead(true);
		}
	}

	return this;
}
std::vector<Coordinate> King::getPossibleMoves(std::vector<std::vector<Piece*>> board) const {
	std::vector<Coordinate> moves;
	Coordinate tmp(this->getPosition().getX(), this->getPosition().getY());

	//x - 1, y - 1
	int X = tmp.getX() - 1;
	int Y = tmp.getY() - 1;
	if (X >= 0 && Y >= 0) {
		if (!board[X][Y] || this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
		}
	}
	//x + 1, y - 1
	X = tmp.getX() + 1;
	Y = tmp.getY() - 1;
	if (X <= _BOARD_HEIGHT && Y >= 0) {
		if (!board[X][Y] || this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
		}
	}
	//x - 1, y + 1
	X = tmp.getX() - 1;
	Y = tmp.getY() + 1;
	if (X >= 0 && Y <= _BOARD_WIDTH) {
		if (!board[X][Y] || this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
		}
	}
	//x + 1, y + 1
	X = tmp.getX() + 1;
	Y = tmp.getY() + 1;
	if (X <= _BOARD_HEIGHT && Y <= _BOARD_WIDTH) {
		if (!board[X][Y] || this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
		}
	}
	//x + 1
	X = tmp.getX() + 1;
	Y = tmp.getY();
	if (X <= _BOARD_HEIGHT) {
		if (!board[X][Y] || this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
		}
	}
	//x - 1
	X = tmp.getX() - 1;
	Y = tmp.getY();
	if (X >= 0) {
		if (!board[X][Y] || this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
		}
	}
	//y + 1
	X = tmp.getX();
	Y = tmp.getY() + 1;
	if (Y <= _BOARD_WIDTH) {
		if (!board[X][Y] || this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
		}
	}
	//y - 1
	X = tmp.getX();
	Y = tmp.getY() - 1;
	if (Y >= 0) {
		if (!board[X][Y] || this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
		}
	}
	
	return moves;
}
Piece* King::clone() {
	return new King(*this);
}
void King::performCastling() {
	if (this->getColor() == Color::White && this->getPosition().getX() == 3 && this->getPosition().getY() == 0) {
		this->castling = true;
		this->setPosition(Coordinate(1, 0));
	}
	else if (this->getColor() == Color::Black && this->getPosition().getX() == 3 && this->getPosition().getY() == 7) {
		this->castling = true;
		this->setPosition(Coordinate(1, 7));
	}
}

King& King::operator=(const King& piece) {
	if (this == &piece) return *this;

	this->position = piece.position;
	this->color = piece.color;
	this->dead = piece.dead;
	this->chosen = piece.chosen;
	this->imagePath = piece.imagePath;
	this->texture = piece.texture;
	this->type = piece.type;
	this->castling = piece.castling;

	return *this;
}

//--------------------------------------------------------------------------------------------------
Queen::Queen() {

}
Queen::Queen(const Queen& queen) : Piece(queen) {
	if (this->color == Color::White) {
		this->imagePath = pathToString(Path::queenWhite);
	}
	else {
		this->imagePath = pathToString(Path::queenBlack);
	}
	this->type = PieceType::Queen;
}
Queen::Queen(const Coordinate& position, Color color, const std::string& pathImage) : Piece(position, color, pathImage) {
	if (this->color == Color::White) {
		this->imagePath = pathToString(Path::queenWhite);
	}
	else {
		this->imagePath = pathToString(Path::queenBlack);
	}
	this->dead = false;
	this->chosen = false;
	this->type = PieceType::Queen;
}
Queen::~Queen() {

}

Piece* Queen::move(const Coordinate& c, std::vector<std::vector<Piece*>> board) {
	if (!board[c.getX()][c.getY()]) {
		this->setPosition(c);
	}
	else {
		if (this->getColor() != board[c.getX()][c.getY()]->getColor()) {
			this->setPosition(c);
			board[c.getX()][c.getY()]->setDead(true);
		}
	}

	return this;
}
std::vector<Coordinate> Queen::getPossibleMoves(std::vector<std::vector<Piece*>> board) const {
	std::vector<Coordinate> moves;
	Coordinate tmp(this->getPosition().getX(), this->getPosition().getY());
	//x - 1
	int X = tmp.getX() - 1;
	int Y = tmp.getY();
	while (X >= 0) {
		if (!board[X][Y]) {
			moves.push_back(Coordinate(X, Y));
			X--;
		}
		else if (this->getColor() !=  board[X][Y]->getColor()) { 
			moves.push_back(Coordinate(X, Y));
			break; 
		}
		else { break; }
	}

	//x + 1
	X = tmp.getX() + 1;
	Y = tmp.getY();
	while (X <= _BOARD_HEIGHT) {
		if (!board[X][Y]) {
			moves.push_back(Coordinate(X, Y));
			X++;
		}
		else if (this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
			break;
		}
		else { break; }
	}
	
	//y - 1
	X = tmp.getX();
	Y = tmp.getY() - 1;
	while (Y >= 0) {
		if (!board[X][Y]) {
			moves.push_back(Coordinate(X, Y));
			Y--;
		}
		else if (this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
			break;
		}
		else { break; }
	}

	//y + 1
	X = tmp.getX();
	Y = tmp.getY() + 1;
	while (Y <= _BOARD_WIDTH) {
		if (!board[X][Y]) {
			moves.push_back(Coordinate(X, Y));
			Y++;
		}
		else if (this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
			break;
		}
		else { break; }
	}

	//x + 1, y + 1
	X = tmp.getX() + 1;
	Y = tmp.getY() + 1;
	while (X <= _BOARD_HEIGHT && Y <= _BOARD_WIDTH) {
		if (!board[X][Y]) {
			moves.push_back(Coordinate(X, Y));
			X++;
			Y++;
		}
		else if (this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
			break;
		}
		else { break; }
	}

	//x - 1, y - 1
	X = tmp.getX() - 1;
	Y = tmp.getY() - 1;
	while (X >= 0 && Y >= 0) {
		if (!board[X][Y]) {
			moves.push_back(Coordinate(X, Y));
			X--;
			Y--;
		}
		else if (this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
			break;
		}
		else { break; }
	}

	//x - 1, y + 1
	X = tmp.getX() - 1;
	Y = tmp.getY() + 1;	
	while (X >= 0 && Y <= _BOARD_WIDTH) {
		if (!board[X][Y]) {
			moves.push_back(Coordinate(X, Y));
			X--;
			Y++;
		}
		else if (this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
			break;
		}
		else { break; }
	}

	//x + 1, y - 1
	X = tmp.getX() + 1;
	Y = tmp.getY() - 1;	
	while (X <= _BOARD_HEIGHT && Y >= 0) {
		if (!board[X][Y]) {
			moves.push_back(Coordinate(X, Y));
			X++;
			Y--;
		}
		else if (this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
			break;
		}
		else { break; }
	}

	return moves;
}
Piece* Queen::clone() {
	return new Queen(*this);
}

Queen& Queen::operator=(const Queen& piece) {
	if (this == &piece) return *this;

	this->position = piece.position;
	this->color = piece.color;
	this->dead = piece.dead;
	this->chosen = piece.chosen;
	this->imagePath = piece.imagePath;
	this->texture = piece.texture;
	this->type = piece.type;

	return *this;
}

//--------------------------------------------------------------------------------
Bishop::Bishop() {

}
Bishop::Bishop(const Bishop& bishop) : Piece(bishop) {
	if (this->color == Color::White) {
		this->imagePath = pathToString(Path::bishopWhite);
	}
	else {
		this->imagePath = pathToString(Path::bishopBlack);
	}
	this->type = PieceType::Bishop;
}
Bishop::Bishop(const Coordinate& position, Color color, const std::string& pathImage) : Piece(position, color, pathImage) {
	if (this->color == Color::White) {
		this->imagePath = pathToString(Path::bishopWhite);
	}
	else {
		this->imagePath = pathToString(Path::bishopBlack);
	}
	this->dead = false;
	this->chosen = false;
	this->type = PieceType::Bishop;
}
Bishop::~Bishop() {

}

Piece* Bishop::move(const Coordinate& c, std::vector<std::vector<Piece*>> board) {
	if (!board[c.getX()][c.getY()]) {
		this->setPosition(c);
	}
	else {
		if (this->getColor() != board[c.getX()][c.getY()]->getColor()) {
			this->setPosition(c);
			board[c.getX()][c.getY()]->setDead(true);
		}
	}

	return this;
}
std::vector<Coordinate> Bishop::getPossibleMoves(std::vector<std::vector<Piece*>> board) const {
	std::vector<Coordinate> moves;
	Coordinate tmp(this->getPosition().getX(), this->getPosition().getY());

	//x + 1, y + 1
	int X = tmp.getX() + 1;
	int Y = tmp.getY() + 1;
	while (X <= _BOARD_HEIGHT && Y <= _BOARD_WIDTH) {
		if (!board[X][Y]) {
			moves.push_back(Coordinate(X, Y));
			X++;
			Y++;
		}
		else if (this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
			break;
		}
		else { break; }
	}

	//x - 1, y - 1
	X = tmp.getX() - 1;
	Y = tmp.getY() - 1;
	while (X >= 0 && Y >= 0) {
		if (!board[X][Y]) {
			moves.push_back(Coordinate(X, Y));
			X--;
			Y--;
		}
		else if (this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
			break;
		}
		else { break; }
	}

	//x - 1, y + 1
	X = tmp.getX() - 1;
	Y = tmp.getY() + 1;
	while (X >= 0 && Y <= _BOARD_WIDTH) {
		if (!board[X][Y]) {
			moves.push_back(Coordinate(X, Y));
			X--;
			Y++;
		}
		else if (this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
			break;
		}
		else { break; }
	}

	//x + 1, y - 1
	X = tmp.getX() + 1;
	Y = tmp.getY() - 1;
	while (X <= _BOARD_HEIGHT && Y >= 0) {
		if (!board[X][Y]) {
			moves.push_back(Coordinate(X, Y));
			X++;
			Y--;
		}
		else if (this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
			break;
		}
		else { break; }
	}

	return moves;
}
Piece* Bishop::clone() {
	return new Bishop(*this);
}

Bishop& Bishop::operator=(const Bishop& piece) {
	if (this == &piece) return *this;

	this->position = piece.position;
	this->color = piece.color;
	this->dead = piece.dead;
	this->chosen = piece.chosen;
	this->imagePath = piece.imagePath;
	this->texture = piece.texture;
	this->type = piece.type;

	return *this;
}
//----------------------------------------------------------------------------------
Rook::Rook() {

}
Rook::Rook(const Rook& rook) : Piece(rook) {
	if (this->color == Color::White) {
		this->imagePath = pathToString(Path::rookWhite);
	}
	else {
		this->imagePath = pathToString(Path::rookBlack);
	}
	this->type = PieceType::Rook;
}
Rook::Rook(const Coordinate& position, Color color, const std::string& pathImage) : Piece(position, color, pathImage) {
	if (this->color == Color::White) {
		this->imagePath = pathToString(Path::rookWhite);
	}
	else {
		this->imagePath = pathToString(Path::rookBlack);
	}
	this->dead = false;
	this->chosen = false;
	this->type = PieceType::Rook;
}
Rook::~Rook() {

}

Piece* Rook::move(const Coordinate& c, std::vector<std::vector<Piece*>> board) {
	if (!board[c.getX()][c.getY()]) {
		this->setPosition(c);
	}
	else {
		if (this->getColor() != board[c.getX()][c.getY()]->getColor()) {
			this->setPosition(c);
			board[c.getX()][c.getY()]->setDead(true);
		}
	}

	return this;
}
std::vector<Coordinate> Rook::getPossibleMoves(std::vector<std::vector<Piece*>> board) const {
	std::vector<Coordinate> moves;
	Coordinate tmp(this->getPosition().getX(), this->getPosition().getY());

	//x - 1
	int X = tmp.getX() - 1;
	int Y = tmp.getY();
	while (X >= 0) {
		if (!board[X][Y]) {
			moves.push_back(Coordinate(X, Y));
			X--;
		}
		else if (this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
			break;
		}
		else { break; }
	}

	//x + 1
	X = tmp.getX() + 1;
	Y = tmp.getY();
	while (X <= _BOARD_HEIGHT) {
		if (!board[X][Y]) {
			moves.push_back(Coordinate(X, Y));
			X++;
		}
		else if (this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
			break;
		}
		else { break; }
	}

	//y - 1
	X = tmp.getX();
	Y = tmp.getY() - 1;	
	while (Y >= 0) {
		if (!board[X][Y]) {
			moves.push_back(Coordinate(X, Y));
			Y--;
		}
		else if (this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
			break;
		}
		else { break; }
	}

	//y + 1
	X = tmp.getX();
	Y = tmp.getY() + 1;
	while (Y <= _BOARD_WIDTH) {
		if (!board[X][Y]) {
			moves.push_back(Coordinate(X, Y));
			Y++;
		}
		else if (this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
			break;
		}
		else { break; }
	}

	return moves;
}
Piece* Rook::clone() {
	return new Rook(*this);
}
void Rook::performCastling() {
	if (this->getColor() == Color::White) {
		this->setPosition(Coordinate(2, 0));
	}
	else {
		this->setPosition(Coordinate(2, 7));
	}
}

Rook& Rook::operator=(const Rook& piece) {
	if (this == &piece) return *this;

	this->position = piece.position;
	this->color = piece.color;
	this->dead = piece.dead;
	this->chosen = piece.chosen;
	this->imagePath = piece.imagePath;
	this->texture = piece.texture;
	this->type = piece.type;

	return *this;
}
//------------------------------------------------------------------------------
Knight::Knight() {

}
Knight::Knight(const Knight& knight) : Piece(knight) {
	if (this->color == Color::White) {
		this->imagePath = pathToString(Path::knightWhite);
	}
	else {
		this->imagePath = pathToString(Path::knightBlack);
	}	
	this->type = PieceType::Knight;
}
Knight::Knight(const Coordinate& position, Color color, const std::string& pathImage) : Piece(position, color, pathImage) {
	if (this->color == Color::White) {
		this->imagePath = pathToString(Path::knightWhite);
	}
	else {
		this->imagePath = pathToString(Path::knightBlack);
	}
	this->dead = false;
	this->chosen = false;
	this->type = PieceType::Knight;
}
Knight::~Knight() {

}

Piece* Knight::move(const Coordinate& c, std::vector<std::vector<Piece*>> board) {
	if (!board[c.getX()][c.getY()]) {
		this->setPosition(c);
	}
	else {
		if (this->getColor() != board[c.getX()][c.getY()]->getColor()) {
			this->setPosition(c);
			board[c.getX()][c.getY()]->setDead(true);
		}
	}

	return this;
}
std::vector<Coordinate> Knight::getPossibleMoves(std::vector<std::vector<Piece*>> board) const {
	std::vector<Coordinate> moves;
	Coordinate tmp(this->getPosition().getX(), this->getPosition().getY());

	//x + 1, y - 2
	int X = tmp.getX() + 1;
	int Y = tmp.getY() - 2;
	if (X <= _BOARD_HEIGHT && Y >= 0) {
		if (!board[X][Y] || this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
		}
	}

	//x + 1, y + 2
	X = tmp.getX() + 1;
	Y = tmp.getY() + 2;
	if (X <= _BOARD_HEIGHT && Y <= _BOARD_WIDTH) {
		if (!board[X][Y] || this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
		}
	}

	//x - 1, y + 2
	X = tmp.getX() - 1;
	Y = tmp.getY() + 2;

	if (X >= 0 && Y <= _BOARD_WIDTH) {
		if (!board[X][Y] || this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
		}
	}

	//x - 1, y - 2
	X = tmp.getX() - 1;
	Y = tmp.getY() - 2;
	if (X >= 0 && Y >= 0) {
		if (!board[X][Y] || this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
		}
	}

	//x + 2, y + 1
	X = tmp.getX() + 2;
	Y = tmp.getY() + 1;

	if (X <= _BOARD_HEIGHT && Y <= _BOARD_WIDTH) {
		if (!board[X][Y] || this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
		}
	}

	//x - 2, y + 1
	X = tmp.getX() - 2;
	Y = tmp.getY() + 1;
	if (X >= 0 && Y <= _BOARD_WIDTH) {
		if (!board[X][Y] || this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
		}
	}
	//x + 2, y - 1
	X = tmp.getX() + 2;
	Y = tmp.getY() - 1;
	if (X <= _BOARD_HEIGHT && Y >= 0) {
		if (!board[X][Y] || this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
		}
	}
	//x - 2, y - 1
	X = tmp.getX() - 2;
	Y = tmp.getY() - 1;

	if (X >= 0 && Y >= 0) {
		if (!board[X][Y] || this->getColor() != board[X][Y]->getColor()) {
			moves.push_back(Coordinate(X, Y));
		}
	}

	return moves;
}
Piece* Knight::clone() {
	return new Knight(*this);
}

Knight& Knight::operator=(const Knight& piece) {
	if (this == &piece) return *this;

	this->position = piece.position;
	this->color = piece.color;
	this->dead = piece.dead;
	this->chosen = piece.chosen;
	this->imagePath = piece.imagePath;
	this->texture = piece.texture;
	this->type = piece.type;

	return *this;
}

//---------------------------------------------------------------------------
Pawn::Pawn() {
	promotion = nullptr;
	firstMove = true;
}
Pawn::Pawn(const Pawn& pawn) : Piece(pawn) {
	if (this->color == Color::White) {
		this->imagePath = pathToString(Path::pawnWhite);
	}
	else {
		this->imagePath = pathToString(Path::pawnBlack);
	}
	this->type = PieceType::Pawn;
	this->promotion = pawn.promotion;
	delete this->promotion;
	this->firstMove = pawn.firstMove;
}
Pawn::Pawn(const Coordinate& position, Color color, const std::string& pathImage) : Piece(position, color, pathImage) {
	if (this->color == Color::White) {
		this->imagePath = pathToString(Path::pawnWhite);
	}
	else {
		this->imagePath = pathToString(Path::pawnBlack);
	}
	this->type = PieceType::Pawn;
	this->dead = false;
	this->chosen = false;
	promotion = nullptr;
	firstMove = true;
}
Pawn::~Pawn() {
	delete promotion;
}

Piece* Pawn::getPromotion() const {
	return this->promotion;
}
bool Pawn::getFirstMove() {
	return this->firstMove;
}
void Pawn::setFirstMove(bool firstMove) {
	this->firstMove = firstMove;
}

Piece* Pawn::move(const Coordinate& c, std::vector<std::vector<Piece*>> board) {
	if (this->getFirstMove()) {
		this->setFirstMove(false);
	}
	if (!board[c.getX()][c.getY()]) {
		this->setPosition(c);
	}
	else {
		if (this->getColor() != board[c.getX()][c.getY()]->getColor()) {
			this->setPosition(c);
			board[c.getX()][c.getY()]->setDead(true);
		}
	}

	return this;
}
std::vector<Coordinate> Pawn::getPossibleMoves(std::vector<std::vector<Piece*>> board) const {
	std::vector<Coordinate> moves;
	Coordinate tmp(this->getPosition().getX(), this->getPosition().getY());
	int X = tmp.getX();
	int Y = tmp.getY();

	if (this->getColor() == Color::White) {
		if (Y == _BOARD_WIDTH) {
			return moves;
		}
		if (this->firstMove) {
			moves.push_back(Coordinate(X, Y + 1));
			moves.push_back(Coordinate(X, Y + 2));

			if (Y < _BOARD_WIDTH) {
				if (X < _BOARD_HEIGHT) {
					if (board[X + 1][Y + 1] != nullptr && board[X + 1][Y + 1]->getColor() == Color::Black) {
						moves.push_back(Coordinate(X + 1, Y + 1));
					}
				}
				if (X > 0) {
					if (board[X - 1][Y + 1] != nullptr && board[X - 1][Y + 1]->getColor() == Color::Black) {
						moves.push_back(Coordinate(X - 1, Y + 1));
					}
				}			
			}
		}
		else {
			if (Y < _BOARD_WIDTH) {
				if (!board[X][Y + 1]) {
					moves.push_back(Coordinate(X, Y + 1));
				}
			}
			if (Y <= _BOARD_WIDTH) {
				if (X < _BOARD_HEIGHT) {
					if (board[X + 1][Y + 1] != nullptr && board[X + 1][Y + 1]->getColor() == Color::Black) {
						moves.push_back(Coordinate(X + 1, Y + 1));
					}
				}
				if (X > 0) {
					if (board[X - 1][Y + 1] != nullptr && board[X - 1][Y + 1]->getColor() == Color::Black) {
						moves.push_back(Coordinate(X - 1, Y + 1));
					}
				}
			}
		}
	}
	else if (this->getColor() == Color::Black) {
		if (Y == 0) {
			return moves;
		}
		if (this->firstMove) {
			moves.push_back(Coordinate(X, Y - 1));	
			moves.push_back(Coordinate(X, Y - 2));

			if (Y > 0) {
				if (X < _BOARD_HEIGHT) {
					if (board[X + 1][Y - 1] != nullptr && board[X + 1][Y - 1]->getColor() == Color::White) {
						moves.push_back(Coordinate(X + 1, Y - 1));
					}
				}
				if (X > 0) {
					if (board[X - 1][Y - 1] != nullptr && board[X - 1][Y - 1]->getColor() == Color::White) {
						moves.push_back(Coordinate(X - 1, Y - 1));
					}
				}
			}
		}
		else {
			if (Y > 0) {
				if (!board[X][Y - 1]) {
					moves.push_back(Coordinate(X, Y - 1));
				}
			}

			if (Y > 0) {
				if (X < _BOARD_HEIGHT) {
					if (board[X + 1][Y - 1] != nullptr && board[X + 1][Y - 1]->getColor() == Color::White) {
						moves.push_back(Coordinate(X + 1, Y - 1));
					}
				}
				if (X > 0) {
					if (board[X - 1][Y - 1] != nullptr && board[X - 1][Y - 1]->getColor() == Color::White) {
						moves.push_back(Coordinate(X - 1, Y - 1));
					}
				}
			}
		}
	}

	return moves;
}

Piece* Pawn::clone() {
	return new Pawn(*this);
}
Piece* Pawn::getPromotion() {
	return this->promotion;
}
void promote(Piece* newPiece, PieceType& type) {
	if (newPiece->getType() == PieceType::Pawn) {
		if (newPiece->getColor() == Color::White) {
			if (newPiece->getPosition().getY() == 7) {
				if (type == PieceType::Queen) {
					Coordinate positionTmp = newPiece->getPosition();
					Color colorTmp = newPiece->getColor();
					delete newPiece;
					newPiece = new Queen(positionTmp, colorTmp, pathToString(Path::queenWhite));
				}
				else if (type == PieceType::Rook) {
					Coordinate positionTmp = newPiece->getPosition();
					Color colorTmp = newPiece->getColor();
					delete newPiece;
					newPiece = new Rook(positionTmp, colorTmp, pathToString(Path::rookWhite));
				}
				else if (type == PieceType::Knight) {
					Coordinate positionTmp = newPiece->getPosition();
					Color colorTmp = newPiece->getColor();
					delete newPiece;
					newPiece = new Knight(positionTmp, colorTmp, pathToString(Path::knightWhite));
				}
				else if (type == PieceType::Bishop) {
					Coordinate positionTmp = newPiece->getPosition();
					Color colorTmp = newPiece->getColor();
					delete newPiece;
					newPiece = new Bishop(positionTmp, colorTmp, pathToString(Path::bishopWhite));
				}
			}
		}
		else {
			if (newPiece->getPosition().getY() == 0) {
				if (type == PieceType::Queen) {
					Coordinate positionTmp = newPiece->getPosition();
					Color colorTmp = newPiece->getColor();
					delete newPiece;
					newPiece = new Queen(positionTmp, colorTmp, pathToString(Path::queenBlack));
				}
				else if (type == PieceType::Rook) {
					Coordinate positionTmp = newPiece->getPosition();
					Color colorTmp = newPiece->getColor();
					delete newPiece;
					newPiece = new Rook(positionTmp, colorTmp, pathToString(Path::rookBlack));
				}
				else if (type == PieceType::Knight) {
					Coordinate positionTmp = newPiece->getPosition();
					Color colorTmp = newPiece->getColor();
					delete newPiece;
					newPiece = new Knight(positionTmp, colorTmp, pathToString(Path::knightBlack));
				}
				else if (type == PieceType::Bishop) {
					Coordinate positionTmp = newPiece->getPosition();
					Color colorTmp = newPiece->getColor();
					delete newPiece;
					newPiece = new Bishop(positionTmp, colorTmp, pathToString(Path::bishopBlack));
				}
			}
		}
	}
	
}
void Pawn::enPassant(Pawn& enemy) {
	if (enemy.getFirstMove()) {
		if (this->getPosition().getY() == enemy.getPosition().getY() && this->getPosition().getX() == enemy.getPosition().getX() + 1) {
			enemy.setDead(true);
			if (this->getColor() == Color::White) {
				this->setPosition(Coordinate(this->getPosition().getX() - 1, this->getPosition().getY() + 1));
			}
			else {
				this->setPosition(Coordinate(this->getPosition().getX() + 1, this->getPosition().getY() - 1));
			}
		}
		else if (this->getPosition().getY() == enemy.getPosition().getY() && this->getPosition().getX() == enemy.getPosition().getX() - 1) {
			enemy.setDead(true);
			if (this->getColor() == Color::White) {
				this->setPosition(Coordinate(this->getPosition().getX() + 1, this->getPosition().getY() + 1));
			}
			else {
				this->setPosition(Coordinate(this->getPosition().getX() - 1, this->getPosition().getY() - 1));
			}
		}
	}
}
Pawn& Pawn::operator=(const Pawn& piece) {
	if (this == &piece) return *this;

	this->position = piece.position;
	this->color = piece.color;
	this->dead = piece.dead;
	this->chosen = piece.chosen;
	this->imagePath = piece.imagePath;
	this->texture = piece.texture;
	this->type = piece.type;
	this->firstMove = piece.firstMove;
	delete this->promotion;
	this->promotion = piece.promotion;

	return *this;
}
