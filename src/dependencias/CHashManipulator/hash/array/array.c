
CHashArray  *newCHashArrayEmpty(){
    CHash * self =  privatenewChash_raw();
    self->private_type = CHASH_ARRAY;
    self->private_sub_elements = (CHash**)malloc(0);
    self->private_size = 0;
    return self;
}

CHashArray * privatenewCHashArray(void *sentinel, ...){
    CHash * self =  newCHashArrayEmpty();

    va_list args;
    va_start(args, sentinel);


    while(true){
        void * current = va_arg(args,void*);
        if(!current){
            break;
        }
        
        CHash * current_element = (CHash*)current;
        CHashArray_append_any(self, current_element);
    }
    va_end(args);
    return self;
}

CHashArray * privatenewCHashStringArray(void *sentinel, ...){
    CHash * self =  newCHashArrayEmpty();

    va_list args;
    va_start(args, sentinel);


    while(true){
        char  * current = va_arg(args,char*);
        if(!current){
            break;
        }
        CHashArray_append_any(self, newCHashString(current));
    }
    va_end(args);
    return self;
}

void CHashArray_append_any(CHashArray *self, CHash *element){

    if(CHash_ensure_Array(self)){
        return ;
    }

    CHash *new_element = privateCHash_copy_if_its_an_reference(element);

    self->private_sub_elements = (CHash**) realloc(
            self->private_sub_elements,
            (self->private_size + 1) * sizeof(CHash**)
    );
    new_element->private_reference_type = PRIVATE_CHASH_ARRAY_ITEM;
    new_element->private_father = self;
    new_element->private_index = self->private_size;
    self->private_sub_elements[self->private_size]= new_element;
    self->private_size+=1;


}

void CHashArray_append_long(CHashArray *self, long element){
    CHashArray_append_any(self, newCHashNumber((double)element));
}
void CHashArray_append_double(CHashArray *self, double element){
    CHashArray_append_any(self, newCHashNumber(element));

}
void CHashArray_append_bool(CHashArray *self, bool element){
    CHashArray_append_any(self, newCHashBool(element));

}
void CHashArray_append_string(CHashArray *self, const char *element){
    CHashArray_append_any(self, newCHashString(element));
}

void CHashArray_append_stack(CHashArray *self, CTextStack *element){
    CHashArray_append_any(self, newCHashStackString(element));
}


void privateCHashArray_append(CHashArray *self, ...){

    if(CHash_ensure_Array(self)){
        return;
    }

    va_list args;
    va_start(args, self);
    while(true){
        void * current = va_arg(args,void*);
        if(!current){
            break;
        }
        CHash * current_element = (CHash*)current;
        CHashArray_append_any(self, current_element);
    }
    va_end(args);

}
void  CHashArray_set(CHashArrayOrObject *self, long index,CHash *element){
    if(privateCHash_ensureArrayOrObject(self)){
        return;
    }
    long formated_index = privateCHashArray_convert_index(self,index);
    if(formated_index == -1){
        return ;
    }

    CHash *new_element = privateCHash_copy_if_its_an_reference(element);

    CHash  *current = self->private_sub_elements[formated_index];
    CHash_free(current);


    self->private_sub_elements[formated_index] = new_element;

}
void  CHashArray_set_long(CHashArrayOrObject *self, long index,long value){
    CHashArray_set(self,index, newCHashNumber((double)value));
}
void  CHashArray_set_double(CHashArrayOrObject *self, long index,double value){
    CHashArray_set(self,index, newCHashNumber(value));

}
void  CHashArray_set_bool(CHashArrayOrObject *self, long index,bool value){
    CHashArray_set(self,index, newCHashBool(value));

}
void  CHashArray_set_string(CHashArrayOrObject *self, long index,const char *value){
    CHashArray_set(self,index, newCHashString(value));
}
void  CHashArray_set_stack(CHashArrayOrObject *self, long index,CTextStack *value){
    CHashArray_set(self,index, newCHashStackString(value));
}


