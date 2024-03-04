

CHashNamespace newCHashNamespace(){
    CHashNamespace self = {0};

    self.load_from_cJSON = CHash_load_from_cJSON;
    self.load_from_json_strimg  = CHash_load_from_json_strimg;
    self.load_from_json_file = CHash_load_from_json_file;

    self.dump_to_cJSON = CHash_dump_to_cJSON;
    self.dump_to_json_string = CHash_dump_to_json_string;
    self.dump_to_json_file = CHash_dump_to_json_file;

    self.set =CHash_set;

    self.newBool = newCHashBool;
    self.toBool = CHash_toBool;
    self.convert_toBool = CHash_convert_toBool;
    self.toBool_converting = CHash_toBool_converting;

    self.set_Bool = CHash_set_Bool;

    self.newNumber = newCHashNumber;
    self.toNumber = CHash_toNumber;
    self.set_Number = CHash_set_Number;
    self.convert_toNumber =CHash_convert_toNumber;
    self.toNumber_converting  =CHash_toNumber_converting;

    self.newStackString = newCHashStackString;
    self.toStack = CHashtoStack;
    self.set_String = CHash_set_String;
    self.set_Stack = CHash_set_Stack;

    self.newString = newCHashString;
    self.toString = CHash_toString;
    self.newNULL = newCHashNULL;

    self.print = CHash_print;
    self.get_path = CHash_get_path;
    self.copy = CHash_copy;
    self.equals  = CHash_equals;
    self.get_size = CHash_get_size;


    self.errors = Chash_errors;
    self.get_error_code = CHash_get_error_code;
    self.get_error_args = CHash_get_error_args;
    self.get_error_menssage= CHash_get_error_menssage;

    self.get_type = CHash_get_type;

    self.free = CHash_free;

    self.object = newCHashObjectModule();
    self.array = newCHashArrayModule();
    self.validator = newCHashValidatorModule();
    return self;
}