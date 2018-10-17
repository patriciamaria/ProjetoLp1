#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#define MES_ATUAL 1
#define MES_ANTERIOR 2

Cliente *inicioC, *fimC; /// Ponteiro para o inicio e o final da estrutura cliente.
void AddCliente(Cliente *c)
{
    if(inicioC == NULL && fimC == NULL) /// Se o inicio e o final da lista de clientes forem nulos 'vazio'.
    {
        inicioC = c;
        fimC = c; /// Insere o primeiro cliente na lista.
    }
    else
    {
        fimC->proximo = c; /// Insere o cliente no final da lista.
        fimC = c;
    }
}

Conta *inicioCO, *fimCO; /// Ponteiro para o inicio e o final da estrutura conta.
void AddConta(Conta *co)
{
    if(inicioCO == NULL && fimCO == NULL) /// Se o inicio e o final da lista de contas forem nulos 'vazio'.
    {
        inicioCO = co;
        fimCO = co; /// Insere a primeira conta na lista.
    }
    else
    {
        fimCO->proximo = co; /// Insere a conta no final da lista.
        fimCO = co;
    }
}

Operacao *inicioOP, *fimOP; /// Ponteiro para o inicio e o final da estrutura operacao.
void AddOperacao(Operacao *op)
{
    if(inicioOP == NULL && fimOP == NULL) /// Se o inicio e o final da lista de operacoes forem nulos 'vazio'.
    {
        inicioOP = op;
        fimOP = op; /// Insere a primeira operacao na lista.
    }
    else
    {
        fimOP->proximo = op; /// Insere a operacao no final da lista.
        fimOP = op;
    }
}

Transacoes *inicioT, *fimT; /// Ponteiro para o inicio e o final da estrutura transacoes.
void AddTransacoes(Transacoes *t)
{
    if(inicioT == NULL && fimT == NULL) /// Se o inicio e o final da lista de transacoes forem nulos 'vazio'.
    {
        inicioT = t;
        fimT = t; /// Insere a primeira transacao na lista.
    }
    else
    {
        fimT->proximo = t; /// Insere a transacao no final da lista.
        fimT = t;
    }
}

Transacoes_cartao_credito *inicioTc, *fimTc; /// Ponteiro para o inicio e o final da estrutura transacoes_cartao_credito.
void AddTransacoes_Cartao_Credito(Transacoes_cartao_credito *tc)
{
    if(inicioTc == NULL && fimTc == NULL) /// Se o inicio e o final da lista de transacoes_cartao_credito forem nulos 'vazio'.
    {
        inicioTc = tc;
        fimTc = tc; /// Insere a primeira transacao_cartao_credito na lista.
    }
    else
    {
        fimTc->proximo = tc; /// Insere a transacao_cartao_credito no final da lista.
        fimTc = tc;
    }
}

