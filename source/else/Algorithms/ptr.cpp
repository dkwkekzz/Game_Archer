#include <iostream>
#include <memory>

struct Home {
	Home(int x, int y) : locationX(x), locationY(y) {
		std::cout << "create Home in ("<< x << ", " << y << ")\n";
	}
	int locationX;
	int locationY;
};

class Archor {
public:
	Archor(int d) : homePtr(new Home(0, 0)), damage(d) {
		std::cout << "create Archor,\n";
	}
	void allocateHome(int x, int y) {
		ph = new Home(x, y);
	}
	void whereIsMyHome() {
		std::cout << "my Home is in (" << ph->locationX << ", " << ph->locationY << ")\n";
	}
	void move() {
		std::cout << "move,\n";
	}
	void attack() {
		std::cout << damage << " attack!\n";
		if(rand() * 100 > 30) std::cout << damage * 2 << " critical Hit!\n";
	}
	Archor& operator= (const Archor& rArc) {
		/*delete ph;
		ph = new Home(*rArc.ph);*/
		/*Home *pOrig = ph;
		//ph = new Home(*rArc.ph);
		delete pOrig;
		std::cout << "my Home is in (" << ph->locationX << ", " << ph->locationY << ")\n";*/
		std::shared_ptr<Home> tempPtr(homePtr);
		

		return *this;
	}
private:
	Home *ph;
	std::shared_ptr<Home> homePtr;
	int damage;
};

/*Archor& Archor::operator= (const Archor& rArc) {
	delete ph;
	ph = new Home(*rArc.ph);
	
	return *this;
}*/

#define MAX 1000000000

const int max = 1000000000;
int *ptr1, *ptr2; //�����Ͱ� �������� ����� ��Ȳ�Դϴ�.

void func1() {
	/*std::cout << "--------" << std::endl;
	//�ش� ������(sPtr1)�� ���� �ȿ� ������, �� �����Ͱ� ����Ű�� �޸�(999)�� ���� ����ֽ��ϴ�.
	std::shared_ptr<int> sPtr1(new int(max));
	std::cout << "sp1: " << *sPtr1 << std::endl;

	//�������� �޸𸮸� �Ҵ��ߴ� �����մϴ�.
	char* cPtr(new char[MAX]);
	std::cin >> cPtr[0];
	delete[] cPtr;
	*/
	int a = 5; //a�� ���ÿ� �����մϴ�.
	ptr1 = &a; //���� �޸𸮿� ����ִ� �����ʹ� ������ �޸𸮸� ����ŵ�ϴ�.
	ptr2 = ptr1; //���� �޸𸮿� ����ִ� �� �ٸ� �����ʹ� ���� �����͸� ����ŵ�ϴ�.
	std::cout << "p1: " << *ptr1 << std::endl;
	std::cout << ptr1 << std::endl;
	std::cout << "p2: " << *ptr2 << std::endl;
	std::cout << ptr2 << std::endl;

	std::cout << "--------" << std::endl;
	//�Լ��� ������ ���ÿ� ���ÿ� �Ҵ�� �ڷ�(a)�� ������ϴ�.
}

int  main() {
	int a = 1, b = 2, c = 3, d = 4;
	func1();
	//fun1�� �ڷ�� ��� ��������ϴ�.
	std::cout << *ptr1 << a << b << c <<d  << std::endl;
	std::cout << ptr1 << std::endl;
	std::cout << "result_p2: " << *ptr2 << std::endl;
	std::cout << ptr2 << std::endl;
	//����� �ڷᰡ ���Դϴ�???
	return 0;
}