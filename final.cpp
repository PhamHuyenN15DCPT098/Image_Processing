#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;
class filter{
	private:
		int height;
		int width;
		int matrix_negative[300][400];
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
		int pixel_int[300][400];
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
		void image_open();
		void image_close();
		void negative();
		//~image();
};
void image::image_open(){
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
	cout<<width<<endl;
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
}
void image::negative(){
	ofstream ofs;
	char c[100];
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
	int matrix_negative[300][400];
	int i,j;
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			matrix_negative[i][j]=255-1-pixel_int[i][j];
			itoa(matrix_negative[i][j],c,10);
			ofs<<" "<<c;
		}
		ofs<<endl;
	}
	cout<<"success"<<endl;
	ofs.close();
	
}
void image::image_close(){
	ifstream ifs;
	ifs.close();
}
int main (){
	image i1;
	i1.image_open();
	i1.image_close();
	i1.negative();
	return 0;
}
