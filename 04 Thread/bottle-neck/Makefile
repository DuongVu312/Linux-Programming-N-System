# Mutilple Thread

CC := gcc
CFLAGS := -pthread

all:
	$(CC) -o single-app single-thread.c $(CFLAGS)
	$(CC) -o multi-app multi-thread.c $(CFLAGS)

clean:
	rm -rf  multi-app single-app