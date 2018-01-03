/* kk2rep2 que1.c */

#include <stdio.h>
#include <math.h>

#define N 10

double x[N], y[N];
double a0, a1;
double cxy;

int main(void){
	double mx=0,my=0;
	double sxy=0,sx=0,sy=0;
	double r;
	int i;

	FILE *fp;
	fp=fopen("data.txt","r");

	for(i=0; i<N; i++){
		fscanf(fp, "%lf %lf", &x[i], &y[i]);
	}
	fclose(fp);

	printf("%3s %8s %8s\n","i", "x[i]", "y[i]");
	for(i=0; i<N; i++){
		printf("%3d %8.1lf %8.2lf\n",i, x[i], y[i]);
	}

	/* mean */
	for(i=0; i<N; i++){
		mx += x[i];
		my += y[i];
	}
	mx = mx/(double)N;
	my = my/(double)N;

	printf("mx=%lf\nmy=%lf\n",mx,my);

	/*  */
	for(i=0; i<N; i++){
		sx  += pow(x[i]-mx, 2);
		sy  += pow(y[i]-my, 2);
		sxy += (x[i]-mx)*(y[i]-my);
	}
	printf("sx=%lf\nsy=%lf\nsxy=%lf\n",sx,sy,sxy);

	/*  */
	a1=sxy/sx;
	a0=my-a1*mx;

	printf("y = f(x) = %lf + %lf * x\n",a0, a1);
	
	/*  */
	r=sxy/sqrt(sx*sy);
	printf("r=%lf",r);

	return 0;
}