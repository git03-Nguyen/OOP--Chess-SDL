#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "Coordinate.h"
#include "Window.h"

#define _BOARD_HEIGHT 7
#define _BOARD_WIDTH 7

enum class Color {
	White,
	Black
};
enum class PieceType {
	King, Queen, Rook, Bishop, Knight, Pawn
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
	case Path::queenWhite:	return "..\\Assets\\Pieces\\QueenWhite.png";
	case Path::queenBlack:	return "..\\Assets\\Pieces\\QueenBlack.png";
	case Path::kingWhite:	return "..\\Assets\\Pieces\\KingWhite.png";
	case Path::kingBlack:	return "..\\Assets\\Pieces\\KingBlack.png";
	case Path::rookWhite:	return "..\\Assets\\Pieces\\RookWhite.png";
	case Path::rookBlack:	return "..\\Assets\\Pieces\\RookBlack.png";
	case Path::knightWhite:	return "..\\Assets\\Pieces\\KnightWhite.png";
	case Path::knightBlack:	return "..\\Assets\\Pieces\\KnightBlack.png";
	case Path::bishopWhite:	return "..\\Assets\\Pieces\\BishopWhite.png";
	case Path::bishopBlack:	return "..\\Assets\\Pieces\\BishopBlack.png";
	case Path::pawnWhite:	return "..\\Assets\\Pieces\\PawnWhite.png";
	case Path::pawnBlack:	return "..\\Assets\\Pieces\\PawnBlack.png";
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
	PieceType type;
public:
	std::vector<int> tableMove;
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
	PieceType getType() const;
	SDL_Texture* getTexture();

	virtual Piece* move(const Coordinate& c, std::vector<std::vector<Piece*>>) = 0;
	virtual std::vector<Coordinate> getPossibleMoves(std::vector<std::vector<Piece*>>) const = 0;
	virtual Piece* clone() = 0;
	void loadImage(SDL_Renderer* renderer);
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
	Piece* move(const Coordinate& c, std::vector<std::vector<Piece*>>);
	std::vector<Coordinate> getPossibleMoves(std::vector<std::vector<Piece*>>) const;
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

	Piece* move(const Coordinate& c, std::vector<std::vector<Piece*>>);
	std::vector<Coordinate> getPossibleMoves(std::vector<std::vector<Piece*>>) const;
	Piece* clone();

	Queen& operator = (const Queen& piece);
};

class Bishop : public Piece {
private:
public:
	Bishop();
	Bishop(const Bishop& queen);
	Bishop(const Coordinate& position, Color color, const std::string& pathImage);
	virtual ~Bishop();

	Piece* move(const Coordinate& c, std::vector<std::vector<Piece*>>);
	std::vector<Coordinate> getPossibleMoves(std::vector<std::vector<Piece*>>) const;
	Piece* clone();

	Bishop& operator = (const Bishop& piece);
};


class Rook : public Piece {
private:
public:
	Rook();
	Rook(const Rook& rook);
	Rook(const Coordinate& position, Color color, const std::string& pathImage);
	virtual ~Rook();

	Piece* move(const Coordinate& c, std::vector<std::vector<Piece*>>);
	std::vector<Coordinate> getPossibleMoves(std::vector<std::vector<Piece*>>) const;
	Piece* clone();
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

	Piece* move(const Coordinate& c, std::vector<std::vector<Piece*>>);
	std::vector<Coordinate> getPossibleMoves(std::vector<std::vector<Piece*>>) const;
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
	void setFirstMove();
	Piece* move(const Coordinate& c, std::vector<std::vector<Piece*>>);
	std::vector<Coordinate> getPossibleMoves(std::vector<std::vector<Piece*>>) const;
	Piece* clone();
	Piece* getPromotion();
	friend void promote(Piece* newPiece, PieceType& type);
	void enPassant(Pawn& enemy);

	Pawn& operator = (const Pawn& piece);
};


