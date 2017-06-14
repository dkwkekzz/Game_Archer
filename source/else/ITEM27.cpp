#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Archer{
public:
	Archer(int n) : playerNumber(n), counter(0) {}
	virtual void attack(){
		count();
		cout << playerNumber << "'s Base shot! <" << counter << ">" << endl;
	}
	//공격을 할 때마다 해당 객체의 카운터는 상승합니다.
	void count(){ counter++; }
private:
	int playerNumber;
	int counter;
};
class Builder{

};
class BladeMaster : public Archer, public Builder{
public:
	BladeMaster(int n) : Archer(n) {}
	virtual void attack(){
		//1. 현재의 파생 클래스를 기본 클래스로 형변환을 시도합니다.
		static_cast<Archer>(*this).attack();
		//2. 해당 클래스의 기본 클래스를 불러옵니다.
		Archer::attack();
		cout << "Critical blade!" << endl;
		//1번과 2번에서의 카운터는 1로 같습니다. 증가하지 않지요.
	}

	typedef vector<shared_ptr<Archer> > VPA;
	VPA arcPtrs;
	typedef vector<shared_ptr<BladeMaster> > VPB;
	VPB blmPtrs;
	void arc_command_attack();
};

void BladeMaster::arc_command_attack(){
	for (VPA::iterator iter = arcPtrs.begin(); 
		iter != arcPtrs.end(); iter++){
		//dynamic_cast로 기본 클래스를 파생 클래스로 전환합니다.
		//여러 가지 파생 클래스가 존재할 수 있으므로 모두 검사합니다.
		if (BladeMaster *pBm = 
			dynamic_cast<BladeMaster*>(iter->get()))
			pBm->attack();
		if (ArchMage *pAm =
			dynamic_cast<ArchMage*>(iter->get()))
			pAm->attack();
		if (DarkKnight *pDk =
			dynamic_cast<BladeMaster*>(iter->get()))
			pDk->attack();
		//이런...
	}
	//파생 클래스의 배열이므로 캐스팅이 필요 없습니다.
	for (VPB::iterator iter = blmPtrs.begin(); 
		iter != blmPtrs.end(); iter++)
		(*iter)->attack();
	//만약 파생 클래스의 함수만 불러오고 싶다면
	//해당 함수를 기본 클래스에서 정의를 안 하고 virtual을 선업합니다.
	//캐스팅을 피할 수 있습니다.
	for (VPA::iterator iter = arcPtrs.begin(); 
		iter != arcPtrs.end(); iter++)
		(*iter)->attack();
}

int main(){
	BladeMaster bm(3);
	bm.arc_command_attack();
}

/*int main(){
	BladeMaster bm;
	//파생 클래스의 주소를 확인합니다.
	cout << "bm: " << &bm << endl;

	Archer *pA = &bm;
	cout << "pA: " << pA << endl;
	Builder *pB = &bm;
	cout << "pB: " << pB << endl;
	//다중 상속인 경우에는 기본클래스의 포인터가 항상 다르다.
	//하지만 단일 상속인 경우에도 가끔은 pA와 bm이 다를 수 있다.
	//bm: 0027FE1F
	//pA: 0027FE1F
	//pB : 0027FE20
}*/

