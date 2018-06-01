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
		int pixel_int_befor[400][400];
		int pixel_int_after[400][400];
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
					pixel_int_befor[i][j]=0;
					pixel_int_after[i][j]=0;
				}
			}
		}
		void image_set();
		void negative();
		void log_transformation();
		void histogram_equalization();
		void write();
		//~image();
};
void image::image_set(){
	ifstream ifs;
	ifs.open("C:\\Users\\User\\Desktop\\final\\mona_lisa.ascii.pgm", ios_base::in);
	//ifs.open("C:\\Users\\User\\Desktop\\final\\feep.ascii.pgm", ios_base::in);
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
		pixel_int_befor[i][j]=strtol(buffer, &end,10);
		for(j=1;j<width;j++)
		{
			pixel_int_befor[i][j]=strtol (end, &end, 10);
		}
	}
	ifs.close();
}
void image::write(){
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
	int i, j;
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			itoa(pixel_int_after[i][j],c,10);
			ofs<<c<<" ";
		}
		ofs<<endl;
	}
	cout<<"success"<<endl;
	ofs.close();
}
void image::negative(){
	int matrix_negative[400][400];
	int i,j;
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			pixel_int_after[i][j]=gray_level-pixel_int_befor[i][j];
		}
	}
}
void image::log_transformation(){
	int matrix_negative[400][400];
	int i,j;
	float a=(float)(gray_level-1)/log10(gray_level);;
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			pixel_int_after[i][j]=a*log10(1+pixel_int_befor[i][j]);
		}
	}
}
void image::histogram_equalization(){
	int count[300]={0};
	int matrix[400][400];
	int k=0;
	int i,j;
	float temp=0;
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			count[pixel_int_befor[i][j]]++;
		}
	}
//	for (i=0;i<=gray_level;i++){
//		cout<<i<<" "<<count[i]<<endl;
//	}
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			temp=0;
			for (k=0;k<=pixel_int_befor[i][j];k++){
				if(count[k]!=0)
				temp=temp+((float)count[k]/(height*width));
			}
			pixel_int_after[i][j]=(int)(temp*gray_level);
		}
	}
}
int Menu(){
	int choice;
	cout<<"==============Filters for an image=============="<<endl;
	cout<<"1. Image negative"<<endl;
	cout<<"2. Log transformation"<<endl;
	cout<<"3. Histogram equalization"<<endl;
	cout<<"4. Smoothing linear filter"<<endl;
	cout<<"5. Laplacian filter"<<endl;
	cout<<"================================================"<<endl;
	cout<<"Your choice is: ";
	cin>>choice;
	return choice;
}
int main (){
	int choice;
	image i1;
	choice=Menu();
	i1.image_set();
	switch (choice){
		case 1:
			i1.negative();
			i1.write();
			break;
		case 2:
			i1.log_transformation();
			i1.write();
			break;
		case 3:
			i1.histogram_equalization();
			i1.write();
			break;
	}
	return 0;
}
