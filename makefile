all:
	clear
	gcc main.c ./src/Menu/menu.c ./src/GerenciadorProcessos/instrucao.c ./src/GerenciadorProcessos/gerenciadorProcessos.c ./src/ProcessoControle/processoControle.c ./src/Pipe/pipe.c ./src/ProcessoImpressao/processoImpressao.c ./src/EstruturasDeDados/fila.c ./src/EstruturasDeDados/lista.c -o main.exe
	./main.exe