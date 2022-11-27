all:
	gcc -o myshell myshell.c
	gcc -o writef writef.c
	gcc -o execx execx.c
clean:
	rm myshell
	rm writef
	rm execx
	