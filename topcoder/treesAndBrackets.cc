#include<iostream>
#include<string>
#include<vector>
using namespace std;

class TreesAndBrackets{
public:
	string check(string t1, string t2){
		vector<int> v1(1,0),v2(1,0);
		for(int i=0;i<t1.size();i++){
			if(t1[i]=='(')v1.push_back(v1[v1.size()-1]+1);
			else v1.push_back(v1[v1.size()-1]-1);
		}
		for(int i=0;i<t2.size();i++){
			if(t2[i]=='(')v2.push_back(v2[v2.size()-1]+1);
			else v2.push_back(v2[v2.size()-1]-1);
		}
		int j=0;
		for(int i=0;i<v1.size();i++){
			if(j<v2.size() && v1[i]==v2[j])j++;
		}
		if(j==v2.size())return "Possible";
		else return "Impossible";
	}
};