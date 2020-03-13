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
        else
                false;
}




int main()
{
		int input[8]={5,6,46,6,10,6,34,6};
                vector<Point> Seg(2*4);
		int i,j;
                for(i=0,j=0;i<4,j<8;i+=2,j+=4)
                {
                        Seg[i].x_c=input[j];
                        Seg[i].y_c=input[j+1];
                        Seg[i].e=0;
                        Seg[i+1].x_c =input[j+2];
                        Seg[i+1].y_c=input[j+3];
                        Seg[i+1].e=1;
                }
                int d1,d2,d3,d4,num_seg=0;
                
                d1=DIRECTION(Seg[2],Seg[3],Seg[0]);
                d2=DIRECTION(Seg[2],Seg[3],Seg[1]);
                d3=DIRECTION(Seg[0],Seg[1],Seg[2]);
                d4=DIRECTION(Seg[0],Seg[1],Seg[3]);
                if(((d1>0 && d2<0)||(d1<0 && d2>0))&&((d3>0 && d4<0)||(d3<0 && d4>0)))
                        cout<<num_seg+1<<"th segment cuts with "<<j/2+1<<"th segment\n";
                else if(d1==0 && ON_SEGMENT(Seg[2],Seg[3],Seg[0]))
                        cout<<num_seg+1<<"th segment over with "<<j/2+1<<"th segment\n";
                else if(d2==0 && ON_SEGMENT(Seg[2],Seg[3],Seg[1]))
                        cout<<num_seg+1<<"th segment over with "<<j/2+1<<"th segment\n";
                else if(d3==0 && ON_SEGMENT(Seg[0],Seg[1],Seg[2]))
                        cout<<num_seg+1<<"th segment over with "<<j/2+1<<"th segment\n";
                else if(d4==0 && ON_SEGMENT(Seg[0],Seg[1],Seg[3]))
                        cout<<num_seg+1<<"th segment over with "<<j/2+1<<"th segment\n";
                else
                        cout<<num_seg+1<<"th segment does not cut with "<<j/2+1<<"th segment\n";

                              
                     //   cout<<Seg[5].x_c<<"\t"<<Seg[5].y_c<<"\n";
   
        return 0;
}

