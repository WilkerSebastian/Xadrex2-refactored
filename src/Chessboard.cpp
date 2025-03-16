#include "Chessboard.h"

#include <iostream>
#include "Settings.h"

Chessboard::Chessboard() {

    this->reset();

}

bool Chessboard::selected(const uint8_t x, const uint8_t y, const bool white) {

    if(Settings::isNormalChess)
        return true;

    bool existWH = this->existWhitePieceInHouse(x, y);

    if ((white && existWH) || (!white && !existWH))
        return true;

    return false;

}

bool Chessboard::existWhitePieceInHouse(const uint8_t x, const uint8_t y) {

    return (
        this->houseIs('s', x, y) || 
        this->houseIs('L', x, y) || 
        this->houseIs('E', x, y) || 
        this->houseIs('X', x, y) || 
        this->houseIs('K', x, y) || 
        this->houseIs('Q', x, y)
    );

}

bool Chessboard::houseIsEmpty(const uint8_t x, const uint8_t y) {

    return this->houseIs('-', x, y);

}

bool Chessboard::houseIs(const char compared, const uint8_t x, const uint8_t y) {

    return this->getHouse(x, y) == compared;

}

void Chessboard::copyHouseTo(const uint8_t sx, const uint8_t sy, const uint8_t dx, const uint8_t dy) {

    this->setHouse(this->getHouse(sx, sy), dx, dy);

}

void Chessboard::swap(const uint8_t sx, const uint8_t sy, const uint8_t dx, const uint8_t dy) {

    char aux = this->getHouse(sx, sy);
    this->setHouse(this->getHouse(dx, dy), sx, sy);
    this->setHouse(aux, dx, dy);

}

void Chessboard::clearHouse(const uint8_t x, const uint8_t y) {

    this->setHouse('-', x, y);

}

void Chessboard::setHouse(const char dist, const uint8_t x, const uint8_t y) {

    this->board[x][y] = dist;

}

char Chessboard::getHouse(const uint8_t x, const uint8_t y) {

    return this->board[x][y];

}

void Chessboard::render() {

    for(uint8_t i = 0; i < BOARD_LEN; i++){
		
        std::cout << i << "  ";

        for(uint8_t j = 0; j < 8; j++)
            std::cout << this->board[i][j] << ' ';
        
        printf("\n");					
	
    }

}

void Chessboard::reset() {

    this->board[0][0]='L';
	this->board[0][1]='E';
	this->board[0][2]='X';
	this->board[0][3]='K';
	this->board[0][4]='Q';
	this->board[0][5]='X';
	this->board[0][6]='E';
	this->board[0][7]='L';

	for(uint8_t i = 0; i < BOARD_LEN; i++)
	    this->board[1][i]='s';

	for(uint8_t i = 2; i < BOARD_LEN - 2; i++)
	    for(uint8_t j = 0; j < BOARD_LEN; j++)
	        this->board[i][j]='-';

	for(uint8_t i = 0; i < BOARD_LEN; i++)
        this->board[6][i]='p';

	this->board[7][0]='T';
	this->board[7][1]='C';
	this->board[7][2]='B';
	this->board[7][3]='R';
	this->board[7][4]='D';
	this->board[7][5]='B';
	this->board[7][6]='C';
	this->board[7][7]='T';

}