/// Funcao para ler o arquivo e inserir na lista.
/// Cada laco executa enquanto estiver no formato especifico.
void LerArquivo(FILE *arquivo)
{
    /// Alocando as listas.
    Cliente *c = (Cliente *) malloc(sizeof(Cliente));
    Conta *co = (Conta *) malloc(sizeof(Conta));
    Operacao *op = (Operacao *) malloc(sizeof(Operacao));
    Transacoes *t = (Transacoes *) malloc(sizeof(Transacoes));
    Transacoes_cartao_credito *tc = (Transacoes_cartao_credito *) malloc(sizeof(Transacoes_cartao_credito));
    fscanf(arquivo, "*cliente*\n"); /// Ler o arquivo enquanto for de cliente.
    while(fscanf(arquivo, "%d, %[^,], %[^,], %[^,], %[^,], %[^;];\n", &c->id_cliente, c->nome, c->cpf, c->telefone, c->municipio, c->estado))
    {
        c->qtde_contas = 0;
        c->saldo_total = 0;
        c->proximo = NULL;
        AddCliente(c); /// Adiciona o cliente lido na lista de clientes.
        c = (Cliente *) malloc(sizeof(Cliente)); /// Alocacao de espaco para um novo cliente.
    }
    fscanf(arquivo, "\n*conta*\n"); /// Ler o arquivo enquanto for de conta.
    while(fscanf(arquivo, "%d, %d, %d, %d;\n", &co->id_conta, &co->numero_conta, &co->variacao, &co->id_cliente))
    {
        co->saldo = 0;
        co->proximo = NULL;
        AddConta(co); /// Adiciona a conta lida na lista de contas.
        co = (Conta *) malloc(sizeof(Conta)); /// Alocacao de espaco para uma nova conta.
    }
    fscanf(arquivo, "\n*operacao*\n"); /// Ler o arquivo enquanto for de operacao.
    while(fscanf(arquivo, "%d, %[^;];\n", &op->id_operacao, op->nome))
    {
        op->proximo = NULL;
        AddOperacao(op); /// Adiciona a operacao lida na lista de operacoes.
        op = (Operacao *) malloc(sizeof(Operacao)); /// Alocacao de espaco para uma nova operacao.
    }
    fscanf(arquivo, "\n*transacoes*\n"); /// Ler o arquivo enquanto for de transacoes.
    while(fscanf(arquivo, "%d/%d/%d, %d, %d, %d, %lf;\n", &t->dia, &t->mes, &t->ano,
            &t->id_operacao, &t->id_conta_origem, &t->id_conta_destino, &t->valor)) {
        Operacao *operacao = inicioOP;
        while(operacao != NULL) {
            if(operacao->id_operacao == t->id_operacao)
                strcpy(t->descricao_t, operacao->nome);
            operacao = operacao->proximo;
        }
        t->proximo = NULL;
        AddTransacoes(t); /// Adiciona a transacao lida na lista de transacoes.
        t = (Transacoes *) malloc(sizeof(Transacoes)); /// Alocacao de espaco para uma nova transacao.
    }
    fscanf(arquivo, "\n*transacoes_cartao_credito*\n"); /// Ler o arquivo enquanto for de transacoes_cartao_credito.
    while(fscanf(arquivo, "%d/%d/%d, %d, %[^,], %d, %lf;\n", &tc->dia_c, &tc->mes_c, &tc->ano_c,
            &tc->id_conta, tc->descricao, &tc->qtde_parcelas, &tc->valor_c) != EOF) {
        tc->proximo = NULL;
        AddTransacoes_Cartao_Credito(tc); /// Adiciona a transacao_cartao_credito lida na lista de transacoes_cartao_credito.
        tc = (Transacoes_cartao_credito *) malloc(sizeof(Transacoes_cartao_credito)); /// Alocacao de espaco para uma nova transacao_cartao_credito.
    }
}

/// Percorro as listas cliente e conta para contar a quantidade de contas que cada cliente possui.
void ContarContasCliente()
{
    Cliente *c = inicioC;
    while(c != NULL) {
        Conta *co = inicioCO;
        while(co != NULL) {
            if(c->id_cliente == co->id_cliente)
                c->qtde_contas = c->qtde_contas + 1; /// Contagem das contas dos clientes.
            co = co->proximo;
        }
        c = c->proximo;
    }
}

/// Percorro as listas conta e transacoes para calcular o saldo de cada conta do cliente.
void CalcularSaldoContas()
{
    Conta *co = inicioCO;
    while(co != NULL) {
        Transacoes *t = inicioT;
        while(t != NULL) {
            /// Operacoes que representam o tipo de transacao financeira que o cliente poderá realizar.
            if(t->id_operacao == 2 && co->id_conta == t->id_conta_destino) { /// 2-deposito.
                co->saldo += t->valor; /// Creditar o valor na conta destino.
            }
            else if(t->id_operacao == 3 && co->id_conta == t->id_conta_destino) { /// 3-transferencia.
                co->saldo += t->valor; /// Creditar na conta destino.
            }
            else if(t->id_operacao == 1 && co->id_conta == t->id_conta_origem) { /// 1-saque.
                co->saldo -= t->valor; /// Debitar o valor na conta origem.
            }
            else if(t->id_operacao == 3 && co->id_conta == t->id_conta_origem) { /// 3-transferencia.
                co->saldo -= t->valor; /// Debitar o valor na conta origem.
            }
            t = t->proximo;
        }
        co = co->proximo;
    }
}

