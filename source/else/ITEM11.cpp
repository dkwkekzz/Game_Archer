#include <iostream>
#include <string>
using namespace std;

class Weapon{
private:
	int type;
};

class Archer{
public:
	Archer& operator=(const Archer& ra); 
	Archer& operator = (Archer ra);
	//함수를 만들어주어야 한다.
	void swap(const Archer& ra);
private:
	Weapon *w;
};
//대입연산자를 실행합니다. 자기 대입이면 ra와 this는 같습니다.
Archer& Archer::operator = (const Archer& ra){
	//자기 대입 검사 - 자기 자신이면 무시합니다.
	if (&ra == this) return *this;
	//원래의 w를 어딘가에 기억해둔다. *pOrig은 원래 w이다.
	Weapon *pOrig = w;
	//w은 *ra.w의 사본을 가리키고 있다. 바뀌었다.
	w = new Weapon(*ra.w);
	//원래 w을 삭제합니다.
	delete pOrig;

	return *this;
}
//참조 전달
Archer& Archer::operator = (const Archer& ra){
	//사본을 만들어야 하네?
	Archer temp(ra);
	swap(temp);

	return *this;
}
//값에 의한 전달
Archer& Archer::operator = (Archer ra){
	//사본이 생긴다는 점을 이용하여 코드를 간결하게
	swap(ra);
	return *this;
}