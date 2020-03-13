#include<bits/stdc++.h>
#include<vector>
//#include"header.h"
using namespace std;


typedef struct start_pt
{
        int x_c;
        int y_c;
        int e;
}Point;


int DIRECTION(Point P1,Point P2,Point P3)
{
	return((P3.x_c-P1.x_c)*(P2.y_c-P1.y_c)-(P2.x_c-P1.x_c)*(P3.y_c-P1.y_c));
	//return (P3-P1)*(P2-P1) vector product returns
}

int min(int a , int b)
{
	if(a<b)
			return a;
	else 
		return b;
}

int max(int a, int b)
{
	if(a>b)
			return a;
	else return b;
}

bool ON_SEGMENT(Point P1,Point P2,Point P3)
{
	if(min(P1.x_c,P2.x_c)<=P3.x_c && max(P1.x_c,P2.x_c)>=P3.x_c && min(P1.y_c,P2.y_c)<=P3.y_c && max(P1.y_c,P2.y_c)>=P3.y_c)
		return true;
	else if(min(P1.x_c,P2.x_c)>=P3.x_c && (min(P1.y_c,P2.y_c)>=P3.y_c || max(P1.y_c,P2.y_c)<=P3.y_c))
		return true;
	if(max(P1.x_c,P2.x_c)<=P3.x_c && (min(P1.y_c,P2.y_c)>=P3.y_c && max(P1.y_c,P2.y_c)<=P3.y_c))
		return true;
	else 
		false;
}




int main()
{
        ifstream fin;
        fin.open("infile.in");
        int NUM_TEST,iter;
        fin>>NUM_TEST;
        for(iter=0;iter<NUM_TEST;iter++)
        {
                int Num_Seg,i;
                fin>>Num_Seg;
		vector<Point> Seg(2*Num_Seg);
                cout<<"TEST CASE:"<<iter+1<<"\n";
		for(i=0;i<2*Num_Seg;i+=2)
                {
                        fin>>Seg[i].x_c;
                        fin>>Seg[i].y_c;
                        Seg[i].e=0;
                        fin>>Seg[i+1].x_c;
                        fin>>Seg[i+1].y_c;
                        Seg[i].e=1;
                }
                int d1,d2,d3,d4,num_seg=0,j;
                for(i=0;i<2*Num_Seg-2;i+=2){
					for(j=i+2;j<2*Num_Seg;j+=2)
					{
                d1=DIRECTION(Seg[j],Seg[j+1],Seg[i]);
                d2=DIRECTION(Seg[j],Seg[j+1],Seg[i+1]);
                d3=DIRECTION(Seg[i],Seg[i+1],Seg[j]);
                d4=DIRECTION(Seg[i],Seg[i+1],Seg[j+1]);
                if(((d1>0 && d2<0)||(d1<0 && d2>0))&&((d3>0 && d4<0)||(d3<0 && d4>0)))
                        cout<<num_seg+1<<"th segment cuts with "<<j/2+1<<"th segment\n";
                else if(d1==0 && ON_SEGMENT(Seg[j],Seg[j+1],Seg[i]))
                        cout<<num_seg+1<<"th segment overlaps with "<<j/2+1<<"th segment\n";
                else if(d2==0 && ON_SEGMENT(Seg[j],Seg[j+1],Seg[i+1]))
                        cout<<num_seg+1<<"th segment overlaps with "<<j/2+1<<"th segment\n";
                else if(d3==0 && ON_SEGMENT(Seg[i],Seg[i+1],Seg[j]))
                        cout<<num_seg+1<<"th segment overlaps with "<<j/2+1<<"th segment\n";
                else if(d4==0 && ON_SEGMENT(Seg[i],Seg[i+1],Seg[j+1]))
                        cout<<num_seg+1<<"th segment overlaps with "<<j/2+1<<"th segment\n";
                else
                        cout<<num_seg+1<<"th segment does not cut with "<<j/2+1<<"th segment\n";

				}
								num_seg++;
				}
     //  			cout<<Seg[5].x_c<<"\t"<<Seg[5].y_c<<"\n";
       }
        return 0;
}




