#pragma once

#ifdef _WIN64
    #include <windows.h>
#endif

#include <cstdint>
#include <cstdlib>
#include <thread>
#include <string>

namespace Utils {

    void sleep(uint32_t ms) {

        std::this_thread::sleep_for(std::chrono::milliseconds(ms));

    };

    void beep(uint32_t frequency, uint32_t duration) {

        #ifdef _WIN64

            Beep(frequency, duration);

        #else 

            std::string command = "beep -f " + std::to_string(frequency) +
                                " -l " + std::to_string(duration);

            system(command.c_str());

        #endif

    };

};