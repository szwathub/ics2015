#include "cpu/exec/template-start.h"

#define instr jz
static void do_execute() {
    if(cpu.ZF == 1) {
        cpu.eip += (int32_t)(DATA_TYPE_S)op_src->val;
    }
    print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jbe
static void do_execute() {
    if(cpu.CF == 1 || cpu.ZF == 1) {
        cpu.eip += (int32_t)(DATA_TYPE_S)op_src->val;
        //cpu.eip += op_src->val;
        /* HACK: */
        //cpu.eip &= 0xffff0ff;
    }
}
make_instr_helper(i)
#undef instr

#define instr jno
static void do_execute() {
    if(cpu.OF == 0) {
        cpu.eip += (int32_t)(DATA_TYPE_S)op_src->val;
    }
}
make_instr_helper(i)
#undef instr

#define instr jle
static void do_execute() {
    if(cpu.ZF == 1 || cpu.SF != cpu.OF) {
        cpu.eip += (int32_t)(DATA_TYPE_S)op_src->val;
    }
}
make_instr_helper(i)
#undef instr

#define instr ja
static void do_execute() {
    if(cpu.CF == 0 && cpu.ZF == 0) {
        cpu.eip += (int32_t)(DATA_TYPE_S)op_src->val;
    }
}
make_instr_helper(i)
#undef instr

#define instr jae
static void do_execute() {
    if(cpu.CF == 0) {
        cpu.eip += (int32_t)(DATA_TYPE_S)op_src->val;
    }
}
make_instr_helper(i)
#undef instr

#define instr jb
static void do_execute() {
    if(cpu.CF == 1) {
        cpu.eip += (int32_t)(DATA_TYPE_S)op_src->val;
    }
}
make_instr_helper(i)
#undef instr

#define instr jcxz
static void do_execute() {
    if(reg_w(R_CX) == 0 || reg_l(R_ECX) == 0) {
        cpu.eip += (int32_t)(DATA_TYPE_S)op_src->val;
    }
}
make_instr_helper(i)
#undef instr

#define instr jg
static void do_execute() {
    if(cpu.ZF == 0 && cpu.SF == cpu.OF) {
        cpu.eip += (int32_t)(DATA_TYPE_S)op_src->val;
    }
}
make_instr_helper(i)
#undef instr

#define instr jge
static void do_execute() {
    if(cpu.SF == cpu.OF) {
        cpu.eip += (int32_t)(DATA_TYPE_S)op_src->val;
    }
}
make_instr_helper(i)
#undef instr

#define instr jl
static void do_execute() {
    if(cpu.SF != cpu.OF) {
        cpu.eip += (int32_t)(DATA_TYPE_S)op_src->val;
    }
}
make_instr_helper(i)
#undef instr

#define instr jne
static void do_execute() {
    if(cpu.ZF == 0) {
        cpu.eip += (int32_t)(DATA_TYPE_S)op_src->val;
        //cpu.eip += op_src->val;
    }
}
make_instr_helper(i)
#undef instr

#define instr jnp
static void do_execute() {
    if(cpu.PF == 0) {
        cpu.eip += (int32_t)(DATA_TYPE_S)op_src->val;
    }
}
make_instr_helper(i)
#undef instr

#define instr jns
static void do_execute() {
    if(cpu.SF == 0) {
        cpu.eip += (int32_t)(DATA_TYPE_S)op_src->val;
    }
}
make_instr_helper(i)
#undef instr

#define instr jo
static void do_execute() {
    if(cpu.OF == 1) {
        cpu.eip += (int32_t)(DATA_TYPE_S)op_src->val;
    }
}
make_instr_helper(i)
#undef instr

#define instr jp
static void do_execute() {
    if(cpu.PF == 1) {
        cpu.eip += (int32_t)(DATA_TYPE_S)op_src->val;
    }
}
make_instr_helper(i)
#undef instr

#define instr js
static void do_execute() {
    if(cpu.SF == 1) {
        cpu.eip += (int32_t)(DATA_TYPE_S)op_src->val;
    }
}
make_instr_helper(i)
#undef instr

#include "cpu/exec/template-end.h"
