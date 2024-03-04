

typedef struct privateCHashError{
    CHash *args;
    int error_code;
    CTextStack * error_mensage;
}privateCHashError;

privateCHashError * privatenewCHashError(CHashObject *args, int error_code, const char *error_menssage);

CTextStack * privateCHashError_create_menssage(CHashObject *args, int error_code, const char *error_mensage);

void CHash_generate_custom_error(CHash  *self, CHashArray *error);

void CHash_generate_custom_error_cleaning_args(CHash  *self, CHashArray *error);


void privateCHashError_free(privateCHashError *self);

bool Chash_errors(CHash *self);

#define CHash_protected(element) if(!Chash_errors(element))

#define CHash_catch(element) if(Chash_errors(element))


void CHash_raise_error(CHash *self,int error_code,const char *error_menssage, CHash *args);

void CHash_raise_error_by_key(CHash *self,const char *key, int error_code,const char *error_menssage, CHash *args);

void CHash_raise_error_by_index(CHash *self,long index, int error_code,const char *error_menssage, CHash *args);


char * CHash_get_error_menssage(CHash *self);


int CHash_get_error_code(CHash *self);

CHash * CHash_get_error_args(CHash *self);


privateCHashError * privateCHashError_get_error(CHash *self);