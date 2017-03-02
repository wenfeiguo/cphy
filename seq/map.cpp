#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main(){
	string s;
	map<string,int> word_count;
	ifstream input("text.txt");
	if(!input) {
		cerr<<"error: can not open input file:"<<endl;
		return -1;
	}
	while (getline(input,s)){//每个字符串一行，所以直接读入一行也可，建议修改
		int n = s.size();
		char temp;
		for(int i = 0;i < n-1; ++i){
			if(s[i]>s[i+1]){
				temp = s[i];
				s[i] = s[i+1];
				s[i+1] = temp;
			}
		}
		++word_count[s];
	}
	map<string,int>::const_iterator map_it = word_count.begin();
	while(map_it != word_count.end()){
		cout<<map_it->first<<"occurs"<<map_it->second<<"times"<<endl;
		++map_it;
	}
}