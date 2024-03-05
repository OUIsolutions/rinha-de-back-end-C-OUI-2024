

void  escreve_chash_em_sub_resource(DtwResource *element,CHash *data);



char * convert_inteiro_para_data_em_str(long int unix_time){
    struct tm * timeinfo;
    timeinfo = localtime(&unix_time);
    char *time_string = (char *)malloc(100);
    strftime(time_string, 100, "%Y-%m-%dT%H:%M:%S", timeinfo);
    return time_string;
}
