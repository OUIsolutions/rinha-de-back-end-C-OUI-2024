

RotaParser  parsear_rota(const char *rota){
    RotaParser rota_obj = {0};

    UniversalGarbage  *garbage = newUniversalGarbage();

    CTextArray * elementos  = CTextArray_split(rota,"/");
    UniversalGarbage_add(garbage, CTextArray_free, elementos);

    if(elementos->size != 4){

        UniversalGarbage_free(garbage);
        rota_obj.invalida = true;
        return rota_obj;
    }
    if(strcmp(elementos->stacks[1]->rendered_text,CLIENTES) != 0){
        UniversalGarbage_free(garbage);
        rota_obj.invalida = true;
        return rota_obj;
    }

    if(strcmp(elementos->stacks[3]->rendered_text,EXTRATO) == 0){
        rota_obj.acao = ACAO_EXTRATO;
    }

    if(strcmp(elementos->stacks[3]->rendered_text,TRANSACOES) == 0){
        rota_obj.acao = ACAO_TRANSACAO;
    }

    if(!rota_obj.acao){
        UniversalGarbage_free(garbage);
        rota_obj.invalida = true;
        return rota_obj;
    }

    rota_obj.id_cliente = strdup(elementos->stacks[2]->rendered_text);
    UniversalGarbage_free(garbage);
    return  rota_obj;
}

