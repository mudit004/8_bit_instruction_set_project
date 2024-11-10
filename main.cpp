#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <array>

#include "Machine.h"
#include "InstructionDecoder.h"
#include "AssemblyParser.h"

using namespace std;

int main()
{
    Machine machine;
    InstructionDecoder decoder;
    AssemblyParser parser;

    // Read assembly code from a file
    ifstream inputFile("assembly_code.txt");
    if (!inputFile)
    {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }

    // Load the file content into a string
    stringstream buffer;
    buffer << inputFile.rdbuf();
    string assemblyCode = buffer.str();

    // Parse assembly code into machine code
    vector<uint8_t> machineCode = parser.parse(assemblyCode);

    for (auto i : machineCode)
    {
        cout << (int)i << " ";
    }
    cout << endl;
    // Reset the machine to initialize registers, flags, and memory
    machine.reset();
    int tc = 17;
    // Execute instructions based on the programCounter
    while (machine.programCounter < machineCode.size() && tc--)
    {
        uint8_t instruction = machineCode[machine.programCounter];
        cout << endl
             << "PC: " << static_cast<int>(machine.programCounter) << endl;

        decoder.decodeAndExecute(instruction, machine);

        // Display register states after each instruction
        cout << "R0: " << static_cast<int>(machine.registers[0]) << "\t";
        cout << "R1: " << static_cast<int>(machine.registers[1]) << endl;
    }

    cout << endl
         << "Memory Dump:" << endl;
    cout << "Address  |  Value" << endl;
    cout << "------------------" << endl;

    for (size_t i = 0; i < machine.memory.size(); i++)
    {
        cout << "0x" << setw(2) << setfill('0') << hex << uppercase << i << "      |  0x"
             << setw(2) << setfill('0') << hex << uppercase << static_cast<int>(machine.memory[i]) << endl;
    }

    return 0;
}
