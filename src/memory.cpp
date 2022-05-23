#include "memory.h"
#include "logic_gates.h"

#include <iostream>


bit DataFlipFLop::Out() {
    return prev_;
}

void DataFlipFLop::Update(const bit& in) {
    prev_ = in;
}

bit RegisterBit::Out() {
    return dff_.Out();
}

void RegisterBit::Update(const bit& in, const bit& load) {
    bit mux_out { Mux(dff_.Out(), in, load) };
    dff_.Update(mux_out);
}

Register16::Register16() {}

Register16::Register16(const byte2& value) {
    bit load { 0b1u };
    Update(value, load);
}

byte2 Register16::Out() {
    byte2 result {};
    result[0] = bit0_.Out()[0];
    result[1] = bit1_.Out()[0];
    result[2] = bit2_.Out()[0];
    result[3] = bit3_.Out()[0];
    result[4] = bit4_.Out()[0];
    result[5] = bit5_.Out()[0];
    result[6] = bit6_.Out()[0];
    result[7] = bit7_.Out()[0];
    result[8] = bit8_.Out()[0];
    result[9] = bit9_.Out()[0];
    result[10] = bit10_.Out()[0];
    result[11] = bit11_.Out()[0];
    result[12] = bit12_.Out()[0];
    result[13] = bit13_.Out()[0];
    result[14] = bit14_.Out()[0];
    result[15] = bit15_.Out()[0];
    return result;
}

void Register16::Update(const byte2& in, const bit& load) {
    bit0_.Update((bit)in[0], load);
    bit1_.Update((bit)in[1], load);
    bit2_.Update((bit)in[2], load);
    bit3_.Update((bit)in[3], load);
    bit4_.Update((bit)in[4], load);
    bit5_.Update((bit)in[5], load);
    bit6_.Update((bit)in[6], load);
    bit7_.Update((bit)in[7], load);
    bit8_.Update((bit)in[8], load);
    bit9_.Update((bit)in[9], load);
    bit10_.Update((bit)in[10], load);
    bit11_.Update((bit)in[11], load);
    bit12_.Update((bit)in[12], load);
    bit13_.Update((bit)in[13], load);
    bit14_.Update((bit)in[14], load);
    bit15_.Update((bit)in[15], load);
}

byte2 RAM8::Read(const bit3& address) {
    return Mux8Way16(reg0_.Out(), reg1_.Out(), reg2_.Out(), 
                     reg3_.Out(), reg4_.Out(), reg5_.Out(), 
                     reg6_.Out(), reg6_.Out(), address);
}

void RAM8::Write(const bit3& address, const byte2& in, const bit& load) {
    if (address == 0b000u) {
        reg0_.Update(in, load);
    } else if (address == 0b001u) {
        reg1_.Update(in, load);
    } else if (address == 0b010u) {
        reg2_.Update(in, load);
    } else if (address == 0b011u) {
        reg3_.Update(in, load);
    } else if (address == 0b100u) {
        reg4_.Update(in, load);
    } else if (address == 0b101u) {
        reg5_.Update(in, load);
    } else if (address == 0b110u) {
        reg6_.Update(in, load);
    } else if (address == 0b111u) {
        reg7_.Update(in, load);
    }
}

byte2 RAM64::Read(const bit6& address)
{
    bit3 ram8_address {};
    ram8_address[0] = address[0];
    ram8_address[1] = address[1];
    ram8_address[2] = address[2];
    bit3 reg16_address {};
    reg16_address[0] = address[3];
    reg16_address[1] = address[4];
    reg16_address[2] = address[5];
    return Mux8Way16(ram8_0_.Read(reg16_address), ram8_1_.Read(reg16_address), ram8_2_.Read(reg16_address), 
                     ram8_3_.Read(reg16_address), ram8_4_.Read(reg16_address), ram8_5_.Read(reg16_address), 
                     ram8_6_.Read(reg16_address), ram8_7_.Read(reg16_address), ram8_address);
}

