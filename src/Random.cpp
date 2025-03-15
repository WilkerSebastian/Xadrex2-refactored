#include <Random.h>

int Random::generateInt(int min, int max) {

    if (min > max) 
        throw std::invalid_argument("min must be less than max");
        
    std::uniform_int_distribution<int> distrib(min, max);

    return distrib(randomEngine);

}