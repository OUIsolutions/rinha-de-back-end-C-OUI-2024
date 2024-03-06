

void escreve_transacao_no_disco(DtwResource *banco, DtwResource *id_cliente, cJSON *dados, int saldo,Transacao *transacao){

    UniversalGarbage  *garbage = newUniversalGarbage();

    //adicionando o novo saldo
    cJSON_ReplaceItemInArray(dados,SALDO_INDEX, cJSON_CreateNumber(saldo));


    //criando a transacao
    cJSON *json_transacao = cJSON_CreateArray();
    UniversalGarbage_add(garbage, cJSON_Delete,json_transacao);
    if(transacao->tipo == CODIGO_CREDITO){
        cJSON_AddItemToArray(json_transacao, cJSON_CreateNumber(transacao->valor));
    }
    if(transacao->tipo== CODIGO_DEBITO){
        cJSON_AddItemToArray(json_transacao, cJSON_CreateNumber(transacao->valor * -1));

    }
    cJSON_AddItemToArray(json_transacao, cJSON_CreateNumber(time(NULL)));
    cJSON_AddItemToArray(json_transacao, cJSON_CreateString(transacao->descricao));


    int id_transacao = 0;

    int total_transacoes  = cJSON_GetArrayItem(dados,TOTAL_TRANSACOES_INDEX)->valueint;
    int ultima_transacao = cJSON_GetArrayItem(dados,ULTIMA_TRANSACAO_INDEX)->valueint;

    if(total_transacoes > 0){
        id_transacao = ultima_transacao+1;
    }

    ultima_transacao  = id_transacao;
    total_transacoes+=1;

    DtwResource *resource_transacaos = resource.sub_resource(id_cliente,CAMINHO_TRANSACOES);


    if(total_transacoes  > MAXIMO_TRANSACOES){
        int primeiro = ultima_transacao - total_transacoes;
        DtwResource *transacao_mais_antiga = resource.sub_resource(resource_transacaos,"%d",primeiro);
        DtwResource_destroy(transacao_mais_antiga);
        total_transacoes-=1;
    }


    cJSON_ReplaceItemInArray(dados,TOTAL_TRANSACOES_INDEX, cJSON_CreateNumber(total_transacoes));
    cJSON_ReplaceItemInArray(dados,ULTIMA_TRANSACAO_INDEX, cJSON_CreateNumber(ultima_transacao));

    //definindo as resources
    char *json_transacao_str = cJSON_PrintUnformatted(json_transacao);
    UniversalGarbage_add_simple(garbage,json_transacao_str);


    char *dados_str = cJSON_PrintUnformatted(dados);
    UniversalGarbage_add_simple(garbage, dados_str);

    resource.set_string_in_sub_resource(resource_transacaos,json_transacao_str,"%d",id_transacao);
    resource.set_string_in_sub_resource(id_cliente, dados_str, CAMINHO_DADOS);
    resource.commit(banco);
    UniversalGarbage_free(garbage);

}