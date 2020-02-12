#include<iostream>
#include<vector>
#include<string>
using namespace std;


//void set_show(int x, A &a)  //友元函数定义，为了访问类A中的成员
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


class C             //友元类定义，为了访问类A中的成员
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