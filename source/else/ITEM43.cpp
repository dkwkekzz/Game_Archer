#include <iostream>
#include <string>
using namespace std;

class Item{
public:
	Item(int p) : price(p) {}
	const int getPrice() const { return price; }
private:
	int price;
};

class Archer{
public:
	void hardWork(int w) { amount = w; }
	void buyItem(const Item& i){ amount -= i.getPrice(); };
private:
	int amount;
};

class Factory{};
Factory potionFactory;
//템플릿이 포함된 기본 클래스
template<typename A>
class Shop{
public:
	void sellPotion(A& buyer){
		Item potion(100);
		buyer.buyItem(potion);
		cout << "sell a potion." << endl;
	}
};

//템플릿이 포함된 기본 클래스를 상속받는 파생 클래스
template <typename A>
class ExtremeShop : public Shop<A>{
public:
	//컴파일러에게 이곳을 찾으라고 지시합니다.
	//파생 클래스에 가려지는 것과는 차이가 있어요.
	using Shop<A>::sellPotion;
	//비가상 함수는 재정의할 수 없으므로 이름이 달라요.
	void sellPotionExtreme(A& buyer){
		//작동하지 않는다. A에 대해서 불분명하기 때문이다.
		this->sellPotion(buyer);
		Shop<A>::sellPotion(buyer);
	}
};

class Builder{
public:
	void hardWork(int w) { amount = w; }
	//Builder는 물건을 못 삽니다.
	//void buyItem(const Item& i){ amount -= i.getPrice(); };
private:
	int amount;

};
//Builder에 대한 완전 템플릿 특수화
/*template<>
class Shop<Builder>{
public:
	//일반 Shop과는 다릅니다.
	void sellItem(Builder& buyer){
		cout << "You can't buy this." << endl;
	}
};*/

int main(){
	Archer a;
	a.hardWork(10000);
	ExtremeShop<Archer> es1;
	es1.sellPotionExtreme(a);
	//Builder b;
	//ExtremeShop<Builder> es2;
	//error C3861: 'sellPotion': 식별자를 찾을 수 없습니다.
	//es2.sellPotionExtreme(b);

}