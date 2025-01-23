#pragma once
#ifndef VWIN_H
#define VWIN_H

#include <ncurses.h>
#include <string.h>
#include <unistd.h>

void sCText(WINDOW *, const char *[], int);

void sWPage();

void sLPage();

#endif
