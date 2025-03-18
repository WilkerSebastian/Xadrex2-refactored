#pragma once

#include "Chessboard.h"
#include "MoveValid.h"

class Movements {

    private:

        Chessboard *board;

        const uint8_t sx; 
        const uint8_t sy; 
        const uint8_t dx; 
        const uint8_t dy; 

        bool isRock();

        bool isRequiem(const bool black);

        bool blackPawn();

        bool whitePawn();

        bool tower();
        
        bool king();
    
        MoveValid independentPieceMovementVerification();

        MoveValid pieceMovementVerification();

    public:

        Movements(Chessboard *board, const uint8_t sx, const uint8_t sy, const uint8_t dx, const uint8_t dy) 
        : board(board), sx(sx), sy(sy), dx(dx), dy(dy) {};

        MoveValid move();

};
