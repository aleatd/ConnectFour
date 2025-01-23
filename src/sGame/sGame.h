#pragma once

#ifndef START_GAME_H
#define START_GAME_H

#include <limits.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "../main.h"

#define ROWS 6
#define COLUMNS 7
#define PLAYER 'X'
#define COMPUTER 'O'
#define EMPTY ' '

bool cWin(char [][COLUMNS], char);

void dGrid(WINDOW*, char [][COLUMNS], int);

int dPiece(char [][COLUMNS], int, char);

int eBoard(char [][COLUMNS]);

int fBestMove(char [][COLUMNS]);

bool cFullBoard(char [][COLUMNS]);

void iGame(char [][COLUMNS]);

int mMax(char [][COLUMNS], int, int, int, int);

void sGame();

#endif
