#pragma once

struct Turn {
  int x;
  int y;

  Turn(int x, int y): x(x), y(y) {}
};

enum X0 {
  x = 1,
  o = -1,
  undefined = 0
};