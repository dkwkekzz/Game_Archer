#include <iostream>
#include <vector>
using namespace std;

//Skill�� tag���Դϴ�. Skill�� �Ӽ��� ǥ���մϴ�.
struct fire_skill_tag{};
struct water_skill_tag{};
struct wind_skill_tag{};
struct holy_skill_tag : public wind_skill_tag{};
struct pain_skill_tag : public fire_skill_tag, water_skill_tag{};
struct rainbow_skill_tag : public pain_skill_tag{};

class Striker{};
class Builder{};
//Archer�� �ҼӼ� ��ų�� �����մϴ�.
template<typename C>
class Archer{
public:
	//����� ����
	class Skill{
	public:
		//skill_category��� �̸��� Ÿ���� ������ ���� �䱸����
		typedef fire_skill_tag skill_category;

	};
};
//���̵� �����ʹ� ����Ӽ� ��ų ����
template<typename C>
class BladeMaster{
public:
	class Skill{
	public:
		typedef pain_skill_tag skill_category;

	};
};
//��ų Ư������ Ŭ�����Դϴ�.
//������ ���߿� ������ ��ų�� � Ÿ������ �˾Ƴ��� �մϴ�.
template<typename Skill>
struct skill_traits{
	//��� SkillŸ���̵� skill_category�� ���մϴ�.
	typedef typename Skill::skill_category skill_category;

};
//���� ���� �ڵ�� ����� ���� ��ü�� �۵������� �⺻Ÿ�Կ��� �۵����� �ʽ��ϴ�.
//�κ� ���ø� Ư��ȭ�� �̿��մϴ�. Ÿ���� �����Ͷ�� �Ʒ� �Լ��� �۵��մϴ�.
template<typename Skill>
struct skill_traits<Skill*>{
	typedef rainbow_skill_tag skill_category;

};
//��ų�� ����ϴ� �Լ��Դϴ�.
//Ư������ Ŭ������ � Ÿ���� ��ų���� ���� Ȯ���ؾ� �մϴ�.
template<typename Skill>
void casting(Skill& s){
	//typeid: Ÿ�� �̸��� ����ϱ� ���� ���� ������.
	//�̴� ��Ÿ�ӿ� �۵��ϸ� type�� ������ Ÿ�ӿ� �������� ���� �����ϸ� �����Դϴ�.
	/*if (typeid(typename skill_traits<Skill>::skill_category)
		== typeid(fire_skill_tag)) cout << "fire" << endl;*/

	//�����ε��ϸ� ������ Ÿ�ӿ� Ÿ���� �˻��� �� �ֽ��ϴ�.
	//Ÿ�Կ� ���� ������ doCasting�� ȣ���մϴ�.
	doCasting(s,
		//skill_category�� ������ ����ü�̱� ������ ()�� �����մϴ�.
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
	//iterator������ ���
	/*vector<int>::iterator iter;
	advance(iter, 1);*/

	//ArcherŬ���� ������ Skill��ü�� �����ϰ� �̸� casting�մϴ�.
	Archer<Striker>::Skill archer_s;
	casting(archer_s); //overload fire
	BladeMaster<Striker>::Skill blade_s;
	casting(blade_s); //overload pain

	int temp = 5;
	int *p = &temp;
	//int*�� casting��?
	//�������̹Ƿ� �κ� Ư��ȭ�� �Լ��� ����˴ϴ�.
	casting(p); //overload rainbow
}