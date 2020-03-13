#include<bits/stdc++.h>

using namespace std;


bool isInterleaved(char* a, char* b, char* c)
{
	int len_c = strlen(c);
	int len_a = strlen(a);
	int len_b = strlen(b);
	bool** T = new bool*[len_a+1];
	for(int i=0;i<=len_a;i++)
		T[i] = new bool[len_b+1];
	T[0][0] = true;
	
	if(len_c != (len_a + len_b))
		return false;

	for(int i=0;i<len_b;i++){
		if(c[i] == b[i] && T[0][i] == true)
			T[0][i+1] = true;
		else
			T[0][i+1] = false;
	} 
	for(int i=0;i<len_a;i++){
		if(c[i] == a[i] && T[i][0] == true)
			T[i+1][0] = true;
		else
			T[i+1][0] = false;
	}
	for(int i=1;i<=len_a;i++){
		for(int j=1;j<=len_b;j++){
			if(c[i+j-1] == a[i-1] && T[i-1][j] == true)
				T[i][j] = true;
			else if(c[i+j-1] == b[j-1] && T[i][j-1] == true)
				T[i][j] = true;
			else
				T[i][j] = false;
		}
	}

	return T[len_a][len_b];

}

// A function to run test cases
void test(char *A, char *B, char *C)
{
    if (isInterleaved(A, B, C))
        cout << C <<" is interleaved of " << A <<" and " << B << endl;
    else
        cout << C <<" is not interleaved of " << A <<" and " << B << endl;
}
 
 
// Driver program to test above functions
int main()
{
    test("XXY", "XXZ", "XXZXXXY");
    test("XY" ,"WZ" ,"WZXY");
    test ("XY", "X", "XXY");
    test ("YX", "X", "XXY");
    test ("XXY", "XXZ", "XXXXZY");
    return 0;
}
