#ifndef REGISTER_H
#define REGISTER_H

#include <cstdint>

class Register {
public:
    virtual void CommitValues() = 0;
};

#endif
