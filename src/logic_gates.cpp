#include "logic_gates.h"


bit1_u Nand(const bit1_u& a, const bit1_u& b) {
    /* Nand Gate */
    bit1_u result { ~(a.bit1_s.val & b.bit1_s.val) };
    return result;
}

bit1_u Not(const bit1_u& a) {
    /* Not Gate */
    return Nand(a, a);
}

bit1_u And(const bit1_u& a, const bit1_u& b) {
    /* And Gate */
    return Not(Nand(a, b));
}

bit1_u Or(const bit1_u& a, const bit1_u& b) {
    /* Or Gate */
    return Not(And(Not(a), Not(b)));
}

bit1_u Xor(const bit1_u& a, const bit1_u& b) {
    /* Xor Gate */
    return Or(And(a, Not(b)), And(b, Not(a)));
}

bit1_u Mux(const bit1_u& a, const bit1_u& b, const bit1_u& sel) {
    /* 2-bit Multiplexor */
    if (sel.bit1_s.val == 0) { return a; }
    return b;
}

bit2_u DMux(const bit1_u& a, const bit1_u& sel) {
    /* 2-bit Demultiplexor */
    bit2_u result{};
    if (sel.bit1_s.val == 0) {
        result.bit2_s.val0 = a.bit1_s.val;
        return result;
    }
    result.bit2_s.val1 = a.bit1_s.val;
    return result;
}

bit1_u AndMuxOr(const bit1_u& a, const bit1_u& b, const bit1_u& sel) {
    /* Programmable Gate */
    return Mux(And(a, b), Or(a, b), sel);
}

