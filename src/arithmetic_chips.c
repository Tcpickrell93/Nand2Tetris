#include "arithmetic_chips.h"
#include "logic_gates.h"
#include "bits.h"


union bit2_u* HalfAdder(union bit1_u *a, 
                        union bit1_u *b) {
    /* Returns [carry, sum] in bits (sum=LSB) */
    union bit2_u result = { .value = 0 };
    result.bit2_s.val0 = Xor(a, b)->value;
    result.bit2_s.val1 = And(a, b)->value;

    return &result;
}

union bit2_u* FullAdder(union bit1_u *a, 
                        union bit1_u *b, 
                        union bit1_u *c) {
    /* Returns [carry, sum] in bits (sum=LSB) */
    union bit2_u* half_res = HalfAdder(a, b);
    union bit1_u half_res_0 = { .value = half_res->bit2_s.val0 };
    union bit1_u half_res_1 = { .value = half_res->bit2_s.val1 };
    union bit2_u* result = HalfAdder(&half_res_0, c);
    union bit1_u result_1 = { .value = result->bit2_s.val1 };
    result->bit2_s.val1 = Or(&half_res_1, &result_1)->value;

    return result;
}
    
union byte2_u* Add16(union byte2_u *a, 
                     union byte2_u *b) {
    union byte2_u sum = { .value = 0 };
    union bit1_u carry = { .value = 0 };
    union bit1_u a_bit = { .value = a->byte2_s.val0 };
    union bit1_u b_bit = { .value = b->byte2_s.val0 };
    union bit2_u* temp_res = FullAdder(&a_bit, &b_bit, &carry);
    sum.byte2_s.val0 = temp_res->bit2_s.val0;
    carry.bit1_s.val = temp_res->bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val1;
    b_bit.bit1_s.val = b->byte2_s.val1; 
    temp_res = FullAdder(&a_bit, &b_bit, &carry);
    sum.byte2_s.val1 = temp_res->bit2_s.val0;
    carry.bit1_s.val = temp_res->bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val2;
    b_bit.bit1_s.val = b->byte2_s.val2; 
    temp_res = FullAdder(&a_bit, &b_bit, &carry);
    sum.byte2_s.val2 = temp_res->bit2_s.val0;
    carry.bit1_s.val = temp_res->bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val3;
    b_bit.bit1_s.val = b->byte2_s.val3; 
    temp_res = FullAdder(&a_bit, &b_bit, &carry);
    sum.byte2_s.val3 = temp_res->bit2_s.val0;
    carry.bit1_s.val = temp_res->bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val4;
    b_bit.bit1_s.val = b->byte2_s.val4; 
    temp_res = FullAdder(&a_bit, &b_bit, &carry);
    sum.byte2_s.val4 = temp_res->bit2_s.val0;
    carry.bit1_s.val = temp_res->bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val5;
    b_bit.bit1_s.val = b->byte2_s.val5; 
    temp_res = FullAdder(&a_bit, &b_bit, &carry);
    sum.byte2_s.val5 = temp_res->bit2_s.val0;
    carry.bit1_s.val = temp_res->bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val6;
    b_bit.bit1_s.val = b->byte2_s.val6; 
    temp_res = FullAdder(&a_bit, &b_bit, &carry);
    sum.byte2_s.val6 = temp_res->bit2_s.val0;
    carry.bit1_s.val = temp_res->bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val7;
    b_bit.bit1_s.val = b->byte2_s.val7; 
    temp_res = FullAdder(&a_bit, &b_bit, &carry);
    sum.byte2_s.val7 = temp_res->bit2_s.val0;
    carry.bit1_s.val = temp_res->bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val8;
    b_bit.bit1_s.val = b->byte2_s.val8; 
    temp_res = FullAdder(&a_bit, &b_bit, &carry);
    sum.byte2_s.val8 = temp_res->bit2_s.val0;
    carry.bit1_s.val = temp_res->bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val9;
    b_bit.bit1_s.val = b->byte2_s.val9; 
    temp_res = FullAdder(&a_bit, &b_bit, &carry);
    sum.byte2_s.val9 = temp_res->bit2_s.val0;
    carry.bit1_s.val = temp_res->bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val10;
    b_bit.bit1_s.val = b->byte2_s.val10; 
    temp_res = FullAdder(&a_bit, &b_bit, &carry);
    sum.byte2_s.val10 = temp_res->bit2_s.val0;
    carry.bit1_s.val = temp_res->bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val11;
    b_bit.bit1_s.val = b->byte2_s.val11; 
    temp_res = FullAdder(&a_bit, &b_bit, &carry);
    sum.byte2_s.val11 = temp_res->bit2_s.val0;
    carry.bit1_s.val = temp_res->bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val12;
    b_bit.bit1_s.val = b->byte2_s.val12; 
    temp_res = FullAdder(&a_bit, &b_bit, &carry);
    sum.byte2_s.val12 = temp_res->bit2_s.val0;
    carry.bit1_s.val = temp_res->bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val13;
    b_bit.bit1_s.val = b->byte2_s.val13; 
    temp_res = FullAdder(&a_bit, &b_bit, &carry);
    sum.byte2_s.val13 = temp_res->bit2_s.val0;
    carry.bit1_s.val = temp_res->bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val14;
    b_bit.bit1_s.val = b->byte2_s.val14; 
    temp_res = FullAdder(&a_bit, &b_bit, &carry);
    sum.byte2_s.val14 = temp_res->bit2_s.val0;
    carry.bit1_s.val = temp_res->bit2_s.val1;

    a_bit.bit1_s.val = a->byte2_s.val15;
    b_bit.bit1_s.val = b->byte2_s.val15; 
    temp_res = FullAdder(&a_bit, &b_bit, &carry);
    sum.byte2_s.val15 = temp_res->bit2_s.val0;
    carry.bit1_s.val = temp_res->bit2_s.val1;

    return &sum;
}
    
union byte2_u* Inc16(union byte2_u *a) {
    union byte2_u increment = { .value = 1 };
    return Add16(a, &increment);
}

union byte2_u* ALU(union byte2_u *a, 
                   union byte2_u *b, 
                   union bit1_u *za, 
                   union bit1_u *na,
                   union bit1_u *zb, 
                   union bit1_u *nb, 
                   union bit1_u *f, 
                   union bit1_u *no,
                   union bit1_u *zr, 
                   union bit1_u *ng) {
    union byte2_u a_copy = *a;
    union byte2_u b_copy = *b;
    union byte2_u output = { .value = 0 };
    if (za->value == 1) {
        a_copy.value = 0;
    }
    if (na->value == 1) {
        a_copy.value = Not16(&a_copy)->value;
    }
    if (zb->value == 1) {
        b_copy.value = 0;
    }
    if (nb->value == 1) {
        b_copy.value = Not16(&b_copy)->value;
    }
    if (f->value == 1) {
        output.value = Add16(&a_copy, &b_copy)->value;
    } else {
        output.value = And16(&a_copy, &b_copy)->value;
    }
    if (no->value == 1) {
        output.value = Not16(&output)->value;
    }
    if (output.value == 0) {
        zr->bit1_s.val = 1;
    }
    if (output.byte2_s.val15 == 1) {
        ng->bit1_s.val = 1;
    }
    return &output;
}
