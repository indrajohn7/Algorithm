#include<bits/stdc++.h>
#define STREAM_LENGTH 20
#define WORD_NUM 100

using namespace std;

class trie{
	
	public:
		char key;
		int load;
		bool visited;
		trie* parent;
		trie** child;
		trie(char w, trie* par)
		{
			key = w;
			visited = false;
			parent = par;
		}
};

void populate_stream(char history[][WORD_NUM][STREAM_LENGTH], int N)
{
	char* save = NULL;
	char* token = NULL;
	FILE* fp = fopen("trie.in","r");
	char* buff = new char[1000];
	int i,j;
	i = j = 0;
	fgets(buff, 1000, fp);
	while(fgets(buff, 1000, fp) != NULL){
		if(i >= N)
			break;
		token = strtok_r(buff, " \n", &save);
		while(token != NULL){

			int len = strlen(token);
			strncpy(history[i][j], token, len);

			if (strchr(token, '.') != NULL){
				history[i][j][len-1] = '\0';
				i++;
				j = 0;
			} else{
				history[i][j][len] = '\0';
				j++;
			}

			token = strtok_r(NULL, " \n", &save);
		}		
	}
}

void print_stream(char history[][WORD_NUM][STREAM_LENGTH], int N)
{
	int row = N;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < WORD_NUM; j++){
			if(history[i][j][0] != '\0'){
				cout<<history[i][j]<<"\t";
			}
		}
		cout<<endl;
	}
}

int main()
{
	trie* tr = new trie('0',NULL);
	ifstream fin;
	fin.open("trie.in");
	int N;
	fin>>N;
	char history[N][WORD_NUM][STREAM_LENGTH];
	for(int i = 0;i < N;i++){
		for(int j = 0; j < WORD_NUM; j++){
			memset(history[i][j], '\0', STREAM_LENGTH);
		}
	}
	populate_stream(history, N);
	
	print_stream(history,N);

	return 0;

}
