#include<bits/stdc++.h>
#include<vector>
#include<list>
#include<math.h>
//#include"header.h"
using namespace std;
#define PI 3.14


typedef struct start_pt
{
        double x_c;
        double y_c;
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
				list<Point> vertex(2*Num_Seg);
				Point p0;
				p0.y_c=Seg[0].y_c;
				p0.x_c=Seg[0].x_c;
				for(i=1;i<2*Num_Seg;i+=1)
				{
					if(p0.y_c>Seg[i].y_c)
					{
						p0.y_c=Seg[i].y_c;
						p0.x_c=Seg[i].x_c;
					}
					else if(p0.y_c==Seg[i].y_c)
					{
						if(p0.x_c>Seg[i].x_c)
						{
							p0.y_c=Seg[i].y_c;
							p0.x_c=Seg[i].x_c;
						}
					}
				}
				cout<<"MIN POINT :"<<p0.x_c<<"\t"<<p0.y_c<<"\n";
				vertex.push_front(p0);
			//	int slope=(Seg[i].y_c-vertex[0].y_c)/(Seg[i].x_c-vertex.x_c)
				list<Point> dummy(2*Num_Seg);
				 for(i=0;i<2*Num_Seg;i++)
				 {
					 if(Seg[i].x_c==p0.x_c && Seg[i].y_c==p0.y_c)
					 {
						 swap(Seg[i].x_c,Seg[0].x_c);
						 swap(Seg[i].y_c,Seg[0].y_c);
						 break;
					 }
				 }
				for(i=1;i<2*Num_Seg;i++)
				{
					for(j=1;j<2*Num_Seg-1;j++)
					{
					if(Seg[j].y_c!=p0.y_c && Seg[j].x_c!=p0.x_c)
					{
						if((atan2((Seg[j].y_c-p0.y_c),(Seg[j].x_c-p0.x_c))*180/PI) > (atan2((Seg[j+1].y_c-p0.y_c),(Seg[j+1].x_c-p0.x_c))*180/PI))
						{
								swap(Seg[j].x_c,Seg[j+1].x_c);
								swap(Seg[j].y_c,Seg[j+1].y_c);
						}
					}
					}		
				}
				for(i=0;i<2*Num_Seg;i++)
					cout<<Seg[i].x_c<<"\t"<<Seg[i].y_c<<"\n";
				vertex.push_front(Seg[1]);
				vertex.push_front(Seg[2]);
				dummy=vertex;
				dummy.pop_front();
				for(i=3;i<2*Num_Seg;i++)
				{
					while(DIRECTION(vertex.front(),dummy.front(),Seg[i])>0)
					{
						vertex.pop_front();
						dummy=vertex;
						//vertex.push_front(Seg[i]);
					}
						//dummy=vertex;
						vertex.push_front(Seg[i]);
				}
				for(list<Point>::iterator it=vertex.begin();it!=vertex.end();it++)
				{
					cout<<"X CO: "<<it->x_c<<"\n";
					cout<<"Y CO: "<<it->y_c<<"\n";
				}
				cout<<"NO. OF VERTEX: "<<vertex.size()<<"\n";
       }
        return 0;
}



