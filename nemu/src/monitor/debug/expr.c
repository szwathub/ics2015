#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

char *substring(char* ch, int pos, int length);

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
	{"-", '-'},						//sub
	{"\\*", '*'},					//mul
	{"/", '/'},						//div
	{"\\(", '('},
	{"\\)", ')'},
	{"[0-9]+", DEC_NUM},			//number
	{"0x[0-9a-fA-f]+", HEX_NUM},	//
	{"\\$[a-z]+", REG},				//REG
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
				nr_token++;
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;


				Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
					i, rules[i].regex, position, substr_len,
					substr_len, substr_start);

				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. Add codes
				 * to record the token in the array ``tokens''. For certain
				 * types of tokens, some extra actions should be performed.
				 */

				switch(rules[i].token_type) {
					case DEC_NUM:
						tokens[nr_token-1].type = DEC_NUM;
						strcpy(tokens[nr_token-1].str,
								substring(substr_start, 0, substr_len));
						break;
					case HEX_NUM:
						tokens[nr_token].type = HEX_NUM;
						strcpy(tokens[nr_token-1].str,
								substring(substr_start, 0, substr_len));
						break;
					case '+':
						tokens[nr_token-1].type = '+';
						strcpy(tokens[nr_token-1].str,
								substring(substr_start, 0, substr_len));
						break;
					case '-':
						tokens[nr_token].type = '-';
						strcpy(tokens[nr_token-1].str,
								substring(substr_start, 0, substr_len));
						break;
					case '*':
						tokens[nr_token].type = '*';
						strcpy(tokens[nr_token-1].str,
								substring(substr_start, 0, substr_len));
						break;
					case '/':
						tokens[nr_token].type = '/';
						strcpy(tokens[nr_token-1].str,
								substring(substr_start, 0, substr_len));
						break;
					case '(':
						tokens[nr_token].type = '(';
						strcpy(tokens[nr_token-1].str,
								substring(substr_start, 0, substr_len));
								break;
					case ')':
						tokens[nr_token].type = ')';
						strcpy(tokens[nr_token-1].str,
								substring(substr_start, 0, substr_len));
						break;
					case REG:
						tokens[nr_token].type = REG;
						strcpy(tokens[nr_token-1].str,
								substring(substr_start, 0, substr_len));
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
 * @describe evaluate the expression and return the value
 * @param {int, int} p, q
 * @return {int} value
 */

int eval(int p, int q) {
	if(p > q) {
		/* Bad expression */
		;
	}
	else if(p == q) {
		/*
		 * Single token
		 * For now, this token should be a number
		 * return the value of the exprssion
		 */
		 ;
	}
	else {
		//val1 = eval(p, op-1);
		//val2 = eval(op+1, q);
		/*
		switch(token_type) {
			case '+': return val1 + val2;
			case '-': ;
			case '*': ;
			case '/': ;
			default: assert(0);
			;
		}*/
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
	char *pch = ch;

	char *subch = (char *)calloc(sizeof(char), length+1);

	int i;

	pch = pch + pos;

	for(i = 0; i < length; i++) {
		subch[i] = *(pch++);
	}
	subch[length] = '\0';

	return subch;
}

uint32_t expr(char *e, bool *success) {
    int i;
	if(!make_token(e)) {
		*success = false;
		printf("Error");
		return 0;
	}
	/* TODO: Insert codes to evaluate the expression. */
	for(i = 0; i < nr_token; i++) {
		if(tokens[i].type == '*' && (i == 0 || tokens[i-1].type != DEC_NUM)) {
			//tokens[i].type == DEREF;
			;
		}
	}
	for(i = 0; i < nr_token; i++) {
		printf("%s\n", tokens[i].str);
	}
	//panic("please implement me");
	return 0;
}
