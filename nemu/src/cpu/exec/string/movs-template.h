#include "cpu/exec/template-start.h"

#define instr movs
static void do_execute() {
    int IncDec = (cpu.DF == 0) ? DATA_BYTE : -DATA_BYTE;

    swaddr_write(reg_l(R_EDI), DATA_BYTE,
            swaddr_read(reg_l(R_ESI), DATA_BYTE));
    reg_l(R_ESI) += IncDec;
    reg_l(R_EDI) += IncDec;
}

make_instr_helper(rm)
#include "cpu/exec/template-end.h"
