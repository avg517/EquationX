#include <bits/stdc++.h>
#include <ncurses.h>
//#include <thread.h>


unsigned char* generate_grafica(){
    unsigend char* grafica =(unsigned char*) malloc(257*sizeof(char));
	for(int j=0x1;j<=0xFF;j+=0x1){
		grafica[j]=j;
    }
    return grafica;
}

void render(unsigned char** buffer, unsigned char** grafica){
	
	grafica[0]=0x80;
	
	unsigned short x,y;
	refresh();
	move(1,1);
	x=1;
	y=1;
	for(y=1;y<=y_res;y++){
		for(x=1;x<=x_res;x++){
			
			addch(grafica[buffer1[x][y]]);
			if(x==x_res){
				move(y+1,1);
			}
		}

	}

	refresh();
}

void print_text(int x,int y,string mesaj){ //o functie care ia cate un char dintr-un string care ii dai,ii zici la ce pozitie sa inceapa si dupa trece prin fiecare caracter si il adauga la buufer

	//mesaj.at(0)   asa iei primul caracter din string
	for(int i=0;i<mesaj.size();i++){
		//printw("ola");
		buffer[x+i][y]=mesaj.at(i);    //ihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyouihateyou
	}

}


void debug(){

	print_text(4,4,200);//fuck you
}




void initial_setup(){
		generate_grafica();
		initscr();//e pentru ncurses
		noecho();//face uncat ce scrii sa nu fie scris pe ecran
		raw();
}

