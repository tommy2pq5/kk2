#include <stdio.h>
#include <math.h>
#include "trape.h"
#include "simps.h"

int div[3]={10,30,50}; 

double prim_f(double x){
	return x;
	//return log(x+sqrt(9+x*x));
}

double f(double x){
	return x*exp(x);
	//return 1/sqrt(9+x*x);
}

int main(void){
	double a=0,b=1;
	int i;
	double st,ss,strue;
	double rerr_tr,rerr_si;
	
	strue=prim_f(b)-prim_f(a);

	printf("%3s,%10s,%10s,%10s,%10s,%10s\n","div", "trape", "simps", "true", "rerr(tra)", "rerr(sim)");	
	for(i=0;i<3;i++){
		st=trape(a,b,div[i],f);
		ss=simps(a,b,div[i],f);
		rerr_tr=(st-strue)/strue*100;
		rerr_si=(ss-strue)/strue*100;
		printf("%3d,%10lf,%10lf,%10lf,%10lf,%10lf\n",div[i], st, ss, strue, rerr_tr, rerr_si);
	}

	return 0;
}