#ifndef LOGIC_GATES_H
#define LOGIC_GATES_H   

#include "bits.h"

bit Nand(const bit& a, const bit& b);
bit Not(const bit& a); 
bit And(const bit& a, const bit& b); 
bit Or(const bit& a, const bit& b); 
bit Xor(const bit& a, const bit& b); 
bit Mux(const bit& a, const bit& b, const bit& sel); 
bit2 DMux(const bit& a, const bit& sel); 
bit AndMuxOr(const bit& a, const bit& b, const bit& sel); 
byte2 Not16(const byte2& a); 
byte2 And16(const byte2& a, const byte2& b); 
byte2 Or16(const byte2& a, const byte2& b); 
byte2 Mux16(const byte2& a, const byte2& b, const bit& sel); 
bit Or8Way(const byte& a); 
byte2 Mux4Way16(const byte2& a, const byte2& b,
                const byte2& c, const byte2& d, const bit2& sel); 
byte2 Mux8Way16(const byte2& a, const byte2& b,
                const byte2& c, const byte2& d,
                const byte2& e, const byte2& f, 
                const byte2& g, const byte2& h, const bit3& sel); 
bit4 DMux4Way(const bit& a, const bit2& sel); 
byte DMux8Way(const bit& a, const bit3& sel); 

#endif // LOGIC_GATES_H
