#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int m, q, n;
double B[500], T[500][500], M[500][500], cashe[501][501];
int Q[500];
string word[500], result[500];

double classify(int first, int second){
	if(second == n) return 1.0;

	double &ret = cashe[first][second];
	if(ret != 1.0) return ret;

	ret = -1e200;
	int best = -1;
	for(int i = 0; i < m; i++){
		double cand;
		if(second == 0){
			cand = B[i] * M[Q[second]][i] + classify(i, second + 1);
		}
		else{
			cand = T[first][i] * M[Q[second]][i] + classify(i, second + 1);
		}
		if(cand > ret){
			ret = cand;
			best = i;
		}
	}
	result[second] = word[best];

	return ret;
}

int main(){
	memset(cashe, 1.0, sizeof(cashe));
	cin >> m >> q;
	for(int i = 0; i < m; i++)
		cin >> word[i];
	for(int i = 0; i < m; i++)
		cin >> B[i];
	for(int i = 0; i < m; i++)
		for(int j = 0; j < m; j++)
			cin >> T[i][j];
	for(int i = 0; i < m; i++)
		for(int j = 0; j < m; j++)
			cin >> M[i][j];
	
	for(int i = 0; i < q; i++){
		cin >> n;
		for(int j = 0; j < n; j++){
			string nString;
			cin >> nString;
			for(int k = 0; k < m; k++)
				if(nString == word[k])
					Q[j] = k;
		}
		classify(0, 0);
		for(int j = 0; j < n; j++)
			cout << result[j] << " ";
		cout << endl;
	}
}

