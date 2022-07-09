#ifndef LOGIC_GATES_H
#define LOGIC_GATES_H   

#include "bits.h"

bit1_u Nand(const bit1_u& a, 
            const bit1_u& b);

bit1_u Not(const bit1_u& a); 

bit1_u And(const bit1_u& a, 
           const bit1_u& b); 

bit1_u Or(const bit1_u& a, 
          const bit1_u& b); 

bit1_u Xor(const bit1_u& a, 
           const bit1_u& b); 

bit1_u Mux(const bit1_u& a, 
           const bit1_u& b, 
           const bit1_u& sel); 

bit2_u DMux(const bit1_u& a, 
            const bit1_u& sel); 

bit1_u AndMuxOr(const bit1_u& a, 
                const bit1_u& b, 
                const bit1_u& sel); 

byte2_u Not16(const byte2_u& a); 
byte2_u And16(const byte2_u& a, 
              const byte2_u& b); 

byte2_u Or16(const byte2_u& a, 
             const byte2_u& b); 

byte2_u Mux16(const byte2_u& a, 
              const byte2_u& b, 
              const bit1_u& sel); 

bit1_u Or8Way(const byte1_u& a); 

byte2_u Mux4Way16(const byte2_u& a, 
                  const byte2_u& b,
                  const byte2_u& c, 
                  const byte2_u& d, 
                  const bit2_u& sel); 

byte2_u Mux8Way16(const byte2_u& a, 
                  const byte2_u& b,
                  const byte2_u& c, 
                  const byte2_u& d,
                  const byte2_u& e, 
                  const byte2_u& f, 
                  const byte2_u& g, 
                  const byte2_u& h, 
                  const bit3_u& sel); 

bit4_u DMux4Way(const bit1_u& a, 
                const bit2_u& sel); 
                
byte1_u DMux8Way(const bit1_u& a, 
                 const bit3_u& sel); 

#endif // LOGIC_GATES_H
