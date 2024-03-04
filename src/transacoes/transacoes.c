
CwebHttpResponse  * gera_transacao(CwebHttpRequest *request,DtwResource *id_cliente){

    Transacao transacao = parseia_transacao(request);
    if(transacao.resposta_de_erro){
        return transacao.resposta_de_erro;
    }
    //isso é importante para evitar problemas de concorrência
    DtwResource_lock(id_cliente);


    return cweb_send_text("aaaaaaa",200);





}