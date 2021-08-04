CC = gcc

.PHONY: clean

serv-clin: serv-clin.c
	$(CC) -o '$@' '$<'

clean:
	rm serv-clin
