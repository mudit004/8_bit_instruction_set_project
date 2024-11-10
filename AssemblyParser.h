#ifndef ASSEMBLY_PARSER_H
#define ASSEMBLY_PARSER_H

#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>

using namespace std;

class AssemblyParser
{
public:
    AssemblyParser();
    vector<uint8_t> parse(const string &assemblyCode);
    unordered_map<string, uint8_t> opcodeMap;
    uint8_t getOpcode(const string &mnemonic);
    uint8_t getOperand(const string &operand);
};

#endif
