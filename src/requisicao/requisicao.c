

Requisicao roda_servidor(CwebHttpRequest *request){

    Requisicao  req = {0};
    UniversalGarbage  *garbage = newUniversalGarbage();
    RotaParser rota_obj = parsear_rota(request->route);
    UniversalGarbage_add_simple(garbage,rota_obj.id_cliente);

    if(rota_obj.invalida){
        UniversalGarbage_free(garbage);
        req.resposta = cweb.response.send_text(ROTA_INVALIDA, INCONSISTENCIA);
        return req;
    }
    DtwResource *banco = resource.newResource(CAMINHO_BANCO);

    UniversalGarbage_add(garbage, DtwResource_free,banco);
    DtwResource *cliente = resource.sub_resource(banco,rota_obj.id_cliente);


    if(DtwResource_type(cliente) == DTW_NOT_FOUND){
        UniversalGarbage_free(garbage);

        req.resposta = cweb.response.send_text(CLIENTE_NAO_EXIST,NAO_ENCONTRADO);
        return req;
    }

    if(rota_obj.acao == ACAO_TRANSACAO){
        req.resposta = gera_transacao(&req,request,banco,cliente);
    }

    if(rota_obj.acao == ACAO_EXTRATO){
        req.resposta = gera_extrato(&req,cliente);
    }
    if(req.adiquiriu_o_bloqueio){
        req.liberou_o_bloqueio = true;
        req.momento_do_bloqueio_liberado = retorna_data_atual();
    }
    UniversalGarbage_free(garbage);

    return req;

}