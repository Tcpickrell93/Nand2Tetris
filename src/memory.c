#include "memory.h"
#include "logic_gates.h"
#include "bits.h"

/*
void UpdateDFF(union bit1_u *dff, 
               union bit1_u *in) {
    dff->bit1_s.val = in->value;
}
void UpdateDFF16(union byte2_u *dff16,
                 union byte2_u *in) {
    dff16->value = in->value;
}
*/
void UpdateRegisterBit(RegisterBit_u *rb, 
                       union bit1_u *in, 
                       union bit1_u *load) {
    rb->value = Mux(rb, in, load)->value;
}

void UpdateRegister16(Register16_u *r16, 
                      union byte2_u *in, 
                      union bit1_u *load) {
    r16->value = Mux16(r16, in, load)->value;
}

union byte2_u* ReadRAM8(struct RAM8 *ram,
                        union bit3_u *address) {
    return Mux8Way16(
        &ram->reg0,
        &ram->reg1,
        &ram->reg2,
        &ram->reg3,
        &ram->reg4,
        &ram->reg5,
        &ram->reg6,
        &ram->reg7,
        address
    );
}

void WriteRAM8(struct RAM8 *ram, 
               union bit3_u *address, 
               union byte2_u *in, 
               union bit1_u *load) {
    switch (address->value) {
        case 0: 
            UpdateRegister16(&ram->reg0, in, load);
            break;
        case 1: 
            UpdateRegister16(&ram->reg1, in, load);
            break;
        case 2: 
            UpdateRegister16(&ram->reg2, in, load);
            break;
        case 3: 
            UpdateRegister16(&ram->reg3, in, load);
            break;
        case 4: 
            UpdateRegister16(&ram->reg4, in, load);
            break;
        case 5: 
            UpdateRegister16(&ram->reg5, in, load);
            break;
        case 6: 
            UpdateRegister16(&ram->reg6, in, load);
            break;
        case 7: 
            UpdateRegister16(&ram->reg7, in, load);
            break;
        default:
            break;
    }
}

union byte2_u* ReadRAM64(struct RAM64 *ram,
                         union bit6_u *address) {
    union bit3_u reg16_address = { 
        .bit3_s.val0 = address->bit6_s.val0,
        .bit3_s.val1 = address->bit6_s.val1,
        .bit3_s.val2 = address->bit6_s.val2 
    };
    union bit3_u ram8_address = {
        .bit3_s.val0 = address->bit6_s.val3,
        .bit3_s.val1 = address->bit6_s.val4,
        .bit3_s.val2 = address->bit6_s.val5
    };
    return Mux8Way16(
        ReadRAM8(&ram->ram0, &reg16_address),
        ReadRAM8(&ram->ram1, &reg16_address),
        ReadRAM8(&ram->ram2, &reg16_address),
        ReadRAM8(&ram->ram3, &reg16_address),
        ReadRAM8(&ram->ram4, &reg16_address),
        ReadRAM8(&ram->ram5, &reg16_address),
        ReadRAM8(&ram->ram6, &reg16_address),
        ReadRAM8(&ram->ram7, &reg16_address),
        &ram8_address
    );
}

void WriteRAM64(struct RAM64 *ram,
                union bit6_u *address,
                union byte2_u *in,
                union bit1_u *load) {
    union bit3_u reg16_address = { .value = 0 }; 
    reg16_address.bit3_s.val0 = address->bit6_s.val0;
    reg16_address.bit3_s.val1 = address->bit6_s.val1;
    reg16_address.bit3_s.val2 = address->bit6_s.val2; 
    union bit3_u ram8_address = { .value = 0 };
    ram8_address.bit3_s.val0 = address->bit6_s.val3;
    ram8_address.bit3_s.val1 = address->bit6_s.val4;
    ram8_address.bit3_s.val2 = address->bit6_s.val5;
    switch (ram8_address.value) {
        case 0: 
            WriteRAM8(&ram->ram0, &reg16_address, in, load);
            break;
        case 1: 
            WriteRAM8(&ram->ram1, &reg16_address, in, load);
            break;
        case 2: 
            WriteRAM8(&ram->ram2, &reg16_address, in, load);
            break;
        case 3: 
            WriteRAM8(&ram->ram3, &reg16_address, in, load);
            break;
        case 4: 
            WriteRAM8(&ram->ram4, &reg16_address, in, load);
            break;
        case 5: 
            WriteRAM8(&ram->ram5, &reg16_address, in, load);
            break;
        case 6: 
            WriteRAM8(&ram->ram6, &reg16_address, in, load);
            break;
        case 7: 
            WriteRAM8(&ram->ram7, &reg16_address, in, load);
            break;
        default:
            break;
    }
}

