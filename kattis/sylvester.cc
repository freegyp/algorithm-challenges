#include<iostream>
using namespace std;
#define ll long long

int getHadValue(ll x,ll y,ll bound){
	if(x==0 && y==0)return 1;
	ll mid = bound>>1;
	if(x>=mid && y>=mid){
		return -getHadValue(x-mid,y-mid,mid);
	}else if(x>=mid){
		return getHadValue(x-mid,y,mid);
	}else if(y>=mid){
		return getHadValue(x,y-mid,mid);
	}else{
		return getHadValue(x,y,mid);
	}
}

int main(){
	int tt;cin>>tt;
	for(int t=0;t<tt;t++){
		ll n,x,y,w,h;cin>>n>>x>>y>>w>>h;
		for(ll j=y;j<y+h;j++){
			for(ll i=x;i<x+w;i++){
				ll bound = 1;
				while(i>=bound || j>=bound)bound <<= 1;
				cout<<getHadValue(i,j,bound)<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
	}
	return 0;
}