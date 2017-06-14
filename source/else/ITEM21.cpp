#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Weapon{
	//이 선언은 Archer가 Weapon에게 접근하도록 해줍니다.
	friend class Archer;
public:
	Weapon(int d = 0, int a = 1) : damage(d), armor(a) {
		cout << "create Weapon: power(" << d + a << ")" << endl;
	}
	void setMaster(const Archer& a);
private:
	int damage;
	int armor;
	//[항목3]: 값이 대입되어 객체 값이 변하는 것을 방지하도록 const선언

	//프랜드 함수 선언: 이 함수는 class Weapon의 함수가 아닙니다.
	//다만 Weapon내부에 선언됨으로 Weapon의 private접근이 가능한 함수가 됩니다.
	friend const Weapon operator*(const Weapon& lw, const Weapon& rw);
	//외부 클래스 멤버 함수를 선언함으로 그 함수에서 지금 클래스의 private접근허용
	friend void Archer::drainAnotherWeapon(const Weapon& w);
};
class Archer{
public:
	//Archer은 Weapon을 친구로 인정합니다. 즉, 선언된 것입니다.
	//Weapon클래스에서는 Archer의 private접근이 가능합니다.
	friend class Weapon;
	void drainAnotherWeapon(const Weapon& w);
private:
	string name;
	int power;
};
void Archer::drainAnotherWeapon(const Weapon& w){
	//아래의 Weapon클래스를 보면 이 함수를 friend로 선언한 모습이 보인다.
	//이는 해당 함수에서 선언된 곳의 private접근이 가능하게 해준다.
	power = w.damage + w.armor;
}

void Weapon::setMaster(const Archer& a){
	//위에서 언급한대로 Archer에서 Weapon을 친구로 선언했으므로
	cout << "my master is " << a.name << endl;
}
const Weapon operator*(const Weapon& lw, const Weapon& rw){
	//damage, armor 둘 다 friend함수 안이기에 접근 가능한 겁니다.
	//여하튼 이렇게 객체를 만들어서 반환해야만 합니다.
	return Weapon(lw.damage*rw.damage, lw.armor*rw.armor);
}

int main(){
	Weapon w1(5, 1), w2(100, 75), w3;
	w3 = w1*w2;

	cout << "Archer is coming..." << endl;
	Archer a;
}