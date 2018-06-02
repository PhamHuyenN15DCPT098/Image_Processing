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
		int **pixel_int_before;
		int **pixel_int_after;
	public:
		image (){
			height=0;
			width=0;
			gray_level=0;
			int i,j;
			pixels=new char*[height];
			pixel_int_before=new int*[height];
			pixel_int_after=new int *[height];
			for (i=0;i<height;i++) {
				pixels[i] = new char[width];
				pixel_int_before[i]=new int[width];
				pixel_int_after[i]=new int [width];
			}
			for (i=0; i<height;i++){
				for (j=0;j<width;j++){
					pixels[i][j]=0;
					pixel_int_before[i][j]=0;
					pixel_int_after[i][j]=0;
				}
			}
		}
		void image_set();
		void negative();
		void log_transformation();
		void histogram_equalization();
		void write();
		void delete_array();
		//~image();
};
void image::image_set(){
	cout<<"set"<<endl;
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
	int i,j;
	char *end;
	pixels=new char *[height];
	pixel_int_before=new int*[height];
	pixel_int_after=new int *[height];
	for (i=0;i<height;i++) {
				pixels[i] = new char[width];
				pixel_int_before[i]=new int[width];
				pixel_int_after[i]=new int [width];
	}
	for (i=0;i<height;i++){
		ifs.getline(buffer, 100000, '\n');
		j=0;
		pixel_int_before[i][j]=strtol(buffer, &end,10);
		cout<<pixel_int_before[i][j]<<" ";
		for(j=1;j<width;j++)
		{
			pixel_int_before[i][j]=strtol (end, &end, 10);
			cout<<pixel_int_before[i][j]<<" ";
		}
		cout<<endl;
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
			ofs<<pixel_int_after[i][j]<<" ";
			cout<<pixel_int_after[i][j]<<" ";
		}
		cout<<endl;
		
		ofs<<endl;
	}
	cout<<"success"<<endl;
	ofs.close();
}
void image::delete_array (){
	int i;
	for (i=0;i<height;i++){
			delete [] pixels[i];
			delete [] pixel_int_before[i];
			delete [] pixel_int_after[i];
	}
}
void image::negative(){
	cout<<"negative"<<endl;
	int i,j;
//	pixels=new char *[height];
//	pixel_int_before=new int*[height];
//	pixel_int_after=new int *[height];
//	for (i=0;i<height;i++) {
//				pixels[i] = new char[width];
//				pixel_int_before[i]=new int[width];
//				pixel_int_after[i]=new int [width];
//	}
	for (i=0;i<height;i++){
		for (j=0;j<width;j++)
		cout<<pixel_int_before[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			pixel_int_after[i][j]=0;
			cout<<pixel_int_after[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			//cout<<pixel_int_before[i][j]<<" ";
			pixel_int_after[i][j]=gray_level-pixel_int_before[i][j];
			cout<<pixel_int_after[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}
void image::log_transformation(){
	int i,j;
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			pixel_int_after[i][j]=0;
			cout<<pixel_int_after[i][j]<<" ";
		}
		cout<<endl;
	}
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			pixel_int_after[i][j]=round(log10(1+pixel_int_before[i][j]));
		}
	}
}
void image::histogram_equalization(){
	int count[gray_level]={0};
	int k=0;
	int i,j;
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			pixel_int_after[i][j]=0;
			cout<<pixel_int_after[i][j]<<" ";
		}
		cout<<endl;
	}
	float temp=0;
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			count[pixel_int_before[i][j]]++;
		}
	}
//	for (i=0;i<=gray_level;i++){
//		cout<<i<<" "<<count[i]<<endl;
//	}
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			temp=0;
			for (k=0;k<=pixel_int_before[i][j];k++){
				if(count[k]!=0)
				temp=temp+((float)count[k]/(height*width));
			}
			pixel_int_after[i][j]=round(temp*gray_level);
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
	
	switch (choice){
		case 1:
			
			i1.image_set();
			i1.negative();
			i1.write();
			i1.delete_array();
			break;
		case 2:
			i1.image_set();
			i1.log_transformation();
			i1.write();
			i1.delete_array();
			break;
		case 3:
			i1.image_set();
			i1.histogram_equalization();
			i1.write();
			i1.delete_array();
			break;
	}
	return 0;
}
