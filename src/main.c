


#include "dependencias/dependencias.h"
#include "declaration.h"
#include "definition.h"


CwebHttpResponse *main_sever(CwebHttpRequest *request ){
    struct  timeval inicio = retorna_data_atual();
    plotar_request_corrente(inicio,request);

#ifdef DEBUG
    //rota para avaliar se gerou algum tipo de memory leah
    if(strcmp(request->route,"/end") ==0){
        cweb_kill_single_process_server();
        return cweb_send_text("aplicação terminada",200);
    }
#endif
    Requisicao resposta = roda_servidor(request);
    plotar_resposta_corrente(resposta.resposta);
    plotar_meta_dados_corrente(inicio,&resposta);
    return  resposta.resposta;
}

int main(int argc, char *argv[]){
    int porta = PORTA_PADRAO;
    int total_processos = MAXIMO_REQUEST;
    bool proceso_unico = false;
    // para rodar via docker
    if(argc >= 2){
        sscanf(argv[1],"%d",&porta);
    }

    if(getenv(VARIAVEL_TOTAL_PROCESSOS)){
        sscanf(getenv(VARIAVEL_TOTAL_PROCESSOS),"%d",&total_processos);
    }
    if(getenv(PROCESSO_UNICO)){
        proceso_unico = true;
    }

    cria_namespaces();

    printf("porta escolhida: %d\n",porta);
    printf("total de proessos:%d\n",total_processos);
    printf("Alea jacta est\n");

    cria_clientes_inicias();

    dtw_remove_any("requisicoes");
    #ifdef DEBUG
        for(int i = 3000;i < 4000; i++){
            CwebServer server = newCwebSever(i, main_sever);
            server.single_process = true;

            if(!CwebServer_start(&server)){
                break;
            }

        }
    #else
            CwebServer server = newCwebSever(porta, main_sever);
            server.single_process = proceso_unico;
            server.max_queue = MAXIMO_FILA;
            server.max_requests =  total_processos;
            server.function_timeout = TIMEOUT_FUNCAO;
            server.client_timeout = TIMEOUT_CLIENTE;
             CwebServer_start(&server);
    #endif

    return 0;
}