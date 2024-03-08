

void plotar_request_corrente(struct timeval inicio,CwebHttpRequest *request){

#ifndef  OBSERVAR
    return ;
#endif

        UniversalGarbage  *garbage = newUniversalGarbage();
        CxpathJson  * data = xpath.newJsonObject();
        UniversalGarbage_add(garbage, cJSON_Delete,data);
        xpath.set_str(data,request->route,"['rota']");
        xpath.set_int(data,inicio.tv_sec,"['inicio','segundos']");
        xpath.set_int(data,inicio.tv_usec,"['inicio','nanosegundos']");

        if(request->content_length){
            unsigned  char *content = CwebHttpRequest_read_content(request,200);
            if(content){
                cJSON *parsed = cJSON_Parse((char*)content);
                if(parsed){
                    xpath.set_cjson_getting_ownership(data,parsed,"['json_body']");
                }

                if(!parsed){
                    xpath.set_str(data,(char*)content,"['body']");
                }
            }
        }
        char *result = xpath.dump_to_string(data,true);
        UniversalGarbage_add_simple(garbage,result);

        CTextStack *path = stack.newStack_string_format(
                "requisicoes/%d/request.json",
                cweb_actual_request
                );

        UniversalGarbage_add(garbage, CTextStack_free,path);
    dtw_write_string_file_content(path->rendered_text,result);
    UniversalGarbage_free(garbage);

}
void plotar_meta_dados_corrente(struct  timeval inicio,void *requisicao){
#ifndef  OBSERVAR
    return ;
#endif
    Requisicao  *req = (Requisicao*)requisicao;
    UniversalGarbage  *garbage = newUniversalGarbage();
    CxpathJson  * data = xpath.newJsonObject();
    UniversalGarbage_add(garbage, cJSON_Delete,data);

    xpath.set_int(data,inicio.tv_sec,"['inicio','segundos']");
    xpath.set_int(data,inicio.tv_usec,"['inicio','nanosegundos']");

    struct timeval fim = retorna_data_atual();
    xpath.set_int(data,fim.tv_sec,"['fim','segundos']");
    xpath.set_int(data,fim.tv_usec,"['fim','nanosegundos']");

    if(req->adiquiriu_a_luz){
        xpath.set_int(data,req->momento_da_luz_adiquirida.tv_sec,"['luz','adiquirida','segundos']");
        xpath.set_int(data,req->momento_da_luz_adiquirida.tv_usec,"['luz','adiquirida','nanosegundos']");
    }

    if(req->liberou_a_luz){
        xpath.set_int(data,req->momento_da_luz_liberada.tv_sec,"['luz','liberada','segundos']");
        xpath.set_int(data,req->momento_da_luz_liberada.tv_usec,"['luz','liberada','nanosegundos']");
    }

    char *result = xpath.dump_to_string(data,true);
    UniversalGarbage_add_simple(garbage,result);

    CTextStack *path = newCTextStack_string_format(
            "requisicoes/%d/meta.json",
            cweb_actual_request
    );
    UniversalGarbage_add(garbage, CTextStack_free,path);
    dtw_write_string_file_content(path->rendered_text,result);
    UniversalGarbage_free(garbage);


}
void plotar_resposta_corrente(CwebHttpResponse *resposta){
#ifndef  OBSERVAR
    return ;
#endif
    UniversalGarbage  *garbage = newUniversalGarbage();
    CxpathJson  * data = xpath.newJsonObject();
    UniversalGarbage_add(garbage, cJSON_Delete,data);
    xpath.set_int(data,resposta->status_code,"['status']");



    if(resposta->content_length){
            char *resposta_formatada = (char*)malloc(resposta->content_length+2);
            UniversalGarbage_add_simple(garbage,resposta_formatada);
            memcpy(resposta_formatada,resposta->content,resposta->content_length);
            resposta_formatada[resposta->content_length] = '\0';
            cJSON *parsed = cJSON_Parse(resposta_formatada);
            if(parsed){
                    xpath.set_cjson_getting_ownership(data,parsed,"['json_body']");
            }
            if(!parsed){
                xpath.set_str(data,resposta_formatada,"['body']");
            }
    }

    char *result = xpath.dump_to_string(data,true);
    UniversalGarbage_add_simple(garbage,result);

    CTextStack *path = newCTextStack_string_format(
            "requisicoes/%d/resposta.json",
            cweb_actual_request
    );
    UniversalGarbage_add(garbage, CTextStack_free,path);
    dtw_write_string_file_content(path->rendered_text,result);
    UniversalGarbage_free(garbage);

}
