#ifndef VEC_H
#define VEC_H

struct Vec{
	vector<float> data;
	
	Vec(int);//构造函数
	void init(const vector<float>&) const;//初始化
	
	Vec add(const Vec&) const;//向量加法
	Vec multiply(float) const;//数乘向量
	float dot(const Vec&) const;//向量点积
	
	float model() const;//向量求模
	int ndim() const;//向量维数
	float getdim(int) const;//获得元素
	
	//算符重载
	Vec operator+(const Vec&) const;
	Vec operator*(float) const;
	float operator*(const Vec&) const;
	
	friend ostream& operator<<(ostream&, const Atom&);
};


#endif