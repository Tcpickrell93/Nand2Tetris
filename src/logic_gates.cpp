#include "logic_gates.h"


bit Nand(const bit& a, const bit& b) {
    /* Nand Gate */
    return ~(a & b);
}

bit Not(const bit& a) {
    /* Not Gate */
    return Nand(a, a);
}

bit And(const bit& a, const bit& b) {
    /* And Gate */
    return Not(Nand(a, b));
}

bit Or(const bit& a, const bit& b) {
    /* Or Gate */
    return Not(And(Not(a), Not(b)));
}

bit Xor(const bit& a, const bit& b) {
    /* Xor Gate */
    return Or(And(a, Not(b)), And(b, Not(a)));
}

bit Mux(const bit& a, const bit& b, const bit& sel) {
    /* 2-bit Multiplexor */
    if (sel[0] == 0) { return a; }
    return b;
}

bit2 DMux(const bit& a, const bit& sel) {
    /* 2-bit Demultiplexor */
    bit2 result{};
    if (sel[0] == 0) {
        result[0] = a[0];
        return result;
    }
    result[1] = a[0];
    return result;
}

bit AndMuxOr(const bit& a, const bit& b, const bit& sel) {
    /* Programmable Gate */
    return Mux(And(a, b), Or(a, b), sel);
}

byte2 Not16(const byte2& a) {
    /* 16-bit Not Gate */
    byte2 result{};
    for (int i = 0; i < 16; i++) {
        result[i] = Not(a[i])[0];
    }
    return result;
}

byte2 And16(const byte2& a, const byte2& b) {
    /* 16-bit And Gate */
    byte2 result{};
    for (int i = 0; i < 16; i++) {
        result[i] = And(a[i], b[i])[0];
    }
    return result;
}

byte2 Or16(const byte2& a, const byte2& b) {
    /* 16-bit Or Gate */
    byte2 result{};
    for (int i = 0; i < 16; i++) {
        result[i] = Or(a[i], b[i])[0];
    }
    return result;
}

byte2 Mux16(const byte2& a, const byte2& b, const bit& sel) {
    /* 16-bit Multiplexor */
    if (sel[0] == 0) { return a; }
    return b;
}

bit Or8Way(const byte& a) {
    /* 8-way Or Gate */
    bit out{};
    for (int i = 0; i < 8; i++) {
        if (a[i] == 1) {
            return out.set();
        }
    }
    return out;
}

byte2 Mux4Way16(const byte2& a, const byte2& b,
                const byte2& c, const byte2& d, const bit2& sel) {
    /* 16-bit 4-Way Multiplexor */
    return Mux16(Mux16(a, b, sel[0]), Mux16(c, d, sel[0]), sel[1]);
}

byte2 Mux8Way16(const byte2& a, const byte2& b,
                const byte2& c, const byte2& d,
                const byte2& e, const byte2& f, 
                const byte2& g, const byte2& h, const bit3& sel) {
    /* 16-bit 8-Way Multiplexor */
    return Mux16(
            Mux16(Mux16(a, b, sel[0]), Mux16(c, d, sel[0]), sel[1]),
            Mux16(Mux16(e, f, sel[0]), Mux16(g, h, sel[0]), sel[1]),
            sel[2]
            );
}

bit4 DMux4Way(const bit& a, const bit2& sel) {
    /* 4-Way Demultiplexor */
    bit4 result{};
    if (sel == 0b00) {
        result[0] = a[0];
    } else if (sel == 0b01) {
        result[1] = a[0];
    } else if (sel == 0b10) {
        result[2] = a[0];
    } else if (sel == 0b11) {
        result[3] = a[0];
    }
    return result;
}

byte DMux8Way(const bit& a, const bit3& sel) {
    /* 8-Way Demultiplexor */
    byte result{};
    if (sel == 0b000) {
        result[0] = a[0];
    } else if (sel == 0b001) {
        result[1] = a[0];
    } else if (sel == 0b010) {
        result[2] = a[0];
    } else if (sel == 0b011) {
        result[3] = a[0];
    } else if (sel == 0b100) {
        result[4] = a[0];
    } else if (sel == 0b101) {
        result[5] = a[0];
    } else if (sel == 0b110) {
        result[6] = a[0];
    } else if (sel == 0b111) {
        result[7] = a[0];
    }
    return result;
}
