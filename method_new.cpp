#include<iostream>
#include<vector>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cmath>
#define MAX 500
#define ROW_MAX 10
#define COL_MAX 10
#define INF 5000000
using namespace std;
double global_a=2.0;
double global_b=3.0;
struct Points {
double x;
double y;
};
struct Dir {
double x;
double y;
};
vector<Dir> random(int,double arr[][2]);
void slave(double min_a,double min_b,int i,double val,double ct[][2],bool visited[]);
int euclid(double a,double b,double arr[][2],bool visited[]);
void calculate(vector <int>& x,vector <int>& y,double a,double b);
double misfit_cal(vector<int>& yob,vector<int>& ycal);
void movement(double arr[][2],bool visited[]);
double misfit_cal(vector<int>& yob_cpy,vector<int>& ycal);
void absorb(double min_a,double min_b,double val_1, double val_2,double val,int i,double ct[][2],bool visited[]);
double square(double a){
    return (a*a);
}
void swap_master_slave(double *a,double *b,double *c,double *d){
double temp_x;
temp_x=*c;
*c=*a;
*a=temp_x;
double temp_y;
temp_y=*d;
*d=*b;
*b=temp_y;
}
//function to generate random double values
double fRand(double fMax, double fMin)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
vector<double> misfit_val;
double misfit=0.0;

  vector<int> xob,yob;
  vector<int> xcal,ycal;
  vector<int> xon,yon;
	vector<int> xos,yos;
	vector<int> xoe,yoe;
	vector<int> xow,yow;
	int L[MAX]={0};
	double min_a,min_b;
//movement of slave towards master
void slave(double min_a,double min_b,int i,double val,double ct[][2],bool visited[]){
    vector<Dir> d;
    vector<int> sl_obx,sl_oby;
    double misfit_slave;
    int move;
    d=random(i,ct);
    visited[i]=true;
    double min_dist=INF,dist;
    //movement occurs till slave =master
    while((ct[i][0] !=min_a)&&(ct[i][1] !=min_b)){
    for(int i=0;i<4;i++)
    {   //computing the min distance of slave directions with the local minima
        dist=sqrt(pow((min_a-d[i].x),2)+pow((min_b-d[i].y),2));
            if(dist <min_dist){
                min_dist=dist;
                move=i;
            }

    }
        calculate(sl_obx,sl_oby,d[move].x,d[move].y);
        calculate(xcal,ycal,global_a,global_b);
        misfit_slave=misfit_cal(sl_oby,ycal);
        //case when slave has lower misfit_val than min_vl itself
        if(misfit_slave <val){
            swap_master_slave(&min_a,&min_b,&d[move].x,&d[move].y);
        }


    }
    absorb(min_a,min_b,d[move].x,d[move].y,val,i,ct,visited);
}
//calcutes the closets pair of points and then return the index of pair of points
int euclid(double a,double b,double arr[][2],bool visited[]){
    double min_dist=INF,dist;
    int k;
    for(int i=0;i<10;i++)
    {
        if(visited[i]!=1)
            dist=sqrt(pow((a-arr[i][0]),2)+pow((b-arr[i][1]),2));
            if(dist <min_dist){
                min_dist=dist;
                 k=i;
            }

    }
    return k;
}

//calculating the movements in all possible 4 directions of a chosen CT
void calculate(vector <int>& x,vector <int>& y,double a,double b){
        // vector<int> x,y;

          int z=0;
        for(int i=1;i<=10;i++)
            {x.push_back(i);
            z=a*i +b;
            y.push_back(z);
            }
    }
