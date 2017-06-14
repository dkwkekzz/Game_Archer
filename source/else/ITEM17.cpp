#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Archer{

};

void battle(shared_ptr<Archer> pw, int level){
	cout << "on Battle!" << endl;
}

int getLevel(){
	int a;  cin >> a;
	return a;
}

int main(){
	//아래처럼 포인터 형식(new로 만들어진 객체)가 shared_ptr형으로 바뀔 수 없다.
	//battle(new Archer(), 1);
	//아래와 같이 명시적으로 객체를 새로 만들어서 넘겨주는 것도 방법이다.
	battle(shared_ptr<Archer>(new Archer()), getLevel());
	//여기서 3가지를 호출하게 된다.
	//객체 생성: new Archer
	//getLevel() 함수 호출
	//shared_ptr 생성자 호출
	//이 3가지의 순서가 일정치 않으므로 객체를 생성하고 예외가 생겨
	//프로그램이 죽을 수도 있다.
	//new로 생성한 객체를 스마트포인터에 담는 코드를 독립적으로 둔다.
	shared_ptr<Archer> pa(new Archer());
	battle(pa, getLevel());
}