/// Percorro as listas cliente e conta para calcular o saldo total de cada cliente.
void CalcularSaldoTotal()
{
    Cliente *c = inicioC;
    while(c != NULL) {
        Conta *co = inicioCO;
        while(co != NULL) {
            if(c->id_cliente == co->id_cliente)
                c->saldo_total += co->saldo; /// Calculando o saldo total de cada cliente.
            co = co->proximo;
        }
        c = c->proximo;
    }
}

/// Funcao para ordenar os clientes por saldo (bubble sort).
void OrdenarClientesSaldo()
{
    Cliente *cli1 = inicioC;
    int id_cliente, qtde_contas;
    double saldo_total;
    char nome[100], cpf[20], telefone[25], municipio[100], estado[10];
    while(cli1 != NULL) {
        Cliente *cli2 = inicioC;
        while(cli2 != NULL) {
            if(cli1->saldo_total > cli2->saldo_total) { /// Compara qual cliente tem o maior saldo.
                id_cliente = cli1->id_cliente;
                qtde_contas = cli1->qtde_contas;
                saldo_total = cli1->saldo_total;
                strcpy(nome, cli1->nome);
                strcpy(cpf, cli1->cpf);
                strcpy(telefone, cli1->telefone);
                strcpy(municipio, cli1->municipio);
                strcpy(estado, cli1->estado);

                cli1->id_cliente = cli2->id_cliente;
                cli1->qtde_contas = cli2->qtde_contas;
                cli1->saldo_total = cli2->saldo_total;
                strcpy(cli1->nome, cli2->nome);
                strcpy(cli1->cpf, cli2->cpf);
                strcpy(cli1->telefone, cli2->telefone);
                strcpy(cli1->municipio, cli2->municipio);
                strcpy(cli1->estado, cli2->estado);

                cli2->id_cliente = id_cliente;
                cli2->qtde_contas = qtde_contas;
                cli2->saldo_total = saldo_total;
                strcpy(cli2->nome, nome);
                strcpy(cli2->cpf, cpf);
                strcpy(cli2->telefone, telefone);
                strcpy(cli2->municipio, municipio);
                strcpy(cli2->estado, estado);
            }
            cli2 = cli2->proximo;
        }
        cli1 = cli1->proximo;
    }
}

/// Funcao para ordenar as transacoes por data (bubble sort).
void OrdenarTransacoesData()
{
    Transacoes *i = inicioT;
    int dia, mes, ano, id_operacao, id_conta_origem, id_conta_destino;
    double valor;
    char descricao_t[100];
    while(i != NULL) {
        Transacoes *j = inicioT;
        while(j != NULL) {
            if(i->ano < j->ano || i->ano == j->ano && i->mes < j->mes || i->ano == j->ano && i->mes == j->mes && i->dia < j->dia) {
            /// Se o ano for menor a data é menor.
            /// OU se o ano for igual e o mes for menor a data é menor.
            /// OU se o ano for igual e o mes for igual e o dia for menor a data é menor.
                dia = i->dia;
                mes = i->mes;
                ano = i->ano;
                id_operacao = i->id_operacao;
                id_conta_origem = i->id_conta_origem;
                id_conta_destino = i->id_conta_destino;
                valor = i->valor;
                strcpy(descricao_t, i->descricao_t);

                i->dia = j->dia;
                i->mes = j->mes;
                i->ano = j->ano;
                i->id_operacao = j->id_operacao;
                i->id_conta_origem = j->id_conta_origem;
                i->id_conta_destino = j->id_conta_destino;
                i->valor = j->valor;
                strcpy(i->descricao_t, j->descricao_t);

                j->dia = dia;
                j->mes = mes;
                j->ano = ano;
                j->id_operacao = id_operacao;
                j->id_conta_origem = id_conta_origem;
                j->id_conta_destino = id_conta_destino;
                j->valor = valor;
                strcpy(j->descricao_t, descricao_t);
            }
            j = j->proximo;
        }
        i = i->proximo;
    }
}

