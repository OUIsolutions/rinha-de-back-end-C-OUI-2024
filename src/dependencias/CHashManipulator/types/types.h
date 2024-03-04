
#define CHASH_NOT_EXIST -1

enum{
    CHASH_NULL,
    CHASH_ARRAY,
    CHASH_OBJECT,
    CHASH_NUMBER,
    CHASH_BOOL,
    CHASH_STRING
};

short CHash_get_type(CHash *self);

const char  *private_Chash_convert_type(long type);
