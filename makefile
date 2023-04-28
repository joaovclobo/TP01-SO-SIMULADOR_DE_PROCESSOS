all:
	clear
	gcc main.c ./src/Menu/menu.c ./src/GerenciadorProcessos/instrucao.c ./src/GerenciadorProcessos/gerenciadorProcessos.c ./src/ProcessoControle/processoControle.c ./src/Pipe/pipe.c -o main.exe
	./main.exe