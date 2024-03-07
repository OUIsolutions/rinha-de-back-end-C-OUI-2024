
Transacao  parseia_transacao(CwebHttpRequest *request){

    Transacao criada = {0};
    cJSON *cjson_body = CWebHttpRequest_read_cJSON(request,MAXIMO_BODY);

    if(!cjson_body){
        criada.resposta_de_erro =  cweb_send_text(BODY_NAO_INFORMADO, INCONSISTENCIA);
        return criada;
    }
    UniversalGarbage  *garbage = newUniversalGarbage();
    CxpathJson *body = xpath.new_from_cJSON_by_reference(cjson_body);
    UniversalGarbage_add(garbage,xpath.free,body);

    char *descricao = xpath.get_str(body,"['%s']",DESCRICAO_CHAVE);
    int valor_em_int  = xpath.get_int(body,"['%s']",VALOR_CHAVE);
    double valor_em_double = xpath.get_double(body,"['%s']",VALOR_CHAVE);
    char *tipo = xpath.get_str(body,"['%s']",TIPO_CHAVE);

    if(xpath.errors.has_errors(body)){
        #ifdef  DEBUG
            CTextStack *menssagem = stack.newStack_string_format(
                    "erro gerado: %s\n em %s\n",
                    xpath.errors.get_error_message(body),
                    xpath.errors.get_error_path(body)
                    );
            UniversalGarbage_add(garbage,stack.free,menssagem);

            criada.resposta_de_erro = cweb.response.send_text(menssagem->rendered_text,INCONSISTENCIA);
            UniversalGarbage_free(garbage);
            return  criada;
        #endif

        criada.resposta_de_erro = cweb.response.send_text("",INCONSISTENCIA);
        UniversalGarbage_free(garbage);
        return criada;
    }

    int tamanho_descricao = (int)strlen(descricao);
    if(tamanho_descricao == 0 || tamanho_descricao > 10){
        criada.resposta_de_erro= cweb_send_text(DESCRICAO_COM_TAMANHO_INVALIDO, INCONSISTENCIA);
        UniversalGarbage_free(garbage);
        return criada;
    }
    if(valor_em_int <0){
        criada.resposta_de_erro =  cweb_send_text(VALOR_PRECISA_SER_INTEIRO, INCONSISTENCIA);
        UniversalGarbage_free(garbage);
        return criada;
    }

    //verifica se não foi passado um double
    if(valor_em_double != (double)valor_em_int){
        criada.resposta_de_erro =  cweb_send_text(VALOR_PRECISA_SER_INTEIRO, INCONSISTENCIA);
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
        criada.resposta_de_erro= cweb_send_text(TIPO_INVALIDO, INCONSISTENCIA);
        UniversalGarbage_free(garbage);
        return criada;
    }

    UniversalGarbage_free(garbage);
    return criada;
}
