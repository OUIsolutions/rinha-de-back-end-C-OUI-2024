

typedef struct CHashNamespace{


    CHash * (*load_from_cJSON)(cJSON *element);
    CHash * (*load_from_json_strimg)(const char *element);
    CHash * (*load_from_json_file)(const char *filename);


    cJSON * (*dump_to_cJSON)(CHash *element);
    char * (*dump_to_json_string)(CHash * element);
    int  (*dump_to_json_file)(CHash *element,const char *filename);
    void (*set)(CHash *self,CHash *element);


    CHash * (*newBool)(bool value);
    bool (*toBool)(CHash *element);
    int (*convert_toBool)(CHash *self);
    bool (*toBool_converting)(CHash *self);

    void (*set_Bool)(CHash *self, bool value);



    CHash * (*newNumber)(double value);
    double  (*toNumber)(CHash *element);
    void (*set_Number)(CHash *self,double  value);
    int (*convert_toNumber)(CHash *self);
    double  (*toNumber_converting)(CHash *self);


    CHash * (*newStackString)(CTextStack *element);
    CTextStack  *(*toStack)(CHash *element);
    void (*set_String)(CHash *self, const char *value);
    void (*set_Stack)(CHash *self,CTextStack *element);


    CHash * (*newString)(const char *value);
    char * (*toString)(CHashArray *element);
    CHash * (*newNULL)();

    void (*print)(CHash *self);
    CHashArray * (*get_path)(CHash *self);
    CHash * (*copy)(CHash *self);

    bool (*errors)(CHash *self);
    char * (*get_error_menssage)(CHash *self);
    int (*get_error_code)(CHash *self);
    CHash * (*get_error_args)(CHash *self);



    bool (*equals)(CHash *element1, CHash *element2);

    long (*get_size)(CHash *self);

    short (*get_type)(CHash *self);


    void (*free)(CHash *self);

    CHashObjectModule  object;
    CHashArrayModule array;
    CHashValidatorModule validator;
}CHashNamespace;

CHashNamespace newCHashNamespace();