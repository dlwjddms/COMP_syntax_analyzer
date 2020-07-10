syntax_analyzer: main.o action.o input.o stack.o
	gcc -o syntax_analyzer main.o action.o input.o stack.o
	 
main.o: action.h input.h stack.h main.c
	gcc -c -o main.o main.c
			 
action.o: action.h action.c
	gcc -c -o action.o action.c
		 
input.o: input.h input.c
	gcc -c -o input.o input.c
			 
stack.o: stack.h stack.c
	 gcc -c -o stack.o stack.c

