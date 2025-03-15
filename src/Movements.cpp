#include "Movements.h"

Movements *Movements::instance_ = nullptr;

Movements *Movements::GetInstance() {

    if (instance_ == nullptr)
        instance_ = new Movements();
    
    return instance_;

}

