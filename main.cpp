#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include "filter.h"
#include "image.h"
using namespace std;
int Menu();
int Menu_Image();
int main (){
	int choice_filter;
	int choice_image;
	char *fname;
	choice_image=Menu_Image();
	image i1;
	choice_filter=Menu();
	switch (choice_image){
		case 1:	
			fname="feep.ascii.pgm";
			break;
		case 2:
			fname="mona_lisa.ascii.pgm";
			break;
		case 3:
			fname="fractal_tree.ascii.pgm";
			break;	
		case 4: 
			fname="lena.ascii.pgm";
			break;
		case 5:
			fname="marcie.ascii.pgm";
			break;
		case 6:
			fname="glassware_noisy.ascii.pgm";
			break;
		case 7:
			fname="casablanca.ascii.pgm";
			break;
		case 8:
			fname="surf.ascii.pgm";
			break;
		case 9:
			fname="plane.pgm";
			break;
		case 10:
			fname="balloons.ascii.pgm";
			break;
	}
	//cout<<fname;9
	switch (choice_filter){
		case 1:
			i1.image_set(fname);
			i1.negative();
			i1.write();
			i1.delete_array();
			break;
		case 2:
			i1.image_set(fname);
			i1.log_transformation();
			i1.write();
			i1.delete_array();
			break;
		case 3:
			i1.image_set(fname);
			i1.histogram_equalization();
			i1.write();
			i1.delete_array();
			break;
		case 4:
			i1.image_set(fname);
			i1.smoothing_linear();
			i1.write();
			i1.delete_array();
			break;
		case 5:
			i1.image_set(fname);
			i1.laplacian();
			i1.write();
			i1.delete_array();
	}
	return 0;
}
