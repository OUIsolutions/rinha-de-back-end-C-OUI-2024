
CwebHttpResponse  * gera_transacao(void *requisicao,CwebHttpRequest *request,DtwResource *banco,DtwResource *id_cliente){


    Transacao transacao = parseia_transacao(request);
    if(transacao.resposta_de_erro){
        return transacao.resposta_de_erro;
    }
    //isso é importante para evitar problemas de concorrência
    UniversalGarbage *garbage = newUniversalGarbage();
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
    
    Requisicao *requisicao_parseada = (Requisicao*)requisicao;
    requisicao_parseada->adiquiriu_o_bloqueio = true;
    requisicao_parseada->momento_do_bloqueio_adiquirido = retorna_data_atual();


    char * dados_str = resource.get_string_from_sub_resource(id_cliente,CAMINHO_DADOS);

    CxpathJson  *dados = xpath.new_from_string(dados_str);
    UniversalGarbage_add(garbage, xpath.free,dados);

    int saldo = xpath.get_int(dados,"['%s']",SALDO_CHAVE_BANCO);
    int limite = xpath.get_int(dados,"['%s']",LIMITE_CHAVE_BANCO);
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
    escreve_transacao_no_disco(banco, id_cliente, dados, saldo, &transacao,requisicao_parseada->momento_do_bloqueio_adiquirido);

    CxpathJson  *resposta =xpath.newJsonObject();
    UniversalGarbage_add(garbage,xpath.free,resposta);
    resposta->element_reference = true;
    xpath.set_int(resposta,saldo,"['%s']",SALDO_CHAVE);
    xpath.set_int(resposta,limite,"['%s']",LIMITE_CHAVE);
    cJSON *resposta_cjson = resposta->element;
    UniversalGarbage_free(garbage);
    return cweb_send_cJSON_cleaning_memory(resposta_cjson,RETORNO_OK);

}