#pragma once

#include "Constants.h"

class Chessboard {

    private:

        char board[BOARD_LEN][BOARD_LEN];

    public:

        Chessboard();

        bool selected(const uint8_t x, const uint8_t y);

        bool existWhitePieceInHouse(const uint8_t x, const uint8_t y);

        bool houseIsEmpty(const uint8_t x, const uint8_t y);

        bool houseIs(const char compared, const uint8_t x, const uint8_t y);

        bool isWhite(const uint8_t x, const uint8_t y);

        void copyHouseTo(const uint8_t sx, const uint8_t sy, const uint8_t dx, const uint8_t dy);

        void swap(const uint8_t sx, const uint8_t sy, const uint8_t dx, const uint8_t dy);

        void clearHouse(const uint8_t x, const uint8_t y);

        void setHouse(const char dist, const uint8_t x, const uint8_t y);

        char getHouse(const uint8_t x, const uint8_t y);

        void render();

        void reset();

};