/// Funcao para ordenar as transacoes do cartao de credito por data (bubble sort).
void OrdenarTransacoesCartaoData()
{
    Transacoes_cartao_credito *a = inicioTc;
    int dia_c, mes_c, ano_c, id_conta, qtde_parcelas;
    char descricao[150];
    double valor_c;
    while(a != NULL) {
        Transacoes_cartao_credito *b = inicioTc;
        while(b != NULL) {
            if(a->ano_c < b->ano_c || a->ano_c == b->ano_c && a->mes_c < b->mes_c
               || a->ano_c == b->ano_c && a->mes_c == b->mes_c && a->dia_c < b->dia_c) {
            /// Se o ano for menor a data é menor.
            /// OU se o ano for igual e o mes for menor a data é menor.
            /// OU se o ano for igual e o mes for igual e o dia for menor a data é menor.
                dia_c = a->dia_c;
                mes_c = a->mes_c;
                ano_c = a->ano_c;
                id_conta = a->id_conta;
                qtde_parcelas = a->qtde_parcelas;
                valor_c = a->valor_c;
                strcpy(descricao, a->descricao);

                a->dia_c = b->dia_c;
                a->mes_c = b->mes_c;
                a->ano_c = b->ano_c;
                a->id_conta = b->id_conta;
                a->qtde_parcelas = b->qtde_parcelas;
                a->valor_c = b->valor_c;
                strcpy(a->descricao, b->descricao);

                b->dia_c = dia_c;
                b->mes_c = mes_c;
                b->ano_c = ano_c;
                b->id_conta = id_conta;
                b->qtde_parcelas = qtde_parcelas;
                b->valor_c = valor_c;
                strcpy(b->descricao, descricao);
            }
            b = b->proximo;
        }
        a = a->proximo;
    }
}

/// ******** FUNÇÕES DE EXIBIÇÃO. ********
void ExibirClientePorEstado()
{
    char estado[10];
    Cliente *c = inicioC;
    int qtde = 0;
    printf("Informe um Estado, apenas a SIGLA do estado: ");
    scanf("%s", estado);
    system("cls");
    while(c != NULL)
    {
        if(!strcmpi(c->estado, estado)) /// Compara o estado na lista de cliente com o estado informado.
        {
            printf("\n|Id do Cliente: %.3d, Nome: %s, CPF: %s, Telefone: %s, Municipio: %s, Quantidade de Contas: %d;\n",
                   c->id_cliente, c->nome, c->cpf, c->telefone, c->municipio, c->qtde_contas);
            qtde++;
        }
        c = c->proximo;
    }
    if (qtde == 0)
    {
        printf ("\nNao contem o estado informado!\n");
    }
    printf("\n");
    system("PAUSE");
}

void ExibirSaldoAtualCliente()
{
    char cpf[20];
    Cliente *c = inicioC;
    printf("Informe o CPF do cliente no formato xxx.xxx.xxx-xx: ");
    scanf("%s", cpf);
    system("cls");
    while(c != NULL) {
        if(!strcmpi(c->cpf, cpf)) { /// Compara o CPF na lista de cliente com o CPF informado.
            printf("\n|Nome do Cliente: %s, Saldo total: %.2lf R$.\n\n", c->nome, c->saldo_total);
            Conta *co = inicioCO;
            while(co != NULL) {
                if(c->id_cliente == co->id_cliente) {
                    printf("|Numero da conta: %d, Variacao: %.3d, Saldo da Conta: %.2lf R$;\n", co->numero_conta,
                           co->variacao, co->saldo);
                }
                co = co->proximo;
            }
        }
        c = c->proximo;
    }
    printf("\n");
    system("PAUSE");
}

