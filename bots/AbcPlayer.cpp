#include <string>
#include "../common.hpp"
#include "../player.cpp"

class AbcPlayer : public Player {
public:
    virtual string getName() {
        return "ABC player";
    }

    virtual Turn makeTurn(X0 playerKind, const X0** field) {

        if (isFirstMove(field) == 0) {
            return Turn(1, 1);
        }; if (isFirstMove(field) == 1) {
            if (field[1][1] != X0::undefined) {
                return makeCornerMove(field);
            } else return Turn(1, 1);
        }

        Turn winningMove = findWinningMove(playerKind, field);
        if (winningMove.x != -1 && winningMove.y != -1) {
            return winningMove;
        }

        Turn blockingMove = findBlockingMove(playerKind, field);
        if (blockingMove.x != -1 && blockingMove.y != -1) {
            return blockingMove;
        }

        for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (field[i][j] == X0::undefined) return Turn(i, j);
                }
            }
        }

private:
    int isFirstMove(const X0** field) {
        int count = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (field[i][j] != X0::undefined) {
                    count++;
                }
            }
        }
        return count;
    }

    Turn makeCornerMove(const X0** field) {
        if (field[0][0] == X0::undefined) {
            return Turn(0, 0);
        } else if (field[0][2] == X0::undefined) {
            return Turn(0, 2);
        } else if (field[2][0] == X0::undefined) {
            return Turn(2, 0);
        } else {
            return Turn(2, 2);
        }
    }

    Turn findWinningMove(X0 playerKind, const X0** field) {

        // Главная диагональ
        int countPlayerDiag = 0;
        int countEmptyDiag = 0;
        int emptyX = -1, emptyY = -1;
        for (int i = 0; i < 3; i++) {
            if (field[i][i] == playerKind) {
                countPlayerDiag++;
            } else if (field[i][i] == X0::undefined) {
                countEmptyDiag++;
                emptyX = i;
                emptyY = i;
            }
        }
        if (countPlayerDiag == 2 && countEmptyDiag == 1) {
            return Turn(emptyX, emptyY);
        }

        // Побочная диагональ
        countPlayerDiag = 0;
        countEmptyDiag = 0;
        emptyX = -1, emptyY = -1;
        for (int i = 0; i < 3; i++) {
            if (field[i][2 - i] == playerKind) {
                countPlayerDiag++;
            } else if (field[i][2 - i] == X0::undefined) {
                countEmptyDiag++;
                emptyX = i;
                emptyY = 2 - i;
            }
        }
        if (countPlayerDiag == 2 && countEmptyDiag == 1){
            return Turn(emptyX, emptyY);
        }

        // Строки
        for (int i = 0; i < 3; i++) {
            int countPlayerKind = 0;
            int countEmpty = 0;
            int emptyX = -1, emptyY = -1;
            for (int j = 0; j < 3; j++) {
                if (field[i][j] == playerKind) {
                    countPlayerKind++;
                } else if (field[i][j] == X0::undefined) {
                    countEmpty++;
                    emptyX = i;
                    emptyY = j;
                }
            }
            if (countPlayerKind == 2 && countEmpty == 1){
                return Turn(emptyX, emptyY);
            }
        }

        // Столбцы
        for (int j = 0; j < 3; j++) {
            int countPlayerKind = 0;
            int countEmpty = 0;
            int emptyX = -1, emptyY = -1;
            for (int i = 0; i < 3; i++) {
                if (field[i][j] == playerKind) {
                    countPlayerKind++;
                } else if (field[i][j] == X0::undefined) {
                    countEmpty++;
                    emptyX = i;
                    emptyY = j;
                }
            }
            if (countPlayerKind == 2 && countEmpty == 1) {
                return Turn(emptyX, emptyY);
            }
        }

        return Turn(-1, -1);
    };

    Turn findBlockingMove(X0 playerKind, const X0** field) {
        X0 opponentKind = (playerKind == X0::o) ? X0::x : X0::o;

        int countPlayerDiag = 0;
        int countEmptyDiag = 0;
        int emptyX = -1, emptyY = -1;
        for (int i = 0; i < 3; i++) {
            if (field[i][i] == opponentKind) {
                countPlayerDiag++;
            } else if (field[i][i] == X0::undefined) {
                countEmptyDiag++;
                emptyX = i;
                emptyY = i;
            }
        }
        if (countPlayerDiag == 2 && countEmptyDiag == 1) {
            return Turn(emptyX, emptyY);
        }

        countPlayerDiag = 0;
        countEmptyDiag = 0;
        emptyX = -1, emptyY = -1;
        for (int i = 0; i < 3; i++) {
            if (field[i][2 - i] == opponentKind) {
                countPlayerDiag++;
            } else if (field[i][2 - i] == X0::undefined) {
                countEmptyDiag++;
                emptyX = i;
                emptyY = 2 - i;
            }
        }
        if (countPlayerDiag == 2 && countEmptyDiag == 1) {
            return Turn(emptyX, emptyY);
        }

        for (int i = 0; i < 3; i++) {
            int countPlayerKind = 0;
            int countEmpty = 0;
            int emptyX = -1, emptyY = -1;
            for (int j = 0; j < 3; j++) {
                if (field[i][j] == opponentKind) {
                    countPlayerKind++;
                } else if (field[i][j] == X0::undefined) {
                    countEmpty++;
                    emptyX = i;
                    emptyY = j;
                }
            }
            if (countPlayerKind == 2 && countEmpty == 1) {
                return Turn(emptyX, emptyY);
            }
        }

        for (int j = 0; j < 3; j++) {
            int countPlayerKind = 0;
            int countEmpty = 0;
            int emptyX = -1, emptyY = -1;
            for (int i = 0; i < 3; i++) {
                if (field[i][j] == opponentKind) {
                    countPlayerKind++;
                } else if (field[i][j] == X0::undefined) {
                    countEmpty++;
                    emptyX = i;
                    emptyY = j;
                }
            }
            if (countPlayerKind == 2 && countEmpty == 1) {
                return Turn(emptyX, emptyY);
            }
        }

        return Turn(-1, -1);
    }

};
