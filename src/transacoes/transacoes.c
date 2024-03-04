
Transacao  parseia_transacao(CwebHttpRequest *request){

    Transacao criada = {0};
    char *content = (char*)CwebHttpRequest_read_content(request,MAXIMO_BODY);
    if(!content){
        criada.resposta_de_erro =  cweb_send_text(BODY_NAO_INFORMADO,MAL_FORMATADO);
        return criada;
    }
    UniversalGarbage  *garbage = newUniversalGarbage();
    CHash *body = CHash_load_from_json_strimg(content);
    UniversalGarbage_add(garbage, CHash_free,body);

    //validando tipos
    criada.descricao = CHashObject_getString(body,DESCRICAO);
    criada.valor = (long)CHashObject_getNumber(body,VALOR);

    double valor_fracionado = CHashObject_getNumber(body,VALOR);
    char *tipo = CHashObject_getString(body,TIPO);

    CHash_catch(body){
        criada.resposta_de_erro =  cweb_send_text(BODY_NAO_INFORMADO,MAL_FORMATADO);
        UniversalGarbage_free(garbage);
        return criada;
    }


    if((double)criada.valor != valor_fracionado){
        criada.resposta_de_erro =cweb_send_text(VALOR_PRECISA_SER_INTEIRO,MAL_FORMATADO);
        UniversalGarbage_free(garbage);
        return criada;
    }


    int tamanho_descricao = strlen(criada.descricao);
    if(tamanho_descricao == 0 || tamanho_descricao > 10){
        criada.resposta_de_erro= cweb_send_text(DESCRICAO_COM_TAMANHO_INVALIDO,MAL_FORMATADO);
        UniversalGarbage_free(garbage);
        return criada;
    }
    if(strcmp(tipo,CODIGO_DEBITO_STR) == 0){
        criada.tipo = CODIGO_DEBITO;
    }
    if(strcmp(tipo,CODIGO_CREDITO_STR) == 0){
        criada.tipo = CODIGO_CREDITO;
    }

    if(!criada.tipo){
        criada.resposta_de_erro= cweb_send_text(TIPO_INVALIDO,MAL_FORMATADO);
        UniversalGarbage_free(garbage);
        return criada;
    }
    UniversalGarbage_free(garbage);
    return criada;
}

CwebHttpResponse  * gera_transacao(CwebHttpRequest *request,DtwResource *id_cliente){

    Transacao transacao = parseia_transacao(request);
    if(transacao.resposta_de_erro){
        return transacao.resposta_de_erro;
    }
    //isso é importante para evitar problemas de concorrência
    DtwResource_lock(id_cliente);

    
    return cweb_send_text("aaaaaaa",200);





}