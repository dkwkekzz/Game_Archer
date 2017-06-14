#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <cassert>
using namespace std;
using ull = unsigned long long;
typedef unsigned long long ull;

const int MOD = 10007;
int n, m, s, e;
string board;
int power[100];
int power2[100];

int opposite[50];
map<ull, int> cache[100];

struct node{
	int x, y;
	int dirx, diry;
	node(int nx = 0, int ny = 0, int dx = 0, int dy = 0){
		x = nx, y = ny, dirx = dx, diry = dy;
	}
}start_p, end_p;

int calcPath(){
	int counter = 0;
	for (int i = 0; i < n*m; i++){
		if (board[i] == '?') counter++;
	}
	return power[counter];
}

int search(node& here){
	if (here.x == end_p.x - end_p.dirx && here.y == end_p.y - end_p.diry) {
		//if (board[8] == '?' && board[7] == '.')
		/*{
			for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++){
				cout << board[i*m + j];
				if (j == m - 1) cout << endl;
			}
			cout << "===============\n";
		}*/
		return calcPath();
	}
	if (here.x < 0 || here.x >= m || here.y < 0 || here.y >= n) return 0;

	char &nc = board[here.x + here.y * m];
	int ret = 0, ndx = 0, ndy = 0;
	if (nc == '.') {
		ndx = here.dirx, ndy = here.diry;
		auto nnode = node(here.x + ndx, here.y + ndy, ndx, ndy);
		ret += search(nnode);
	}
	else if (nc == '\\') {
		ndx = here.diry, ndy = here.dirx;
		auto nnode = node(here.x + ndx, here.y + ndy, ndx, ndy);
		ret += search(nnode);
	}
	else if (nc == '/') {
		ndx = -here.diry, ndy = -here.dirx;
		auto nnode = node(here.x + ndx, here.y + ndy, ndx, ndy);
		ret += search(nnode);
	}
	else if (nc == '?') {
		nc = '.';
		ndx = here.dirx, ndy = here.diry;
		auto nnode = node(here.x + ndx, here.y + ndy, ndx, ndy);
		ret += search(nnode);
		nc = '\\';
		ndx = here.diry, ndy = here.dirx;
		nnode = node(here.x + ndx, here.y + ndy, ndx, ndy);
		ret += search(nnode);
		nc = '/';
		ndx = -here.diry, ndy = -here.dirx;
		nnode = node(here.x + ndx, here.y + ndy, ndx, ndy);
		ret += search(nnode);
		nc = '?';
	}
	return ret % MOD;
}

node setPoint(int value){
	if (value <= m) return node(value - 1, 0, 0, 1);
	if (value <= m + n) return node(0, value - m - 1, 1, 0);
	if (value <= m + 2*n) return node(m - 1, value - m - n - 1, -1, 0);
	return node(value - m - 2 * n - 1, n - 1, 0, -1);
}

void precalc(){
	power[0] = 1;
	for (int i = 1; i < 100; i++) power[i] = (power[i - 1] * 3) % MOD;
	power2[0] = 1;
	for (int i = 1; i < 100; i++) power2[i] = (power2[i - 1] * 3) % MOD;
}



inline int calcPath(int index, int value){
	int counter = 0;
	for (int i = index + 1; i < n*m; i++) {
		if (board[i] == '?') counter++;
	}
	return (value * power[counter]) % MOD;
}

inline bool isAnswer(int a, int b){
	return (a == s && b == e) || (a == e && b == s);
}

inline vector<int> getTarget(ull key) {
	vector<int> ret(m + 1);
	for (int i = 0; i < ret.size(); i++, key /= (70)) {
		int value = key % (70);
		ret[i] = value;
	}
	return ret;
}

inline ull getKey(const vector<int>& target, int right) {
	ull ret = 0, exp = 1;
	for (int i = 0; i < target.size(); i++, exp *= (70)) {
		if (target[i] == s) ret += s * exp;
		else if (target[i] == e) ret += e * exp;
		else if (target[i] == right) ret += right * exp;
		else if (target[i] == right - n + 1) ret += (right - n + 1) * exp;
		else if (target[i] > m + 2 * n) ret += (target[i]) * exp;
	}
	return ret;
}

