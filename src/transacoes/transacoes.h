


typedef struct {

    CwebHttpResponse *resposta_de_erro;
    char *descricao;
    long valor;
    short tipo;

}Transacao;


Transacao  parseia_transacao(CwebHttpRequest *request);


CwebHttpResponse  * gera_transacao(void *requisicao,CwebHttpRequest *request,DtwResource *banco,DtwResource *id_cliente);

void escreve_transacao_no_disco(
        DtwResource *banco,
        DtwResource *id_cliente,
        CxpathJson *dados,
        int saldo,
        Transacao *transacao,
        struct  timeval  momento_da_luz_adiquirida
        );