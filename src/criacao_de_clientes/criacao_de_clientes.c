
CxpathJson * obter_clientes_default(){
    CxpathJson * started = xpath.newJsonArray();
    xpath.set_int(started,0,"['$append',%d]",SALDO_INDEX);
    xpath.set_int(started,100000,"['-1',%d]",LIMITE_INDEX);
    xpath.set_int(started,0,"['-1',%d]",TOTAL_TRANSACOES_INDEX);
    xpath.set_int(started,0,"['-1',%d]",ULTIMA_TRANSACAO_INDEX);

    xpath.set_int(started,0,"['$append',%d]",SALDO_INDEX);
    xpath.set_int(started,80000,"['-1',%d]",LIMITE_INDEX);
    xpath.set_int(started,0,"['-1',%d]",TOTAL_TRANSACOES_INDEX);
    xpath.set_int(started,0,"['-1',%d]",ULTIMA_TRANSACAO_INDEX);

    xpath.set_int(started,0,"['$append',%d]",SALDO_INDEX);
    xpath.set_int(started,1000000,"['-1',%d]",LIMITE_INDEX);
    xpath.set_int(started,0,"['-1',%d]",TOTAL_TRANSACOES_INDEX);
    xpath.set_int(started,0,"['-1',%d]",ULTIMA_TRANSACAO_INDEX);

    xpath.set_int(started,0,"['$append',%d]",SALDO_INDEX);
    xpath.set_int(started,10000000,"['-1',%d]",LIMITE_INDEX);
    xpath.set_int(started,0,"['-1',%d]",TOTAL_TRANSACOES_INDEX);
    xpath.set_int(started,0,"['-1',%d]",ULTIMA_TRANSACAO_INDEX);

    xpath.set_int(started,0,"['$append',%d]",SALDO_INDEX);
    xpath.set_int(started,500000,"['-1',%d]",LIMITE_INDEX);
    xpath.set_int(started,0,"['-1',%d]",TOTAL_TRANSACOES_INDEX);
    xpath.set_int(started,0,"['-1',%d]",ULTIMA_TRANSACAO_INDEX);

    return started;
}

void cria_clientes_inicias(){
    UniversalGarbage  *garbage = newUniversalGarbage();
    DtwResource *banco = resource.newResource(CAMINHO_BANCO);

    DtwResource_destroy(banco);
    UniversalGarbage_add(garbage, resource.free,banco);

    CxpathJson *clientes =obter_clientes_default();
    UniversalGarbage_add(garbage, xpath.free,clientes);

    char *json_parsed = NULL;
    UniversalGarbage_add_simple(garbage,json_parsed);
    int total = xpath.size(clientes,"[]");
    for(int i = 0; i < total; i++){
        CxpathJson  * atual = xpath.get_array(clientes,"[%d]",i);
        DtwResource * resource_cliente = DtwResource_sub_resource(banco,"%d",i+1);
        json_parsed =  xpath.dump_to_string(atual,false);
        UniversalGarbage_resset(garbage,json_parsed);
        resource.set_string_in_sub_resource(resource_cliente,json_parsed,CAMINHO_DADOS);
    }

    DtwResource_commit(banco);
    UniversalGarbage_free(garbage);
}