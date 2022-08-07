#ifndef MEMORY_H
#define MEMORY_H

#include "bits.h"

typedef union bit1_u RegisterBit_u;
void UpdateRegisterBit(RegisterBit_u *rb, 
                       union bit1_u *in, 
                       union bit1_u *load);

typedef union byte2_u Register16_u;
void UpdateRegister16(Register16_u *r16, 
                      union byte2_u *in, 
                      union bit1_u *load);

struct RAM8 {
    Register16_u reg0;
    Register16_u reg1;
    Register16_u reg2;
    Register16_u reg3;
    Register16_u reg4;
    Register16_u reg5;
    Register16_u reg6;
    Register16_u reg7;
};
union byte2_u* ReadRAM8(struct RAM8 *ram,
                        union bit3_u *address);
void WriteRAM8(struct RAM8 *ram, 
               union bit3_u *address, 
               union byte2_u *in, 
               union bit1_u *load); 
struct RAM64 {
    struct RAM8 ram0;
    struct RAM8 ram1;
    struct RAM8 ram2;
    struct RAM8 ram3;
    struct RAM8 ram4;
    struct RAM8 ram5;
    struct RAM8 ram6;
    struct RAM8 ram7;
};
union byte2_u* ReadRAM64(struct RAM64 *ram,
                         union bit6_u *address);
void WriteRAM64(struct RAM64 *ram,
                union bit6_u *address,
                union byte2_u *in,
                union bit1_u *load);

/*
struct RAM512 {
    struct RAM64 ram0;
    struct RAM64 ram1;
    struct RAM64 ram2;
    struct RAM64 ram3;
    struct RAM64 ram4;
    struct RAM64 ram5;
    struct RAM64 ram6;
    struct RAM64 ram7;
};
union byte2_u* ReadRAM512(struct RAM512 *ram, 
                          union bit9_u *address);
void WriteRAM512(struct RAM512 *ram, 
                 union bit9_u *address, 
                 union byte2_u *in, 
                 union bit1_u *load);

struct RAM4k {
    struct RAM512 ram0;
    struct RAM512 ram1;
    struct RAM512 ram2;
    struct RAM512 ram3;
    struct RAM512 ram4;
    struct RAM512 ram5;
    struct RAM512 ram6;
    struct RAM512 ram7;
};
union byte2_u* ReadRAM4k(struct RAM4k *ram, 
                         union bit12_u *address);
void WriteRAM4k(struct RAM4k *ram, 
                union bit12_u *address, 
                union byte2_u *in, 
                union bit1_u *load);                  

struct RAM16k {
    struct RAM4k ram0;
    struct RAM4k ram1;
    struct RAM4k ram2;
    struct RAM4k ram3;
};
union byte2_u* ReadRAM16k(struct RAM16k *ram, 
                          union bit14_u *address);
void WriteRAM16k(struct RAM16k *ram, 
                 union bit14_u *address, 
                 union byte2_u *in, 
                 union bit1_u *load);
*/
#endif // MEMORY_H

