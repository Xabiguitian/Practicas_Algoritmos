all: monticulo.c p4.c
	gcc -Wall monticulo.c p4.c -lm
	./a.out

leaks:
	gcc -g -O0 -Wall p4.c monticulo.c -lm
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes ./a.out