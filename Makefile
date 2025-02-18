CC = clang
CFLAGS = -std=c99 -Wall -Wextra -pedantic
LIBS = -lncurses

OBJECTS = crossy.o display.o main.o

all: c-Rossy

run: c-Rossy
	@./c-Rossy

c-Rossy: $(OBJECTS)
	@$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $(OBJECTS) $(LIBS)

clean:
	@rm $(OBJECTS) c-Rossy
