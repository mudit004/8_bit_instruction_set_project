
#ifndef INSTRUCTION_DECODER_H
#define INSTRUCTION_DECODER_H

#include "Machine.h"

class InstructionDecoder {
public:
    void decodeAndExecute(uint8_t instruction, Machine &machine);
};

#endif
