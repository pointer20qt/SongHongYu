#include<iostream>
#include<vector>
#include<string>
using namespace std;


//void set_show(int x, A &a)  //��Ԫ�������壬Ϊ�˷�����A�еĳ�Ա
//{
//	a.data = x;
//	cout << a.data << endl;
//}
class A
{
public:
	friend class C;
private:
	int data;
};


class C             //��Ԫ�ඨ�壬Ϊ�˷�����A�еĳ�Ա
{
public:
	void set_show(int x, A &a) { a.data = x; cout << a.data << endl; }
};
int main()
{
	using AA = A;
	AA a;
	using CC = C;
	CC c;
	c.set_show(123,a);

	return 0;
}