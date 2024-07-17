#include <stdio.h>
#include <string.h>

char state[2][9];

void init_state(void) {
    for (int i = 0; i < 9; i++) {
	state[0][i] = i + '1';
    }

    memset(state[1], '-', 9);
}

void clear(void) {
    printf("\e[1;1H\e[2J");
}

void update_screen(void) {
    clear();

    printf("%c %c %c | %c %c %c\n%c %c %c | %c %c %c\n%c %c %c | %c %c %c\n", state[0][0], state[0][1], state[0][2], state[1][0], state[1][1], state[1][2], state[0][3], state[0][4], state[0][5], state[1][3], state[1][4], state[1][5], state[0][6], state[0][7], state[0][8], state[1][6], state[1][7], state[1][8]);
}

int main(void) {
    init_state();
    update_screen();
}
