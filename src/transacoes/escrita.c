

void escreve_transacao_no_disco(
        DtwResource *banco,
        DtwResource *id_cliente,
        CxpathJson *dados,
        int saldo,
        Transacao *transacao
        
        ){

    UniversalGarbage  *garbage = newUniversalGarbage();

    //adicionando o novo saldo
    xpath.set_int(dados,saldo,"['%s']",SALDO_CHAVE_BANCO);

    //criando a transacao
    CxpathJson  *json_transacao = xpath.newJsonObject();
    UniversalGarbage_add(garbage, xpath.free,json_transacao);

    if(transacao->tipo == CODIGO_CREDITO){
        xpath.set_int(json_transacao,transacao->valor,"['%s']",VALOR_CHAVE_BANCO);
    }

    if(transacao->tipo== CODIGO_DEBITO){
        xpath.set_int(json_transacao,transacao->valor* -1,"['%s']",VALOR_CHAVE_BANCO);
    }

    xpath.set_int(json_transacao,momento_da_luz_adiquirida.tv_sec,"['%s']",DATA_SEGUNDOS_CHAVE);
    xpath.set_int(json_transacao,momento_da_luz_adiquirida.tv_usec,"['%s']",DATA_NANO_SEGUNDOS_CHAVE);
    xpath.set_str(json_transacao,transacao->descricao,"['%s']",DESCRICCAO_CHAVE_BANCO);

    int id_transacao = 0;

    int total_transacoes  = xpath.get_int(dados,"['%s']",TOTAL_TRANSACOES_CHAVE_BANCO);
    int ultima_transacao = xpath.get_int(dados,"['%s']",ULTIMA_TRANSACAO_CHAVE_BANCO);

    if(total_transacoes > 0){
        id_transacao = ultima_transacao+1;
    }

    ultima_transacao  = id_transacao;
    total_transacoes+=1;

    DtwResource *resource_transacaos = resource.sub_resource(id_cliente,CAMINHO_TRANSACOES);


    if(total_transacoes  > MAXIMO_TRANSACOES){
        int primeiro = ultima_transacao - total_transacoes;
        DtwResource *transacao_mais_antiga = resource.sub_resource(resource_transacaos,"%d",primeiro);
        resource.destroy(transacao_mais_antiga);
        total_transacoes-=1;
    }

    xpath.set_int(dados,total_transacoes,"['%s']",TOTAL_TRANSACOES_CHAVE_BANCO);
    xpath.set_int(dados,ultima_transacao,"['%s']",ULTIMA_TRANSACAO_CHAVE_BANCO);

    //definindo as resources
    char *json_transacao_str = xpath.dump_to_string(json_transacao,IDENTAR);
    UniversalGarbage_add_simple(garbage,json_transacao_str);


    char *dados_str = xpath.dump_to_string(dados,IDENTAR);
    UniversalGarbage_add_simple(garbage, dados_str);

    resource.set_string_in_sub_resource(resource_transacaos,json_transacao_str,"%d",id_transacao);
    resource.set_string_in_sub_resource(id_cliente, dados_str, CAMINHO_DADOS);
    resource.commit(banco);
    UniversalGarbage_free(garbage);

}