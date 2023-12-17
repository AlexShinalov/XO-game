#include <iostream>

/*
Мы проводим турнир по игре в крестики-нолики. Турнир проводится между ботами. Боты должны быть зарегистрировны для участия в турнире до его начала.
Каждый бот должен иметь имя и поддерживать протокол игры. В конце турнира распечатывается турнирная таблица, отсортированная по набранным очкам.

Турнир проводится как совокупность игр. Под "игрой" мы понимаем один рауд игры в Крестики-Колики между двумя различными участниками на поле размером 3x3.
За игру начисляются очки: 0 - за проигрыш, 1 - ничья, 3 - выигрыш.
В рамах турнира все участники играют друг с другом как за 'x' так и за '0'.

Правила игры:
 - если игрок совершает недопустимый ход (делает ход на занятое поле или вне его пределов) - он автоматически проигрывает, соперник получает 3 очка
 - если игрок складывает 3 в ряд - получает 3 очка
 - если игровое поле заполнено и ни один из игроков не выиграл - объявляется ничья и игроки получают по 1 очку.
  */

#include "TourOrganizer.cpp"
#include "player.cpp"
#include "bots/BotPlayer.cpp"
#include "bots/botVictor.cpp"
#include "bots/Makarova.cpp"
#include "bots/botNikolay.cpp"
#include "bots/AbcPlayer.cpp"



using namespace std;

int main() {
    TourOrganizer tour;

    tour.registerPlayer(new botNikolay());
    tour.registerPlayer(new BotPlayer());
    tour.registerPlayer(new Makarova());


    // for (int count = 0; count < 2; count++) {
    //   Player *bot = new BotPlayer(to_string(count));
    //   tour.registerPlayer(bot);
    // }

    tour.startAndPlayTour();
    tour.printTourTable();
}