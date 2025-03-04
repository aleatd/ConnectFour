#include "start_game.h"

/* Controlla se l'utente o la macchina hanno vinto */
bool check_win(char board[ROWS][COLUMNS], const char piece) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLUMNS; c++) {
            if (board[r][c] == piece) {
                /* Controllo orizzontale */
                if (c + 3 < COLUMNS &&
                    board[r][c + 1] == piece &&
                    board[r][c + 2] == piece &&
                    board[r][c + 3] == piece) {
                    return true;
                    }
                /* Controllo verticale */
                if (r + 3 < ROWS &&
                    board[r + 1][c] == piece &&
                    board[r + 2][c] == piece &&
                    board[r + 3][c] == piece) {
                    return true;
                    }
                /* Controllo diagonale */
                if (r + 3 < ROWS && c + 3 < COLUMNS &&
                    board[r + 1][c + 1] == piece &&
                    board[r + 2][c + 2] == piece &&
                    board[r + 3][c + 3] == piece) {
                    return true;
                    }
                /* Controllo diagonale */
                if (r - 3 >= 0 && c + 3 < COLUMNS &&
                    board[r - 1][c + 1] == piece &&
                    board[r - 2][c + 2] == piece &&
                    board[r - 3][c + 3] == piece) {
                    return true;
                    }
            }
        }
    }
    return false;
}

void draw_grid(WINDOW *window, char board[ROWS][COLUMNS], const int column) {
    const int sX = 2;
    const int sY = 2;

    /* Pulisce la finestra */
    werase(window);

    /* Disegna griglia */
    for (int i = 0; i < ROWS * 2 + 1; i++) {
        for (int j = 0; j < COLUMNS * 4 + 1; j++) {
            if (i % 2 == 0) {
                mvwaddch(window, sY + i, sX + j, (j % 4 == 0) ? ACS_PLUS : ACS_HLINE);
            } else if (j % 4 == 0) {
                mvwaddch(window, sY + i, sX + j, ACS_VLINE);
            }
        }
    }

    /* Disegna il contenuto delle celle */
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            mvwprintw(window, sY + i * 2 + 1, sX + j * 4 + 1, " %c ", board[i][j]);
        }
    }

    /* Mostra il cursore */
    mvwprintw(window, sY - 1, sX + column * 4, " v ");
    wrefresh(window);
}

/* Assegna il contenuto se non esiste */
int drop_piece(char board[ROWS][COLUMNS], const int column, const char piece) {
    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][column] == EMPTY) {
            board[i][column] = piece;
            return 1;
        }
    }
    return 0;
}

/* Valuta la griglia */
int evaluate_board(char board[][COLUMNS]) {
    if (check_win(board, PLAYER)) {
      return 1000;
    }

    if (check_win(board, COMPUTER)) {
      return -1000;
    }

    int score = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (board[i][j] == PLAYER) score++;
            else if (board[i][j] == COMPUTER) score--;
        }
    }
    return score;
}

int find_best_move(char board[][COLUMNS]) {
    int bestMove = -1, bestScore = INT_MIN;

    for (int i = 0; i < COLUMNS; i++) {
        /* Controlla se la colonna non è piena */
        if (board[0][i] == EMPTY) {
            /* Inserisce temporaneamente un contenuto */
            int rowPlayed = -1;
            for (int row = ROWS - 1; row >= 0; row--) {
                if (board[row][i] == EMPTY) {
                    board[row][i] = PLAYER;
                    rowPlayed = row;
                    break;
                }
            }

            if (rowPlayed != -1) {
                /* Valuta la mossa con Minimax */
                int score = algorithm(board, 5, INT_MIN, INT_MAX, 0);

                /* Ripristina la board dopo la valutazione */
                board[rowPlayed][i] = EMPTY;

                // Se il punteggio è migliore, aggiorna la mossa migliore
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = i;
                }
            }
        }
    }

    return bestMove;
}

