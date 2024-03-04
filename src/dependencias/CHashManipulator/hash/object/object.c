



CHashObject  * newCHashObjectEmpty(){
    CHash * self =  privatenewChash_raw();
    self->private_type = CHASH_OBJECT;
    self->private_sub_elements = (CHash**)malloc(0);
    self->private_size = 0;
    return self;
}

CHashObject* privatenewCHashObject(void * sentinel, ...){
    CHash * self =  newCHashObjectEmpty();

    va_list args;
    va_start(args, sentinel);

    const int GETTING_KEY = 0;
    const int GETTING_VALUE = 1;


    int state = GETTING_KEY;
    char *key = NULL;

    while(true){
        void * current = va_arg(args,void*);
        
        if(!current){
            break;
        }

        if(state == GETTING_KEY){
            key = (char*)current;
            state = GETTING_VALUE;
            continue;
        }

        if(state == GETTING_VALUE){
            CHashObject_set_any(self, key, (CHash *) current);
            state = GETTING_KEY;

        }

    }
    
    va_end(args);

    return self;
}


CHash * privateCHashObject_get_by_key_or_null(CHashObject * self, const char *key){
    if(Chash_errors(self)){
        return NULL;
    }
    for(int i =0;i < self->private_size; i ++){
        CHash * current = self->private_sub_elements[i];
        if(strcmp(current->private_key, key) == 0){
            return current;
        }
    }
    return NULL;
}

bool CHashObject_exist(CHashObject *self, const char *key){
    CHash  *element = privateCHashObject_get_by_key_or_null(self,key);
    if(element){
        return  true;
    }
    return false;
}



char * CHashObject_get_key_by_index(CHashObject *self,long index){
    CHash  *element = CHashArray_get(self,index);
    if(!element){
        return NULL;
    }
    return CHashObject_get_key_of_element(element);
}



char   * CHashObject_get_key_of_element(CHash *self){
    if(Chash_errors(self)){
        return NULL;
    }
    if(self->private_reference_type != PRIVATE_CHASH_KEYVAL){
        CHash_raise_error(self,CHASH_NOT_HAVE_KEY,"element of #path# does not have an key",NULL);
    }
    return self->private_key;
}



void  CHashObject_remove(CHashObject *self, const char *key){
    if(CHash_ensure_Object(self)){
        return ;
    }

    bool found = false;

    for(int i =0;i < self->private_size; i ++){
        CHash * current = self->private_sub_elements[i];
        if(strcmp(current->private_key, key) == 0){
            CHash_free(current);
            found = true;
            self->private_size-=1;
        }

        if(found && i < self->private_size){
            self->private_sub_elements[i] = self->private_sub_elements[i + 1];
        }

    }
    
}
void  CHashObject_set_any(CHashObject * self, const char *key, CHash *element){
    if(CHash_ensure_Object(self)){
        return ;
    }

    CHash *formated_element = privateCHash_copy_if_its_an_reference(element);

    CHashObject_remove(self, key);

    self->private_sub_elements = (CHash**) realloc(
            self->private_sub_elements,
            (self->private_size + 1) * sizeof(CHash**)
    );

    formated_element->private_reference_type = PRIVATE_CHASH_KEYVAL;
    formated_element->private_father = self;
    formated_element->private_key = strdup(key);
    self->private_sub_elements[self->private_size]= formated_element;
    self->private_size+=1;
}

void  CHashObject_set_long(CHashObject * self, const char *key, long value){
    CHashObject_set_any(self,key, newCHashNumber((double)value));
}

void  CHashObject_set_double(CHashObject * self, const char *key, double value){
    CHashObject_set_any(self,key, newCHashNumber(value));
}

void  CHashObject_set_bool(CHashObject * self, const char *key, bool value){
    CHashObject_set_any(self,key, newCHashBool(value));
}

void  CHashObject_set_string(CHashObject * self, const char *key, const char *value){
    CHashObject_set_any(self,key, newCHashString(value));
}


void  CHashObject_set_Stack(CHashObject * self, const char *key,CTextStack *stack_value){
    CHashObject_set_any(self,key, newCHashStackString(stack_value));
}


void  CHashObject_set_default(CHashObject * self, const char *key, CHash *element){
    if(CHashObject_exist(self,key)){
        if(element->private_reference_type == PRIVATE_CHASH_NOT_A_REFERENCE){
            CHash_free(element);
        }
        return;
    }
    CHashObject_set_any(self, key, element);
}





void  privateCHashObject_set(CHashObject *self , ...){

    if(CHash_ensure_Object(self)){
        return;
    }
    va_list args;

    va_start(args, self);

    const int GETTING_KEY = 0;
    const int GETTING_VALUE = 1;

    int state = GETTING_KEY;

    char *key =NULL;

    while (true){
        void * current = va_arg(args,void*);
        if(!current){
            break;
        }

        if(state == GETTING_KEY){
            key = (char*)current;
            state = GETTING_VALUE;
            continue;
        }

        if(state == GETTING_VALUE){
            CHashObject_set_any(self, key, (CHash *) current);
         
            state = GETTING_KEY;
        }

    }
    va_end(args);
    
}
short  CHashObject_get_type(CHashObject *self, const char *key){
    CHash  *element = privateCHashObject_get_by_key_or_null(self,key);
    return CHash_get_type(element);
}


CHash * CHashObject_get(CHashObject * self, const char *key){

    if(CHash_ensure_Object(self)){
        return NULL;
    }

    CHash *element = privateCHashObject_get_by_key_or_null(self, key);

    if(element){
        return  element;
    }


    CHash_raise_error(self,
                      CHASH_ELEMENT_NOT_EXIST,
                      "element of key:#key# at #path# not exist",
                      newCHashObject("key", newCHashString(key))
    );

    return  NULL;
}
CHashArray * CHashObject_getArray(CHashObject * self, const char *key){
    CHashArray  *element = CHashObject_get(self,key);
    if(CHash_ensure_Array(element)){
        return NULL;
    };

    return element;
}

CHashObject * CHashObject_getObject(CHashObject * self, const char *key){
    
    CHashObject *element = CHashObject_get(self,key);
    if(CHash_ensure_Object(element)){
        return NULL;
    }
    return element;
}



double CHashObject_getNumber(CHashObject * self, const char *key){
    CHash *element = CHashObject_get(self,key);
    return CHash_toNumber(element);
}

double CHashObject_getNumber_converting(CHashObject * self, const char *key){
    CHash *element = CHashObject_get(self,key);
    return CHash_toNumber_converting(element);
}

bool CHashObject_getBool(CHashObject * self, const char *key){
    CHash *element = CHashObject_get(self,key);
    return CHash_toBool(element);
}

bool CHashObject_getBool_converting(CHashObject * self, const char *key){
    CHash *element = CHashObject_get(self,key);
    return CHash_toBool_converting(element);
}

char  * CHashObject_getString(CHashObject * self, const char *key){
    CHash *element = CHashObject_get(self,key);
    return CHash_toString(element);
}

CTextStack * CHashObject_getStack(CHashObject * self, const char *key){
    CHash *element = CHashObject_get(self,key);
    return CHashtoStack(element);
}

