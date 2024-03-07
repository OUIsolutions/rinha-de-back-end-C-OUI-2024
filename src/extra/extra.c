



struct timeval retorna_microsegundos() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv;
}