#include "dependencias/dependencias.h"
#include "declaration.h"
#include "definition.h"


CwebHttpResponse *main_sever(CwebHttpRequest *request ){


#ifdef DEBUG
    //rota para avaliar se gerou algum tipo de memory leah
    if(strcmp(request->route,"/end") ==0){
        cweb_kill_single_process_server();
        return cweb_send_text("aplicação terminada",200);
    }
#endif
    UniversalGarbage  *garbage = newUniversalGarbage();
    RotaParser rota_obj = parsear_rota(request->route);
    UniversalGarbage_add_simple(garbage,rota_obj.id_cliente);

    if(rota_obj.invalida){
        UniversalGarbage_free(garbage);
        return cweb_send_text(ROTA_INVALIDA, INCONSISTENCIA);
    }
    DtwResource *banco = new_DtwResource(CAMINHO_BANCO);
    UniversalGarbage_add(garbage, DtwResource_free,banco);

    DtwResource *cliente = DtwResource_sub_resource(banco,rota_obj.id_cliente);
    if(DtwResource_type(cliente) == DTW_NOT_FOUND){
        UniversalGarbage_free(garbage);
        return cweb_send_text(CLIENTE_NAO_EXIST,NAO_ENCONTRADO);
    }
    CwebHttpResponse *resposta  = NULL;

    if(rota_obj.acao == ACAO_TRANSACAO){
        resposta = gera_transacao(request,banco,cliente);
    }
    if(rota_obj.acao == ACAO_EXTRATO){
        resposta = gera_extrato(request,banco,cliente);
    }
    UniversalGarbage_free(garbage);
    return resposta;

}

int main(int argc, char *argv[]){
    cria_clientes_inicias();

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
            cweb.server.start(&server);
    #endif

    return 0;
}