#include <string>
#include <iostream>
using namespace std;

string image;

string solve(string::iterator &it) {
	char head = *it;
	it++;
	if (head == 'w' || head == 'b') return string(1, head);
	string a = solve(it);
	string b = solve(it);
	string c = solve(it);
	string d = solve(it);
	return "x" + c + d + a + b;
}

int main() {
	string::iterator it;
	it = image.begin();
	cin >> image;
	cout << solve(it) << endl;
}