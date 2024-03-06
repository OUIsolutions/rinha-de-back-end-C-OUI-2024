
#include "dependencias/dependencias.h"
#include "globais.h"
#include "declaration.h"
#include "definition.h"

int total_process;
int creation_per_process;
const char *target = "a.txt";

void append_once(int num){


    DtwResource *r = new_DtwResource(target);
    bloqueia_em_fila(r,retorna_microsegundos(),"a.txt");
    char *result = DtwResource_get_string(r);
    CTextStack * formated = newCTextStack_string_format("%s%d => %d\n",result,num,getpid());
    DtwResource_set_string(r,formated->rendered_text);

    CTextStack_free(formated);
    DtwResource_commit(r);
    DtwResource_free(r);
}

int main(int argc, char *argv[]){


    total_process  = 30;
    creation_per_process = 1;

    dtw_remove_any(target);
    dtw_write_string_file_content(target,"");

    for(int i = 0; i < total_process; i ++){
                if(fork()==0){
                    append_once(i);
                    exit(0);
                }
        //printf("pegou aqui\n");

    }



    // Aguarda o término de todos os processos filhos

    for (int i = 0; i < total_process; i++) {
        int status;
        wait(&status);
    }



}