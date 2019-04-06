
#include <stdio.h>
#include <stdlib.h>

double function(double x, double y){
	return 2*x*y;
}



int main (int argc, char **argv){

	double upperlimitx, lowerlimitx, upperlimity, lowerlimity;
	double dx,dy;
	double sum;
	double x;
	double y;
	int i,j;
	double numItsx,numItsy;


	dx = 0.002;
	dy = 0.002;

if (argc==2){
	sum = 0.0;
	dx = atof(argv[1]);
	dy = dx;

	upperlimity = 10.0;
	lowerlimity = 0.0;
	numItsy = (upperlimity - lowerlimity)/dy;

	for (j=0;j<(int)numItsy;j++){
		y=lowerlimity + (double)j*dy;

		lowerlimitx = 0.0;
		upperlimitx = 4.0*y;
		numItsx = (upperlimitx - lowerlimitx)/dx;

		if ((j%500)==0){
			printf("%d ",j);
			fflush(stdout);
		}

		for (i=0;i<(int)numItsx;i++){
			x=lowerlimitx + (double)i * dx;
			sum = sum + function(x,y)*dx*dy;
		}// for i
	}// for j

	printf("\nsum = %f\n",sum);

} else {
printf ("usage\n");
}
return 0;

}// main
