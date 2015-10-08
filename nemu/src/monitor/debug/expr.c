#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>
#include <stdlib.h>

char *substring(char* ch, int pos, int length);
uint32_t eval(int p, int q);
bool check_parentness(int p, int q);
uint32_t hextodec(char *str);

enum {
	NOTYPE = 256, EQ, HEX_NUM, DEC_NUM, REG

	/* TODO: Add more token types */

};

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +",	NOTYPE},				// spaces
	{"\\+", '+'},					// plus
	{"==", EQ},						// equal
	{"-", '-'},						// sub
	{"\\*", '*'},					// mul
	{"/", '/'},						// div
	{"\\(", '('},
	{"\\)", ')'},
	{"0x[0-9a-fA-F]+", HEX_NUM},	//
	{"[0-9]+", DEC_NUM},			// number
	{"\\$[a-z]+", REG},				// REG
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			Assert(ret == 0, "regex compilation failed: %s\n%s",
					error_msg, rules[i].regex);
		}
	}
}

typedef struct token {
	int type;
	char str[32];
} Token;

Token tokens[32];
int nr_token;

static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;

	nr_token = 0;

	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0
				&& pmatch.rm_so == 0) {
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;


				//Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
				//	i, rules[i].regex, position, substr_len,
				//	substr_len, substr_start);

				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. Add codes
				 * to record the token in the array ``tokens''. For certain
				 * types of tokens, some extra actions should be performed.
				 */

				switch(rules[i].token_type) {
					case DEC_NUM:
						tokens[nr_token].type = DEC_NUM;
						strcpy(tokens[nr_token].str,
								substring(substr_start, 0, substr_len));
						nr_token++;
						break;
					case HEX_NUM:
						tokens[nr_token].type = HEX_NUM;
						strcpy(tokens[nr_token].str,
								substring(substr_start, 0, substr_len));
						nr_token++;
						break;
					case '+':
						tokens[nr_token].type = '+';
						strcpy(tokens[nr_token].str,
								substring(substr_start, 0, substr_len));
						nr_token++;
						break;
					case '-':
						tokens[nr_token].type = '-';
						strcpy(tokens[nr_token].str,
								substring(substr_start, 0, substr_len));
						nr_token++;
						break;
					case '*':
						tokens[nr_token].type = '*';
						strcpy(tokens[nr_token].str,
								substring(substr_start, 0, substr_len));
						nr_token++;
						break;
					case '/':
						tokens[nr_token].type = '/';
						strcpy(tokens[nr_token].str,
								substring(substr_start, 0, substr_len));
						nr_token++;
						break;
					case '(':
						tokens[nr_token].type = '(';
						strcpy(tokens[nr_token].str,
								substring(substr_start, 0, substr_len));
						nr_token++;
						break;
					case ')':
						tokens[nr_token].type = ')';
						strcpy(tokens[nr_token].str,
								substring(substr_start, 0, substr_len));
						nr_token++;
						break;
					case REG:
						tokens[nr_token].type = REG;
						strcpy(tokens[nr_token].str,
								substring(substr_start, 0, substr_len));
						nr_token++;
						break;
					case NOTYPE:
						break;
					//default: panic("please implement me");
				}

				break;
			}
		}

		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n",
				position, e, position, "");
			return false;
		}
	}

	return true;
}

/*
 * @describe get the value of the reg
 * @param {string} reg
 * @return {uint32_t}
 */
uint32_t getreg(char* reg) {
	uint32_t res;
	if(!strcmp(reg, "$eax")) res = cpu.eax;
	else if(!strcmp(reg, "$ecx")) res = cpu.ecx;
	else if(!strcmp(reg, "$edx")) res = cpu.edx;
	else if(!strcmp(reg, "$ebx")) res = cpu.ebx;
	else if(!strcmp(reg, "$esp")) res = cpu.esp;
	else if(!strcmp(reg, "$ebp")) res = cpu.ebp;
	else if(!strcmp(reg, "$esi")) res = cpu.esi;
	else if(!strcmp(reg, "$edi")) res = cpu.edi;

	else if(!strcmp(reg, "$eip")) res = cpu.eip;

	else if(!strcmp(reg, "$ax")) res = reg_w(0);
	else if(!strcmp(reg, "$cx")) res = reg_w(1);
	else if(!strcmp(reg, "$dx")) res = reg_w(2);
	else if(!strcmp(reg, "$bx")) res = reg_w(3);
	else if(!strcmp(reg, "$sp")) res = reg_w(4);
	else if(!strcmp(reg, "$bp")) res = reg_w(5);
	else if(!strcmp(reg, "$si")) res = reg_w(6);
	else if(!strcmp(reg, "$di")) res = reg_w(7);

	else if(!strcmp(reg, "$al")) res = reg_b(0);
	else if(!strcmp(reg, "$cl")) res = reg_b(1);
	else if(!strcmp(reg, "$dl")) res = reg_b(2);
	else if(!strcmp(reg, "$bl")) res = reg_b(3);
	else if(!strcmp(reg, "$ah")) res = reg_b(4);
	else if(!strcmp(reg, "$ch")) res = reg_b(5);
	else if(!strcmp(reg, "$dh")) res = reg_b(6);
	else if(!strcmp(reg, "$bh")) res = reg_b(7);

	else assert(0);
	return res;
}
/*
 * @describe evaluate the expression and return the value
 * @param {int, int} p, q
 * @return {int} value
 */
