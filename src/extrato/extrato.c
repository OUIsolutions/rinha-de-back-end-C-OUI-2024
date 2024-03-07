

CwebHttpResponse  * gera_extrato(DtwResource *id_cliente){

    UniversalGarbage *garbage = newUniversalGarbage();
    DtwResource_lock(id_cliente);

    marcar_obtencao_da_luz();

    char * dados_str = resource.get_string_from_sub_resource(id_cliente,CAMINHO_DADOS);


    CxpathJson  *dados = xpath.new_from_string(dados_str);
    UniversalGarbage_add(garbage, cJSON_Delete,dados);

    int saldo = xpath.get_int(dados,"[%d]",SALDO_INDEX);
    int limite = xpath.get_int(dados,"[%d]",LIMITE_INDEX);
    int total_transacoes  = xpath.get_int(dados,"[%d]",TOTAL_TRANSACOES_INDEX);
    int ultima_transacao =  xpath.get_int(dados,"[%d]",ULTIMA_TRANSACAO_INDEX);


    CxpathJson  *resposta = xpath.newJsonObject();
    UniversalGarbage_add(garbage,xpath.free,resposta);
    //marca para xpath que não é para ele limpar o cjson interno
    resposta->element_reference = true;

    xpath.set_int(resposta, saldo, "['%s','%s']", SALDO_CHAVE, TOTAL_CHAVE);
    xpath.set_int(resposta, limite, "['%s','%s']", SALDO_CHAVE, LIMITE_CHAVE);
    
    char *data_do_extrato = convert_inteiro_para_data_em_str(time(NULL));
    UniversalGarbage_add_simple(garbage,data_do_extrato);
    xpath.set_str(resposta,data_do_extrato,"['%s','%s']",SALDO_CHAVE,DATA_EXTRATO_CHAVE);


    DtwResource  *pasta_transacoes = resource.sub_resource(id_cliente,CAMINHO_TRANSACOES);
    char *realizada_em = NULL;
    UniversalGarbage_add_simple(garbage,realizada_em);


    CxpathJson *array_transacao = NULL;
    UniversalGarbage_add(garbage, xpath.free,array_transacao);

    for(int i =ultima_transacao; i >= (ultima_transacao+1) - total_transacoes; i--){

        char * texto_transacao = resource.get_string_from_sub_resource(pasta_transacoes,"%d",i);

        array_transacao = xpath.new_from_string(texto_transacao);
        UniversalGarbage_resset(garbage,array_transacao);


        int valor = xpath.get_int(array_transacao,"[%d]",VALOR_INDEX);
        long data = xpath.get_int(array_transacao,"[%d]",DATA_INDEX);
        char *descricao = xpath.get_str(array_transacao,"[%d]",DESCRICAO_INDEX);
        realizada_em = convert_inteiro_para_data_em_str(data);
        UniversalGarbage_resset(garbage,realizada_em);

        if(valor < 0){
            xpath.set_int(resposta,valor * -1, "['%s','$append' ,'%s']", ULTIMAS_TRANSACOES_CHAVE, VALOR_CHAVE);
            xpath.set_str(resposta,CODIGO_DEBITO_STR,"['%s',-1,'%s']",ULTIMAS_TRANSACOES_CHAVE,TIPO_CHAVE);
        }

        if(valor >=0){
            xpath.set_int(resposta,valor, "['%s','$append' ,'%s']", ULTIMAS_TRANSACOES_CHAVE, VALOR_CHAVE);
            xpath.set_str(resposta,CODIGO_CREDITO_STR,"['%s',-1,'%s']",ULTIMAS_TRANSACOES_CHAVE,TIPO_CHAVE);
        }
        xpath.set_str(resposta,descricao,"['%s',-1,'%s']",ULTIMAS_TRANSACOES_CHAVE,DESCRICAO_CHAVE);
        xpath.set_str(resposta,realizada_em,"['%s',-1,'%s']",ULTIMAS_TRANSACOES_CHAVE,REALIZADA_EM_CHAVE);
    }
    cJSON *resposta_em_cjson = resposta->element;
    UniversalGarbage_free(garbage);
    return cweb_send_cJSON_cleaning_memory(resposta_em_cjson,RETORNO_OK);

}
