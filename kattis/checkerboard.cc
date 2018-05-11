#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long


ll total(vector<vector<ll> > &board,int mode0,int mode1){
	ll res = 0,rows=board.size(),cols = board[0].size();
	int impossible=0;
	vector<int> changed;
	for(ll i=0;i<rows;i++){
		for(ll j=0;j<cols;j++){
			ll up=0,left=0,lower;
			if(i>0)up=board[i-1][j];
			if(j>0)left=board[i][j-1];
			lower = max(up,left)+1;
			if(board[i][j]==0){
				if(rows>1 && cols>1){
					int mode=(((i+j)&1)==1)?mode1:mode0;
					ll mod;
					if(mode==1)mod=i&1;
					else mod=(i&1)^1;
					if((lower&1)!=mod)lower++;
				}
				board[i][j] = lower;
				changed.push_back(i*cols+j);
			}else if(board[i][j]<lower){
				impossible=1;
				break;
			}
			res+=board[i][j];
		}
		if(impossible)break;
	}
	while(!changed.empty()){
		ll r=changed.back()/cols,c=changed.back()%cols;
		changed.pop_back();
		board[r][c] = 0;
	}
	if(impossible)return -1;
	return res;
}

int main(){
	vector<vector<ll> > board;
	ll ans=-1;
	int n,m,mask0=3,mask1=3;cin>>n>>m;
	for(ll i=0;i<n;i++){
		vector<ll> row;
		for(ll j=0;j<m;j++){
			ll elem;cin>>elem;
			row.push_back(elem);
			if(elem>0 && n>1 && m>1){
				if((i+j)&1){
					if((i&1)^(elem&1))mask1&=2;
					else mask1&=1;
				}else{
					if((i&1)^(elem&1))mask0&=2;
					else mask0&=1;
				}
			}
		}
		board.push_back(row);
	}
	for(int i=mask0;i>0;i-=i&-i){
		for(int j=mask1;j>0;j-=j&-j){
			ll res = total(board,i&-i,j&-j);
			if(res!=-1){
				if(ans==-1)ans=res;
				else ans = res<ans?res:ans;
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}

