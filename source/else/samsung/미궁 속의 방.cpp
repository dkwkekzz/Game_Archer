// �Ʒ� �⺻ ������ �ڵ带 ���� �Ǵ� �����ϰ� ������ �ڵ带 ����ϼŵ� �˴ϴ�.
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

int maze[200000];
int n, k;

void makeMaze(int n){
	maze[0] = 1;
	for (int i = 1; i < n * 2 - 1; i++){
		if (i % 2 == 1) maze[i] = maze[i - 1] + 1;
		else if (i % 2 == 0) maze[i] = maze[i - 1] + i * 2;

		if (i >= n) maze[i] -= 2 * (i - n + 1) - 1;
	}

	for (int i = 0; i < n * 2 - 1; i++) cout << maze[i] << " ";
	cout << endl;
}

unsigned long long visitRoom(const string& s){
	int y = 0, x = 0;

	unsigned long long ret = 1;
	for (int i = 0; i < k; i++){
		if (s[i] == 'D') y++;
		else if (s[i] == 'U') y--;
		else if (s[i] == 'R') x++;
		else if (s[i] == 'L') x--;

		int room = x + y;
		if (room % 2 == 1) ret += maze[room] + y;
		else if (room % 2 == 0) ret += maze[room] - y;
		//cout << "y: " << y << " x: " << x << " -> ret: " << ret << endl;
	}

	return ret;
}

int main(int argc, char** argv) {
	/* �Ʒ� freopen �Լ��� input.txt �� read only �������� �� ��,
	������ ǥ�� �Է�(Ű����) ��� input.txt ���Ϸ� ���� �о���ڴٴ� �ǹ��� �ڵ��Դϴ�.
	���� ������ PC ���� �׽�Ʈ �� ����, �Է°��� input.txt�� ������ �� freopen �Լ��� ����ϸ�,
	�� �Ʒ����� scanf �Լ� �Ǵ� cin�� ����Ͽ� ǥ���Է� ��� input.txt ���Ϸ� ���� �Է°��� �о� �� �� �ֽ��ϴ�.
	����, ���� PC���� freopen �Լ��� ������� �ʰ� ǥ���Է��� ����Ͽ� �׽�Ʈ�ϼŵ� �����մϴ�.
	��, Codeground �ý��ۿ��� "�����ϱ�" �� ������ �ݵ�� freopen �Լ��� ����ų� �ּ�(//) ó�� �ϼž� �մϴ�. */
	FILE *input;
	
	freopen_s(&input, "input.txt", "r", stdin);

	//setbuf(stdout, NULL);
	cin.sync_with_stdio(false);

	int TC;
	int test_case;

	cin >> TC;
	for (test_case = 1; test_case <= TC; test_case++) {
		// �� �κп��� �˰��� ���α׷��� �ۼ��Ͻʽÿ�.

		cin >> n >> k;

		makeMaze(n);

		string s;
		cin >> s;

		// �� �κп��� ������ ����Ͻʽÿ�.
		printf("Case #%d\n", test_case);	// cout ��� ����
		cout << visitRoom(s) << endl;
	}

	return 0;	// �������� �� �ݵ�� 0�� �����ؾ� �մϴ�.
}