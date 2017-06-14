#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <cmath>
#include <windows.h>
using namespace std;

LARGE_INTEGER Frequency;
LARGE_INTEGER BeginTime;
LARGE_INTEGER Endtime;

const int INF = 987654321, MAX_N = 505;
int n, m, c;
string melody[MAX_N]; //int test1, test2;
int tokens[MAX_N*MAX_N];
vector<int> sa;
vector<vector<int> > psa;

struct Comparator{
	const vector<int>& group;
	int t;
	Comparator(const vector<int>& _group, int _t): group(_group), t(_t){}
	bool operator()(int i, int j){
		if (group[i] != group[j]) return group[i] < group[j];
		return group[i + t] < group[j + t];
	}
};

vector<int> getSuffixArray(const string& s){
	int t = 1, n = s.size();
	vector<int> group(n + 1);
	for (int i = 0; i < n; i++) { 
		group[i] = s[i]; 
	}
	group[n] = -1;
	
	vector<int> perm(n);
	for (int i = 0; i < n; i++) { perm[i] = i; }
	while (t < n){
		Comparator compareUsing2T(group, t);
		sort(perm.begin(), perm.end(), compareUsing2T);
		t *= 2;
		if (t >= n) break;
		vector<int> newGroup(n + 1);
		newGroup[n] = -1;
		newGroup[perm[0]] = 0;
		for (size_t i = 1; i < n; i++){
			if (compareUsing2T(perm[i - 1], perm[i]))
				newGroup[perm[i]] = newGroup[perm[i - 1]] + 1;
			else newGroup[perm[i]] = newGroup[perm[i - 1]];
		}
		group = newGroup;
	}
	return perm;
}

vector<int> kasai(const string& s, const vector<int>& sa){
	int n = s.size(), k = 0;
	vector<int> lcp(n, 0), rank(n, 0);
	for (int i = 0; i<n; i++) rank[sa[i]] = i;
	for (int i = 0; i<n; i++, k ? k-- : 0){
		if (rank[i] == n - 1) { k = 0; continue; }
		int j = sa[rank[i] + 1];
		while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
			if (s[i + k] == '$') break;
			k++;
		}
		lcp[rank[i]] = k;
	}
	return lcp;
}

vector<vector<int> > getPSA(){
	vector<vector<int> > ret(n);
	for (int i = 0; i < sa.size(); i++){
		int color = tokens[sa[i]];
		ret[color].push_back(i);
	}
	return ret;
}

int cache_ch[MAX_N][1 << 6];
int check(int start, int selected){
	int &ret = cache_ch[start][selected];
	if (ret != -1) return ret;

	string ps;
	vector<int> mpsa;
	selected = (selected * 2) + 1;
	for (int i = selected, j = 0; i; i >>= 1, j++){
		if (i & 1) {
			int e = j + start;
			if (e >= n) return ret = -INF;
			ps += melody[e] + "$";
			for (int j = 0; j < psa[e].size(); j++){
				mpsa.push_back(psa[e][j]);
			}
		}
	}
	sort(mpsa.begin(), mpsa.end());
	vector<pair<int, int> > psaData;
	for (int i = 0; i < mpsa.size(); i++){
		int e = sa[mpsa[i]];
		psaData.push_back(make_pair(e, i));
	}
	sort(psaData.begin(), psaData.end());
	for (int i = 0; i < mpsa.size(); i++){
		mpsa[psaData[i].second] = i;
	}

	vector<int> lcp = kasai(ps, mpsa);
	if (start == 1 && selected == 15)
	{
		cout << "start: " << start << " selected: " << selected << endl;
		cout << endl;
		printf(" i sa lcp\n");
		for (int i = 0; i < mpsa.size(); i++){
			int csa = mpsa[i];
			string cs = ps.substr(csa, ps.size());
			printf("%2d %2d %2d s: %d ", i, csa, lcp[i], tokens[psaData[csa].first]);
			cout << cs << endl;
		}
		cout << endl;
	}

	ret = 0;
	int state = 0, val = INF;
	deque<int> dq;
	for (int i = 0; i < c; i++){
		int cs = tokens[psaData[mpsa[i]].first];
		state |= (1 << (cs - start));
		dq.push_back(cs);
	}
	for (int i = 0; i < lcp.size(); i++){
		int cs = tokens[psaData[mpsa[i]].first];
		state |= (1 << (cs - start));
		if (state == selected) ret = max(ret, val);
		if (lcp[i] == 0){
			state = 0, val = INF;
		}
		else{
			val = min(val, lcp[i]);
		}
	}
	cout << "ret: " << ret << endl;
	cout << endl;
	return ret;
}

int cache[MAX_N][1 << 7];
int mixing(int start, int state){
	if (start >= n) return 0;

	int &ret = cache[start][state];
	if (ret != -1) return ret;

	ret = mixing(start + 1, state >> 1);
	if (state & 1) return ret;
	else state >>= 1;
	for (int i = 1; i < (1 << m); i++){
		int curState = i & ~state;
		//__builtin_popcount(curState) == c-1
		if (__popcnt(curState) == c - 1){
			ret = max(ret, check(start, curState)
				+ mixing(start + 1, (curState | state)));
		}
	}
	return ret;
}

int main(){
	string s;
	/*FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);
	cin >> n >> m >> c;
	
	for (int i = 0, token = 0; i < n; i++, token = s.size()) {
		cin >> melody[i];
		s += melody[i] + "$";
		for (int j = token; j < s.size(); j++){ tokens[j] = i; }
	}*/
	//QueryPerformanceFrequency((LARGE_INTEGER *)&Frequency);
	
	memset(cache_ch, -1, sizeof(cache_ch));
	memset(cache, -1, sizeof(cache));

	n = 25, m = 6, c = 4;
	for (int i = 0, token = 0; i < n; i++, token = s.size()) {
		for (int j = 0; j < 25; j++){
			melody[i] += ('a' + rand() % 7);
		}
		s += melody[i] + "$";
		for (int j = token; j < s.size(); j++){ tokens[j] = i; }
	}
	/*QueryPerformanceCounter((LARGE_INTEGER *)&BeginTime);

	QueryPerformanceCounter(&Endtime);
	long long elapsed = Endtime.QuadPart - BeginTime.QuadPart;
	double duringtime = (double)elapsed / (double)Frequency.QuadPart;
	cout << "time: " << duringtime << endl;*/

	sa = getSuffixArray(s);
	psa = getPSA();

	cout << mixing(0, 0) << endl;

	return 0;
}
