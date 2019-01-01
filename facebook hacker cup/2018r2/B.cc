#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
#define ll long long

ll bfs(int cur,vector<int>& stack,vector<int>& reqCount,vector<vector<int> >& children){
	if(reqCount[cur]>0){
		stack.push_back(cur);
	}
	ll ans=0;
}

int main(){
	int tt;cin>>tt;
	for(int t=1;t<=tt;t++){
		ll n,m,a,b;cin>>n>>m>>a>>b;
		vector<int> reqCount(n,0);
		vector<vector<int> > children;
		for(int i=0;i<n;i++){
			vector<int> row;
			children.push_back(row);
		}
	}
	return 0;
}