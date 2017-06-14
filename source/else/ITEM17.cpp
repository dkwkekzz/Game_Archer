#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Archer{

};

void battle(shared_ptr<Archer> pw, int level){
	cout << "on Battle!" << endl;
}

int getLevel(){
	int a;  cin >> a;
	return a;
}

int main(){
	//�Ʒ�ó�� ������ ����(new�� ������� ��ü)�� shared_ptr������ �ٲ� �� ����.
	//battle(new Archer(), 1);
	//�Ʒ��� ���� ��������� ��ü�� ���� ���� �Ѱ��ִ� �͵� ����̴�.
	battle(shared_ptr<Archer>(new Archer()), getLevel());
	//���⼭ 3������ ȣ���ϰ� �ȴ�.
	//��ü ����: new Archer
	//getLevel() �Լ� ȣ��
	//shared_ptr ������ ȣ��
	//�� 3������ ������ ����ġ �����Ƿ� ��ü�� �����ϰ� ���ܰ� ����
	//���α׷��� ���� ���� �ִ�.
	//new�� ������ ��ü�� ����Ʈ�����Ϳ� ��� �ڵ带 ���������� �д�.
	shared_ptr<Archer> pa(new Archer());
	battle(pa, getLevel());
}