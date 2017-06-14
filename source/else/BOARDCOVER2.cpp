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
const int MAX_HWRC = 10 + 5;
int t, h, w, r, c;
vector<string> board;
int covered[MAX_HWRC][MAX_HWRC];
int best, rest;

vector<string> block;
vector<vector<pair<int, int> > > rotations;
int blockSize;

bool set(int y, int x, const vector<pair<int, int> >& block, int delta){
	for (int i = 0; i < block.size(); i++){
		int ny = block[i].first, nx = block[i].second;
		if (y + ny >= h || x + nx >= w || y + ny < 0 || x + nx < 0) return false;
		if (delta == 1 && covered[y + ny][x + nx]) return false;
		if (delta == -1 && !covered[y + ny][x + nx]) return false;
	}
	for (int i = 0; i < block.size(); i++){
		int ny = block[i].first, nx = block[i].second;
		if (delta == 1) covered[y + ny][x + nx] = 1;
		if (delta == -1) covered[y + ny][x + nx] = 0;
	}
	rest -= block.size() * delta;
	return true;
}

void search(int placed){
	if (best >= placed + rest / blockSize) return;
	//아직 채우지 못한 빈 칸을 찾는다.
	int y = -1, x = -1;
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			if (!covered[i][j]){
				y = i, x = j;
				break;
			}
		}
		if (y != -1) break;
	}
	//모든 칸을 채웠다면
	if (y == -1){
		best = max(best, placed);
		return;
	}
	//빈 칸을 찾았다면 덮는다.
	for (int i = 0; i < rotations.size(); i++){
		if (set(y, x, rotations[i], 1)) search(placed + 1);
		set(y, x, rotations[i], -1);
	}
	//이 칸을 덮지 않고 막아둔다.
	covered[y][x] = 1; rest--;
	search(placed);
	covered[y][x] = 0; rest++;
}

int solve(){
	for (int y = 0; y < h; y++){
		for (int x = 0; x < w; x++){
			covered[y][x] = (board[y][x] == '#' ? 1 : 0);
			if (!covered[y][x]) rest++;
		}
	}
	search(0);
	return best;
}

vector<string> rotate(const vector<string>& arr){
	vector<string> ret(arr[0].size(), string(arr.size(), ' '));
	for (int i = 0; i < arr.size(); i++){
		for (int j = 0; j < arr[0].size(); j++){
			ret[j][arr.size() - i - 1] = arr[i][j];
		}
	}
	return ret;
}

void generateRotations(vector<string> block){
	rotations.clear();
	rotations.resize(4); // 4번 돌린다.
	for (int rot = 0; rot < 4; rot++){
		int oY = -1, oX = -1; // 원점
		for (int i = 0; i < block.size(); i++){
			for (int j = 0; j < block[i].size(); j++){
				if (block[i][j] == '#'){ //처음 등장한 #이 원점
					if (oY == -1){
						oY = i, oX = j;
					} //해당 블록에서의 원점으로 부터의 거리(정점)를 저장한다.
					rotations[rot].push_back(make_pair(i - oY, j - oX));
				}
			}
		} //블록을 돌려서 다음 블록을 저장한다.
		block = rotate(block);
	} //정렬하여 중복을 제거한다.
	sort(rotations.begin(), rotations.end());
	rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());
	blockSize = rotations[0].size();
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);
	cin >> t;
	for (int tc = 0; tc < t; tc++){
		cin >> h >> w >> r >> c;
		board = vector<string>(h), block = vector<string>(r);
		for (int i = 0; i < h; i++) cin >> board[i];
		for (int i = 0; i < r; i++) cin >> block[i];
		generateRotations(block);
		cout << solve() << endl;
	}
	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}