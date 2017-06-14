#include "karatsuba_multiply.h"

//�ڸ��� �ø� ó��
void normalize(vector<int>& a){
	int n = a.size();
	//�ڸ����� �ö� �� �����Ƿ� 0�� �����Ѵ�.
	a.push_back(0);

	for (int i = 0; i < n; i++){
		//�ش� ���ڰ� �������
		if (a[i] < 0){
			//���� -11�� ó���Ѵٸ�, ������ ��� ���ش���(9�� ���ؾ� ��� ���� �ø� �� �ְ� 0������ 10���ٴ� �۾ƾ� �Ѵ�.)
			//-11 + 20���� ����Ѵ�.
			int borrow = (abs(a[i]) + 9) / 10;
			//20�� �����ش�.
			a[i + 1] -= borrow;
			a[i] += borrow * 10;
		}
		else{
			a[i + 1] += a[i] / 10;
			a[i] %= 10;
		}
	}
	//0�� �ƴ� ������ ���ڸ����� 0�� �κ��� �����Ѵ�.
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

//�� �� ������ ��: ī������ ���� ����
vector<int> karatsuba(const vector<int>& a, const vector<int>& b){
	int an = a.size(), bn = b.size();

	//a�� b���� ũ�� �����Ѵ�.
	if (an < bn) return karatsuba(b, a);

	//�������: a�� b�� 0�� ��� -> 0�� ��ȯ�Ѵ�.
	if (an == 0 || bn == 0) return vector<int>();

	//�������: ũ�Ⱑ 50�ڸ����� ���� ��� �Ϲ� �������� �����Ѵ�.
	if (an <= 50) return multiply(a, b);

	int half = an / 2;
	//a�� b�� ����(ó���� �������� half��ŭ)���� �����Ѵ�.
	//�� �κ��̶� �ڸ����� �´� ���� ����鿡�� �̵��̹Ƿ� �� ������ �ƴ�, an / 2�� �������� �����Ѵ�.
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

//���� ���� ���� ���
void printNumber(const vector<int>& a){
	int n = a.size();

	cout << "a = ";
	for (int i = 0; i < n; i++){
		cout << a[n - 1 - i];
	}
	cout << endl;
}