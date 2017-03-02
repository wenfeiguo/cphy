#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stdlib.h>
#include <math.h>

using namespace std;

struct pdb{
	string name;
	string atom;
	string acid;
	int num;
	float site[3];
	char mass;
	float m;
	
	pdb();
	
	void creatpdb(string*);
};

pdb::pdb(){};

void pdb::creatpdb(string* words){
	name = words[0];
	atom = words[2];
	acid = words[3];
	const char* t = words[5].c_str();
	num = atoi(t);
	const char* x = words[6].c_str();
	const char* y = words[7].c_str();
	const char* z = words[8].c_str();
	site[0] = atof(x);
	site[1] = atof(y);
	site[2] = atof(z);
	mass = words[11][0];
	switch(mass){
		case 'C':
		m = 12.0;break;
		case 'N':
		m = 14.0;break;
		case 'O':
		m = 16.0;break;
		case 'S':
		m = 32.0;break;
	}
};

struct ATOM{
	string str = "ATOM";
	string acid;
	float mass,x,y,z;
};

float dist(int i, int j,vector<pdb>& oneline){
	return sqrt(((oneline[i]).site[0] - (oneline[j]).site[0])*((oneline[i]).site[0] - (oneline[j]).site[0])+
	((oneline[i]).site[1] - (oneline[j]).site[1])*((oneline[i]).site[1] - (oneline[j]).site[1])+
	((oneline[i]).site[2] - (oneline[j]).site[2])*((oneline[i]).site[2] - (oneline[j]).site[2]));
}

void HAR(vector<pdb>& oneline,char* outfile){
	int lines = oneline.size();
	ofstream output(outfile,ios::app);
	output.setf(ios::fixed, ios::floatfield);
	output.precision(2);
	for(int i=0;i<(lines-1);++i){
		if((oneline[i]).atom=="CA"){
			for(int j=i+1;j<lines;++j){
				if((oneline[j]).atom=="CA"){
					output<<"HAR\t"<<(oneline[i]).num<<"\t"<<(oneline[j]).num<<"\t100.0\t"
					<<dist(i,j,oneline)<<endl;
					break;
				}
			}
		}
	}
}

void LJ(vector<pdb>& oneline,char* outfile){
	int lines = oneline.size();
	ofstream output(outfile,ios::app);
	output.setf(ios::fixed, ios::floatfield);
	output.precision(2);
	vector<int> n;
	n.push_back(0);
	for(int i=1;i<lines;++i){
		if ((oneline[i-1]).num!=(oneline[i]).num)
			n.push_back(i);
	}
	//int lenth = n.size();
	n.push_back(lines);
	int lenth = n.size();
	int jout=0;
	int kout=0;
	int strength=0;
	for(int i=0;i<(lenth - 3);i++){
		for(int z=2;z<(lenth-i-1);z++){
		for(int j=n[i];j<n[i+1];j++){
			if((oneline[j]).atom=="CA"){
				jout = j;
			}
			for(int k=n[i+z];k<n[i+z+1];k++){
				if(dist(j,k,oneline)<5.0){
					strength++;
				}
				if((oneline[k]).atom=="CA"){
					kout = k;
				}
			}
		}
		if(strength!=0){
			output<<"LJ\t"<<(oneline[jout]).num<<"\t"<<(oneline[kout]).num<<"\t"
			<<strength<<".0\t"<<dist(jout,kout,oneline)<<endl;
		}else{
			output<<"REP\t"<<(oneline[jout]).num<<"\t"<<(oneline[kout]).num<<"\t"
			<<"1.0\t"<<"4.0\t"<<endl;
		}
		jout = kout = strength = 0;
		}
		/*for(int i=lenth-4;;i++){
			for(int j=n[i];j<n[i+1];j++){
				if((oneline[j]).atom=="CA"){
				jout = j;}
				for(int k=n[i+2];k<lines;k
				*/
	}
}
	
int main(){
	vector<pdb> oneline;
	pdb temp;
	map<int,float> total_m;
	char filename[50] = "1COA.pdb";
	ifstream input(filename);
	char outfile[50] = "output.txt";
	ofstream output(outfile);
	map<char,float> mass;
	if(!input) {
		cerr<<"error: can not open the file"<<endl;
		return -1;
	}
	//string words[20];
	string line;
	while (getline(input,line)){
		//if(trim(line).empty())
			//continue;
		int len = line.size();
		int j = 0;
		string words[20];
		for(int i =0;i<len;++i){
			if(line[i]=='\t'||line[i]==' '){
				if(line[i-1]=='\t'||line[i-1]==' ');
				else
					j++;
			}
			else
				words[j] = words[j] + line[i];
		}
		if(words[0]=="ATOM"){
			temp.creatpdb(words);
			oneline.push_back(temp);
			total_m[temp.num]+=temp.m;
		}
	}
	int lines = oneline.size();
	for(int i=0;i<lines;++i){
		if((oneline[i]).atom=="CA"){
		output<<(oneline[i]).name<<"\t"<<(oneline[i]).acid<<"\t"<<total_m[(oneline[i]).num]<<"\t"
		<<(oneline[i]).site[0]<<"\t"<<(oneline[i]).site[1]<<"\t"<<(oneline[i]).site[2]<<endl;
		}
	}
	HAR(oneline,outfile);
	LJ(oneline,outfile);
}