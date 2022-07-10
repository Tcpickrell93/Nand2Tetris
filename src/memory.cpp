#include "memory.h"
#include "logic_gates.h"
#include "bits.h"

#include <iostream>


void UpdateDFF(bit1_u& dff, 
               const bit1_u& in) {
    dff.bit1_s.val = in.value;
}

void UpdateDFF16(byte2_u& dff16,
                 const byte2_u& in) {
    dff16.value = in.value;
}

void UpdateRegisterBit(RegisterBit_u& rb, 
                       const bit1_u& in, 
                       const bit1_u& load) {
    UpdateDFF(rb.regbit_s.dff, Mux(rb.regbit_s.dff, in, load));
}

void UpdateRegister16(Register16_u& r16,
                      const byte2_u& in,
                      const bit1_u& load) {
    UpdateDFF16(r16.r16_s.dff16, Mux16(r16.r16_s.dff16, in, load));
}

byte2_u ReadRAM8(const RAM8& ram,
                 const bit3_u& address) {
    return Mux8Way16(ram.reg0.r16_s.dff16,
                     ram.reg1.r16_s.dff16,
                     ram.reg2.r16_s.dff16,
                     ram.reg3.r16_s.dff16,
                     ram.reg4.r16_s.dff16,
                     ram.reg5.r16_s.dff16,
                     ram.reg6.r16_s.dff16,
                     ram.reg7.r16_s.dff16,
                     address);
}

void WriteRAM8(RAM8& ram, 
               const bit3_u& address, 
               const byte2_u& in, 
               const bit1_u& load) {
    switch (address.value) {
        case 0: 
            UpdateRegister16(ram.reg0, in, load);
            break;
        case 1: 
            UpdateRegister16(ram.reg1, in, load);
            break;
        case 2: 
            UpdateRegister16(ram.reg2, in, load);
            break;
        case 3: 
            UpdateRegister16(ram.reg3, in, load);
            break;
        case 4: 
            UpdateRegister16(ram.reg4, in, load);
            break;
        case 5: 
            UpdateRegister16(ram.reg5, in, load);
            break;
        case 6: 
            UpdateRegister16(ram.reg6, in, load);
            break;
        case 7: 
            UpdateRegister16(ram.reg7, in, load);
            break;
        default:
            break;
    }
}

byte2_u ReadRAM64(const RAM64& ram,
                  const bit6_u& address) {
    bit3_u reg16_address { 
        .bit3_s.val0 = address.bit6_s.val0,
        .bit3_s.val1 = address.bit6_s.val1,
        .bit3_s.val2 = address.bit6_s.val2 
    };
    bit3_u ram8_address {
        .bit3_s.val0 = address.bit6_s.val3,
        .bit3_s.val1 = address.bit6_s.val4,
        .bit3_s.val2 = address.bit6_s.val5
    };
    return Mux8Way16(
        ReadRAM8(ram.ram0, reg16_address),
        ReadRAM8(ram.ram1, reg16_address),
        ReadRAM8(ram.ram2, reg16_address),
        ReadRAM8(ram.ram3, reg16_address),
        ReadRAM8(ram.ram4, reg16_address),
        ReadRAM8(ram.ram5, reg16_address),
        ReadRAM8(ram.ram6, reg16_address),
        ReadRAM8(ram.ram7, reg16_address),
        ram8_address
    );
}

void WriteRAM64(RAM64& ram,
                const bit6_u& address,
                const byte2_u& in,
                const bit1_u& load) {
    bit3_u reg16_address { 
        .bit3_s.val0 = address.bit6_s.val0,
        .bit3_s.val1 = address.bit6_s.val1,
        .bit3_s.val2 = address.bit6_s.val2 
    };
    bit3_u ram8_address {
        .bit3_s.val0 = address.bit6_s.val3,
        .bit3_s.val1 = address.bit6_s.val4,
        .bit3_s.val2 = address.bit6_s.val5
    };
    switch (ram8_address.value) {
        case 0: 
            WriteRAM8(ram.reg0, reg16_address, in, load);
            break;
        case 1: 
            WriteRAM8(ram.reg1, reg16_address, in, load);
            break;
        case 2: 
            WriteRAM8(ram.reg2, reg16_address, in, load);
            break;
        case 3: 
            WriteRAM8(ram.reg3, reg16_address, in, load);
            break;
        case 4: 
            WriteRAM8(ram.reg4, reg16_address, in, load);
            break;
        case 5: 
            WriteRAM8(ram.reg5, reg16_address, in, load);
            break;
        case 6: 
            WriteRAM8(ram.reg6, reg16_address, in, load);
            break;
        case 7: 
            WriteRAM8(ram.reg7, reg16_address, in, load);
            break;
        default:
            break;
    }
}

