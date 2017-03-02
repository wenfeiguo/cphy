#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>

using namespace std;

struct Vec{
	vector<float> data;
	
	Vec();//0参数构造函数
	void init(const float*, const int);//n参数初始化
	
	Vec add(const Vec&) const;//向量加法
	Vec multiply(float) const;//数乘向量
	float dot(const Vec&) const;//向量点积
	
	float model() const;//向量求模
	int ndim() const;//向量维数
	float getdim(int) const;//获得元素
	void output();//输出向量
	
	//算符重载
	void operator=(const Vec&);
	Vec operator+(const Vec&) const;
	Vec operator*(float) const;
	float operator*(const Vec&) const;
	
	//friend ostream& operator<<(ostream&, const Vec&);
};


//创建一个3维的零向量
Vec::Vec(){
	vector<float> tmp(3);
	data.swap(tmp);
}

//gei xiangliang fuzhi
void Vec::init(const float* a, const int n){//a[n]存储用于初始化的n个参数
	vector<float> tmp(n);
	for(int i=0;i<n;++i)
		tmp[i]=a[i];
	data.swap(tmp);
}

Vec Vec::add(const Vec& v) const{
	Vec v1;
	vector<float> tmp;
	int idim = v.ndim();
	for(int i =0; i<idim;++i)
		tmp.push_back(data[i] + v.data[i]);
	v1.data.swap(tmp);
	return v1;
}

Vec Vec::multiply(float c)const{
	Vec v1;
	vector<float> tmp;
	tmp = data;
	for(int i=0; i< ndim();i++)
		tmp[i]*=c;
	v1.data.swap(tmp);//连用两个.会不会有问题？
	return v1;
}

float Vec::dot(const Vec& v) const{
	float s=0.0;
	for (int i=0; i< (int)v.ndim();i++)
		s+=(data[i]*v.data[i]);
	return s;
}

float Vec::model() const{
	float s =0.0;
	for(int i=0; i< (int)ndim();i++)
		s+=(data[i]*data[i]);
	return sqrt(s);
}

int Vec::ndim() const {
	return data.size();
}

float Vec::getdim(int i) const{
	return data[i];
}

void Vec::output(){
	int idim = ndim();
	for(int i=0; i< idim; i++)
		cout<<data[i]<<endl;
}

Vec Vec::operator+(const Vec& v) const{
	int idim = ndim();
	if(ndim() != v.ndim()){
		cerr << "the numbers of the two vectors are not equal!"<<endl;
		exit(1);
	}
	
	vector<float> newdata(idim,0.0);
	for(int i=0; i<idim;++i)
		newdata[i] = getdim(i) + v.getdim(i);
	Vec newvec;
	newvec.data = newdata;
	return newvec;
}

void Vec::operator=(const Vec& v){
	data = v.data;
}

/*ostream& operator<<(ostream& os, Vec& v){//我也不知道这是干嘛的，就照着写了
	os<<v.data;
	return os;
}*/

int main(){
	float a[3] = {1.0,0,0};
	int i =3;
	Vec vec1;
	vec1.init(a,i);
	vec1.output();
	
	vec1 = vec1.add(vec1);
	vec1.output();
	
	float b = 2.0;
	vec1 = vec1.multiply(b);
	vec1.output();
	
}