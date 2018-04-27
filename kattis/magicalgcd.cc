#include<iostream>
#include<vector>
#include<utility>
#include<cstdlib>
#include<algorithm>
using namespace std;

long long gcd(long long a,long long b){
	while(b>0){
		long long c = a%b;
		a = b;
		b = c;
	}
	return a;
}

int main(){
	int tt;cin>>tt;
	while(tt--){
		int n;cin>>n;
		long long ans=0;
		vector<pair<long long,int> > divisors;
		for(int i=0;i<n;i++){
			vector<pair<long long,int> > _nexts,nexts;
			long long num;cin>>num;
			for(int j=0;j<divisors.size();j++){
				_nexts.push_back(make_pair(gcd(num,divisors[j].first),divisors[j].second));
			}
			_nexts.push_back(make_pair(num,i));
			sort(_nexts.begin(),_nexts.end());
			for(int j=0;j<_nexts.size();j++){
				if(nexts.size()==0 || _nexts[j].first!=nexts.back().first){
					nexts.push_back(_nexts[j]);
					ans = max(ans,_nexts[j].first*(i-_nexts[j].second+1));
				}
			}
			divisors = nexts;
		}
		cout<<ans<<endl;
	}
	return 0;
}