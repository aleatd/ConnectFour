#include "show_state.h"

/* Centra il testo */
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

/* Visualizza 'hai vinto' */
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

    const int startY = (LINES - 7) / 2;
    const int startX = (COLS - 42) / 2;

    for (int i = 0; i < 7; i++) {
        mvprintw(startY + i, startX, "%s", message[i]);
    }

    refresh();
    getch();
}

/* Visualizza 'hai perso' */
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

    const int startY = (LINES - 7) / 2;
    const int startX = (COLS - 42) / 2;

    for (int i = 0; i < 7; i++) {
        mvprintw(startY + i, startX, "%s", message[i]);
    }

    refresh();
    getch();
}
