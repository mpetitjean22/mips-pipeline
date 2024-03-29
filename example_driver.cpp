#include <iostream>
#include <iomanip>
#include <fstream>
#include <errno.h>
#include "MemoryStore.h"
#include "RegisterInfo.h"
#include "EndianHelpers.h"
#include "DriverFunctions.h"

using namespace std;

static MemoryStore *mem;

int initMemory(ifstream & inputProg)
{
    if(inputProg && mem)
    {
        uint32_t curVal = 0;
        uint32_t addr = 0;

        while(inputProg.read((char *)(&curVal), sizeof(uint32_t)))
        {
            curVal = ConvertWordToBigEndian(curVal);
            int ret = mem->setMemValue(addr, curVal, WORD_SIZE);

            if(ret)
            {
                cout << "Could not set memory value!" << endl;
                return -EINVAL;
            }

            //We're reading 4 bytes each time...
            addr += 4;
        }
    }
    else
    {
        cout << "Invalid file stream or memory image passed, could not initialise memory values" << endl;
        return -EINVAL;
    }

    return 0;
}

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        cout << "Usage: ./cycle_sim <file name>" << endl;
        return -EINVAL;
    }

    ifstream prog;
    prog.open(argv[1], ios::binary | ios::in);

    mem = createMemoryStore();

    if(initMemory(prog))
    {
        return -EBADF;
    }

    CacheConfig icConfig;
    icConfig.cacheSize = 1024;
    icConfig.blockSize = 64;
    icConfig.type = DIRECT_MAPPED;
    icConfig.missLatency = 5;
    CacheConfig dcConfig = icConfig;

    // we did this one
    initSimulator(icConfig, dcConfig, mem);

    // we did this one
    runCycles(10);



    // IMPLEMENT THIS ONE!
    runTillHalt();

    // why is this spelt with an s...
    finaliseSimulator();

    delete mem;
    return 0;
}
