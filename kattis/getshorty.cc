#include<iostream>
#include<iomanip>
#include<queue>
#include<utility>
#include<vector>
#include<unordered_map>
using namespace std;
#define umap unordered_map
#define pq priority_queue

int main(){
	int n,m;
	while(true){
		cin>>n>>m;
		if(n==0 && m==0)break;
		umap<int,umap<int,float> > graph;
		vector<float> dist(n,0.0);
		dist[0] = 1.0;
		for(int i=0;i<n;i++){
			umap<int,float> neighs;
			graph[i] = neighs;
		}
		for(int i=0;i<m;i++){
			int left,right;
			float d;cin>>left>>right>>d;
			graph[left][right] = d;
			graph[right][left] = d;
		}
		pq<pair<float,int> > _queue;
		_queue.push(make_pair(1.0,0));
		while(!_queue.empty()){
			float d = _queue.top().first;
			int cur = _queue.top().second;
			_queue.pop();
			if(d==dist[cur]){
				for(auto it=graph[cur].begin();it!=graph[cur].end();it++){
					int neigh = it->first;
					float dd = it->second;
					if(d*dd>dist[neigh]){
						dist[neigh] = d*dd;
						_queue.push(make_pair(dist[neigh],neigh));
					}
				}
			}
		}
		cout<<fixed;
		cout<<setprecision(4)<<dist.back()<<endl;
	}
	return 0;
}