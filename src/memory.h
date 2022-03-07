#ifndef MEMORY_H
#define MEMORY_H

#include "bits.h"
#include <vector>

class DataFlipFLop {
public:
    void Update(const bit& in);
    bit Out();

private:
    bit prev_ {};
};
    
class RegisterBit {
public:
    void Update(const bit& in, const bit& load);
    bit Out();

private:
    DataFlipFLop dff_ {};
};

class Register16 {
public:
    Register16();
    void Update(const byte2& in, const byte2& load);
    byte2 Out();

private:
    std::vector<RegisterBit> registers_ {};
};


#endif // MEMORY_H

