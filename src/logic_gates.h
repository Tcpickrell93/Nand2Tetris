#ifndef LOGIC_GATES_H
#define LOGIC_GATES_H   

#include "bits.h"

union bit1_u* Nand(union bit1_u *a, 
                   union bit1_u *b);

union bit1_u* Not(union bit1_u *a); 

union bit1_u* And(union bit1_u *a, 
                 union bit1_u *b); 

union bit1_u* Or(union bit1_u *a, 
                 union bit1_u *b); 

union bit1_u* Xor(union bit1_u *a, 
                  union bit1_u *b); 

union bit1_u* Mux(union bit1_u *a, 
                  union bit1_u *b, 
                  union bit1_u *sel); 

union bit2_u* DMux(union bit1_u *a, 
                   union bit1_u *sel); 

union bit1_u* AndMuxOr(union bit1_u *a, 
                       union bit1_u *b, 
                       union bit1_u *sel); 

union byte2_u* Not16(union byte2_u *a); 

union byte2_u* And16(union byte2_u *a, 
                     union byte2_u *b); 

union byte2_u* Or16(union byte2_u *a, 
                    union byte2_u *b); 

union byte2_u* Mux16(union byte2_u *a, 
                     union byte2_u *b, 
                     union bit1_u *sel); 

union bit1_u* Or8Way(union byte1_u *a); 

union byte2_u* Mux4Way16(union byte2_u *a, 
                         union byte2_u *b,
                         union byte2_u *c, 
                         union byte2_u *d, 
                         union bit2_u *sel); 

union byte2_u* Mux8Way16(union byte2_u *a, 
                         union byte2_u *b,
                         union byte2_u *c, 
                         union byte2_u *d,
                         union byte2_u *e, 
                         union byte2_u *f, 
                         union byte2_u *g, 
                         union byte2_u *h, 
                         union bit3_u *sel); 

union bit4_u* DMux4Way(union bit1_u *a, 
                       union bit2_u *sel); 
                
union byte1_u* DMux8Way(union bit1_u *a, 
                        union bit3_u *sel); 

#endif // LOGIC_GATES_H
