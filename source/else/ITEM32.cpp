#include <stdio.h>     
#include <assert.h>     

void print_number(int* myInt) {
	//단정문은 제시한 문장이 실패할 일이 없다고 확신하는 것입니다.
	assert(myInt != NULL);
	printf("%d\n", *myInt);
}

int main()
{
	int a = 10;
	int * b = NULL;
	int * c = NULL;

	b = &a;

	print_number(b);
	print_number(c);

	return 0;
}