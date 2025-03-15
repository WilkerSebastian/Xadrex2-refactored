#pragma once

class Sound {

    private:

        Sound() {}

        static Sound* instance_;

    public:

        Sound(Sound &other) = delete;

        void operator = (const Sound &) = delete;

        static Sound *GetInstance();

        void the_final_countdown();
        void desistencia();
        void empateNegado();
        void empate();
        void assassinato(int round);
        void requi();

};