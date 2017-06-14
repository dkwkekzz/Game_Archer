#include <iostream>
#include <string>
using namespace std;

class Weapon{
private:
	int type;
};

class Archer{
public:
	Archer& operator=(const Archer& ra); 
	Archer& operator = (Archer ra);
	//�Լ��� ������־�� �Ѵ�.
	void swap(const Archer& ra);
private:
	Weapon *w;
};
//���Կ����ڸ� �����մϴ�. �ڱ� �����̸� ra�� this�� �����ϴ�.
Archer& Archer::operator = (const Archer& ra){
	//�ڱ� ���� �˻� - �ڱ� �ڽ��̸� �����մϴ�.
	if (&ra == this) return *this;
	//������ w�� ��򰡿� ����صд�. *pOrig�� ���� w�̴�.
	Weapon *pOrig = w;
	//w�� *ra.w�� �纻�� ����Ű�� �ִ�. �ٲ����.
	w = new Weapon(*ra.w);
	//���� w�� �����մϴ�.
	delete pOrig;

	return *this;
}
//���� ����
Archer& Archer::operator = (const Archer& ra){
	//�纻�� ������ �ϳ�?
	Archer temp(ra);
	swap(temp);

	return *this;
}
//���� ���� ����
Archer& Archer::operator = (Archer ra){
	//�纻�� ����ٴ� ���� �̿��Ͽ� �ڵ带 �����ϰ�
	swap(ra);
	return *this;
}