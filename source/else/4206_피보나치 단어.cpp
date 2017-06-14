#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <cmath>
using namespace std;
typedef long long int64;
const int MAX_N = 100 + 5;
int tc, n;
string p;
int64 fibonacci[MAX_N]; 
vector<int> pi;

void getPartialMatch(const string& N){
	int n = N.size();
	int begin = 1, matched = 0;
	pi = vector<int>(n, 0);
	while (begin + matched < n){
		if (N[begin + matched] == N[matched]){
			matched++;
			pi[begin + matched - 1] = matched;
		}
		else{
			if (matched == 0) begin++;
			else{
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
}

bool kmpSearch(const string& H, const string& p, int start){
	int h = H.size(), ps = p.size();
	int begin = max(0, start), matched = 0;
	while (begin < start + ps - 1){
		if (matched < ps && H[begin + matched] == p[matched]){
			matched++;
			if (matched == ps) return true;
		}
		else{
			if (matched == 0) begin++;
			else{
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return false;
}

int64 findPattern(){
	string patterns[3];
	int64 ret = 0;
	patterns[0] = "0", patterns[1] = "1";
	if (p == "0") {
		if (n == 0) return 1;
		return fibonacci[n - 2 + 1];
	}
	if (p == "1")
		return fibonacci[n - 1 + 1];
	for (int i = 2; i <= n; i++){
		patterns[i % 3] = patterns[(i - 1) % 3] + patterns[(i - 2) % 3];
		if (kmpSearch(patterns[i % 3], p, patterns[(i-1)%3].size() - p.size() + 1)) 
			ret += fibonacci[n - i + 1];
		if (patterns[(i - 2) % 3].size() >= p.size()) 
			patterns[i % 3] = patterns[(i - 2) % 3];
	}
	return ret;
}

void precalc(){
	fibonacci[1] = 1;
	for (int i = 2; i < MAX_N; i++)
		fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);
	
	cin.sync_with_stdio(false);
	precalc();
	while (cin >> n >> p){
		if (n < 0) break;
		getPartialMatch(p);
		cout << "Case " << ++tc << ": " << findPattern() << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}