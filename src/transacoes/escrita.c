

void escreve_transacao_no_disco(DtwResource *banco, DtwResource *id_cliente, cJSON *dados, int saldo, int valor){

    UniversalGarbage  *garbage = newUniversalGarbage();

    //adicionando o novo saldo
    cJSON_ReplaceItemInArray(dados,SALDO_INDEX, cJSON_CreateNumber(saldo));


    //criando a transacao
    cJSON *json_transacao = cJSON_CreateArray();
    UniversalGarbage_add(garbage, cJSON_Delete,json_transacao);
    cJSON_AddItemToArray(json_transacao, cJSON_CreateNumber(valor));
    cJSON_AddItemToArray(json_transacao, cJSON_CreateNumber(time(NULL)));


    int id_transacao = 0;
    cJSON *lista_transacoes = cJSON_GetArrayItem(dados,TRANSACOES_INDEX);

    int total_transacoes  = cJSON_GetArraySize(lista_transacoes);
    if(total_transacoes > 0){
        cJSON *ultima = cJSON_GetArrayItem(lista_transacoes,total_transacoes -1);
        id_transacao = ultima->valueint+1;
    }
    cJSON_AddItemToArray(lista_transacoes, cJSON_CreateNumber(id_transacao));


    //definindo as resources
    char *json_transacao_str = cJSON_PrintUnformatted(json_transacao);
    UniversalGarbage_add_simple(garbage,json_transacao_str);


    char *dados_str = cJSON_PrintUnformatted(dados);
    UniversalGarbage_add_simple(garbage, dados_str);

    DtwResource *resource_transacaos = DtwResource_sub_resource(id_cliente,CAMINHO_TRANSACOES);
    DtwResource_set_string_in_sub_resource(resource_transacaos,json_transacao_str,"%d",id_transacao);
    DtwResource_set_string_in_sub_resource(id_cliente, dados_str, CAMINHO_DADOS);
    DtwResource_commit(banco);
    UniversalGarbage_free(garbage);

}