//#include<iostream>
//#include<vector>
//#include<string>
//using namespace std;
//
//class school
//{
//public:
//	std::string schoolName;
//	std::string schoolType;
//	std::string address;
//	school *test;
//	//Ĭ�ϵ��ƶ������Ĭ�ϵĿ�������Ч��һ��
//	school(school&& c)
//	{
//		test = c.test;
//		c.test = NULL;
//		cout << "�ƶ�����" << endl;
//	}
//	school(std::string schoolName, std::string schoolType, std::string address){
//		this->schoolName = schoolName;
//		this->address = address;
//		this->schoolType = schoolType;
//	}
//
//
//
//};
//
//int main()
//{
//	school s1("1", "1", "1");
//	school s2(move(s1));
//}