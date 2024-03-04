
CHash * privatenewChash_raw(){
    CHash  *self = (CHash*) malloc(sizeof (CHash));
    *self = (CHash){0};
    return self;
}

void CHash_print(CHash *self){
    char * result = CHash_dump_to_json_string(self);
    printf("%s\n",result);
    free(result);
}

CHashArray * CHash_get_path(CHash *self){

    if(self->private_reference_type == PRIVATE_CHASH_NOT_A_REFERENCE){
        return newCHashArrayEmpty();
    }

    CHashArray  *path = CHash_get_path(self->private_father);

    if(self->private_reference_type == PRIVATE_CHASH_ARRAY_ITEM){
        CHashArray_append(path, newCHashNumber(self->private_index));
    }

    if(self->private_reference_type == PRIVATE_CHASH_KEYVAL){
        CHashArray_append(path, newCHashString(self->private_key));
    }
    return path;

}

bool CHash_equals(CHash *element1, CHash *element2){
    if(!element1  && !element2){
        return true;
    }
    if(element1 && element2){
        char *element1_str = CHash_dump_to_json_string(element1);
        char *element2_str = CHash_dump_to_json_string(element2);

        bool equal = strcmp(element1_str,element2_str) == 0;
        free(element1_str);
        free(element2_str);
        return equal;
    }
    return  false;

}

void privateCHash_free_values(CHash *self){

    if(self->private_type == CHASH_STRING){
        CTextStack_free(self->private_value_stack);
    }

    if(self->private_type == CHASH_OBJECT || self->private_type == CHASH_ARRAY){
        long size = (long)self->private_size;
        for(int i = 0; i < size; i++){
            CHash * current = self->private_sub_elements[i];
            CHash_free(current);
        }
        free(self->private_sub_elements);
    }

}
void CHash_free(CHash *self){
    if(!self){
        return;
    }
    if(self->private_reference_type == PRIVATE_CHASH_KEYVAL){
        free(self->private_key);
    }
    if(self->private_reference_type == PRIVATE_CHASH_NOT_A_REFERENCE){
        if(self->private_error){
            privateCHashError *error = (privateCHashError*)self->private_error;
            privateCHashError_free(error);
        }
    }

    privateCHash_free_values(self);

    free(self);
}


void CHash_set(CHash *self,CHash *element){
    if(Chash_errors(self)){
        return;
    }
    privateCHash_free_values(self);
    CHash  *target_element = privateCHash_copy_if_its_an_reference(element);

    self->private_type = target_element->private_type;
    self->private_size = target_element->private_size;

    if(self->private_type == CHASH_STRING){
        self->private_value_stack = target_element->private_value_stack;
    }

    if(self->private_type == CHASH_BOOL){
        self->private_value_bool = target_element->private_value_bool;
    }

    if(self->private_type == CHASH_NUMBER){
        self->private_value_double = target_element->private_value_double;
    }

    if(self->private_type == CHASH_OBJECT || self->private_type == CHASH_ARRAY){
        self->private_sub_elements = target_element->private_sub_elements;
        for (int i = 0; i < self->private_size; i++){
            CHash  *current = self->private_sub_elements[i];
            current->private_father = self->private_father;
        }
    }

    free(target_element);

}

long CHash_get_size(CHash *self){
    if(Chash_errors(self)){
       return -1;
    }
    if(self->private_type == CHASH_STRING){
        return (long)self->private_value_stack->size;
    }
    if(self->private_type == CHASH_OBJECT || self->private_type == CHASH_ARRAY){
        return (long)self->private_size;
    }
    CHash_raise_error(self,CHASH_NOT_ITERABLE, "the element at #path# its not an iterable (string,array,object)",NULL);
    return -1;
}


CHash * CHash_copy(CHash *self){
    if(!self){
        return newCHashNULL();
    }

    if(self->private_type == CHASH_STRING){
        return newCHashString(self->private_value_stack->rendered_text);
    }
    

    if(self->private_type == CHASH_NUMBER){
        return newCHashNumber(self->private_value_double);
    }
    
    if(self->private_type == CHASH_BOOL){
        return newCHashBool(self->private_value_bool);
    }

    if(self->private_type == CHASH_ARRAY ){
        CHash * new_element  = newCHashArrayEmpty();

        for(long i =0; i < self->private_size; i++){
            CHash * copy = CHash_copy(CHashArray_get(self,i));
            CHashArray_append(new_element, copy);
        }
        return new_element;

    }

    if(self->private_type == CHASH_OBJECT){
        CHash * new_element  = newCHashObjectEmpty();

        for(long  i =0; i < self->private_size; i++){
            CHash  * current = CHashArray_get(self,i);
            CHash *copy = CHash_copy(current);

            CHashObject_set_many(new_element, current->private_key, copy);
        }
        return new_element;
    }


    return newCHashNULL();
}
CHash * privateCHash_copy_if_its_an_reference(CHash *self){
    if(!self){
        return NULL;
    }

    if(self->private_reference_type == PRIVATE_CHASH_NOT_A_REFERENCE){
        return self;
    }
    return CHash_copy(self);

}
CHash * privateCHash_get_first_object(CHash *self){
    if(self->private_reference_type == PRIVATE_CHASH_NOT_A_REFERENCE) {
        return self;
    }
    return privateCHash_get_first_object(self->private_father);

}
CHash * newCHashNULL(){
    return privatenewChash_raw();
}
