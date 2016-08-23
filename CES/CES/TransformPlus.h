#include<cstring>
#include<string>
using namespace std;
#pragma once
/**
 * C++ (int , double , string , CString)��ת��
 * @author shianqi@imudges.com
 * ������vs2010
 */
class TransformPlus
{
public:
	TransformPlus(void);
	~TransformPlus(void);
	//CString
	CString toCString(string str);
	CString toCString(double dbl);
	CString toCString(int i);

	//string
	string toString(CString cstr);
	string toString(double dbl);
	string toString(int i);
	string toString(TCHAR *STR);
	string toString(char* c);

	//double
	double toDouble(CString cstr);
	double toDouble(string str);
	double toDouble(int i);

	//int
	int toInt(CString cstr);
	int toInt(string str);
	int toInt(double dbl);

	//const char*
	
};

