BIN=room25
OBJS=src/main.o src/board/room.o src/board/room_effect.o src/board/cell.o       \
src/board/board.o src/game/game.o src/game/action.o src/game/move.o           \
src/game/slide.o src/game/see.o src/game/push.o src/board/deadly-room.o       \
src/player/player.o src/player/human_player.o src/player/term-player.o       \
src/board/acid-room.o src/board/torture-room.o src/board/flooding-room.o        \
src/player/avatar.o src/player/prisoner.o src/player/robot.o                 \
src/game/scheduling.o src/utils/Log.o

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

make-doc:
	@(cd doc && doxygen conf_file)
