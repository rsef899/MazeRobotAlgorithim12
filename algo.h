#ifndef _ALGO_H
#define _ALGO_H

#include "defs.h"
#include <stdbool.h>

int run_algo(uint8_t map[MAP_HEIGHT][MAP_WIDTH], Point start, Point end, Point *result);

#endif // _ALGO_H
