#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

float spiral1 (float t){ //ro = theta/4pi y ro = (theta + pi)/4pi
	return t / (4 * M_PI);
}

float spiral2 (float t){
	return (t + M_PI) / (4 * M_PI);
}

void cartopol(float x, float y, float *r, float *t){
	*r = sqrt(x*x + y*y);
	*t = atan2(y,x);
}

int check_c (float x, float y){
	float angle, mod;
	cartopol(x,y,&mod,&angle); // en angle y mod están los resultados
	float m1 = spiral1(angle);
	float m2 = spiral2(angle);
	if (m1 < m2){
		float c = m2 - m1;
		if (mod < m1)
			return 0;
		if (mod < m2)
			return 1;
		if (mod < m2+c)
			return 0;
		if (mod < m2+2*c)
			return 1;
		if (mod < m2+3*c)
			return 0;
		if (mod < m2+4*c)
			return 1;
	}
	else{
		float c = m1 - m2;
		if (mod < m2)
			return 0;
		if (mod < m1)
			return 1;	
		if (mod < m1+c)
			return 0;
		if (mod < m1+2*c)
			return 1;
		if (mod < m1+3*c)
			return 0;
		if (mod < m1+4*c)
			return 1;
	}

}

void ej_c (int n){
	time_t t;
	srand48((long int) time(&t));
	int total = n/2;
	FILE *fp = fopen("c_points.data", "w");

	int classA = 0;
	int classB = 0;

	//fprintf(fp, "x,y,c\n"); //para R
	while(classA<total || classB<total){
		float r1 = drand48() * 2.0 - 1.0;
		float r2 = drand48() * 2.0 - 1.0;	
		float mod = r1 * r1 + r2 * r2;
		int c = check_c(r1,r2);

		if (mod <= 1.0){
			if (c == 0 && classA<total){
				classA++;	
				fprintf(fp, "%f, %f, %d\n", r1, r2, c);
			}
			if (c == 1 && classB<total){
				classB++;
				fprintf(fp, "%f, %f, %d\n", r1, r2, c);
			}
		}
	}
}

int main(int argc, char **argv){

	int n = atoi(argv[1]);

	FILE *f = fopen("c_points.names", "w"); //w para poder escribir
	fprintf(f, "0,1.\n");
	fprintf(f, "a: continuous.\n");
	fprintf(f, "b: continuous.\n");


	time_t t;
	srand48((long int) time(&t));

	ej_c(n);




	return 0;

}
