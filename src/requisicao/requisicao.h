

typedef struct {

    CwebHttpResponse *resposta;
    bool adiquiriu_o_bloqueio;
    bool liberou_o_bloqueio;
    struct timeval momento_do_bloqueio_adiquirido;
    struct timeval momento_do_bloqueio_liberado;

}Requisicao;

Requisicao roda_servidor(CwebHttpRequest *request);