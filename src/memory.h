#ifndef MEMORY_H
#define MEMORY_H

#include "bits.h"

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
    Register16();
    Register16(const byte2& value);
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

class RAM64 {
public:
    byte2 Read(const bit6& address);
    void Write(const bit6& address, const byte2& in, const bit& load);

private:
    RAM8 ram8_0_ {};
    RAM8 ram8_1_ {};
    RAM8 ram8_2_ {};
    RAM8 ram8_3_ {};
    RAM8 ram8_4_ {};
    RAM8 ram8_5_ {};
    RAM8 ram8_6_ {};
    RAM8 ram8_7_ {};
};

class RAM512 {
public:
    byte2 Read(const bit9& address);
    void Write(const bit9& address, const byte2& in, const bit& load);

private:
    RAM64 ram64_0_ {};
    RAM64 ram64_1_ {};
    RAM64 ram64_2_ {};
    RAM64 ram64_3_ {};
    RAM64 ram64_4_ {};
    RAM64 ram64_5_ {};
    RAM64 ram64_6_ {};
    RAM64 ram64_7_ {};
};

class RAM4k {
public:
    byte2 Read(const bit12& address);
    void Write(const bit12& address, const byte2& in, const bit& load);

private:
    RAM512 ram512_0_ {};
    RAM512 ram512_1_ {};
    RAM512 ram512_2_ {};
    RAM512 ram512_3_ {};
    RAM512 ram512_4_ {};
    RAM512 ram512_5_ {};
    RAM512 ram512_6_ {};
    RAM512 ram512_7_ {};
};

class RAM16k {
public:
    byte2 Read(const bit14& address);
    void Write(const bit14& address, const byte2& in, const bit& load);

private:
    RAM4k ram4k_0_ {};
    RAM4k ram4k_1_ {};
    RAM4k ram4k_2_ {};
    RAM4k ram4k_3_ {};
};

#endif // MEMORY_H

