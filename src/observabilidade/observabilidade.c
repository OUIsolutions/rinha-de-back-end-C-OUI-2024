

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