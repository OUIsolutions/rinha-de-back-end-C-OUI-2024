#include "dependencias/CWebStudio.h"
#define DEBUG

CwebHttpResponse *main_sever(CwebHttpRequest *request ){

    return cweb_send_text("Hello World", 200);

}

int main(int argc, char *argv[]){
    #ifdef DEBUG
        for(int i = 3000;i < 4000; i++){
            CwebServer server = newCwebSever(i, main_sever);
            server.single_process = true;
            if(CwebServer_start(&server)){
                break;
            }
        }
    #endif

    return 0;
}