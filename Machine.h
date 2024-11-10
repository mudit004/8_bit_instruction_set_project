#ifndef MACHINE_H
#define MACHINE_H

#include <array>
#include <unordered_map>
#include <cstdint>
#include <string>
using namespace std;

class Machine
{
public:
    // 4 general-purpose registers (8-bit each for simplicity)
    array<uint8_t, 4> registers = {0, 0, 0, 0};

    // Program counter (8-bit addressable, for simplicity)
    uint8_t programCounter = 0;

    // Flags
    unordered_map<string, bool> flags = {
        {"Z", false} // Zero flag
    };

    // 16-byte memory for demonstration
    array<uint8_t, 16> memory = {0};

    // Reset machine state
    void reset();
};

#endif
