#include "logic_gates.h"
#include "bits.h"


void Nand(union bit1_u *a, 
          union bit1_u *b,
          union bit1_u *result) {
    /* Nand Gate */
    result->value = !(a->bit1_s.val & b->bit1_s.val);
}

void Not(union bit1_u *a,
         union bit1_u *result) {
    /* Not Gate */
    Nand(a, a, result);
}

void And(union bit1_u *a, 
         union bit1_u *b,
         union bit1_u *result) {
    /* And Gate */
    Nand(a, b, result);
    Not(result, result);
}

void Or(union bit1_u *a, 
        union bit1_u *b,
        union bit1_u *result) {
    /* Or Gate */
    union bit1_u temp_a = { .value = 0 };
    Not(a, &temp_a);
    union bit1_u temp_b = { .value = 0 };
    Not(b, &temp_b);
    And(&temp_a, &temp_b, result);
    Not(result, result);
}

void Xor(union bit1_u *a, 
         union bit1_u *b,
         union bit1_u *result) {
    /* Xor Gate */
    union bit1_u temp_a = { .value = 0 };
    Not(a, &temp_a);
    And(b, &temp_a, &temp_a);
    union bit1_u temp_b = { .value = 0 };
    Not(b, &temp_b);
    And(a, &temp_b, &temp_b);
    Or(&temp_a, &temp_b, result);
}

union bit1_u* Mux(union bit1_u *a, 
                  union bit1_u *b, 
                  union bit1_u *sel) {
    /* 2-bit Multiplexor */
    if (sel->bit1_s.val == 0) { return a; }
    return b;
}

void DMux(union bit1_u *a, 
          union bit1_u *sel,
          union bit2_u *result) {
    /* 2-bit Demultiplexor */
    result->value = 0;
    if (sel->bit1_s.val == 0) {
        result->bit2_s.val0 = a->bit1_s.val;
    } else {
        result->bit2_s.val1 = a->bit1_s.val;
    }
}

void AndMuxOr(union bit1_u *a, 
              union bit1_u *b, 
              union bit1_u *sel,
              union bit1_u *result) {
    /* Programmable Gate */
    union bit1_u temp_and = { .value = 0 };
    And(a, b, &temp_and);
    union bit1_u temp_or = { .value = 0 };
    Or(a, b, &temp_or);
    result->value = Mux(&temp_and, &temp_or, sel)->value;
}

void Not16(union byte2_u *a,
           union byte2_u *result) {
    /* 16-bit Not Gate */
    union bit1_u a_bit = { .value = a->byte2_s.val0 };
    union bit1_u res_bit = { .value = 0 };
    Nand(&a_bit, &a_bit, &res_bit);
    result->byte2_s.val0 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val1;
    Nand(&a_bit, &a_bit, &res_bit);
    result->byte2_s.val1 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val2;
    Nand(&a_bit, &a_bit, &res_bit);
    result->byte2_s.val2 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val3;
    Nand(&a_bit, &a_bit, &res_bit);
    result->byte2_s.val3 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val4;
    Nand(&a_bit, &a_bit, &res_bit);
    result->byte2_s.val4 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val5;
    Nand(&a_bit, &a_bit, &res_bit);
    result->byte2_s.val5 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val6;
    Nand(&a_bit, &a_bit, &res_bit);
    result->byte2_s.val6 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val7;
    Nand(&a_bit, &a_bit, &res_bit);
    result->byte2_s.val7 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val8;
    Nand(&a_bit, &a_bit, &res_bit);
    result->byte2_s.val8 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val9;
    Nand(&a_bit, &a_bit, &res_bit);
    result->byte2_s.val9 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val10;
    Nand(&a_bit, &a_bit, &res_bit);
    result->byte2_s.val10 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val11;
    Nand(&a_bit, &a_bit, &res_bit);
    result->byte2_s.val11 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val12;
    Nand(&a_bit, &a_bit, &res_bit);
    result->byte2_s.val12 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val13;
    Nand(&a_bit, &a_bit, &res_bit);
    result->byte2_s.val13 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val14;
    Nand(&a_bit, &a_bit, &res_bit);
    result->byte2_s.val14 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val15;
    Nand(&a_bit, &a_bit, &res_bit);
    result->byte2_s.val15 = res_bit.value;
}

