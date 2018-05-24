#include<iostream>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
	int n,m;cin>>n;
	int *cost = (int*)malloc(sizeof(int)*(n+1)),*table = (int*)malloc(sizeof(int)*30001);
	cost[0] = 0;
	for(int i=0;i<30001;i++)table[i] = -1;
	table[0] = n+1;
	for(int i=1;i<=n;i++){
		cin>>cost[i];
		for(int j=0;j<30001;j++){
			if(j+cost[i]<30001){
				if(table[j]==0)table[j+cost[i]]=0;
				else if(table[j]>0){
					if(table[j+cost[i]]<0)table[j+cost[i]]=i;
					else table[j+cost[i]]=0;
				}
			}
		}
	}
	for(int i=1;i<30001;i++){
		if(table[i-cost[table[i]]]==0)table[i]=0;
	}
	cin>>m;
	for(int i=0;i<m;i++){
		int total;cin>>total;
		if(table[total]<0)cout<<"Impossible"<<endl;
		else if(table[total]==0)cout<<"Ambiguous"<<endl;
		else{
			vector<int> elems;
			for(int j=total;j>0;j-=cost[table[j]]){
				elems.push_back(table[j]);
			}
			sort(elems.begin(),elems.end());
			for(int j:elems)cout<<j<<" ";
			cout<<endl;
		}
	}
	return 0;
}