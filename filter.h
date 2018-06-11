#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <cmath>
using namespace std;
class Filter{
	protected:
		int height;
		int width;
		int **matrix;
	public:
		Filter();
		void set_filter_h_w(int h, int w);// set height, width
		void set_filter_matrix(int i, int j,int n);
		int get_height();
		int get_width();
		int get_matrix(int i, int j);
};

Filter::Filter(){
	height=0;
	width=0;
	int i,j;
	matrix = new int *[height];
	for (i=0;i<height;i++) matrix[i]=new int [width];
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			matrix[i][j]=0;
		}
	}
}
void Filter::set_filter_h_w(int h, int w){
	height=h;
	width=w;
}
void Filter::set_filter_matrix(int i, int j,int n){
	matrix[i][j]=n;
}
int Filter::get_height(){
	return height;
}
int Filter::get_width(){
	return width;
}
int Filter::get_matrix(int i, int j){
	return matrix[i][j];
}
class smoothing_filter : public Filter{
	public: 
		smoothing_filter (int height, int width){ // contructor khoi tao voi tham so truyen vao la height, width
			matrix=new int *[height];
			for (int i=0;i<height;i++) 	
				matrix[i]=new int [width];
		}
		void set_SF ();// set smoothing filter
};
class laplacian_filter : public Filter{
	public: 
		laplacian_filter (int height, int width){ // constructor khoi tao voi tham so truyen vao la height, width
			matrix=new int *[height];
			for (int i=0;i<height;i++) 	
				matrix[i]=new int [width];
		}
		void set_LF ();// set laplacian filter
};
void smoothing_filter::set_SF(){
	set_filter_h_w(3,3);
	int i, j;
	int m[3][3]={1,1,1,1,1,1,1,1,1};
	for (i=0;i<get_height();i++)
		for (j=0;j<get_width();j++){
			set_filter_matrix(i, j, m[i][j]);
		}
}
void laplacian_filter::set_LF(){
	set_filter_h_w(3,3);
	int i, j;
	int m[3][3]={1,1,1,1,-8,1,1,1,1};
	for (i=0;i<get_height();i++)
		for (j=0;j<get_width();j++){
			set_filter_matrix(i, j, m[i][j]);
		}
}


