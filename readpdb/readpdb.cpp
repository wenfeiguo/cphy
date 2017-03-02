#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stdlib.h>

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
	char t[20] = words[5].c_str();
	num = atoi(t);
	char x[20] = words[6].c_str();
	char y[20] = words[7].c_str();
	char z[20] = words[8].c_str();
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

int main(){
	vector<pdb> oneline;
	pdb temp;
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
			cout<<temp.name<<"	"<<(temp.site)[0]<<"	"<<temp.mass<<endl;
		}
	}
	
}