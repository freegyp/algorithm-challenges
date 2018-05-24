#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
using namespace std;
#define umap unordered_map
#define ll long long
#define MOD 1000000007

int main(){
	int n;
	string famName;
	cin>>n>>famName;
	umap<string,ll> dic;
	for(int i=0;i<n;i++){
		string word;ll count;
		cin>>word>>count;
		dic[word] = count;
	}
	vector<ll> table(famName.size()+1,0);
	table[0] = 1;
	for(int i=0;i<famName.size();i++){
		if(table[i]>0){
			string cand;
			for(int j=i;j<famName.size();j++){
				cand.push_back(famName[j]);
				if(dic.find(cand)!=dic.end()){
					table[j+1] = (table[j+1]+table[i]*dic[cand])%MOD;
				}
			}
		}
	}
	cout<<table.back()<<endl;
	return 0;
}