byte2_u ReadRAM512(const RAM512& ram, const bit9_u& address) {
    bit6_u ram8_address { 
        .bit6_s.val0 = address.bit9_s.val0,
        .bit6_s.val1 = address.bit9_s.val1,
        .bit6_s.val2 = address.bit9_s.val2,
        .bit6_s.val3 = address.bit9_s.val3,
        .bit6_s.val4 = address.bit9_s.val4,
        .bit6_s.val5 = address.bit9_s.val5 
    };
    bit3_u ram64_address {
        .bit3_s.val0 = address.bit9_s.val6,
        .bit3_s.val1 = address.bit9_s.val7,
        .bit3_s.val2 = address.bit9_s.val8
    };
    return Mux8Way16(
        ReadRAM64(ram.ram0, ram8_address),
        ReadRAM64(ram.ram1, ram8_address),
        ReadRAM64(ram.ram2, ram8_address),
        ReadRAM64(ram.ram3, ram8_address),
        ReadRAM64(ram.ram4, ram8_address),
        ReadRAM64(ram.ram5, ram8_address),
        ReadRAM64(ram.ram6, ram8_address),
        ReadRAM64(ram.ram7, ram8_address),
        ram64_address
    );
}

void WriteRAM512(RAM512& ram, 
                 const bit9_u& address, 
                 const byte2_u& in, 
                 const bit1_u& load) {
    bit6_u ram8_address { 
        .bit6_s.val0 = address.bit9_s.val0,
        .bit6_s.val1 = address.bit9_s.val1,
        .bit6_s.val2 = address.bit9_s.val2,
        .bit6_s.val3 = address.bit9_s.val3,
        .bit6_s.val4 = address.bit9_s.val4,
        .bit6_s.val5 = address.bit9_s.val5 
    };
    bit3_u ram64_address {
        .bit3_s.val0 = address.bit9_s.val6,
        .bit3_s.val1 = address.bit9_s.val7,
        .bit3_s.val2 = address.bit9_s.val8
    };
    switch (ram64_address.value) {
        case 0: 
            WriteRAM64(ram.reg0, ram8_address, in, load);
            break;
        case 1: 
            WriteRAM64(ram.reg1, ram8_address, in, load);
            break;
        case 2: 
            WriteRAM64(ram.reg2, ram8_address, in, load);
            break;
        case 3: 
            WriteRAM64(ram.reg3, ram8_address, in, load);
            break;
        case 4: 
            WriteRAM64(ram.reg4, ram8_address, in, load);
            break;
        case 5: 
            WriteRAM64(ram.reg5, ram8_address, in, load);
            break;
        case 6: 
            WriteRAM64(ram.reg6, ram8_address, in, load);
            break;
        case 7: 
            WriteRAM64(ram.reg7, ram8_address, in, load);
            break;
        default:
            break;
    }
}

byte2_u ReadRAM4k(const RAM4k& ram, 
                  const bit12_u& address) {
    bit9_u ram64_address { 
        .bit9_s.val0 = address.bit12_s.val0,
        .bit9_s.val1 = address.bit12_s.val1,
        .bit9_s.val2 = address.bit12_s.val2,
        .bit9_s.val3 = address.bit12_s.val3,
        .bit9_s.val4 = address.bit12_s.val4,
        .bit9_s.val5 = address.bit12_s.val5,
        .bit9_s.val6 = address.bit12_s.val6,
        .bit9_s.val7 = address.bit12_s.val7,
        .bit9_s.val8 = address.bit12_s.val8 
    };
    bit3_u ram512_address {
        .bit3_s.val0 = address.bit12_s.val9,
        .bit3_s.val1 = address.bit12_s.val10,
        .bit3_s.val2 = address.bit12_s.val11
    };
    return Mux8Way16(
        ReadRAM512(ram.ram0, ram64_address),
        ReadRAM512(ram.ram1, ram64_address),
        ReadRAM512(ram.ram2, ram64_address),
        ReadRAM512(ram.ram3, ram64_address),
        ReadRAM512(ram.ram4, ram64_address),
        ReadRAM512(ram.ram5, ram64_address),
        ReadRAM512(ram.ram6, ram64_address),
        ReadRAM512(ram.ram7, ram64_address),
        ram512_address
    );
}

