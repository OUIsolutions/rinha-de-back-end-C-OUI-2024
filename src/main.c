#include "dependecies.h"
#include "declaration.h"
#include "definition.h"


CwebHttpResponse *main_sever(CwebHttpRequest *request ){


    RotaParser rota = parsear_rota(request->route);

    
    return cweb.response.send_text("Hello World", 200);

}

int main(int argc, char *argv[]){
    #ifdef DEBUG
        for(int i = 3000;i < 4000; i++){
            CwebServer server = newCwebSever(i, main_sever);
            server.single_process = true;
            if(cweb.server.start(&server)){
                break;
            }
        }
    #else
            CwebServer server = newCwebSever(PORTA_PADRAO, main_sever);
            cweb.server.start(&server)
    #endif

    return 0;
}