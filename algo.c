#include "algo.h"

#include <assert.h>
#include <stdint.h>
#include <string.h>

#define IDX_POINT(map, p) ((map)[(p).y][(p).x])

#define LEFT(p) ((Point){.x = (p).x - 1, .y = (p).y})
#define RIGHT(p) ((Point){.x = (p).x + 1, .y = (p).y})
#define ABOVE(p) ((Point){.x = (p).x, .y = (p).y - 1})
#define BELOW(p) ((Point){.x = (p).x, .y = (p).y + 1})

// INPUTS
// map:
//   Outer pointer points to rows
//   Inner pointer points to each column inside the row
// result:
//   The output of your path should be put here. It is
//   an array of MAX_PATH_SIZE points.
//
// RETURNS:
//  The length of the path
int run_algo(uint8_t map[MAP_HEIGHT][MAP_WIDTH], Point start, Point end,
             Point *result) {
  // The following algorithm finds a random possible path
  // uses the result array as a stack

  result[0] = start;
  size_t stackSize = 1;

  // Stack allocated map, might be inefficient
  // if we know we aren't multi-threaded, we can make it static
  uint8_t visited[MAP_HEIGHT][MAP_WIDTH];
  memset(visited, 0, sizeof(visited));

  while (stackSize != 0) {
    Point curr = result[stackSize - 1];
    assert(IDX_POINT(map, curr) != POINT_WALL);
    IDX_POINT(visited, curr) = true;

    if (point_eq(curr, end)) {
      return stackSize;
    }

    // clang-format off
    if (curr.x + 1 < MAP_WIDTH 
				&& !IDX_POINT(map, RIGHT(curr)) 
				&& !IDX_POINT(visited, RIGHT(curr))) {
      assert(stackSize < MAX_PATH_SIZE);
      result[stackSize++] = RIGHT(curr);
      continue;
    }

    if (curr.x - 1 >= 0 
				&& !IDX_POINT(map, LEFT(curr)) 
				&& !IDX_POINT(visited, LEFT(curr))) {
      assert(stackSize < MAX_PATH_SIZE);
      result[stackSize++] = LEFT(curr);
      continue;
    }

    if (curr.y - 1 >= 0 
				&& !IDX_POINT(map, ABOVE(curr))
				&& !IDX_POINT(visited, ABOVE(curr))) {
      assert(stackSize < MAX_PATH_SIZE);
      result[stackSize++] = ABOVE(curr);
      continue;
    }

    if (curr.y + 1 < MAP_HEIGHT 
				&& !IDX_POINT(map, BELOW(curr))
				&& !IDX_POINT(visited, BELOW(curr))) {
      assert(stackSize < MAX_PATH_SIZE);
      result[stackSize++] = BELOW(curr);
      continue;
    }
    // clang-format on

    stackSize--;
  }

  return 0;
}
