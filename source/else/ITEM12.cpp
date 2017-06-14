#include <iostream>
#include <string>
using namespace std;

class Archer{
public:
	void levelUp();
	void printBaseInfo();
	Archer& operator = (const Archer& a);
private:
	string name;
	int level = 0;
};

void Archer::levelUp(){
	level++;
}

void Archer::printBaseInfo(){
	cout << "level: " << level << endl;
}

Archer& Archer::operator = (const Archer& a){
	name = a.name;
	level = a.level;
	return *this;
}

class BladeMaster : public Archer{
public:
	void setForce(int value);
	void printInfo();
	BladeMaster& operator=(const BladeMaster& bm);
private:
	int force = 0;
	
};

void BladeMaster::setForce(int value){
	force += value;
}
void BladeMaster::printInfo(){
	printBaseInfo();
	cout << "force: " << force << endl;
}

BladeMaster::BladeMaster(const BladeMaster& bm) : Archer(bm){

}

BladeMaster& BladeMaster::operator = (const BladeMaster& bm){
	Archer::operator=(bm);
	force = bm.force;
	return *this;
}

int main(){
	BladeMaster *bm1 = new BladeMaster();
	BladeMaster *bm2 = new BladeMaster(); 
	bm1->printInfo();
	cout << "==========" << endl;
	bm2->printInfo();
	cout << "==========" << endl;
	//bm1의 레벨은 3입니다.
	bm1->levelUp(); bm1->levelUp(); bm1->levelUp();
	//bm1=bm2와 다르다는 것을 잊지 마세요!
	*bm2 = *bm1;
	bm1->printInfo();
	cout << "==========" << endl;
	bm2->printInfo();
	cout << "==========" << endl;
	//복사함에도 불구하고 bm1과 bm2의 레벨이 다릅니다.
}