byte2_u Not16(const byte2_u& a) {
    /* 16-bit Not Gate */
    byte2_u result {};
    bit1_u a_bit { a.byte2_s.val0 };
    result.byte2_s.val0 = Nand(a_bit, a_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val1;
    result.byte2_s.val1 = Nand(a_bit, a_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val2;
    result.byte2_s.val2 = Nand(a_bit, a_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val3;
    result.byte2_s.val3 = Nand(a_bit, a_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val4;
    result.byte2_s.val4 = Nand(a_bit, a_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val5;
    result.byte2_s.val5 = Nand(a_bit, a_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val6;
    result.byte2_s.val6 = Nand(a_bit, a_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val7;
    result.byte2_s.val7 = Nand(a_bit, a_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val8;
    result.byte2_s.val8 = Nand(a_bit, a_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val9;
    result.byte2_s.val9 = Nand(a_bit, a_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val10;
    result.byte2_s.val10 = Nand(a_bit, a_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val11;
    result.byte2_s.val11 = Nand(a_bit, a_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val12;
    result.byte2_s.val12 = Nand(a_bit, a_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val13;
    result.byte2_s.val13 = Nand(a_bit, a_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val14;
    result.byte2_s.val14 = Nand(a_bit, a_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val15;
    result.byte2_s.val15 = Nand(a_bit, a_bit).bit1;
    return result;
}

byte2_u And16(const byte2_u& a, const byte2_u& b) {
    /* 16-bit And Gate */
    byte2_u result {};
    bit1_u a_bit { a.byte2_s.val0 };
    bit1_u b_bit { b.byte2_s.val0 };
    result.byte2_s.val0 = And(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val1;
    b_bit.bit1_s.val = b.byte2_s.val1;
    result.byte2_s.val1 = And(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val2;
    b_bit.bit1_s.val = b.byte2_s.val2;
    result.byte2_s.val2 = And(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val3;
    b_bit.bit1_s.val = b.byte2_s.val3;
    result.byte2_s.val3 = And(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val4;
    b_bit.bit1_s.val = b.byte2_s.val4;
    result.byte2_s.val4 = And(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val5;
    b_bit.bit1_s.val = b.byte2_s.val5;
    result.byte2_s.val5 = And(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val6;
    b_bit.bit1_s.val = b.byte2_s.val6;
    result.byte2_s.val6 = And(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val7;
    b_bit.bit1_s.val = b.byte2_s.val7;
    result.byte2_s.val7 = And(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val8;
    b_bit.bit1_s.val = b.byte2_s.val8;
    result.byte2_s.val8 = And(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val9;
    b_bit.bit1_s.val = b.byte2_s.val9;
    result.byte2_s.val9 = And(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val10;
    b_bit.bit1_s.val = b.byte2_s.val10;
    result.byte2_s.val10 = And(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val11;
    b_bit.bit1_s.val = b.byte2_s.val11;
    result.byte2_s.val11 = And(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val12;
    b_bit.bit1_s.val = b.byte2_s.val12;
    result.byte2_s.val12 = And(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val13;
    b_bit.bit1_s.val = b.byte2_s.val13;
    result.byte2_s.val13 = And(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val14;
    b_bit.bit1_s.val = b.byte2_s.val14;
    result.byte2_s.val14 = And(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val15;
    b_bit.bit1_s.val = b.byte2_s.val15;
    result.byte2_s.val15 = And(a_bit, b_bit).bit1;
    return result;
}

byte2_u Or16(const byte2_u& a, const byte2_u& b) {
    /* 16-bit Or Gate */
    byte2_u result {};
    bit1_u a_bit { a.byte2_s.val0 };
    bit1_u b_bit { b.byte2_s.val0 };
    result.byte2_s.val0 = Or(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val1;
    b_bit.bit1_s.val = b.byte2_s.val1;
    result.byte2_s.val1 = Or(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val2;
    b_bit.bit1_s.val = b.byte2_s.val2;
    result.byte2_s.val2 = Or(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val3;
    b_bit.bit1_s.val = b.byte2_s.val3;
    result.byte2_s.val3 = Or(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val4;
    b_bit.bit1_s.val = b.byte2_s.val4;
    result.byte2_s.val4 = Or(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val5;
    b_bit.bit1_s.val = b.byte2_s.val5;
    result.byte2_s.val5 = Or(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val6;
    b_bit.bit1_s.val = b.byte2_s.val6;
    result.byte2_s.val6 = Or(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val7;
    b_bit.bit1_s.val = b.byte2_s.val7;
    result.byte2_s.val7 = Or(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val8;
    b_bit.bit1_s.val = b.byte2_s.val8;
    result.byte2_s.val8 = Or(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val9;
    b_bit.bit1_s.val = b.byte2_s.val9;
    result.byte2_s.val9 = Or(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val10;
    b_bit.bit1_s.val = b.byte2_s.val10;
    result.byte2_s.val10 = Or(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val11;
    b_bit.bit1_s.val = b.byte2_s.val11;
    result.byte2_s.val11 = Or(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val12;
    b_bit.bit1_s.val = b.byte2_s.val12;
    result.byte2_s.val12 = Or(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val13;
    b_bit.bit1_s.val = b.byte2_s.val13;
    result.byte2_s.val13 = Or(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val14;
    b_bit.bit1_s.val = b.byte2_s.val14;
    result.byte2_s.val14 = Or(a_bit, b_bit).bit1;
    a_bit.bit1_s.val = a.byte2_s.val15;
    b_bit.bit1_s.val = b.byte2_s.val15;
    result.byte2_s.val15 = Or(a_bit, b_bit).bit1;
    return result;
}

byte2_u Mux16(const byte2_u& a, const byte2_u& b, const bit1_u& sel) {
    /* 16-bit Multiplexor */
    if (sel.bit1 == 0) { return a; }
    return b;
}

bit1_u Or8Way(const byte1_u& a) {
    /* 8-way Or Gate */
    bit1_u result { a.byte1 > 0 };
    return result;
}

byte2_u Mux4Way16(const byte2_u& a, const byte2_u& b,
                  const byte2_u& c, const byte2_u& d, const bit2_u& sel) {
    /* 16-bit 4-Way Multiplexor */
    bit1_u sel_0 { sel.bit2_s.val0 };
    bit1_u sel_1 { sel.bit2_s.val1 };
    return Mux16(Mux16(a, b, sel_0), Mux16(c, d, sel_0), sel_1);
}

byte2_u Mux8Way16(const byte2_u& a, const byte2_u& b,
                  const byte2_u& c, const byte2_u& d,
                  const byte2_u& e, const byte2_u& f, 
                  const byte2_u& g, const byte2_u& h, const bit3_u& sel) {
    /* 16-bit 8-Way Multiplexor */
    bit1_u sel_0 { sel.bit3_s.val0 };
    bit1_u sel_1 { sel.bit3_s.val1 };
    bit1_u sel_2 { sel.bit3_s.val2 };
    return Mux16(
        Mux16(Mux16(a, b, sel_0), 
              Mux16(c, d, sel_0), 
              sel_1),
        Mux16(Mux16(e, f, sel_0), 
              Mux16(g, h, sel_0), 
              sel_1),
        sel_2
    );
}

bit4_u DMux4Way(const bit1_u& a, const bit2_u& sel) {
    /* 4-Way Demultiplexor */
    bit4_u result{};
    if (sel.bit2 == 0) {
        result.bit4_s.val0 = a.bit1_s.val;
    } else if (sel.bit2 == 1) {
        result.bit4_s.val1 = a.bit1_s.val;
    } else if (sel.bit2 == 2) {
        result.bit4_s.val2 = a.bit1_s.val;
    } else if (sel.bit2 == 3) {
        result.bit4_s.val3 = a.bit1_s.val;
    }
    return result;
}

byte1_u DMux8Way(const bit1_u& a, const bit3_u& sel) {
    /* 8-Way Demultiplexor */
    byte1_u result{};
    if (sel.bit3 == 0) {
        result.byte1_s.val0 = a.bit1_s.val;
    } else if (sel.bit3 == 1) {
        result.byte1_s.val1 = a.bit1_s.val;
    } else if (sel.bit3 == 2) {
        result.byte1_s.val2 = a.bit1_s.val;
    } else if (sel.bit3 == 3) {
        result.byte1_s.val3 = a.bit1_s.val;
    } else if (sel.bit3 == 4) {
        result.byte1_s.val4 = a.bit1_s.val;
    } else if (sel.bit3 == 5) {
        result.byte1_s.val5 = a.bit1_s.val;
    } else if (sel.bit3 == 6) {
        result.byte1_s.val6 = a.bit1_s.val;
    } else if (sel.bit3 == 7) {
        result.byte1_s.val7 = a.bit1_s.val;
    }
    return result;
}