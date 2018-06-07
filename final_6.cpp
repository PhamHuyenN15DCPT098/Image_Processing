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
		int **GrayScale_before;
		int **GrayScale_after;
	public:
		image ();
		void image_set(char *fname);
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
int Menu();
int Menu_Image();
int Menu_Image(){
	int choice;
	cout<<"=================Some pictures=================="<<endl;
	cout<<"1. Feep"<<endl;
	cout<<"2. Monalisa"<<endl;
	cout<<"3. Fractal tree"<<endl;
	cout<<"4. Lena"<<endl;
	cout<<"5. Marcie"<<endl;
	cout<<"6. Glassware noisy"<<endl;
	cout<<"7. Casablanca"<<endl;
	cout<<"8. Surf"<<endl;
	cout<<"9. Plane"<<endl;
	cout<<"10. Balloons"<<endl;
	cout<<"================================================"<<endl;
	cout<<"Your choice is: ";
	cin>>choice;
	return choice;
}
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
image::image(){
	height=0;
	width=0;
	gray_level=0;
	int i,j;
	pixels=new char*[height];
	GrayScale_before=new int*[height];
	GrayScale_after=new int *[height];
	for (i=0;i<height;i++) {
		pixels[i] = new char[width];
		GrayScale_before[i]=new int[width];
		GrayScale_after[i]=new int [width];
	}
	for (i=0; i<height;i++){
		for (j=0;j<width;j++){
			pixels[i][j]=0;
			GrayScale_before[i][j]=0;
			GrayScale_after[i][j]=0;
		}
	}
}
void image::image_set(char fname[]){
	char add[]="C:\\Users\\User\\Desktop\\final\\";// address
	strcat(add,fname);
	cout<<add<<endl;
	ifstream ifs;
	ifs.open(add, ios_base::in);
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
	width=strtol(buffer,&c,10); // get width 
	height=atoi(c);				// get height
	ifs.getline(buffer,100000,'\n');
	gray_level=atoi(buffer);
	int i,j;
	char *end;
	pixels=new char *[height];
	GrayScale_before=new int*[height];
	GrayScale_after=new int *[height];
	for (i=0;i<height;i++) {
				pixels[i] = new char[width];
				GrayScale_before[i]=new int[width];
				GrayScale_after[i]=new int [width];
	}
	int dem=0;
	int a;
	for (i=0;i<height;i++){
		for(j=0;j<width;j++)
		{	
			ifs>>GrayScale_before[i][j];
		}
	}
	ifs.close();
}
void image::write(){
	ofstream ofs;
	ofs.open("C:\\Users\\User\\Desktop\\final\\result.pgm", ios_base::out);
	if (ofs.fail()==true)
		cout<<"Failed to open this file"<<endl;
	ofs<<"P2"<<endl;
	ofs<<width<<" ";
	ofs<<height<<endl;
	ofs<<gray_level<<endl;
	int i, j;
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			ofs<<GrayScale_after[i][j]<<" ";
			//cout<<GrayScale_after[i][j]<<" ";
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
			delete [] GrayScale_before[i];
			delete [] GrayScale_after[i];
	}
}
void image::negative(){
	int i,j;
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			GrayScale_after[i][j]=gray_level-GrayScale_before[i][j];
		}
	}
}
void image::log_transformation(){
	int i,j;
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			GrayScale_after[i][j]=round(log10(1+GrayScale_before[i][j]));
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
			count[GrayScale_before[i][j]]++;
		}
	}
	for (i=0;i<height;i++){
		for (j=0;j<width;j++){
			temp=0;
			for (k=0;k<=GrayScale_before[i][j];k++){
				if(count[k]!=0)
				temp=temp+((float)count[k]/(height*width));
			}
			GrayScale_after[i][j]=round(temp*gray_level);
		}
	}
}
void image::smoothing_linear(){
	int i, j;
	smoothing_filter sm1(3,3);
	sm1.set_SF();
	int sum_matrix=0;
	for (i=0;i<sm1.get_height();i++){
		for (j=0;j<sm1.get_width();j++)
		sum_matrix=sum_matrix+sm1.get_matrix(i,j);
	}
//	cout<<sum_matrix<<endl;
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
			GrayScale_after[i][j]=0;
		}
	}
	for (i=0;i<height;i++){
		if (i==0){
				for(j=0;j<width;j++){
					if (j==0){
						sum[i][j]=GrayScale_before[i][j]*(sm1.get_matrix(0,1)+sm1.get_matrix(0,0)+sm1.get_matrix(1,0)+sm1.get_matrix(1,1))+GrayScale_before[i][j+1]*(sm1.get_matrix(0,2)+sm1.get_matrix(1,2))
							+GrayScale_before[i+1][j]*(sm1.get_matrix(2,0)+sm1.get_matrix(2,1))+GrayScale_before[i+1][i+1]*sm1.get_matrix(2,2);
					}
					else if (j==width-1){
						sum[i][j]=GrayScale_before[i][j]*(sm1.get_matrix(0,1)+sm1.get_matrix(0,2)+sm1.get_matrix(1,2)+sm1.get_matrix(1,1))+GrayScale_before[i][j-1]*(sm1.get_matrix(0,0)+sm1.get_matrix(1,0))
						+GrayScale_before[i+1][j]*(sm1.get_matrix(2,1)+sm1.get_matrix(2,2))+GrayScale_before[i+1][j-1]*sm1.get_matrix(2,0);
					}
					else{
						sum[i][j]=GrayScale_before[i][j]*(sm1.get_matrix(0,1)+sm1.get_matrix(1,1))+GrayScale_before[i][j-1]*(sm1.get_matrix(1,0)+sm1.get_matrix(0,0))+GrayScale_before[i][j+1]*(sm1.get_matrix(0,2)+sm1.get_matrix(1,2))
							+GrayScale_before[i+1][j-1]*sm1.get_matrix(2,0)+GrayScale_before[i+1][j]*sm1.get_matrix(2,1)+GrayScale_before[i+1][j+1]*sm1.get_matrix(2,2);
					}
				}
			}
			else if (i==height-1){
				for (j=0;j<width;j++){
					if (j==0){
						sum[i][j]=GrayScale_before[i][j]*(sm1.get_matrix(1,0)+sm1.get_matrix(2,0)+sm1.get_matrix(2,1)+sm1.get_matrix(1,1))+GrayScale_before[i][j+1]*(sm1.get_matrix(1,2)+sm1.get_matrix(2,2))
							+GrayScale_before[i-1][j]*(sm1.get_matrix(0,0)+sm1.get_matrix(0,1))+GrayScale_before[i-1][j+1]*sm1.get_matrix(0,2);
					}
					else if (j==width-1){
						sum[i][j]=GrayScale_before[i][j]*(sm1.get_matrix(1,2)+sm1.get_matrix(2,1)+sm1.get_matrix(2,2)+sm1.get_matrix(1,1))+GrayScale_before[i][j-1]*(sm1.get_matrix(1,0)+sm1.get_matrix(2,0))
						+GrayScale_before[i-1][j]*(sm1.get_matrix(0,1)+sm1.get_matrix(0,2))+GrayScale_before[i-1][j-1]*sm1.get_matrix(0,0);
					}
					else {
						sum[i][j]=GrayScale_before[i][j]*(sm1.get_matrix(2,1)+sm1.get_matrix(1,1))+GrayScale_before[i][j-1]*(sm1.get_matrix(1,0)+sm1.get_matrix(2,0))+GrayScale_before[i][j+1]*(sm1.get_matrix(1,2)+sm1.get_matrix(2,2))
							+GrayScale_before[i-1][j-1]*sm1.get_matrix(0,0)+GrayScale_before[i-1][j]*sm1.get_matrix(0,1)+GrayScale_before[i-1][j+1]*sm1.get_matrix(0,2);
					}
				}
			}
			else{
				for (j=0;j<width;j++){   
					if (j==0){
						sum[i][j]=GrayScale_before[i][j]*(sm1.get_matrix(1,0)+sm1.get_matrix(1,1))+GrayScale_before[i-1][j]*(sm1.get_matrix(0,0)+sm1.get_matrix(0,1))+GrayScale_before[i+1][j]*(sm1.get_matrix(2,0)+sm1.get_matrix(2,1))
							+GrayScale_before[i-1][j+1]*sm1.get_matrix(0,2)+GrayScale_before[i][j+1]*sm1.get_matrix(1,2)+GrayScale_before[i+1][j+1]*sm1.get_matrix(2,2);
					}
					else if (j==width-1){
						sum[i][j]=GrayScale_before[i][j]*(sm1.get_matrix(1,2)+sm1.get_matrix(1,1))+GrayScale_before[i-1][j]*(sm1.get_matrix(0,1)+sm1.get_matrix(0,2))+GrayScale_before[i+1][j]*(sm1.get_matrix(2,1)+sm1.get_matrix(2,2))
							+GrayScale_before[i-1][j-1]*sm1.get_matrix(0,0)+GrayScale_before[i][j-1]*sm1.get_matrix(1,0)+GrayScale_before[i+1][j-1]*sm1.get_matrix(2,0);
					}
					else {
						sum[i][j]=GrayScale_before[i-1][j-1]*sm1.get_matrix(0,0)+GrayScale_before[i-1][j]*sm1.get_matrix(0,1)+GrayScale_before[i-1][j+1]*sm1.get_matrix(0,2)
							+GrayScale_before[i][j-1]*sm1.get_matrix(1,0)+GrayScale_before[i][j]*sm1.get_matrix(1,1)+GrayScale_before[i][j+1]*sm1.get_matrix(1,2)
							+GrayScale_before[i+1][j-1]*sm1.get_matrix(2,0)+GrayScale_before[i+1][j]*sm1.get_matrix(2,1)+GrayScale_before[i+1][j+1]*sm1.get_matrix(2,2);
					}
				}
			}
	}
	for (i=0;i<height;i++){
		for(j=0;j<width;j++){
			GrayScale_after[i][j]=round((float)sum[i][j]/sum_matrix);
		}
	}
	for (i=0;i<height;i++) delete [] sum[i]; // delete sum
}
void image::laplacian(){
	int i, j;
	laplacian_filter lf1(3,3);
	lf1.set_LF();
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
			GrayScale_after[i][j]=0;
		}
	}
	for (i=0;i<height;i++){
		if (i==0){
				for(j=0;j<width;j++){
					if (j==0){
						temp[i][j]=GrayScale_before[i][j]*(lf1.get_matrix(0,1)+lf1.get_matrix(0,0)+lf1.get_matrix(1,0)+lf1.get_matrix(1,1))+GrayScale_before[i][j+1]*(lf1.get_matrix(0,2)+lf1.get_matrix(1,2))
							+GrayScale_before[i+1][j]*(lf1.get_matrix(2,0)+lf1.get_matrix(2,1))+GrayScale_before[i+1][i+1]*lf1.get_matrix(2,2);
					}
					else if (j==width-1){
						temp[i][j]=GrayScale_before[i][j]*(lf1.get_matrix(0,1)+lf1.get_matrix(0,2)+lf1.get_matrix(1,2)+lf1.get_matrix(1,1))+GrayScale_before[i][j-1]*(lf1.get_matrix(0,0)+lf1.get_matrix(1,0))
						+GrayScale_before[i+1][j]*(lf1.get_matrix(2,1)+lf1.get_matrix(2,2))+GrayScale_before[i+1][j-1]*lf1.get_matrix(2,0);
					}
					else{
						temp[i][j]=GrayScale_before[i][j]*(lf1.get_matrix(0,1)+lf1.get_matrix(1,1))+GrayScale_before[i][j-1]*(lf1.get_matrix(1,0)+lf1.get_matrix(0,0))+GrayScale_before[i][j+1]*(lf1.get_matrix(0,2)+lf1.get_matrix(1,2))
							+GrayScale_before[i+1][j-1]*lf1.get_matrix(2,0)+GrayScale_before[i+1][j]*lf1.get_matrix(2,1)+GrayScale_before[i+1][j+1]*lf1.get_matrix(2,2);
					}
				}
			}
			else if (i==height-1){
				for (j=0;j<width;j++){
					if (j==0){
						temp[i][j]=GrayScale_before[i][j]*(lf1.get_matrix(1,0)+lf1.get_matrix(2,0)+lf1.get_matrix(2,1)+lf1.get_matrix(1,1))+GrayScale_before[i][j+1]*(lf1.get_matrix(1,2)+lf1.get_matrix(2,2))
							+GrayScale_before[i-1][j]*(lf1.get_matrix(0,0)+lf1.get_matrix(0,1))+GrayScale_before[i-1][j+1]*lf1.get_matrix(0,2);
					}
					else if (j==width-1){
						temp[i][j]=GrayScale_before[i][j]*(lf1.get_matrix(1,2)+lf1.get_matrix(2,1)+lf1.get_matrix(2,2)+lf1.get_matrix(1,1))+GrayScale_before[i][j-1]*(lf1.get_matrix(1,0)+lf1.get_matrix(2,0))
						+GrayScale_before[i-1][j]*(lf1.get_matrix(0,1)+lf1.get_matrix(0,2))+GrayScale_before[i-1][j-1]*lf1.get_matrix(0,0);
					}
					else {
						temp[i][j]=GrayScale_before[i][j]*(lf1.get_matrix(2,1)+lf1.get_matrix(1,1))+GrayScale_before[i][j-1]*(lf1.get_matrix(1,0)+lf1.get_matrix(2,0))+GrayScale_before[i][j+1]*(lf1.get_matrix(1,2)+lf1.get_matrix(2,2))
							+GrayScale_before[i-1][j-1]*lf1.get_matrix(0,0)+GrayScale_before[i-1][j]*lf1.get_matrix(0,1)+GrayScale_before[i-1][j+1]*lf1.get_matrix(0,2);
					}
				}
			}
			else{
				for (j=0;j<width;j++){   
					if (j==0){
						temp[i][j]=GrayScale_before[i][j]*(lf1.get_matrix(1,0)+lf1.get_matrix(1,1))+GrayScale_before[i-1][j]*(lf1.get_matrix(0,0)+lf1.get_matrix(0,1))+GrayScale_before[i+1][j]*(lf1.get_matrix(2,0)+lf1.get_matrix(2,1))
							+GrayScale_before[i-1][j+1]*lf1.get_matrix(0,2)+GrayScale_before[i][j+1]*lf1.get_matrix(1,2)+GrayScale_before[i+1][j+1]*lf1.get_matrix(2,2);
					}
					else if (j==width-1){
						temp[i][j]=GrayScale_before[i][j]*(lf1.get_matrix(1,2)+lf1.get_matrix(1,1))+GrayScale_before[i-1][j]*(lf1.get_matrix(0,1)+lf1.get_matrix(0,2))+GrayScale_before[i+1][j]*(lf1.get_matrix(2,1)+lf1.get_matrix(2,2))
							+GrayScale_before[i-1][j-1]*lf1.get_matrix(0,0)+GrayScale_before[i][j-1]*lf1.get_matrix(1,0)+GrayScale_before[i+1][j-1]*lf1.get_matrix(2,0);
					}
					else {
						temp[i][j]=GrayScale_before[i-1][j-1]*lf1.get_matrix(0,0)+GrayScale_before[i-1][j]*lf1.get_matrix(0,1)+GrayScale_before[i-1][j+1]*lf1.get_matrix(0,2)
							+GrayScale_before[i][j-1]*lf1.get_matrix(1,0)+GrayScale_before[i][j]*lf1.get_matrix(1,1)+GrayScale_before[i][j+1]*lf1.get_matrix(1,2)
							+GrayScale_before[i+1][j-1]*lf1.get_matrix(2,0)+GrayScale_before[i+1][j]*lf1.get_matrix(2,1)+GrayScale_before[i+1][j+1]*lf1.get_matrix(2,2);
					}
				}
			}
		}
	for (i=0;i<height;i++){
		for(j=0;j<width;j++){
			if (lf1.get_matrix(1,1)<0)
				GrayScale_after[i][j]=GrayScale_before[i][j]-temp[i][j];
			else
				GrayScale_after[i][j]=GrayScale_before[i][j]+temp[i][j];
			if (GrayScale_after[i][j]<0)	GrayScale_after[i][j]=0;
		}
	}
	for (i=0;i<height;i++) delete [] temp[i];
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


