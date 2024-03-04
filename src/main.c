#include "dependencias/dependencias.h"
#include "declaration.h"
#include "definition.h"


CwebHttpResponse *main_sever(CwebHttpRequest *request ){


    RotaParser rota_obj = parsear_rota(request->route);
    if(rota_obj.invalida){
        return cweb.response.send_text(ROTA_INVALIDA,MAL_FORMATADO);
    }
    UniversalGarbage  *garbage = newUniversalGarbage();
    DtwResource *banco = resource.newResource(CAMINHO_BANCO);
    UniversalGarbage_add(garbage,resource.free,banco);

    DtwResource *cliente = resource.sub_resource(banco,rota_obj.id_cliente);
    if(resource.type(cliente) == DTW_NOT_FOUND){
        UniversalGarbage_free(garbage);
        return cweb.response.send_text(CLIENTE_NAO_EXIST,NAO_ENCONTRADO);
    }





    return cweb.response.send_text("Hello World", 200);

}

int main(int argc, char *argv[]){
    inicializa_namespaces();
    cria_clientes_inicias();
    #ifdef DEBUG
        for(int i = 3000;i < 4000; i++){
            CwebServer server = newCwebSever(i, main_sever);
            server.single_process = true;

            if(!cweb.server.start(&server)){
                break;
            }

        }
    #else
            CwebServer server = newCwebSever(PORTA_PADRAO, main_sever);
            cweb.server.start(&server);
    #endif

    return 0;
}