#include "vec.h"
#include<vector>

//创建一个n维的零向量
Vec::Vec(int n){
	if(n>0){
		int i =0;
		for(i;i<n;++i)
			data.push_back(0.0);
	}else{
		printf("Wrong, ndim must > 0\n");
	}
}

//gei xiangliang fuzhi
void init(const vector<float>& v) const{
	int idim = ndim();
	if(ndim() != v.size()){
		cerr<<"the numbers of the two vectors are not equal "<<endl;
		exit(1);
	}else{
		for(int i=0;i<idim;++i)
			data[i] = v[i];
	}
}

Vec Vec::add(const Vec& v){
	int idim = ndim();
	for(int i =0; i<idim;++i)
		data[i]+= v.data[i];
}

Vec Vec::multiply(float c) const{
	for(int i=0; i< ndim();i++)
		data[i]*=c;
}

float Vec::dot(const Vec& v) const{
	float s=0.0;
	for (int i=0; i< ndim();i++)
		s+=(data[i]*v.data[i]);
	return s;
}

float Vec::model() const{
	float s =0.0;
	for(int i=0; i< ndim();i++)
		s+=(data[i]*data[i]);
	return sqrt(s);
}

int Vec::ndim() const {
	return data.size();
}

float Vec::float getdim(int i) const{
	return data[i];
}

Vec Vec::operator+(const Vec& v) const{
	int idim = ndim();
	if(ndim() != v.ndim){
		cerr << "the numbers of the two vectors are not equal!"<<endl;
		exit(1);
	}
	
	vector<float> newdata(idim,0.0);
	for(int i=0; i<idim;++i)
		newdata[i] = getdim(i) + v.getdim[i];
	Vec newvec(idim);
	return newvec;
};