extern "C" {


int** generate_empty_graph(int lower_bound, int upper_bound);
double** generate_empty_graph_double(int lower_bound, int upper_bound);
int** calculate_first_degree(int lower_bound,int upper_bound,int a,int b);
//double** calculate_second_degree(double lower_bound,double upper_bound,double a,double b,double c)
void initialize_graph(double** graph,double rate,double lower_bound,double upper_bound);
void compute_graph(double** graph,int flag,double number);
double** create_graph();
int get_flag();
void add_to_graph(double** graph);


}