void ExibirSaldoClientes()
{
    Cliente *c = inicioC;
    while(c != NULL)
    {
        printf("\n|Nome do Cliente: %s, CPF: %s, Saldo total das Contas: %.2lf;\n", c->nome, c->cpf, c->saldo_total);
        c = c->proximo;
    }
    printf("\n");
    system("PAUSE");
}

void ExibirExtratoBancario(int mes)
{
    struct tm * data_atual; /// Estrutura para armazenar a data atual.
    time_t tempo; ///Estrutura para pegar a data atual do sistema.
    char cpf[20];
    int numero_conta, ano;
    double saldo_atual = 0, saldo_anterior = 0;
    tempo = time(NULL); /// Iniciando o tempo.
    data_atual = localtime(&tempo); /// Pegando a data atual do sistema.
    ano = data_atual-> tm_year + 1900;
    Cliente * c = inicioC;
    printf("Informe o CPF do cliente no formato xxx.xxx.xxx-xx: ");
    scanf("%s", cpf);
    printf("Informe o numero da conta do cliente: ");
    scanf("%d", &numero_conta);
    if(mes == MES_ANTERIOR) {
        printf("Informe o mes/ano no formato xx/xxxx: "); /// Usuario informa o ano e mes desejado.
        scanf("%d/%d", &mes, &ano);
        system("cls");
        printf("===================================================================\n");
        printf("\t\tExtrato do Mes: %.2d de %d\n", mes, ano);
        printf("===================================================================\n\n");
    }
    else {
        mes = data_atual-> tm_mon + 1; /// Mes atual do sistema.
        system("cls");
        printf("===================================================================\n");
        printf("\t\tExtrato do Mes: %.2d de %d\n", mes, ano);
        printf("===================================================================\n\n");
    }
    while(c != NULL) { /// Percorre a lista de cliente para buscar o cliente que possui o CPF informado.
        if(!strcmpi(cpf, c->cpf)) /// Compara o CPF na lista de cliente com o CPF informado.
            break; /// Para quando encontrar o cliente.
        c = c->proximo; /// Se nao encontrar verifica o proximo cliente.
    }
    Transacoes * t = inicioT;
    while(t != NULL) {
        Conta * co = inicioCO;
        while(co != NULL) {
            /// Verifica quais contas pertence a atual transacao.
            if(t->id_conta_origem == co->id_conta || t->id_conta_destino == co->id_conta) {
                /// Verifica se a conta pertence ao cliente informado.
                if(co->id_cliente == c->id_cliente && co->numero_conta == numero_conta) {
                    /// Filtra todas as transacoes que menores ou iguais ao mes e ano atual.
                    if(t->ano < ano ||  t->ano == ano && t->mes <= mes) {
                        /// Se a operacao for deposito e o numero da conta é de destino creditar o valor.
                        if(t->id_operacao == 2 && co->id_conta == t->id_conta_destino) {
                            /// Filtra as transacoes realizadas no mes e ano atual.
                            if(t->mes == mes && t->ano == ano)
                                printf("|Data: %.2d/%.2d/%d, |Descricao: %s, |Valor: %.2lf R$\n", t->dia, t->mes,
                                    t->ano, t->descricao_t, t->valor);
                            saldo_atual += t->valor; /// Creditar o valor do deposito na conta do cliente.
                            /// As transacoes que nao sao do mes e ano atual representam o saldo anterior do cliente.
                            if(t->ano < ano || t->ano == ano && t->mes < mes)
                                saldo_anterior += t->valor; /// Creditar o valor do deposito na conta do cliente.
                        }
                        /// Se a operacao for transferencia e o numero da conta é de destino creditar o valor.
                        else if(t->id_operacao == 3 && co->id_conta == t->id_conta_destino) {
                            if(t->mes == mes && t->ano == ano)
                                printf("|Data: %.2d/%.2d/%d, |Descricao: %s, |Valor: %.2lf R$\n", t->dia, t->mes,
                                    t->ano, t->descricao_t, t->valor);
                            saldo_atual += t->valor; /// Creditar o valor da transferencia na conta do cliente.
                            if(t->ano < ano || t->ano == ano && t->mes < mes)
                                saldo_anterior += t->valor; /// Creditar o valor da transferencia na conta do cliente.
                        }
                        /// Se a operacao for saque e o numero da conta é de origem debitar o valor.
                        /// No extrato deve ser exibido o valor com sinal negativo.
                        else if(t->id_operacao == 1 && co->id_conta == t->id_conta_origem) {
                            /// Filtra as transacoes realizadas no mes e ano atual.
                            if(t->mes == mes && t->ano == ano)
                                printf("|Data: %.2d/%.2d/%d, |Descricao: %s, |Valor: -%.2lf R$\n", t->dia, t->mes,
                                    t->ano, t->descricao_t, t->valor);
                            saldo_atual -= t->valor; /// Debitar o valor do saque da conta do cliente.
                            /// As transacoes que nao sao do mes e ano atual representam o saldo anterior do cliente.
                            if(t->ano < ano || t->ano == ano && t->mes < mes)
                                saldo_anterior -= t->valor; /// Debitar o valor do saque da conta do cliente.
                        }
                        /// Se a operacao for transferencia e o numero da conta é de origem debitar o valor.
                        /// extrato deve ser exibido o valor com sinal negativo.
                        else if(t->id_operacao == 3 && co->id_conta == t->id_conta_origem) {
                            if(t->mes == mes && t->ano == ano)
                                printf("|Data: %.2d/%.2d/%d, |Descricao: %s, |Valor: -%.2lf R$\n", t->dia, t->mes,
                                    t->ano, t->descricao_t, t->valor);
                            saldo_atual -= t->valor; /// Debitar o valor da transferencia na conta do cliente.
                            if(t->ano < ano || t->ano == ano && t->mes < mes)
                                saldo_anterior -= t->valor; /// Debitar o valor da transferencia na conta do cliente.
                        }
                    }
                }
            }
            co = co->proximo;
        }
        t = t->proximo;
    }
    printf("\n");
    printf("===================================================================\n\n");
    printf("|Saldo Anterior: %.2lf R$;\n", saldo_anterior);
    printf("|Saldo Atual: %.2lf R$.\n\n", saldo_atual);
    printf("===================================================================\n\n");
    system("PAUSE");
}

