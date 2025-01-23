#include "vWin.h"

void sCText(WINDOW *win, const char *text[], const int lines) {
    /* Massimo di x, y */
    int mY, mX;
    getmaxyx(win, mY, mX);

    for (int i = 0; i < lines; i++) {
        const int length = strlen(text[i]);
        mvwprintw(win, (mY - lines) / 2 + i, (mX - length) / 2, "%s", text[i]);
    }

    wrefresh(win);
}

void sWPage() {
    clear();
    refresh();

    const char *message[] = {
        " __     __          __          ___       ",
        " \\ \\   / /          \\ \\        / (_)      ",
        "  \\ \\_/ /__  _   _   \\ \\  /\\  / / _ _ __  ",
        "   \\   / _ \\| | | |   \\ \\/  \\/ / | | '_ \\ ",
        "    | | (_) | |_| |    \\  /\\  /  | | | | |",
        "    |_|\\___/ \\__,_|     \\/  \\/   |_|_| |_|",
        "                                          "
    };

    int startY = (LINES - 7) / 2;
    int startX = (COLS - 42) / 2;

    for (int i = 0; i < 7; i++) {
        mvprintw(startY + i, startX, "%s", message[i]);
    }

    refresh();
    getch();  // Attende input per uscire dalla schermata
}

void sLPage() {
    clear();
    refresh();

    const char *message[] = {
        " __     __           _                    ",
        " \\ \\   / /          | |                   ",
        "  \\ \\_/ /__  _   _  | |     ___  ___  ___ ",
        "   \\   / _ \\| | | | | |    / _ \\/ __|/ _ \\",
        "    | | (_) | |_| | | |___| (_) \\__ \\  __/",
        "    |_|\\___/ \\__,_| |______\\___/|___/\\___|",
        "                                          "
    };

    int startY = (LINES - 7) / 2;
    int startX = (COLS - 42) / 2;

    for (int i = 0; i < 7; i++) {
        mvprintw(startY + i, startX, "%s", message[i]);
    }

    refresh();
    getch();  // Attende input per uscire dalla schermata
}
