
typedef struct CHashObjectModule{

    CHashObject  * (*newObjectEmpty)();
    void  (*set_any)(CHashObject * self, const char *key, CHash *element);
    void  (*set_long)(CHashObject * self, const char *key, long value);
    void  (*set_double)(CHashObject * self, const char *key, double value);
    void  (*set_bool)(CHashObject * self, const char *key, bool value);
    void  (*set_string)(CHashObject * self, const char *key, const char *value);
    void  (*set_Stack)(CHashObject * self, const char *key,CTextStack *stack_value);


    void  (*set_default)(CHashObject * self, const char *key, CHash *element);

    void  (*remove)(CHashObject *self, const char *key);

    char * (*get_key_by_index)(CHashObject *self,long index);

    char   * (*get_key_of_element)(CHash *self);

    short  (*get_type)(CHashObject *self, const char *key);
    bool (*exist)(CHashObject *self, const char *key);

    CHash * (*get)(CHashObject * self, const char *key);

    CHashArray * (*getArray)(CHashObject * self, const char *key);

    CHashObject * (*getObject)(CHashObject * self, const char *key);

    double (*getNumber)(CHashObject * self, const char *key);
    double (*getNumber_converting)(CHashObject * self, const char *key);

    bool (*getBool)(CHashObject * self, const char *key);
    bool (*getBool_converting)(CHashObject * self, const char *key);

    char  * (*getString)(CHashObject * self, const char *key);
    CTextStack * (*getStack)(CHashObject * self, const char *key);



}CHashObjectModule;

CHashObjectModule newCHashObjectModule();