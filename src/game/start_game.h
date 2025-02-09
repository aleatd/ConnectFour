#pragma once

#ifndef START_GAME_H
#define START_GAME_H

#include <limits.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "../main/main.h"

#define ROWS 6
#define COLUMNS 7
#define PLAYER 'X'
#define COMPUTER 'O'
#define EMPTY ' '

bool check_win(char [][COLUMNS], char);

void draw_grid(WINDOW*, char [][COLUMNS], int);

int drop_piece(char [][COLUMNS], int, char);

int evaluate_board(char [][COLUMNS]);

int find_best_move(char [][COLUMNS]);

bool is_full_board(char [][COLUMNS]);

void init_grid(char [][COLUMNS]);

int algorithm(char [][COLUMNS], int, int, int, int); //mini_max_algorithm

void start_game();

#endif
