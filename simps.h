/* simps.h ƒVƒ“ƒvƒ\ƒ“‚ÌŒöŽ® */
double simps(double a, double b, int n, double (*f)(double)){
	double x,s,s1,s2,h;
	int i;
	
	s=s1=s2=0;
	h=(b-a)/(2*n);
	for(i=1;i<2*n;i+=2){
		x=a+i*h;
		s1+=(f)(x);
	}
	for(i=2;i<2*n;i+=2){
		x=a+i*h;
		s2+=(f)(x);
	}
	s=h/3*((f)(a)+4*s1+2*s2+(f)(b));
	return s;
}