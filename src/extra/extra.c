

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


struct timeval retorna_microsegundos() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv;
}