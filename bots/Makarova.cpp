#include "../common.hpp"
#include "../player.cpp"

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

class Makarova : public Player {
public:
    virtual string getName() override {
        return "Makarova ABC player";
    }

    virtual Turn makeTurn(X0 playerKind, const X0** field) override {
        int x = rand() % 3;
        int y = rand() % 3;

        return Turn(x, y);
    }
};
