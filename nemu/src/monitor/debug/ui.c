#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "cpu/helper.h"

void cpu_exec(uint32_t);
void print_bin_instr(swaddr_t eip, int len);
void ptest(swaddr_t eip_temp,int instr_len,int n_temp);

/* We use the ``readline'' library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(nemu) >");

	if (line_read && *line_read) {
		add_history(line_read);
	}

	return line_read;
}
/*
 * @describe Continue the execution of the program
 * @param {string} args
 */
static int cmd_c(char *args) {
	cpu_exec(-1);
	return 0;
}

/*
 * @describe Exit NEMU
 * @param {string} args
 */
static int cmd_q(char *args) {
	return -1;
}

static int cmd_help(char *args);

/*
 * @describe Single-step Debugging
 * @param {string} args
 */
static int cmd_si(char *args) {
	if(args == NULL) {
		cpu_exec(1);
	}
	else {
		cpu_exec(atoi(args));
	}
	return 0;
}

/*
 * @describe Printing reg status or watchpoint
 * @param {string} args
 */
static int cmd_info(char *args) {
	WP *wp = get_wp_head();
	int i = 0;
	if(args == NULL) {
		printf("The most commonly used info commands are:\n\n");
		printf("r\t\tprint reg status\n");
		printf("w\t\tprint information of watchpoint\n");
	}
	else if(strcmp(args, "r") == 0) {
		for(i = 0; i < 8; i++) {
			printf("%s\t\t 0x%x\t%u\n", regsl[i], cpu.gpr[i]._32, cpu.gpr[i]._32);
		}
		for(i = 0; i < 8; i++) {
			printf("%s\t\t 0x%x\t%u\n", regsw[i], cpu.gpr[i]._16, cpu.gpr[i]._16);
		}
		for(i = 0; i < 8; i++) {
			//printf("%s\t\t 0x%x\t%u\n", regsb[i], cpu.gpr[i]._8, cpu.gpr[i]._8);
		}
	}
	else if(strcmp(args, "w") == 0) {
		if(wp->NO < 0) {
			return -1;
		}
		else {
			for(i = 0; i < wp->NO; i++) {
				if(wp->exist == 1) {
					printf("%d/t%d\n",wp->NO,wp->watchpointadd);
				}
				wp = wp->next;
			}
		}
	}
	else if(strcmp(args, "--help") == 0) {
		printf("The most commonly used info commands are:\n\n");
		printf("r\t\tprint reg status\n");
		printf("w\t\tprint information of watchpoint\n");
	}
	else {
		printf("info: '%s' is not a info command. See 'info --help'.\n", args);
	}
	return 0;
}

/**
 * @describe
 * @param {string} args
 */
static int cmd_p(char *args) {
	if(args == NULL) {
		printf("Simple: p expr\n");
		return 0;
	}
	bool flag;
	printf("%d\n", expr(args, &flag));
	return 0;
}

/**
 * @describe Scan memory
 * @param {string} args
 */
static int cmd_scan(char *args) {
	char *args_len;
	char *expression;
	int count;
	if(args == NULL) {
		printf("Simple: x N expr\n");
		return 0;
	}
	args_len = args + strlen(args);
	char *arg = strtok(args, " ");
	count = atoi(arg);

	expression = arg + strlen(arg) + 1;

	if(expression > args_len) {
		printf("Simple: x N expr\n");
		return 0;
	}
	bool flag;
	uint32_t address = expr(expression, &flag);
	while(count > 8) {
		print_bin_instr(address, 8);
		address += 8;
		count -= 8;
	}
	if(count > 0) {
		print_bin_instr(address, count);
	}
	printf("\n");
	return 0;
}

/* TODO:
 * @describe Set a watchpoint
 * @param {string} args
 */
static int cmd_w(char *args) {
	return 0;
}

/*
 * @describe Delete a watch point
 * @param {string} args
 */
static int cmd_delete(char *args) {
	WP *wp = get_wp_head();
	int i;
	for(i = 0; i < 32; i++) {
		if(atoi(args) >= 32) {
			printf("Error!\n");
			return 0;
		}
		else if(atoi(args) == wp->NO) {
			wp->exist = 0;
			return 0;
		}
		else {
			printf("NO.%d watchpoint not found!\n", atoi(args));
			return 0;
		}
		wp = wp->next;
	}
	return 0;
}

/* TODO
 *
 */
static int cmd_bt(char *args) {
		return 0;
}

static struct {
	char *name;
	char *description;
	int (*handler) (char *);
} cmd_table [] = {
	{ "help", "Display informations about all supported commands", cmd_help },
	{ "c", "Continue the execution of the program", cmd_c },
	{ "q", "Exit NEMU", cmd_q },
	{ "si", "Single-step debugging", cmd_si},
	{ "info", "Print reg status or watchpoint", cmd_info},
	{ "p", "表达式求值", cmd_p},
	{ "x", "Scan memory", cmd_scan},
	{ "w", "Set a watchpoint", cmd_w},
	{ "d", "Delete a watchpoint", cmd_delete},
	{ "bt", "Print ", cmd_bt}

	/* Add more commands */

};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
	/* extract the first argument */
	char *arg = strtok(NULL, " ");
	int i;

	if(arg == NULL) {
		/* no argument given */
		for(i = 0; i < NR_CMD; i ++) {
			printf("%s\t\t%s\n", cmd_table[i].name, cmd_table[i].description);
		}
	}
	else {
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(arg, cmd_table[i].name) == 0) {
				printf("%s\t\t%s\n", cmd_table[i].name, cmd_table[i].description);
				return 0;
			}
		}
		printf("Nemu: command not found: %s\n", arg);
	}
	return 0;
}

void ui_mainloop() {
	while(1) {
		char *str = rl_gets();
		char *str_end = str + strlen(str);

		/* extract the first token as the command */
		char *cmd = strtok(str, " ");
		if(cmd == NULL) {
			continue;
		}

		/* treat the remaining string as the arguments,
		 * which may need further parsing
		 */
		char *args = cmd + strlen(cmd) + 1;
		if(args >= str_end) {
			args = NULL;
		}

#ifdef HAS_DEVICE
		extern void sdl_clear_event_queue(void);
		sdl_clear_event_queue();
#endif

		int i;
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(cmd, cmd_table[i].name) == 0) {
				if(cmd_table[i].handler(args) < 0) {
					return;
				}
				break;
			}
		}

		if(i == NR_CMD) {
			printf("Nemu: command not found: %s\n", cmd);
		}
	}
}
