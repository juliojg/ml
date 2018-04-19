#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


double normal(float sigma, float mu, float x){
	return (1.0 / (sigma * sqrt(2 * M_PI))) * exp(-(x - mu)*(x - mu) / (2.0 * sigma * sigma));
}



void ej_b (int n, int d, double c){ //centrada en (1,0,0,...,0) y (-1,0,0,...,0))
	FILE *fp = fopen("b_points.data", "w"); //w para poder escribir
	int total = n / 2;
	double sigma = c;
	int center;
	for (int i=0; i<total; i++){
		for (int j=0;j<d;){
			center = 0;
			if (j == 0)
				center = 1;
			double r1 = (drand48() * 10 * sigma) - (5 * sigma) + center; //mapeo a lo que abarca y "lo centro"
			double nval = normal(sigma,center,r1);
			double r2 = drand48() * 1.0/(sqrt(2*M_PI) * sigma);
			if (r2 <= nval){
				fprintf(fp, "%f, ", r1);
				j++;
			}
		}
			fprintf(fp, "1\n");
	}
	for (int i=0; i<total; i++){
		for (int j=0;j<d;){
			center = 0;
			if (j == 0)
				center = -1;
			double r1 = (drand48() * 10 * sigma) - (5 * sigma) + center; //mapeo a lo que abarca y "lo centro"
			double nval = normal(sigma,center,r1);
			double r2 = drand48() * 1.0/(sqrt(2*M_PI) * sigma);
			if (r2 <= nval){
				fprintf(fp, "%f, ", r1);
				j++;

			}
		}
			fprintf(fp, "0\n");
	}
}




int main(int argc, char **argv){

	int d = atoi(argv[1]);
	int n = atoi(argv[2]);
	double c = atof(argv[3]);
	
	time_t t;
	srand48((long int) time(&t));

	FILE *f = fopen("b_points.names", "w"); //w para poder escribir
	fprintf(f, "0,1.\n");
	for(int i='a'; i < d + 'a'; i++){
		fprintf(f, "%c: continuous.\n", (char)i);
	}

	ej_b(n,d,c);

	return 0;

}
