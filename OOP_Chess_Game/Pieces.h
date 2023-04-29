#pragma once
#include <vector>
#include <string>
#include <SDL.h>

#include "Coordinate.h"

#define _BOARD_HEIGHT 7
#define _BOARD_WIDTH 7

enum class Color {
	White,
	Black
};

enum class Path {
	queenWhite,
	queenBlack,
	kingWhite,
	kingBlack,
	rookWhite,
	rookBlack,
	knightWhite,
	knightBlack,
	bishopWhite,
	bishopBlack,
	pawnWhite,
	pawnBlack,
};
inline std::string pathToString(Path p) {
	switch (p) {
	case Path::queenWhite:	return "QueenWhite.png";
	case Path::queenBlack:	return "QueenBlack.png";
	case Path::kingWhite:	return "KingWhite.png";
	case Path::kingBlack:	return "KingBlack.png";
	case Path::rookWhite:	return "RookWhite.png";
	case Path::rookBlack:	return "RookBlack.png";
	case Path::knightWhite:	return "KnightWhite.png";
	case Path::knightBlack:	return "KnightBlack.png";
	case Path::bishopWhite:	return "BishopWhite.png";
	case Path::bishopBlack:	return "BishopBlack.png";
	case Path::pawnWhite:	return "PawnWhite.png";
	case Path::pawnBlack:	return "PawnBlack.png";
	default: 
		throw "Unimplemented item!";
	}
}

class Piece {
protected:
	Coordinate position;
	Color color;
	bool dead;
	bool chosen;
	std::string imagePath;
	SDL_Texture* texture;
	int id;

public:
	Piece();
	Piece(const Piece& pieces);
	Piece(const Coordinate& position, Color color, const std::string& imagePath);
	virtual ~Piece();

	void setPosition(Coordinate postion);
	void setColor(Color color);
	void setDead(bool dead);
	void setChosen(bool chosen);

	Coordinate getPosition() const;
	Color getColor() const;
	bool getDead() const;
	bool getChosen() const;
	int getId() const;

	virtual Piece* move(const Coordinate& c) = 0;
	virtual std::vector<Coordinate> getPossibleMoves() const = 0;
	virtual Piece* clone() = 0;
	virtual std::string getNameClass() const = 0;
	void loadImage();
	void destroyImage();

	virtual Piece& operator = (const Piece& piece);
};

class King : public Piece {
private:
	bool castling;
public:
	King();
	King(const King& king);
	King(const Coordinate& position, Color color, const std::string& pathImage);
	virtual ~King();

	void setCastling();
	bool getCastling() const;
	Piece* move(const Coordinate& c);
	std::vector<Coordinate> getPossibleMoves() const;
	std::string getNameClass() const;
	Piece* clone();
	void performCastling();

	King& operator = (const King& piece);
};

class Queen : public Piece {
private:
public:
	Queen();
	Queen(const Queen& queen);
	Queen(const Coordinate& position, Color color, const std::string& pathImage);
	virtual ~Queen();

	Piece* move(const Coordinate& c);
	std::vector<Coordinate> getPossibleMoves() const;
	Piece* clone();
	std::string getNameClass() const;

	Queen& operator = (const Queen& piece);
};

class Bishop : public Piece {
private:
public:
	Bishop();
	Bishop(const Bishop& queen);
	Bishop(const Coordinate& position, Color color, const std::string& pathImage);
	virtual ~Bishop();

	Piece* move(const Coordinate& c);
	std::vector<Coordinate> getPossibleMoves() const;
	Piece* clone();
	std::string getNameClass() const;

	Bishop& operator = (const Bishop& piece);
};


class Rook : public Piece {
private:
public:
	Rook();
	Rook(const Rook& rook);
	Rook(const Coordinate& position, Color color, const std::string& pathImage);
	virtual ~Rook();

	Piece* move(const Coordinate& c);
	std::vector<Coordinate> getPossibleMoves() const;
	Piece* clone();
	std::string getNameClass() const;
	void performCastling();

	Rook& operator = (const Rook& piece);
};

class Knight : public Piece {
private:
public:
	Knight();
	Knight(const Knight& knight);
	Knight(const Coordinate& position, Color color, const std::string& pathImage);
	virtual ~Knight();

	Piece* move(const Coordinate& c);
	std::vector<Coordinate> getPossibleMoves() const;
	std::string getNameClass() const;
	Piece* clone();

	Knight& operator = (const Knight& piece);
};

class Pawn: public Piece {
private:
	Piece* promotion;
	bool firstMove;
public:
	Pawn();
	Pawn(const Pawn& pawn);
	Pawn(const Coordinate& position, Color color, const std::string& pathImage);
	virtual ~Pawn();

	Piece* getPromotion() const;
	bool getFirstMove();
	void setFirstMoveFalse();
	Piece* move(const Coordinate& c);
	std::vector<Coordinate> getPossibleMoves() const;
	std::string getNameClass() const;
	Piece* clone();
	Piece* getPromotion();
	friend void promote(Piece* newPiece, std::string nameClass);
	void enPassant();

	Pawn& operator = (const Pawn& piece);
};

