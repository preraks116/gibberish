CC=gcc
all:
	$(CC) main.c -o gibberish
clean:
	rm gibberish
	rm history.txt
	touch history.txt