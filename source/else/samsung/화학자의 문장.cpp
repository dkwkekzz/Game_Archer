/* 문제를 푸실 때, 아래 "화학원소 기호"를 활용하시기 바랍니다.*/


// 아래 기본 제공된 코드를 수정 또는 삭제하고 본인이 코드를 사용하셔도 됩니다.
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
#include <vector>
using namespace std;

const char double_char[14] = { 'a', 'd', 'e', 'g', 'l', 'm', 'r', 't', 'x', 'z', '!', '!', '!', '!' };
const char double_char_back[14][9] = {
	{ 'l', 'r', 's', 'g', 'u', 't', 'm', 'c', '!' },
	{ 'b', 's', 'y', '!' },
	{ 'u', 'r', 's', '!' },
	{ 'a', 'e', 'd', '!' },
	{ 'i', 'v', 'a', 'u', 'r', '!' },
	{ 'g', 'n', 'o', 't', 'd', '!' },
	{ 'b', 'u', 'h', 'e', 'n', 'a', 'g', 'f', '!' },
	{ 'i', 'c', 'e', 'a', 'l', 'b', 'm', 'h', '!' },
	{ 'e', '!' },
	{ 'n', 'r', '!' },
	{ '!' },
	{ '!' },
	{ '!' },
	{ '!' },
};
const char single_char[14] = { 'b', 'c', 'f', 'h', 'i', 'k', 'n', 'o', 'p', 's', 'u', 'v', 'w', 'y' };

const char single_char_back[14][12] = {
	{ 'e', 'r', 'a', 'i', 'h', 'k', '!' },
	{ 'l', 'a', 'r', 'o', 'u', 'd', 's', 'n', 'e', 'f', 'm', '!' },
	{ 'e', 'r', 'l', 'm', '!' },
	{ 'e', 'f', 'g', 's', 'o', '!' },
	{ 'n', 'r', '!' },
	{ 'r', '!' },
	{ 'e', 'a', 'i', 'b', 'd', 'o', 'p', '!' },
	{ 's', '!' },
	{ 'd', 't', 'b', 'o', 'r', 'm', 'u', 'a', '!' },
	{ 'i', 'c', 'e', 'r', 'n', 'b', 'g', 'm', '!' },
	{ '!' },
	{ '!' },
	{ '!' },
	{ 'b', '!' },
};
const char exit_char[2] = { 'j', 'q' };

int cache[50005];

int checkChemistryFunc(const string& s, int start){
	if (start == s.size()) return 1;
	if (start == s.size() - 1){
		char c = s[start];
		if (c == exit_char[0] || c == exit_char[1]) return 0;
		for (int j = 0; j < 14; j++) {
			if (c == single_char[j]) return 1;
		}
		return 0;
	}
	
	int &ret = cache[start];
	if (ret != -1) return ret;

	ret = 1;
	char c = s[start], nc = s[start + 1];

	if (nc == exit_char[0] || nc == exit_char[1]) return ret = 0;

	for (int j = 0; j < 14; j++) {
		if (c == single_char[j]) {
			int check = checkChemistryFunc(s, start + 1);
			for (int k = 0; single_char_back[j][k] != '!'; k++){
				if (nc == single_char_back[j][k]) check += checkChemistryFunc(s, start + 2);
			}
			return ret = (check > 0 ? 1 : 0);
		}
		else if (c == double_char[j]){
			for (int k = 0; double_char_back[j][k] != '!'; k++){
				if (nc == double_char_back[j][k]) return ret *= checkChemistryFunc(s, start + 2);
			}
		}
	}
	
	return ret = 0;
}

int main(int argc, char** argv) {
	FILE *stream;

	freopen_s(&stream, "input.txt", "r", stdin);

	//setbuf(stdout, NULL);

	cin.sync_with_stdio(false);

	int TC;
	int test_case;

	cin >> TC;
	for (test_case = 1; test_case <= TC; test_case++) {
		// 이 부분에서 알고리즘 프로그램을 작성하십시오.
		memset(cache, -1, sizeof(cache));
		string s;
		cin >> s;

		printf("Case #%d\n", test_case);
		cout << (checkChemistryFunc(s, 0) ? "YES" : "NO") << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}