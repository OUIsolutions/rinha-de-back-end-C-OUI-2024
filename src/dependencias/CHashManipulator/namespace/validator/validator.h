

typedef struct CHashValidatorModule {
    void (*raise_error)(CHash *self,int error_code,const char *error_menssage, CHash *args);

    void (*raise_error_by_key)(CHash *self,const char *key, int error_code,const char *error_menssage, CHash *args);
    void (*raise_error_by_index)(CHash *self,long index, int error_code,const char *error_menssage, CHash *args);
    void (*generate_custom_error)(CHash  *self, CHashArray *error);
    void (*generate_custom_error_cleaning_args)(CHash  *self, CHashArray *error);

    int (*ensure_Number)(CHash *element);
    int (*ensure_Number_by_key)(CHash *object, const char *key);
    int (*ensure_Number_by_index)(CHash *array, long index);

    int (*ensure_Long)(CHash *element);
    int (*ensure_Long_by_key)(CHash *object, const char *key);
    int (*ensure_Long_by_index)(CHash *array, long index);

    int (*ensure_min_value)(CHash *element, double  min);
    int (*ensure_min_value_by_key)(CHash *object, const char *key, double min );
    int (*ensure_min_value_by_index)(CHash *array, long index, double min);


    int (*ensure_max_value)(CHash *element, double  max);
    int (*ensure_max_value_by_key)(CHash *object, const char *key, double  max);
    int (*ensure_max_value_by_index)(CHash *array, long index, double  max);

    int (*ensure_Bool)(CHash *element);
    int (*ensure_Bool_by_key)(CHash *object , const char *key);
    int (*ensure_Bool_by_index)(CHash *array , long index);

    int (*ensure_String)(CHash *element);
    int (*ensure_String_by_key)(CHash *object , const char *key);
    int (*ensure_String_by_index)(CHash *array , long index);
    int (*ensure_only_chars)(CHash *element, const char *seq);

    int (*ensure_Object)(CHash *element);
    int (*ensure_Object_by_key)(CHash *object , const char *key);
    int (*ensure_Object_by_index)(CHash *array , long index);
    int (*ensure_only_keys)(CHashObject *object, CHashStringArray *keys);
    int (*ensure_only_keys_cleaning_args)(CHashObject *object, CHashStringArray *keys);


    int (*ensure_Array)(CHash *element);
    int (*ensure_Array_by_key)(CHash *object , const char *key);
    int (*ensure_Array_by_index)(CHash *array , long index);

    int (*ensure_all_types)(CHash *element, short expected_type);
    int (*ensure_all_String)(CHash *element);
    int (*ensure_all_Numbers)(CHash *element);
    int (*ensure_all_Bool)(CHash *element);


    int (*ensure_min_size)(CHash *iterable,long min);
    int (*ensure_min_size_by_key)(CHash  *object, const char *key,long min);
    int (*ensure_min_size_by_index)(CHash  *array, long index,long  min);

    int (*ensure_size)(CHash *iterable,long size);
    int (*ensure_size_by_key)(CHash  *object, const char *key,long size);
    int (*ensure_size_by_index)(CHash  *array, long index,long  size);


    int (*ensure_max_size)(CHash *iterable,long max);
    int (*ensure_max_size_by_key)(CHash  *object, const char *key,long max);
    int (*ensure_max_size_by_index)(CHash  *array, long index,long  max);


}CHashValidatorModule;

CHashValidatorModule newCHashValidatorModule();
