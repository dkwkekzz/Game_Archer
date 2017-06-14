#include <iostream>
#include <new>
using namespace std;

//newó���ڸ� ��Ƴ��� ��ü�Դϴ�.
//�ڵ����� curó���� ���� ��, oldó���ڷ� �����մϴ�. 
class NewHandlerHolder{
public:
	//������ newó���ڸ� ȹ���մϴ�.
	explicit NewHandlerHolder(new_handler nh) : handler(nh) {}
	//���� ó���ڷ� ������ ó���ڸ� �����ϰ� ������ ó���ڷ� ��ġ�մϴ�.
	~NewHandlerHolder(){ std::set_new_handler(handler); }
private:
	new_handler handler;
	//���縦 �����մϴ�.
	NewHandlerHolder(const NewHandlerHolder&);
	NewHandlerHolder& operator=(const NewHandlerHolder&);
};

class Archer{
public:
	//�������� set_new_handler�� �������մϴ�. ������ ������ �����ϴ�.
	//���� pó���ڸ� ��ġ�ϸ� oldó���ڸ� ��ȯ�մϴ�.
	static new_handler set_new_handler(new_handler p) throw(){
		new_handler oldHandler = currentHandler;
		currentHandler = p;
		return oldHandler;
	}
	//new�����ڸ� �������մϴ�.
	void* operator new(size_t size) throw(bad_alloc){
		//ǥ�ؿ��� ������ �ڿ��� �����ϰ� ������ �ڿ��� ��ġ�մϴ�.
		//cur�̶�� �ڵ鷯�� Ŭ������ ��ġ�ߴٸ�, old ���� ó���ڴ� �����մϴ�.
		//�����԰� ���ÿ� ������ cur�� ��ġ�ϰ� old�� �����صӴϴ�.
		//���� curó���ڷ� �����Ѵٸ�, NHŬ������ �����ص� oldó���ڸ� ��ġ�� ���Դϴ�.
		NewHandlerHolder h(std::set_new_handler(currentHandler));
		//������ new�����ڷ� �޸𸮸� �Ҵ��մϴ�.
		return operator new(size);
	}
private:
	static new_handler currentHandler;
};
//null�� �ʱ�ȭ�մϴ�.
new_handler Archer::currentHandler = 0;

class BladeMaster{
public:
	BladeMaster(int s, int p) : sword(s) { cout << "power! " << p << endl; }
	int getSword() const { return sword; }
private:
	int sword;
};

/*namespace std{
	//typedef�� �Լ� ������ �缱��
	//new_handler��� �Լ��� ����ó�� ���ϴ�.
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
	//ArcherŬ���� ��ü pA�� ���� �Ҵ� �� ����
	Archer *pA = new Archer(1); // state=1
	//���� ��, delete�� pA �޸� ����
	if (!pA->getState()) delete pA;

	//������ �ִ� �޸𸮿� ���ο� ��ü�� �����մϴ�.
	//��ü ������ �޸𸮸� ���� �����ϴ� ���Դϴ�.
	new(pA)BladeMaster(2, 9);
	cout << pA->getState() << endl; // state=2
	//cout << pA->getSword() << endl;

	delete pA;

	//Archer *pAA = new(nothrow)Archer;
	//if (!pAA) cout << "error" << endl;

	//new�������� ������ �迭 ���� �Ҵ� �� �ʱ�ȭ
	Archer **pGA = new Archer*[100];
	for (int i = 0; i < 100; i++)
		pGA[i] = new Archer(i);
	//malloc�� ������ �迭 ���� �Ҵ� �� �ʱ�ȭ
	//��ü ũ��(sizeof(BM*))�� �迭 ũ��(100)�� ���Ѹ�ŭ �޸� �Ҵ�
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