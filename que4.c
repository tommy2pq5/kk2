/* program2-9A */
/* クランク・ニコルソン法による熱伝導方程式の数値解法
	参考：堀之内・酒井・榎園、ANSI Cによる数値計算法入門（第2版）、森北出版、2002） */
/* 9.12式 */
	
#include <stdio.h>
#include <math.h>

#define G1(t) 100.0
#define G2(t) 100.0

#define F1(x) 0.0
#define F2(x) x
#define F3(x) -x+2
#define N 30

void fgusj(int n, double b[][N+2], double e[][2*N+2]){
	int i,j,k,l;
	double d,e2;
	for(i=1;i<=n+1;i++){
		for(j=1;j<=n+1;j++){
			e[i][j]=b[i][j];
			if(i==j) e[i][n+1+j]=1.0;
			else	e[i][n+1+j]=0.0;
		}
	}
	for(i=1;i<=n+1;i++){
		d=e[i][i];
		for(j=i;j<=2*n+2;j++){e[i][j]=e[i][j]/d;}
		for(k=1;k<=n+1;k++){
			if(k==i) continue;
			e2=e[k][i];
			for(l=1;l<=2*n+2;l++) e[k][l]=e[k][l]-e[i][l]*e2;
		}
	}
}

int main(void){
	int i,j,k,kosu,m,n;
	double c,b2,hx,ht,t,s,p,q,x;
	static double a[5],z[N+2][N+2], b[N+2][N+2];
	static double e[N+2][2*N+2];
	char qq,zz;
	
	char filename[20];
	FILE *fp;
	
	
	printf("このプログラムは、熱伝導方程式\n\n");
	printf("	Zt = c Zxx	（cは定数）\n\n");
	printf("を次の境界条件および初期条件：\n\n");	
	printf("境界条件：Z (0,t) = g1(t), Z (a,t) = g2(t)\n");
	printf("初期条件：Z (x,0) = f(x)\n\nのもとに");
	printf("クランク・ニコルソン法で解きます。");
	printf("\n\n境界条件 G1(t), G2(t)はマクロ定義");
	printf("で設定済みです\n\n");
	printf("次に必要事項を入力します");
	printf("エンターキーを押してください\n");
	scanf("%c",&zz);
	while(1){
		printf("f(x)はいくつの分岐から成り立ちますか。\n\n");
		printf("\n	（分岐数は3以下とする）\n");
		scanf("%d%c",&kosu,&zz);
		a[0]=0.0;
		for(i=1;i<=kosu;i++){
			printf("f%1d(x)=F%1d(x)と認証済み",i,i);
			printf("	[%5.2lf, a]の a = ",a[i-1]);
			scanf("%lf%c",&a[i],&zz);
		}
		printf("\n以下の値を入力してください。\n");
		printf("熱伝導方程式の定数	c=");
		scanf("%lf%c",&c,&zz);
		printf("時間軸の区間 [0, t] t=");
		scanf("%lf%c",&b2,&zz);
		printf("xの刻み幅	hx=");
		scanf("%lf%c",&hx,&zz);
		printf("tの刻み幅	ht=");
		scanf("%lf%c",&ht,&zz);
		printf("正しく入力されましたか。(y/n)");
		scanf("%c%c",&qq,&zz);
		if(qq=='y') break;
	}
	m=b2/ht;	n=a[kosu]/hx;
	
	/* 初期条件より t=0 における値を代入する */
	for(i=1; i<=n-1; i++){
		x=a[0]+hx*(double)i;
		if(x <= a[1]){ z[i][0] = F1(x); continue;}
		if(x <= a[2]){ z[i][0] = F2(x); continue;}
		if(x <= a[3]){ z[i][0] = F3(x);}
	}
	
	/* 境界上家円より x=0, x=aにおける値を代入する */
	for(j=0; j<=m; j++){
		t = ht*(double)j;
		z[0][j] = G1(t);
		z[n+1][j]=G2(t);
	}
	s=(hx*hx)/(c*ht);
	p=2.0*(1.0+s); q=2.0*(1.0-s);
	b[1][1]=1.0;	b[n+1][n+1]=1.0;
	for(i=2; i<=n; i++){
		b[i][i-1]=1.0;
		b[i][i]=-p;
		b[i][i+1]=1.0;
	}
	fgusj(n, b, e);
	/* Z(x,ｔ）の値を求める */
	for(j=1; j<=m; j++){
		b[1][n+2]=z[0][j];
		b[n+1][n+2]=z[n+1][j];
		for(i=2; i<=n; i++){
			b[i][n+2]=-z[i-2][j-1]+q*z[i-1][j-1]-z[i][j-1];
		}
		for(i=0; i<=n; i++){
			s=0.0;
			for(k=1; k<=n+1; k++){
				s += e[i+1][n+1+k]*b[k][n+2];
			}
			z[i][j]=s;
		}
	}
	printf("\n計算を終了しました。結果を出力します。\n");
	
	

	
	printf("データを書き込むファイル名を入力してください。（20字以内)\n");
	scanf("%s",filename);
	
	fp=fopen(filename, "w");
	
	/*
	fprintf(fp,"\n熱伝導方程式 Z t = %2.0lfZ x x の",c);
	fprintf(fp,"クランクニコルソン法による数値解\n\n");
	*/
	
	fprintf(fp, "t/x");
	for(i=0; i<=n; i++){
		fprintf(fp, " %7.4lf",hx*(double)i);
	}
	fprintf(fp,"\n");
	for(j=0; j<=m; j++){
		fprintf(fp, "%7.4lf",ht*(double)j);
		for(i=0; i<=n; i++){
			fprintf(fp," %7.4lf",z[i][j]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
	return 0;
}