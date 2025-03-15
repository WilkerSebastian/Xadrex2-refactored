#pragma once

#include <random>

class Random {

    private:
    
        static inline std::mt19937 randomEngine{ std::random_device{}() };

    public:
    
        static int generateInt(int min, int max);


};
