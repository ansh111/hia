#include<iostream>
#include<vector>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#define MAX 500
#define ROW_MAX 10
#define COL_MAX 10
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
struct List{
int row;
int col;
};

void calculate(vector <int>& x,vector <int>& y,double a,double b){
        // vector<int> x,y;

          int z=0;
        for(int i=1;i<=10;i++)
            {x.push_back(i);
            z=a*i +b;
            y.push_back(z);
            }
    }

vector<Dir> random(double a,double b);
double misfit_cal(vector<int>& yob,vector<int>& ycal);
/*void swap(double &x,double &y){
*x=*x+*y;
*y=*x-*y;
*x=*x-*y;
}*/
double square(double a){
    return (a*a);
}
double fRand(double fMax, double fMin)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
vector<double> misfit_val;
//vector<Points> p(5,0);
//int size=p.size();
  int j=0;
  vector<int> xob,yob;
  vector<int> xcal,ycal;
  vector<int> xon,yon;
	vector<int> xos,yos;
	vector<int> xoe,yoe;
	vector<int> xow,yow;
	int L[MAX]={0};
	
	int i=0;
void movement(double a,double b){
        //generating the list for movement
        while(1) {
	calculate(xob,yob,a,b);
        calculate(xcal,ycal,global_a,global_b);
        double misfit;
	int i=0;
        vector<Dir> d;
        misfit=misfit_cal(yob,ycal);
	cout<<"misfit = "<<misfit<<endl;
        d=random(a,b);
	cout<<d[0].x<<endl;

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
	cout <<"misfit = "<<misfit<<"  "<<"misfit_val[k] = "<<misfit_val[k]<<endl;
        if(misfit >misfit_val[k])
        {
            a=d[k].x;
            b=d[k].y;
		
            L[i++]=misfit_val[k];
	cout<<"val is "<<L[i];
            if((L[i]<L[i-1])&&(L[i]<L[i+1])){
                    cout<<a<<b;
		break;
            }
            
        }
	}
}

}
vector<Dir> random(double a,double b)
    {
        vector<Dir> p;
	Dir obj;
	obj.x=fRand(ROW_MAX -a,a);
	obj.y=fRand((COL_MAX -(b+1)),(b+1));
	p.push_back(obj);
	obj.x=fRand((ROW_MAX -a),a);
	obj.y=fRand((b-1),0);
	p.push_back(obj);
	obj.x=fRand((ROW_MAX -(a+1)),(a+1));
	obj.y=fRand((COL_MAX-b),b);
	p.push_back(obj);
	obj.x=fRand((a-1),0);
	obj.y=fRand((COL_MAX-b),b);
	p.push_back(obj);
        return p;

    }
 
    double misfit_cal(vector<int>& yob,vector<int>& ycal){
        double sum=0,yob_sum=0;
	vector<int> cpy=ycal;
	//cpy= ycal;
	cout<<yob.size()<<"  "<<"ycal.size() = "<<ycal.size()<<"  "<<"cpy.size() = "<<cpy.size();
        while(!yob.empty() && !ycal.empty()){
		//cout<<"in misfit while\n";
            sum +=(yob.back()-ycal.back());
		cout<<"back = "<<yob.back()<<endl;
            yob_sum +=yob.back();
            yob.pop_back();
            ycal.pop_back();
        }
cpy.resize(10);
ycal=cpy;
        return square(sum/yob_sum);
}
    int main()
    {
	cout<<"start\n";

	movement(3.0,7.0);
        //random(3.0,7.0);
        return 0;
    }