void And16(union byte2_u *a, 
           union byte2_u *b,
           union byte2_u *result) {
    /* 16-bit And Gate */
    union bit1_u a_bit = { .value = a->byte2_s.val0 };
    union bit1_u b_bit = { .value = b->byte2_s.val0 };
    union bit1_u res_bit = { .value = 0 };
    And(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val0 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val1;
    b_bit.bit1_s.val = b->byte2_s.val1;
    And(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val1 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val2;
    b_bit.bit1_s.val = b->byte2_s.val2;
    And(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val2 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val3;
    b_bit.bit1_s.val = b->byte2_s.val3;
    And(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val3 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val4;
    b_bit.bit1_s.val = b->byte2_s.val4;
    And(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val4 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val5;
    b_bit.bit1_s.val = b->byte2_s.val5;
    And(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val5 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val6;
    b_bit.bit1_s.val = b->byte2_s.val6;
    And(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val6 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val7;
    b_bit.bit1_s.val = b->byte2_s.val7;
    And(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val7 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val8;
    b_bit.bit1_s.val = b->byte2_s.val8;
    And(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val8 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val9;
    b_bit.bit1_s.val = b->byte2_s.val9;
    And(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val9 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val10;
    b_bit.bit1_s.val = b->byte2_s.val10;
    And(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val10 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val11;
    b_bit.bit1_s.val = b->byte2_s.val11;
    And(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val11 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val12;
    b_bit.bit1_s.val = b->byte2_s.val12;
    And(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val12 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val13;
    b_bit.bit1_s.val = b->byte2_s.val13;
    And(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val13 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val14;
    b_bit.bit1_s.val = b->byte2_s.val14;
    And(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val14 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val15;
    b_bit.bit1_s.val = b->byte2_s.val15;
    And(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val15 = res_bit.value;
}

void Or16(union byte2_u *a, 
          union byte2_u *b,
          union byte2_u *result) {
    /* 16-bit Or Gate */
    union bit1_u a_bit = { .value = a->byte2_s.val0 };
    union bit1_u b_bit = { .value = b->byte2_s.val0 };
    union bit1_u res_bit = { .value = 0 };
    Or(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val0 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val1;
    b_bit.bit1_s.val = b->byte2_s.val1;
    Or(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val1 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val2;
    b_bit.bit1_s.val = b->byte2_s.val2;
    Or(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val2 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val3;
    b_bit.bit1_s.val = b->byte2_s.val3;
    Or(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val3 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val4;
    b_bit.bit1_s.val = b->byte2_s.val4;
    Or(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val4 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val5;
    b_bit.bit1_s.val = b->byte2_s.val5;
    Or(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val5 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val6;
    b_bit.bit1_s.val = b->byte2_s.val6;
    Or(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val6 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val7;
    b_bit.bit1_s.val = b->byte2_s.val7;
    Or(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val7 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val8;
    b_bit.bit1_s.val = b->byte2_s.val8;
    Or(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val8 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val9;
    b_bit.bit1_s.val = b->byte2_s.val9;
    Or(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val9 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val10;
    b_bit.bit1_s.val = b->byte2_s.val10;
    Or(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val10 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val11;
    b_bit.bit1_s.val = b->byte2_s.val11;
    Or(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val11 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val12;
    b_bit.bit1_s.val = b->byte2_s.val12;
    Or(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val12 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val13;
    b_bit.bit1_s.val = b->byte2_s.val13;
    Or(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val13 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val14;
    b_bit.bit1_s.val = b->byte2_s.val14;
    Or(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val14 = res_bit.value;
    a_bit.bit1_s.val = a->byte2_s.val15;
    b_bit.bit1_s.val = b->byte2_s.val15;
    Or(&a_bit, &b_bit, &res_bit);
    result->byte2_s.val15 = res_bit.value;
}

union byte2_u* Mux16(union byte2_u *a, 
                     union byte2_u *b, 
                     union bit1_u *sel) {
    /* 16-bit Multiplexor */
    if (sel->value == 0) { return a; }
    return b;
}

void Or8Way(union byte1_u *a,
            union byte1_u *result) {
    /* 8-way Or Gate */
    result->value = (a->value > 0);
}

union byte2_u* Mux4Way16(union byte2_u *a, 
                         union byte2_u *b,
                         union byte2_u *c, 
                         union byte2_u *d, 
                         union bit2_u *sel) {
    /* 16-bit 4-Way Multiplexor */
    union bit1_u sel_0 = { .value = sel->bit2_s.val0 };
    union bit1_u sel_1 = { .value = sel->bit2_s.val1 };
    union byte2_u* ab_res = Mux16(a, b, &sel_0);
    union byte2_u* cd_res = Mux16(c, d, &sel_0);
    return Mux16(ab_res, cd_res, &sel_1);
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
    union byte2_u* ab_res = Mux16(a, b, &sel_0);
    union byte2_u* cd_res = Mux16(c, d, &sel_0);
    union byte2_u* abcd_res = Mux16(ab_res, cd_res, &sel_1);
    union byte2_u* ef_res = Mux16(e, f, &sel_0);
    union byte2_u* gh_res = Mux16(g, h, &sel_0);
    union byte2_u* efgh_res = Mux16(ef_res, gh_res, &sel_1);
    return Mux16(abcd_res, efgh_res, &sel_2);
}

void DMux4Way(union bit1_u *a, 
              union bit2_u *sel,
              union bit4_u *result) {
    /* 4-Way Demultiplexor */
    result->value = 0;
    if (sel->value == 0) {
        result->bit4_s.val0 = a->bit1_s.val;
    } else if (sel->value == 1) {
        result->bit4_s.val1 = a->bit1_s.val;
    } else if (sel->value == 2) {
        result->bit4_s.val2 = a->bit1_s.val;
    } else if (sel->value == 3) {
        result->bit4_s.val3 = a->bit1_s.val;
    }
}

void DMux8Way(union bit1_u *a, 
              union bit3_u *sel,
              union byte1_u *result) {
    /* 8-Way Demultiplexor */
    result->value = 0;
    if (sel->value == 0) {
        result->byte1_s.val0 = a->bit1_s.val;
    } else if (sel->value == 1) {
        result->byte1_s.val1 = a->bit1_s.val;
    } else if (sel->value == 2) {
        result->byte1_s.val2 = a->bit1_s.val;
    } else if (sel->value == 3) {
        result->byte1_s.val3 = a->bit1_s.val;
    } else if (sel->value == 4) {
        result->byte1_s.val4 = a->bit1_s.val;
    } else if (sel->value == 5) {
        result->byte1_s.val5 = a->bit1_s.val;
    } else if (sel->value == 6) {
        result->byte1_s.val6 = a->bit1_s.val;
    } else if (sel->value == 7) {
        result->byte1_s.val7 = a->bit1_s.val;
    }
}
