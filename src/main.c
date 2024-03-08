


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



    cria_namespaces();


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
            CwebServer server = newCwebSever(PORTA_PADRAO, main_sever);
            server.max_queue = MAXIMO_FILA;
            server.max_requests =  MAXIMO_REQUEST;
            server.function_timeout = TIMEOUT_FUNCAO;
            server.client_timeout = TIMEOUT_CLIENTE;
             CwebServer_start(&server);
    #endif

    return 0;
}