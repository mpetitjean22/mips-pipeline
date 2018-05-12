#ifndef REGISTER_H
#define REGISTER_H

#include <inttypes.h>

class StageRegister {
public:
    virtual void CommitValues() = 0;
};

#endif
