

void plotar_request_corrente(CwebHttpRequest *request){

#ifndef  OBSERVAR
    return ;
#endif

        UniversalGarbage  *garbage = newUniversalGarbage();
        cJSON  * data = cJSON_CreateObject();
        UniversalGarbage_add(garbage, cJSON_Delete,data);
        cJSON_AddStringToObject(data,"rota",request->route);
        if(request->content_length){
            unsigned  char *content = CwebHttpRequest_read_content(request,200);
            if(content){
                cJSON *parsed = cJSON_Parse((char*)content);
                if(parsed){
                    cJSON_AddItemToObject(data,"json_body",parsed);
                }
                else{
                    cJSON_AddStringToObject(data,"body",(char*)content);
                }
            }
        }
        char *result = cJSON_Print(data);
        UniversalGarbage_add_simple(garbage,result);

        CTextStack *path = newCTextStack_string_format(
                "requisicoes/%d/request.json",
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
    cJSON  * data = cJSON_CreateObject();
    UniversalGarbage_add(garbage, cJSON_Delete,data);
    cJSON_AddNumberToObject(data,"status",resposta->status_code);
    if(adiquiriu_a_luz){
        cJSON *adiquiriu = cJSON_CreateObject();
        cJSON_AddItemToObject(data,"luz_adiquirida",adiquiriu);
        cJSON_AddNumberToObject(adiquiriu,"segundos",momento_da_luz_adiquirida.tv_sec);
        cJSON_AddNumberToObject(adiquiriu,"nanosegundos",momento_da_luz_adiquirida.tv_usec);
    }
    if(liberou_a_luz){
        cJSON *liberou = cJSON_CreateObject();
        cJSON_AddItemToObject(data,"luz_liberada",liberou);
        cJSON_AddNumberToObject(liberou,"segundos",momento_da_luz_liberada.tv_sec);
        cJSON_AddNumberToObject(liberou,"nanosegundos",momento_da_luz_liberada.tv_usec);
    }


    if(resposta->content_length){
            char *resposta_formatada = (char*)malloc(resposta->content_length+2);
            UniversalGarbage_add_simple(garbage,resposta_formatada);
            memcpy(resposta_formatada,resposta->content,resposta->content_length);
            resposta_formatada[resposta->content_length] = '\0';
            cJSON *parsed = cJSON_Parse(resposta_formatada);
            if(parsed){
                    cJSON_AddItemToObject(data,"json_body",parsed);
            }
            if(!parsed){
                cJSON_AddStringToObject(data,"body",resposta_formatada);
            }
    }

    char *result = cJSON_Print(data);
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