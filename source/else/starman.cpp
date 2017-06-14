#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <cmath>
using namespace std;
typedef unsigned long long uint64;

int q;

void init(vector<vector<string> >& album){
	album[1967][0] = "DavidBowie";
	album[1969][0] = "SpaceOddity";
	album[1970][0] = "TheManWhoSoldTheWorld";
	album[1971][0] = "HunkyDory";
	album[1972][0] = "TheRiseAndFallOfZiggyStardustAndTheSpidersFromMars";
	album[1973][0] = "AladdinSane";
	album[1973][1] = "PinUps";
	album[1974][0] = "DiamondDogs";
	album[1975][0] = "YoungAmericans";
	album[1976][0] = "StationToStation";
	album[1977][0] = "Low";
	album[1977][1] = "Heroes";
	album[1979][0] = "Lodger";
	album[1980][0] = "ScaryMonstersAndSuperCreeps";
	album[1983][0] = "LetsDance";
	album[1984][0] = "Tonight";
	album[1987][0] = "NeverLetMeDown";
	album[1993][0] = "BlackTieWhiteNoise";
	album[1995][0] = "1.Outside";
	album[1997][0] = "Earthling";
	album[1999][0] = "Hours";
	album[2002][0] = "Heathen";
	album[2003][0] = "Reality";
	album[2013][0] = "TheNextDay";
	album[2016][0] = "BlackStar";
}

void input(){

}

void preCalc(){

}

int solve(const vector<vector<string> >& album){
	int s, e;
	for (int i = 0; i < q; i++){
		vector<pair<int, string> > ret;
		cin >> s >> e;
		for (int j = s; j <= e; j++){
			if (album[j][0] != "") ret.push_back(make_pair(j, album[j][0]));
			if (album[j][1] != "") ret.push_back(make_pair(j, album[j][1]));
		}
		
		cout << ret.size() << endl;
		for (int i = 0; i < ret.size(); i++) cout << ret[i].first << " " << ret[i].second << endl;
	}
	
	return 0;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);
	cin >> q;
	vector<vector<string> > album(2017, vector<string>(2, ""));
	init(album);
	input(); 
	solve(album);

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}