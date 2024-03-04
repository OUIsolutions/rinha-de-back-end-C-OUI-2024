

char * CHash_toString(CHashArray *element);

CTextStack  *CHashtoStack(CHash *element);

CHash * newCHashStackString(CTextStack *element);

CHash * newCHashString(const char *value);

void CHash_set_String(CHash *self, const char *value);

void CHash_set_Stack(CHash *self,CTextStack *element);
