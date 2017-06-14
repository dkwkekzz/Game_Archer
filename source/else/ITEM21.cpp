#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Weapon{
	//�� ������ Archer�� Weapon���� �����ϵ��� ���ݴϴ�.
	friend class Archer;
public:
	Weapon(int d = 0, int a = 1) : damage(d), armor(a) {
		cout << "create Weapon: power(" << d + a << ")" << endl;
	}
	void setMaster(const Archer& a);
private:
	int damage;
	int armor;
	//[�׸�3]: ���� ���ԵǾ� ��ü ���� ���ϴ� ���� �����ϵ��� const����

	//������ �Լ� ����: �� �Լ��� class Weapon�� �Լ��� �ƴմϴ�.
	//�ٸ� Weapon���ο� ��������� Weapon�� private������ ������ �Լ��� �˴ϴ�.
	friend const Weapon operator*(const Weapon& lw, const Weapon& rw);
	//�ܺ� Ŭ���� ��� �Լ��� ���������� �� �Լ����� ���� Ŭ������ private�������
	friend void Archer::drainAnotherWeapon(const Weapon& w);
};
class Archer{
public:
	//Archer�� Weapon�� ģ���� �����մϴ�. ��, ����� ���Դϴ�.
	//WeaponŬ���������� Archer�� private������ �����մϴ�.
	friend class Weapon;
	void drainAnotherWeapon(const Weapon& w);
private:
	string name;
	int power;
};
void Archer::drainAnotherWeapon(const Weapon& w){
	//�Ʒ��� WeaponŬ������ ���� �� �Լ��� friend�� ������ ����� ���δ�.
	//�̴� �ش� �Լ����� ����� ���� private������ �����ϰ� ���ش�.
	power = w.damage + w.armor;
}

void Weapon::setMaster(const Archer& a){
	//������ ����Ѵ�� Archer���� Weapon�� ģ���� ���������Ƿ�
	cout << "my master is " << a.name << endl;
}
const Weapon operator*(const Weapon& lw, const Weapon& rw){
	//damage, armor �� �� friend�Լ� ���̱⿡ ���� ������ �̴ϴ�.
	//����ư �̷��� ��ü�� ���� ��ȯ�ؾ߸� �մϴ�.
	return Weapon(lw.damage*rw.damage, lw.armor*rw.armor);
}

int main(){
	Weapon w1(5, 1), w2(100, 75), w3;
	w3 = w1*w2;

	cout << "Archer is coming..." << endl;
	Archer a;
}