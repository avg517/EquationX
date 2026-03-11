#include "graph_generator.h"
#include <iostream>

int main(){
    
    int** graph = calculate_first_degree(0,5,2,4);
    for(int i=0;i<6;i++){
        std::cout<<graph[0][i]<<" ";
        std::cout<<graph[1][i]<<std::endl;
    }
    
    return 0;
}