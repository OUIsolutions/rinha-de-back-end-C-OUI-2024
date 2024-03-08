

typedef struct {

    CwebHttpResponse *resposta;
    bool adiquiriu_a_luz;

    struct timeval momento_da_luz_adiquirida;
    struct timeval momento_da_luz_liberada;

}Requisicao;

Requisicao roda_servidor(CwebHttpRequest *request);