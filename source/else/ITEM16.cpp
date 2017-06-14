#include <iostream>
#include <string>
using namespace std;

typedef struct{
	int data;
} S1;
// S1이라고 타입정의합니다. C와 C++에서 문제없이 동작합니다.

struct S2{
	int data;
};
//S2라고 타입정의합니다. 

struct{
	int data;
}S3;

int main(){
	S1 mine1;       // 문제없이 동작합니다. 이때 S1은 typedef입니다.
	S2 mine2;       // 역시 문제없이 동작합니다. 이때 S2도 역시 typedef입니다.
	S3 mine3;       // 문제가 발생합니다! S3는 typedef가 아니라 변수입니다.따라서 S3 mine3;는 옳지 않습니다.

	S1.data = 5;      // 에러가 발생합니다. S1은 변수가 아닌 typedef입니다.
	S2.data = 5;      // 역시 에러가 발생합니다. S2는 변수가 아닌 typedef입니다.
	S3.data = 5;      // 잘 동작합니다. S3자체가 변수이기 때문에 문제가 없습니다.

}