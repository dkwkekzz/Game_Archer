#include <iostream>
#include <new>
using namespace std;

//new처리자를 담아놓는 객체입니다.
//자동으로 cur처리자 실패 시, old처리자로 변경합니다. 
class NewHandlerHolder{
public:
	//현재의 new처리자를 획득합니다.
	explicit NewHandlerHolder(new_handler nh) : handler(nh) {}
	//전역 처리자로 기존의 처리자를 해제하고 현재의 처리자로 설치합니다.
	~NewHandlerHolder(){ std::set_new_handler(handler); }
private:
	new_handler handler;
	//복사를 방지합니다.
	NewHandlerHolder(const NewHandlerHolder&);
	NewHandlerHolder& operator=(const NewHandlerHolder&);
};

class Archer{
public:
	//정적으로 set_new_handler을 재정의합니다. 기존과 동작은 같습니다.
	//받은 p처리자를 설치하며 old처리자를 반환합니다.
	static new_handler set_new_handler(new_handler p) throw(){
		new_handler oldHandler = currentHandler;
		currentHandler = p;
		return oldHandler;
	}
	//new연산자를 재정의합니다.
	void* operator new(size_t size) throw(bad_alloc){
		//표준에서 현재의 자원을 저장하고 기존의 자원을 설치합니다.
		//cur이라는 핸들러를 클래스에 설치했다면, old 전역 처리자는 저장합니다.
		//저장함과 동시에 전역에 cur로 설치하고 old는 저장해둡니다.
		//만약 cur처리자로 실패한다면, NH클래스로 저장해둔 old처리자를 설치할 것입니다.
		NewHandlerHolder h(std::set_new_handler(currentHandler));
		//전역의 new연산자로 메모리를 할당합니다.
		return operator new(size);
	}
private:
	static new_handler currentHandler;
};
//null로 초기화합니다.
new_handler Archer::currentHandler = 0;

class BladeMaster{
public:
	BladeMaster(int s, int p) : sword(s) { cout << "power! " << p << endl; }
	int getSword() const { return sword; }
private:
	int sword;
};

/*namespace std{
	//typedef로 함수 포인터 재선언
	//new_handler라는 함수를 변수처럼 씁니다.
	typedef void(*new_handler)();
	
	new_handler set_new_handler(new_handler p) throw();
}*/

void outOfMemory(){
	cout << "error: outOfMemory" << endl;
	abort();
}

int main(){
	set_new_handler(outOfMemory);
	int *pA = new int[1000000000];

	/*
	//Archer클래스 객체 pA의 동적 할당 및 생성
	Archer *pA = new Archer(1); // state=1
	//죽을 시, delete로 pA 메모리 해제
	if (!pA->getState()) delete pA;

	//기존에 있던 메모리에 새로운 객체를 생성합니다.
	//객체 생성의 메모리를 직접 지정하는 것입니다.
	new(pA)BladeMaster(2, 9);
	cout << pA->getState() << endl; // state=2
	//cout << pA->getSword() << endl;

	delete pA;

	//Archer *pAA = new(nothrow)Archer;
	//if (!pAA) cout << "error" << endl;

	//new연산자의 다차원 배열 동적 할당 및 초기화
	Archer **pGA = new Archer*[100];
	for (int i = 0; i < 100; i++)
		pGA[i] = new Archer(i);
	//malloc의 다차원 배열 동적 할당 및 초기화
	//객체 크기(sizeof(BM*))에 배열 크기(100)를 곱한만큼 메모리 할당
	BladeMaster **pGB = (BladeMaster**)malloc(sizeof(BladeMaster*)* 100);
	*/
	
	return 0;
}

// new_handler example
/*#include <iostream>     // std::cout
#include <cstdlib>      // std::exit
#include <new>          // std::set_new_handler

void no_memory() {
	std::cout << "Failed to allocate memory!\n";
	std::exit(1);
}

int main() {
	std::set_new_handler(no_memory);
	std::cout << "Attempting to allocate 1 GiB...";
	char* p = new char[1024 * 1024 * 1024];
	std::cout << "Ok\n";
	delete[] p;
	return 0;
}*/