void ExibirFaturaCartao()
{
    char nome_arquivo[150], cpf[20];
    double valor_minimo = 0, valor_total = 0;
    int mes, ano, parcela;
    Cliente *c = inicioC;
    printf("Informe o CPF do cliente no formato xxx.xxx.xxx-xx: ");
    scanf("%s", cpf);
    printf("Informe o mes/ano no formato xx/xxxx: ");
    scanf("%d/%d", &mes, &ano);
    system("cls");
    printf("=====================================================================\n");
    printf("\t\tFatura do Cartao: Mes %.2d de %d\n", mes, ano);
    printf("=====================================================================\n\n");
    strcpy(nome_arquivo, "Fatura do cliente ");
    while(c != NULL) {
        if(!strcmpi(cpf, c->cpf)) /// Filtro do CPF.
            break;
        c = c->proximo;
    }
    printf("|Nome do cliente: %s.\n", c->nome);
    strcat(nome_arquivo, c->nome);
    strcat(nome_arquivo, ".txt");
    FILE * arquivo = fopen(nome_arquivo, "w");
    fprintf(arquivo, "=====================================================================\n");
    fprintf(arquivo, "\t\tFatura do Cartao: Mes %.2d de %d\n", mes, ano);
    fprintf(arquivo, "=====================================================================\n\n");
    fprintf(arquivo, "|Nome do cliente: %s.\n", c->nome); /// Escreve no arquivo.
    Transacoes_cartao_credito * tc = inicioTc;
    while(tc != NULL) {
        Conta * co = inicioCO;
        while(co != NULL) {
            if(tc->id_conta == co->id_conta && co->id_cliente == c->id_cliente) {
                if(tc->ano_c < ano ||  tc->ano_c == ano && tc->mes_c < mes) {
                    parcela = (mes + (ano * 12)) - (tc->mes_c + (tc->ano_c * 12)); /// Calcula o numero da parcela.
                    if(parcela <= tc->qtde_parcelas) {
                        printf("|Data: %.2d/%.2d/%d, |Descricao: %s %d/%d, |Valor: %.2lf\n", tc->dia_c, tc->mes_c,
                            tc->ano_c, tc->descricao, parcela, tc->qtde_parcelas, tc->valor_c / tc->qtde_parcelas);
                        fprintf(arquivo, "|Data: %.2d/%.2d/%d, |Descricao: %s %d/%d, |Valor: %.2lf\n", tc->dia_c, tc->mes_c,
                            tc->ano_c, tc->descricao, parcela, tc->qtde_parcelas, tc->valor_c / tc->qtde_parcelas);
                        valor_total += tc->valor_c / tc->qtde_parcelas;
                    }
                }
            }
            co = co->proximo;
        }
        tc = tc->proximo;
    }
    valor_minimo = valor_total * 0.1; /// Valor minimo da fatura corresponde a 10% do valor total.
    printf("\n");
    printf("=====================================================================\n");
    printf("|Valor Minimo da fatura: %.2lf R$;\n", valor_minimo);
    printf("|Valor Total da fatura: %.2lf R$.\n", valor_total);
    printf("=====================================================================\n\n");
    fprintf(arquivo, "\n");
    fprintf(arquivo, "=====================================================================\n");
    fprintf(arquivo, "|Valor Minimo da fatura: %.2lf R$;\n", valor_minimo);
    fprintf(arquivo, "|Valor Total da fatura: %.2lf R$.\n", valor_total);
    fprintf(arquivo, "=====================================================================\n\n");
    system("PAUSE");
    fclose(arquivo);
}

