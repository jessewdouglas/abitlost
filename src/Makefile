P=abitlost
OBJECTS=main.o
CFLAGS=-std=c99 -g -Wall -Wextra -pedantic

$(P): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	$(RM) $(P) $(OBJECTS)
