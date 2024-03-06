

void plotar_request_corrente(CwebHttpRequest *request){
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
    UniversalGarbage  *garbage = newUniversalGarbage();
    cJSON  * data = cJSON_CreateObject();
    UniversalGarbage_add(garbage, cJSON_Delete,data);
    cJSON_AddNumberToObject(data,"status",resposta->status_code);
    if(resposta->content_length){
            char *readed_contnt = (char*)malloc(resposta->content_length);
            UniversalGarbage_add_simple(garbage,readed_contnt);
            memccpy(readed_contnt,resposta->content,sizeof (char),resposta->content_length);
            readed_contnt[resposta->content_length] = '\0';

            cJSON *parsed = cJSON_Parse(readed_contnt);
            if(parsed){
                cJSON_AddItemToObject(data,"json_body",parsed);
            }
            if(!parsed){
                cJSON_AddStringToObject(data,"body",readed_contnt);
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