

//Dados
#ifdef DEBUG
#define SALDO_CHAVE_BANCO "saldo"
#define LIMITE_CHAVE_BANCO "limite"
#define  VALOR_CHAVE_BANCO "valor"
#define  TOTAL_TRANSACOES_CHAVE_BANCO "total_transacoes"
#define  ULTIMA_TRANSACAO_CHAVE_BANCO "ultima_transacao"
#define  DATA_CHAVE_BANCO "data"
#define  DESCRICCAO_CHAVE_BANCO "descricao"
#else

#define SALDO_CHAVE_BANCO "s"
#define LIMITE_CHAVE_BANCO "l"
#define  VALOR_CHAVE_BANCO "v"
#define  TOTAL_TRANSACOES_CHAVE_BANCO "t"
#define  ULTIMA_TRANSACAO_CHAVE_BANCO "i"
#define  DATA_CHAVE_BANCO "d"
#define  DESCRICCAO_CHAVE_BANCO "y"
#endif