union byte2_u* ReadRAM512(struct RAM512 *ram, 
                          union bit9_u *address) {
    union bit6_u ram8_address = { 
        .bit6_s.val0 = address->bit9_s.val0,
        .bit6_s.val1 = address->bit9_s.val1,
        .bit6_s.val2 = address->bit9_s.val2,
        .bit6_s.val3 = address->bit9_s.val3,
        .bit6_s.val4 = address->bit9_s.val4,
        .bit6_s.val5 = address->bit9_s.val5 
    };
    union bit3_u ram64_address = {
        .bit3_s.val0 = address->bit9_s.val6,
        .bit3_s.val1 = address->bit9_s.val7,
        .bit3_s.val2 = address->bit9_s.val8
    };
    return Mux8Way16(
        ReadRAM64(&ram->ram0, &ram8_address),
        ReadRAM64(&ram->ram1, &ram8_address),
        ReadRAM64(&ram->ram2, &ram8_address),
        ReadRAM64(&ram->ram3, &ram8_address),
        ReadRAM64(&ram->ram4, &ram8_address),
        ReadRAM64(&ram->ram5, &ram8_address),
        ReadRAM64(&ram->ram6, &ram8_address),
        ReadRAM64(&ram->ram7, &ram8_address),
        &ram64_address
    );
}

void WriteRAM512(struct RAM512 *ram, 
                 union bit9_u *address, 
                 union byte2_u *in, 
                 union bit1_u *load) {
    union bit6_u ram8_address = { .value = 0 };
    ram8_address.bit6_s.val0 = address->bit9_s.val0;
    ram8_address.bit6_s.val1 = address->bit9_s.val1;
    ram8_address.bit6_s.val2 = address->bit9_s.val2;
    ram8_address.bit6_s.val3 = address->bit9_s.val3;
    ram8_address.bit6_s.val4 = address->bit9_s.val4;
    ram8_address.bit6_s.val5 = address->bit9_s.val5;
    union bit3_u ram64_address = { .value = 0 };
    ram64_address.bit3_s.val0 = address->bit9_s.val6;
    ram64_address.bit3_s.val1 = address->bit9_s.val7;
    ram64_address.bit3_s.val2 = address->bit9_s.val8;
    switch (ram64_address.value) {
        case 0: 
            WriteRAM64(&ram->ram0, &ram8_address, in, load);
            break;
        case 1: 
            WriteRAM64(&ram->ram1, &ram8_address, in, load);
            break;
        case 2: 
            WriteRAM64(&ram->ram2, &ram8_address, in, load);
            break;
        case 3: 
            WriteRAM64(&ram->ram3, &ram8_address, in, load);
            break;
        case 4: 
            WriteRAM64(&ram->ram4, &ram8_address, in, load);
            break;
        case 5: 
            WriteRAM64(&ram->ram5, &ram8_address, in, load);
            break;
        case 6: 
            WriteRAM64(&ram->ram6, &ram8_address, in, load);
            break;
        case 7: 
            WriteRAM64(&ram->ram7, &ram8_address, in, load);
            break;
        default:
            break;
    }
}

union byte2_u* ReadRAM4k(struct RAM4k *ram, 
                         union bit12_u *address) {
    union bit9_u ram64_address = { .value = 0 };
    ram64_address.bit9_s.val0 = address->bit12_s.val0;
    ram64_address.bit9_s.val1 = address->bit12_s.val1;
    ram64_address.bit9_s.val2 = address->bit12_s.val2;
    ram64_address.bit9_s.val3 = address->bit12_s.val3;
    ram64_address.bit9_s.val4 = address->bit12_s.val4;
    ram64_address.bit9_s.val5 = address->bit12_s.val5;
    ram64_address.bit9_s.val6 = address->bit12_s.val6;
    ram64_address.bit9_s.val7 = address->bit12_s.val7;
    ram64_address.bit9_s.val8 = address->bit12_s.val8;
    union bit3_u ram512_address = { .value = 0 };
    ram512_address.bit3_s.val0 = address->bit12_s.val9;
    ram512_address.bit3_s.val1 = address->bit12_s.val10;
    ram512_address.bit3_s.val2 = address->bit12_s.val11;
    return Mux8Way16(
        ReadRAM512(&ram->ram0, &ram64_address),
        ReadRAM512(&ram->ram1, &ram64_address),
        ReadRAM512(&ram->ram2, &ram64_address),
        ReadRAM512(&ram->ram3, &ram64_address),
        ReadRAM512(&ram->ram4, &ram64_address),
        ReadRAM512(&ram->ram5, &ram64_address),
        ReadRAM512(&ram->ram6, &ram64_address),
        ReadRAM512(&ram->ram7, &ram64_address),
        &ram512_address
    );
}

