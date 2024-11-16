CFLAGS=-Wall -Wextra -pedantic
CC=cc
BIN=ox
SRC=main.c

${BIN}: ${SRC}
	${CC} ${CFLAGS} $^ -o $@

clean:
	rm ${BIN}
