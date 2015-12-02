#include "cpu/exec/template-start.h"

#define instr cmps
static void do_execute() {
    int IncDec = 0;

    IncDec = (cpu.DF == 0) ? DATA_BYTE : -DATA_BYTE;

    DATA_TYPE src = MEM_R(reg_l(R_ESI));
    DATA_TYPE dest = MEM_R(reg_l(R_EDI));
    DATA_TYPE result =  src - dest;

    result =  src - dest;

    DATA_TYPE mask8 = (DATA_TYPE)0xFF;
    DATA_TYPE mask4 = (DATA_TYPE)0x0F;
    cpu.ZF = result ? 0 : 1;
    cpu.CF = ((uint32_t)(src) >= (uint32_t)(dest)) ? 0 : 1;
    cpu.AF = (((dest&mask4) - (src&mask4)) > mask4) ? 1 : 0;
    cpu.PF = Check_Parity_Flag(result&mask8);

    cpu.SF = ((result >> (sizeof(DATA_BYTE) * 8 - 1)) == 1) ? 1 : 0;
    if (src > 0) {
        cpu.OF = (result < dest) ? 1 : 0;
    }
    else if (src < 0) {
        cpu.OF = (result > dest) ? 1 : 0;
    }
    else {
        cpu.OF = 0;
    }

    reg_l(R_ESI) += IncDec;
    reg_l(R_EDI) += IncDec;

    print_asm_template1();
}

make_instr_helper(rm)


#include "cpu/exec/template-end.h"