void WriteRAM4k(struct RAM4k *ram, 
                union bit12_u *address, 
                union byte2_u *in, 
                union bit1_u *load) {
    union bit9_u ram64_address = { .value = 0 };
    ram64_address.bit9_s.val0 = address->bit12_s.val0;
    ram64_address.bit9_s.val1 = address->bit12_s.val1;
    ram64_address.bit9_s.val2 = address->bit12_s.val2;
    ram64_address.bit9_s.val3 = address->bit12_s.val3;
    ram64_address.bit9_s.val4 = address->bit12_s.val4;
    ram64_address.bit9_s.val5 = address->bit12_s.val5;
    ram64_address.bit9_s.val6 = address->bit12_s.val6;
    ram64_address.bit9_s.val7 = address->bit12_s.val7;
    ram64_address.bit9_s.val8 = address->bit12_s.val8;
    union bit3_u ram512_address = { .value = 0 };
    ram512_address.bit3_s.val0 = address->bit12_s.val9;
    ram512_address.bit3_s.val1 = address->bit12_s.val10;
    ram512_address.bit3_s.val2 = address->bit12_s.val11;
    switch (ram512_address.value) {
        case 0: 
            WriteRAM512(&ram->ram0, &ram64_address, in, load);
            break;
        case 1: 
            WriteRAM512(&ram->ram1, &ram64_address, in, load);
            break;
        case 2: 
            WriteRAM512(&ram->ram2, &ram64_address, in, load);
            break;
        case 3: 
            WriteRAM512(&ram->ram3, &ram64_address, in, load);
            break;
        case 4: 
            WriteRAM512(&ram->ram4, &ram64_address, in, load);
            break;
        case 5: 
            WriteRAM512(&ram->ram5, &ram64_address, in, load);
            break;
        case 6: 
            WriteRAM512(&ram->ram6, &ram64_address, in, load);
            break;
        case 7: 
            WriteRAM512(&ram->ram7, &ram64_address, in, load);
            break;
        default:
            break;
    }
}

union byte2_u* ReadRAM16k(struct RAM16k *ram, 
                          union bit14_u *address) {
    union bit12_u ram512_address = { .value = 0 };
    ram512_address.bit12_s.val0 = address->bit14_s.val0;
    ram512_address.bit12_s.val1 = address->bit14_s.val1;
    ram512_address.bit12_s.val2 = address->bit14_s.val2;
    ram512_address.bit12_s.val3 = address->bit14_s.val3;
    ram512_address.bit12_s.val4 = address->bit14_s.val4;
    ram512_address.bit12_s.val5 = address->bit14_s.val5;
    ram512_address.bit12_s.val6 = address->bit14_s.val6;
    ram512_address.bit12_s.val7 = address->bit14_s.val7;
    ram512_address.bit12_s.val8 = address->bit14_s.val8;
    ram512_address.bit12_s.val9 = address->bit14_s.val9;
    ram512_address.bit12_s.val10 = address->bit14_s.val10;
    ram512_address.bit12_s.val11 = address->bit14_s.val11;
    union bit2_u ram4k_address = { .value = 0 };
    ram4k_address.bit2_s.val0 = address->bit14_s.val12;
    ram4k_address.bit2_s.val1 = address->bit14_s.val13;
    return Mux4Way16(
        ReadRAM4k(&ram->ram0, &ram512_address),
        ReadRAM4k(&ram->ram1, &ram512_address),
        ReadRAM4k(&ram->ram2, &ram512_address),
        ReadRAM4k(&ram->ram3, &ram512_address),
        &ram4k_address
    );
}

void WriteRAM16k(struct RAM16k *ram, 
                 union bit14_u *address, 
                 union byte2_u *in, 
                 union bit1_u *load) {
    union bit12_u ram512_address = { .value = 0 };
    ram512_address.bit12_s.val0 = address->bit14_s.val0;
    ram512_address.bit12_s.val1 = address->bit14_s.val1;
    ram512_address.bit12_s.val2 = address->bit14_s.val2;
    ram512_address.bit12_s.val3 = address->bit14_s.val3;
    ram512_address.bit12_s.val4 = address->bit14_s.val4;
    ram512_address.bit12_s.val5 = address->bit14_s.val5;
    ram512_address.bit12_s.val6 = address->bit14_s.val6;
    ram512_address.bit12_s.val7 = address->bit14_s.val7;
    ram512_address.bit12_s.val8 = address->bit14_s.val8;
    ram512_address.bit12_s.val9 = address->bit14_s.val9;
    ram512_address.bit12_s.val10 = address->bit14_s.val10;
    ram512_address.bit12_s.val11 = address->bit14_s.val11;
    union bit2_u ram4k_address = { .value = 0 };
    ram4k_address.bit2_s.val0 = address->bit14_s.val12;
    ram4k_address.bit2_s.val1 = address->bit14_s.val13;
    switch (ram4k_address.value) {
        case 0: 
            WriteRAM4k(&ram->ram0, &ram512_address, in, load);
            break;
        case 1: 
            WriteRAM4k(&ram->ram1, &ram512_address, in, load);
            break;
        case 2: 
            WriteRAM4k(&ram->ram2, &ram512_address, in, load);
            break;
        case 3: 
            WriteRAM4k(&ram->ram3, &ram512_address, in, load);
            break;
        default:
            break;
    }
}
