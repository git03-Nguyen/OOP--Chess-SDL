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
            std::cout << "--------------------------------------------" << std::endl;
            for (auto e : tempMoves){
                 std::cout << "index: " << i;
                 std::cout << "Coordinate: " << e.getX() << ", " << e.getY() << std::endl;
             }
            std::cout << "--------------------------------------------" << std::endl;
        }

        tempMoves.clear();
    }
    
    if (enableMovingPieces.size() == 0) throw std::string("Don't have any moves\n!!!");

    // random piece;
    int pieceIdx = rand() % enableMovingPieces.size();
    // random move for piece;
    int moveIdx = rand() % moves[pieceIdx].size();

    std::cout << "index: " << enableMovingPieces[pieceIdx] << std::endl;
    std::cout << "Coordinate: " << moves[pieceIdx][moveIdx].getX() << ", " << moves[pieceIdx][moveIdx].getY() << std::endl;

    return std::pair<int, Coordinate>(enableMovingPieces[pieceIdx], moves[pieceIdx][moveIdx]);
}
