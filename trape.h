/* trape.h ‘äŒ`Œö®‚É‚æ‚é”’lÏ•ª */
double trape(double a, double b, int n, double (*func)(double)){
	double s,x,h;
	int i;
	
	h=(b-a)/n;
	s=0;
	
	for(i=1;i<n;i++){
		x=a+h*i;
		s+=(func)(x);
	}
	s=h/2.0*((func)(a)+2*s+(func)(b));
	return s;
}