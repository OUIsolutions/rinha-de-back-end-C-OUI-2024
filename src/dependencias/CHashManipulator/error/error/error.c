

privateCHashError * privatenewCHashError(CHashObject *args, int error_code, const char *error_menssage){
    privateCHashError  *self = (privateCHashError*) malloc(sizeof (privateCHashError));
    self->args = args;
    self->error_code = error_code;
    self->error_mensage =  privateCHashError_create_menssage(args,error_code,error_menssage);

    return self;
}

CTextStack * privateCHashError_create_menssage(CHashObject *args, int error_code, const char *error_mensage){
    CTextStack  * error = newCTextStack_string(error_mensage);

    long args_size = CHash_get_size(args);
    for(int i = 0; i < args_size; i++){
        CHash *current = CHashArray_get(args,i);
        char *key = CHashObject_get_key_of_element(current);
        char *value = CHash_dump_to_json_string(current);
        CTextStack * formated_key = newCTextStack_string_empty();
        CTextStack_format(formated_key,"#%s#",key);
        CTextStack_self_replace(error,formated_key->rendered_text,value);
        CTextStack_free(formated_key);
        free(value);
    }
    return error;
}

void CHash_generate_custom_error(CHash  *self, CHashArray *errors){
    if(!self){
        return;
    }
    if(!Chash_errors(self)){
        return;
    }
    long  size = CHash_get_size(errors);
    long error_code = CHash_get_error_code(self);

    for(int i =0; i < size; i++){
        CHashObject  *current_object = CHashArray_get(errors,i);
        int code = (int)CHashObject_getNumber(current_object,"code");
        char *menssage = CHashObject_getString(current_object,"message");

        if(!Chash_errors(errors) && error_code == code){
          privateCHashError *generated_errror = privateCHashError_get_error(self);

            CTextStack_free(generated_errror->error_mensage);
            generated_errror->error_mensage = privateCHashError_create_menssage(
                    generated_errror->args,
                    code,
                    menssage
                    );
            break;
        }

    }

}

void CHash_generate_custom_error_cleaning_args(CHash  *self, CHashArray *error){
    CHash_generate_custom_error(self,error);
    CHash_free(error);
}

privateCHashError * privateCHashError_get_error(CHash *self){

    CHash  *first =  privateCHash_get_first_object(self);
    if(first->private_error){
        return (privateCHashError*)first->private_error;
    }
    return NULL;
}


bool Chash_errors(CHash *self){
    
    if(!self){
        return true;
    }

    privateCHashError *error  = privateCHashError_get_error(self);
    if(error){
        return true;
    }
    return false;
}


void CHash_raise_error(CHash *self,int error_code,const char *error_menssage, CHash *args){


    if(Chash_errors(self)){
        CHash_free(args);
        return;
    }

    CHash *formated_args = args;

    if(!args){
        formated_args = newCHashObjectEmpty();
    }
    CHashArray *path = CHash_get_path(self);

    if(CHash_get_size(path) > 0){
        CHash * last = CHashArray_get(path,-1);
        CHashObject_set_default(formated_args,"reference",last);
    }

    CHashObject_set_default(formated_args,  "path",path);
    CHashObject_set_default(formated_args,"value", CHash_copy(self));
    CHashObject_set_default(formated_args,"type",newCHashString(private_Chash_convert_type(self->private_type)));


    privateCHashError *created = privatenewCHashError(
            formated_args,
            error_code,
            error_menssage
    );
    CHash *first = privateCHash_get_first_object(self);
    first->private_error = (void*)created;

    
}

void CHash_raise_error_by_key(CHash *self,const char *key, int error_code,const char *error_menssage, CHash *args){
    if(Chash_errors(self)){return;}

    CHash *formated_args = args;

    if(!args){
        formated_args = newCHashObjectEmpty();
    }
    CHashArray *path = CHash_get_path(self);
    CHashArray_append_any(path, newCHashString(key));
    CHashObject_set_any(formated_args, "path", path);
    CHash_raise_error(self,error_code,error_menssage,formated_args);
}


void CHash_raise_error_by_index(CHash *self,long index, int error_code,const char *error_menssage, CHash *args){
    if(Chash_errors(self)){return;}

    CHash *formated_args = args;

    if(!args){
        formated_args = newCHashObjectEmpty();
    }
    CHashArray *path = CHash_get_path(self);
    CHashArray_append_any(path, newCHashNumber((double) index));
    CHashObject_set_any(formated_args, "path", path);
    CHash_raise_error(self,error_code,error_menssage,formated_args);
}


void privateCHashError_free(privateCHashError *self){
    CTextStack_free(self->error_mensage);
    CHash_free(self->args);
    free(self);
}

char * CHash_get_error_menssage(CHash *self){
    if(!self){

        return (char*)"element its NULL , (impossíble to get error menssage)\n";
    }

    if(!Chash_errors(self)){
        return NULL;
    }

    privateCHashError  *error = privateCHashError_get_error(self);

    return error->error_mensage->rendered_text;
}

int CHash_get_error_code(CHash *self){

    if(!self){
        return CHASH_ELEMENT_IS_NULL;
    }

    if(!Chash_errors(self)){
        return 0;
    }
    privateCHashError  *error = privateCHashError_get_error(self);
    return error->error_code;
}

CHash * CHash_get_error_args(CHash *self){
    if(!Chash_errors(self)){
        return NULL;
    }
    privateCHashError  *error = privateCHashError_get_error(self);
    return error->args;
}
