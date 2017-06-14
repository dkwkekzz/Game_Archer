#include <cstdio>
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

const int MAX_N = 2001, MAX_M = 1000000;
int n, m;
int N[MAX_N];
int cache[MAX_N][MAX_N];

int isPalindrome(int s, int e){
	if (s >= e) return 1;

	int &ret = cache[s][e];
	if (ret != -1) return ret;

	return ret = (N[s] == N[e] ? isPalindrome(s + 1, e - 1) : 0);
}

int main(){
	cin.sync_with_stdio(false);
	memset(cache, -1, sizeof(cache));
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> N[i];
	}
	cin >> m;
	for (int i = 0; i < m; i++){
		int a, b; cin >> a >> b;
		cout << isPalindrome(a, b) << endl;
	}

	return 0;
}