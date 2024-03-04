


typedef struct {

    CwebHttpResponse *resposta_de_erro;
    char *descricao;
    long valor;
    short tipo;

}Transacao;


Transacao  parseia_transacao(CwebHttpRequest *request);


CwebHttpResponse  * gera_transacao(CwebHttpRequest *request,DtwResource *banco,DtwResource *id_cliente);
