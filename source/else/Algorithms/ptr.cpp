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
int *ptr1, *ptr2; //포인터가 전역으로 선언된 상황입니다.

void func1() {
	/*std::cout << "--------" << std::endl;
	//해당 포인터(sPtr1)는 스택 안에 있으며, 그 포인터가 가리키는 메모리(999)는 힙에 들어있습니다.
	std::shared_ptr<int> sPtr1(new int(max));
	std::cout << "sp1: " << *sPtr1 << std::endl;

	//동적으로 메모리를 할당했다 해제합니다.
	char* cPtr(new char[MAX]);
	std::cin >> cPtr[0];
	delete[] cPtr;
	*/
	int a = 5; //a를 스택에 생성합니다.
	ptr1 = &a; //전역 메모리에 들어있는 포인터는 스택의 메모리를 가리킵니다.
	ptr2 = ptr1; //전역 메모리에 들어있는 또 다른 포인터는 위의 포인터를 가리킵니다.
	std::cout << "p1: " << *ptr1 << std::endl;
	std::cout << ptr1 << std::endl;
	std::cout << "p2: " << *ptr2 << std::endl;
	std::cout << ptr2 << std::endl;

	std::cout << "--------" << std::endl;
	//함수가 끝남과 동시에 스택에 할당된 자료(a)는 사라집니다.
}

int  main() {
	int a = 1, b = 2, c = 3, d = 4;
	func1();
	//fun1의 자료는 모두 사라졌습니다.
	std::cout << *ptr1 << a << b << c <<d  << std::endl;
	std::cout << ptr1 << std::endl;
	std::cout << "result_p2: " << *ptr2 << std::endl;
	std::cout << ptr2 << std::endl;
	//사라진 자료가 보입니다???
	return 0;
}