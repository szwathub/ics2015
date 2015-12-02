#include "cpu/exec/template-start.h"

make_helper(concat(movsx_b_rm2r_, SUFFIX)) {
    int len = decode_rm2r_b(eip + 1);
    DATA_TYPE result = op_src->val;

    DATA_TYPE mask = (1 << (8 * DATA_BYTE -1)) && (0 << (8 * op_src->size - 1));

    if (result >> (8 * op_src->size - 1) == 1) {
        result |= mask;
    }
    else {
        result &= ((1 << 8 * op_src->size)-1);
    }
    OPERAND_W(op_dest, result);

    return len + 1;
}

#if DATA_BYTE == 4
make_helper(movsx_w_rm2r_l){
    int len = decode_rm2r_w(eip + 1);

    DATA_TYPE result = op_src->val;

    DATA_TYPE mask = (1 << (8 * DATA_BYTE -1)) && (0 << (8 * op_src->size - 1));

    if (result >> (8 * op_src->size - 1) == 1) {
        result |= mask;
    }
    else {
        result &= ((1 << 8 * op_src->size)-1);
    }
    OPERAND_W(op_dest, result);

    return len + 1;
}
#endif

#include "cpu/exec/template-end.h"
