#ifndef ARITHMETIC_CHIPS_H
#define ARITHMETIC_CHIPS_H

#include "bits.h" 

bit2_u HalfAdder(const bit1_u& a, 
                 const bit1_u& b); 

bit2_u FullAdder(const bit1_u& a, 
                 const bit1_u& b, 
                 const bit1_u& c); 

byte2_u Add16(const byte2_u& a, 
              const byte2_u& b);

byte2_u Inc16(const byte2_u& a);

byte2_u ALU(const byte2_u& a, 
            const byte2_u& b, 
            const bit1_u& za, 
            const bit1_u& na,
            const bit1_u& zb, 
            const bit1_u& nb, 
            const bit1_u& f, 
            const bit1_u& no,
            bit1_u& zr, 
            bit1_u& ng); 

#endif // ARITHMETIC_CHIPS_H
