#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> pi;
typedef pair<int,pi> pii;
typedef map<int,pi> vmap;

int max_freq(vmap work)
{
	int max =-1;
	for(vmap::iterator it = work.begin(); it != work.end(); it++){
		int count = 0, quot = it->first;
		int num = it->second.first;
		while(num < it->second.second){
			count++;
			num = num*quot;
		}
		if(count > max)
			max = count;
	}
	return max+1;
}

int lenOfLongestGP(int* set, int N)
{
	int max = 1;
	sort(set, set+N);
	vmap work;
	for(int i=1;i<N;i++){
		for(int j=0;j<i;j++){
			int quot = 1, remainder = 0;
			quot = set[i]/set[j];
			remainder = set[i]%set[j];
			if(remainder == 0){
				vmap::iterator it = work.begin();
				it = work.find(quot);
				if(it == work.end()){
					work[quot] = make_pair(set[j],set[i]);
				} else {
					it->second.second = set[i];
				}
			}
		}
	}
	int res = max_freq(work);
	return res;
}


int main()
{
	int set1[] = {1, 3, 9, 27, 81, 243};
    int n1 = sizeof(set1)/sizeof(set1[0]);
    cout << lenOfLongestGP(set1, n1) << "\n";
 
    int set2[] = {1, 3, 4, 9, 7, 27};
    int n2 = sizeof(set2)/sizeof(set2[0]);
    cout << lenOfLongestGP(set2, n2) << "\n";
 
    int set3[] = {2, 3, 5, 7, 11, 13};
    int n3 = sizeof(set3)/sizeof(set3[0]);
    cout << lenOfLongestGP(set3, n3) << "\n";
	
	return 0;
}