void RAM64::Write(const bit6& address, const byte2& in, const bit& load) {
    bit3 ram8_address {};
    ram8_address[0] = address[0];
    ram8_address[1] = address[1];
    ram8_address[2] = address[2];
    bit3 reg16_address {};
    reg16_address[0] = address[3];
    reg16_address[1] = address[4];
    reg16_address[2] = address[5];
    if (ram8_address == 0b000u) {
        ram8_0_.Write(reg16_address, in, load);
    } else if (ram8_address == 0b001u) {
        ram8_1_.Write(reg16_address, in, load);
    } else if (ram8_address == 0b010u) {
        ram8_2_.Write(reg16_address, in, load);
    } else if (ram8_address == 0b011u) {
        ram8_3_.Write(reg16_address, in, load);
    } else if (ram8_address == 0b100u) {
        ram8_4_.Write(reg16_address, in, load);
    } else if (ram8_address == 0b101u) {
        ram8_5_.Write(reg16_address, in, load);
    } else if (ram8_address == 0b110u) {
        ram8_6_.Write(reg16_address, in, load);
    } else if (ram8_address == 0b111u) {
        ram8_7_.Write(reg16_address, in, load);
    }
}

byte2 RAM512::Read(const bit9& address)
{
    bit3 ram64_address {};
    ram64_address[0] = address[0];
    ram64_address[1] = address[1];
    ram64_address[2] = address[2];
    bit6 ram8_address {};
    ram8_address[0] = address[3];
    ram8_address[1] = address[4];
    ram8_address[2] = address[5];
    ram8_address[3] = address[6];
    ram8_address[4] = address[7];
    ram8_address[5] = address[8];
    return Mux8Way16(ram64_0_.Read(ram8_address), ram64_1_.Read(ram8_address), ram64_2_.Read(ram8_address), 
                     ram64_3_.Read(ram8_address), ram64_4_.Read(ram8_address), ram64_5_.Read(ram8_address), 
                     ram64_6_.Read(ram8_address), ram64_7_.Read(ram8_address), ram64_address);
}

void RAM512::Write(const bit9& address, const byte2& in, const bit& load) {
    bit3 ram64_address {};
    ram64_address[0] = address[0];
    ram64_address[1] = address[1];
    ram64_address[2] = address[2];
    bit6 ram8_address {};
    ram8_address[0] = address[3];
    ram8_address[1] = address[4];
    ram8_address[2] = address[5];
    ram8_address[3] = address[6];
    ram8_address[4] = address[7];
    ram8_address[5] = address[8];
    if (ram64_address == 0b000u) {
        ram64_0_.Write(ram8_address, in, load);
    } else if (ram64_address == 0b001u) {
        ram64_1_.Write(ram8_address, in, load);
    } else if (ram64_address == 0b010u) {
        ram64_2_.Write(ram8_address, in, load);
    } else if (ram64_address == 0b011u) {
        ram64_3_.Write(ram8_address, in, load);
    } else if (ram64_address == 0b100u) {
        ram64_4_.Write(ram8_address, in, load);
    } else if (ram64_address == 0b101u) {
        ram64_5_.Write(ram8_address, in, load);
    } else if (ram64_address == 0b110u) {
        ram64_6_.Write(ram8_address, in, load);
    } else if (ram64_address == 0b111u) {
        ram64_7_.Write(ram8_address, in, load);
    }
}

byte2 RAM4k::Read(const bit12& address)
{
    bit3 ram512_address {};
    ram512_address[0] = address[0];
    ram512_address[1] = address[1];
    ram512_address[2] = address[2];
    bit9 ram64_address {};
    ram64_address[0] = address[3];
    ram64_address[1] = address[4];
    ram64_address[2] = address[5];
    ram64_address[3] = address[6];
    ram64_address[4] = address[7];
    ram64_address[5] = address[8];
    ram64_address[6] = address[9];
    ram64_address[7] = address[10];
    ram64_address[8] = address[11];
    return Mux8Way16(ram512_0_.Read(ram64_address), ram512_1_.Read(ram64_address), ram512_2_.Read(ram64_address), 
                     ram512_3_.Read(ram64_address), ram512_4_.Read(ram64_address), ram512_5_.Read(ram64_address), 
                     ram512_6_.Read(ram64_address), ram512_7_.Read(ram64_address), ram512_address);
}

