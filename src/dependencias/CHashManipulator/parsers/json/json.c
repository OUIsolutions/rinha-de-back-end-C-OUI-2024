
cJSON * privateCHash_dumps_json_object(CHashObject * object){
    long size = object->private_size;
    cJSON * element = cJSON_CreateObject();
    for(int i = 0; i < size; i++){
        CHashArray *current  = CHashArray_get(object, i);
        cJSON *current_json = CHash_dump_to_cJSON(current);
        cJSON_AddItemToObject(element, current->private_key, current_json);
    }
    return element;
}

cJSON * privateCHash_dumps_json_array(CHashArray * array){
    long size = array->private_size;
    cJSON *element = cJSON_CreateArray();
    for(int i = 0; i < size; i++){
        CHashArray *current  = CHashArray_get(array, i);
        cJSON *current_json = CHash_dump_to_cJSON(current);
        cJSON_AddItemToArray(element,current_json);
    }
    return element;
}


cJSON * CHash_dump_to_cJSON(CHash *element){
    int type = element->private_type;
    if(type == CHASH_OBJECT){
        return privateCHash_dumps_json_object(element);
    }
    if(type == CHASH_ARRAY){
        return privateCHash_dumps_json_array(element);
    }
    if(type == CHASH_STRING){
        char *value  = CHash_toString(element);
        return cJSON_CreateString(value);
    }
    if(type == CHASH_NUMBER){
        return cJSON_CreateNumber(CHash_toNumber(element));
    }

    if(type == CHASH_BOOL){
        return cJSON_CreateBool(CHash_toBool(element));
    }



    return cJSON_CreateNull();

}

char * CHash_dump_to_json_string(CHash * element){
    cJSON * created = CHash_dump_to_cJSON(element);
    char * result  = cJSON_Print(created);
    cJSON_Delete(created);
    return result;
}

int  CHash_dump_to_json_file(CHash *element,const char *filename){
    char *content = CHash_dump_to_json_string(element);
    if(!content){
        return 1;
    }
    privateCHash_write_file(filename,content);
    free(content);
    return 0;

}
CHashArray * privateCHash_load_json_object(cJSON *element){

    int size = cJSON_GetArraySize(element);

    CHashObject *equivalent = newCHashObjectEmpty();

    for(int i = 0; i < size; i++){
        cJSON *current = cJSON_GetArrayItem(element,i);
        char *key = current->string;
        CHash * value = CHash_load_from_cJSON(current);
        CHashObject_set_any(equivalent, key, value);
    }

    return equivalent;

}

CHash  * privateCHash_load_json_array(cJSON *element){
    int size = cJSON_GetArraySize(element);
    CHashObject *equivalent = newCHashArrayEmpty();
    for(int i = 0; i < size; i++){
        cJSON *current = cJSON_GetArrayItem(element,i);
        CHash * value = CHash_load_from_cJSON(current);
        CHashArray_append_any(equivalent, value);
    }
    return equivalent;
}


CHash * CHash_load_from_cJSON(cJSON *element){

    if(!element){
        return newCHashNULL();
    }

    if(element->type == cJSON_Object){
        return privateCHash_load_json_object(element);
    }

    if(element->type == cJSON_Array){
        return privateCHash_load_json_array(element);
    }
    if(cJSON_IsBool(element)){
        bool value = element->valueint;
        return newCHashBool(value);
    }
    if(element->type == cJSON_String){
        return newCHashString(element->valuestring);
    }

    if(element->type == cJSON_Number){
        return newCHashNumber(element->valuedouble);
    }

    return newCHashNULL();



}

CHash * CHash_load_from_json_strimg(const char *content){
    cJSON *parsed = cJSON_Parse(content);
    if(!parsed){
        CHash *null_element = newCHashNULL();
        CHash_raise_error(null_element,CHASH_NOT_VALID_JSON,
                          "content #content# its not an valid json",
                          newCHashObject("content", newCHashString(content))
        );
        return  null_element;
    }

    CHash *result =CHash_load_from_cJSON(parsed);
    cJSON_Delete(parsed);
    return result;
}

CHash * CHash_load_from_json_file(const char *filename){
    char *content = privateCHash_read_file(filename);
    if(!content){
        CHash *null_element = newCHashNULL();
        CHash_raise_error(null_element,CHASH_FILE_NOT_FOUND,"file at #filepath# not found",
                          newCHashObject("filepath", newCHashString(filename))
        );
        return  null_element;
    }
    CHash *result =  CHash_load_from_json_strimg(content);

    free(content);

    return result;
}


