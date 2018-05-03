//Not accepted yet...
#include<iostream>
#include<unordered_set>
#include<cstdlib>
using namespace std;

#define uset unordered_set

int main(){
	int tt;cin>>tt;
	for(int t=1;t<=tt;t++){
		int n,k;cin>>n>>k;
		uset<int> blacklist;
		int *counts = (int*)malloc(sizeof(int)*(1<<n));
		for(int i=0;i<(1<<n);i++)counts[i]=0;
		for(int i=0;i<k;i++){
			int left,right;cin>>left>>right;
			blacklist.insert((1<<(left-1))|(1<<(right-1)));
		}
		for(int cur=1;cur<(1<<n);cur<<=1){
			counts[cur] = 1;
			for(int i=1;i<cur;i++){
				int j=i;
				while(j>0){
					if(blacklist.find((j&-j)|cur)==blacklist.end()){
						counts[cur|i] += counts[i];
					}
					j -= (j&-j);
				}
			}
		}
		cout<<"Case #"<<t<<": "<<counts[(1<<n)-1]<<endl;
	}
	return 0;
}