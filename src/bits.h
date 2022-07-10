#ifndef BITS_H
#define BITS_H


union bit1_u {
    struct bit1_s {
        unsigned int val : 1;
    } bit1_s;
    unsigned int value;
};

union bit2_u {
    struct bit2_s {
        unsigned int val0 : 1;
        unsigned int val1 : 1;
    } bit2_s;
    unsigned int value;
};

union bit3_u {
    struct bit3_s {
        unsigned int val0 : 1;
        unsigned int val1 : 1;
        unsigned int val2 : 1;
    } bit3_s;
    unsigned int value;
};

union bit4_u {
    struct bit4_s {
        unsigned int val0 : 1;
        unsigned int val1 : 1;
        unsigned int val2 : 1;
        unsigned int val3 : 1;
    } bit4_s;
    unsigned int value;
};

union byte1_u {
    struct byte1_s {
        unsigned int val0 : 1;
        unsigned int val1 : 1;
        unsigned int val2 : 1;
        unsigned int val3 : 1;
        unsigned int val4 : 1;
        unsigned int val5 : 1;
        unsigned int val6 : 1;
        unsigned int val7 : 1;
    } byte1_s;
    unsigned int value;
};

union byte2_u {
    struct byte2_s {
        unsigned int val0 : 1;
        unsigned int val1 : 1;
        unsigned int val2 : 1;
        unsigned int val3 : 1;
        unsigned int val4 : 1;
        unsigned int val5 : 1;
        unsigned int val6 : 1;
        unsigned int val7 : 1;
        unsigned int val8 : 1;
        unsigned int val9 : 1;
        unsigned int val10 : 1;
        unsigned int val11 : 1;
        unsigned int val12 : 1;
        unsigned int val13 : 1;
        unsigned int val14 : 1;
        unsigned int val15 : 1;
    } byte2_s;
    unsigned int value;
};

struct jump_flags_s {
    unsigned int j1 : 1;
    unsigned int j2 : 1;
    unsigned int j3 : 1;
    unsigned int zr : 1;
    unsigned int ng : 1;
};

#endif // BITS_H
