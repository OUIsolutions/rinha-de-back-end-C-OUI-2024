

void CHashArray_foreach(CHashArray *self,void  (*callback)(CHash *current)){
    if(privateCHash_ensureArrayOrObject(self)){
        return;
    }
    long size = CHash_get_size(self);
    for(long i = 0; i < size;i++){

        CHash *current = CHashArray_get(self,i);
        callback(current);
        if(Chash_errors(self)){
            break;
        }
    }
}
void CHashArray_foreach_with_args(CHashArray *self,void  (*callback)(CHash *current,va_list args),...){

    if(privateCHash_ensureArrayOrObject(self)){
        return;
    }
    long size = CHash_get_size(self);

    for(long i = 0; i < size;i++){
        va_list  args;
        va_start(args, callback);
        CHash *current = CHashArray_get(self,i);
        callback(current,args);
        va_end(args);
        if(Chash_errors(self)){
            break;
        }
    }

}
/*
CHashArray * CHashArray_map(CHashArray *self,CHash* (*callback)(CHash *current)){

    if(privateCHash_ensureArrayOrObject(self)){
        return NULL;
    }

    CHashArray  *new_element = newCHashArrayEmpty();

    long size = CHash_get_size(self);
    for(long i = 0; i < size;i++){

        CHash *current = CHashArray_get(self,i);
        CHash *created = callback(current);
        if(Chash_errors(self)){
            CHash_free(new_element);
            CHash_free(created);
            return NULL;
        }
        CHashArray_append_once(new_element,current);
    }
    return  new_element;
}

CHashArray * CHashArray_map_with_args(CHashArray *self,CHash* (*callback)(CHash *current,va_list args),...){

    if(CHash_ensure_Array(self)){
        return NULL;
    }
    CHashArray  *new_element = newCHashArrayEmpty();

    long size = CHash_get_size(self);
    for(long i = 0; i < size;i++){
        va_list  args;
        va_start(args, callback);
        CHash *current = CHashArray_get(self,i);
        CHash *created = callback(current,args);
        va_end(args);
        if(Chash_errors(self)){
            CHash_free(new_element);
            CHash_free(created);
            return NULL;
        }
        CHashArray_append_once(new_element,current);
    }
    return  new_element;
}
*/