int solve(){
	int ret = 0;
	vector<int> init;
	for (int i = 1; i <= m + 1; i++) init.push_back(i);
	cache[0][getKey(init, 0)] = 1;
	for (int i = 0; i < n*m; i++){
		const int x = i % m, y = i / m;
		const int left = y + m + 1, right = y + m + n + 1;
		const int bottom = x + m + 2 * n + 1;
		for (auto iter = cache[i].begin(); iter != cache[i].end(); iter++){
			const char c = board[i];
			const ull key = (*iter).first;
			const int counter = (*iter).second;
			if (c == '.' || c == '?'){
				vector<int> target = getTarget(key);
				bool isBreak = false;
				assert(target[x] <= right || target[x] > m + 2 * n);
				assert(target[m] <= right || target[m] > m + 2 * n);
				if (y == n - 1) {
					if (target[x] < bottom && target[x] != right) { // 모두 내부에 있다면
						if (isAnswer(bottom, target[x])) {
							ret = (ret + calcPath(i, counter)) % MOD;
							isBreak = true;
						}
					}
				}
				if (!isBreak && x == m - 1) {
					if (target[m] <= right) { // 모두 내부에 있다면
						if (isAnswer(right, target[m])) {
							ret = (ret + calcPath(i, counter)) % MOD;
							isBreak = true;
						}
					}
					target[m] = left + 1;
				}
				if (!isBreak) {
					int& next_counter = cache[i + 1][getKey(target, right)];
					next_counter += counter;
					next_counter %= MOD;
				}
			}
			if (c == '\\' || c == '?'){
				vector<int> target = getTarget(key);
				bool isBreak = false;
				auto temp = target;
				swap(target[x], target[m]); // 들어가는 경로
				for (int& t : target) { // 나가는 경로
					if (t == right) t = bottom;
					else if (t == bottom) t = right;
				}
				assert(target[x] <= right || target[x] > m + 2 * n);
				assert(target[m] <= right || target[m] > m + 2 * n);
				if (y == n - 1) {
					if (target[x] < bottom && target[x] != right) { // 모두 내부에 있다면
						if (isAnswer(bottom, target[x])) {
							ret = (ret + calcPath(i, counter)) % MOD;
							isBreak = true;
						}
					}
				}
				if (!isBreak && x == m - 1) {
					if (target[m] <= right) { // 모두 내부에 있다면
						if (isAnswer(right, target[m])) {
							ret = (ret + calcPath(i, counter)) % MOD;
							isBreak = true;
						}
					}
					target[m] = left + 1;
				}
				if (!isBreak) {
					int& next_counter = cache[i + 1][getKey(target, right)];
					next_counter += counter;
					next_counter %= MOD;
				}

			}
			if (c == '/' || c == '?'){
				vector<int> target = getTarget(key);
				bool isBreak = false;
				bool isInner_top = false, isInner_left = false;
				assert(target[x] <= right || target[x] > m + 2 * n);
				assert(target[m] <= right || target[m] > m + 2 * n);
				int top_t = target[x], left_t = target[m];
				for (int& t : target) {
					if (t == right) t = top_t;
					else if(t == bottom) t = left_t;
				}
				target[x] = right; target[m] = bottom; // 들어가는 경로
				isInner_top = top_t < right;
				isInner_left = left_t < right;
				if (x == m - 1){
					isInner_top |= (top_t == right);
					isInner_left |= (left_t == right);
				}
				if (y == n - 1){
					isInner_top |= (top_t <= bottom);
					isInner_left |= (left_t <= bottom);
				}
				if (isInner_top && isInner_left) { // 나가는 경로
					if (isAnswer(top_t, left_t)) {
						ret = (ret + calcPath(i, counter)) % MOD;
						isBreak = true;
					}
				}
				if (y == n - 1 && x == m - 1){
					if (isAnswer(right, bottom))
						ret = (ret + calcPath(i, counter)) % MOD;
				}
				if (!isBreak && x == m - 1) {
					target[m] = left + 1;
				}
				if (!isBreak) {
					int& next_counter = cache[i + 1][getKey(target, right)];
					next_counter += counter;
					next_counter %= MOD;
				}
			}
			//next j
		}
		//next i
	}
	return ret;
}

int main() {
	FILE *stream; freopen_s(&stream, "input.txt", "r", stdin);
	cin.sync_with_stdio(false);
	cin >> n >> m >> s >> e;
	board.resize(n*m);
	for (int i = 0; i < n * m; i++) cin >> board[i];
	//scaffolding
	{
		start_p = setPoint(s);
		end_p = setPoint(e);
		precalc();
		string made = "";
		cout << search(start_p) << endl;
	}
	//solve
	{
		cout << solve() << endl;
	}

	return 0;
}