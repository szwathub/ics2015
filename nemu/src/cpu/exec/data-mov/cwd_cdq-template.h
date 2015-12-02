#include "cpu/exec/template-start.h"

make_helper(concat(cwd_cdq_r_, SUFFIX)) {
    if(DATA_BYTE == 2) {
        if((cpu.gpr[0]._16 >> 15) == 1) {
            cpu.gpr[2]._16 = 0xffff;
        }
        else {
            cpu.gpr[2]._16 = 0x0000;
        }
    }
    else {
        if((cpu.eax>>31) == 1) {
            cpu.edx = 0xffffffff;
        }
        else {
            cpu.edx = 0x00000000;
        }
    }

    return 1;
}

//make_instr_helper(r)
#include "cpu/exec/template-end.h"
