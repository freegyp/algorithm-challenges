#include<iostream>
#include<cstdlib>
using namespace std;
#define ll long long

int main(){
	int n,q;cin>>n;
	ll *table = (ll*)malloc(sizeof(ll)*25001);
	for(int i=0;i<25001;i++){
		table[i] = 0;
	}
	for(int i=0;i<n;i++){
		int t;
		ll a,b;
		cin>>a>>b>>t;
		if(b==0){
			for(int j=0;j<25001;j++){
				if(j+t<=25000)table[j+t] = (table[j+t]>table[j]+a)?table[j+t]:(table[j]+a);
			}
		}else{
			ll dec=1;
			while(true){
				ll fun = a-b*(dec-1)*(dec-1);
				if(fun<=0)break;
				else{
					for(int j=25000;j>=t;j--){
						table[j] = table[j-t]+fun>table[j]?table[j-t]+fun:table[j];
					}
				}
				dec++;
			}
		}
	}
	cin>>q;
	for(int i=0;i<q;i++){
		int t;cin>>t;
		cout<<table[t]<<endl;
	}
	return 0;
}