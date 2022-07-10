#ifndef MEMORY_H
#define MEMORY_H

#include "bits.h"


void UpdateDFF(bit1_u& dff, 
               const bit1_u& in);

union RegisterBit_u;
void UpdateRegisterBit(RegisterBit_u& rb, 
                       const bit1_u& in, 
                       const bit1_u& load);

void UpdateDFF16(byte2_u& dff16,
                 const byte2_u& in);
union Register16_u;
void UpdateRegister16(Register16_u& r16, 
                      const byte2_u in, 
                      const bit1_u& load);

struct RAM8;
byte2_u ReadRAM8(const RAM8& ram,
                 const bit3_u& address);
void WriteRAM8(RAM8& ram, 
               const bit3_u& address, 
               const byte2_u& in, 
               const bit1_u& load); 

struct RAM64;
byte2_u ReadRAM64(const RAM64& ram,
                  const bit6_u& address);
void WriteRAM64(RAM64& ram,
                const bit6_u& address,
                const byte2_u& in,
                const bit1_u& load);

struct RAM512;
byte2_u ReadRAM512(const RAM512& ram, 
                   const bit9_u& address);
void WriteRAM512(RAM512& ram, 
                 const bit9_u& address, 
                 const byte2_u& in, 
                 const bit1_u& load);

struct RAM4k;
byte2_u ReadRAM4k(const RAM4k& ram, 
                  const bit12_u& address);
void WriteRAM4k(RAM4k& ram, 
                const bit12_u& address, 
                const byte2_u& in, 
                const bit1_u& load);                  

struct RAM16k;
byte2_u ReadRAM16k(const RAM16k& ram, 
                   const bit14_u& address);


#endif // MEMORY_H

