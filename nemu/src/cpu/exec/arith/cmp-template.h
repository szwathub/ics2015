#include "cpu/exec/template-start.h"

#define instr cmp
static void do_execute() {
    DATA_TYPE result = op_dest->val - (int32_t)(DATA_TYPE_S)op_src->val;


    DATA_TYPE mask8 = (DATA_TYPE)0xFF;
    DATA_TYPE mask4 = (DATA_TYPE)0x0F;
    cpu.ZF = result ? 0 : 1;
    cpu.CF = ((uint32_t)(op_src->val) >= (uint32_t)(op_dest->val)) ? 1 : 0;
    cpu.AF = (((op_dest->val & mask4) - (op_src->val & mask4)) > mask4) ? 1 : 0;
    cpu.PF = Check_Parity_Flag(result & mask8);

    cpu.SF = MSB(result);
    if (op_src->val > 0) {
		cpu.OF = (result > op_dest->val) ? 1 : 0;
	}
	else if (op_src->val < 0) {
		cpu.OF = (result < op_dest->val) ? 1 : 0;
	}
	else {
		cpu.OF = 0;
	}

    print_asm_template2();
}
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif

make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)
#include "cpu/exec/template-end.h"
