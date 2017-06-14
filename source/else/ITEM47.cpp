#include <iostream>
#include <vector>
using namespace std;

//Skill의 tag들입니다. Skill의 속성을 표현합니다.
struct fire_skill_tag{};
struct water_skill_tag{};
struct wind_skill_tag{};
struct holy_skill_tag : public wind_skill_tag{};
struct pain_skill_tag : public fire_skill_tag, water_skill_tag{};
struct rainbow_skill_tag : public pain_skill_tag{};

class Striker{};
class Builder{};
//Archer은 불속성 스킬을 구사합니다.
template<typename C>
class Archer{
public:
	//사용자 정의
	class Skill{
	public:
		//skill_category라는 이름의 타입을 가지는 것이 요구사항
		typedef fire_skill_tag skill_category;

	};
};
//블레이드 마스터는 고통속성 스킬 구사
template<typename C>
class BladeMaster{
public:
	class Skill{
	public:
		typedef pain_skill_tag skill_category;

	};
};
//스킬 특성정보 클래스입니다.
//컴파일 도중에 소유한 스킬이 어떤 타입인지 알아내야 합니다.
template<typename Skill>
struct skill_traits{
	//어떠한 Skill타입이든 skill_category로 통합니다.
	typedef typename Skill::skill_category skill_category;

};
//위와 같은 코드는 사용자 정의 객체는 작동하지만 기본타입에는 작동하지 않습니다.
//부분 템플릿 특수화를 이용합니다. 타입이 포인터라면 아래 함수로 작동합니다.
template<typename Skill>
struct skill_traits<Skill*>{
	typedef rainbow_skill_tag skill_category;

};
//스킬을 사용하는 함수입니다.
//특성정보 클래스로 어떤 타입의 스킬인지 먼저 확인해야 합니다.
template<typename Skill>
void casting(Skill& s){
	//typeid: 타입 이름을 사용하기 위해 쓰는 예약어군요.
	//이는 런타임에 작동하며 type이 컴파일 타임에 정해지는 점을 감안하면 낭비입니다.
	/*if (typeid(typename skill_traits<Skill>::skill_category)
		== typeid(fire_skill_tag)) cout << "fire" << endl;*/

	//오버로딩하면 컴파일 타임에 타입을 검사할 수 있습니다.
	//타입에 따른 적절한 doCasting을 호출합니다.
	doCasting(s,
		//skill_category의 본질은 구조체이기 때문에 ()가 존재합니다.
		typename skill_traits<Skill>::skill_category());
}

template<typename Skill>
void doCasting(Skill& s, fire_skill_tag){
	cout << "overload fire" << endl;
}
template<typename Skill>
void doCasting(Skill& s, pain_skill_tag){
	cout << "overload pain" << endl;
}
template<typename Skill>
void doCasting(Skill& s, rainbow_skill_tag){
	cout << "overload rainbow" << endl;
}

int main(){
	//iterator에서의 경우
	/*vector<int>::iterator iter;
	advance(iter, 1);*/

	//Archer클래스 내부의 Skill객체를 생성하고 이를 casting합니다.
	Archer<Striker>::Skill archer_s;
	casting(archer_s); //overload fire
	BladeMaster<Striker>::Skill blade_s;
	casting(blade_s); //overload pain

	int temp = 5;
	int *p = &temp;
	//int*가 casting을?
	//포인터이므로 부분 특수화의 함수가 적용됩니다.
	casting(p); //overload rainbow
}