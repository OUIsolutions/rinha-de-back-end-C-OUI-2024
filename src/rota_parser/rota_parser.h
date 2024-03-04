

typedef struct {
    bool  invalida;
    const char *id_cliente;
    short  acao;
} RotaParser;

RotaParser  parsear_rota(const char *rota);

