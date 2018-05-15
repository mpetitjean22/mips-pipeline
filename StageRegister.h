/* -------------------------------------------------------------------------- */
/* StageRegister.h                                                            */
/* -------------------------------------------------------------------------- */

#ifndef REGISTER_H
#define REGISTER_H

#include <inttypes.h>

/* the parent class that will be used to make all of our stage register between
    all of the stages IF, ID, EX, MEM, and WB */ 
class StageRegister {
public:
    virtual void CommitValues() = 0;
};

#endif
