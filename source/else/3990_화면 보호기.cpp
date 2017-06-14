#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <cmath>
using namespace std;
typedef long double ldouble;
struct Node{
	Node() : a(0.0), b(0.0), c(0.0), f(0.0), cnt(0.0) {}
	Node(ldouble _a, ldouble _b, ldouble _c, ldouble _f, ldouble _cnt){
		a = _a, b = _b; c = _c; f = _f; cnt = _cnt;
	}
	ldouble a, b, c, f, cnt;
};
Node operator+(Node na, Node nb){
	na.a += nb.a; na.b += nb.b; na.c += nb.c;
	na.f += nb.f;
	na.cnt += nb.cnt;
	return na;
}
Node operator-(Node na, Node nb){
	na.a -= nb.a; na.b -= nb.b; na.c -= nb.c;
	na.f -= nb.f;
	na.cnt -= nb.cnt;
	return na;
}

const int MAX_N = 100005, MAX_H = 1005;
int n, m, h[MAX_N];
Node S[MAX_N], psum[MAX_H][MAX_H];

void add(int x, int y, Node n, int sgn) {
	for (int i = x + 1; i < MAX_H; i += i & -i)
	for (int j = y + 1; j < MAX_H; j += j & -j)
		psum[i][j] = (sgn == -1) ? (psum[i][j] - n) : (psum[i][j] + n);
}

Node getSum(int x, int y) {
	Node ret(0, 0, 0, 0, 0);
	for (int i = x + 1; i; i -= i & -i)
	for (int j = y + 1; j; j -= j & -j)
		ret = ret + psum[i][j];
	return ret;
}

void update(int i) {
	int h1 = h[i], h2 = h[i + 1];
	ldouble s = min(h1, h2);
	ldouble b = max(h1, h2);

	S[i].a = -(ldouble)0.5 / (b - s);
	S[i].b = (ldouble)b / (b - s);
	S[i].c = -(ldouble)0.5 * s * s / (b - s);
	S[i].f = (ldouble)0.5 * (b + s);
	S[i].cnt = (ldouble)1.0;
	add(h1, h2, S[i], 1);
}

ldouble query1(int h) {
	Node U = getSum(h - 1, h - 1);
	Node R = getSum(h, MAX_H - 2);
	Node F = getSum(MAX_H - 2, h);
	Node T = getSum(MAX_H - 2, MAX_H - 2) - R - F + getSum(h, h);
	R = R - getSum(h, h - 1);
	F = F - getSum(h - 1, h);

	ldouble sol = (ldouble)n * h;
	sol -= U.f;
	sol -= R.a * h * h + R.b * h + R.c;
	sol -= F.a * h * h + F.b * h + F.c;
	sol -= T.cnt * h;

	return sol;
}

void query2(int x0, int nh){
	add(h[x0], h[x0 + 1], S[x0], -1);
	add(h[x0 - 1], h[x0], S[x0 - 1], -1);

	h[x0] = nh;

	update(x0);
	update(x0 - 1);
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> h[i];
	for (int i = 0; i < n - 1; i++) update(i);
	for (int i = 0; i < m; i++){
		int d1, d2; char q; cin >> q >> d1;
		if (q == 'Q'){
			printf("%0.3lf\n", query1(d1));
		}
		else{
			cin >> d2;
			query2(d1, d2);
		}
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}