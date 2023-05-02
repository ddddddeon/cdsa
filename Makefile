NAME=cdsa
LIBS=
CFLAGS=-g -Wall $(LIBS) #-DDEBUG

CC=clang
OUTFILE=bin/$(NAME)
INFILES=$(wildcard src/*.c)

$(NAME):
	set -e; \
	rm src/*~ src/\#* 2>/dev/null || true; \
	if [ ! -d bin ]; then mkdir bin; fi; \
	$(CC) -static -o $(OUTFILE) $(INFILES) $(CFLAGS)

clean:	findBin
	@rm -rf bin;

findBin:
	@[ -d bin ];

install:
	@mv bin/$(NAME) /usr/bin/$(NAME); \
	chmod a+x /usr/bin/$(NAME); \
	echo "[OK] installed to /usr/bin/$(NAME)";

check:
	@valgrind --tool=memcheck --leak-check=full --show-reachable=yes --num-callers=20 --track-fds=yes ./bin/$(NAME)

trace:
	@strace ./bin/$(NAME)

all: $(NAME) findBin install

rebuild: clean $(NAME) install
