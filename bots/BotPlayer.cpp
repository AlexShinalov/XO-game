#pragma once
#include "../common.hpp"
#include "../player.cpp"
#include <string>
#include <random>

using namespace std;

class BotPlayer: public Player {
private:
  string name;
public:
  BotPlayer() : name("BotPlayer") {}

  virtual string getName() override { return "Bot " + name; }
  virtual Turn makeTurn(X0 playerKind, const X0 **field) override {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distributon(0, 2);
    
    int x = distributon(gen);
    int y = distributon(gen);

    while (field[x][y] != undefined) {
      x = distributon(gen);
      y = distributon(gen);
    }
    return Turn(x, y);
  }
};