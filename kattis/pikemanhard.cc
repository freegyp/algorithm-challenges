#include<iostream>
#include<vector>
#include<unordered_map>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define ll long long
#define MOD 1000000007
#define umap unordered_map

int main(){
	int n;
	ll t,a,b,c,t0;
	cin>>n>>t>>a>>b>>c>>t0;
	vector<ll> loop;
	int *checked = (int*)malloc((c+1)*sizeof(int));
	for(int i=0;i<=c;i++)checked[i]=-1;
	ll ct=t0;
	while(checked[ct]<0 && loop.size()<n){
		checked[ct] = loop.size();
		loop.push_back(ct);
		ct = (a*ct+b)%c+1;
	}
	if(loop.size()==n){
		sort(loop.begin(),loop.end());
		vector<ll> cdf;
		ll pre=0,ans=0;
		for(ll tt:loop){
			if(pre+tt>t)break;
			cdf.push_back(pre+tt);
			pre += tt;
		}
		for(ll v:cdf){
			ans = (ans+v)%MOD;
		}
		cout<<cdf.size()<<" "<<ans<<endl;
	}else{
		int start = checked[ct],remain;
		umap<ll,ll> elemCounts;
		for(int i=0;i<start;i++)elemCounts[loop[i]] = 1;
		ll repeats = (n-start)/(loop.size()-start);
		for(int i=start;i<loop.size();i++)elemCounts[loop[i]] = repeats;
		remain = n-start-repeats*(loop.size()-start);
		for(int i=start;i<start+remain;i++)elemCounts[loop[i]]++;
		sort(loop.begin(),loop.end());
		ll pre=0,ans=0,totalCount=0;
		for(ll num:loop){
			if(pre+num*elemCounts[num]>t){
				ll _count = (t-pre)/num;
				if(_count>0)ans += (pre*2+(_count+1)*num)*_count/2;
				totalCount += _count;
				break;
			}else{
				ans += (pre*2+(elemCounts[num]+1)*num)*elemCounts[num]/2;
				ans %= MOD;
				pre += num*elemCounts[num];
				totalCount += elemCounts[num];
			}
		}
		cout<<totalCount<<" "<<ans<<endl;
	}
	return 0;
}
