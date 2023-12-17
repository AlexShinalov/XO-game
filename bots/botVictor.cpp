#pragma once

#include <string>
#include "../common.hpp"
#include "../player.cpp"
#include <random>
#include <time.h>

using namespace std;

class botVictor : public Player {
public:
  virtual string getName() {
    return "botVictor";
  }
  Turn makeTurn(X0 playerkind, const X0** field) override {
      int size_field = sizeof(field) / sizeof(X0*);
      Turn step_player(0, 0);
      int bestscore = -1000;

      for (int i = 0; i < size_field; ++i){
        for (int j = 0; j < size_field; ++j){
          if (!field[i][j]){
            X0** board_for_minimax = add_board(size_field);
            copy_board(board_for_minimax, field, size_field);
            board_for_minimax[i][j] = playerkind;
            int score = minimax(board_for_minimax, 0, false);
            if (score > bestscore) {
                bestscore = score;
                step_player = Turn(i, j);
            }
          }
        }
      }
    return step_player;
  }
private:
  X0** add_board(int size_field){
    X0** board = new X0* [size_field];;

    for (int i=0; i<size_field; i++) {
      board[i] = new X0[size_field];
    }
    return board;
  }
  void copy_board(X0** new_board, const X0** old_board, int size_field){
      for (int i = 0; i < size_field; ++i){
        for (int j = 0; j < size_field; ++j){
          new_board[i][j] = old_board[i][j];
        }
      }
  }
  int minimax(X0** board, int depth, bool isMaximizing) {
    return 0;
  }
};
