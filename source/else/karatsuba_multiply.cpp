#include "karatsuba_multiply.h"

//자릿수 올림 처리
void normalize(vector<int>& a){
	int n = a.size();
	//자릿수가 올라갈 수 있으므로 0을 삽입한다.
	a.push_back(0);

	for (int i = 0; i < n; i++){
		//해당 숫자가 음수라면
		if (a[i] < 0){
			//만일 -11을 처리한다면, 음수를 모두 없앤다음(9를 더해야 모든 수를 올릴 수 있고 0때문에 10보다는 작아야 한다.)
			//-11 + 20으로 계산한다.
			int borrow = (abs(a[i]) + 9) / 10;
			//20을 빌려준다.
			a[i + 1] -= borrow;
			a[i] += borrow * 10;
		}
		else{
			a[i + 1] += a[i] / 10;
			a[i] %= 10;
		}
	}
	//0이 아닌 수에서 앞자리부터 0인 부분을 삭제한다.
	while (a.size() > 1 && a.back() == 0) a.pop_back();
}

//multiply({3, 2, 1}, {6, 5, 4}) = 123 * 456
vector<int> multiply(const vector<int>& a, const vector<int>& b){
	vector<int> c(a.size() + b.size() + 1, 0);

	for (int i = 0; i < a.size(); i++){
		for (int j = 0; j < b.size(); j++){
			c[i + j] += a[i] * b[j];
		}
	}
	normalize(c);

	return c;
}

//a += b * (10^k);
void addTo(vector<int>& a, const vector<int>& b, int k){
	int n;
	if (a.size() >= b.size() + k){
		n = b.size() + k;
	}
	else{
		n = a.size();
		for (int i = n; i < b.size() + k; i++) a.push_back(0);
	}

	for (int i = k; i < n; i++){
		a[i] += b[i - k];
	}

	normalize(a);
}

//a -= b; (a >= b)
void subFrom(vector<int>& a, const vector<int>& b){
	int n = b.size();

	for (int i = 0; i < n; i++){
		a[i] -= b[i];
	}

	normalize(a);
}

//두 긴 정수의 곱: 카라츠바 정수 곱셈
vector<int> karatsuba(const vector<int>& a, const vector<int>& b){
	int an = a.size(), bn = b.size();

	//a가 b보다 크게 포맷한다.
	if (an < bn) return karatsuba(b, a);

	//기저사례: a나 b가 0인 경우 -> 0을 반환한다.
	if (an == 0 || bn == 0) return vector<int>();

	//기저사례: 크기가 50자리보다 작은 경우 일반 곱셈으로 변경한다.
	if (an <= 50) return multiply(a, b);

	int half = an / 2;
	//a와 b를 절반(처음을 기준으로 half만큼)으로 분할한다.
	//한 부분이라도 자릿수가 맞는 것이 연산면에서 이득이므로 각 절반이 아닌, an / 2를 기준으로 분할한다.
	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
	vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());

	//(a0 + a1) * (b0 + b1) = a0*b0 + (a1*b0 + a0*b1) + a1*b1 = z0 + z1 + z2
	vector<int> z2 = karatsuba(a1, b1);
	vector<int> z0 = karatsuba(a0, b0);
	//(a1*b0 + a0*b1) = z1 = (a0 + a1) * (b0 + b1) - z0 - z2
	addTo(a0, a1, 0); addTo(b0, b1, 0);
	vector<int> z1 = karatsuba(a0, b0);
	subFrom(z1, z0); subFrom(z1, z2);

	//ret = z2 * 10^an + z1 * 10^half + z2
	vector<int> ret;
	addTo(ret, z2, an);
	addTo(ret, z1, half);
	addTo(ret, z0, 0);

	return ret;
}

//벡터 안의 숫자 출력
void printNumber(const vector<int>& a){
	int n = a.size();

	cout << "a = ";
	for (int i = 0; i < n; i++){
		cout << a[n - 1 - i];
	}
	cout << endl;
}