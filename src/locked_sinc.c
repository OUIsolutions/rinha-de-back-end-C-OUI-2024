
#include "dependencias/dependencias.h"
#include "globais.h"
#include "declaration.h"
#include "definition.h"

int total_process;
int creation_per_process;
const char *target = "a.txt";

void append_once(int num){

    DtwResource *target_r = new_DtwResource(target);
    DtwResource_lock(target_r);
   // printf("processo %d bloqueou\n",num);

    long size;
    bool is_binary;
    char *element = DtwResource_get_string()
    //printf("%s\n",element);
/*
    char *formated = (char*) calloc(30000,sizeof(char*));
    strcpy(formated,element);

    char current_num[20];
    sprintf(current_num,"%d\n",num);


    for(int x = 0; x < creation_per_process; x++){
        strcat(formated,current_num);
    }

    DtwResource_set_string(target_r,formated);
  */
    DtwResource_commit(target_r);
    DtwResource_free(target_r);
}

int main(int argc, char *argv[]){


    total_process  = 30;
    creation_per_process = 1;

    dtw_remove_any(target);
    dtw_write_string_file_content(target,"");

    for(int i = 0; i < total_process; i ++){


            append_once(i);
        //    exit(0);


    }



    // Aguarda o término de todos os processos filhos

    for (int i = 0; i < total_process; i++) {
        int status;
        wait(&status);
    }



}