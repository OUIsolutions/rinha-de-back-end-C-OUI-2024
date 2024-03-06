
void  bloqueia_em_fila(DtwResource  *target,struct timeval inicio,const char *filename){

    UniversalGarbage  *garbage = newUniversalGarbage();



    const int PID_INDEX = 0;
    const int SECOND_INDEX = 1;
    const int NANO_INDEX = 2;


    int proprio_pid = getpid();

    CTextStack * locker_descriptor_file = newCTextStack_string_format("%s.quue_locker",filename);
    UniversalGarbage_add(garbage, CTextStack_free, locker_descriptor_file);

    int pid_concoorente = 0;

    int total_suscess = 0;
    while (true){
        DtwResource_lock(target);

        if(total_suscess > 5){
            printf("soltou \n");
            UniversalGarbage_free(garbage);
            return;
        }

        pid_concoorente = dtw_load_long_file_content(locker_descriptor_file->rendered_text);


        //significa que somos os mais antigos e nenhum outro processo sobrescreveu
        //já que verificamos a partir do json que foi escrito
        if(pid_concoorente == proprio_pid){
            printf("esta bloqueado pela gente\n");

            total_suscess+=1;
            DtwResource_unlock(target);
            dorme_milisegundos(ESPERA_PELA_LUZ_MS);
            continue;
        }

        total_suscess = 0;
        //significa que o pid concorrente morreu
        if(pid_concoorente == -1){
            printf("pid concorrente morreu\n");
            dtw_write_long_file_content(locker_descriptor_file->rendered_text,proprio_pid);
            DtwResource_unlock(target);
            dorme_milisegundos(ESPERA_PELA_LUZ_MS);
            continue;
        }

        if(proprio_pid < pid_concoorente){
            printf("nosso pid é mais antigo\n");

            dtw_write_long_file_content(locker_descriptor_file->rendered_text,proprio_pid);
            DtwResource_unlock(target);
            dorme_milisegundos(ESPERA_PELA_LUZ_MS);
            continue;
        }
    }


}
