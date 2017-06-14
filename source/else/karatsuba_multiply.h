#pragma once 
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//�ڸ��� �ø� ó��
void normalize(vector<int>& a);

//multiply({3, 2, 1}, {6, 5, 4}) = 123 * 456
vector<int> multiply(const vector<int>& a, const vector<int>& b);

//a += b * (10^k);
void addTo(vector<int>& a, const vector<int>& b, int k);

//a -= b; (a >= b)
void subFrom(vector<int>& a, const vector<int>& b);

//�� �� ������ ��: ī������ ���� ����
vector<int> karatsuba(const vector<int>& a, const vector<int>& b);

//���� ���� ���� ���
void printNumber(const vector<int>& a);