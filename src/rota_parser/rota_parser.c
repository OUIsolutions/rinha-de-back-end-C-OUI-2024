

RotaParser  parsear_rota(const char *rota){
    RotaParser criada = {0};

    UniversalGarbage  *garbage = newUniversalGarbage();

    CTextArray * elementos  = CTextArray_split(rota,"/");
    UniversalGarbage_add(garbage,stack_array.free, elementos);

    if(elementos->size != 3){
        UniversalGarbage_free(garbage);
        criada.invalida = true;
        return criada;
    }

    if(strcmp(elementos->stacks[0]->rendered_text,CLIENTES) != 0){
        UniversalGarbage_free(garbage);
        criada.invalida = true;
        return criada;
    }
    criada.id_cliente = elementos->stacks[1]->rendered_text;


    if(strcmp(elementos->stacks[2]->rendered_text,TRANSACOES) == 0){
        criada.acao = ACAO_TRANSACAO;
    }


    if(strcmp(elementos->stacks[2]->rendered_text,EXTRATO) == 0){
        criada.acao = ACAO_EXTRATO;
    }
    if(!criada.acao){
        criada.invalida = true;
    }


    return  criada;
}