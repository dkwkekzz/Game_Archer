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
	//���ؽ��� ���� ��ó�Դϴ�.
	mutex m;
	int number;
	int level;
	Skill* skill;
};
void Archer::moreStrongArcher(Skill& s){
	//��������� ������� ������ ���ݴϴ�.
	//m.lock(); �̴� ���ܰ� �߻��ϸ� �޸𸮰� ����˴ϴ�.
	//�̴� �ڵ� ��� ��ġ�� ������ �˴ϴ�.
	Lock lm(&m);
	//������ ��ų�� �����ϰ� ���ο� ��ų�� ���ϴ�.
	delete skill;
	skill = new Skill(s);
	level++;

	cout << "Upgrade is complete." << endl;
}

void t_func(int id){
	
}

//�̴� ()�� ���ܰ� �߻��ϸ�, �����Ű�� �ʰ� unexpected�Լ��� ȣ���Ѵ�. 
//������ �̴� ���� �� ������ �ʴ´ٰ� �ϴµ�?
double myfunction(char param) throw (int);

//ǥ������ ���� Ȱ��. ������ ���� Ȱ���Ѵ�.
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
		//���ܰ� ����� ������(throw).
		if (!a) throw a;
		else throw myex;
	}
	//���� ���� �޴´�.
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
		//�Ϲ����� ����� ���� �Լ��� static�Լ��� �����ϴ�.
		//t[i] = thread(t_func, i);
		//Ŭ���� ��� �Լ����� ��쿡�� ������ ���� �����Ѵ�.
		t[i] = thread([&](){ a.moreStrongArcher(s[i]); });
	for (int i = 0; i < 10; i++) 
		t[i].join();*/

	return 0;
}