#include "cpu/exec/template-start.h"

#define instr jz
static void do_execute() {
    if(cpu.ZF == 1) {
        cpu.eip += op_src->val;
    }

    print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jbe
static void do_execute() {
    if(cpu.CF == 1 || cpu.ZF == 1) {
        cpu.eip += op_src->val;
        /* HACK for instruction jnbe_i_b */
        /* TODO: fix the magic number */
        cpu.eip &= 0xFFFFF0FF;
    }
}
make_instr_helper(i)
#undef instr

#include "cpu/exec/template-end.h"
