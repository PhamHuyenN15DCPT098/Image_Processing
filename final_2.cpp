#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <cmath>
using namespace std;
class filter{
	private:
		int height;
		int width;
		int matrix_negative[400][400];
	public:
		filter(){
			height=0;
			width=0;
			int i,j;
			for (i=0;i<height;i++){
				for (j=0;j<width;j++){
					matrix_negative[i][j]=0;
				}
			}
		}
};
class image {
	private:
		int height;
		int width;
		int gray_level;
		char **pixels;
		int pixel_int[400][400];
	public:
		image (){
			height=0;
			width=0;
			gray_level=0;
			int i,j;
			for (i=0;i<height;i++) pixels[i] = new char[width];
			for (i=0; i<height;i++){
				for (j=0;j<width;j++){
					pixels[i][j]=0;
					pixel_int[i][j]=0;
				}
			}
		}
		void image_set();
		void negative();
		void log_transformation();
		void histogram_equalization();
		//~image();
};
void image::image_set(){
	ifstream ifs;
	//ifs.open("C:\\Users\\User\\Desktop\\final\\mona_lisa.ascii.pgm", ios_base::in);
	ifs.open("C:\\Users\\User\\Desktop\\final\\feep.ascii.pgm", ios_base::in);
	if (ifs.fail()==true)
		cout<<"Failed to open this file"<<endl;
	char buffer[100000];
	char *c;
	ifs.getline(buffer,100000,'\n');
	if (buffer[0]!='P'|| buffer[1]!='2'){
		cout<<"Format error"<<endl;	
		ifs.close();
		return ;
	}
	do {
		ifs.getline(buffer,100000,'\n');
	} while (buffer[0]=='#');
	width=strtol(buffer,&c,10);
	height=atoi(c);
	ifs.getline(buffer,100000,'\n');
	gray_level=atoi(buffer);
	pixels=new char *[height];
	int i,j;
	char *end;
	for (i=0;i<height;i++) pixels[i] = new char[width];
	for (i=0;i<height;i++){
		ifs.getline(buffer, 100000, '\n');
		j=0;
		pixel_int[i][j]=strtol(buffer, &end,10);
		//cout<<pixel_int[i][j]<<" ";
		for(j=1;j<width;j++)
		{
			pixel_int[i][j]=strtol (end, &end, 10);
			//cout<<pixel_int[i][j]<<" ";
		}
		//cout<<endl;
	}
	ifs.close();
}
void image::negative(){
	ofstream ofs;
	char c[300];
	ofs.open("C:\\Users\\User\\Desktop\\final\\feep.ascii (2).pgm", ios_base::out);
	if (ofs.fail()==true)
		cout<<"Failed to open this file"<<endl;
	ofs<<"P2"<<endl;
	itoa(width,c,10);
	ofs<<c<<" ";
	itoa(height,c,10);
	ofs<<c<<endl;
	itoa(gray_level,c,10);
	ofs<<c<<endl;
	int matrix_negative[400][400];
	int i,j;
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			matrix_negative[i][j]=gray_level-pixel_int[i][j];
			itoa(matrix_negative[i][j],c,10);
			ofs<<c<<" ";
		}
		ofs<<endl;
	}
	cout<<"success"<<endl;
	ofs.close();
}
void image::log_transformation(){
	ofstream ofs;
	char c[300];
	ofs.open("C:\\Users\\User\\Desktop\\final\\feep.ascii (2).pgm", ios_base::out);
	if (ofs.fail()==true)
		cout<<"Failed to open this file"<<endl;
	ofs<<"P2"<<endl;
	itoa(width,c,10);
	ofs<<c<<" ";
	itoa(height,c,10);
	ofs<<c<<endl;
	itoa(gray_level,c,10);
	ofs<<c<<endl;
	int matrix_negative[400][400];
	int i,j,a;
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			a=(gray_level-1)/log10(gray_level);
			matrix_negative[i][j]=a*log10(1+pixel_int[i][j]);
			itoa(matrix_negative[i][j],c,10);
			ofs<<c<<" ";
		}
		ofs<<endl;
	}
	cout<<"success"<<endl;
	ofs.close();
}
void image::histogram_equalization(){
	ofstream ofs;
	char c[300];
	ofs.open("C:\\Users\\User\\Desktop\\final\\feep.ascii (2).pgm", ios_base::out);
	if (ofs.fail()==true)
		cout<<"Failed to open this file"<<endl;
	ofs<<"P2"<<endl;
	itoa(width,c,10);
	ofs<<c<<" ";
	itoa(height,c,10);
	ofs<<c<<endl;
	itoa(gray_level,c,10);
	ofs<<c<<endl;
	int count[300]={0};
	int matrix[400][400];
	int k=0;
	int i,j;
	float temp=0;
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			count[pixel_int[i][j]]++;
		}
	}
	for (i=0;i<=gray_level;i++){
	//	cout<<i<<" "<<count[i]<<endl;
	}
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			temp=0;
			for (k=0;k<=pixel_int[i][j];k++){
				if(count[k]!=0)
				temp=temp+((float)count[k]/(height*width));
				
			}
			matrix[i][j]=(int)(temp*gray_level);
			cout<<matrix[i][j]<<" ";
		}
			
		cout<<endl;
			
			
	}
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			itoa(matrix[i][j],c,10);
			ofs<<c<<" ";
		}
		ofs<<endl;
	}
	cout<<"success"<<endl;
	ofs.close();
	
}
int main (){
	image i1;
	i1.image_set();
	//i1.negative();
	//i1.log_transformation();
	i1.histogram_equalization();
	return 0;
}
