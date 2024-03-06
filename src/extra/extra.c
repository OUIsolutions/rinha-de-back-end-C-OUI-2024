

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

int dorme_milisegundos(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

struct timeval retorna_microsegundos() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv;
}