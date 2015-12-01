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
        /* HACK: */
        cpu.eip &= 0xffff0ff;
    }
}
make_instr_helper(i)
#undef instr

#define instr jno
static void do_execute() {
    if(cpu.OF == 0) {
        cpu.eip += op_src->val;
    }
}
make_instr_helper(i)
#undef instr

#define instr jle
static void do_execute() {
    printf("%x\n", cpu.eip);
    printf("%x\n", op_src->val);
    if(cpu.ZF == 1 || cpu.SF != cpu.OF){
        cpu.eip += op_src->val;
    }
    printf("%x\n", cpu.eip);
}
make_instr_helper(i)
#undef instr


#include "cpu/exec/template-end.h"
