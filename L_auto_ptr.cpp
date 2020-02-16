#include<iostream>
#include<memory>
using namespace std;

template<class T>
class L_autoptr
{
	T* obj=nullptr;
public:
	L_autoptr(T* ptr) : obj(ptr)
	{
	
	}
	L_autoptr() = default;
	~L_autoptr()
	{
		delete obj;
	}
	L_autoptr(L_autoptr<T>& ptr )
	{
		obj = ptr.obj;
		ptr.obj = nullptr;
	}
	L_autoptr& operator=(L_autoptr<T> & ptr)
	{
		delete obj;
		obj = ptr.obj;
		ptr.obj = nullptr;
		return *this;
	}
	void reset(T* newptr)
	{
		delete obj;
		obj = newptr;
	}
	T* release()
	{
		auto tmp = obj;
		obj = nullptr;
		return tmp;
	}
	T& operator*(){
		return *obj;
	}
	T* operator->(){
		return obj;
	}
};
class A
{
public:
	int value;
	A(int value)
	{
		this->value = value;
	}
};
int main()
{
	A* a = new A(3);
	L_autoptr<A> aaa(a);
	cout << aaa->value << endl;
	L_autoptr<string > ptr{ new string("我是shy") };
	L_autoptr<string > ptr2;
	ptr2 = ptr;
	ptr2.reset(new string("我是wml"));
	ptr2.release();
	//autoptr
}