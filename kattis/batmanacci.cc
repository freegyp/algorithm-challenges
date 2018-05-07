#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define ll long long

int main(){
	vector<ll> fib(3,1);
	int n;ll k;
	cin>>n>>k;
	for(int i=3;i<=n;i++){
		ll cur = fib[i-1]+fib[i-2];
		if(cur>1000000000000000000)cur = 1000000000000000001;
		fib.push_back(cur);
	}
	while(n>=3){
		if(k<=fib[n-2]){
			n -= 2;
		}else{
			k -= fib[n-2];
			n--;
		}
	}
	if(n==2) cout<<"A"<<endl;
	else if(n==1) cout<<"N"<<endl;
	return 0;
}