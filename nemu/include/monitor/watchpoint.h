#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include "common.h"

typedef struct watchpoint {
	int total;
	int NO;
	char* expr;
	uint32_t value;
	struct watchpoint *next;

	/* Add more members if necessary */
} WP;

/**
 * @describe init watchpoint list
 * @param {None}
 * @return {None}
 */
void init_wp_list();

/**
 * @describe
 * @param {None}
 * @return {WP *}
 */
WP *new_wp();

/**
 * @describe
 * @param {WP *} wp
 * @return {None}
 */
void free_wp(WP *wp);

/**
 * @describe add a watchpoint onto list
 * @param {char} args
 * @return {None}
 */
void add_wp(char* args);

/**
 * @describe
 * @param {int} NO
 * @param {None}
 */
int del_wp(int NO);

/**
 * @describe
 * @param {None}
 * @return {None}
 */
int show_all_wp();
#endif
