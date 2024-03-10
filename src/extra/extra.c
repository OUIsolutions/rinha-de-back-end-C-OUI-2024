

char * convert_inteiro_para_data_em_str(long segundos,long nano_segundos){

    struct tm * timeinfo;
    timeinfo = localtime(&segundos);
    char time_string[100] = {0};
    strftime(time_string, 100, "%Y-%m-%dT%H:%M:%S", timeinfo);
    char *final = (char*)malloc(100);
    sprintf(final,"%s.%ld",time_string,nano_segundos);
    return final;
}

CwebHttpResponse  *realiza_bloqueio(DtwResource *id_cliente){
    int inicio = time(NULL);
    while(resource.lock(id_cliente));
    int agora = time(NULL);
    int duracao = agora - inicio;
    if(duracao > TOLERANCIA_BLOQUEIO){
        //significa que deu merda e o cliente vai aborta
        return cweb.response.send_text(ERRO_INTERNO_MESSAGEM,ERRO_INTERNO);

    }
    return NULL;
}
struct timeval retorna_data_atual() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv;
}