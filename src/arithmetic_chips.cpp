#include "arithmetic_chips.h"
#include "logic_gates.h"


bit2_u HalfAdder(const bit1_u& a, 
                 const bit1_u& b) {
    /* Returns [carry, sum] in bits (sum=LSB) */
    bit2_u result{};
    result.bit2_s.val0 = Xor(a, b).value;
    result.bit2_s.val1 = And(a, b).value;
    return result;
}

bit2_u FullAdder(const bit1_u& a, 
                 const bit1_u& b, 
                 const bit1_u& c) {
    /* Returns [carry, sum] in bits (sum=LSB) */
    bit2_u half_res { HalfAdder(a, b) };
    bit1_u half_res_0 { half_res.bit2_s.val0 };
    bit1_u half_res_1 { half_res.bit2_s.val1 };
    bit2_u result { HalfAdder(half_res_0, c) };
    bit1_u result_1 { result.bit2_s.val1 };
    result.bit2_s.val1 = Or(half_res_1, result_1).value;
    return result;
}
    
byte2_u Add16(const byte2_u& a, 
              const byte2_u& b) {
    byte2_u sum {};
    bit1_u carry {};
    bit1_u a_bit { a.byte2_s.val0 };
    bit1_u b_bit { b.byte2_s.val0 };
    bit2_u temp_res { FullAdder(a_bit, b_bit, carry) };
    sum.byte2_s.val0 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a.byte2_s.val1;
    b_bit.bit1_s.val = b.byte2_s.val1; 
    temp_res = FullAdder(a_bit, b_bit, carry);
    sum.byte2_s.val1 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a.byte2_s.val2;
    b_bit.bit1_s.val = b.byte2_s.val2; 
    temp_res = FullAdder(a_bit, b_bit, carry);
    sum.byte2_s.val2 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a.byte2_s.val3;
    b_bit.bit1_s.val = b.byte2_s.val3; 
    temp_res = FullAdder(a_bit, b_bit, carry);
    sum.byte2_s.val3 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a.byte2_s.val4;
    b_bit.bit1_s.val = b.byte2_s.val4; 
    temp_res = FullAdder(a_bit, b_bit, carry);
    sum.byte2_s.val4 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a.byte2_s.val5;
    b_bit.bit1_s.val = b.byte2_s.val5; 
    temp_res = FullAdder(a_bit, b_bit, carry);
    sum.byte2_s.val5 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a.byte2_s.val6;
    b_bit.bit1_s.val = b.byte2_s.val6; 
    temp_res = FullAdder(a_bit, b_bit, carry);
    sum.byte2_s.val6 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a.byte2_s.val7;
    b_bit.bit1_s.val = b.byte2_s.val7; 
    temp_res = FullAdder(a_bit, b_bit, carry);
    sum.byte2_s.val7 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a.byte2_s.val8;
    b_bit.bit1_s.val = b.byte2_s.val8; 
    temp_res = FullAdder(a_bit, b_bit, carry);
    sum.byte2_s.val8 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a.byte2_s.val9;
    b_bit.bit1_s.val = b.byte2_s.val9; 
    temp_res = FullAdder(a_bit, b_bit, carry);
    sum.byte2_s.val9 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a.byte2_s.val10;
    b_bit.bit1_s.val = b.byte2_s.val10; 
    temp_res = FullAdder(a_bit, b_bit, carry);
    sum.byte2_s.val10 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a.byte2_s.val11;
    b_bit.bit1_s.val = b.byte2_s.val11; 
    temp_res = FullAdder(a_bit, b_bit, carry);
    sum.byte2_s.val11 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a.byte2_s.val12;
    b_bit.bit1_s.val = b.byte2_s.val12; 
    temp_res = FullAdder(a_bit, b_bit, carry);
    sum.byte2_s.val12 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a.byte2_s.val13;
    b_bit.bit1_s.val = b.byte2_s.val13; 
    temp_res = FullAdder(a_bit, b_bit, carry);
    sum.byte2_s.val13 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a.byte2_s.val14;
    b_bit.bit1_s.val = b.byte2_s.val14; 
    temp_res = FullAdder(a_bit, b_bit, carry);
    sum.byte2_s.val14 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    a_bit.bit1_s.val = a.byte2_s.val15;
    b_bit.bit1_s.val = b.byte2_s.val15; 
    temp_res = FullAdder(a_bit, b_bit, carry);
    sum.byte2_s.val15 = temp_res.bit2_s.val0;
    carry.bit1_s.val = temp_res.bit2_s.val1;

    return sum;
}
    
byte2_u Inc16(const byte2_u& a) {
    byte2_u increment{ 1 };
    return Add16(a, increment);
}

byte2_u ALU(const byte2_u& a, 
            const byte2_u& b, 
            const bit1_u& za, 
            const bit1_u& na,
            const bit1_u& zb, 
            const bit1_u& nb, 
            const bit1_u& f, 
            const bit1_u& no,
            bit1_u& zr, 
            bit1_u& ng) {
    byte2_u a_copy { a };
    byte2_u b_copy { b };
    byte2_u output {};
    if (za.value == 1) {
        a_copy.value = 0;
    }
    if (na.value == 1) {
        a_copy = Not16(a_copy);
    }
    if (zb.value == 1) {
        b_copy.value = 0;
    }
    if (nb.value == 1) {
        b_copy = Not16(b_copy);
    }
    if (f.value == 1) {
        output = Add16(a_copy, b_copy);
    } else {
        output = And16(a_copy, b_copy);
    }
    if (no.value == 1) {
        output = Not16(output);
    }
    if (output.value == 0) {
        zr.bit1_s.val = 1;
    }
    if (output.byte2_s.val15 == 1) {
        ng.bit1_s.val = 1;
    }
    return output;
}
