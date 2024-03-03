

RotaParser  parsear_rota(const char *rota){
    RotaParser criada;

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



    return  criada;
}