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
}
Piece::~Piece() {
	SDL_DestroyTexture(texture);
	texture = nullptr;
	tableMove.clear();
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
PieceType Piece::getType() const {
	return this->type;
}
Texture* Piece::getTexture() {
	return this->texture;
}
void Piece::loadImage(SDL_Renderer* renderer) {
	SDL_Surface* img = IMG_Load(this->pathImage.c_str());
	if (!img) {
		std::cout << "Can't load\n";
	}
	SDL_Texture* gTexture = SDL_CreateTextureFromSurface(renderer, img);
	this->texture = gTexture;
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

Piece* Pawn::clone() {
	return new Pawn(*this);
}
Piece* Pawn::getPromotion() {
	return this->promotion;
}
void promote(Piece* newPiece, PieceType& type) {
	if (newPiece->getType() == PieceType::Pawn) {
		if (newPiece->getColor() == Color::White) {
			if (newPiece->getPosition().getY() == 8) {
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
			if (newPiece->getPosition().getY() == 1) {
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
