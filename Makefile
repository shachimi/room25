BIN=room25
OBJS=src/main.o src/room/room.o src/room/room_effect.o src/room/cell.o       \
src/room/board.o src/player/player.o src/player/human_player.o               \
src/game/game.o src/game/action.o src/game/move.o

LIBS=
CFLAGS=-Werror -Wextra -Wall

all: $(BIN)


%.o: %.c
	g++ -g -c $^ -Isrc -o $@

%.o: %.cc
	g++ -g -c $^ -Isrc -o $@

$(BIN): $(OBJS)
	g++ -g $^ -o $@

clean:
	@find . -name '*.o' -delete -print
	@find . -name '*_flymake.*' -delete -print

.phony:
	clean
