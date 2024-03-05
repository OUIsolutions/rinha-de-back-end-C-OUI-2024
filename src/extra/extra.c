

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


DtwLocker  * bloqueia_x_vezes(char *target_lock){
    DtwLocker * locker = newDtwLocker();
    locker->total_checks = TOTAL_LOCK_CHECKS;
    locker->fail_delay = PUNICAO_DO_LOCKER;
    locker->max_wait = 1000000;
    locker->max_lock_time = MAX_LOCK_TIME;
    for(int i = 0; i < TOTAL_DE_BLOQUEADORES; i++){
        CTextStack *criado  = newCTextStack_string_format("%s%d",target_lock,locker);
        DtwLocker_lock(locker,criado->rendered_text);
        CTextStack_free(criado);
    }

    return locker;
}

