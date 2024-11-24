# 8-Bit Instruction Set Emulator

## Overview
This project implements an 8-bit instruction set emulator, capable of reading assembly code, parsing it into machine code, and executing it. It provides a simple platform to simulate basic CPU operations, memory manipulation, and control flow.

---

## Features
1. **Instruction Set Support**: The emulator supports a set of basic assembly instructions, including arithmetic, logical, memory, and control flow operations.
2. **Assembly Parser**: Converts human-readable assembly code into machine-readable 8-bit instructions.
3. **Instruction Decoder**: Decodes machine instructions and executes them on the virtual machine.
4. **Memory Dump**: Displays memory contents after execution.
5. **State Inspection**: Shows register states after each instruction for debugging.

---

## How to Use

### 1. Prerequisites
- A C++11-compatible compiler (e.g., GCC, Clang, MSVC).
- Basic understanding of assembly language and C++.

### 2. Files in the Repository
- `main.cpp`: Main program to run the emulator.
- `Machine.cpp`: Simulates the CPU, including registers and memory.
- `InstructionDecoder.cpp`: Decodes and executes machine instructions.
- `AssemblyParser.cpp`: Parses assembly code into machine code.
- `assembly_code.txt`: Input assembly file with example code.
- `Makefile`: Automates the build process for the emulator.

---

### 3. Building and Running the Emulator
To compile, clean, and run the emulator, follow these steps:

#### a. Build the Emulator
Use the provided `Makefile` to compile the project:
```bash
make
```

This will generate an executable named `machine`.

#### b. Run the Emulator
Run the executable using the command:
```bash
make run
```

The `make run` command ensures the program builds successfully before executing.

#### c. Clean Up
To remove the compiled executable, use:
```bash
make clean
```

---

### 4. Input Assembly Code
The program reads assembly code from a file named `assembly_code.txt`. Ensure this file exists in the same directory as the executable. Here's an example file content:

```assembly
LOADI R0, 1      
LOADI R1, 3      
ADD R0, R1       
STORE R0, 0x01   
DEC R1           
JZ 0x07          
JMP 0x02         
NOP              
```

Modify `assembly_code.txt` as needed to test other instructions.

---

### 5. Output
The program outputs the following:
1. **Parsed Machine Code**: The 8-bit machine instructions generated from the input assembly code.
2. **Execution Trace**: Displays the program counter (PC) and register states after each instruction.
3. **Memory Dump**: A table showing the contents of memory after execution.


---

## Instruction Set

| Mnemonic | Opcode | Description                             |
|----------|--------|-----------------------------------------|
| `ADD`    | `0x0`  | Add two registers.                     |
| `SUB`    | `0x1`  | Subtract one register from another.    |
| `MOV`    | `0x2`  | Move data between registers.           |
| `LOAD`   | `0x3`  | Load a value from memory to a register.|
| `STORE`  | `0x4`  | Store a register value into memory.    |
| `LOADI`  | `0x5`  | Load an immediate value into a register.|
| `JMP`    | `0x6`  | Unconditional jump.                   |
| `JZ`     | `0x7`  | Jump if the zero flag is set.          |
| `INC`    | `0x8`  | Increment a register.                  |
| `DEC`    | `0x9`  | Decrement a register.                  |
| `AND`    | `0xA`  | Perform logical AND between two values.|
| `OR`     | `0xB`  | Perform logical OR between two values. |
| `NOP`    | `0xC`  | No operation.                          |

---

## Troubleshooting
- **Error: Unable to open file.**  
  Ensure `assembly_code.txt` exists in the same directory as the executable.
  
- **Unknown mnemonic 'XYZ'.**  
  Check the spelling of the instruction in the assembly code file.

- **Registers or memory show unexpected values.**  
  Verify the assembly code logic and ensure it's valid.

---

## Future Enhancements
1. Expand the instruction set to include more operations (e.g., multiplication, division).
2. Add support for floating-point arithmetic.
3. Improve debugging with detailed flag state tracking.

---

Made with ❤️ by Dhruv and Mudit