void RAM4k::Write(const bit12& address, const byte2& in, const bit& load) {
    bit3 ram512_address {};
    ram512_address[0] = address[0];
    ram512_address[1] = address[1];
    ram512_address[2] = address[2];
    bit9 ram64_address {};
    ram64_address[0] = address[3];
    ram64_address[1] = address[4];
    ram64_address[2] = address[5];
    ram64_address[3] = address[6];
    ram64_address[4] = address[7];
    ram64_address[5] = address[8];
    ram64_address[6] = address[9];
    ram64_address[7] = address[10];
    ram64_address[8] = address[11];
    if (ram512_address == 0b000u) {
        ram512_0_.Write(ram64_address, in, load);
    } else if (ram512_address == 0b001u) {
        ram512_1_.Write(ram64_address, in, load);
    } else if (ram512_address == 0b010u) {
        ram512_2_.Write(ram64_address, in, load);
    } else if (ram512_address == 0b011u) {
        ram512_3_.Write(ram64_address, in, load);
    } else if (ram512_address == 0b100u) {
        ram512_4_.Write(ram64_address, in, load);
    } else if (ram512_address == 0b101u) {
        ram512_5_.Write(ram64_address, in, load);
    } else if (ram512_address == 0b110u) {
        ram512_6_.Write(ram64_address, in, load);
    } else if (ram512_address == 0b111u) {
        ram512_7_.Write(ram64_address, in, load);
    }
}

byte2 RAM16k::Read(const bit14& address)
{
    bit2 ram4k_address {};
    ram4k_address[0] = address[0];
    ram4k_address[1] = address[1];
    bit12 ram512_address {};
    ram512_address[0] = address[3];
    ram512_address[1] = address[4];
    ram512_address[2] = address[5];
    ram512_address[3] = address[6];
    ram512_address[4] = address[7];
    ram512_address[5] = address[8];
    ram512_address[6] = address[9];
    ram512_address[7] = address[10];
    ram512_address[8] = address[11];
    ram512_address[9] = address[12];
    ram512_address[10] = address[13];
    ram512_address[11] = address[14];
    return Mux4Way16(ram4k_0_.Read(ram512_address), ram4k_1_.Read(ram512_address),
                     ram4k_2_.Read(ram512_address), ram4k_3_.Read(ram512_address), ram4k_address);
}

void RAM16k::Write(const bit14& address, const byte2& in, const bit& load) {
    bit2 ram4k_address {};
    ram4k_address[0] = address[0];
    ram4k_address[1] = address[1];
    bit12 ram512_address {};
    ram512_address[0] = address[3];
    ram512_address[1] = address[4];
    ram512_address[2] = address[5];
    ram512_address[3] = address[6];
    ram512_address[4] = address[7];
    ram512_address[5] = address[8];
    ram512_address[6] = address[9];
    ram512_address[7] = address[10];
    ram512_address[8] = address[11];
    ram512_address[9] = address[12];
    ram512_address[10] = address[13];
    ram512_address[11] = address[14];
    if (ram4k_address == 0b00u) {
        ram4k_0_.Write(ram512_address, in, load);
    } else if (ram4k_address == 0b01u) {
        ram4k_1_.Write(ram512_address, in, load);
    } else if (ram4k_address == 0b10u) {
        ram4k_2_.Write(ram512_address, in, load);
    } else if (ram4k_address == 0b11u) {
        ram4k_3_.Write(ram512_address, in, load);
    }
}
