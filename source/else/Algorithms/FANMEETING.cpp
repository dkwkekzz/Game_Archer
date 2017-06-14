#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int m, n;

vector<int> multiply(const vector<int> &a, const vector<int> &b) {
	int as = a.size(), bs = b.size();
	vector<int> c(as + bs + 1, 0);
	for (int i = 0; i < as; i++)
		for (int j = 0; j < bs; j++)
			c[i + j] += a[i] * b[j];
	return c;
}

vector<int> add(const vector<int> &a, const vector<int> &b, int k) {
	int as = a.size(), bs = b.size();
	vector<int> c(max(as, bs + k), 0);
	for (int i = k; i < bs + k; i++) c[i + k] = b[i];
	for (int i = 0; i < max(as, bs + k); i++) c[i] += a[i];
	return c;
}

vector<int> sub(const vector<int> &a, const vector<int> &b) {
	int as = a.size(), bs = b.size();
	if (bs > as) sub(b, a);
	vector<int> c(as, 0);
	for (int i = 0; i < as; i++) c[i] = a[i] - b[i];
	return c;
}

vector<int> karatsuba(const vector<int> &a, const vector<int> &b) {
	int as = a.size(), bs = b.size();
	if (as == 0 || bs == 0) return vector<int>();
	if (bs > as) karatsuba(b, a);
	if (as < 50) return multiply(a, b);

	int half = as / 2;
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b1(b.begin() + min<int>(bs, half), b.end());
	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> b0(b.begin(), b.begin() + min<int>(bs, half));
	vector<int> z2 = karatsuba(a1, b1);
	vector<int> z0 = karatsuba(a0, b0);
	vector<int> z1 = sub(karatsuba(add(a0, a1, 0), add(b0, b1, 0)), add(z2, z0, 0));
	vector<int> ret;
	return add(add(add(ret, z0, 0), z1, half), z2, as);
}

int hug(const vector<int> &member, const vector<int> &fan) {
	int count = 0;
	vector<int> ret;
	ret = karatsuba(fan, member);
	for (int i = m; i <= n; i++) {
		if (ret[i] == 0) count++;
	}
	return count;
}

int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		vector<int> member;
		vector<int> fan;
		string str1, str2;
		cin >> str1;
		m = str1.size() - 1;
		for (int j = m; j >= 0; j--) {
			if (str1[j] == 'M') member.push_back(1);
			else member.push_back(0);
		}
		cin >> str2;
		n = str2.size() - 1;
		for (int j = 0; j <= n; j++) {
			if (str2[j] == 'M') fan.push_back(1);
			else fan.push_back(0);
		}
		cout << hug(member, fan) << endl;
	}
}