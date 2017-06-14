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
//���ø��� ���Ե� �⺻ Ŭ����
template<typename A>
class Shop{
public:
	void sellPotion(A& buyer){
		Item potion(100);
		buyer.buyItem(potion);
		cout << "sell a potion." << endl;
	}
};

//���ø��� ���Ե� �⺻ Ŭ������ ��ӹ޴� �Ļ� Ŭ����
template <typename A>
class ExtremeShop : public Shop<A>{
public:
	//�����Ϸ����� �̰��� ã����� �����մϴ�.
	//�Ļ� Ŭ������ �������� �Ͱ��� ���̰� �־��.
	using Shop<A>::sellPotion;
	//�񰡻� �Լ��� �������� �� �����Ƿ� �̸��� �޶��.
	void sellPotionExtreme(A& buyer){
		//�۵����� �ʴ´�. A�� ���ؼ� �Һи��ϱ� �����̴�.
		this->sellPotion(buyer);
		Shop<A>::sellPotion(buyer);
	}
};

class Builder{
public:
	void hardWork(int w) { amount = w; }
	//Builder�� ������ �� ��ϴ�.
	//void buyItem(const Item& i){ amount -= i.getPrice(); };
private:
	int amount;

};
//Builder�� ���� ���� ���ø� Ư��ȭ
/*template<>
class Shop<Builder>{
public:
	//�Ϲ� Shop���� �ٸ��ϴ�.
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
	//error C3861: 'sellPotion': �ĺ��ڸ� ã�� �� �����ϴ�.
	//es2.sellPotionExtreme(b);

}