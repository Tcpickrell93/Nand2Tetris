#ifndef ARITHMETIC_CHIPS_H
#define ARITHMETIC_CHIPS_H

#include "bits.h" 

union bit2_u* HalfAdder(union bit1_u *a, 
                        union bit1_u *b); 

union bit2_u* FullAdder(union bit1_u *a, 
                        union bit1_u *b, 
                        union bit1_u *c); 

union byte2_u* Add16(union byte2_u *a, 
                     union byte2_u *b);

union byte2_u* Inc16(union byte2_u *a);

union byte2_u* ALU(union byte2_u *a, 
                   union byte2_u *b, 
                   union bit1_u *za, 
                   union bit1_u *na,
                   union bit1_u *zb, 
                   union bit1_u *nb, 
                   union bit1_u *f, 
                   union bit1_u *no,
                   union bit1_u *zr, 
                   union bit1_u *ng); 

#endif // ARITHMETIC_CHIPS_H
