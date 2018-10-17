/// Estrutura para os Clientes.
typedef struct Cliente
{
    int id_cliente;
    char nome[100];
    char cpf[20];
    char telefone[25];
    char municipio[100];
    char estado[10];
    int qtde_contas;
    double saldo_total;
    struct Cliente *proximo;
} Cliente;

/// Estrutura para as Contas.
typedef struct Conta
{
    int id_conta;
    int numero_conta;
    int variacao;
    int id_cliente;
    double saldo;
    struct Conta *proximo;
} Conta;

/// Estrutura para as Operações .
typedef struct Operacao
{
    int id_operacao;
    char nome[100];
    struct Operacao *proximo;
} Operacao;

/// Estrutura para as Transações .
typedef struct Transacoes
{
    int dia;
    int mes;
    int ano;
    int id_operacao;
    int id_conta_origem;
    int id_conta_destino;
    double valor;
    char descricao_t[100];
    struct Transacoes *proximo;
} Transacoes;

/// Estrutura para as Transações de Cartão de Crédito.
typedef struct Transacoes_cartao_credito
{
    int dia_c;
    int mes_c;
    int ano_c;
    int id_conta;
    char descricao[150];
    int qtde_parcelas;
    double valor_c;
    struct Transacoes_cartao_credito *proximo;
} Transacoes_cartao_credito;
