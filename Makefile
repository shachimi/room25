BIN=room25
OBJS=src/board/room.o src/board/room_effect.o src/board/cell.o               \
src/board/board.o src/game/game.o src/game/config.o src/board/deadly-room.o  \
src/player/player.o src/player/term-player.o                                 \
src/board/acid-room.o src/board/torture-room.o src/board/flooding-room.o     \
src/player/avatar.o src/player/prisoner.o src/player/robot.o                 \
src/game/scheduling.o src/utils/Log.o src/board/room-factory.o               \
src/game/standard-rule.o src/game/rule.o src/board/prison-room.o             \
src/board/fog-room.o src/board/freeze-room.o src/board/vortex-room.o         \
src/board/pivot-room.o src/board/gear-room.o src/utils/utils.o               \
src/board/warp-room.o src/board/illusion-room.o src/board/vision-room.o      \
src/board/tunnel-room.o src/check/z_base.o
PRE_PROC=
LIBS=
CFLAGS=-Werror -Wextra -Wall

all: $(BIN)


%.o: %.c
	g++ $(PRE_PROC) -g -c $^ -Isrc -o $@

%.o: %.cc
	g++ $(PRE_PROC) -g -c $^ -Isrc -o $@

$(BIN): $(OBJS) src/main.o
	g++ -g $^ -Isrc -o $@

zchk: PRE_PROC=-D ZTEST_ON
zchk: $(OBJS) src/check/z.o
	g++ $(PRE_PROC) -g $^ -Isrc -o $@

check: zchk
	./zchk

tags:
	@ctags -e -o TAGS `find . -name '*.[hc][hc]'`

clean:
	@find . -name '*.o' -delete -print
	@find . -name '*_flymake.*' -delete -print

.phony:
	clean check tags

make-doc:
	@(cd doc && doxygen conf_file)
