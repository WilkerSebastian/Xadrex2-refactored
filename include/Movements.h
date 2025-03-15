#pragma once

class Movements {

    private:

        Movements() {}

        static Movements* instance_;
    
    public:

        Movements(Movements &other) = delete;

        void operator = (const Movements &) = delete;

        static Movements *GetInstance();
    
};
