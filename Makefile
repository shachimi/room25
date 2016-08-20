BIN=room25
OBJS=src/main.o src/room/room.o src/room/room_effect.o src/room/cell.o       \
src/room/board.o src/game/game.o src/game/action.o src/game/move.o           \
src/game/slide.o src/game/see.o src/game/push.o src/room/deadly-room.o       \
src/player/player.o src/player/human_player.o src/player/term-player.o       \
src/room/acid-room.o src/room/torture-room.o src/room/flooding-room.o        \
src/player/avatar.o src/player/prisoner.o src/player/robot.o                 \
src/game/scheduling.o src/utils/Log.o

LIBS=
CFLAGS=-Werror -Wextra -Wall

all: $(BIN)


%.o: %.c
	g++ -g -c $^ -Isrc -o $@

%.o: %.cpp
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
