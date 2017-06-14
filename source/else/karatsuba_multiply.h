#pragma once 
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//자릿수 올림 처리
void normalize(vector<int>& a);

//multiply({3, 2, 1}, {6, 5, 4}) = 123 * 456
vector<int> multiply(const vector<int>& a, const vector<int>& b);

//a += b * (10^k);
void addTo(vector<int>& a, const vector<int>& b, int k);

//a -= b; (a >= b)
void subFrom(vector<int>& a, const vector<int>& b);

//두 긴 정수의 곱: 카라츠바 정수 곱셈
vector<int> karatsuba(const vector<int>& a, const vector<int>& b);

//벡터 안의 숫자 출력
void printNumber(const vector<int>& a);