void WriteRAM4k(RAM4k& ram, 
                const bit12_u& address, 
                const byte2_u& in, 
                const bit1_u& load) {
    bit9_u ram64_address { 
        .bit9_s.val0 = address.bit12_s.val0,
        .bit9_s.val1 = address.bit12_s.val1,
        .bit9_s.val2 = address.bit12_s.val2,
        .bit9_s.val3 = address.bit12_s.val3,
        .bit9_s.val4 = address.bit12_s.val4,
        .bit9_s.val5 = address.bit12_s.val5,
        .bit9_s.val6 = address.bit12_s.val6,
        .bit9_s.val7 = address.bit12_s.val7,
        .bit9_s.val8 = address.bit12_s.val8 
    };
    bit3_u ram512_address {
        .bit3_s.val0 = address.bit12_s.val9,
        .bit3_s.val1 = address.bit12_s.val10,
        .bit3_s.val2 = address.bit12_s.val11
    };
    switch (ram512_address.value) {
        case 0: 
            WriteRAM512(ram.reg0, ram64_address, in, load);
            break;
        case 1: 
            WriteRAM512(ram.reg1, ram64_address, in, load);
            break;
        case 2: 
            WriteRAM512(ram.reg2, ram64_address, in, load);
            break;
        case 3: 
            WriteRAM512(ram.reg3, ram64_address, in, load);
            break;
        case 4: 
            WriteRAM512(ram.reg4, ram64_address, in, load);
            break;
        case 5: 
            WriteRAM512(ram.reg5, ram64_address, in, load);
            break;
        case 6: 
            WriteRAM512(ram.reg6, ram64_address, in, load);
            break;
        case 7: 
            WriteRAM512(ram.reg7, ram64_address, in, load);
            break;
        default:
            break;
    }
}

byte2_u ReadRAM16k(const RAM16k& ram, 
                   const bit14_u& address) {
    bit12_u ram512_address { 
        .bit12_s.val0 = address.bit14_s.val0,
        .bit12_s.val1 = address.bit14_s.val1,
        .bit12_s.val2 = address.bit14_s.val2,
        .bit12_s.val3 = address.bit14_s.val3,
        .bit12_s.val4 = address.bit14_s.val4,
        .bit12_s.val5 = address.bit14_s.val5,
        .bit12_s.val6 = address.bit14_s.val6,
        .bit12_s.val7 = address.bit14_s.val7,
        .bit12_s.val8 = address.bit14_s.val8,
        .bit12_s.val9 = address.bit14_s.val9,
        .bit12_s.val10 = address.bit14_s.val10,
        .bit12_s.val11 = address.bit14_s.val11 
    };
    bit2_u ram4k_address {
        .bit3_s.val0 = address.bit14_s.val12,
        .bit3_s.val1 = address.bit14_s.val13,
    };
    return Mux8Way16(
        ReadRAM4k(ram.ram0, ram512_address),
        ReadRAM4k(ram.ram1, ram512_address),
        ReadRAM4k(ram.ram2, ram512_address),
        ReadRAM4k(ram.ram3, ram512_address),
        ReadRAM4k(ram.ram4, ram512_address),
        ReadRAM4k(ram.ram5, ram512_address),
        ReadRAM4k(ram.ram6, ram512_address),
        ReadRAM4k(ram.ram7, ram512_address),
        ram4k_address
    );
}

void WriteRAM16k(RAM16k& ram, 
                 const byte2_u& address, 
                 const byte2_u& in, 
                 const bit1_u& load) {
    bit12_u ram512_address { 
        .bit12_s.val0 = address.bit14_s.val0,
        .bit12_s.val1 = address.bit14_s.val1,
        .bit12_s.val2 = address.bit14_s.val2,
        .bit12_s.val3 = address.bit14_s.val3,
        .bit12_s.val4 = address.bit14_s.val4,
        .bit12_s.val5 = address.bit14_s.val5,
        .bit12_s.val6 = address.bit14_s.val6,
        .bit12_s.val7 = address.bit14_s.val7,
        .bit12_s.val8 = address.bit14_s.val8,
        .bit12_s.val9 = address.bit14_s.val9,
        .bit12_s.val10 = address.bit14_s.val10,
        .bit12_s.val11 = address.bit14_s.val11 
    };
    bit2_u ram4k_address {
        .bit3_s.val0 = address.bit14_s.val12,
        .bit3_s.val1 = address.bit14_s.val13,
    };
    switch (ram4k_address.value) {
        case 0: 
            WriteRAM4k(ram.reg0, ram512_address, in, load);
            break;
        case 1: 
            WriteRAM4k(ram.reg1, ram512_address, in, load);
            break;
        case 2: 
            WriteRAM4k(ram.reg2, ram512_address, in, load);
            break;
        case 3: 
            WriteRAM4k(ram.reg3, ram512_address, in, load);
            break;
        default:
            break;
    }
}
