

void  escreve_chash_em_sub_resource(DtwResource *resource,CHash *data){
    UniversalGarbage  *garbage = newUniversalGarbage();
    cJSON *elemento = CHash_dump_to_cJSON(data);
    UniversalGarbage_add(garbage, cJSON_Delete,elemento);
#ifdef  DEBUG
    char *parsed = cJSON_Print(elemento);
#else
    char *parsed = cJSON_PrintUnformatted(elemento);
#endif
    UniversalGarbage_add_simple(garbage,parsed);
    DtwResource_set_string(resource,parsed);
    UniversalGarbage_free(garbage);
}

CwebHttpResponse * envia_erro_de_validacao_da_chash(CHash *elemento){
#ifdef  DEBUG
    char *message = CHash_get_error_menssage(elemento);
    CTextStack *messagem_formatada = newCTextStack_string_format(
            "erro de validacao do body:\n%s",
            message
            );
    char *menssagem_str = CTextStack_self_transform_in_string_and_self_clear(messagem_formatada);
    return cweb_send_text_cleaning_memory(menssagem_str,MAL_FORMATADO);
#else
    return cweb_send_text("",MAL_FORMATADO);
#endif
}