

typedef struct {
    bool  invalida;
    const char *id_cliente;
    uint8_t  acao;
} RotaParser;

RotaParser  parsear_rota(const char *rota);

