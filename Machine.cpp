
#include "Machine.h"

void Machine::reset() {
    registers.fill(0);
    flags["Z"] = false;
    flags["PC"] = 0;
    memory.fill(0);
}
