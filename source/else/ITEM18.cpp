#include <iostream>
#include <memory>
using namespace std;

struct Human{
	explicit Human(int value) : data(value){};
	int data;
};
struct Elf{
	explicit Elf(int value) : data(value){};
	int data;
};
class Dark{
public:
	//����ڰ� 1���� blood��� ����� �ܿ��� �Ѵٸ� �Ǽ��� �����?
	static Dark blood(){ return Dark(1); }
	static Dark gold(){ return Dark(2); }
	static Dark role(){ return Dark(3); }
private:
	//������ �ٸ� ���� ���� ���� �������� private�� ����
	explicit Dark(int value) : data(value){};
	int data;
};

class Potion{
public:
	//�̿� ���� ������ �� �Ű������� �߸��� ���ڸ� �ֱⰡ ����.
	Potion(int human, int elf, int dark){};
	//�Ʒ�ó�� ���ο� Ÿ������ �����ϸ� �Ǽ��� �����ϴ�.
	Potion(Human h, Elf e, Dark d){};
};

//��򰡿� ���Ե� ������ �����ϴ� ���丮 �Լ��Դϴ�.
//�����͸� ��ȯ�մϴ�.
Potion* createPotion(){
	return new Potion(Human(1), Elf(1), Dark::blood());
}
//����Ʈ �����͸� ��ȯ�մϴ�.
shared_ptr<Potion> createPotionBySmart(){
	return shared_ptr<Potion>(new Potion(Human(1), Elf(1), Dark::blood()));
}

void getRidOfPotion(Potion* pP){
	delete pP;
}

int main(){
	//�Ʒ��� ���� �ڵ�� �����մϴ�. 
	//����ڰ� �޸� ������ �� �� ���� ������ delete�� 2�� ����� ���� �ִ�.
	//����Ʈ �����ͷ� �ذ��� �� ������ 
	//����ڰ� �����ϰ� ����Ʈ �����͸� ������� ���� ���� �ִ�.
	Potion* redPotion = createPotion();

	//���� ����Ʈ �����ͷ� ����ؾ߸� �ϹǷ� ����� ���� �����ϴ�.
	shared_ptr<Potion> bluePotion = createPotionBySmart();
	//�Ʒ��� �����ڸ� ���� null shared_ptr�� �����Ѵ�.
	shared_ptr<Potion> eatenPotion(static_cast<Potion*>(0), getRidOfPotion);
	//�Ʒ�ó�� ���Ը� �ϸ� �����ڰ� ������ �����͸� ����ϳ׿�!
	eatenPotion = bluePotion;
}