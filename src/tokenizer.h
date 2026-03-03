#ifdef __cplusplus
extern "C" {
#endif
void appendchrtostr(char **str,const char chr);
void appendinttoarray(size_t cnt,int** arr,const int toappend);
void appendarrtomat(size_t rows,char*** strings,char* str);
int tokenize(const char* str,int strsz,int** identifiers,char*** command,int* numoftokens);
void free_tokens(int *identifiers,char** commands,int num_tokens); 
#ifdef __cplusplus
}
#endif