void CHashArray_remove(CHashArrayOrObject *self, long index){

    if(privateCHash_ensureArrayOrObject(self)){
        return;
    }
    long formated_index = privateCHashArray_convert_index(self,index);
    if(formated_index == -1){
        return ;
    }


    CHash  *current = self->private_sub_elements[formated_index];

    CHash_free(current);
    self->private_size-=1;

    for(long i = formated_index; i <  self->private_size;i++){
        self->private_sub_elements[i] = self->private_sub_elements[i + 1];

    }
}
long privateCHashArray_convert_index(CHashArrayOrObject *self, long index){
    long formated_index = index;
    if(index < 0){
        formated_index = (long)self->private_size +index;
    }
    if(formated_index < 0|| formated_index>= self->private_size){
        CHash_raise_error(
                self,
                CHASH_NOT_VALID_INDEX,
                " index: #index# its not valid, at #path#",
                newCHashObject(
                        "index", newCHashNumber(index)
                )
        );
        return -1;
    }
    return formated_index;
}
CHash * CHashArray_get(CHashArrayOrObject *self, long index){
    if(privateCHash_ensureArrayOrObject(self)){
        return NULL;

    }

    long formated_index = privateCHashArray_convert_index(self,index);
    if(formated_index == -1){
        return NULL;
    }

    return self->private_sub_elements[formated_index];
}

long CHashArray_find(CHashArray *self, CHash *element){
    long size = CHash_get_size(self);
    for(long i = 0; i < size; i++){
        CHash *current = CHashArray_get(self,i);
        if(CHash_equals(current,element)){
            return i;
        }
    }
    return -1;
}
long CHashArray_find_Number(CHashArray *self, double element){
    CHash *created = newCHashNumber(element);
    long index = CHashArray_find(self,created);
    CHash_free(created);
    return index;
}

long CHashArray_find_Bool(CHashArray *self, bool  element){
    CHash *created = newCHashBool(element);
    long index = CHashArray_find(self,created);
    CHash_free(created);
    return index;
}

long CHashArray_find_String(CHashArray *self, const char *element){
    CHash *created = newCHashString(element);
    long index = CHashArray_find(self,created);
    CHash_free(created);
    return index;
}



short CHashArray_get_type(CHashArray *self, long index){
    if(privateCHash_ensureArrayOrObject(self)){
        return CHASH_NOT_EXIST;
    }
    long formated_index = privateCHashArray_convert_index(self,index);
    if(formated_index == -1){
        return CHASH_NOT_EXIST;
    }
    CHash  *element = self->private_sub_elements[formated_index];
    return CHash_get_type(element);

}

void CHashArray_switch(CHashArrayOrObject *self, long index ,long target_index){
    if(privateCHash_ensureArrayOrObject(self)){
        return ;
    }
    long formated_index = privateCHashArray_convert_index(self,index);
    if(formated_index == -1){
        return;
    }
    long formated_target_index = privateCHashArray_convert_index(self,target_index);
    if(formated_target_index == -1){
        return;
    }

    CHash *changed = self->private_sub_elements[formated_index];

    self->private_sub_elements[formated_index] =  self->private_sub_elements[target_index];
    self->private_sub_elements[formated_index]->private_index = formated_index;

    self->private_sub_elements[target_index] = changed;
    changed->private_index = target_index;

}
CHashArray * CHashArray_getArray(CHashArrayOrObject * self, long index){
    CHash *element = CHashArray_get(self,index);
    if(CHash_ensure_Array(element)){
        return NULL;
    }
    return  element;
}

CHashObject * CHashArray_getObject(CHashArrayOrObject * self, long index){
    CHashObject *element = CHashArray_get(self,index);
    if(CHash_ensure_Object(element)){
        return NULL;
    }
    return element;
}



double CHashArray_getNumber(CHashArrayOrObject * self, long index){
    CHashObject *element = CHashArray_get(self,index);
    return CHash_toNumber(element);
}

double CHashArray_getNumber_converting(CHashArrayOrObject *self, long index){
    CHashObject *element = CHashArray_get(self,index);
    return CHash_toNumber_converting(element);
}

bool CHashArray_getBool(CHashArrayOrObject * self, long index){
    CHashObject *element = CHashArray_get(self,index);
    return CHash_toBool(element);

}

bool CHashArray_getBool_converting(CHashObject * self, long index){
    CHashObject *element = CHashArray_get(self,index);
    return CHash_toBool_converting(element);
}

char  * CHashArray_getString(CHashArrayOrObject * self, long index){
    CHashObject *element = CHashArray_get(self,index);
    return CHash_toString(element);
}
CTextStack  * CHashArray_getStack(CHashObject * self, long index){
    CHashObject *element = CHashArray_get(self,index);
    return CHashtoStack(element);
}