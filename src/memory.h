#ifndef MEMORY_H
#define MEMORY_H

#include "bits.h"


void UpdateDFF(bit1_u& dff, 
               const bit1_u& in);
union RegisterBit_u {
    struct RegisterBit_s {
        bit1_u dff;
    } regbit_s;
    unsigned int value;
};
void UpdateRegisterBit(RegisterBit_u& rb, 
                       const bit1_u& in, 
                       const bit1_u& load);

void UpdateDFF16(byte2_u& dff16,
                 const byte2_u& in);
union Register16_u {
    struct Register16_s {
        byte2_u dff16;
    } r16_s;
    unsigned int value;
};
void UpdateRegister16(Register16_u& r16, 
                      const byte2_u in, 
                      const bit1_u& load);

struct RAM8 {
    Register16_u reg0;
    Register16_u reg1;
    Register16_u reg2;
    Register16_u reg3;
    Register16_u reg4;
    Register16_u reg5;
    Register16_u reg6;
    Register16_u reg7;
};
byte2_u ReadRAM8(const RAM8& ram,
                 const bit3_u& address);
void WriteRAM8(RAM8& ram, 
               const bit3_u& address, 
               const byte2_u& in, 
               const bit1_u& load); 

struct RAM64 {
    RAM8 ram0;
    RAM8 ram1;
    RAM8 ram2;
    RAM8 ram3;
    RAM8 ram4;
    RAM8 ram5;
    RAM8 ram6;
    RAM8 ram7;
};
byte2_u ReadRAM64(const RAM64& ram,
                  const bit6_u& address);
void WriteRAM64(RAM64& ram,
                const bit6_u& address,
                const byte2_u& in,
                const bit1_u& load);

struct RAM512 {
    RAM64 ram0;
    RAM64 ram1;
    RAM64 ram2;
    RAM64 ram3;
    RAM64 ram4;
    RAM64 ram5;
    RAM64 ram6;
    RAM64 ram7;
};
byte2_u ReadRAM512(const RAM512& ram, 
                   const bit9_u& address);
void WriteRAM512(RAM512& ram, 
                 const bit9_u& address, 
                 const byte2_u& in, 
                 const bit1_u& load);

struct RAM4k {
    RAM512 ram0;
    RAM512 ram1;
    RAM512 ram2;
    RAM512 ram3;
    RAM512 ram4;
    RAM512 ram5;
    RAM512 ram6;
    RAM512 ram7;
};
byte2_u ReadRAM4k(const RAM4k& ram, 
                  const bit12_u& address);
void WriteRAM4k(RAM4k& ram, 
                const bit12_u& address, 
                const byte2_u& in, 
                const bit1_u& load);                  

struct RAM16k {
    RAM4k ram0;
    RAM4k ram1;
    RAM4k ram2;
    RAM4k ram3;
};
byte2_u ReadRAM16k(const RAM16k& ram, 
                   const bit14_u& address);


#endif // MEMORY_H

