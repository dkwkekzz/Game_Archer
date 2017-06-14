class Stone{
public:
	//해당 클래스 참조자를 반환한다. 인자 역시 참조자이다.
	Stone& operator=(const Stone& rs){
		//대입한 후에, 자기 자신의 참조자를 반환한다.
		return *this;
		//이렇게 해야 다시 참조자를 인자로 넘기고하는 방식이 가능해지지
	}
};