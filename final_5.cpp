#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <cmath>
using namespace std;
class image {
	private:
		int height;
		int width;
		int gray_level;
		char **pixels;
		int **pixel_int_before;
		int **pixel_int_after;
	public:
		image ();
		void image_set();
		void negative();
		void log_transformation();
		void histogram_equalization();
		void smoothing_linear();
		void laplacian();
		void write();
		void delete_array();
		//~image();
};
class Filter{
	private:
		int height;
		int width;
		int **matrix;
	public:
		Filter();
		void set_filter_h_w(int h, int w);// set height, width
		void set_filter_matrix(int &i, int &j,int &n);
		int get_height();
		int get_width();
		int get_matrix(int i, int j);
};
class smoothing_filter : private Filter{
	public: 
		void set_SF (){
			set_filter_h_w(3,3);
			int **m;
			int i, j;
			m=new int *[get_height()];
			for (i=0;i<get_height();i++) 	m[i]=new int [get_width()];
			m[0][0]=1;
			m[0][1]=1;
			m[0][2]=1;
			m[1][0]=1;
			m[1][1]=1;
			m[1][2]=1;
			m[2][0]=1;
			m[2][1]=1;
			m[2][2]=1;
			cout<<get_height()<<get_width();
			for (i=0;i<get_height();i++)
				for (j=0;j<get_width();j++){
					cout<<"i: "<<i<<", j: "<<j<<": "<<endl;
					set_filter_matrix(i, j, m[i][j]);
					cout<<get_matrix(i, j);
				}
				
		}
};
int Menu();
int main (){
	int choice;
	image i1;
	smoothing_filter sm1;
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
		case 4:
			i1.image_set();
			i1.smoothing_linear();
			i1.write();
			i1.delete_array();
			break;
		case 5:
			i1.image_set();
			i1.smoothing_linear();
			i1.laplacian();
			i1.write();
			i1.delete_array();
	}
	//sm1.set_SF();
	return 0;
}
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
void Filter::set_filter_matrix(int &i, int &j,int &n){
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
image::image(){
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
void image::image_set(){
	ifstream ifs;
	//ifs.open("C:\\Users\\User\\Desktop\\final\\venus2.ascii.pgm", ios_base::in);
	ifs.open("C:\\Users\\User\\Desktop\\final\\mona_lisa.ascii.pgm", ios_base::in);
	//ifs.open("C:\\Users\\User\\Desktop\\final\\draft.pgm", ios_base::in);
//	ifs.open("C:\\Users\\User\\Desktop\\final\\feep.ascii.pgm", ios_base::in);
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
		for(j=1;j<width;j++)
		{
			pixel_int_before[i][j]=strtol (end, &end, 10);
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
	ofs<<width<<" ";
	ofs<<height<<endl;
	ofs<<gray_level<<endl;
	int i, j;
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			ofs<<pixel_int_after[i][j]<<" ";
			//cout<<pixel_int_after[i][j]<<" ";
		}
		//cout<<endl;
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
	int i,j;
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			pixel_int_after[i][j]=gray_level-pixel_int_before[i][j];
		}
	}
}
void image::log_transformation(){
	int i,j;
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
void image::smoothing_linear(){
	int i, j;
	int **sum;
	sum=new int *[height];
	for (i=0;i<height;i++)	sum[i]=new int [width];
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			sum[i][j]==0;
		}
	}
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			pixel_int_after[i][j]=0;
		}
	}
	for (i=0;i<height;i++){
		if (i==0){
				for(j=0;j<width;j++){
					if (j==0){
						sum[i][j]=4*pixel_int_before[i][j]+2*pixel_int_before[i][j+1]
							+2*pixel_int_before[i+1][j]+pixel_int_before[i+1][i+1];
					}
					else if (j==width-1){
						sum[i][j]=4*pixel_int_before[i][j]+2*pixel_int_before[i][j-1]+2*pixel_int_before[i+1][j]+pixel_int_before[i+1][j-1];
					}
					else{
						sum[i][j]=2*pixel_int_before[i][j]+2*pixel_int_before[i][j-1]+2*pixel_int_before[i][j+1]
							+pixel_int_before[i+1][j-1]+pixel_int_before[i+1][j]+pixel_int_before[i+1][j+1];
					}
				}
			}
			else if (i==height-1){
				for (j=0;j<width;j++){
					if (j==0){
						sum[i][j]=4*pixel_int_before[i][j]+2*pixel_int_before[i][j+1]
							+2*pixel_int_before[i-1][j]+pixel_int_before[i-1][j+1];
					}
					else if (j==width-1){
						sum[i][j]=4*pixel_int_before[i][j]+2*pixel_int_before[i][j-1]+2*pixel_int_before[i-1][j]+pixel_int_before[i-1][j-1];
					}
					else {
						sum[i][j]=2*pixel_int_before[i][j]+2*pixel_int_before[i][j-1]+2*pixel_int_before[i][j+1]
							+pixel_int_before[i-1][j-1]+pixel_int_before[i-1][j]+pixel_int_before[i-1][j+1];
					}
				}
			}
			else{
				for (j=0;j<width;j++){   
					if (j==0){
						sum[i][j]=2*pixel_int_before[i][j]+2*pixel_int_before[i-1][j]+2*pixel_int_before[i+1][j]
							+pixel_int_before[i-1][j+1]+pixel_int_before[i][j+1]+pixel_int_before[i+1][j+1];
					}
					else if (j==width-1){
						sum[i][j]=2*pixel_int_before[i][j]+2*pixel_int_before[i-1][j]+2*pixel_int_before[i+1][j]
							+pixel_int_before[i-1][j-1]+pixel_int_before[i][j-1]+pixel_int_before[i+1][j-1];
					}
					else {
						sum[i][j]=pixel_int_before[i-1][j-1]+pixel_int_before[i-1][j]+pixel_int_before[i-1][j+1]
							+pixel_int_before[i][j-1]+pixel_int_before[i][j]+pixel_int_before[i][j+1]
							+pixel_int_before[i+1][j-1]+pixel_int_before[i+1][j]+pixel_int_before[i+1][j+1];
					}
				}
			}
		}
	cout<<endl;
	for (i=0;i<height;i++){
		for(j=0;j<width;j++){
			pixel_int_after[i][j]=round((float)sum[i][j]/9);
		}
	}
	for (i=0;i<height;i++) delete [] sum[i]; // delete sum
}
void image::laplacian(){
	int A[3][3]={1,1,1,1,-8,1,1,1,1 };
	int i, j;
	int **temp;
	temp=new int *[height];
	for (i=0;i<height;i++)	temp[i]=new int [width];
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			temp[i][j]==0;
		}
	}
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			pixel_int_after[i][j]=0;
		}
	}
	for (i=0;i<height;i++){
		if (i==0){
				for(j=0;j<width;j++){
					if (j==0){
						temp[i][j]=pixel_int_before[i][j]*(A[0][1]+A[0][0]+A[1][0]+A[1][1])+pixel_int_before[i][j+1]*(A[0][2]+A[1][2])
							+pixel_int_before[i+1][j]*(A[2][0]+A[2][1])+pixel_int_before[i+1][i+1]*A[2][2];
					}
					else if (j==width-1){
						temp[i][j]=pixel_int_before[i][j]*(A[0][1]+A[0][2]+A[1][2]+A[1][1])+pixel_int_before[i][j-1]*(A[0][0]+A[1][0])
						+pixel_int_before[i+1][j]*(A[2][1]+A[2][2])+pixel_int_before[i+1][j-1]*A[2][0];
					}
					else{
						temp[i][j]=pixel_int_before[i][j]*(A[0][1]+A[1][1])+pixel_int_before[i][j-1]*(A[1][0]+A[0][0])+pixel_int_before[i][j+1]*(A[0][2]+A[1][2])
							+pixel_int_before[i+1][j-1]*A[2][0]+pixel_int_before[i+1][j]*A[2][1]+pixel_int_before[i+1][j+1]*A[2][2];
					}
					
				}
			}
			else if (i==height-1){
				for (j=0;j<width;j++){
					if (j==0){
						temp[i][j]=pixel_int_before[i][j]*(A[1][0]+A[2][0]+A[2][1]+A[1][1])+pixel_int_before[i][j+1]*(A[1][2]+A[2][2])
							+pixel_int_before[i-1][j]*(A[0][0]+A[0][1])+pixel_int_before[i-1][j+1]*A[0][2];
					}
					else if (j==width-1){
						temp[i][j]=pixel_int_before[i][j]*(A[1][2]+A[2][1]+A[2][2]+A[1][1])+pixel_int_before[i][j-1]*(A[1][0]+A[2][0])
						+pixel_int_before[i-1][j]*(A[0][1]+A[0][2])+pixel_int_before[i-1][j-1]*A[0][0];
					}
					else {
						temp[i][j]=pixel_int_before[i][j]*(A[2][1]+A[1][1])+pixel_int_before[i][j-1]*(A[1][0]+A[2][0])+pixel_int_before[i][j+1]*(A[1][2]+A[2][2])
							+pixel_int_before[i-1][j-1]*A[0][0]+pixel_int_before[i-1][j]*A[0][1]+pixel_int_before[i-1][j+1]*A[0][2];
					}
				}
			}
			else{
				for (j=0;j<width;j++){   
					if (j==0){
						temp[i][j]=pixel_int_before[i][j]*(A[1][0]+A[1][1])+pixel_int_before[i-1][j]*(A[0][0]+A[0][1])+pixel_int_before[i+1][j]*(A[2][0]+A[2][1])
							+pixel_int_before[i-1][j+1]*A[0][2]+pixel_int_before[i][j+1]*A[1][2]+pixel_int_before[i+1][j+1]*A[2][2];
					}
					else if (j==width-1){
						temp[i][j]=pixel_int_before[i][j]*(A[1][2]+A[1][1])+pixel_int_before[i-1][j]*(A[0][1]+A[0][2])+pixel_int_before[i+1][j]*(A[2][1]+A[2][2])
							+pixel_int_before[i-1][j-1]*A[0][0]+pixel_int_before[i][j-1]*A[1][0]+pixel_int_before[i+1][j-1]*A[2][0];
					}
					else {
						temp[i][j]=pixel_int_before[i-1][j-1]*A[0][0]+pixel_int_before[i-1][j]*A[0][1]+pixel_int_before[i-1][j+1]*A[0][2]
							+pixel_int_before[i][j-1]*A[1][0]+pixel_int_before[i][j]*A[1][1]+pixel_int_before[i][j+1]*A[1][2]
							+pixel_int_before[i+1][j-1]*A[2][0]+pixel_int_before[i+1][j]*A[2][1]+pixel_int_before[i+1][j+1]*A[2][2];
					}
				}
			}
		}
	cout<<endl;
	for (i=0;i<height;i++){
		for(j=0;j<width;j++){
			if (A[1][1]<0)
				pixel_int_after[i][j]=pixel_int_before[i][j]-temp[i][j];
			else
				pixel_int_after[i][j]=pixel_int_before[i][j]+temp[i][j];
			if (pixel_int_after[i][j]<0)	pixel_int_after[i][j]=0;
			cout<<pixel_int_after[i][j]<<" ";
		}
		cout<<endl;
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

