
CHashArray  * obter_clientes_default(){
    return newCHashArray(

            newCHashObject(
                    "id",chash.newString("1"),
                    "limite",chash.newNumber(100000),
                    "saldo",chash.newNumber(0)
            ),

            newCHashObject(
                    "id",chash.newString("2"),
                    "limite",chash.newNumber(80000),
                    "saldo",chash.newNumber(0)

            ),

            newCHashObject(
                    "id",chash.newString("3"),
                    "limite",chash.newNumber(1000000),
                    "saldo",chash.newNumber(0)

            ),

            newCHashObject(
                    "id",chash.newString("4"),
                    "limite",chash.newNumber(10000000),
                    "saldo",chash.newNumber(0)

            ),
            newCHashObject(
                    "id",chash.newString("5"),
                    "limite",chash.newNumber(500000),
                    "saldo",chash.newNumber(0)
            )
    );
}

void cria_clientes_inicias(){
    UniversalGarbage  *garbage = newUniversalGarbage();
    DtwResource *banco = resource.newResource(CAMINHO_BANCO);
    UniversalGarbage_add(garbage,resource.free,banco);

    CHashArray  *clientes =obter_clientes_default();
    UniversalGarbage_add(garbage,chash.free,clientes);

    int total = chash.get_size(clientes);
    for(int i = 0; i < total; i++){
        CHashObject *cliete_atual = chash.array.getObject(clientes, i);
        char *id = chash.object.getString(cliete_atual, "id");
        int saldo = chash.object.getNumber(cliete_atual, "saldo");
        int limite  = chash.object.getNumber(cliete_atual,"limite");

        DtwResource *resource_cliente = resource.sub_resource(banco,id);
        resource.set_long_in_sub_resource(resource_cliente,saldo,CAMINHO_SALDO);
        resource.set_long_in_sub_resource(resource_cliente,limite,CAMINHO_LIMITE);
    }
    resource.commit(banco);
    UniversalGarbage_free(garbage);
}