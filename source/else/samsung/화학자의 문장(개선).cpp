/* 문제를 푸실 때, 아래 "화학원소 기호"를 활용하시기 바랍니다.
  */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <vector>
using namespace std;

const string symbol[120] = {
	"H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne", "Na", "Mg", "Al",
	"Si", "P", "S", "Cl", "Ar", "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe",
	"Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr",
	"Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb",
	"Te", "I", "Xe", "Cs", "Ba", "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au",
	"Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn", "Fr", "Ra", "Rf", "Db", "Sg",
	"Bh", "Hs", "Mt", "Ds", "Rg", "Cn", "Fl", "Lv", "La", "Ce", "Pr", "Nd",
	"Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu", "Ac",
	"Th", "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm", "Md",
	"No", "Lr"
};

int single_c[1 << 7];
int double_c[1 << 7][1 << 7];

int solve(const string& s){
	int ch[50005], re[50005];
	ch[0] = -1;
	for (int i = 1; s[i]; i++) ch[i] = toupper(s[i]) - 'A';

	re[0] = 1;
	int i;
	for (i = 1; s[i]; i++){
		re[i] = 0;
		if (single_c[ch[i]]) re[i] |= re[i - 1];
		if (double_c[ch[i]][ch[i - 1]]) re[i] |= re[i - 2];
	}

	return re[s.size() - 1];
}

void preCalc(){
	for (int i = 0; symbol[i][0]; i++){
		if (!symbol[i][1]) {
			int a = toupper(symbol[i][0]) - 'A';
			single_c[a] = 1;
		}
		else{
			int a = toupper(symbol[i][1]) - 'A';
			int b = toupper(symbol[i][0]) - 'A';
			double_c[a][b] = 1;
		}
	}
}

int main(){
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);
	//setbuf(stdout, NULL);

	preCalc(); 

	int TC; 

	cin >> TC;
	for (int i = 1; i <= TC; i++){
		string s;
		cin >> s;

		cout << "Case #" << i << "\n" << (solve(s) == 1 ? "YES" : "NO") << endl;
	}
	return 0;
}