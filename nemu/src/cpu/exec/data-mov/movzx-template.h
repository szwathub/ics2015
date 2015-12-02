#include "cpu/exec/template-start.h"

make_helper(concat(movzx_b_rm2r_, SUFFIX)) {
    int len = decode_rm2r_b(eip + 1);
    DATA_TYPE result = op_src->val & ((1 << (op_src->size * 8)) - 1);

    OPERAND_W(op_dest, result);

    return len + 1;
}

#if DATA_BYTE == 4
make_helper(movzx_w_rm2r_l){
    int len = decode_rm2r_w(eip + 1);

    DATA_TYPE result = op_src->val & ((1 << (op_src->size * 8)) - 1);
    OPERAND_W(op_dest, result);

    return len + 1;
}
#endif

#include "cpu/exec/template-end.h"
