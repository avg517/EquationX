#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"
#include "tokenizer.h"
#include <stddef.h>
void appendchrtostr(char** str,const char chr){
        size_t len=strlen(*str);
        char* temp=realloc(*str, len+2);
        temp[len]=chr;
        temp[len+1]='\0';
        *str=temp;
}//appending a character to array

void appendinttoarray(size_t cnt,int** arr,const int toappend){
        int* temp=realloc(*arr, sizeof(int)*(cnt+1));
        temp[cnt]=toappend;
        *arr=temp;
}//appending int to an array
void appendarrtomat(size_t rows,char*** strings,char* str){
        if (!str) {return;}
        char** temp=realloc(*strings, (rows+1)*sizeof(char*));
        if (!temp){
                fprintf(stderr,"failed to reallocate memory");
                return;
        }
        size_t len=strlen(str);
        temp[rows]=malloc(len+1);
        if (!temp[rows]){
                fprintf(stderr,"failed to allocate new memory\n");
                return;
        }
        strcpy(temp[rows], str);
        *strings=temp;
}//appending an array to a matrix

void free_tokens(int *identifiers, char** commands, int num_tokens) {
        if (commands) {
                for (int i = 0; i < num_tokens; ++i) {
                        free(commands[i]);
                        commands[i]=NULL;
                }
                free(commands);
                commands=NULL;
        }
        free(identifiers);
        identifiers=NULL;
}//free za tokens
int tokenize(const char* str,int strsz,int** identifiers,char*** command,int* numoftokens){
        char* temp = malloc(1);
        temp[0] = '\0';

        for (int i=0; i<strsz; ++i) {
                char ch = str[i];

                if (isalpha(ch)) {
                        temp[0] = '\0';
                        appendchrtostr(&temp, ch);
                        ++i;
                        while (i < strsz && isalnum(str[i])) {
                                appendchrtostr(&temp, str[i]);
                                ++i;
                        }
                        appendinttoarray(*numoftokens, identifiers, identifiersign);
                        appendarrtomat(*numoftokens, command, temp);
                        (*numoftokens)++;
                        i--;
                } else if (isdigit(ch)) {
                        temp[0] = '\0';
                        appendchrtostr(&temp, ch);
                        appendinttoarray(*numoftokens, identifiers, numbersign);
                        ++i;
                        while (i < strsz && (isdigit(str[i]) || str[i]=='.')) {
                                appendchrtostr(&temp, str[i]);
                                ++i;
                        }
                        appendarrtomat(*numoftokens, command, temp);
                        (*numoftokens)++;
                        i--;
                } else if (ispunct(ch)){
                        temp[0] = '\0';
                        appendchrtostr(&temp, ch);
                        switch (ch) {
                                case ';':
                                        appendinttoarray(*numoftokens,identifiers, semicolonsign);
                                break;
                                case ',':
                                        appendinttoarray(*numoftokens,identifiers, commasign);
                                break;
                                case '{':
                                        appendinttoarray(*numoftokens,identifiers, obracketsign);
                                break;
                                case '}':
                                        appendinttoarray(*numoftokens,identifiers, cbracketsign);
                                break;
                                case '(':
                                        appendinttoarray(*numoftokens,identifiers, oparantesesign);
                                break;
                                case ')':
                                        appendinttoarray(*numoftokens,identifiers, cparantesesign);
                                break;
                                case '>':
                                        if (i+1<strsz && str[i+1]=='='){
                                                appendinttoarray(*numoftokens, identifiers, greaterequsign);
                                                ++i;
                                        } else {
                                                appendinttoarray(*numoftokens, identifiers, greatersign);
                                        }
                                break;
                                case '<':
                                        if (i+1<strsz && str[i+1]=='='){
                                                appendinttoarray(*numoftokens, identifiers, lessequ);
                                                ++i;
                                        } else {
                                                appendinttoarray(*numoftokens, identifiers, lesssign);
                                        }
                                break;
                                case '=':
                                        if (i+1<strsz && str[i+1]=='='){
                                                appendinttoarray(*numoftokens, identifiers, equalequsign); 
                                                ++i;
                                        } else {
                                                appendinttoarray(*numoftokens, identifiers, equalsign);
                                        }
                                break;
                                case '[':
                                        appendinttoarray(*numoftokens,identifiers, osquarebracket);
                                break;
                                case ']':
                                        appendinttoarray(*numoftokens,identifiers, csquarebracket);
                                break; 
                                case '+':
                                        appendinttoarray(*numoftokens,identifiers, addsign); 
                                break;
                                case '-':
                                        appendinttoarray(*numoftokens,identifiers, minussign);
                                break;
                                case '*':
                                        appendinttoarray(*numoftokens,identifiers, multiplysign);
                                break;
                                case '/':
                                        appendinttoarray(*numoftokens,identifiers, dividesign); 
                                break;
                                case '%':
                                        appendinttoarray(*numoftokens, identifiers, modsign);
                                break;
                                case '\'':
                                        appendinttoarray(*numoftokens,identifiers, apostrophe);
                                break;
                                case '\"':
                                        appendinttoarray(*numoftokens,identifiers, quotation); 
                                break;
                                case '\\':
                                        appendinttoarray(*numoftokens,identifiers,backslash);
                                break;
                                case '?':
                                        appendinttoarray(*numoftokens,identifiers,questionmark); 
                                break;
                        }
                        appendarrtomat(*numoftokens, command, temp);
                        (*numoftokens)++;
                }
        }

        free(temp);
        return 0;
}

