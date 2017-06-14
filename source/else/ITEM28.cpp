#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Weapon{
public:
	Weapon(int t, int p) : type(t), power(p) {}
	void setType(int t) { type = t; }
	void setPower(int p) { power = p; }
	void getInfo() const { cout << type << ": " << power << endl; }
private:
	int type;
	int power;
};

class Archer{
public:
	void setWeapon(shared_ptr<Weapon> pW) 
	{ pWeapons.push_back(pW); };
	const Weapon& upgradeWeapon(int n) const 
	{ return *pWeapons[n].get(); };
private:
	//���� ������� private�� ��ȣ�Ǿ� ������ �� �����ϴ�.
	vector<shared_ptr<Weapon> > pWeapons;
};

int main(){
	Archer player1;
	//player1�� 6���� ���⸦ �����մϴ�.
	for (int i = 0; i < 6; i++)
		player1.setWeapon(shared_ptr<Weapon>(new Weapon(i, 100)));
	//���ο� ���⸦ ������ �ű�ϴ�.
	//�տ� �ݵ�� const�� �ٿ��� ������ �� �ֽ��ϴ�.
	const Weapon *pNewWeapon = &(player1.upgradeWeapon(1));
	//���ο� ���⺸�� �÷��̾ ���� �״´ٸ�?
	delete &player1;
	//�ɰ��� ������ ����±���.
	pNewWeapon->getInfo();
}