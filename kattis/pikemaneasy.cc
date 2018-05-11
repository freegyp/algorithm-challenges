#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define MOD 1000000007

int main(){
	int n;
	ll t0,t,a,b,c;
	vector<ll> times,endTimes;
	cin>>n>>t>>a>>b>>c>>t0;
	times.push_back(t0);
	for(int i=1;i<n;i++){
		times.push_back((a*times.back()+b)%c+1);
	}
	sort(times.begin(),times.end());
	ll pre=0,ans=0;
	for(ll tt:times){
		if(pre+tt>t)break;
		endTimes.push_back(pre+tt);
		pre += tt;
	}
	cout<<endTimes.size()<<" ";
	for(ll tt:endTimes){
		ans = (ans+tt)%MOD;
	}
	cout<<ans<<endl;
	return 0;
}