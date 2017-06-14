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
	//나의 무기들은 private에 보호되어 변경할 수 없습니다.
	vector<shared_ptr<Weapon> > pWeapons;
};

int main(){
	Archer player1;
	//player1이 6개의 무기를 장착합니다.
	for (int i = 0; i < 6; i++)
		player1.setWeapon(shared_ptr<Weapon>(new Weapon(i, 100)));
	//새로운 무기를 꺼내어 옮깁니다.
	//앞에 반드시 const를 붙여야 참조할 수 있습니다.
	const Weapon *pNewWeapon = &(player1.upgradeWeapon(1));
	//새로운 무기보다 플레이어가 먼저 죽는다면?
	delete &player1;
	//심각한 오류가 생기는군요.
	pNewWeapon->getInfo();
}