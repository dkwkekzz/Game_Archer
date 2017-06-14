#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void normalize(vector<int> &c) {
	c.push_back(0);
	int cs = c.size();
	for (int i = 0; i < cs; i++) {
		if (c[i] < 0) {
			int borrow = (abs(c[i]) + 9) / 10;
			c[i + 1] -= borrow;
			c[i] += borrow * 10;
		}
		else {
			c[i + 1] += c[i] / 10;
			c[i] %= 10;
		}
	}
	while (c.back() == 0 && c.size() > 1) c.pop_back();
}

vector<int> multiply(const vector<int> &a, const vector<int> &b) {
	int as = a.size(), bs = b.size();
	vector<int> c(as + bs + 1, 0);
	for (int i = 0; i < as; i++)
		for (int j = 0; j < bs; j++)
			c[i + j] += a[i] * b[j];
	normalize(c);
	return c;
}

vector<int> add(const vector<int> &a, const vector<int> &b, int k) {
	int as = a.size(), bs = b.size();
	vector<int> c(max(as, bs + k), 0);
	for (int i = k; i < bs + k; i++) c[i + k] = b[i];
	for (int i = 0; i < max(as, bs + k); i++) c[i] += a[i];
	normalize(c);
	return c;
}

vector<int> sub(const vector<int> &a, const vector<int> &b) {
	int as = a.size(), bs = b.size();
	if (bs > as) sub(b, a);
	vector<int> c(as, 0);
	for (int i = 0; i < as; i++) c[i] = a[i] - b[i];
	normalize(c);
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