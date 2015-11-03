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
#include "cpu/exec/template-end.h"
