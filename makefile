all:
	clear
	gcc main.c ./src/Menu/menu.c ./src/GerenciadorProcessos/instrucao.c -o main.exe
	./main.exe