/* Controlla se la griglia è piena */
bool is_full_board(char board[][COLUMNS]) {
    for (int j = 0; j < COLUMNS; j++) {
        if (board[0][j] == EMPTY) {
          return false;
        }
    }

    return true;
}

void init_grid(char board[][COLUMNS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            board[i][j] = EMPTY;
        }
    }
}

int max(const int f, const int s) {
    return f > s ? f : s;
}

int min(const int f, const int s) {
    return f < s ? f : s;
}

int algorithm(char board[][COLUMNS], const int depth, int alpha, int beta, const int mPlayer) {
    if (check_win(board, PLAYER)) {
        return 1000 - depth;  // Vittoria del giocatore
    }

    if (check_win(board, COMPUTER)) {
        return -1000 + depth;  // Vittoria del computer
    }

    if (depth == 0 || is_full_board(board)) {
        return evaluate_board(board);  // Valutazione della board se la profondità è zero
    }

    if (mPlayer) {  // Massimizzazione (giocatore)
        int hEvaluation = INT_MIN;
        for (int i = 0; i < COLUMNS; i++) {
            if (board[0][i] == EMPTY) {
                int rowPlayed = -1;
                for (int row = ROWS - 1; row >= 0; row--) {
                    if (board[row][i] == EMPTY) {
                        board[row][i] = PLAYER;
                        rowPlayed = row;
                        break;
                    }
                }

                if (rowPlayed != -1) {
                    int evaluation = algorithm(board, depth - 1, alpha, beta, 0);

                    board[rowPlayed][i] = EMPTY;

                    hEvaluation = max(hEvaluation, evaluation);
                    alpha = max(alpha, evaluation);

                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }
        return hEvaluation;
    }

    // Minimizzazione (computer)
    int lEvaluation = INT_MAX;
    for (int i = 0; i < COLUMNS; i++) {
        if (board[0][i] == EMPTY) {
            int rowPlayed = -1;
            for (int row = ROWS - 1; row >= 0; row--) {
                if (board[row][i] == EMPTY) {
                    board[row][i] = COMPUTER;
                    rowPlayed = row;
                    break;
                }
            }

            if (rowPlayed != -1) {
                int evaluation = algorithm(board, depth - 1, alpha, beta, 1);

                board[rowPlayed][i] = EMPTY;

                lEvaluation = min(lEvaluation, evaluation);
                beta = min(beta, evaluation);

                if (beta <= alpha) {
                    break;
                }
            }
        }
    }

    return lEvaluation;
}

void start_game() {
    char board[ROWS][COLUMNS];
    int cursor = 0, player = 1;

    initscr(); cbreak(); noecho();
    keypad(stdscr, TRUE); curs_set(0);
    srand(time(NULL));

    init_grid(board);
    WINDOW *gameWin = newwin(ROWS * 2 + 3, COLUMNS * 4 + 3, (LINES - (ROWS * 2 + 3)) / 2, (COLS - (COLUMNS * 4 + 3)) / 2);

    while (player != -1) {
        draw_grid(gameWin, board, cursor);

        if (player == 1) {
            int selected = getch();
            if (selected == KEY_LEFT) {
                cursor = cursor > 0 ? cursor - 1 : COLUMNS - 1;
            } else if (selected == KEY_RIGHT) {
                cursor = (cursor + 1) % COLUMNS;
            } else if (selected == '\n' && drop_piece(board, cursor, PLAYER)) {
                if (check_win(board, PLAYER)) {
                    delwin(gameWin);
                    endwin();
                    sWPage();
                    return;
                }
                player = 2;
            }
        } else {
            int column = find_best_move(board);
            drop_piece(board, column, COMPUTER);
            if (check_win(board, COMPUTER)) {
                delwin(gameWin);
                endwin();
                sLPage();
                return;
            }
            player = 1;
        }
    }

    delwin(gameWin);
    endwin();
}
