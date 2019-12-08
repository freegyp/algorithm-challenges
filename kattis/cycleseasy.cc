#include<bits/stdc++.h>
using namespace std;
#define MOD 9901
#define uset unordered_set
#define umap unordered_map

int safeCheck(umap<int,uset<int> > &dic,int x,int y){
	if(dic.find(x)==dic.end())return 0;
	if(dic[x].find(y)==dic[x].end())return 0;
	return 1;
}

int main(){
	int tt;cin>>tt;
	for(int t=1;t<=tt;t++){
		int n,k;cin>>n>>k;
		umap<int,uset<int> > taboos;
		for(int i=0;i<k;i++){
			int left,right;cin>>left>>right;
			left--;right--;
			if(taboos.find(1<<left)==taboos.end())taboos[1<<left] = uset<int>();
			taboos[1<<left].insert(1<<right);
			if(taboos.find(1<<right)==taboos.end())taboos[1<<right] = uset<int>();
			taboos[1<<right].insert(1<<left);
		}
		umap<int,umap<int,int> > table;
		for(int mask=1;mask<(1<<(n-1));mask++){
			table[mask] = umap<int,int>();
			if(mask==(mask&-mask)){
				table[mask][mask] = 1^safeCheck(taboos,mask,1<<(n-1));
			}else{
				for(int mask2 = mask;mask2>0;mask2-=mask2&-mask2){
					int out = mask2&-mask2;
					table[mask][out] = 0;
					int pre = mask^out;
					for(int mask3 = pre;mask3>0;mask3-=mask3&-mask3){
						int preOut = mask3&-mask3;
						if(!safeCheck(taboos,preOut,out)){
							table[mask][out] += table[pre][preOut];
							//table[mask][out] %= MOD;
						}
					}
				}
			}
		}
		int ans = 0;
		for(int i=1;i<(1<<(n-1));i<<=1){
			ans += (1^safeCheck(taboos,i,1<<(n-1)))*table[(1<<(n-1))-1][i];
			//ans %= MOD;
		}
		ans /= 2;
		ans %= MOD;
		cout<<"Case #"<<t<<": "<<ans<<endl;
	}
	return 0;
}