#include <fstream>
#include <iostream>
#include <string>
extern "C" {
        void free_tokens(int *identifiers,char** commands,int num_tokens);
        void tokenize(const char* str,int strsz,int** identifiers,char*** command,int *numoftokens);
}
int main(){
        std::ifstream fin("tokenizer.cpp");
        std::string str;
        int toks=0;
        int *identifier=NULL;
        char** commands=NULL;
        while (std::getline(fin,str)){
                tokenize(str.c_str(), str.size(),&identifier, &commands, &toks);
        }
        for (int i=0;i<toks;++i){
                std::cout<<commands[i]<<" = "<<identifier[i]<<"\n";
        }
        free_tokens(identifier,commands, toks);

}
