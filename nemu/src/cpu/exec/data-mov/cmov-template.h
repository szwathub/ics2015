#include "cpu/exec/template-start.h"

#define instr cmovo
static void do_execute() {
    if(cpu.OF == 1) {
        OPERAND_W(op_dest, op_src->val);
    }
    print_asm_template1();
}
make_instr_helper(rm2r);
#undef instr

#define instr cmovno
static void do_execute() {
    if(cpu.OF == 0) {
        OPERAND_W(op_dest, op_src->val);
    }
    print_asm_template1();
}
make_instr_helper(rm2r);
#undef instr

#define instr cmovb     //CMOVB, CMOVC, CMOVNAE
static void do_execute() {
    if(cpu.CF == 1) {
        OPERAND_W(op_dest, op_src->val);
    }
    print_asm_template1();
}
make_instr_helper(rm2r);
#undef instr

#define instr cmovae     //CMOVAE, CMOVNB, CMOVNC
static void do_execute() {
    if(cpu.CF == 0) {
        OPERAND_W(op_dest, op_src->val);
    }
    print_asm_template1();
}
make_instr_helper(rm2r);
#undef instr

#define instr cmove     //CMOVE, CMOVZ
static void do_execute() {
    if(cpu.ZF == 1) {
        OPERAND_W(op_dest, op_src->val);
    }
    print_asm_template1();
}
make_instr_helper(rm2r);
#undef instr

#define instr cmovne     //CMOVNE, CMOVNZ
static void do_execute() {
    if(cpu.ZF == 0) {
        OPERAND_W(op_dest, op_src->val);
    }
    print_asm_template1();
}
make_instr_helper(rm2r);
#undef instr

#define instr cmovbe     //CMOVBE, CMOVNA
static void do_execute() {
    if(cpu.CF == 1 || cpu.ZF == 1) {
        OPERAND_W(op_dest, op_src->val);
    }
    print_asm_template1();
}
make_instr_helper(rm2r);
#undef instr

#define instr cmova     //CMOVA, CMOVNBE
static void do_execute() {
    if(cpu.CF == 0 && cpu.ZF == 0) {
        OPERAND_W(op_dest, op_src->val);
    }
    print_asm_template1();
}
make_instr_helper(rm2r);
#undef instr

#define instr cmovs
static void do_execute() {
    if(cpu.SF == 1) {
        OPERAND_W(op_dest, op_src->val);
    }
    print_asm_template1();
}
make_instr_helper(rm2r);
#undef instr

#define instr cmovns
static void do_execute() {
    if(cpu.SF == 0) {
        OPERAND_W(op_dest, op_src->val);
    }
    print_asm_template1();
}
make_instr_helper(rm2r);
#undef instr

#define instr cmovp
static void do_execute() {
    if(cpu.PF == 1) {
        OPERAND_W(op_dest, op_src->val);
    }
    print_asm_template1();
}
make_instr_helper(rm2r);
#undef instr

#define instr cmovnp    //CMOVNP, CMOVPO
static void do_execute() {
    if(cpu.PF == 0) {
        OPERAND_W(op_dest, op_src->val);
    }
    print_asm_template1();
}
make_instr_helper(rm2r);
#undef instr

#define instr cmovl    //CMOVL, CMOVNGE
static void do_execute() {
    if(cpu.SF != cpu.OF) {
        OPERAND_W(op_dest, op_src->val);
    }
    print_asm_template1();
}
make_instr_helper(rm2r);
#undef instr

#define instr cmovge    //CMOVGE, CMOVNL
static void do_execute() {
    if(cpu.SF == cpu.OF) {
        OPERAND_W(op_dest, op_src->val);
    }
    print_asm_template1();
}
make_instr_helper(rm2r);
#undef instr

#define instr cmovle    //CMOVLE, CMOVNG
static void do_execute() {
    if(cpu.ZF == 1 || cpu.SF != cpu.OF) {
        OPERAND_W(op_dest, op_src->val);
    }
    print_asm_template1();
}
make_instr_helper(rm2r);
#undef instr

#define instr cmovg    //CMOVG, CMOVNLE
static void do_execute() {
    if(cpu.ZF == 0 && cpu.SF == cpu.OF) {
        OPERAND_W(op_dest, op_src->val);
    }
    print_asm_template1();
}
make_instr_helper(rm2r);
#undef instr
#include "cpu/exec/template-end.h"
