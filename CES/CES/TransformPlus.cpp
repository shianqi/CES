#include "StdAfx.h"
#include "TransformPlus.h"


TransformPlus::TransformPlus(void)
{
}


TransformPlus::~TransformPlus(void)
{
}

//CString
CString TransformPlus::toCString(string str){
	CString cstr(str.c_str());
	return cstr;
}

CString TransformPlus::toCString(double dbl){
	CString t;
	t.Format("%f",dbl);
	return t;
}

CString TransformPlus::toCString(int i){
	CString t;
	t.Format("%d",i);
	return t;
}


//String
string TransformPlus::toString(CString cstr){
	string s(cstr.GetBuffer());
	string str = s;
	return str;
}

string TransformPlus::toString(double dbl){
	char buffer[20];
	sprintf_s(buffer, "%f", dbl);
	string str = buffer;
	return buffer;
}

string TransformPlus::toString(int i){
	char str[8]; 
	int length = sprintf(str, "%05X", i); 
	return str;
}

string TransformPlus::toString(char* c){
	string s(c);
	return s;
}

//double
double TransformPlus::toDouble(CString cstr){
	return atof(cstr);
}

double TransformPlus::toDouble(string str){
	double value = atof(str.c_str());
	return value;
}

double TransformPlus::toDouble(int i){
	double dbl = (double)i;
	return dbl;
}


//int
int TransformPlus::toInt(CString cstr){
	int i = _ttoi(cstr);
	return i;
}

int TransformPlus::toInt(string str){
	int n = atoi(str.c_str());
	return n;
}

int TransformPlus::toInt(double dbl){
	int i = (int)dbl;
	return i;
}


