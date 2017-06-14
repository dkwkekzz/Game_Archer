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
	//사용자가 1번이 blood라는 사실을 외워야 한다면 실수가 잦겠지?
	static Dark blood(){ return Dark(1); }
	static Dark gold(){ return Dark(2); }
	static Dark role(){ return Dark(3); }
private:
	//엉뚱한 다른 값이 들어가는 것을 막기위해 private에 선언
	explicit Dark(int value) : data(value){};
	int data;
};

class Potion{
public:
	//이와 같은 선언은 각 매개변수에 잘못된 숫자를 넣기가 쉽다.
	Potion(int human, int elf, int dark){};
	//아래처럼 새로운 타입으로 선언하면 실수를 막습니다.
	Potion(Human h, Elf e, Dark d){};
};

//어딘가에 포함된 포션을 생성하는 펙토리 함수입니다.
//포인터를 반환합니다.
Potion* createPotion(){
	return new Potion(Human(1), Elf(1), Dark::blood());
}
//스마트 포인터를 반환합니다.
shared_ptr<Potion> createPotionBySmart(){
	return shared_ptr<Potion>(new Potion(Human(1), Elf(1), Dark::blood()));
}

void getRidOfPotion(Potion* pP){
	delete pP;
}

int main(){
	//아래와 같은 코드는 위험합니다. 
	//사용자가 메모리 해제를 안 할 수도 있으며 delete를 2번 사용할 수도 있다.
	//스마트 포인터로 해결할 수 있지만 
	//사용자가 깜빡하고 스마트 포인터를 사용하지 않을 수도 있다.
	Potion* redPotion = createPotion();

	//이제 스마트 포인터로 사용해야만 하므로 까먹을 일이 없습니다.
	shared_ptr<Potion> bluePotion = createPotionBySmart();
	//아래는 삭제자를 가진 null shared_ptr을 생성한다.
	shared_ptr<Potion> eatenPotion(static_cast<Potion*>(0), getRidOfPotion);
	//아래처럼 대입만 하면 삭제자가 지정된 포인터를 사용하네요!
	eatenPotion = bluePotion;
}