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
	fprintf(fp,"R,a,q,Iq\n");

	// convert q to radians
	Eo = 100.0;

	numysteps = 100;
	numtsteps = 100;

	dt = 1/(double)numtsteps;
	dy = a/(double)numysteps;

	for (k=0;k<(90*4);k++){ //angle ; every 0.25 degrees
	q =((double)k)*PI/(180.0*4.0);// convert k in degrees to radians
	Iq=0; // intensity at some angle q
	for (j=0;j<numtsteps;j++){
		t = dt*(double)j;
		Eq = 0;// electric field at some angle q
		for (i=0;i<numysteps;i++){
			y = (dy *(double)i)-(a/2.0);
			r = sqrt(pow(R,2.0) + pow(y,2.0) - 2.0*y*R*sin(q));
			Eq+=Eo*((sin(2*PI*(t - r)))*dy)/r;
		}
		Iq+= pow(Eq,2.0)*dt;
	}

	printf("R=%.2f\ta=%.2f\tq=%.2f degrees\t%e\n",R,a,q*180.0/PI,Iq);
	fprintf(fp,"%.2f,%.2f,%.2f,%e\n",R,a,q*180.0/PI,Iq);
	}
	fclose(fp);
} else {
	printf ("usage: ./calcIntensity <R> <a> filename\n");
}
return 0;

}// main
