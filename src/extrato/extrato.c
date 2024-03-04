

CwebHttpResponse  * gera_extrato(CwebHttpRequest *request,DtwResource *banco,DtwResource *id_cliente){
    DtwResource_lock(id_cliente);
    char * dados_str = DtwResource_get_string_from_sub_resource(id_cliente,CAMINHO_DADOS);


    UniversalGarbage *garbage = newUniversalGarbage();
    cJSON *dados = cJSON_Parse(dados_str);
    UniversalGarbage_add(garbage, cJSON_Delete,dados);

    int saldo = cJSON_GetArrayItem(dados,SALDO_INDEX)->valueint;
    int limite = cJSON_GetArrayItem(dados,LIMITE_INDEX)->valueint;
    cJSON *resposta = cJSON_CreateObject();
    cJSON *responsta_saldo = cJSON_CreateObject();
    cJSON *ultimas_transacoes = cJSON_CreateArray();

    cJSON_AddItemToObject(resposta,SALDO,responsta_saldo);
    cJSON_AddItemToObject(resposta,ULTIMAS_TRANSACOES,ultimas_transacoes);

    cJSON_AddNumberToObject(responsta_saldo,TOTAL,saldo);
    cJSON_AddNumberToObject(responsta_saldo,LIMITE,limite);

    char *data_do_extrato = convert_inteiro_para_data_em_str(time(NULL));
    UniversalGarbage_add_simple(garbage,data_do_extrato);
    cJSON_AddStringToObject(responsta_saldo,REALIZADA_EM,data_do_extrato);


    int total_transacoes  = cJSON_GetArrayItem(dados,TOTAL_TRANSACOES_INDEX)->valueint;
    int ultima_transacao = cJSON_GetArrayItem(dados,ULTIMA_TRANSACAO_INDEX)->valueint;

    DtwResource  *pasta_transacoes = DtwResource_sub_resource(id_cliente,CAMINHO_TRANSACOES);

    char *realizada_em = NULL;
    UniversalGarbage_add_simple(garbage,realizada_em);

    cJSON *array_transacao = NULL;
    UniversalGarbage_add(garbage, cJSON_Delete,array_transacao);
    for(int i =ultima_transacao; i >= (ultima_transacao+1) - total_transacoes; i--){

        char * texto_transacao = DtwResource_get_string_from_sub_resource(pasta_transacoes,"%d",i);

        array_transacao = cJSON_Parse(texto_transacao);
        UniversalGarbage_resset(garbage,array_transacao);

        int valor = cJSON_GetArrayItem(array_transacao,VALOR_INDEX)->valueint;
        long data = cJSON_GetArrayItem(array_transacao,DATA_INDEX)->valueint;
        char *descricao = cJSON_GetArrayItem(array_transacao,DESCRICAO_INDEX)->valuestring;
        realizada_em = convert_inteiro_para_data_em_str(data);
        UniversalGarbage_resset(garbage,realizada_em);


        cJSON  *objeto_transcao = cJSON_CreateObject();
        cJSON_AddItemToArray(ultimas_transacoes,objeto_transcao);


        if(valor < 0){
            cJSON_AddNumberToObject(objeto_transcao,VALOR,valor *-1);

            cJSON_AddStringToObject(objeto_transcao,TIPO, CODIGO_DEBITO_STR);
        }

        if(valor >=0){
            cJSON_AddNumberToObject(objeto_transcao,VALOR,valor );
            cJSON_AddStringToObject(objeto_transcao,TIPO, CODIGO_CREDITO_STR);
        }

        cJSON_AddStringToObject(objeto_transcao,DESCRICAO,descricao);
        cJSON_AddStringToObject(objeto_transcao,REALIZADA_EM,realizada_em);
    }
    UniversalGarbage_free(garbage);
    return cweb_send_cJSON_cleaning_memory(resposta,RETORNO_OK);

}
