NAME=cdsa
CC=clang
LD=lld
LIBS=-lcheck -lpthread -lm -lrt -lsubunit -pthread
INCLUDES=
TEST_LIBS=-L./bin -l$(NAME)
USE_LINKER=-fuse-ld=$(LD)
CFLAGS=-g -Wall $(INCLUDES)
LIB_DIR=/usr/lib/
LIB_NAME=lib$(NAME).so
LIB_OUTFILE=bin/$(LIB_NAME)
INFILES=$(wildcard src/*.c)
HEADER_INFILES=$(wildcard src/*.h)
HEADER_OUTPATH=/usr/include/
TEST_INFILES=$(wildcard test/*.c)
TEST_OUTFILE=bin/test

.PHONY: $(NAME)
$(NAME): library
	set -e;\
	$(CC) -shared -o $(LIB_OUTFILE) $(wildcard bin/*.o); \
	$(CC) -o $(TEST_OUTFILE) $(TEST_INFILES) $(LIB_OUTFILE) $(CFLAGS) $(USE_LINKER) $(LIBS);

library:
	set -e; \
	if [ ! -d bin ]; then mkdir bin; fi; \
	for FILE in $(INFILES); do \
		$(CC) $(CFLAGS)-c -fPIC $$FILE -o bin/$$(basename $${FILE%%.*}).o;\
	done;

clean:	findBin
	@rm -rf bin;

findBin:
	@[ -d bin ];

install:
	@cp $(LIB_OUTFILE) $(LIB_DIR)$(LIB_NAME); \
	mkdir -p $(HEADER_OUTPATH)$(NAME); \
	for FILE in $(HEADER_INFILES); do \
		cp $$FILE $(HEADER_OUTPATH)$(NAME)/$$(basename $${FILE%%.*}.h); \
	done;

uninstall:
	rm $(LIB_DIR)$(LIB_NAME); \
	rm $(HEADER_OUTPATH)$(NAME).h;

.PHONY: test
test: $(NAME)
	bin/test;

check:
	@valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./bin/test;

trace:
	@strace ./bin/test

all: $(NAME) findBin install

rebuild: clean $(NAME) install
