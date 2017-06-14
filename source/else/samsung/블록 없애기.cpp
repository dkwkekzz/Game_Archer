#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int n;

pair<int, int> findLowest(const vector<pair<int, int> >& H, const vector<bool>& isDelete){
	for (int i = 0; i < n; i++){
		int first_index = H[i].first;
		if (!isDelete[first_index]) return H[i];
	}

	return pair<int, int>(-1, -1);
}

int solve(const vector<pair<int, int> >& H, vector<pair<int, int> >& deletePoint, vector<bool>& isDelete){
	int time = 0, re_block = n;

	while (re_block > 0){
		pair<int, int> lowest = findLowest(H, isDelete);
		int elapsedTime = lowest.second - time;

		for (int j = 0; j < elapsedTime; j++){
			time++;

			for (int i = 0; i < deletePoint.size(); i++){
				int index = deletePoint[i].first + (time - deletePoint[i].second);
				if (index < n){
					if (!isDelete[index]) {
						isDelete[index] = true; re_block--;
					}
				}

				index = deletePoint[i].first - (time - deletePoint[i].second);
				if (index >= 0){
					if (!isDelete[index]) {
						isDelete[index] = true; re_block--;
					}
				}
			}

			if (re_block <= 0) break;
		}

		deletePoint.push_back(pair<int, int>(lowest.first, time));
		if (!isDelete[lowest.first]) {
			isDelete[lowest.first] = true; re_block--;
		}
	}
	
	return time;
}

int compare(pair<int, int> i, pair<int, int> j){
	return i.second < j.second;
}

int main(int argc, char** argv) {
	/* 아래 freopen 함수는 input.txt 를 read only 형식으로 연 후,
	앞으로 표준 입력(키보드) 대신 input.txt 파일로 부터 읽어오겠다는 의미의 코드입니다.
	만약 본인의 PC 에서 테스트 할 때는, 입력값을 input.txt에 저장한 후 freopen 함수를 사용하면,
	그 아래에서 scanf 함수 또는 cin을 사용하여 표준입력 대신 input.txt 파일로 부터 입력값을 읽어 올 수 있습니다.
	또한, 본인 PC에서 freopen 함수를 사용하지 않고 표준입력을 사용하여 테스트하셔도 무방합니다.
	단, Codeground 시스템에서 "제출하기" 할 때에는 반드시 freopen 함수를 지우거나 주석(//) 처리 하셔야 합니다. */
	FILE *stream;

	freopen_s(&stream, "input.txt", "r", stdin);

	//setbuf(stdout, NULL);

	cin.sync_with_stdio(false);

	int TC;
	int test_case;

	cin >> TC;
	for (test_case = 1; test_case <= TC; test_case++) {
		// 이 부분에서 알고리즘 프로그램을 작성하십시오.
		cin >> n;
		vector<pair<int, int> > H(n);
		for (int i = 0; i < n; i++) {
			H[i].first = i; cin >> H[i].second;
		}
		sort(H.begin(), H.end(), compare);

		vector<bool> isDelete(n, 0);
		vector<pair<int, int> > deletePoint;
		deletePoint.push_back(pair<int, int>(-1, 0)); deletePoint.push_back(pair<int, int>(n, 0));

		printf("Case #%d\n", test_case);
		cout << solve(H, deletePoint, isDelete) << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}