
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592654

int main (int argc, char **argv){
	double R, a, Eq, Iq, q, t, dy, dt, r, y;
	unsigned int i, j;
	unsigned int numysteps;
	unsigned int numtsteps;


if (argc==4){
	R = atof(argv[1]);
	a = atof(argv[2]);
	q = atof(argv[3]);
	// convert q to radians
	q = q*PI/180.0;

	numysteps = 100;
	numtsteps = 100;

	dt = 1/(double)numtsteps;
	dy = 1/(double)numysteps;

	Iq=0; // intensity at some angle q
	for (j=0;j<numtsteps;j++){
		t = dt*(double)j;
		Eq = 0;
		for (i=0;i<numysteps;i++){
			y = (-1.0*a/2.0) + dy *(double)i;
			r = sqrt(pow(R,2.0) + pow(y,2.0) - 2*y*R*sin(q));
			Eq+=((sin(2*PI*(t - r)))*dy)/r;
//			printf("%f %f\t",r,Eq);
		}
		Iq+= pow(Eq,2.0)*dt;
		printf("%d\t%e\n",j,Iq);
	}

	printf("R=%f\ta=%f\tq=%fradians\n",R,a,q);

} else {
	printf ("usage: ./calcIntensity <R> <a> <theta(degrees)> \n");
}
return 0;

}// main
