#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

const int MOD = 1000000000+7;
string e, digits;
int m;
int cashe[1<<14][20][2];
double overlap;

int egg(string &made, int used, int mod, bool less){
	if((used == (1 << e.size()) - 1) && mod == 0) return 1;

	int &ret = cashe[used][mod][less];
	if(ret != -1) return ret;

	ret = 0;
	int index = made.size();
	for(int i = 0; i < e.size(); i++){
		if(i >= 1 && digits[i - 1] == digits[i] && (used & (1<<(i - 1)))==0 )
				continue;
		else if((used & (1<<i)) == 0){
			if((used == 0 || !less) && e[index] > e[i])
				ret += egg(made + e[i], used | (1<<i), ((mod + (int)(e[i] - '0')) % m) * 10, 1);
			else if (!less && e[index] == e[i])
				ret += egg(made + e[i], used | (1<<i), ((mod + (int)(e[i] - '0')) % m) * 10, 0);
			else if (less)
				ret += egg(made + e[i], used | (1<<i), ((mod + (int)(e[i] - '0')) % m) * 10, 1);
		}
	}
	ret %= MOD;
	return ret;
}

/*double overLap(const string &e){
	int overlap[10];
	memset(overlap, 0, sizeof(overlap));
	for(int i = 0; i < e.size(); i++){
		int a = (int)(e[i] - '0');
		overlap[a]++;
	}

	double ret = 1.0;
	for(int i = 0; i < 10; i++)
		if(overlap[i] != 0)
			ret *= overlap[i];
	return ret;
}*/

int main(){
	memset(cashe, -1, sizeof(cashe));
	cin >> e >> m;
	//overlap = overLap(e);
	digits = e;
	sort(digits.begin(), digits.end());
	string made = "";
	cout << egg(made, 0, 0, 0) - 1 << endl;
}
