#pragma once

#include "Piece.h"

class UI {

    private:

        enum class SelectRequire {
            TOWER = 1,
            KINGHT = 2,
            BISHOP = 3,
            QUEEN = 4,
            KING = 5
        };

        void pause();

        void clear();
    
    public:

        Piece::Pieces selectRequiem(const bool white);

};
