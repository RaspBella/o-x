#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>

struct termios old, new;

char opts[9];
char board[9]; 
bool current_player = 1;
char winner = 0;
int move_count = 0;

void init_state(void) {
    // termios stuff
    tcgetattr(STDIN_FILENO, &old);
    new = old;
    new.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new);

    for (int i = 0; i < 9; i++) {
	opts[i] = i + '1';
    }

    memset(board, '-', 9);
}

void clear(void) {
    printf("\e[1;1H\e[2J");
}

void update_screen(void) {
    clear();

    printf("Current player: %c\n%c %c %c | %c %c %c\n%c %c %c | %c %c %c\n%c %c %c | %c %c %c\n", current_player ? 'o' : 'x', opts[0], opts[1], opts[2], board[0], board[1], board[2], opts[3], opts[4], opts[5], board[3], board[4], board[5], opts[6], opts[7], opts[8], board[6], board[7], board[8]);
}

char get_move(void) {
get_character:
    int input = getc(stdin);

    while (input < '1' || input > '9') goto get_character;

    while (opts[input - '1'] == '-') goto get_character;

    return input;
}

void play_move(char move) {
    opts[move - '1'] = '-';
    board[move - '1'] = (current_player ? 'o' : 'x');
}

void check(char move) {
    switch (move - '1') {
	case 0:
	    if (((board[0] == board[1]) && (board[0] == board[2])) ||
		((board[0] == board[4]) && (board[0] == board[8])) ||
		((board[0] == board[3]) && (board[0] == board[6]))) winner = board[0];
	    break;
	case 1:
	    if (((board[0] == board[1]) && (board[1] == board[2])) ||
		((board[1] == board[4]) && (board[1] == board[7]))) winner = board[1];
	    break;
	case 2:
	    if (((board[0] == board[2]) && (board[1] == board[2])) ||
		((board[2] == board[4]) && (board[2] == board[6])) ||
		((board[2] == board[5]) && (board[2] == board[8]))) winner = board[2];
	    break;
	case 3:
	    if (((board[0] == board[3]) && (board[5] == board[6])) ||
		((board[3] == board[4]) && (board[3] == board[5]))) winner = board[3];
	    break;
	case 4:
	    if (((board[0] == board[4]) && (board[4] == board[8])) ||
		((board[1] == board[4]) && (board[4] == board[7])) ||
		((board[2] == board[4]) && (board[4] == board[6])) ||
		((board[3] == board[4]) && (board[4] == board[5]))) winner = board[4];
	    break;
	case 5:
	    if (((board[2] == board[5]) && (board[5] == board[8])) ||
		((board[5] == board[3]) && (board[4] == board[5]))) winner = board[5];
	    break;
	case 6:
	    if (((board[6] == board[0]) && (board[3] == board[6])) ||
		((board[6] == board[2]) && (board[4] == board[6])) ||
		((board[6] == board[7]) && (board[6] == board[8]))) winner = board[6];
	    break;
	case 7:
	    if (((board[7] == board[1]) && (board[4] == board[7])) ||
		((board[6] == board[7]) && (board[7] == board[8]))) winner = board[7];
	    break;
	case 8:
	    if (((board[8] == board[0]) && (board[4] == board[8])) ||
		((board[8] == board[2]) && (board[5] == board[8])) ||
		((board[8] == board[6]) && (board[7] == board[8]))) winner = board[8];
	    break;
    }
}

void cleanup(void) {
    // termios
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
}

int main(void) {
    init_state();

    while (winner == 0 && move_count < 9) {
	update_screen();

	char move = get_move();
	play_move(move);

	update_screen();

	move_count++;

	check(move);

	current_player = !current_player;
    }

    if (winner == 0) {
	printf("The game was a draw\n");
    }
    else {
	printf("The winner was player of %c\n", winner);
    }

    cleanup();
}
