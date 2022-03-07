#include "arithmetic_chips.h"
#include "logic_gates.h"


bit2 HalfAdder(const bit& a, const bit& b) {
    /* Returns [carry, sum] in bits (sum=LSB) */
    bit2 result{};
    result[0] = Xor(a, b)[0];
    result[1] = And(a, b)[0];
    return result;
}

bit2 FullAdder(const bit& a, const bit& b, const bit& c) {
    /* Returns [carry, sum] in bits (sum=LSB) */
    bit2 temp_res{ HalfAdder(a, b) };
    bit2 result{ HalfAdder((bit)temp_res[0], c) };
    result[1] = Or((bit)temp_res[1], (bit)result[1])[0];
    return result;
}
    
byte2 Add16(const byte2& a, const byte2& b) {
    byte2 sum{};
    bit carry{};
    for (int i = 0; i < 16; i++) {
        bit2 temp_res{ FullAdder((bit)a[i], (bit)b[i], carry) };
        sum[i] = temp_res[0];
        carry = (bit)temp_res[1];
    }
    return sum;
}
    
byte2 Inc16(const byte2& a) {
    byte2 increment{ 0b0000'0000'0000'0001u };
    return Add16(a, increment);
}

byte2 ALU(const byte2& a, const byte2& b, const bit& za, const bit& na,
          const bit& zb, const bit& nb, const bit& f, const bit& no,
          bit& zr, bit& ng) {
    byte2 a_copy{ a };
    byte2 b_copy{ b };
    byte2 output{};
    if (za[0] == 1) {
        a_copy.reset();
    }
    if (na[0] == 1) {
        a_copy = Not16(a_copy);
    }
    if (zb[0] == 1) {
        b_copy.reset();
    }
    if (nb[0] == 1) {
        b_copy = Not16(b_copy);
    }
    if (f[0] == 1) {
        output = Add16(a_copy, b_copy);
    } else {
        output = And16(a_copy, b_copy);
    }
    if (no[0] == 1) {
        output = Not16(output);
    }
    if (output == 0) {
        zr[0] = 1;
    }
    if (output[15] == 1) {
        ng[0] = 1;
    }
    return output;
}
