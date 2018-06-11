#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <filter.h>
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
	//cout<<add<<endl;
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
	cout<<"Success"<<endl;
	cout<<"Please open image result.pgm at C:\\Users\\User\\Desktop\\final"<<endl;
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
