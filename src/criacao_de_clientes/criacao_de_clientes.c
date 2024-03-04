
CHashArray  * obter_clientes_default(){
    return newCHashArray(

            newCHashArray(
                    newCHashNumber(0), //saldo
                    newCHashNumber(100000), //limite
                    newCHashArrayEmpty() //transacoes
            ),

            newCHashArray(
                    newCHashNumber(0), //saldo
                    newCHashNumber(80000), //limite
                    newCHashArrayEmpty() //transacoes

            ),

            newCHashArray(
                    newCHashNumber(0), //saldo
                    newCHashNumber(1000000), //limite
                    newCHashArrayEmpty() //transacoes
            ),

            newCHashArray(
                    newCHashNumber(0), //saldo
                    newCHashNumber(10000000), //limtie
                    newCHashArrayEmpty() //transacoes

            ),
            newCHashArray(
                    newCHashNumber(0), //saldo
                    newCHashNumber(500000), //limite
                    newCHashArrayEmpty() //transacoes
            )
    );
}

void cria_clientes_inicias(){
    UniversalGarbage  *garbage = newUniversalGarbage();
    DtwResource *banco = new_DtwResource(CAMINHO_BANCO);

#ifdef DEBUG
    DtwResource_destroy(banco);
#else
    if(DtwResource_type(banco) != DTW_NOT_FOUND){
        return;
    }
#endif

    UniversalGarbage_add(garbage, DtwResource_free,banco);

    CHashArray  *clientes =obter_clientes_default();
    UniversalGarbage_add(garbage, CHash_free,clientes);


    int total = CHash_get_size(clientes);
    for(int i = 0; i < total; i++){
        CHashArray *cliente_atual = CHashArray_getArray(clientes, i);
        DtwResource * resource_cliente = DtwResource_sub_resource(banco,"%d",i+1);
        DtwResource * dados = DtwResource_sub_resource(resource_cliente,CAMINHO_DADOS);
        escreve_chash_em_sub_resource(dados,cliente_atual);

    }
    DtwResource_commit(banco);
    UniversalGarbage_free(garbage);
}