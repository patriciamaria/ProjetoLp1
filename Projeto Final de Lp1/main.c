#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"

int main()
{
    FILE *arquivo = fopen ("arquivo_dados.txt", "r"); /// Abrir o arquivo de texto para a leitura.
    if(arquivo == NULL)
    {
        printf("Nao foi possivel abrir o arquivo!\n");
        return 0;
    }
    LerArquivo(arquivo);
    ContarContasCliente();
    CalcularSaldoContas();
    CalcularSaldoTotal();
    OrdenarClientesSaldo();
    OrdenarTransacoesData();
    OrdenarTransacoesCartaoData();
    ControleMenu();
    fclose(arquivo);
    return 0;
}
