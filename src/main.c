#include "dependencias/dependencias.h"
#include "declaration.h"
#include "definition.h"


CwebHttpResponse *main_sever(CwebHttpRequest *request ){


    RotaParser rota_obj = parsear_rota(request->route);
    if(rota_obj.invalida){
        return cweb_send_text(ROTA_INVALIDA,MAL_FORMATADO);
    }
    UniversalGarbage  *garbage = newUniversalGarbage();
    DtwResource *banco = new_DtwResource(CAMINHO_BANCO);
    UniversalGarbage_add(garbage, DtwResource_free,banco);

    DtwResource *cliente = DtwResource_sub_resource(banco,rota_obj.id_cliente);
    if(DtwResource_type(cliente) == DTW_NOT_FOUND){
        UniversalGarbage_free(garbage);
        return cweb_send_text(CLIENTE_NAO_EXIST,NAO_ENCONTRADO);
    }
    CwebHttpResponse *resposta  = NULL;

    if(rota_obj.acao == ACAO_TRANSACAO){
        resposta = gera_transacao(request,cliente);
    }


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