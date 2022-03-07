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

/*
bit RegisterBit(const bit& in, const bit& load, bit& prev_out, bit& prev_in) {
    //std::cout << "RB_in: " << in << ", RB_load: " << load << ", RB_prev_out: " << prev_out << std::endl;
    bit out{ DataFlipFLop(Mux(prev_out, in, load), prev_in) };
    prev_out = out;
    return out;
} 

byte2 Register16(const byte2& in, const bit& load, byte2& prev_out, byte2& prev_in) {
    byte2 out{};
    for (int i = 0; i < 16; i++) {
        bit prev_in_bit{ prev_in[i] };
        bit prev_out_bit{ prev_out[i] };
        out[i] = RegisterBit((bit)in[i], load, prev_out_bit, prev_in_bit)[0];
        prev_out[i] = out[i];
        prev_in[i] = in[i];
    }
    return out; 
}
*/
