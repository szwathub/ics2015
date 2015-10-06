#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include "common.h"

typedef struct watchpoint {
	int total;
	int NO;
	uint32_t watchpointadd;
	//uint32_t date;
	int exist;
	struct watchpoint *next;

	/* TODO: Add more members if necessary */
} WP;

void init_wp_list();
WP* get_wp_head();

#endif
