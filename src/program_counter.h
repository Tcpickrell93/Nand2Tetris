#ifndef PROGRAM_COUNTER_H
#define PROGRAM_COUNTER_H

#include "memory.h"

class ProgramCounter {
public:
    void Update(const byte2& in, const bit& load, const bit& increment, const bit& reset);
    byte2 Out();
    
private:
    Register16 reg_ {};
};
    
# endif // PROGRAM_COUNTER_H
