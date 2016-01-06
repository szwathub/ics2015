#include "cpu/exec/template-start.h"

make_helper(concat(call_i_, SUFFIX)){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    if(DATA_BYTE == 2) {
        cpu.esp -= 2;
        MEM_W(cpu.esp, cpu.eip + len + 1);
        cpu.eip = (cpu.eip + op_src->val) & 0x0000ffff;
    }

    if(DATA_BYTE == 4){
        cpu.esp -= 4;
        MEM_W(cpu.esp,  cpu.eip + len + 1);
        cpu.eip += op_src->val;
    }
    print_asm_template1();

    return len + 1;
}

make_helper(concat(call_rm_, SUFFIX)){
    int len = concat(decode_rm_, SUFFIX)(eip + 1);
    if(2 == DATA_BYTE){
        cpu.esp -= 2;
        MEM_W(cpu.esp, cpu.eip + len + 1);
        cpu.eip = (op_src->val & 0x0000ffff) - 2;
    }
    else if(4 == DATA_BYTE){
        cpu.esp -= 4;
        MEM_W(cpu.esp, cpu.eip + len + 1);
        cpu.eip = op_src->val - 2;
    }
    printf("%x\n%x\n", cpu.eip, MEM_R(op_src->val));
    print_asm_template1();

    return 0;
}
#include "cpu/exec/template-end.h"
