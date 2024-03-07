

void plotar_request_corrente(CwebHttpRequest *request){

#ifndef  OBSERVAR
    return ;
#endif

        UniversalGarbage  *garbage = newUniversalGarbage();
        CxpathJson  * data = xpath.newJsonObject();
        UniversalGarbage_add(garbage, cJSON_Delete,data);
        xpath.set_str(data,request->route,"['rota']");

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

void plotar_resposta_corrente(int inicio,CwebHttpResponse *resposta){
#ifndef  OBSERVAR
    return ;
#endif
    UniversalGarbage  *garbage = newUniversalGarbage();
    CxpathJson  * data = xpath.newJsonObject();
    UniversalGarbage_add(garbage, cJSON_Delete,data);
    xpath.set_int(data,resposta->status_code,"['status']");
    xpath.set_int(data,inicio,"['inicio']");
    xpath.set_int(data, time(NULL),"['fim']");

    if(adiquiriu_a_luz){
        xpath.set_int(data,momento_da_luz_adiquirida.tv_sec,"['luz','adiquirida','segundos']");
        xpath.set_int(data,momento_da_luz_adiquirida.tv_usec,"['luz','adiquirida','nanosegundos']");
    }

    if(liberou_a_luz){
        xpath.set_int(data,momento_da_luz_liberada.tv_sec,"['luz','liberada','segundos']");
        xpath.set_int(data,momento_da_luz_liberada.tv_usec,"['luz','liberada','nanosegundos']");
    }


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

void marcar_obtencao_da_luz(){


#ifndef  OBSERVAR
    return ;
#endif
    adiquiriu_a_luz = true;
    momento_da_luz_adiquirida = retorna_microsegundos();
}

void  marcar_liberacao_da_luz(){

#ifndef  OBSERVAR
    return ;
#endif

    if(adiquiriu_a_luz){
        momento_da_luz_liberada = retorna_microsegundos();
        liberou_a_luz = true;
    }
}