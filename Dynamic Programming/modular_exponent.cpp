#include<bits/stdc++.h>

using namespace std;

int main()
{
	int iter,Num_Test;
	ifstream fin;
	fin.open("mod.in");
	fin>>Num_Test;
	for(iter=0;iter<Num_Test;iter++){
		int coeff,expo,mod;
		fin>>coeff>>expo>>mod;
		vector<int> v;
		int bin=0;
		while((expo/(pow(2,bin)))){
			if(expo&((int)(pow(2,bin))))
				v.push_back(1);
			else
				v.push_back(0);
			bin++;
		}
		int c=0,d=1;
		for(int i=bin-1;i>=0;i--){
			c=2*c;
			d=(d*d)%mod;
			if(v[i]==1){
				c+=1;
				d=(d*coeff)%mod;
			}
		}
		cout<<"CASE #"<<iter+1<<":\t"<<d<<endl;
	}
	return 0;
}