#include "arithmetic_chips.h"
#include "logic_gates.h"
#include "bits.h"


void HalfAdder(union bit1_u *a, 
               union bit1_u *b,
               union bit2_u *result) {
    /* 
    a       b       sum     carry
    -----------------------------
    0       0       0       0
    0       1       1       0
    1       0       1       0
    1       1       0       0
    
    Returns [carry, sum] in bits (sum=LSB) 
    */
    union bit1_u temp_res = { .value = 0 };
    // Sum value can be determined from Xor of a and b
    Xor(a, b, &temp_res);
    result->bit2_s.val0 = temp_res.value;
    // Carry value can be determined from And of a and b
    And(a, b, &temp_res);
    result->bit2_s.val1 = temp_res.value;
}

void FullAdder(union bit1_u *a, 
               union bit1_u *b, 
               union bit1_u *c,
               union bit2_u *result) {
    /* 
    a       b       c       sum     carry
    -------------------------------------
    0       0       0       0       0
    0       0       1       1       0
    0       1       0       1       0
    0       1       1       0       1
    1       0       0       1       0
    1       0       1       0       1
    1       1       0       0       1
    1       1       1       1       1

    Returns [carry, sum] in bits (sum=LSB) 
    */
    result->value = 0;
    union bit2_u temp_res = { .value = 0 };
    // Perform half adder with a and b
    HalfAdder(a, b, &temp_res);
    union bit1_u temp_res_0 = { .value = temp_res.bit2_s.val0 };
    union bit1_u temp_res_1 = { .value = temp_res.bit2_s.val1 };
    // Perform half adder with carry from first half adder and carry from full adder
    HalfAdder(&temp_res_0, c, result);
    union bit1_u result_1 = { .value = result->bit2_s.val1 };
    Or(&temp_res_1, &result_1, &temp_res_0); // reuse temp_res_0
    result->bit2_s.val1 = temp_res_0.value;
}
    
void Add16(union byte2_u *a, 
           union byte2_u *b,
           union byte2_u *result) {
    union bit1_u carry = { .value = 0 };
    union bit2_u temp_res = { .value = 0 };
    union bit1_u a_bit = { .value = a->byte2_s.val0 };
    union bit1_u b_bit = { .value = b->byte2_s.val0 };
    FullAdder(&a_bit, &b_bit, &carry, &temp_res);
    result->byte2_s.val0 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val1;
    b_bit.bit1_s.val = b->byte2_s.val1; 
    FullAdder(&a_bit, &b_bit, &carry, &temp_res);
    result->byte2_s.val1 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val2;
    b_bit.bit1_s.val = b->byte2_s.val2; 
    FullAdder(&a_bit, &b_bit, &carry, &temp_res);
    result->byte2_s.val2 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val3;
    b_bit.bit1_s.val = b->byte2_s.val3; 
    FullAdder(&a_bit, &b_bit, &carry, &temp_res);
    result->byte2_s.val3 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val4;
    b_bit.bit1_s.val = b->byte2_s.val4; 
    FullAdder(&a_bit, &b_bit, &carry, &temp_res);
    result->byte2_s.val4 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val5;
    b_bit.bit1_s.val = b->byte2_s.val5; 
    FullAdder(&a_bit, &b_bit, &carry, &temp_res);
    result->byte2_s.val5 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val6;
    b_bit.bit1_s.val = b->byte2_s.val6; 
    FullAdder(&a_bit, &b_bit, &carry, &temp_res);
    result->byte2_s.val6 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val7;
    b_bit.bit1_s.val = b->byte2_s.val7; 
    FullAdder(&a_bit, &b_bit, &carry, &temp_res);
    result->byte2_s.val7 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val8;
    b_bit.bit1_s.val = b->byte2_s.val8; 
    FullAdder(&a_bit, &b_bit, &carry, &temp_res);
    result->byte2_s.val8 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val9;
    b_bit.bit1_s.val = b->byte2_s.val9; 
    FullAdder(&a_bit, &b_bit, &carry, &temp_res);
    result->byte2_s.val9 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val10;
    b_bit.bit1_s.val = b->byte2_s.val10; 
    FullAdder(&a_bit, &b_bit, &carry, &temp_res);
    result->byte2_s.val10 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val11;
    b_bit.bit1_s.val = b->byte2_s.val11; 
    FullAdder(&a_bit, &b_bit, &carry, &temp_res);
    result->byte2_s.val11 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val12;
    b_bit.bit1_s.val = b->byte2_s.val12; 
    FullAdder(&a_bit, &b_bit, &carry, &temp_res);
    result->byte2_s.val12 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val13;
    b_bit.bit1_s.val = b->byte2_s.val13; 
    FullAdder(&a_bit, &b_bit, &carry, &temp_res);
    result->byte2_s.val13 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val14;
    b_bit.bit1_s.val = b->byte2_s.val14; 
    FullAdder(&a_bit, &b_bit, &carry, &temp_res);
    result->byte2_s.val14 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val15;
    b_bit.bit1_s.val = b->byte2_s.val15; 
    FullAdder(&a_bit, &b_bit, &carry, &temp_res);
    result->byte2_s.val15 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;
}
    
union byte2_u Inc16(union byte2_u *a) {
    union byte2_u increment = { .value = 1 };
    union byte2_u result = { .value = 0 };
    Add16(a, &increment, &result);
    return result;
}

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
         union byte2_u *result) {
    result->value = 0;
    union byte2_u a_copy = { .value = a->value };
    union byte2_u b_copy = { .value = b->value };
    if (za->value == 1) {
        a_copy.value = 0;
    }
    if (na->value == 1) {
        Not16(&a_copy, &a_copy);
    }
    if (zb->value == 1) {
        b_copy.value = 0;
    }
    if (nb->value == 1) {
        Not16(&b_copy, &b_copy);
    }
    if (f->value == 1) {
        Add16(&a_copy, &b_copy, result);
    } else {
        And16(&a_copy, &b_copy, result);
    }
    if (no->value == 1) {
        Not16(result, result);
    }
    if (result->value == 0) {
        zr->bit1_s.val = 1;
    }
    if (result->byte2_s.val15 == 1) {
        ng->bit1_s.val = 1;
    }
}