void movement(double arr[][2],bool visited[]){
        //generating the list for movement
        int index;
        double a,b;
        a=arr[0][0];
        b=arr[0][1];
        visited[0]=true;
        srand(time(NULL));
        double val=0.0;
        int i=0;
        while(1) {
     	calculate(xob,yob,a,b);
        calculate(xcal,ycal,global_a,global_b);
        vector<Dir> d;
        misfit=misfit_cal(yob,ycal);
	//cout<<"misfit = "<<misfit<<endl;
        d=random(0,arr);
//	cout<<d[0].x<<endl;

	//computes the possible observeable dir
    calculate(xon,yon,d[0].x,d[0].y);
    calculate(xos,yos,d[1].x,d[1].y);
    calculate(xoe,yoe,d[2].x,d[2].y);
	calculate(xow,yow,d[3].x,d[3].y);
	//calculates in misfit_val for n,s,e,w directions

    misfit_val.assign(4,0);
	misfit_val[0]=misfit_cal(yon,ycal);
	misfit_val[1]=misfit_cal(yos,ycal);
	misfit_val[2]=misfit_cal(yoe,ycal);
	misfit_val[3]=misfit_cal(yow,ycal);


	for(int k=0;k<4;k++){
	//cout <<"misfit = "<<misfit<<"  "<<"misfit_val[k] = "<<misfit_val[k]<<endl;
	//condition if calculated misfit is greater than any of misfit in 4 directions
        if(misfit >misfit_val[k])
        {
            a=d[k].x;
            b=d[k].y;

            L[i++]=misfit_val[k];
            cout<<"val is "<<L[i-1];
            //condition for local minima
            if((L[i]<L[i-1])&&(L[i]<L[i+1])){
                    cout<<a<<b;

                    min_a=a;
                    min_b=b;
                    val=L[i];
                    break;
            }

        }


	}
	 //searching for nearest CT
        index =euclid(min_a,min_b,arr,visited);
     //Making it as slave of the
        slave(min_a,min_b,index,val,arr,visited);
        break;
}

}
//random function that generates values of a,b in all 4 directions
vector<Dir> random(int i,double arr[][2])
    {
        double a,b;
        a=arr[i][0];
        b=arr[i][1];
        vector<Dir> p;
	Dir obj;
	obj.x=a;
	obj.y=fRand(b,0);
	cout<<obj.x<<" "<<obj.y<<endl;
	p.push_back(obj);
	obj.x=a;
	obj.y=fRand(COL_MAX,b);
	cout<<obj.x<<" "<<obj.y<<endl;
	p.push_back(obj);
	obj.x=fRand(ROW_MAX,a);
	obj.y=b;
		cout<<obj.x<<" "<<obj.y<<endl;
	p.push_back(obj);
	obj.x=fRand(a,0);
	obj.y=b;
		cout<<obj.x<<" "<<obj.y<<endl;
	p.push_back(obj);
        return p;

    }
    //function for misfit calculations

    double misfit_cal(vector<int>& yob_cpy,vector<int>& ycal){
        double sum=0,yob_sum=0;
	vector<int> cpy=ycal;
	//cpy= ycal;
	//cout<<yob_cpy.size()<<"  "<<"ycal.size() = "<<ycal.size()<<"  "<<"cpy.size() = "<<cpy.size();
        while(!yob_cpy.empty() && !ycal.empty()){
		//cout<<"in misfit while\n";
            sum +=(yob_cpy.back()-ycal.back());
	//	cout<<"back = "<<yob_cpy.back()<<endl;
            yob_sum +=yob_cpy.back();
            yob_cpy.pop_back();
            ycal.pop_back();
        }
cpy.resize(10);
ycal=cpy;
        return square(sum/yob_sum);
}

    //method for CT absorption when master-slave coincide
void absorb(double min_a,double min_b,double val_1, double val_2,double val,int i,double ct[][2],bool visited[]){
    //till no CT is left unvisited condition is true
    int index;
    while(visited[i]==false){
if((val_1==min_a) && (val_2==min_b)){
    index=euclid(min_a,min_b,ct,visited);
    slave(min_a,min_b,index,val,ct,visited);
}

}
cout<<"Global minima x= "<<min_a<<"Global minima y= "<<min_b;
}

    int main()
    {
	//cout<<"start\n";
	bool visited[10];
	for(int i=0;i<10;i++)
        visited[i]=false;
 double ct[10][2]= {{2.0,5.0},{1.0,1.5},{0.5,0.5},{0.7,0.7},{3.5,3.5},{2.5,2.5},{1.5,2.0},{2.0,2.0},{3.0,3.0},{2.5,3.0}};
	movement(ct,visited);
        //random(2.0,5.0);
        return 0;
    }
