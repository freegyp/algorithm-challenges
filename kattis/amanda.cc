#include<iostream>
#include<cstdlib>
#include<vector>
#include<unordered_map>
#include<unordered_set>
using namespace std;
#define umap unordered_map
#define uset unordered_set

int bipartite(umap<int,umap<int,int> > &graph,uset<int> &cluster,int *airports,int node,int curVal){
	cluster.insert(node);
	airports[node] = curVal;
	for(auto it=graph[node].begin();it!=graph[node].end();it++){
		int neigh = it->first;
		if(airports[neigh]==-1){
			if(!bipartite(graph,cluster,airports,neigh,1-curVal))return 0;
		}else if(airports[neigh]==airports[node])return 0;
	}
	return 1;
}

int main(){
	int n,m;cin>>n>>m;
	int *airports = (int*)malloc(n*sizeof(int));
	umap<int,umap<int,int> > graph;
	for(int i=0;i<n;i++){
		airports[i] = -1;
		umap<int,int> neighs;
		graph[i] = neighs;
	}
	vector<int> stack;
	for(int i=0;i<m;i++){
		int left,right,c;
		cin>>left>>right>>c;
		left--;right--;
		graph[left][right] = c;
		graph[right][left] = c;
		if(c!=1){
			airports[left] = c/2;
			airports[right] = c/2;
			stack.push_back(left);
			stack.push_back(right);
		}
	}
	int possible = 1;
	while(!stack.empty()){
		int cur = stack.back();stack.pop_back();
		for(auto it=graph[cur].begin();it!=graph[cur].end();it++){
			int neigh = it->first,total = it->second;
			if(airports[neigh]==-1){
				if(total-airports[cur]<0){
					possible = 0;
					break;
				}else{
					airports[neigh] = total-airports[cur];
					stack.push_back(neigh);
				}
			}else if(airports[cur]+airports[neigh]!=total){
				possible = 0;
				break;
			}
		}
		if(!possible)break;
	}
	if(possible){
		int ans = 0;
		for(int i=0;i<n;i++){
			if(airports[i]>0)ans += airports[i];
		}
		uset<int> cluster;
		for(int i=0;i<n;i++){
			if(airports[i]==-1){
				cluster.clear();
				if(!bipartite(graph,cluster,airports,i,1)){
					possible = 0;
					break;
				}else{
					int ones = 0;
					for(int j:cluster){
						ones += airports[j];
					}
					ans += ones<(cluster.size()-ones)?ones:(cluster.size()-ones);
				}
			}
		}
		if(possible)cout<<ans<<endl;
		else cout<<"impossible"<<endl;
	}else{
		cout<<"impossible"<<endl;
	}
	return 0;
}