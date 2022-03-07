#ifndef ARITHMETIC_CHIPS_H
#define ARITHMETIC_CHIPS_H

#include "bits.h" 

bit2 HalfAdder(const bit& a, const bit& b); 
bit2 FullAdder(const bit& a, const bit& b, const bit& c); 
byte2 Add16(const byte2& a, const byte2& b);
byte2 Inc16(const byte2& a);
byte2 ALU(const byte2& a, const byte2& b, const bit& za, const bit& na,
          const bit& zb, const bit& nb, const bit& f, const bit& no,
          bit& zr, bit& ng); 

#endif // ARITHMETIC_CHIPS_H
