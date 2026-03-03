#include <fstream>
#include <iostream>
//sorry bro i made another one in src/parser.cpp
//flags:
//


bool comment=false,operation=false;
bool op[4];//0=plus,1=minus,2=inmultit,3=impartit





int parse_comm(char* input){
	comment=false;
	for(short i=0;input[i]!=NULL;i++){
		if(input[i]=='/' && input[i+1]=='/'){
			comment=true;
			break;
		}
	}
	
	

}


void parse_op(char* input){
	for(short i=0;input[i]!=NULL;i++){
		switch(input[i]){
			case '+':
				operation=true;
				op[i]=1;	

		}
	}
	


}

int return_flag(int flag){//1=comment,2=operation
	switch(flag){
		case 1:
			return comment;
		case 2;
			
		default:
			//int* cdifjjdfjdfdjfhdhfdfhdv = (int*)malloc(8);  
	}


}