void Menu()
{
    printf("\n\n");
    printf("\t\tSISTEMA DE CONTROLE DE OPERACOES FINANCEIRAS  \n\n\n");
    printf("( 1 ) LISTAGEM DE CLIENTES POR ESTADO.                \n");
    printf("( 2 ) SALDO ATUAL DO CLIENTE.                         \n");
    printf("( 3 ) LISTAGEM DO SALDO DOS CLIENTES.                 \n");
    printf("( 4 ) EXTRATO BANCARIO (MES ATUAL).                   \n");
    printf("( 5 ) EXTRATO BANCARIO (MES ANTERIOR).                \n");
    printf("( 6 ) FATURA DO CARTAO DE CREDITO.                    \n");
    printf("( 0 ) SAIR.                                         \n\n");
    printf("DIGITE O NUMERO DA OPCAO DESEJADA: ");
}

void ControleMenu()
{
    int menu;
    do {
        Menu();
        scanf("%d", &menu);
        system("cls");
        switch(menu) {
        case 1:
            ExibirClientePorEstado();
            printf("\n\n");
            break;
        case 2:
            ExibirSaldoAtualCliente();
            printf("\n\n");
            break;
        case 3:
            ExibirSaldoClientes();
            printf("\n\n");
            break;
        case 4:
            ExibirExtratoBancario(MES_ATUAL);
            printf("\n\n");
            break;
        case 5:
            ExibirExtratoBancario(MES_ANTERIOR);
            printf("\n\n");
            break;
        case 6:
            ExibirFaturaCartao();
            printf("\n\n");
            break;
        }
        system("cls");
    } while(menu != 0);
}
