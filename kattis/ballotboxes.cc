#include<iostream>
#include<vector>
using namespace std;

int main(){
	while(true){
		int n,b;cin>>n>>b;
		if(n==-1 && b==-1)break;
		vector<int> populations;
		for(int i=0;i<n;i++){
			int p;cin>>p;
			populations.push_back(p);
		}
		int lower=0,upper=5000000;
		while(upper-lower>1){
			int mid=(upper+lower)/2,demand=0;
			for(int p:populations){
				demand += p/mid;
				if(p%mid>0)demand++;
			}
			if(demand<=b)upper = mid;
			else lower = mid;
		}
		cout<<upper<<endl;
	}
	return 0;
}