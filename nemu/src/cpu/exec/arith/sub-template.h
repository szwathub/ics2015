#include "cpu/exec/template-start.h"

#define instr sub

static void do_execute () {
	DATA_TYPE result, dest, src;
	dest = op_dest->val;
	src = op_src->val;
	result = dest - src;
	OPERAND_W(op_dest, result);


	printf("result=%x\n", result);
	cpu.ZF = (dest == src) ? 0 : 1;
	print_asm_template1();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif

#include "cpu/exec/template-end.h"
