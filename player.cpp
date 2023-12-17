#pragma once

#include <string>
#include "common.hpp"
#include "player.h"

using namespace std;

class Player {
public:
    virtual string getName() = 0;
    virtual Turn makeTurn(X0 playerKind, const X0** field) = 0;
};

class BasicPlayer : Player {
    virtual string getName() {
        return "Basic player";
    }

    virtual Turn makeTurn(X0 playerKind, const X0** field) {
        return Turn(0,0);
    }
};