uint32_t eval(int p, int q) {
	if(p > q) {
		/* Bad expression */
		assert(0);
	}
	else if(p == q) {
		/*
		 * Single token
		 * For now, this token should be a number
		 * return the value of the exprssion
		 */
		if(tokens[p].type == DEC_NUM) {
			return atoi(tokens[p].str);
		}
		if(tokens[p].type == HEX_NUM) {
			return strtol(tokens[p].str, NULL, 16);
		}
		if(tokens[p].type == REG) {
			return getreg(tokens[p].str);
		}
	}
	else if(check_parentness(p, q) == true) {
		/* the expression is surrounded by a matched pair of parentheses.
		 * If that is the case, just throw away the parentheses.
		 */
		return eval(p + 1, q - 1);
	}
	else {
		int i = p;
		int j = 0;
		int op = -1;
		int flag = 0;
		uint32_t val1;
		uint32_t val2;

		for(j = 0; i <= q; i++) {
			if(j == 0
				&& (tokens[i].type == '+' || tokens[i].type == '-')) {
				if(flag < 2) {
					op = i;
					flag = 2;
				}
			}
			else if(j == 0
				&& (tokens[i].type == '*' || tokens[i].type == '/')) {
				if(op == -1) {
					op = i;
				}
				if( flag < 1) {
					op = i;
					flag = 1;
				}
			}
		}

		val1 = eval(p, op - 1);
		val2 = eval(op + 1, q);
		switch(tokens[op].type) {
			case '+':
				return val1 + val2;
				break;
			case '-':
				return val1 - val2;
				break;
			case '*':
				return val1 * val2;
				break;
			case '/':
				return val1 / val2;
				break;
				default: assert(0);
		}
	}

	return 0;
}

/*
 * @describe returns the characters in a string beginning at the specified
 *		location through the specified number of characters.
 * @param {string, int, int} ch, pos, length
 * @return {string}
 */
char *substring(char* ch, int pos, int length) {
	int i;
	char *pch = ch;
	char *subch = (char *)calloc(sizeof(char), length+1);

	pch = pch + pos;

	for(i = 0; i < length; i++) {
		subch[i] = *(pch++);
	}
	subch[length] = '\0';

	return subch;
}

/*
 * @describe
 * @param {int, int} p, q;
 * return {boolean}
 */
bool check_parentness(int p, int q) {
	if(tokens[p].type == '(' && tokens[q].type == ')') {
		int i = p + 1;
		int j = 0;

		while(i < q) {
			if(tokens[i].type == '(') {
				j++;
			}
			else if(tokens[i].type == ')') {
				if(j == 0) {
					return false;
				}
				j--;
			}
			i++;
		}
		if(j == 0) {
			return true;
		}
	}
	return false;
}

/*
 * @describe HEX_NUM to DEC_NUM
 * @param {string}
 * @return {int}
 */
uint32_t hextodec(char *str) {
	int len = strlen(str);
	int i;

	uint32_t res = 0;
	for(i = 2; i < len; i++) {
		if(str[i] >= 'A' && str[i] <= 'F') {
			res = res * 16 + (str[i] - 'A' + 10);
		}
		if(str[i] >= 'a' && str[i] <= 'f') {
			res = res * 16 + (str[i] - 'a' + 10);
		}
		if(str[i] >= '0' && str[i] <= '9') {
			res = res * 16 + (str[i] - '0');
		}
	}
	return res;
}

uint32_t expr(char *e, bool *success) {
    int i;
	if(!make_token(e)) {
		*success = false;
		return 0;
	}
	*success = true;
	/* TODO: Insert codes to evaluate the expression. */
	for(i = 0; i < nr_token; i++) {
		if(tokens[i].type == '*' && (i == 0 || tokens[i-1].type != DEC_NUM)) {
			//tokens[i].type == DEREF;
			;
		}
	}
	for(i = 0; i < nr_token; i++) {
		printf("tokens[%d]: type: %d : %s\n", i, tokens[i].type ,tokens[i].str);
	}
	return eval(0, nr_token - 1);
	//panic("please implement me");
}
