#ifndef MEMORY_H
#define MEMORY_H

#include "bits.h"

class DataFlipFLop
{
public:
    void Update(const bit& in);
    bit Out();

private:
    bit prev_ {};
};
    
class RegisterBit
{
public:
    void Update(const bit& in, const bit& load);
    bit Out();

private:
    DataFlipFLop dff_ {};
};

//bit RegisterBit(const bit& in, const bit& load, bit& prev_out, bit& prev_in);

#endif // MEMORY_H

