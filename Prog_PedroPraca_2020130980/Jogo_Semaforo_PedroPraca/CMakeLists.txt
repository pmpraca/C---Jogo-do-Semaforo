cmake_minimum_required(VERSION 3.23)
project(Jogo_Semaforo_PedroPraca C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Jogo_Semaforo_PedroPraca
        exame_ex1_2019/main.c
        main.c
        semaforo.c
        semaforo.h
        utils.c
        utils.h)
