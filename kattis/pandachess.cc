#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<cstdlib>
using namespace std;
#define ll long long
#define umap unordered_map
#define uset unordered_set

void safeInsert(umap<ll,uset<ll> > &graph,umap<ll,int> &pred,ll left,ll right){
	if(graph.find(left)==graph.end()){
		uset<ll> losers;
		graph[left] = losers;
	}
	if(graph[left].find(right)==graph[left].end()){
		if(pred.find(right)==pred.end())pred[right]=0;
		pred[right]++;
		graph[left].insert(right);
	}
}

int main(){
	int n,m,d;
	umap<ll,uset<ll> > graph;
	umap<ll,int> pred,order;
	cin>>n>>m>>d;
	for(int i=0;i<m;i++){
		ll left,right;cin>>left>>right;
		safeInsert(graph,pred,left,right);
	}
	vector<ll> stack;
	for(auto it=graph.begin();it!=graph.end();it++){
		if(pred.find(it->first)==pred.end()){
			stack.push_back(it->first);
			order[it->first] = 1;
		}
	}
	while(!stack.empty()){
		ll cur=stack.back();stack.pop_back();
		if(graph.find(cur)==graph.end())continue;
		for(ll neigh:graph[cur]){
			if(order.find(neigh)==order.end() || order[cur]+1>order[neigh]){
				order[neigh] = order[cur]+1;
			}
			pred[neigh]--;
			if(pred[neigh]==0){
				stack.push_back(neigh);
			}
		}
	}
	int *BIT = (int*)malloc((n+1)*sizeof(int));
	for(int i=0;i<=n;i++)BIT[i]=0;
	for(int i=0;i<n;i++){
		ll ic;cin>>ic;
		if(order.find(ic)!=order.end()){
			int idx = order[ic],pre=0;
			for(int j=idx-1;j>0;j-=j&-j){
				pre = pre>BIT[j]?pre:BIT[j];
			}
			for(int j=idx;j<=n;j+=j&-j){
				BIT[j] = BIT[j]>(pre+1)?BIT[j]:(pre+1);
			}
		}
	}
	int maxOrder=0;
	for(int i=n;i>0;i-=i&-i){
		maxOrder = maxOrder>BIT[i]?maxOrder:BIT[i];
	}
	cout<<(n-maxOrder)*2<<endl;
	return 0;
}
