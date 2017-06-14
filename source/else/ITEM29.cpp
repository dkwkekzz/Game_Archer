#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;

class Lock{
public:
	Lock(mutex* m) : mutexPtr(m){ mutexPtr->lock(); }
	~Lock(){ mutexPtr->unlock(); }
private:
	mutex* mutexPtr;
};

class Skill{
public:
	Skill(int p) : power(p) {}
private:
	int power;
};

class Archer{
public:
	Archer(int n) : number(n), level(1), skill(new Skill(1)) {}
	void moreStrongArcher(Skill& s);
private:
	//뮤텍스를 가진 아처입니다.
	mutex m;
	int number;
	int level;
	Skill* skill;
};
void Archer::moreStrongArcher(Skill& s){
	//스레드들이 순서대로 들어오게 해줍니다.
	//m.lock(); 이는 예외가 발생하면 메모리가 누출됩니다.
	//이는 자동 잠금 장치를 가지게 됩니다.
	Lock lm(&m);
	//기존의 스킬을 삭제하고 새로운 스킬을 배웁니다.
	delete skill;
	skill = new Skill(s);
	level++;

	cout << "Upgrade is complete." << endl;
}

void t_func(int id){
	
}

//이는 ()의 예외가 발생하면, 종료시키지 않고 unexpected함수를 호출한다. 
//하지만 이는 지금 잘 쓰이지 않는다고 하는데?
double myfunction(char param) throw (int);

//표준적인 예외 활용. 다음과 같이 활용한다.
#include <exception>
class myexception : public exception
{
	virtual const char* what() const throw()
	{
		return "My exception happened";
	}
} myex;

int main(){
	try{
		int a;
		cin >> a;
		//예외가 생기면 던진다(throw).
		if (!a) throw a;
		else throw myex;
	}
	//던진 값을 받는다.
	catch (int e){
		cout << "no accept " << e << endl;
	}
	catch (exception& e)
	{
		cout << e.what() << '\n';
	}

	/*Archer a(1);
	vector<Skill> s;
	for (int i = 0; i < 10; i++) s.push_back(Skill(i + 1));
	thread t[10];
	for (int i = 0; i < 10; i++) 
		//일반적인 방법은 전역 함수나 static함수만 가능하다.
		//t[i] = thread(t_func, i);
		//클래스 멤버 함수같은 경우에는 다음과 같이 선언한다.
		t[i] = thread([&](){ a.moreStrongArcher(s[i]); });
	for (int i = 0; i < 10; i++) 
		t[i].join();*/

	return 0;
}