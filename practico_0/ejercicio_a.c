#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//en R hacer: tbl <- read.table("a_points.cvs") y plot(tbl$V1, tbl$V2)


double normal(float sigma, float mu, float x){
	return (1.0 / (sigma * sqrt(2 * M_PI))) * exp(-(x - mu)*(x - mu) / (2.0 * sigma * sigma));
}

void ej_a (int n, int d, double c){
	FILE *fp = fopen("a_points.data", "w"); //w para poder escribir
	int total = n / 2;
	int center;
	double sigma = sqrt(d) * c;
	for (int i=0; i<total; i++){
		for (int j=0;j<d;){
			center = 1;
			double r1 = (drand48() * 10 * sigma) - (5 * sigma) + center; //mapeo a lo que abarca y "lo centro (en 1)"
			double nval = normal(sigma,center,r1); //centrada en el (1,1,...,1)
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
			center = -1;
			double r1 = (drand48() * 10 * sigma) - (5 * sigma) + center; //mapeo a lo que abarca y "lo centro"
			double nval = normal(sigma,center,r1); //centrada en el (-1,-1,...,-1)
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

	FILE *f = fopen("a_points.names", "w"); //w para poder escribir
	fprintf(f, "0,1.\n");
	for(int i='a'; i < d + 'a'; i++){
		fprintf(f, "%c: continuous.\n", (char)i);
	}

	ej_a(n,d,c);

	return 0;

}

