#include "Pieces.h"

Piece::Piece() {
	Coordinate::Coordinate();
	color = {};
	dead = false;
	chosen = false; 
	imagePath = "";
	texture = nullptr;
	id = 0;
}
Piece::Piece(const Piece& pieces) {
	this->position = pieces.position;
	this->color = pieces.color;
	this->dead = pieces.dead;
	this->chosen = pieces.chosen;
	this->imagePath = pieces.imagePath;
	this->texture = pieces.texture;
	this->id = pieces.id;
}
Piece::Piece(const Coordinate& position, Color color, const std::string& imagePath) {
	this->position = position;
	this->color = color;
	this->imagePath = imagePath;
}
Piece::~Piece() {
	SDL_DestroyTexture(texture);
}

void Piece::setPosition(Coordinate postion) {
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
int Piece::getId() const {
	return this->id;
}

void Piece::loadImage() {

}
void Piece::destroyImage() {

}

Piece& Piece::operator=(const Piece& piece) {
	if (this == &piece) return *this;
	this->position = piece.position;
	this->color = piece.color;
	this->dead = piece.dead;
	this->chosen = piece.chosen;
	this->imagePath = piece.imagePath;
	this->texture = piece.texture;
	this->id = piece.id;
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
	this->castling = king.castling;
}
King::King(const Coordinate& position, Color color, const std::string& pathImage) : Piece(position, color, pathImage) {
	if (this->color == Color::White) {
		this->imagePath = pathToString(Path::kingWhite);
	}
	else {
		this->imagePath = pathToString(Path::kingBlack);
	}
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
Piece* King::move(const Coordinate& c) {
	this->position = c;

	return this;
}
std::vector<Coordinate> King::getPossibleMoves() const {
	std::vector<Coordinate> moves;

	if (this->getColor() == Color::White) {
		Coordinate tmp(this->getPosition().getX() - 1, this->getPosition().getY() - 1);
		int X = tmp.getX();
		int Y = tmp.getY();
		if (X >= 0 && Y >= 0) {
			for (int i = 0; i < 3; i++, Y++) {
				if (Y >= 0 && Y <= _BOARD_WIDTH) {
					moves.push_back(tmp);
				}
			}
		}
		tmp = Coordinate(tmp.getX() + 1, tmp.getY() - 1);
		X = tmp.getX();
		Y = tmp.getY();
		if (X <= _BOARD_HEIGHT && Y >= 0) {
			for (int i = 0; i < 3; i++, Y++) {
				if (Y >= 0 && Y <= _BOARD_WIDTH) {
					moves.push_back(tmp);
				}
			}
		}
		tmp = Coordinate(tmp.getX(), tmp.getY() + 1);
		X = tmp.getX();
		Y = tmp.getY();
		if (Y <= _BOARD_HEIGHT) {
			moves.push_back(tmp);
		}
		tmp = Coordinate(tmp.getX(), tmp.getY() - 1);
		X = tmp.getX();
		Y = tmp.getY();
		if (Y >= 0) {
			moves.push_back(tmp);
		}
	}
	else {
		Coordinate tmp(this->getPosition().getX() - 1, this->getPosition().getY() + 1);
		int X = tmp.getX();
		int Y = tmp.getY();
		if (X >= 0 && X <= _BOARD_HEIGHT) {
			for (int i = 0; i < 3; i++, Y--) {
				if (Y >= 0 && Y <= _BOARD_WIDTH) {
					moves.push_back(tmp);
				}
			}
		}
		tmp = Coordinate(tmp.getX() + 1, tmp.getY() + 1);
		X = tmp.getX();
		Y = tmp.getY();
		if (X >= 0 && X <= _BOARD_HEIGHT) {
			for (int i = 0; i < 3; i++, Y--) {
				if (Y >= 0 && Y <= _BOARD_WIDTH) {
					moves.push_back(tmp);
				}
			}
		}
		tmp = Coordinate(tmp.getX(), tmp.getY() + 1);
		X = tmp.getX();
		Y = tmp.getY();
		if (Y <= _BOARD_HEIGHT) {
			moves.push_back(tmp);
		}
		tmp = Coordinate(tmp.getX(), tmp.getY() - 1);
		X = tmp.getX();
		Y = tmp.getY();
		if (Y >= 0) {
			moves.push_back(tmp);
		}
	}

	return moves;
}
std::string King::getNameClass() const {
	return "King";
}
Piece* King::clone() {
	return new King(*this);
}
void King::performCastling() {
	if (this->getColor() == Color::White && this->getPosition().getX() == 4 && this->getPosition().getY() == 1) {
		this->castling = true;
		this->move(Coordinate(2, 1));
	}
	else if (this->getColor() == Color::Black && this->getPosition().getX() == 4 && this->getPosition().getY() == 8) {
		this->castling = true;
		this->move(Coordinate(2, 8));
	}
}

King& King::operator=(const King& piece) {
	if (this == &piece) return *this;

	*this = piece;
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
}
Queen::~Queen() {

}

Piece* Queen::move(const Coordinate& c) {
	this->position = c;

	return this;
}
std::vector<Coordinate> Queen::getPossibleMoves() const {
	std::vector<Coordinate> moves;

	//x - 1
	Coordinate tmp(this->getPosition().getX() - 1, this->getPosition().getY());
	while (tmp.getX() >= 0) {
		tmp += Coordinate(-1, 0);
		moves.push_back(tmp);
	}

	//x + 1
	tmp = Coordinate(this->getPosition().getX() + 1, this->getPosition().getY());
	while (tmp.getX() <= _BOARD_HEIGHT) {
		tmp += Coordinate(1, 0);
		moves.push_back(tmp);
	}
	
	//y - 1
	tmp = Coordinate(this->getPosition().getX(), this->getPosition().getY() - 1);
	while (tmp.getY() >= 0) {
		tmp += Coordinate(0, -1);
		moves.push_back(tmp);
	}

	//y + 1
	tmp = Coordinate(this->getPosition().getX(), this->getPosition().getY() - 1);
	while (tmp.getY() <= _BOARD_WIDTH) {
		tmp += Coordinate(0, 1);
		moves.push_back(tmp);
	}

	//x + 1, y + 1
	tmp = Coordinate(this->getPosition().getX() + 1, this->getPosition().getY() + 1);
	while (tmp.getX() <= _BOARD_HEIGHT && tmp.getY() <= _BOARD_WIDTH) {
		tmp += Coordinate(1, 1);
		moves.push_back(tmp);
	}

	//x - 1, y - 1
	tmp = Coordinate(this->getPosition().getX() - 1, this->getPosition().getY() - 1);
	while (tmp.getX() >= 0 && tmp.getY() >= 0) {
		tmp += Coordinate(-1, -1);
		moves.push_back(tmp);
	}

	//x - 1, y + 1
	tmp = Coordinate(this->getPosition().getX() - 1, this->getPosition().getY() + 1);
	while (tmp.getX() >= 0 && tmp.getY() <= _BOARD_WIDTH) {
		tmp += Coordinate(-1, 1);
		moves.push_back(tmp);
	}

	//x + 1, y - 1
	tmp = Coordinate(this->getPosition().getX() + 1, this->getPosition().getY() - 1);
	while (tmp.getX() <= _BOARD_HEIGHT && tmp.getY() >= 0) {
		tmp += Coordinate(1, -1);
		moves.push_back(tmp);
	}

	return moves;
}
Piece* Queen::clone() {
	return new Queen(*this);
}
std::string Queen::getNameClass() const {
	return "Queen";
}

Queen& Queen::operator=(const Queen& piece) {
	if (this == &piece) return *this;

	*this = piece;

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
}
Bishop::~Bishop() {

}

Piece* Bishop::move(const Coordinate& c) {
	this->position = c;

	return this;
}
std::vector<Coordinate> Bishop::getPossibleMoves() const {
	std::vector<Coordinate> moves;
	//x + 1, y + 1
	Coordinate tmp(this->getPosition().getX() + 1, this->getPosition().getY() + 1);
	while (tmp.getX() <= _BOARD_HEIGHT && tmp.getY() <= _BOARD_WIDTH) {
		tmp += Coordinate(1, 1);
		moves.push_back(tmp);
	}

	//x - 1, y - 1
	tmp = Coordinate(this->getPosition().getX() - 1, this->getPosition().getY() - 1);
	while (tmp.getX() >= 0 && tmp.getY() >= 0) {
		tmp += Coordinate(-1, -1);
		moves.push_back(tmp);
	}

	//x - 1, y + 1
	tmp = Coordinate(this->getPosition().getX() - 1, this->getPosition().getY() + 1);
	while (tmp.getX() >= 0 && tmp.getY() <= _BOARD_WIDTH) {
		tmp += Coordinate(-1, 1);
		moves.push_back(tmp);
	}

	//x + 1, y - 1
	tmp = Coordinate(this->getPosition().getX() + 1, this->getPosition().getY() - 1);
	while (tmp.getX() <= _BOARD_HEIGHT && tmp.getY() >= 0) {
		tmp += Coordinate(1, -1);
		moves.push_back(tmp);
	}

	return moves;
}
Piece* Bishop::clone() {
	return new Bishop(*this);
}
std::string Bishop::getNameClass() const {
	return "Bishop";
}

Bishop& Bishop::operator=(const Bishop& piece) {
	if (this == &piece) return *this;

	*this = piece;

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
}
Rook::~Rook() {

}

Piece* Rook::move(const Coordinate& c) {
	this->position = c;

	return this;
}
std::vector<Coordinate> Rook::getPossibleMoves() const {
	std::vector<Coordinate> moves;

	//x - 1
	Coordinate tmp(this->getPosition().getX() - 1, this->getPosition().getY());
	while (tmp.getX() >= 0) {
		tmp += Coordinate(-1, 0);
		moves.push_back(tmp);
	}

	//x + 1
	tmp = Coordinate(this->getPosition().getX() + 1, this->getPosition().getY());
	while (tmp.getX() <= _BOARD_HEIGHT) {
		tmp += Coordinate(1, 0);
		moves.push_back(tmp);
	}

	//y - 1
	tmp = Coordinate(this->getPosition().getX(), this->getPosition().getY() - 1);
	while (tmp.getY() >= 0) {
		tmp += Coordinate(0, -1);
		moves.push_back(tmp);
	}

	//y + 1
	tmp = Coordinate(this->getPosition().getX(), this->getPosition().getY() - 1);
	while (tmp.getY() <= _BOARD_WIDTH) {
		tmp += Coordinate(0, 1);
		moves.push_back(tmp);
	}

	return moves;
}
Piece* Rook::clone() {
	return new Rook(*this);
}
std::string Rook::getNameClass() const {
	return "Rook";
}
void Rook::performCastling() {
	if (this->getColor() == Color::White) {
		this->move(Coordinate(1, 3));
	}
	else {
		this->move(Coordinate(8, 3));
	}
}

Rook& Rook::operator=(const Rook& piece) {
	if (this == &piece) return *this;

	*this = piece;

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
}
Knight::~Knight() {

}

Piece* Knight::move(const Coordinate& c) {
	this->position = c;

	return this;
}
std::vector<Coordinate> Knight::getPossibleMoves() const {
	std::vector<Coordinate> moves;

	//x + 1, y - 2
	Coordinate tmp(this->getPosition().getX() + 1, this->getPosition().getY() - 2);
	if (tmp.getX() <= _BOARD_HEIGHT && tmp.getY() >= 0) {
		moves.push_back(tmp);
	}

	//x + 1, y + 2
	tmp = Coordinate(this->getPosition().getX() + 1, this->getPosition().getY() + 2);
	if (tmp.getX() <= _BOARD_HEIGHT && tmp.getY() <= _BOARD_WIDTH) {
		moves.push_back(tmp);
	}

	//x - 1, y + 2
	tmp = Coordinate(this->getPosition().getX() - 1, this->getPosition().getY() + 2);
	if (tmp.getX() >= 0 && tmp.getY() <= _BOARD_WIDTH) {
		moves.push_back(tmp);
	}

	//x - 1, y - 2
	tmp = Coordinate(this->getPosition().getX() - 1, this->getPosition().getY() - 2);
	if (tmp.getX() >= 0 && tmp.getY() >= 0) {
		moves.push_back(tmp);
	}

	//x + 2, y + 1
	tmp = Coordinate(this->getPosition().getX() + 2, this->getPosition().getY() + 1);
	if (tmp.getX() <= _BOARD_HEIGHT && tmp.getY() <= _BOARD_WIDTH) {
		moves.push_back(tmp);
	}

	//x - 2, y + 1
	tmp = Coordinate(this->getPosition().getX() - 2, this->getPosition().getY() + 1);
	if (tmp.getX() >= 0 && tmp.getY() <= _BOARD_WIDTH) {
		moves.push_back(tmp);
	}

	//x + 2, y - 1
	tmp = Coordinate(this->getPosition().getX() + 2, this->getPosition().getY() - 1);
	if (tmp.getX() <= _BOARD_HEIGHT && tmp.getY() >= 0) {
		moves.push_back(tmp);
	}

	//x - 2, y - 1
	tmp = Coordinate(this->getPosition().getX() - 2, this->getPosition().getY() - 1);
	if (tmp.getX() >= 0 && tmp.getY() >= 0) {
		moves.push_back(tmp);
	}

	return moves;
}
std::string Knight::getNameClass() const {
	return "Knight";
}
Piece* Knight::clone() {
	return new Knight(*this);
}

Knight& Knight::operator=(const Knight& piece) {
	if (this == &piece) return *this;

	*this = piece;

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
void Pawn::setFirstMoveFalse() {
	firstMove = false;
}

Piece* Pawn::move(const Coordinate& c) {
	this->position = c;

	return this;
}
std::vector<Coordinate> Pawn::getPossibleMoves() const {
	std::vector<Coordinate> moves;

	if (this->getColor() == Color::White) {
		if (this->firstMove) {
			Coordinate tmp(this->getPosition().getX(), this->getPosition().getY() + 1);
			moves.push_back(tmp);
			tmp = Coordinate(this->getPosition().getX(), this->getPosition().getY() + 2);
			moves.push_back(tmp);

			tmp = Coordinate(this->getPosition().getX() - 1, this->getPosition().getY() + 1);
			moves.push_back(tmp);
			tmp = Coordinate(this->getPosition().getX() + 1, this->getPosition().getY() + 1);
			moves.push_back(tmp);
		}
		else {
			Coordinate tmp(this->getPosition().getX(), this->getPosition().getY() + 1);
			moves.push_back(tmp);
			tmp = Coordinate(this->getPosition().getX() - 1, this->getPosition().getY() + 1);
			moves.push_back(tmp);
			tmp = Coordinate(this->getPosition().getX() + 1, this->getPosition().getY() + 1);
			moves.push_back(tmp);
		}
	}
	else if (this->getColor() == Color::Black) {
		if (this->firstMove) {
			Coordinate tmp(this->getPosition().getX(), this->getPosition().getY() - 1);
			moves.push_back(tmp);
			tmp = Coordinate(this->getPosition().getX(), this->getPosition().getY() - 2);
			moves.push_back(tmp);

			tmp = Coordinate(this->getPosition().getX() - 1, this->getPosition().getY() - 1);
			moves.push_back(tmp);
			tmp = Coordinate(this->getPosition().getX() + 1, this->getPosition().getY() - 1);
			moves.push_back(tmp);
		}
		else {
			Coordinate tmp(this->getPosition().getX(), this->getPosition().getY() - 1);
			moves.push_back(tmp);
			tmp = Coordinate(this->getPosition().getX() - 1, this->getPosition().getY() - 1);
			moves.push_back(tmp);
			tmp = Coordinate(this->getPosition().getX() + 1, this->getPosition().getY() - 1);
			moves.push_back(tmp);
		}
	}

	return moves;
}
std::string Pawn::getNameClass() const {
	return "Pawn";
}
Piece* Pawn::clone() {
	return new Pawn(*this);
}
Piece* Pawn::getPromotion() {
	return this->promotion;
}
void promote(Piece* newPiece, std::string nameClass) {
	if (newPiece->getNameClass() == "Pawn") {
		if (newPiece->getColor() == Color::White) {
			if (newPiece->getPosition().getY() == 8) {
				if (nameClass == "Queen") {
					Coordinate positionTmp = newPiece->getPosition();
					Color colorTmp = newPiece->getColor();
					delete newPiece;
					newPiece = new Queen(positionTmp, colorTmp, pathToString(Path::queenWhite));
				}
				else if (nameClass == "Rook") {
					Coordinate positionTmp = newPiece->getPosition();
					Color colorTmp = newPiece->getColor();
					delete newPiece;
					newPiece = new Rook(positionTmp, colorTmp, pathToString(Path::kingWhite));
				}
				else if (nameClass == "Knight") {
					Coordinate positionTmp = newPiece->getPosition();
					Color colorTmp = newPiece->getColor();
					delete newPiece;
					newPiece = new Knight(positionTmp, colorTmp, pathToString(Path::knightWhite));
				}
				else if (nameClass == "Bishop") {
					Coordinate positionTmp = newPiece->getPosition();
					Color colorTmp = newPiece->getColor();
					delete newPiece;
					newPiece = new Bishop(positionTmp, colorTmp, pathToString(Path::bishopWhite));
				}
			}
		}
		else {
			if (newPiece->getPosition().getY() == 1) {
				if (nameClass == "Queen") {
					Coordinate positionTmp = newPiece->getPosition();
					Color colorTmp = newPiece->getColor();
					delete newPiece;
					newPiece = new Queen(positionTmp, colorTmp, pathToString(Path::queenBlack));
				}
				else if (nameClass == "Rook") {
					Coordinate positionTmp = newPiece->getPosition();
					Color colorTmp = newPiece->getColor();
					delete newPiece;
					newPiece = new Rook(positionTmp, colorTmp, pathToString(Path::kingBlack));
				}
				else if (nameClass == "Knight") {
					Coordinate positionTmp = newPiece->getPosition();
					Color colorTmp = newPiece->getColor();
					delete newPiece;
					newPiece = new Knight(positionTmp, colorTmp, pathToString(Path::knightBlack));
				}
				else if (nameClass == "Bishop") {
					Coordinate positionTmp = newPiece->getPosition();
					Color colorTmp = newPiece->getColor();
					delete newPiece;
					newPiece = new Bishop(positionTmp, colorTmp, pathToString(Path::bishopBlack));
				}
			}
		}
	}
	
}
void Pawn::enPassant() {

}
Pawn& Pawn::operator=(const Pawn& piece) {
	if (this == &piece) return *this;

	*this = piece;
	this->firstMove = piece.firstMove;
	delete this->promotion;
	this->promotion = piece.promotion;

	return *this;
}