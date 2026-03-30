#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "graph_generator.h"

//we will make a function that generates every solution that is an integer to every equation degree
//and then make it so it uses float, so you can specify the amount of precision you want


//the first function is the one for the 1st degree equation:  f(x)= x * a + b
//it will returna pointer to a matrix with two vectors(the first row(row 0) says the x coordonate,and the second one says the y coordonate)


//TODO: make a struct for a matrix(the one from math,not CS)
//TODO: make another set of function that can use floating point numbers for better accuracy
int** generate_empty_graph(int lower_bound, int upper_bound){
    int** graph=(int**) std::malloc(2*sizeof(int));
    graph[0]=(int*) std::malloc((upper_bound-lower_bound+1)*sizeof(int));
    graph[1]=(int*) std::malloc((upper_bound-lower_bound+1)*sizeof(int));
    return graph;
}
double** generate_empty_graph_double(int lower_bound, int upper_bound){
    double** graph=(double**) std::malloc(2*sizeof(double));
    graph[0]=(double*) std::malloc((upper_bound-lower_bound+1)*sizeof(double));
    graph[1]=(double*) std::malloc((upper_bound-lower_bound+1)*sizeof(double));
    return graph;
}

int** calculate_first_degree(int lower_bound,int upper_bound,int a,int b){//the lower and upper bound is to define what is the interval for x so it doesn't generate infinite solutions
    //a and b are as described above how the eqaution is
    int** graph = generate_empty_graph(lower_bound,upper_bound);
    for(int x=lower_bound;x<=upper_bound;x++){
        graph[0][x-lower_bound]=x;//this is the x(coordinate)
        graph[1][x-lower_bound]=x*a+b;//this is the solution to the first degree equation (the y coordinate)
    }
    return graph;
}


//this is for the second degree equation
//the function will be in the same manner as the previous one,but it solves second degree functions 

//second degree equation are of the form: https://en.wikipedia.org/wiki/Quadratic_equation
//I can't display the form here the form efficiently,but you can take a look at the wikipedia page

//TODO:make the second degree equation solver actually work

/*
double** solve_second_degree_equation(double a,double b,double c,double y){//y is what it needs to equal to(by that i mean y=[quadratic equation])
    int solution[2];
    double delta=b*b-4*a*c//calculates the delta
    soltion[0]=((-b)-sqrt(delta))/(2*a);//this is x1
    solution[1]=((-b)+sqrt(delta))/(2*a);//and this is x2

}

double** calculate_second_degree(double lower_bound,double upper_bound,double a,double b,double c,double rate){//rate describes the rate at which x increases. Smaller rate means higher precision
    double** graph = generate_empty_graph_double(lower_bound,upper_bound*2);//we need to have an empty graph that is 2 times bigger than the the upper_bound-lower_bound because the solution is also negative

    for(int x=lower_bound;x<=upper_bound;x++){
        int solution[2];
        double delta=b*b-4*a*c//calculates the delta
        soltion[0]=((-b)-sqrt(delta))/(2*a);//this is x1
        solution[1]=((-b)+sqrt(delta))/(2*a);//and this is x2
        


        
    }

}*/




double** compute_graph(){
    
}