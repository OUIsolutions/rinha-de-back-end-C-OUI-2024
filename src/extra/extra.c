

char * convert_inteiro_para_data_em_str(long segundos,long nano_segundos){

    struct tm * timeinfo;
    timeinfo = localtime(&segundos);
    char time_string[100] = {0};
    strftime(time_string, 100, "%Y-%m-%dT%H:%M:%S", timeinfo);
    char *final = (char*)malloc(100);
    sprintf(final,"%s.%ld",time_string,nano_segundos);
    return final;
}


struct timeval retorna_microsegundos() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv;
}