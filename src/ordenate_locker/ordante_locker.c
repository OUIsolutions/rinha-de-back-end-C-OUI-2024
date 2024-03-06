
void  bloqueia_em_fila(DtwResource  *target,struct timeval inicio,const char *filename){

    UniversalGarbage  *garbage = newUniversalGarbage();
    char *locker_descriptor_file = NULL;
    UniversalGarbage_add_simple(garbage,locker_descriptor_file);



    const int PID_INDEX = 0;
    const int SECOND_INDEX = 1;
    const int NANO_INDEX = 2;

    cJSON *proprio_lock_descriptor = cJSON_CreateArray();
    UniversalGarbage_add(garbage, cJSON_Delete,proprio_lock_descriptor);

    cJSON_AddItemToArray(proprio_lock_descriptor, cJSON_CreateNumber(getpid()));
    cJSON_AddItemToArray(proprio_lock_descriptor, cJSON_CreateNumber(inicio.tv_sec));
    cJSON_AddItemToArray(proprio_lock_descriptor, cJSON_CreateNumber(inicio.tv_usec));



    while (true){
        DtwResource_lock(target);

        locker_descriptor_file = dtw_concat_path(target->path,"locker");
        UniversalGarbage_resset(garbage,locker_descriptor_file);



        if(dtw_entity_type(locker_descriptor_file) == DTW_NOT_FOUND){

        }
        DtwResource_unlock(target);
    }


}
