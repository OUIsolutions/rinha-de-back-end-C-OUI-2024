

CHashValidatorModule newCHashValidatorModule(){
    CHashValidatorModule self = {0};
    self.raise_error = CHash_raise_error;
    self.raise_error_by_key = CHash_raise_error_by_key;
    self.raise_error_by_index = CHash_raise_error_by_index;
    self.generate_custom_error = CHash_generate_custom_error;
    self.generate_custom_error_cleaning_args = CHash_generate_custom_error_cleaning_args;

    self.ensure_Number = CHash_ensure_Number;
    self.ensure_Number_by_key = CHash_ensure_Number_by_key;
    self.ensure_Number_by_index = CHash_ensure_Number_by_index;

    self.ensure_Long = CHash_ensure_Long;
    self.ensure_Long_by_key = CHash_ensure_Long_by_key;
    self.ensure_Long_by_index = CHash_ensure_Long_by_index;

    self.ensure_min_value = CHash_ensure_min_value;
    self.ensure_min_value_by_key = CHash_ensure_min_value_by_key;
    self.ensure_min_value_by_index = CHash_ensure_min_value_by_index;

    self.ensure_max_value = CHash_ensure_max_value;
    self.ensure_max_value_by_key =CHash_ensure_max_value_by_key;
    self.ensure_max_value_by_index =CHash_ensure_max_value_by_index;



    self.ensure_Bool = CHash_ensure_Bool;
    self.ensure_Bool_by_key = CHash_ensure_Bool_by_key;
    self.ensure_Bool_by_index = CHash_ensure_Bool_by_index;

    self.ensure_String = CHash_ensure_String;
    self.ensure_String_by_key = CHash_ensure_String_by_key;
    self.ensure_String_by_index = CHash_ensure_String_by_index;
    self.ensure_only_chars = Chash_ensure_only_chars;

    self.ensure_Object = CHash_ensure_Object;
    self.ensure_Object_by_key = CHash_ensure_Object_by_key;
    self.ensure_Object_by_index = CHash_ensure_Object_by_index;
    self.ensure_only_keys =CHash_ensure_only_keys;
    self.ensure_only_keys_cleaning_args =CHash_ensure_only_keys_cleaning_args;


    self.ensure_Array = CHash_ensure_Array;
    self.ensure_Array_by_key = CHash_ensure_Array_by_key;
    self.ensure_Array_by_index = CHash_ensure_Array_by_index;

    self.ensure_all_types = CHash_ensure_all_types;
    self.ensure_all_String  = CHash_ensure_all_String;
    self.ensure_all_Bool = CHash_ensure_all_Bool;
    self.ensure_all_Numbers = CHash_ensure_all_Numbers;
    self.ensure_min_size = CHash_ensure_min_size;
    self.ensure_min_size_by_key = CHash_ensure_min_size_by_key;
    self.ensure_min_size_by_index = CHash_ensure_min_size_by_index;

    self.ensure_size = CHash_ensure_size;
    self.ensure_size_by_key= CHash_ensure_size_by_key;
    self.ensure_size_by_index = CHash_ensure_size_by_index;

    self.ensure_max_size = CHash_ensure_max_size;
    self.ensure_max_size_by_key  = CHash_ensure_max_size_by_key;
    self.ensure_max_size_by_index = CHash_ensure_max_size_by_index;

    return self;
}