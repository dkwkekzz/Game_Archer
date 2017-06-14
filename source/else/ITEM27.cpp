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
	//������ �� ������ �ش� ��ü�� ī���ʹ� ����մϴ�.
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
		//1. ������ �Ļ� Ŭ������ �⺻ Ŭ������ ����ȯ�� �õ��մϴ�.
		static_cast<Archer>(*this).attack();
		//2. �ش� Ŭ������ �⺻ Ŭ������ �ҷ��ɴϴ�.
		Archer::attack();
		cout << "Critical blade!" << endl;
		//1���� 2�������� ī���ʹ� 1�� �����ϴ�. �������� ������.
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
		//dynamic_cast�� �⺻ Ŭ������ �Ļ� Ŭ������ ��ȯ�մϴ�.
		//���� ���� �Ļ� Ŭ������ ������ �� �����Ƿ� ��� �˻��մϴ�.
		if (BladeMaster *pBm = 
			dynamic_cast<BladeMaster*>(iter->get()))
			pBm->attack();
		if (ArchMage *pAm =
			dynamic_cast<ArchMage*>(iter->get()))
			pAm->attack();
		if (DarkKnight *pDk =
			dynamic_cast<BladeMaster*>(iter->get()))
			pDk->attack();
		//�̷�...
	}
	//�Ļ� Ŭ������ �迭�̹Ƿ� ĳ������ �ʿ� �����ϴ�.
	for (VPB::iterator iter = blmPtrs.begin(); 
		iter != blmPtrs.end(); iter++)
		(*iter)->attack();
	//���� �Ļ� Ŭ������ �Լ��� �ҷ����� �ʹٸ�
	//�ش� �Լ��� �⺻ Ŭ�������� ���Ǹ� �� �ϰ� virtual�� �����մϴ�.
	//ĳ������ ���� �� �ֽ��ϴ�.
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
	//�Ļ� Ŭ������ �ּҸ� Ȯ���մϴ�.
	cout << "bm: " << &bm << endl;

	Archer *pA = &bm;
	cout << "pA: " << pA << endl;
	Builder *pB = &bm;
	cout << "pB: " << pB << endl;
	//���� ����� ��쿡�� �⺻Ŭ������ �����Ͱ� �׻� �ٸ���.
	//������ ���� ����� ��쿡�� ������ pA�� bm�� �ٸ� �� �ִ�.
	//bm: 0027FE1F
	//pA: 0027FE1F
	//pB : 0027FE20
}*/

