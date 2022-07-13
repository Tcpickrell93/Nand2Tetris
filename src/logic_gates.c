#include "logic_gates.h"
#include "bits.h"


union bit1_u* Nand(union bit1_u *a, 
                   union bit1_u *b) {
    /* Nand Gate */
    union bit1_u result = { .value = 0 };
    result.value = ~(a->bit1_s.val & b->bit1_s.val);
    return &result;
}

union bit1_u* Not(union bit1_u *a) {
    /* Not Gate */
    return Nand(a, a);
}

union bit1_u* And(union bit1_u *a, 
                  union bit1_u *b) {
    /* And Gate */
    return Not(Nand(a, b));
}

union bit1_u* Or(union bit1_u *a, 
                 union bit1_u *b) {
    /* Or Gate */
    return Not(And(Not(a), Not(b)));
}

union bit1_u* Xor(union bit1_u *a, 
                  union bit1_u *b) {
    /* Xor Gate */
    return Or(And(a, Not(b)), And(b, Not(a)));
}

union bit1_u* Mux(union bit1_u *a, 
                  union bit1_u *b, 
                  union bit1_u *sel) {
    /* 2-bit Multiplexor */
    if (sel->bit1_s.val == 0) { return a; }
    return b;
}

union bit2_u* DMux(union bit1_u *a, 
                   union bit1_u *sel) {
    /* 2-bit Demultiplexor */
    union bit2_u result = { .value = 0 };
    if (sel->bit1_s.val == 0) {
        result.bit2_s.val0 = a->bit1_s.val;
        return &result;
    }
    result.bit2_s.val1 = a->bit1_s.val;
    return &result;
}

union bit1_u* AndMuxOr(union bit1_u *a, 
                       union bit1_u *b, 
                       union bit1_u *sel) {
    /* Programmable Gate */
    return Mux(And(a, b), Or(a, b), sel);
}

