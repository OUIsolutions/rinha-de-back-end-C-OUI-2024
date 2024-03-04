
int private_chash_check_type(CHash *element, unsigned short  expected_type);

int CHash_ensure_Number(CHash *element);
int CHash_ensure_Number_by_key(CHash *object, const char *key);
int CHash_ensure_Number_by_index(CHash *array, long index);

int CHash_ensure_Long(CHash *element);
int CHash_ensure_Long_by_key(CHash *object, const char *key);
int CHash_ensure_Long_by_index(CHash *array, long index);


int CHash_ensure_min_value(CHash *element, double  min);
int CHash_ensure_min_value_by_key(CHash *object, const char *key, double min );
int CHash_ensure_min_value_by_index(CHash *array, long index, double min);


int CHash_ensure_max_value(CHash *element, double  max);
int CHash_ensure_max_value_by_key(CHash *object, const char *key, double  max);
int CHash_ensure_max_value_by_index(CHash *array, long index, double  max);




int CHash_ensure_Bool(CHash *element);
int CHash_ensure_Bool_by_key(CHash *object , const char *key);
int CHash_ensure_Bool_by_index(CHash *array , long index);

int CHash_ensure_String(CHash *element);
int Chash_ensure_only_chars(CHash *element, const char *seq);

int CHash_ensure_String_by_key(CHash *object , const char *key);
int CHash_ensure_String_by_index(CHash *array , long index);

int CHash_ensure_Object(CHash *element);
int CHash_ensure_Object_by_key(CHash *object , const char *key);
int CHash_ensure_Object_by_index(CHash *array , long index);

int CHash_ensure_only_keys(CHashObject *object, CHashStringArray *keys);
int CHash_ensure_only_keys_cleaning_args(CHashObject *object, CHashStringArray *keys);


int CHash_ensure_Array(CHash *element);
int CHash_ensure_Array_by_key(CHash *object , const char *key);
int CHash_ensure_Array_by_index(CHash *array , long index);

int CHash_ensure_all_types(CHash *element, short expected_type);
int CHash_ensure_all_String(CHash *element);
int CHash_ensure_all_Numbers(CHash *element);
int CHash_ensure_all_Bool(CHash *element);


int CHash_ensure_min_size(CHash *iterable,long min);
int CHash_ensure_min_size_by_key(CHash  *object, const char *key,long min);
int CHash_ensure_min_size_by_index(CHash  *array, long index,long  min);

int CHash_ensure_size(CHash *iterable,long size);
int CHash_ensure_size_by_key(CHash  *object, const char *key,long size);
int CHash_ensure_size_by_index(CHash  *array, long index,long  size);

int CHash_ensure_max_size(CHash *iterable,long max);
int CHash_ensure_max_size_by_key(CHash  *object, const char *key,long max);
int CHash_ensure_max_size_by_index(CHash  *array, long index,long  max);





int privateCHash_ensureArrayOrObject(CHash *element);
