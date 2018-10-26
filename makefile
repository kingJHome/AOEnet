maintest: main.c graph.c stack.c
	gcc -g $^ -o $@

main: main.c graph.c stack.c
	gcc -o $@ $^