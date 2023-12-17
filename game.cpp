#pragma once

#include "common.hpp"
#include "player.cpp"
#include <iostream>
#include "game.h"

using namespace std;
class Game {
    Player *player_x;
    Player *player_0;
    X0 **field;
    int fieldSize;

    X0 lastMove;

public:
    X0 piece(int row, int col) {
        return field[row][col];
    }

    void drawField() {
        for (int index = 0; index < fieldSize; index++) {
            for (int jndex = 0; jndex < fieldSize; jndex++) {
                if (field[index][jndex] == X0::x) cout << "X ";
                else if (field[index][jndex] == X0::o) cout << "O ";
                else cout << "- ";
            }
            cout << '\n';
        }
    }

    int getResult() {
        int result = 10;
        isGameOver(&result);
        return result;
    }

    Game(Player *player_x, Player *player_0):
            Game(3, player_x, player_0)
    {}

    Game(int fieldSize, Player *player_x, Player *player_0) {
        field = new X0 *[fieldSize];
        for (int i=0; i<fieldSize; i++) {
            field[i] = new X0[fieldSize];
        }
        this->fieldSize = fieldSize;

        this->player_x = player_x;
        this->player_0 = player_0;

        lastMove = X0::undefined;
    }

    void nextTurn() {
        if (lastMove == X0::o || lastMove == X0::undefined) {
            Turn turn = player_x->makeTurn(X0::x, (const X0 **)field);
            // todo: check whether a cell is already occupied
            field[turn.x][turn.y] = X0::x;
            lastMove = X0::x;

            cout << player_x->getName() << ": " << turn.x << " " << turn.y << '\n';
        } else {
            Turn turn = player_0->makeTurn(X0::o, (const X0 **)field);
            // todo: check whether a cell is already occupied
            field[turn.x][turn.y] = X0::o;
            lastMove = X0::o;

            cout << player_0->getName() << ": " << turn.x << " " << turn.y << '\n';
        }
    }

    bool isGameOver(int *result = nullptr) {
        if (checkWin(X0::x)) {
            if (result != nullptr) *result = 1;
            return true;
        }
        else if (checkWin(X0::o)) {
            if (result != nullptr) *result = -1;
            return true;
        }

        for (int index = 0; index < fieldSize; index++) {
            for (int jndex = 0; jndex < fieldSize; jndex++) {
                if (field[index][jndex] == X0::undefined) {
                    if (result != nullptr) *result = 2;
                    return false;
                }
            }
        }

        if (result != nullptr) *result = 0;
        return true;
    }

    bool checkWin(X0 kindOf) {
        for (int index = 0; index < fieldSize; index++) {
            bool win = true;

            //horizontal
            for (int jndex = 0; jndex < fieldSize; jndex++) {
                if (field[index][jndex] != kindOf) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
            win = true;

            // vertical
            for (int jndex = 0; jndex < fieldSize; jndex++) {
                if (field[index][jndex] != kindOf) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
            win = true;
        }

        // left-to-right
        bool win = true;
        for (int index = 0; index < fieldSize; index++) {
            if (field[index][index] != kindOf) {
                win = false;
                break;
            }
        }
        if (win) return true;
        win = true;

        // right-to-left
        for (int index = 0; index < fieldSize; index++){
            if (field[index][fieldSize - index - 1] != kindOf) {
                win = false;
                break;
            }
        }
        return win;
    }

};