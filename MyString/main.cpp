#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

struct MyString{
	
	char *pstr;
	
	MyString();
	MyString(char);
	MyString(const char*);
	MyString(const MyString&);
	~MyString();
	
	int count(char);
	int count(const char*);
	
	void operator=(char);
	void operator=(const char*);
	void operator=(const MyString&);
	
	MyString operator+(char);
	MyString operator+(const char*);
	MyString operator+(const MyString&);
	
	friend ostream& operator<<(ostream&, MyString&);
};

MyString::MyString(){
	char* pTmp = (char*) malloc(1);
	if(pTmp == NULL){
		printf("Alloc memory failure");
		exit(1);
	}else{
		pTmp[0] = '\0';
		pstr = pTmp;
	}
}

MyString::MyString(char v){
	pstr = NULL;
	*this = v;
}

MyString::MyString(const char* v){
	pstr = NULL;
	*this = v;
}

MyString::MyString(const MyString& v){
	pstr = NULL;
	*this = v;
}

MyString::~MyString(){
	free(pstr);
}


int MyString::count(char v){
	int n = 0;
	for(int i=0; i<strlen(pstr); ++i){
		if(pstr[i] == v)
			++n;
	}
	return n;
}

int MyString::count(const char* v){
	int n = 0;
	for(int i=0; i<strlen(v); ++i){
		n += count(v[i]);
	}
	return n;
}

void MyString::operator=(const char* v){
	char* pTmp = (char*)realloc(pstr,strlen(v)+1);
	if(pTmp == NULL){
		printf("Alloc memory failure");
		exit(1);
	}else{
		strcpy(pTmp,v);
		pstr = pTmp;
	}
}

void MyString::operator=(char v){
	char s[2] = {v,'\0'};
	*this = s;
}

void MyString::operator=(const MyString& v){
	*this = v.pstr;
}

MyString MyString::operator+(char v){
	char s[2] = {v, '\0'};
	char* pTmp = (char*)realloc(pstr,strlen(pstr)+2);
	strcpy(pTmp,pstr);
	strcat(pTmp,s);
	pstr = pTmp;
}

	
MyString MyString::operator+(const char* v){
	char* pTmp =(char*)realloc(pstr,strlen(pstr)+strlen(v));
	strcpy(pTmp,pstr);
	strcat(pTmp,v);
	pstr = pTmp;
}

MyString MyString::operator+(const MyString& v){
	char* pTmp = (char*)realloc(pstr,strlen(pstr)+strlen(v.pstr));
	strcpy(pTmp,pstr);
	strcat(pTmp,v.pstr);
	*this = pTmp;
}


ostream& operator<<(ostream& os, MyString& v){
	os << v.pstr;
	return os;
}

int main(){
	MyString str = 'X';
	cout << str << endl;
	
	str = "C style string 1";
	cout << "There are" << str.count('s')
	<<" 's' in the string\""
	<< str << '"' << endl;
	
	cout << "There are " << str.count("st")
	<< " 's' or 'y' in the string \""
	<< str << '"' << endl;
	
	MyString str2;
	cout << str2 << endl;
	
	str2 = str;
	cout << str2 << endl;
	
	str = "XXXXX";
	cout << str2 << "  " << str << endl;
	
	cout << "There are " << str.count('X')
	<< " 'X' in the string \""
	<< str << '"' << endl;
	
	str + 'y';
	cout << str << endl;
	
	str + "china";
	cout << str << endl;
	
	str = 'X';
	str + str2;
	cout << str << endl;
	
	
}
