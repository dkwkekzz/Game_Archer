#include <iostream>
#include <string>
using namespace std;

typedef struct{
	int data;
} S1;
// S1�̶�� Ÿ�������մϴ�. C�� C++���� �������� �����մϴ�.

struct S2{
	int data;
};
//S2��� Ÿ�������մϴ�. 

struct{
	int data;
}S3;

int main(){
	S1 mine1;       // �������� �����մϴ�. �̶� S1�� typedef�Դϴ�.
	S2 mine2;       // ���� �������� �����մϴ�. �̶� S2�� ���� typedef�Դϴ�.
	S3 mine3;       // ������ �߻��մϴ�! S3�� typedef�� �ƴ϶� �����Դϴ�.���� S3 mine3;�� ���� �ʽ��ϴ�.

	S1.data = 5;      // ������ �߻��մϴ�. S1�� ������ �ƴ� typedef�Դϴ�.
	S2.data = 5;      // ���� ������ �߻��մϴ�. S2�� ������ �ƴ� typedef�Դϴ�.
	S3.data = 5;      // �� �����մϴ�. S3��ü�� �����̱� ������ ������ �����ϴ�.

}