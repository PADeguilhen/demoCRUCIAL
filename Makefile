CC = clang
CFLAGS = -std=c99 -Wall -Wextra -pedantic -fsanitize=address,undefined,leak
LIBS = -lncurses -lpthread

OBJECTS = crossy.o display.o main.o
T = test.o crossy.o display.o

all: c-Rossy

run: c-Rossy
	@./c-Rossy

c-Rossy: $(OBJECTS)
	@$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $(OBJECTS) $(LIBS)

clean:
	@rm $(OBJECTS) c-Rossy

debug: c-Rossy
	./c-Rossy debug

test: $(T)
	@$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $(T) $(LIBS)