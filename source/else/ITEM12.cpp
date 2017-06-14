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
	//bm1�� ������ 3�Դϴ�.
	bm1->levelUp(); bm1->levelUp(); bm1->levelUp();
	//bm1=bm2�� �ٸ��ٴ� ���� ���� ������!
	*bm2 = *bm1;
	bm1->printInfo();
	cout << "==========" << endl;
	bm2->printInfo();
	cout << "==========" << endl;
	//�����Կ��� �ұ��ϰ� bm1�� bm2�� ������ �ٸ��ϴ�.
}