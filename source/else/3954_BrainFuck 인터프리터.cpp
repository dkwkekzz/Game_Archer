#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <cmath>
using namespace std;
typedef long long int64;

int tc, sm, sc, si;
char code[5000], input[5000];
unsigned char memory[100005];
int codeIndex, memoryIndex, inputIndex;
pair<int, int> loop;

bool isLoop(){
	while (codeIndex < sc){
		checkChar(code[codeIndex]);
		codeIndex++;
	}

	int start = codeIndex, startMemoryIndex = memoryIndex, end = 0, counter = 0;
	while (++codeIndex < sc){
		if (++counter > 4100) {
			loop = make_pair(start, end);
			return true;
		}
	}
	return false;
}

void checkChar(char c){
	if (c == '+') memory[memoryIndex]++;
	else if (c == '-') memory[memoryIndex]--;
	else if (c == '>'){
		if (++memoryIndex >= sm) memoryIndex = 0;
	}
	else if (c == '<'){
		if (--memoryIndex < 0) memoryIndex = sm - 1;
	}
	else if (c == '.') return;
	else if (c == ',') memory[memoryIndex] = (++inputIndex == si ? 255 : input[inputIndex]);
	else if (c == '[') {

	}
	else if (c == ']'){

	}
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);
	cin >> tc;
	while (tc--){
		memset(memory, 0, sizeof(memory));
		memset(code, 0, sizeof(code));
		memset(input, 0, sizeof(input));
		cin >> sm >> sc >> si; 
		cin.ignore(); 
		cin.getline(code, sc + 1);
		cin.getline(input, si + 1);
		codeIndex = 0, memoryIndex = 0, inputIndex = -1;
		!isLoops(0, codeIndex) ? cout << "Terminates" : cout << "Loops " << loop.first << " " << loop.second;
		cout << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}