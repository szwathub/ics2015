#include "cpu/exec/template-start.h"

#define instr stos
static void do_execute() {
    if(DATA_BYTE == 1) {
        MEM_W(reg_l(R_EDI), reg_b(R_AL));
        if(cpu.DF == 0) {
            reg_l(R_EDI) += 1;
        }
        else {
            reg_l(R_EDI) -= 1;
        }
    }

    else if(DATA_BYTE == 2) {
        MEM_W(reg_l(R_EDI), reg_b(R_AX));
        if(cpu.DF == 0) {
            reg_l(R_EDI) += 2;
        }
        else {
            reg_l(R_EDI) -= 2;
        }
    }
    else {
        MEM_W(reg_l(R_EDI), reg_b(R_EAX));
        if(cpu.DF == 0) {
            reg_l(R_EDI) += 4;
        }
        else {
            reg_l(R_EDI) -= 4;
        }
    }
    
    print_asm_template1();
}

make_instr_helper(rm)


#include "cpu/exec/template-end.h"
