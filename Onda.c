#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main(){
	int x_min1=0;
	int n_x2=101;
	int n_y2=101;
	int n_t2=101;
	int n_t1=100000;
	int n_x1 = 129;
	int lx2= 0.5;
	int ly2= 0.5;
	double dt1=0.00001;
	double dt2=0.00001;
	double dx1=0.005;
	double dx2=lx2/(n_x2-1);
	double dy2=ly2/(n_y2-1);
	double c1=250;
	double r1 = c1*dt1/dx1;
	double cf1 = 0;
	double cf2 = 0;
	double v1;
	double v2;
	double v3;
	double v4;
	double rx, ry;
	double matriz3[n_t2][n_x2][n_y2];
	rx= pow(c1*dt2/dx2, 2.0);
	ry= pow(c1*dt2/dy2, 2.0);
	double ** matriz1 = malloc(n_t1*sizeof(double));
	double ** matriz2 = malloc(n_t1*sizeof(double));

	for (int i=0;i<n_t1;i++)
	{
		matriz1[i]=malloc(n_x1*sizeof(double));
		matriz2[i]=malloc(n_x1*sizeof(double));
	}

	FILE *in;
	in = fopen("cond_ini_cuerda.dat", "r");
	if(!in){
		printf("problems opening");
		exit(1);
	}
	printf("I'm reading");

	for (int i=0;i<n_x1+1;i++){
		fscanf(in, "%lf %lf \n",&v1, &v2);
		matriz1[1][i]=v2;
		matriz1[0][i]=v2;
		matriz2[1][i]=v2;
		matriz2[0][i]=v2;
	}
	
	for(int i=1;i<(n_t1-1);i++){
		matriz1[i][n_x1-1] = cf2;
		matriz1[i][0] = cf1;
		matriz2[i][0]= cf1;
		matriz2[i][n_x1-1]= sin((2*M_PI*c1/0.64)*dt1*i);
		for (int j=1;j<(n_x1-1);j++){
			matriz1[i+1][j]=2*matriz1[i][j]-matriz1[i-1][j]+pow(r1,2)*(matriz1[i][j+1]-2*matriz1[i][j]+matriz1[i][j-1]) ;
			matriz2[i+1][j]=2*matriz2[i][j]-matriz2[i-1][j]+pow(r1,2)*(matriz2[i][j+1]-2*matriz2[i][j]+matriz2[i][j-1]) ;
		}
		
	}
	in = fopen("resultado","w");
	if(!in){
	printf("can't open file %s\n","resultado");
	exit(1);
	}
	for(int j=0;j<n_x1;j++){
	fprintf(in,"%f %f\n",matriz1[n_t1-1][j], matriz2[n_t1-1][j]);
	}	
	fclose(in);
	return 0;
	FILE *in1;
	in = fopen("cond_ini_tambor.dat", "r");
	if(!in1){
		printf("problems opening");
		exit(1);
	}
	printf("I'm reading");

	for (int i=0;i<n_x1+1;i++)
	{
		for(int j=0;j<n_x1+1;j++)
		{
			fscanf(in1, "%lf %lf \n",&v3, &v4);
			matriz3[1][i][j]=v4;
			matriz3[0][i][j]=v4;
		}
		
	}
	
	for(int i=1;i<(n_t1-1);i++){
		matriz3[i][0][0] = cf2;
		matriz3[i][n_x2][n_y2] = cf1;
		for (int j=1;j<(n_x1-1);j++)
		{
			for(int k=1;k<(n_y2-1);k++)
			{
				matriz3[i+1][j][k]=2*matriz3[i][j][k]-matriz3[i-1][j][k]+pow(r1,2)*(matriz3[i][j+1][k]-2*matriz3[i][j][k]+matriz3[i][j-1][k])+ 2*matriz3[i][j][k]-matriz3[i-1][j][k]+pow(r1,2)*(matriz3[i][j][k+1]-2*matriz3[i][j][k]+matriz3[i][j][k-1]);
			}
		}
		
	}
	in1 = fopen("resultadoT","w");
	if(!in1){
	printf("can't open file %s\n","resultadoT");
	exit(1);
	}
	for(int j=0;j<n_x2;j++)
	{
		for(int k=0;k<n_y2;k++)
	fprintf(in1, "%f\n",matriz3[n_t2-1][j][k]);
	}	
	fclose(in1);
	return 0;
}

