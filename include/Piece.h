#pragma once

#include <vector>

namespace Piece {

    enum class Pieces : char {
        WHITE_TOWER = 'L',
        WHITE_KNIGHT = 'E',
        WHITE_BISHOP = 'X',
        WHITE_KING = 'K',
        WHITE_QUEEN = 'Q',
        WHITE_PAWN = 's',
        BLACK_PAWN = 'p',
        BLACK_TOWER = 'T',
        BLACK_KNIGHT = 'C',
        BLACK_BISHOP = 'B',
        BLACK_KING = 'R',
        BLACK_QUEEN = 'D',
        BLANK_PIECE = '-'
    };

    inline const std::vector<Pieces> pieces = {
        Pieces::BLANK_PIECE,
        Pieces::WHITE_TOWER,
        Pieces::WHITE_KNIGHT,
        Pieces::WHITE_BISHOP,
        Pieces::WHITE_KING,
        Pieces::WHITE_QUEEN,
        Pieces::WHITE_PAWN,
        Pieces::BLACK_PAWN,
        Pieces::BLACK_TOWER,
        Pieces::BLACK_KNIGHT,
        Pieces::BLACK_BISHOP,
        Pieces::BLACK_KING,
        Pieces::BLACK_QUEEN,
    }; 

}