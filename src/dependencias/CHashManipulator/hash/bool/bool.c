

bool CHash_toBool(CHash *element){
    if(CHash_ensure_Bool(element)){
        return false;
    }
    return element->private_value_bool;
}

int CHash_convert_toBool(CHash *self){

    if(Chash_errors(self)){
        return 1;
    }

    if(self->private_type == CHASH_BOOL){
        return 0;
    }

    if(self->private_type == CHASH_NUMBER){
        CHash_set_Bool(self,(bool)self->private_value_double);
        return 0;
    }


    if(self->private_type != CHASH_STRING){
        CHash_raise_error(self,
                          CHASH_WRONG_TYPE,
                          "element at #path# is not convertable to number ",
                         newCHashObject(
                                  "expected_type", newCHashString(
                                  private_Chash_convert_type(CHASH_BOOL)
                                )
                          )
        );
        return 1;
    }

    int type  = CTextStack_typeof(self->private_value_stack);

    if(type != CTEXT_BOOL){
        CHash_raise_error(self,
                          CHASH_WRONG_TYPE,
                          "element at #path# is not convertible to bool ",
                        newCHashObject(
                                  "expected_type", newCHashString(
                                  private_Chash_convert_type(CHASH_BOOL)
                                )
                          )
        );
        return 1;
    }

    bool  value = CTextStack_parse_to_bool(self->private_value_stack);
    CHash_set_Bool(self,value);
    return 0;

}

bool CHash_toBool_converting(CHash *self){

    if(CHash_convert_toBool(self)){
        return false;
    }
    return self->private_value_bool;
}


void CHash_set_Bool(CHash *self, bool value){
    if(Chash_errors(self)){
        return;
    }

    privateCHash_free_values(self);
    self->private_type = CHASH_BOOL;
    self->private_value_bool = value;
}


CHash * newCHashBool(bool value){
    CHash * self =  privatenewChash_raw();
    self->private_type = CHASH_BOOL;
    self->private_value_bool = value;
    return self;
}

