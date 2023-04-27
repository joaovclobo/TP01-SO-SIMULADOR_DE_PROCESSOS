
typedef struct GerenciadorProcesso
{
    int tempo;
    Cpu cpu;
    TabelaDeProcessos arrTabelaProcessos;
    EstadoPronto filaEstadoPronto;
    EstadoBloqueado filaEstadoBloqueado;
    int filaEstadoExecucao;
} GerenciadorProcesso;