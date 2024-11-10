#include "AssemblyParser.h"
#include <sstream>
#include <iostream>
#include <cctype>
#include <algorithm>

using namespace std;

AssemblyParser::AssemblyParser()
{
    // Updated opcode map to align with the decoder's switch cases
    opcodeMap = {
        {"ADD", 0x0},   // Addition
        {"SUB", 0x1},   // Subtraction
        {"MOV", 0x2},   // Move (Register to Register)
        {"LOAD", 0x3},  // Load (Register from Memory)
        {"STORE", 0x4}, // Store (Register to Memory)
        {"LOADI", 0x5}, // Load Immediate (Immediate value to Register)
        {"JMP", 0x6},   // Unconditional Jump
        {"JZ", 0x7},    // Jump if Zero Flag is Set
        {"INC", 0x8},   // Increment Register
        {"DEC", 0x9},   // Decrement Register
        {"AND", 0xA},   // Logical AND
        {"OR", 0xB},    // Logical OR
        {"NOP", 0xC}    // No Operation
    };
}

vector<uint8_t> AssemblyParser::parse(const string &assemblyCode)
{
    vector<uint8_t> machineCode;
    istringstream stream(assemblyCode);
    string line;

    while (getline(stream, line))
    {
        istringstream lineStream(line);
        string mnemonic, dest, src;

        lineStream >> mnemonic >> dest;

        // Handle comma-separated syntax and detect presence of src operand
        if (!dest.empty() && dest.back() == ',')
            dest.pop_back();

        lineStream >> src;
        // cout << "Mnemonic: " << mnemonic << " Dest: " << dest << " Src: " << src << endl;
        uint8_t opcode = static_cast<uint8_t>(getOpcode(mnemonic));
        // cout << "Opcode: " << (int)opcode << endl;
        if (opcode == 0xFF)
        {
            cerr << "Error: Unknown mnemonic '" << mnemonic << "'" << endl;
            continue;
        }

        uint8_t destValue = getOperand(dest);
        uint8_t srcValue = src.empty() ? 5 : getOperand(src); // Default src to 0 if absent
        // cout << "Instruction:" << (int)opcode << " " << (int)destValue << " " << (int)srcValue << endl;
        // Combine opcode, dest, and src into an 8-bit instruction
        // cout << "Opcode: " << (int)opcode << " destValue: " << (int)destValue << " srcValue: " << (int)srcValue << endl;
        uint8_t instruction = 0;
        if (srcValue == 5)
        {
            instruction = (opcode << 4) | (destValue & 0x0F);
        }
        else
        {
            instruction = (opcode << 4) | ((destValue & 0x03) << 2) | (srcValue & 0x03);
        }
        // cout << "Instruction:" << (int)instruction << endl
        //  << endl;
        machineCode.push_back(instruction);
    }

    return machineCode;
}

uint8_t AssemblyParser::getOpcode(const string &mnemonic)
{
    if (opcodeMap.find(mnemonic) != opcodeMap.end())
    {
        return static_cast<uint8_t>((int)opcodeMap[mnemonic]);
    }
    else
    {
        return 0xFF; // Invalid opcode
    }
}

uint8_t AssemblyParser::getOperand(const string &operand)
{
    if (operand.empty())
    {
        return 0; // Default to 0 if operand is missing
    }

    // Check if the operand is a register
    if (operand[0] == 'R')
    {
        if (isdigit(operand[1]) && operand.length() == 2)
        {                            // Ensure the format is "R<digit>"
            return operand[1] - '0'; // Convert register number to integer
        }
        else
        {
            cerr << "Error: Invalid register format '" << operand << "'" << endl;
            return 0; // Return default or consider an error code
        }
    }
    else if (operand.size() > 2 && operand[0] == '0' && (operand[1] == 'x' || operand[1] == 'X'))
    {
        // Check if the rest of the operand is a valid hexadecimal number
        if (all_of(operand.begin() + 2, operand.end(), [](char c)
                   { return isxdigit(c); }))
        {
            return stoi(operand, nullptr, 16); // Convert hexadecimal string to integer
        }
        else
        {
            cerr << "Error: Invalid hexadecimal value '" << operand << "'" << endl;
            return 0; // Return default or consider an error code
        }
    }
    else if (all_of(operand.begin(), operand.end(), ::isdigit))
    {                         // Check for decimal number
        return stoi(operand); // Convert decimal string to integer
    }
    else
    {
        cerr << "Error: Invalid immediate value '" << operand << "'" << endl;
        return 0; // Return default or consider an error code
    }
}
