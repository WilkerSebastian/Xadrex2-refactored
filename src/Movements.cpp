#include "Movements.h"

#include "Settings.h"
#include "Piece.h"

using namespace Piece;

MoveValid Movements::move() {

    MoveValid validator;

    validator = this->independentPieceMovementVerification();

    if (validator != MoveValid::PROCEED)
        return validator;

    return this->pieceMovementVerification();

}

MoveValid Movements::pieceMovementVerification() {

    const char _piece = this->board->getHouse(this->sx, this->sy);

    if (_piece == static_cast<char>(Pieces::WHITE_PAWN)) {

        if (!this->whitePawn())
            return MoveValid::NOT_VALID;

        return this->isRequiem(false) ? MoveValid::REQUIEM : MoveValid::VALID;

    } else if (_piece == static_cast<char>(Pieces::BLACK_PAWN)) {

        if (!this->blackPawn())
            return MoveValid::NOT_VALID;

        return this->isRequiem(true) ? MoveValid::REQUIEM : MoveValid::VALID;

    }  else if (_piece == static_cast<char>(Pieces::WHITE_TOWER) || _piece == static_cast<char>(Pieces::BLACK_TOWER))
        return this->tower() ? MoveValid::VALID : MoveValid::NOT_VALID;


}

MoveValid Movements::independentPieceMovementVerification() {

    if (this->isRock())
        return MoveValid::ROCK;

    if (!Settings::isNormalChess)
        return MoveValid::VALID;

    if (this->sx == this->dx && this->sy == this->dy)
        return MoveValid::NOT_VALID;

    bool existWH = board->existWhitePieceInHouse(this->dx, this->dy);

    bool white = board->isWhite(this->sx, this->sy);

    if ((white && existWH) || (!white && !existWH))
        return MoveValid::NOT_VALID;    

}

bool Movements::isRequiem(const bool black) {

    if (black)
        return this->dx == 0;

    return this->dx == 7;

}

bool Movements::blackPawn() {
 
    bool distIsEmpty = board->houseIsEmpty(this->dx, this->dy);
    bool frontMovement = this->sx - 1 == this->dx && this->sy == this->dy;
    bool sideCapture = this->sx - 1 == this->dx && (this->sy - 1 == this->dy || this->sy + 1 == this->dy);
    bool doubleFront = this->sx == 6 && this->sx - 2 == this->dx && this->sy == this->dy;
    bool pathToDistIsEmpty = board->houseIsEmpty(this->sx - 1, this->sy);
 
    return (
        (frontMovement && distIsEmpty) || 
        (sideCapture && !distIsEmpty) || 
        (doubleFront && pathToDistIsEmpty && !distIsEmpty)
    );

}

bool Movements::whitePawn() {

    bool distIsEmpty = board->houseIsEmpty(this->dx, this->dy);
    bool frontMovement = this->sx + 1 == this->dx && this->sy == this->dy;
    bool sideCapture = this->sx + 1 == this->dx && (this->sy - 1 == this->dy || this->sy + 1 == this->dy);
    bool doubleFront = this->sx == 1 && this->sx + 2 == this->dx && this->sy == this->dy;
    bool pathToDistIsEmpty = board->houseIsEmpty(this->sx + 1, this->sy);
 
    return (
        (frontMovement && distIsEmpty) || 
        (sideCapture && !distIsEmpty) || 
        (doubleFront && pathToDistIsEmpty && !distIsEmpty)
    );

}

bool Movements::tower() {

    if (this->sx == this->dx && this->sy <= this->dy) {

        for (uint8_t i = sy + 1; i < dy; i++) {

            if (!this->board->houseIsEmpty(sx, i))
                return false;
        
        }

        return true;

    } else if (this->sx == this->sx && this->sy >= this->dy) {

        for (uint8_t i = sy - 1; i > dy; i--) {

            if (!this->board->houseIsEmpty(sx, i))
                return false;
        
        }
        
        return true;

    } else if (this->sx >= this->dx && this->sy == this->dy) {

        for (uint8_t i = this->sx - 1; i > dx; i--) {

            if (!this->board->houseIsEmpty(i, sy))           
                return false;
            
        }

        return true;

    } else if(this->sx <= this->dx && this->sy == this->dy) {

        for (uint8_t i = this->sx + 1; i < this->dx; i++) {

            if (!this->board->houseIsEmpty(i, sy))
                return false;

        }

        return true;

    } 
    
    return false;

}

bool Movements::isRock() {

    return(
        (board->houseIs('K', this->sx, this->sy) && board->houseIs('L', this->dx, this->dy)) ||
        (board->houseIs('R', this->sx, this->sy) && board->houseIs('T', this->dx, this->dy))
    );

}
