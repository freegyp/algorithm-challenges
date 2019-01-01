#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
#define vint vector<int>
#define umap unordered_map
#define uimap umap<int,int>
#define uivmap umap<int,vector<int> >

vint toposort(uimap &neighs,uivmap &preds){
	vint stack,ans;
	for(auto it=neighs.begin();it!=neighs.end();it++){
		if(it->second ==0 )stack.push_back(it->first);
	}
	while(!stack.empty()){
		if(stack.size()>1){
			return ans;
		}
		int cur = stack.back();stack.pop_back();
		ans.push_back(cur);
		if(preds.find(cur)!=preds.end()){
			for(int pred:preds[cur]){
				neighs[pred]--;
				if(neighs[pred]==0)stack.push_back(pred);
			}
		}
	}
	return ans;
}

int main(){
	int n,k;cin>>n>>k;
	uimap neighs;
	uivmap preds;
	for(int i=0;i<n;i++){
		neighs[i] = 0;
		vint row;
		preds[i] = row;
	}
	for(int i=0;i<k;i++){
		int a,b;cin>>a>>b;
		preds[a].push_back(b);
		neighs[b]++;
	}
	vint ans = toposort(neighs,preds);
	if(ans.size()<n)cout<<"back to the lab"<<endl;
	else{
		for(int i=0;i<n;i++){
			if(i!=n-1)cout<<ans[i]<<" ";
			else cout<<ans[i]<<endl;
		}
	}
	return 0;
}