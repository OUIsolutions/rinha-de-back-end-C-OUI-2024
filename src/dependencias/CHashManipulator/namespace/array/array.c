

CHashArrayModule newCHashArrayModule(){
    CHashArrayModule self = {0};
    self.newArrayEmpty = newCHashArrayEmpty;
    self.append_any = CHashArray_append_any;
    self.append_double =CHashArray_append_double;
    self.append_long = CHashArray_append_long;
    self.append_bool = CHashArray_append_bool;
    self.append_string = CHashArray_append_string;
    self.append_stack =CHashArray_append_stack;

    self.set = CHashArray_set;
    self.set_double = CHashArray_set_double;
    self.set_long =CHashArray_set_long;
    self.set_bool =CHashArray_set_bool;
    self.set_string = CHashArray_set_string;
    self.set_stack = CHashArray_set_stack;

    self.remove = CHashArray_remove;
    self.get = CHashArray_get;
    self.foreach = CHashArray_foreach;
    self.foreach_with_args = CHashArray_foreach_with_args;

    //self.map = CHashArray_map;
    //self.map_with_args = CHashArray_map_with_args;

    self.find = CHashArray_find;
    self.find_Number =CHashArray_find_Number;
    self.find_Bool = CHashArray_find_Bool;
    self.find_String = CHashArray_find_String;

    self.get_type = CHashArray_get_type;
    self.getArray = CHashArray_getArray;
    self.getObject = CHashArray_getObject;
    self.getString = CHashArray_getString;
    self.getStack  = CHashArray_getStack;
    self.getNumber = CHashArray_getNumber;
    self.getNumber_converting = CHashArray_getNumber_converting;
    self.getBool = CHashArray_getBool;
    self.getBool_converting = CHashArray_getBool_converting;
    return self;
}