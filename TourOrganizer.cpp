#pragma once

#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include "player.cpp"
#include "game.cpp"
#include "player.h"
#include "game.h"
#include <algorithm>

using namespace std;

struct PlayerInfo {
    Player *player;
    int points;

    PlayerInfo(Player *player): player(player), points(0) {}
};

struct TourOrganizer {
private:
    vector<PlayerInfo> players;

public:
    TourOrganizer() {}

    int countPlayers() { return players.size(); }

    void registerPlayer(Player *player) {
        PlayerInfo playerInfo(player);
        players.push_back(playerInfo);
        cout << "Register: " << player->getName() << '\n';
    }

    void startAndPlayTour() {
        for (int index = 0; index < players.size(); index++) {
            for (int jndex = 0; jndex < players.size(); jndex++) {
                if (index == jndex) continue;

                Player *player1 = players[index].player;
                Player *player2 = players[jndex].player;
                Game game(player1, player2);

                cout << "\n\nPlaying " << player1->getName() << "(x) and " << player2->getName() << "(o)\n";
                game.drawField();

                int result = 10;
                while (!game.isGameOver(&result)) {
                    for (int index = 0; index < 2; index++) cout << '\n';

                    game.nextTurn();
                    game.drawField();
                }

                if (result == 0) {
                    players[index].points += 1;
                    players[jndex].points += 1;
                } else if (result == 1) {
                    players[index].points += 3;
                } else if (result == -1) {
                    players[jndex].points += 3;
                }


                this_thread::sleep_for(chrono::seconds(2));
            }
        }
    }

    void printTourTable() {
        sort(players.begin(), players.end(), [](const PlayerInfo &p1, const PlayerInfo &p2) {
            return p1.points > p2.points;
        });

        cout << "Tour table\n";
        cout << "Name of player\tPoints\n";

        for (const PlayerInfo &info : players) {
            cout << info.player->getName() << "\t\t" << info.points << '\n';
        }
    }
};