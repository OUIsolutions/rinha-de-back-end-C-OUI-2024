
Transacao  parseia_transacao(CwebHttpRequest *request){

    Transacao criada = {0};
    cJSON *body = CWebHttpRequest_read_cJSON(request,MAXIMO_BODY);
    if(!body){
        criada.resposta_de_erro =  cweb_send_text(BODY_NAO_INFORMADO, INCONSISTENCIA);
        return criada;
    }

    if(!cJSON_IsObject(body)){
        criada.resposta_de_erro =  cweb_send_text(BODY_NAO_E_UM_OBJETO, INCONSISTENCIA);
        return criada;
    }
    //parseando descricao
    cJSON *json_descricao = cJSON_GetObjectItem(body, DESCRICAO_CHAVE);
    if(!json_descricao){
        criada.resposta_de_erro =  cweb_send_text(DESCRICAO_NAO_INFORMADA, INCONSISTENCIA);
        return criada;
    }

    if(!cJSON_IsString(json_descricao)){
        criada.resposta_de_erro =  cweb_send_text(DESCRICAO_NAO_E_UMA_STRING, INCONSISTENCIA);
        return criada;
    }

    int tamanho_descricao = strlen(json_descricao->valuestring);
    if(tamanho_descricao == 0 || tamanho_descricao > 10){
        criada.resposta_de_erro= cweb_send_text(DESCRICAO_COM_TAMANHO_INVALIDO, INCONSISTENCIA);
        return criada;
    }

    criada.descricao = json_descricao->valuestring;

    //parseando valor
    cJSON *json_valor = cJSON_GetObjectItem(body, VALOR_CHAVE);

    if(!json_valor){
        criada.resposta_de_erro =  cweb_send_text(VALOR_NAO_INFORMADO, INCONSISTENCIA);
        return criada;
    }
    if(!cJSON_IsNumber(json_valor)){
        criada.resposta_de_erro =  cweb_send_text(VALOR_PRECISA_SER_INTEIRO, INCONSISTENCIA);
        return criada;
    }

    if(json_valor->valuedouble != (double)json_valor->valueint){
        criada.resposta_de_erro =  cweb_send_text(VALOR_PRECISA_SER_INTEIRO, INCONSISTENCIA);
        return criada;
    }
    if(json_valor->valueint <0){
        criada.resposta_de_erro =  cweb_send_text(VALOR_PRECISA_SER_INTEIRO, INCONSISTENCIA);
        return criada;
    }

    criada.valor = json_valor->valueint;
    cJSON *json_tipo = cJSON_GetObjectItem(body, TIPO_CHAVE);
    if(!json_tipo){
        criada.resposta_de_erro =  cweb_send_text(TIPO_NAO_INFORMADO, INCONSISTENCIA);
        return criada;
    }
    if(!cJSON_IsString(json_tipo)){
        criada.resposta_de_erro =  cweb_send_text(TIPO_INVALIDO, INCONSISTENCIA);
        return criada;
    }

    if(strcmp(json_tipo->valuestring,CODIGO_DEBITO_STR) == 0){
        criada.tipo = CODIGO_DEBITO;
    }
    if(strcmp(json_tipo->valuestring,CODIGO_CREDITO_STR) == 0){
        criada.tipo = CODIGO_CREDITO;
    }
    if(!criada.tipo){
        criada.resposta_de_erro= cweb_send_text(TIPO_INVALIDO, INCONSISTENCIA);
        return criada;
    }
    return criada;
}
