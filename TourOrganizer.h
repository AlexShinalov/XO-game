#pragma once

#include "player.cpp"
#include "game.cpp"
#include "TourOrganizer.cpp"
using namespace std;


struct PlayerInfo {
    Player *player;
    int points;

    PlayerInfo(Player *player) : player(player), points(0) {}
};

class TourOrganizer {
private:
    std::vector<PlayerInfo> players;

public:
    TourOrganizer();

    int countPlayers();
    void registerPlayer(Player *player);
    void startAndPlayTour();
    void printTourTable();
};