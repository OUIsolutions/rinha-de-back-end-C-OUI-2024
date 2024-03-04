


CHashObject* privatenewCHashObject(void * sentinel, ...);
#define newCHashObject(...) privatenewCHashObject(NULL,__VA_ARGS__,NULL)

CHashObject  * newCHashObjectEmpty();

void  CHashObject_set_any(CHashObject * self, const char *key, CHash *element);
void  CHashObject_set_long(CHashObject * self, const char *key, long value);
void  CHashObject_set_double(CHashObject * self, const char *key, double value);
void  CHashObject_set_bool(CHashObject * self, const char *key, bool value);
void  CHashObject_set_string(CHashObject * self, const char *key, const char *value);
void  CHashObject_set_Stack(CHashObject * self, const char *key,CTextStack *stack_value);



void  privateCHashObject_set(CHashObject *self , ...);
#define  CHashObject_set_many(self,...)privateCHashObject_set(self,__VA_ARGS__,NULL)

void  CHashObject_set_default(CHashObject * self, const char *key, CHash *element);

void  CHashObject_remove(CHashObject *self, const char *key);

CHash * privateCHashObject_get_by_key_or_null(CHashObject * self, const char *key);

bool CHashObject_exist(CHashObject *self, const char *key);



char * CHashObject_get_key_by_index(CHashObject *self,long index);


char   * CHashObject_get_key_of_element(CHash *self);


short  CHashObject_get_type(CHashObject *self, const char *key);

CHash * CHashObject_get(CHashObject * self, const char *key);


CHashArray * CHashObject_getArray(CHashObject * self, const char *key);

CHashObject * CHashObject_getObject(CHashObject * self, const char *key);


double CHashObject_getNumber(CHashObject * self, const char *key);

double CHashObject_getNumber_converting(CHashObject * self, const char *key);

bool CHashObject_getBool(CHashObject * self, const char *key);

bool CHashObject_getBool_converting(CHashObject * self, const char *key);


char  * CHashObject_getString(CHashObject * self, const char *key);


CTextStack * CHashObject_getStack(CHashObject * self, const char *key);