union byte2_u* Not16(union byte2_u *a) {
    /* 16-bit Not Gate */
    union byte2_u result = { .value = 0 };
    union bit1_u a_bit = { .value = a->byte2_s.val0 };
    result.byte2_s.val0 = Nand(&a_bit, &a_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val1;
    result.byte2_s.val1 = Nand(&a_bit, &a_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val2;
    result.byte2_s.val2 = Nand(&a_bit, &a_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val3;
    result.byte2_s.val3 = Nand(&a_bit, &a_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val4;
    result.byte2_s.val4 = Nand(&a_bit, &a_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val5;
    result.byte2_s.val5 = Nand(&a_bit, &a_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val6;
    result.byte2_s.val6 = Nand(&a_bit, &a_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val7;
    result.byte2_s.val7 = Nand(&a_bit, &a_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val8;
    result.byte2_s.val8 = Nand(&a_bit, &a_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val9;
    result.byte2_s.val9 = Nand(&a_bit, &a_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val10;
    result.byte2_s.val10 = Nand(&a_bit, &a_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val11;
    result.byte2_s.val11 = Nand(&a_bit, &a_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val12;
    result.byte2_s.val12 = Nand(&a_bit, &a_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val13;
    result.byte2_s.val13 = Nand(&a_bit, &a_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val14;
    result.byte2_s.val14 = Nand(&a_bit, &a_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val15;
    result.byte2_s.val15 = Nand(&a_bit, &a_bit)->value;
    return &result;
}

union byte2_u* And16(union byte2_u *a, 
                     union byte2_u *b) {
    /* 16-bit And Gate */
    union byte2_u result = { .value = 0 };
    union bit1_u a_bit = { .value = a->byte2_s.val0 };
    union bit1_u b_bit = { .value = b->byte2_s.val0 };
    result.byte2_s.val0 = And(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val1;
    b_bit.bit1_s.val = b->byte2_s.val1;
    result.byte2_s.val1 = And(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val2;
    b_bit.bit1_s.val = b->byte2_s.val2;
    result.byte2_s.val2 = And(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val3;
    b_bit.bit1_s.val = b->byte2_s.val3;
    result.byte2_s.val3 = And(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val4;
    b_bit.bit1_s.val = b->byte2_s.val4;
    result.byte2_s.val4 = And(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val5;
    b_bit.bit1_s.val = b->byte2_s.val5;
    result.byte2_s.val5 = And(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val6;
    b_bit.bit1_s.val = b->byte2_s.val6;
    result.byte2_s.val6 = And(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val7;
    b_bit.bit1_s.val = b->byte2_s.val7;
    result.byte2_s.val7 = And(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val8;
    b_bit.bit1_s.val = b->byte2_s.val8;
    result.byte2_s.val8 = And(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val9;
    b_bit.bit1_s.val = b->byte2_s.val9;
    result.byte2_s.val9 = And(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val10;
    b_bit.bit1_s.val = b->byte2_s.val10;
    result.byte2_s.val10 = And(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val11;
    b_bit.bit1_s.val = b->byte2_s.val11;
    result.byte2_s.val11 = And(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val12;
    b_bit.bit1_s.val = b->byte2_s.val12;
    result.byte2_s.val12 = And(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val13;
    b_bit.bit1_s.val = b->byte2_s.val13;
    result.byte2_s.val13 = And(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val14;
    b_bit.bit1_s.val = b->byte2_s.val14;
    result.byte2_s.val14 = And(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val15;
    b_bit.bit1_s.val = b->byte2_s.val15;
    result.byte2_s.val15 = And(&a_bit, &b_bit)->value;
    return &result;
}

union byte2_u* Or16(union byte2_u *a, 
                    union byte2_u *b) {
    /* 16-bit Or Gate */
    union byte2_u result = { .value = 0 };
    union bit1_u a_bit = { .value = a->byte2_s.val0 };
    union bit1_u b_bit = { .value = b->byte2_s.val0 };
    result.byte2_s.val0 = Or(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val1;
    b_bit.bit1_s.val = b->byte2_s.val1;
    result.byte2_s.val1 = Or(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val2;
    b_bit.bit1_s.val = b->byte2_s.val2;
    result.byte2_s.val2 = Or(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val3;
    b_bit.bit1_s.val = b->byte2_s.val3;
    result.byte2_s.val3 = Or(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val4;
    b_bit.bit1_s.val = b->byte2_s.val4;
    result.byte2_s.val4 = Or(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val5;
    b_bit.bit1_s.val = b->byte2_s.val5;
    result.byte2_s.val5 = Or(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val6;
    b_bit.bit1_s.val = b->byte2_s.val6;
    result.byte2_s.val6 = Or(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val7;
    b_bit.bit1_s.val = b->byte2_s.val7;
    result.byte2_s.val7 = Or(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val8;
    b_bit.bit1_s.val = b->byte2_s.val8;
    result.byte2_s.val8 = Or(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val9;
    b_bit.bit1_s.val = b->byte2_s.val9;
    result.byte2_s.val9 = Or(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val10;
    b_bit.bit1_s.val = b->byte2_s.val10;
    result.byte2_s.val10 = Or(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val11;
    b_bit.bit1_s.val = b->byte2_s.val11;
    result.byte2_s.val11 = Or(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val12;
    b_bit.bit1_s.val = b->byte2_s.val12;
    result.byte2_s.val12 = Or(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val13;
    b_bit.bit1_s.val = b->byte2_s.val13;
    result.byte2_s.val13 = Or(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val14;
    b_bit.bit1_s.val = b->byte2_s.val14;
    result.byte2_s.val14 = Or(&a_bit, &b_bit)->value;
    a_bit.bit1_s.val = a->byte2_s.val15;
    b_bit.bit1_s.val = b->byte2_s.val15;
    result.byte2_s.val15 = Or(&a_bit, &b_bit)->value;
    return &result;
}

union byte2_u* Mux16(union byte2_u *a, 
                     union byte2_u *b, 
                     union bit1_u *sel) {
    /* 16-bit Multiplexor */
    if (sel->value == 0) { return a; }
    return b;
}

union bit1_u* Or8Way(union byte1_u *a) {
    /* 8-way Or Gate */
    union bit1_u result = { .value = a->value > 0 };
    return &result;
}

union byte2_u* Mux4Way16(union byte2_u *a, 
                         union byte2_u *b,
                         union byte2_u *c, 
                         union byte2_u *d, 
                         union bit2_u *sel) {
    /* 16-bit 4-Way Multiplexor */
    union bit1_u sel_0 = { .value = sel->bit2_s.val0 };
    union bit1_u sel_1 = { .value = sel->bit2_s.val1 };
    return Mux16(Mux16(a, b, &sel_0), Mux16(c, d, &sel_0), &sel_1);
}

union byte2_u* Mux8Way16(union byte2_u *a, 
                         union byte2_u *b,
                         union byte2_u *c, 
                         union byte2_u *d,
                         union byte2_u *e, 
                         union byte2_u *f, 
                         union byte2_u *g, 
                         union byte2_u *h, 
                         union bit3_u *sel) {
    /* 16-bit 8-Way Multiplexor */
    union bit1_u sel_0 = { .value = sel->bit3_s.val0 };
    union bit1_u sel_1 = { .value = sel->bit3_s.val1 };
    union bit1_u sel_2 = { .value = sel->bit3_s.val2 };
    return Mux16(
        Mux16(Mux16(a, b, &sel_0), 
              Mux16(c, d, &sel_0), 
              &sel_1),
        Mux16(Mux16(e, f, &sel_0), 
              Mux16(g, h, &sel_0), 
              &sel_1),
        &sel_2
    );
}

union bit4_u* DMux4Way(union bit1_u *a, 
                       union bit2_u *sel) {
    /* 4-Way Demultiplexor */
    union bit4_u result = { .value = 0 };
    if (sel->value == 0) {
        result.bit4_s.val0 = a->bit1_s.val;
    } else if (sel->value == 1) {
        result.bit4_s.val1 = a->bit1_s.val;
    } else if (sel->value == 2) {
        result.bit4_s.val2 = a->bit1_s.val;
    } else if (sel->value == 3) {
        result.bit4_s.val3 = a->bit1_s.val;
    }
    return &result;
}

union byte1_u* DMux8Way(union bit1_u *a, 
                        union bit3_u *sel) {
    /* 8-Way Demultiplexor */
    union byte1_u result = { .value = 0 };
    if (sel->value == 0) {
        result.byte1_s.val0 = a->bit1_s.val;
    } else if (sel->value == 1) {
        result.byte1_s.val1 = a->bit1_s.val;
    } else if (sel->value == 2) {
        result.byte1_s.val2 = a->bit1_s.val;
    } else if (sel->value == 3) {
        result.byte1_s.val3 = a->bit1_s.val;
    } else if (sel->value == 4) {
        result.byte1_s.val4 = a->bit1_s.val;
    } else if (sel->value == 5) {
        result.byte1_s.val5 = a->bit1_s.val;
    } else if (sel->value == 6) {
        result.byte1_s.val6 = a->bit1_s.val;
    } else if (sel->value == 7) {
        result.byte1_s.val7 = a->bit1_s.val;
    }
    return &result;
}