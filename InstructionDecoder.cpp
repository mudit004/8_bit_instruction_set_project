#include <iostream>
#include "InstructionDecoder.h"

void InstructionDecoder::decodeAndExecute(uint8_t instruction, Machine &machine)
{
    uint8_t opcode = (instruction >> 4);
    uint8_t dest = 0;
    if (opcode == 0x6 || opcode == 0x7 || opcode == 0xC || opcode == 0x8 || opcode == 0x9)
    {
        dest = instruction & 0x0F;
    }
    else
    {
        dest = ((instruction & 0x0C) >> 2);
    }
    uint8_t src = instruction & 0x03;
    if (opcode == 0xC)
    {
        src = 0;
    }

    // cout << "Running Instruction: " << static_cast<int>(opcode) << " " << static_cast<int>(dest) << " " << static_cast<int>(src) << endl;
    switch (opcode)
    {
    case 0x0: // ADD
        machine.registers[dest] += machine.registers[src];
        break;
    case 0x1: // SUB
        machine.registers[dest] -= machine.registers[src];
        break;
    case 0x2: // MOV (Register to Register)
        machine.registers[dest] = machine.registers[src];
        break;
    case 0x3: // LOAD (Register from Memory)
        machine.registers[dest] = machine.memory[src];
        break;
    case 0x4: // STORE (Register to Memory)
        machine.memory[src] = machine.registers[dest];
        break;
    case 0x5:                          // LOADI (Immediate value to Register)
        machine.registers[dest] = src; // Assuming src holds an immediate value
        break;
    case 0x6:                          // JMP (Unconditional Jump)
        machine.programCounter = dest; // Jump to the destination
        return;                        // Do not increment PC here, because the jump has already set the PC
    case 0x7:                          // JZ (Jump if Zero Flag is Set)
        if (machine.flags["Z"])
        {
            machine.programCounter = dest; // Jump to the destination if Zero flag is set
            return;                        // Do not increment PC here, because the jump has already set the PC
        }
        else
        {
            machine.programCounter++; // Increment PC if no jump was taken
        }
        break;
    case 0x8: // INC (Increment Register)
        machine.registers[dest]++;
        break;
    case 0x9: // DEC (Decrement Register)
        machine.registers[dest]--;
        break;
    case 0xA: // AND
        machine.registers[dest] &= machine.registers[src];
        break;
    case 0xB: // OR
        machine.registers[dest] |= machine.registers[src];
        break;
    case 0xC: // NOP (No Operation)
        // Do nothing
        break;
    default:
        // Unrecognized opcode
        break;
    }

    // Update the zero flag based on the result in dest register
    // machine.flags["Z"] = (machine.registers[dest] == 0) ? true : false;

    if (machine.registers[dest] == 0)
    {
        // cout << "Say hi!!" << endl;
        machine.flags["Z"] = true;
    }
    else
    {
        // cout << "Say byee!!" << endl;
        machine.flags["Z"] = false;
    }

    // Increment the program counter after each instruction (unless a jump was executed)
    if (opcode != 0x6 && opcode != 0x7) // Don't increment for JMP or JZ
    {
        machine.programCounter++;
    }
}
