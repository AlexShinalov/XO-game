
#pragma once

#include <string>
#include "../common.hpp"
#include "../player.cpp"
#include <random>
#include <time.h>

using namespace std;


class botNikolay : public Player {
public:
    virtual string getName() {
        return "botNikolay";
    }

    Turn makeTurn(X0 playerkind, const X0** field) override {
        int size = sizeof(field) / sizeof(X0*);
        Turn step_player(0, 0);
        int bestscore = -1000;

        for (int i = 0; i < size_field; ++i) {
            for (int j = 0; j < size_field; ++j) {
                if (field[i][j] == undefined) {
                    X0** board_for_minimax = add_board(size_field);
                    copy_board(board_for_minimax, field, size_field);
                    board_for_minimax[i][j] = playerkind;
                    int score = minimax(board_for_minimax, 0, false, playerkind);
                    if (score > bestscore) {
                        bestscore = score;
                        step_player = Turn(i, j);
                    }
                    delete_board(board_for_minimax, size_field);
                }
            }
        }
        return step_player;
    }

private:
    const int max_depth = 5;
    const int size_field = 3;
    X0** add_board(int size_field) {
        X0** board = new X0*[size_field];
        for (int i = 0; i < size_field; i++) {
            board[i] = new X0[size_field];
        }
        return board;
    }

    void delete_board(X0** board, int size) {
        for (int i = 0; i < size; i++) {
            delete[] board[i];
        }
        delete[] board;
    }

    void copy_board(X0** new_board, const X0** old_board, int size) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                new_board[i][j] = old_board[i][j];
            }
        }
    }



    int evaluate(X0** board, X0 playerkind) {
        // Проверка по горизонталям
        for (int i = 0; i < size_field; ++i) {
            if (board[i][0] == playerkind && board[i][1] == playerkind && board[i][2] == playerkind) {
                return 100;
            }
        }

        // Проверка по вертикалям
        for (int i = 0; i < size_field; ++i) {
            if (board[0][i] == playerkind && board[1][i] == playerkind && board[2][i] == playerkind) {
                return 100;
            }
        }

        // Проверка диагоналей
        if ((board[0][0] == playerkind && board[1][1] == playerkind && board[2][2] == playerkind) ||
            (board[0][2] == playerkind && board[1][1] == playerkind && board[2][0] == playerkind)) {
            return 100;
        }

        // Проверка на ничью
        bool is_draw = true;
        for (int i = 0; i < size_field; ++i) {
            for (int j = 0; j < size_field; ++j) {
                if (board[i][j] == undefined) {
                    is_draw = false; // Есть пустые клетки, игра не окончена
                    break;
                }
            }
        }
        if (is_draw) {
            return 0; // Ничья
        }


        return 50;
    }

    int minimax(X0** board, int depth, bool isMaximizing, X0 playerkind) {
        int score = evaluate(board, playerkind);

        if (score != 0 || depth >= max_depth) {
            return score;
        }

        if (isMaximizing) {
            int bestscore = -1000;
            for (int i = 0; i < size_field; ++i) {
                for (int j = 0; j < size_field; ++j) {
                    if (board[i][j] == undefined) {
                        board[i][j] = playerkind;
                        int current_score = minimax(board, depth + 1, false, playerkind);
                        board[i][j] = undefined;
                        bestscore = max(bestscore, current_score);
                    }
                }
            }
            return bestscore;
        } else {
            int bestscore = 1000;
            for (int i = 0; i < size_field; ++i) {
                for (int j = 0; j < size_field; ++j) {
                    if (board[i][j] == undefined) {
                        board[i][j] = (playerkind == x ? o : (playerkind == o ? x : undefined));
                        int current_score = minimax(board, depth + 1, true, playerkind);
                        board[i][j] = undefined;
                        bestscore = min(bestscore, current_score);
                    }
                }
            }
            return bestscore;
        }
    }

};