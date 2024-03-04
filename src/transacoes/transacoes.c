
CwebHttpResponse  * gera_transacao(CwebHttpRequest *request,DtwResource *banco,DtwResource *id_cliente){

    Transacao transacao = parseia_transacao(request);
    if(transacao.resposta_de_erro){
        return transacao.resposta_de_erro;
    }
    //isso é importante para evitar problemas de concorrência

    DtwResource_lock(id_cliente);
    char * dados_str = DtwResource_get_string_from_sub_resource(id_cliente,CAMINHO_DADOS);


    UniversalGarbage *garbage = newUniversalGarbage();
    cJSON *dados = cJSON_Parse(dados_str);
    UniversalGarbage_add(garbage, cJSON_Delete,dados);

    int saldo = cJSON_GetArrayItem(dados,SALDO_INDEX)->valueint;
    int limite = cJSON_GetArrayItem(dados,LIMITE_INDEX)->valueint;
    int saldo_full = saldo+limite;

    if(transacao.tipo == CODIGO_DEBITO){
        saldo_full-=transacao.valor;
        saldo-=transacao.valor;
    }

    if(transacao.tipo == CODIGO_CREDITO){
        saldo+=transacao.valor;
    }

    if(saldo_full < 0){
        UniversalGarbage_free(garbage);
        return cweb_send_text(LIMITE_INDISPONIVEL,INCONSISTENCIA);
    }
    escreve_transacao_no_disco(banco, id_cliente, dados, saldo, transacao.valor,transacao.descricao);

    cJSON *resposta =cJSON_CreateObject();
    cJSON_AddNumberToObject(resposta,SALDO,saldo);
    cJSON_AddNumberToObject(resposta,LIMITE,limite);
    UniversalGarbage_free(garbage);
    return cweb_send_cJSON_cleaning_memory(resposta,RETORNO_OK);



}