cmake_minimum_required(VERSION 3.23)
project(XO)

set(CMAKE_CXX_STANDARD 14)

add_executable(XO main.cpp game.cpp player.cpp TourOrganizer.cpp TourOrganizer.h bots/botNikolay.cpp)
