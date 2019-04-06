#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592654

int main (int argc, char **argv){
	double R, a, Eq, Iq, q, t, dy, dt, r, y, Eo;
	unsigned int i, j,k;
	unsigned int numysteps;
	unsigned int numtsteps;
	FILE *fp;
	char filename[32];

if (argc==4){
	R = atof(argv[1]);
	a = atof(argv[2]);
	strcpy(filename,argv[3]);
	fp = fopen(filename,"w");
	if (!fp){
		printf("unable to open file %s\n",filename);
		return 1;
		}

	printf("R=%.2f\ta=%.2f\n",R,a);
	fprintf(fp,"R=,%.2f,a=,%.2f\n",R,a);

	Eo = 100.0;// overall radiator strength. this just sets scale
	numysteps = 100;
	numtsteps = 100;
	dt = 1/(double)numtsteps;// assume period T=1
	dy = a/(double)numysteps;
	for (k=0;k<(90*4);k++){ //angle.  x 4 for  every 0.25 degrees
	q =((double)k)*PI/(180.0*4.0);// convert k in degrees to radians
	// Point P is at distance R at angle q from the perpendicular center line

	Iq=0; // intensity at point P.  Set this to zero in preperation for integration
	for (j=0;j<numtsteps;j++){
		t = dt*(double)j;
		Eq = 0;// electric field at some angle q. Initialize in prep for integration
		for (i=0;i<numysteps;i++){
			y = (dy *(double)i)-(a/2.0);  // y is variable describing where the position of the radiator at dy
			r = sqrt(pow(R,2.0) + pow(y,2.0) - 2.0*y*R*sin(q));// law of cosines to compute actual distance to point P
			Eq+=Eo*((sin(2*PI*(t - r)))*dy)/r;// discrete adding 
			// the i loop will give Σ Eo/r sin(2πt/T - 2πr/lambda) δt
			// using T=1 and lambda =1
		}
		Iq+= pow(Eq,2.0)*dt; // discrete adding.  The j loop will give Σ<E²>δt
	}
// print to screen and write to file
	printf("%.2f deg\t%e\n",q*180.0/PI,Iq);
	fprintf(fp,"%.2f,%e\n",q*180.0/PI,Iq);
	}
	fclose(fp);
} else {
	printf ("usage: ./singleSlitCalc <R> <a> filename\n");
}
return 0;
}// main
