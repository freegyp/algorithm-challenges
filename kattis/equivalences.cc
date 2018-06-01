//Not accepted yet.
#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
using namespace std;
#define umap unordered_map
#define uset unordered_set

int main(){
	int tt;cin>>tt;
	for(int t=0;t<tt;t++){
		int n,m;cin>>n>>m;
		umap<int,uset<int> > graph,rGraph;
		umap<int,int> order,group;
		for(int i=1;i<=n;i++){
			uset<int> neighs1,neighs2;
			graph[i] = neighs1;
			rGraph[i] = neighs2;
			order[i] = -1;
			group[i] = -1;
		}
		for(int i=0;i<m;i++){
			int left,right;cin>>left>>right;
			graph[left].insert(right);
			rGraph[right].insert(left);
		}
		int curOrder = 1;
		for(int i=1;i<=n;i++){
			vector<int> stack(1,i);
			while(!stack.empty()){
				int cur=stack.back();stack.pop_back();
				if(order[cur]>0)continue;
				order[cur] = curOrder++;
				for(int neigh:graph[cur]){
					if(order[neigh]<0){
						stack.push_back(neigh);
					}
				}
			}
		}
		vector<int> nodes(n,-1);
		for(auto it=order.begin();it!=order.end();it++){
			nodes[it->second-1] = it->first;
		}
		int groups=0;
		umap<int,int> gin,gout;
		for(int i:nodes){
			if(group[i]<0){
				vector<int> stack(1,i);
				while(!stack.empty()){
					int cur=stack.back();stack.pop_back();
					if(group[cur]>=0)continue;
					group[cur] = groups;
					for(int neigh:rGraph[cur]){
						if(group[cur]<0){
							stack.push_back(neigh);
						}
					}
				}
				gin[i] = 0;
				gout[i] = 0;
				groups++;
			}
		}
		if(groups==1){
			cout<<0<<endl;
		}else{
			for(int i=1;i<=n;i++){
				for(int j:graph[i]){
					if(group[i]!=group[j]){
						gin[group[j]]++;
						gout[group[i]]++;
					}
				}
			}
			int zin=0,zout=0;
			for(int i=0;i<groups;i++){
				if(gin[i]==0)zin++;
				if(gout[i]==0)zout++;
			}
			int ans = zin>zout?zin:zout;
			cout<<ans<<endl;
		}
	}
	return 0;
}