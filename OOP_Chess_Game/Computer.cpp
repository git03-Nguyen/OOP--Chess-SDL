#include "Computer.h"

Computer::Computer() {

}
// defaul, com 1st, 0;
std::pair<int, Coordinate> Computer::playWithEasyMode()
{
    srand(time(NULL));
    std::vector<int> enableMovingPieces;
    std::vector<std::vector<Coordinate>> moves;
    for (int i = 0; i < 16; i++) {
        Piece* piece = Board::piecesList[i];
        if (piece->getDead()) continue;
        piece->setChosen(true);
        std::vector<std::vector<Coordinate>> temp = piece->getPossibleMoves(Board::piecesOnBoard);
        piece->setChosen(false);
        std::vector<Coordinate> tempMoves;
        tempMoves.reserve(temp[0].size() + temp[1].size());
        copy(temp[0].begin(), temp[0].end(), std::back_inserter(tempMoves));
        copy(temp[1].begin(), temp[1].end(), std::back_inserter(tempMoves));

        if (tempMoves.size() >= 1) {
            enableMovingPieces.push_back(i);
            moves.push_back(tempMoves);
            tempMoves.clear();
        }
    }
    
    if (enableMovingPieces.size() == 0) throw std::string("Don't have any moves\n!!!");

    // random piece;
    int pieceIdx = rand() % enableMovingPieces.size();
    // random move for piece;
    int moveIdx = rand() % moves[pieceIdx].size();

  
    return std::pair<int, Coordinate>(enableMovingPieces[pieceIdx], moves[pieceIdx][moveIdx]);
}

std::pair<int, Coordinate> Computer::evadeEaten() {

    std::vector<Coordinate> moves;
    for (int i = 16; i < 32; i++) {
        Piece* piece = Board::piecesList[i];
        if (piece->getDead()) continue;
        std::vector<Coordinate> temp = piece->getPossibleMoves(Board::piecesOnBoard)[0];
        if (temp.size() == 0) continue;
        moves.insert(moves.end(), temp.begin(), temp.end());
    }

    for (int i = 0;i < 8;i++) {
        Piece* piece = Board::piecesList[i];
        for (auto u1 : moves) {
            if (u1 == piece->getPosition()) {
                return getNonEatenMove(i);
            }
        }
    }

    return std::pair<int, Coordinate>(-1, Coordinate(-1, -1));
}

std::pair<int,Coordinate> Computer::getNonEatenMove(int idx) {
    std::vector<Coordinate> movesOfPiece;
    Board::piecesList[idx]->setChosen(true);
    movesOfPiece = Board::piecesList[idx]->getPossibleMoves(Board::piecesOnBoard)[0];
    Board::piecesList[idx]->setChosen(false);

    std::vector<Coordinate> moves;
    for (int i = 16; i < 32; i++) {
        Piece* piece = Board::piecesList[i];
        if (piece->getDead()) continue;
        std::vector<Coordinate> temp = piece->getPossibleMoves(Board::piecesOnBoard)[0];
        if (temp.size() == 0) continue;
        moves.insert(moves.end(), temp.begin(), temp.end());
    }

    for (auto u1 : movesOfPiece) {
        bool flag = true;
        for (auto u2 : moves) {
            if (u1 == u2) {
                flag = false;
                break;
            }
        }
        if (flag) return std::pair<int, Coordinate>(idx, u1);
    }
    return std::pair<int, Coordinate>(-1, Coordinate(-1,-1));  
}

std::pair<int, Coordinate> Computer::playWithHardMode() {
    srand(time(NULL));
    std::vector<int> enableMovingPieces;
    std::vector<std::vector<std::vector<Coordinate>>> moves;

    for (int i = 0; i < 16; i++) {
        Piece* piece = Board::piecesList[i];
        if (piece->getDead()) continue;
        piece->setChosen(true);
        std::vector<std::vector<Coordinate>> temp = piece->getPossibleMoves(Board::piecesOnBoard);
        piece->setChosen(false);

        if (temp[0].size() + temp[1].size() >= 1) {
            enableMovingPieces.push_back(i);
            moves.push_back(temp);
        }
    }

    if (enableMovingPieces.size() == 0) throw std::string("Don't have any moves\n!!!");

    std::vector<PieceType> type{ PieceType::King,PieceType::Queen,PieceType::Rook,PieceType::Bishop,PieceType::Knight,PieceType::Pawn };
    
    //eatingMove
    for (auto e : type) {
        for (int i = 0; i < moves.size(); i++) {
            for (int j = 0; j < moves[i][1].size(); j++) {
                Piece* piece = Board::getPieceAt(moves[i][1][j]);
                if (piece->getType() == e) {
                    return std::pair<int, Coordinate>(enableMovingPieces[i], moves[i][1][j]);
                }
            }
        }
    }

    std::pair<int, Coordinate> res;
    //move ne; duyet het; tra ve; 
    res = evadeEaten();
    if (res.first >= 0) return res;
    //move ko bi an, tra ve i,coordinate; dau vao la nhung quan co di duoc. 
  
    for (int i = 0; i < 7; i ++) {
        int pieceIdx = rand() % enableMovingPieces.size();
        res = getNonEatenMove(pieceIdx);
        if (res.first >= 0) return res;
    }
    
    // random piece;
    int pieceIdx = rand() % enableMovingPieces.size();
    // random move for piece;
    int moveIdx = rand() % moves[pieceIdx][0].size();

    return std::pair<int, Coordinate>(enableMovingPieces[pieceIdx], moves[pieceIdx][0][moveIdx]);
}