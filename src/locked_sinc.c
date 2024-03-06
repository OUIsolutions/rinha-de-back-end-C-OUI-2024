
#include "dependencias/dependencias.h"
#include "globais.h"
#include "declaration.h"
#include "definition.h"

int total_process;
int creation_per_process;
const char *target = "a.txt";

void append_once(int num){

    DtwResource *r = new_DtwResource(target);
    while(DtwResource_lock(r));
    char *result = dtw_load_string_file_content(target);
    CTextStack * formated = newCTextStack_string_format("%s%d\n",result,num);
    printf("%s\n",formated->rendered_text);
    dtw_write_string_file_content(target,formated->rendered_text);
    free(result);
    CTextStack_free(formated);
    DtwResource_free(r);
    /*
    DtwLocker  *locker = newDtwLocker();
    DtwLocker_lock(locker,target);
    char *result = dtw_load_string_file_content(target);
    CTextStack * formated = newCTextStack_string_format("%s%d\n",result,num);
    printf("%s\n",formated->rendered_text);
    dtw_write_string_file_content(target,formated->rendered_text);
    free(result);
    CTextStack_free(formated);
    DtwLocker_free(locker);
    */
}

int main(int argc, char *argv[]){


    total_process  = 30;
    creation_per_process = 1;

    dtw_remove_any(target);
    dtw_write_string_file_content(target,"");

    for(int i = 0; i < total_process; i ++){
            if(fork() == 0){
                //printf("pegou aqui\n");
                append_once(i);
                exit(0);
            }
    }



    // Aguarda o término de todos os processos filhos

    for (int i = 0; i < total_process; i++) {
        int status;
        wait(&status);
    }



}