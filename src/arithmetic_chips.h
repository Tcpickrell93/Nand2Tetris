#ifndef ARITHMETIC_CHIPS_H
#define ARITHMETIC_CHIPS_H

#include "bits.h" 


void HalfAdder(union bit1_u *a, 
               union bit1_u *b,
               union bit2_u *result); 

void FullAdder(union bit1_u *a, 
               union bit1_u *b, 
               union bit1_u *c,
               union bit2_u *result); 

void Add16(union byte2_u *a, 
           union byte2_u *b,
           union byte2_u *result);

void Inc16(union byte2_u *a,
           union byte2_u *result);

void ALU(union byte2_u *a, 
         union byte2_u *b, 
         union bit1_u *za, 
         union bit1_u *na,
         union bit1_u *zb, 
         union bit1_u *nb, 
         union bit1_u *f, 
         union bit1_u *no,
         union bit1_u *zr, 
         union bit1_u *ng,
         union byte2_u *result); 

#endif // ARITHMETIC_CHIPS_H
