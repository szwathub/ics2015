#include "cpu/exec/template-start.h"

#define instr add

static void do_execute() {
	DATA_TYPE result, dest, src;
	dest = op_dest->val;
	src = op_src->val;
	result = dest + src;

	DATA_TYPE mask8 = (DATA_TYPE)0xFF;
	DATA_TYPE mask4 = (DATA_TYPE)0x0F;
	OPERAND_W(op_dest, result);

	// printf("dest=%x  src=%x  result=%x\n",dest,src,result);
	if (src > 0) {
		cpu.OF = (result < dest) ? 1 : 0;
	}
	else if (src < 0) {
		cpu.OF = (result > dest) ? 1 : 0;
	}
	else {
		cpu.OF = 0;
	}
	cpu.SF = ((result >> (sizeof(DATA_BYTE) * 8 - 1)) == 1) ? 1 : 0;
	cpu.ZF = (result == 0) ? 1 : 0;
	cpu.AF = (((dest&mask4) - (src&mask4)) > mask4) ? 1 : 0;
	cpu.PF = Check_Parity_Flag(result&mask8);
	cpu.CF = (dest < src) ? 1 : 0;
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
