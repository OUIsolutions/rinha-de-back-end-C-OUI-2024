
void  bloqueia_em_fila(DtwResource  *target,struct timeval inicio,const char *filename){

    UniversalGarbage  *garbage = newUniversalGarbage();



    const int PID_INDEX = 0;
    const int SECOND_INDEX = 1;
    const int NANO_INDEX = 2;

    cJSON *proprio_lock_descriptor = cJSON_CreateArray();
    UniversalGarbage_add(garbage, cJSON_Delete,proprio_lock_descriptor);

    int proprio_pid = getpid();
    cJSON_AddItemToArray(proprio_lock_descriptor, cJSON_CreateNumber(proprio_pid));
    cJSON_AddItemToArray(proprio_lock_descriptor, cJSON_CreateNumber(inicio.tv_sec));
    cJSON_AddItemToArray(proprio_lock_descriptor, cJSON_CreateNumber(inicio.tv_usec));

    char *locker_descriptor_file = dtw_concat_path(target->path,"locker");
    UniversalGarbage_add_simple(garbage,locker_descriptor_file);

    char *codigo_gerado = cJSON_PrintUnformatted(proprio_lock_descriptor);
    UniversalGarbage_add_simple(garbage,codigo_gerado);

    char *conteudo_lock_descriptor_concorrente = NULL;
    UniversalGarbage_add_simple(garbage,conteudo_lock_descriptor_concorrente);

    cJSON * json_lock_descriptor_concorrente  = NULL;
    UniversalGarbage_add(garbage, cJSON_Delete,json_lock_descriptor_concorrente);


    while (true){
        DtwResource_lock(target);

        conteudo_lock_descriptor_concorrente = dtw_load_string_file_content(locker_descriptor_file);
        UniversalGarbage_resset(garbage,conteudo_lock_descriptor_concorrente);


        if(!conteudo_lock_descriptor_concorrente){
            dtw_write_string_file_content(locker_descriptor_file,codigo_gerado);
            DtwResource_unlock(target);
            dorme_milisegundos(ESPERA_PELA_LUZ_MS);
            continue;
        }
        json_lock_descriptor_concorrente = cJSON_Parse(conteudo_lock_descriptor_concorrente);
        UniversalGarbage_resset(garbage,json_lock_descriptor_concorrente);

        if(!json_lock_descriptor_concorrente){
            dtw_write_string_file_content(locker_descriptor_file,codigo_gerado);
            DtwResource_unlock(target);
            dorme_milisegundos(ESPERA_PELA_LUZ_MS);
            continue;
        }

        int pid_concorrente = cJSON_GetArrayItem(json_lock_descriptor_concorrente,PID_INDEX)->valueint;
        //significa que somos os mais antigos e nenhum outro processo sobrescreveu
        //já que verificamos a partir do json que foi escrito
        if(pid_concorrente == proprio_pid){
            UniversalGarbage_free(garbage);
            return;
        }
        if(getpgid(pid_concorrente) < 0){
            dtw_write_string_file_content(locker_descriptor_file,codigo_gerado);
            DtwResource_unlock(target);
            dorme_milisegundos(ESPERA_PELA_LUZ_MS);
            continue;
        }

        long segundo_do_bloqueio_concorrente = cJSON_GetArrayItem(json_lock_descriptor_concorrente,SECOND_INDEX)->valueint;
        //significa que somos mais antigos então podemos roubar a luz e eseprar
        // para ver se alguém não roubou nossa luz
        if(inicio.tv_sec < segundo_do_bloqueio_concorrente  ){
            dtw_write_string_file_content(locker_descriptor_file,codigo_gerado);
            DtwResource_unlock(target);
            dorme_milisegundos(ESPERA_PELA_LUZ_MS);
            continue;
        }
        //sigifica que o concorrente é mais antigo então durmimos esperamos nossavez
        if(inicio.tv_sec > segundo_do_bloqueio_concorrente){
            DtwResource_unlock(target);
            dorme_milisegundos(ESPERA_PELA_LUZ_MS);
        }
        long concorrente_nano_segundos = cJSON_GetArrayItem(json_lock_descriptor_concorrente,NANO_INDEX)->valueint;

        //aqui iremos disputar os nanosegundos

        //significa que somos mais antigos então podemos roubar a luz e eseprar
        // para ver se alguém não roubou nossa luz
        if(inicio.tv_usec < concorrente_nano_segundos){
            dtw_write_string_file_content(locker_descriptor_file,codigo_gerado);
            DtwResource_unlock(target);
            dorme_milisegundos(ESPERA_PELA_LUZ_MS);
            continue;
        }
        //sigifica que o concorrente é mais antigo então durmimos esperamos nossavez

        if(inicio.tv_usec > concorrente_nano_segundos){
            DtwResource_unlock(target);
            dorme_milisegundos(ESPERA_PELA_LUZ_MS);
            continue;
        }


        //aqui é uma possibilidade hipotética,mas vou tentar cobrir
        //se tudo for igual, ganha o pid menor
        if(proprio_pid <= pid_concorrente){
            dtw_write_string_file_content(locker_descriptor_file,codigo_gerado);
            DtwResource_unlock(target);
            dorme_milisegundos(ESPERA_PELA_LUZ_MS);
            continue;
        }


    }


}
