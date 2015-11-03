#include "cpu/exec/template-start.h"

#define instr test

static void do_execute() {
    DATA_TYPE result;
    DATA_TYPE mask8 = (DATA_TYPE)0xFF;

    result = op_dest->val & op_src->val;

    cpu.CF = cpu.OF = 0;
    cpu.ZF = (result == 0) ? 1 : 0;
    cpu.SF = ((result >> (sizeof(DATA_BYTE) * 8 - 1)) == 1) ? 1 : 0;
    cpu.PF = Check_Parity_Flag(result & mask8);
    print_asm_template1();
}

make_instr_helper(r2rm)
make_instr_helper(i2rm)
make_instr_helper(i2a)

#include "cpu/exec/template-end.h"
