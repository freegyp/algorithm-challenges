#include<iostream>
#include<unordered_map>
using namespace std;
#define umap unordered_map

int main(){
	int tt;cin>>tt;
	for(int t=0;t<tt;t++){
		int n,cdf=0,ans=0;cin>>n;
		umap<int,int> preCount;
		preCount[0] = 1;
		for(int i=0;i<n;i++){
			int num;cin>>num;
			cdf += num;
			if(preCount.find(cdf-47)!=preCount.end()){
				ans += preCount[cdf-47];
			}
			if(preCount.find(cdf)==preCount.end())preCount[cdf]=0;
			preCount[cdf]++;
		}
		cout<<ans<<endl;
	}
	return 0;
}