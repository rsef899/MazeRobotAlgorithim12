#include "algo.h"
#include "defs.h"
#include <raylib.h>
#include <stddef.h>

#define GRID_SCALE 30
#define T(x) ((x)*GRID_SCALE)

static uint8_t map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

static uint8_t food_list[5][2] = {{1, 9}, {5, 5}, {7, 1}, {13, 5}, {9, 9}};

// Pre-declaration for functions defined later on
void visualise_map(uint8_t map[MAP_HEIGHT][MAP_WIDTH], int startx, int starty);
void draw_path(Point *path, int pathLength, int startx, int starty);

int main(int argc, char **argv) {

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(40 + MAP_WIDTH * GRID_SCALE, 40 + MAP_HEIGHT * GRID_SCALE,
             "Robot Visualiser - 301");

  const Point startPoint = (Point){.x = 1, .y = 1};
  const Point endPoint = (Point){.x = 17, .y = 13};

  Point path[MAX_PATH_SIZE];
  int pathLength = run_algo(map, startPoint, endPoint, path);

  // Event loop
  while (!WindowShouldClose()) {
    ClearBackground(BLACK);

    BeginDrawing();

    visualise_map(map, 20, 20);
    DrawCircle(T(startPoint.x) + 20 + GRID_SCALE / 2,
               T(startPoint.y) + 20 + GRID_SCALE / 2, 5, ORANGE);
    DrawCircle(T(endPoint.x) + 20 + GRID_SCALE / 2, T(endPoint.y) + 20 + GRID_SCALE / 2,
               5, GREEN);

    draw_path(path, pathLength, 20, 20);

    EndDrawing();
  }
}

void visualise_map(uint8_t map[MAP_HEIGHT][MAP_WIDTH], int sx, int sy) {
  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      if (map[y][x] == POINT_WALL)
        DrawRectangle(T(x) + sx, T(y) + sy, GRID_SCALE, GRID_SCALE, WHITE);
      else
        DrawRectangleLines(T(x) + sx, T(y) + sy, GRID_SCALE, GRID_SCALE, WHITE);
    }
  }
}

void draw_path(Point *path, int pathLength, int sx, int sy) {
  for (int i = 0; i < (pathLength - 1); i++) {
    Point curr = path[i];
    Point next = path[i + 1];

    DrawLine(T(curr.x) + sx + GRID_SCALE / 2, T(curr.y) + sy + GRID_SCALE / 2,
             T(next.x) + sx + GRID_SCALE / 2, T(next.y) + sy + GRID_SCALE / 2, RED);

    DrawCircle(T(curr.x) + sx + GRID_SCALE / 2, T(curr.y) + sy + GRID_SCALE / 2, 3,
               RED);
  }

  // If we have a non-zero length path, draw the
  // last circle
  if (pathLength > 0) {
    Point last = path[pathLength - 1];
    DrawCircle(T(last.x) + sx + GRID_SCALE / 2, T(last.y) + sy + GRID_SCALE / 2, 3,
               RED);
  }
}

uint8_t point_eq(Point a, Point b) { return a.x == b.x && a.y == b.y; }
