BIN=room25
OBJS=src/board/room.o src/board/room_effect.o src/board/cell.o               \
src/board/board.o src/game/game.o src/game/config.o src/board/deadly-room.o  \
src/player/player.o src/player/human_player.o src/player/term-player.o       \
src/board/acid-room.o src/board/torture-room.o src/board/flooding-room.o     \
src/player/avatar.o src/player/prisoner.o src/player/robot.o                 \
src/game/scheduling.o src/utils/Log.o src/board/room-factory.o               \
src/game/standard-rule.o src/game/rule.o src/board/prison-room.o             \
src/board/fog-room.o src/board/freeze-room.o src/board/vortex-room.o         \
src/board/pivot-room.o src/board/gear-room.o src/utils/utils.o               \
src/board/warp-room.o src/board/illusion-room.o src/board/vision-room.o      \
src/board/tunnel-room.o src/game/game-client.o src/network/network.o         \
src/network/push.o src/network/move.o src/network/see.o src/network/slide.o  \
src/network/select-cell.o src/network/message-factory.o                      \
src/player/away-player.o src/network/use-action.o

LIBS=
CFLAGS=
CC=g++


all: $(BIN)

client: all

server: src/server.o
	$(CC) -g $(CFLAGS) $^ -Isrc -o $@

%.o: %.c
	$(CC) -g $(CFLAGS) -c $^ -Isrc -o $@

%.o: %.cc
	$(CC) -g $(CFLAGS) -c $^ -Isrc -o $@

$(BIN): $(OBJS) src/main.o
	$(CC) -g $(CFLAGS) $^ -Isrc -o $@

zchk: $(OBJS) src/check/z.o
	$(CC) -g $(CFLAGS) $^ -Isrc -o $@

check: zchk
	./zchk

clean:
	@find . -name '*.o' -delete -print
	@find . -name '*_flymake.*' -delete -print

.phony:
	clean check

make-doc:
	@(cd doc && doxygen conf_file)
