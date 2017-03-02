#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main(){
	char filename[50] = "test.txt";
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
		//cout<<line<<endl;
		if(trim(line).empty())
			continue;
		int len = line.size();
		int j = 0;
		string words[20];
		for(int i =0;i<len;++i){
			if(line[i]=='\t'||line[i]==' ')
				j++;
			else
				words[j] = words[j] + line[i];
		}
		if(words[0]=="ATOM"){
			cout<<line<<endl;
			output<<words[0]<<'	';
			if(words[3]=="CA"){
				output<<words[4]<<"\t"<<//其他信息可以直接输出没有影响，mass利用map输出
	}
}