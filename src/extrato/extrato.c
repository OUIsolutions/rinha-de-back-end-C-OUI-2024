

CwebHttpResponse  * gera_extrato(void *requisicao,DtwResource *id_cliente){


    int inicio = time(NULL);
    while(resource.lock(id_cliente)){
        int agora = time(NULL);
        int duracao = agora - inicio;
        if(duracao > TIMEOUT_FUNCAO){
            //significa que deu merda e o cliente vai aborta
            return cweb_send_text("",ERRO_INTERNO);
        }
    }
    int agora = time(NULL);
    int duracao = agora - inicio;
    if(duracao > TIMEOUT_FUNCAO){
        //significa que deu merda e o cliente vai aborta
        return cweb_send_text("",ERRO_INTERNO);
    }

    UniversalGarbage *garbage = newUniversalGarbage();
    Requisicao  *requisicao_parseada = (Requisicao*)requisicao;
    requisicao_parseada->adiquiriu_o_bloqueio = true;
    requisicao_parseada->momento_do_bloqueio_adiquirido =retorna_data_atual();


    char * dados_str = resource.get_string_from_sub_resource(id_cliente,CAMINHO_DADOS);


    CxpathJson  *dados = xpath.new_from_string(dados_str);
    UniversalGarbage_add(garbage, cJSON_Delete,dados);

    int saldo = xpath.get_int(dados,"['%s']",SALDO_CHAVE_BANCO);
    int limite = xpath.get_int(dados,"['%s']",LIMITE_CHAVE_BANCO);
    int total_transacoes  = xpath.get_int(dados,"['%s']",TOTAL_TRANSACOES_CHAVE_BANCO);
    int ultima_transacao =  xpath.get_int(dados,"['%s']",ULTIMA_TRANSACAO_CHAVE_BANCO);


    CxpathJson  *resposta = xpath.newJsonObject();
    UniversalGarbage_add(garbage,xpath.free,resposta);
    //marca para xpath que não é para ele limpar o cjson interno
    resposta->element_reference = true;

    xpath.set_int(resposta, saldo, "['%s','%s']", SALDO_CHAVE, TOTAL_CHAVE);
    xpath.set_int(resposta, limite, "['%s','%s']", SALDO_CHAVE, LIMITE_CHAVE);

    //isso é importante, já que o que vale não é  o momento da requisicao
    // mas sim o momento que adiquirimos o bloqueio do cliente
    char *data_do_extrato = convert_inteiro_para_data_em_str(
            requisicao_parseada->momento_do_bloqueio_adiquirido.tv_sec,
            requisicao_parseada->momento_do_bloqueio_adiquirido.tv_usec
            );
    UniversalGarbage_add_simple(garbage,data_do_extrato);
    xpath.set_str(resposta,data_do_extrato,"['%s','%s']",SALDO_CHAVE,DATA_EXTRATO_CHAVE);


    DtwResource  *pasta_transacoes = resource.sub_resource(id_cliente,CAMINHO_TRANSACOES);
    char *realizada_em = NULL;
    UniversalGarbage_add_simple(garbage,realizada_em);


    CxpathJson *objeto_transacao = NULL;
    UniversalGarbage_add(garbage, xpath.free, objeto_transacao);

    for(int i =ultima_transacao; i >= (ultima_transacao+1) - total_transacoes; i--){

        char * texto_transacao = resource.get_string_from_sub_resource(pasta_transacoes,"%d",i);

        objeto_transacao = xpath.new_from_string(texto_transacao);
        UniversalGarbage_resset(garbage, objeto_transacao);


        int valor = xpath.get_int(objeto_transacao, "['%s']", VALOR_CHAVE_BANCO);
        long segundos = xpath.get_int(objeto_transacao, "['%s']", DATA_SEGUNDOS_CHAVE);
        long nano_segundos = xpath.get_int(objeto_transacao,"['%s']",DATA_NANO_SEGUNDOS_CHAVE);
        char *descricao = xpath.get_str(objeto_transacao, "['%s']", DESCRICCAO_CHAVE_BANCO);
        realizada_em = convert_inteiro_para_data_em_str(segundos,nano_segundos);
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
