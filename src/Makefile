P=cjam2022
OBJECTS=main.o
CFLAGS=-std=c99 -g -Wall -Werror -pedantic

$(P): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	$(RM) $(P) $(OBJECTS)
