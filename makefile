shell379: shell379.o builtin.o utils.o
	gcc -o shell379 shell379.o builtin.o utils.o

shell379.o: shell379.c shell379.h builtin.c builtin.h utils.c utils.h
	gcc -c shell379.c builtin.c utils.c

builtin.o: builtin.c builtin.h utils.c utils.h
	gcc -c builtin.c utils.c

utils.o: utils.c utils.h
	gcc -c utils.c

clean:
	rm -rf *.o shell379