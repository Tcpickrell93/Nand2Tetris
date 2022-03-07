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

Register16::Register16() {
    for (int i = 0; i < 16; i++) {
        registers_.push_back(RegisterBit());
    }
}

byte2 Register16::Out() {
    byte2 result {};
    for (int i = 0; i < 16; i++) {
        result[i] = registers_[i].Out()[0];
    }
    return result;
}

void Register16::Update(const byte2& in, const byte2& load) {
    for (int i = 0; i < 16; i++) {
        bit in_bit = in[i];
        bit load_bit = load[i];
        registers_[i].Update(in_bit, load_bit);
    }
}