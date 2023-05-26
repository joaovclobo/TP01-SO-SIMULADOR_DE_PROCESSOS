FilaPrioridade:
	clear
	gcc main.c ./src/Menu/menu.c ./src/ProcessoSimulado/instrucao.c ./src/ProcessoSimulado/processoSimulado.c ./src/GerenciadorProcessos/cpu.c ./src/GerenciadorProcessos/gerenciadorProcessos.c ./src/ProcessoControle/processoControle.c ./src/Pipe/pipe.c ./src/ProcessoImpressao/processoImpressao.c ./src/EstruturasDeDados/fila.c ./src/EstruturasDeDados/lista.c -o mainFilaPrioridade.exe
	./mainFilaPrioridade.exe 2

FilaSimples:
	clear
	gcc mainFS.c ./src/Menu/menu.c ./src/ProcessoSimulado/instrucao.c ./src/ProcessoSimulado/processoSimulado.c ./src/GerenciadorProcessos/cpuFS.c ./src/GerenciadorProcessos/gerenciadorProcessosFS.c ./src/ProcessoControle/processoControle.c ./src/Pipe/pipe.c ./src/ProcessoImpressao/processoImpressaoFS.c ./src/EstruturasDeDados/fila.c ./src/EstruturasDeDados/lista.c -o mainFilaSimples.exe
	./mainFilaSimples.exe 2 3