cmake_minimum_required(VERSION 3.28)
project(A2T2_3_4)

set(CMAKE_CXX_STANDARD 23)

add_executable(A2T2_3_4 main.cpp
        "BoardGame_Classes.h"
        Game3_Board.h
        Game3_Player.h
        Game6_Board.h
        Game6_Player.h
        Game7_Board.h
        Game7_Player.h
        Game8_Board.h
        Game8_Player.h
        PYRAMIC_XO.h
        wordTic_tac_toe.h
)
