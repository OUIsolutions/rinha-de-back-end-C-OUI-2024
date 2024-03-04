

double CHash_toNumber(CHash *element){

    if(CHash_ensure_Number(element)){
        return -1;
    }
    return element->private_value_double;

}
int CHash_convert_toNumber(CHash *self){
    if(Chash_errors(self)){
        return 1;
    }
    if(self->private_type == CHASH_NUMBER){
        return 0;
    }
    if(self->private_type != CHASH_STRING){
        CHash_raise_error(self,
                          CHASH_WRONG_TYPE,
                          "element at #path# is not convertible to number ",
                         newCHashObject(
                                  "expected_type", newCHashString(
                                  private_Chash_convert_type(CHASH_NUMBER)
                                )
                          )
        );
        return 1;
    }

    if(!CTextStack_is_a_num(self->private_value_stack)){
        CHash_raise_error(self,
                          CHASH_WRONG_TYPE,
                          "element at #path# is not convertible to number ",
                         newCHashObject(
                                  "expected_type", newCHashString(
                                  private_Chash_convert_type(CHASH_NUMBER)
                                )
                          )
        );
        return 1;
    }

    double  value = CTextStack_parse_to_double(self->private_value_stack);
    CHash_set_Number(self,value);
    return 0;
}

double  CHash_toNumber_converting(CHash *self){
    if(CHash_convert_toNumber(self)){
        return -1;
    }
    return self->private_value_double;
}


void CHash_set_Number(CHash *self,double  value){
    if(Chash_errors(self)){
        return;
    }

    privateCHash_free_values(self);
    self->private_type = CHASH_NUMBER;
    self->private_value_double = value;

}



CHash * newCHashNumber(double value){
    CHash * self =  privatenewChash_raw();
    self->private_type = CHASH_NUMBER;
    self->private_value_double = value;
    return self;
}

