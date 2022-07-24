#ifndef LOGIC_GATES_H
#define LOGIC_GATES_H   

#include "bits.h"

void Nand(union bit1_u *a, 
          union bit1_u *b,
          union bit1_u *result);

void Not(union bit1_u *a,
         union bit1_u *result); 

void And(union bit1_u *a, 
         union bit1_u *b,
         union bit1_u *result); 

void Or(union bit1_u *a, 
        union bit1_u *b,
        union bit1_u *result); 

void Xor(union bit1_u *a, 
         union bit1_u *b,
         union bit1_u *result); 

void Mux(union bit1_u *a, 
         union bit1_u *b, 
         union bit1_u *sel,
         union bit1_u *result); 

void DMux(union bit1_u *a, 
          union bit1_u *sel,
          union bit2_u *result); 

void AndMuxOr(union bit1_u *a, 
              union bit1_u *b, 
              union bit1_u *sel,
              union bit1_u *result); 

void Not16(union byte2_u *a,
           union byte2_u *result); 

void And16(union byte2_u *a, 
           union byte2_u *b,
           union byte2_u *result); 

void Or16(union byte2_u *a, 
          union byte2_u *b,
          union byte2_u *result); 

void Mux16(union byte2_u *a, 
           union byte2_u *b, 
           union bit1_u *sel,
           union byte2_u *result); 

void Or8Way(union byte1_u *a,
            union byte1_u *result); 

void Mux4Way16(union byte2_u *a, 
               union byte2_u *b,
               union byte2_u *c, 
               union byte2_u *d, 
               union bit2_u *sel,
               union byte2_u *result); 

void Mux8Way16(union byte2_u *a, 
               union byte2_u *b,
               union byte2_u *c, 
               union byte2_u *d,
               union byte2_u *e, 
               union byte2_u *f, 
               union byte2_u *g, 
               union byte2_u *h, 
               union bit3_u *sel,
               union byte2_u *result); 

void DMux4Way(union bit1_u *a, 
              union bit2_u *sel,
              union bit4_u *result); 
                
void DMux8Way(union bit1_u *a, 
              union bit3_u *sel,
              union byte1_u *result); 

#endif // LOGIC_GATES_H
