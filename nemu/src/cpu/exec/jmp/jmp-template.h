#include "cpu/exec/template-start.h"
make_helper(concat(jmp_i_, SUFFIX)){
    int len = concat(decode_i_, SUFFIX)(eip + 1);
    //printf("%x\n", op_src->val);
    cpu.eip += (uint32_t)(DATA_TYPE)op_src->val;
    if(DATA_BYTE == 2) {
        cpu.eip &= 0x0000ffff;
    }
    print_asm_template1();

    return len + 1;
}

make_helper(concat(jmp_rm_, SUFFIX)){
    //int len =
    concat(decode_rm_, SUFFIX)(eip + 1);
    cpu.eip = (uint32_t)(DATA_TYPE)op_src->val;
    if(2 == DATA_BYTE){
        cpu.eip &= 0x0000ffff;
    }
    print_asm_template1();

    return 0;
}

#include "cpu/exec/template-end.h"
