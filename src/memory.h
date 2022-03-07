#ifndef MEMORY_H
#define MEMORY_H

#include "bits.h"
#include <vector>

class DataFlipFLop {
public:
    void Update(const bit& in);
    bit Out();

private:
    bit prev_ {};
};
    
class RegisterBit {
public:
    void Update(const bit& in, const bit& load);
    bit Out();

private:
    DataFlipFLop dff_ {};
};

class Register16 {
public:
    void Update(const byte2& in, const bit& load);
    byte2 Out();

private:
    RegisterBit bit0_ {};
    RegisterBit bit1_ {};
    RegisterBit bit2_ {};
    RegisterBit bit3_ {};
    RegisterBit bit4_ {};
    RegisterBit bit5_ {};
    RegisterBit bit6_ {};
    RegisterBit bit7_ {};
    RegisterBit bit8_ {};
    RegisterBit bit9_ {};
    RegisterBit bit10_ {};
    RegisterBit bit11_ {};
    RegisterBit bit12_ {};
    RegisterBit bit13_ {};
    RegisterBit bit14_ {};
    RegisterBit bit15_ {};
};

class RAM8 {
public:
    byte2 Read(const bit3& address);
    void Write(const bit3& address, const byte2& in, const bit& load);
    
private:
    Register16 reg0_ {};
    Register16 reg1_ {};
    Register16 reg2_ {};
    Register16 reg3_ {};
    Register16 reg4_ {};
    Register16 reg5_ {};
    Register16 reg6_ {};
    Register16 reg7_ {};
};

#endif // MEMORY_H

