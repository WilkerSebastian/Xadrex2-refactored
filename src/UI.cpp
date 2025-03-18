#include "UI.h"

#include <iostream>
#include "Sound.h"
#include "Settings.h"
#include "Piece.h"

using namespace Piece;

Piece::Pieces UI::selectRequiem(const bool white) {

    Pieces piece;
    uint8_t selectRequiem;

    std::cout << "\nPeão Requiem\n\n";

    Sound::GetInstance()->requi(); 
    
    if (white) {

        std::cout << "Pra qual peça o seu peão vai mega-evoluir?\n\n"
                << "1)Liteira\n2)Elefante\n3)Xamã\n4)Queen\n" << !Settings::isNormalChess ? "5)King Crimson" : '\0';

    } else {

        std::cout << "Pra qual peça o seu peão vai mega-evoluir?\n\n"
                << "1)Torre\n2)Cavalo\n3)Bispo\n4)Rainha\n" << !Settings::isNormalChess ? "5)Reinaldo" : '\0';

    }

    std::cin >> selectRequiem;
    
    switch (selectRequiem) {
        case static_cast<uint8_t>(SelectRequire::TOWER):

            piece = white ? Pieces::WHITE_TOWER : Pieces::BLACK_TOWER;
            break;

        case static_cast<uint8_t>(SelectRequire::KINGHT):

            piece = white ? Pieces::WHITE_KNIGHT : Pieces::BLACK_KNIGHT;
            break;

        case static_cast<uint8_t>(SelectRequire::BISHOP):

            piece = white ? Pieces::WHITE_BISHOP : Pieces::BLACK_BISHOP;
            break;
        
        case static_cast<uint8_t>(SelectRequire::QUEEN):

            piece = white ? Pieces::WHITE_QUEEN : Pieces::BLACK_QUEEN;
            break;
        
        case static_cast<uint8_t>(SelectRequire::KING):

            piece = white ? Pieces::WHITE_KING : Pieces::BLACK_KING;
            break;

        default:

            std::cout << "\nAo ser abandonado pelo seu" << (white ? "King" : "rei") << ", o peão decide mudar de lado\n";
            break;
    }

    this->pause();

}

void UI::pause() {

    std::cout << "Pressione qualquer tecla para continuar. . .";
    getchar();

}

void UI::clear() {

    #ifdef _WIN64
        system("cls");
    #else
        system("clear");
    #endif

}