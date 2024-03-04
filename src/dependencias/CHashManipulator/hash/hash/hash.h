
typedef struct CHash{

    unsigned short private_type;
    unsigned short private_reference_type;

    void *private_error;
    struct CHash *private_father;

    unsigned long private_size;

    //these is the reference system
    union {
        unsigned long private_index;
        char * private_key;
    };
    //these is the values sysstem
    union {
        CTextStack  *private_value_stack;
        double private_value_double;
        bool private_value_bool;
        struct CHash **private_sub_elements;
    };

}CHash;

enum {
    PRIVATE_CHASH_NOT_A_REFERENCE,
    PRIVATE_CHASH_ARRAY_ITEM,
    PRIVATE_CHASH_KEYVAL
};

typedef CHash CHashArray;
typedef CHash CHashObject;
typedef CHash CHashArrayOrObject;
typedef  CHash CHashStringArray;

CHash * privatenewChash_raw();



void CHash_print(CHash *self);

CHashArray * CHash_get_path(CHash *self);


CHash * CHash_copy(CHash *self);

CHash * privateCHash_copy_if_its_an_reference(CHash *self);

void CHash_free(CHash *self);

void CHash_set(CHash *self,CHash *element);

void privateCHash_free_values(CHash *self);

bool CHash_equals(CHash *element1, CHash *element2);

long CHash_get_size(CHash *self);


CHash * privateCHash_get_first_object(CHash *self);

CHash * newCHashNULL();