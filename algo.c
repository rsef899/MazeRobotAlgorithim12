#include "algo.h"
#include "defs.h"

#include <assert.h>
#include <stdint.h>
#include <string.h>

// Macros that allow easy creation of adjacent points
// i.e. LEFT(start), will get you the position that is
// left from the starting point.
#define LEFT(p) ((Point){.x = (p).x - 1, .y = (p).y})
#define RIGHT(p) ((Point){.x = (p).x + 1, .y = (p).y})
#define ABOVE(p) ((Point){.x = (p).x, .y = (p).y - 1})
#define BELOW(p) ((Point){.x = (p).x, .y = (p).y + 1})

// INPUTS
// map:
//	 The map to be used to run BFS on
// start:
//	 Start points for the algorithm
// ends:
//   The end points which the algorithm should search for
// endCount:
//	 The number of possible end points we have (size of array ends points to)
// out:
//   Where your final path should be written. It is an array.
//
// RETURNS:
//  The length of the path
AlgoResult run_algo(const uint8_t map[MAP_HEIGHT][MAP_WIDTH],
                    Point start,
                    const Point *ends,
                    size_t endCount,
                    Point *out) {
  out[0] = start;
  out[1] = LEFT(out[0]);
  return (AlgoResult){.pathLength = 2};
}

// Don't need to modify this
uint8_t point_eq(Point a, Point b) { return a.x == b.x && a.y == b.y; }
