#include<iostream>
#include<queue>
#include<unordered_map>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;
#define umap unordered_map
#define Graph umap<int,umap<int,int> >

int bfs(Graph &graph,int s,int t){
	queue<int> q;
	umap<int,int> pred,cap;
	cap[s] = INT_MAX;
	q.push(s);
	while(!q.empty() && cap.find(t)==cap.end()){
		int cur=q.front();q.pop();
		for(auto it=graph[cur].begin();it!=graph[cur].end();it++){
			if(cap.find(it->first)==cap.end() && it->second>0){
				cap[it->first] = min(it->second,cap[cur]);
				pred[it->first] = cur;
				q.push(it->first);
			}
		}
	}
	if(cap.find(t)!=cap.end()){
		for(int cur=t;cur!=s;cur=pred[cur]){
			graph[cur][pred[cur]] += cap[t];
			graph[pred[cur]][cur] -= cap[t];
		}
		return cap[t];
	}
	return 0;
}

int max_flow(Graph &graph,int m){
	int flow=0;
	while(1){
		int f = bfs(graph,1,m);
		if(f==0)return flow;
		flow+=f;
	}
}

void safeInsert(Graph &graph,int s,int t,int cap){
	if(graph.find(s)==graph.end()){
		umap<int,int> row;
		graph[s] = row;
	}
	graph[s][t] = cap;
	if(graph.find(t)==graph.end()){
		umap<int,int> row2;
		graph[t] = row2;
	}
	graph[t][s] = 0;
}

int main(){
	int n,m;
	while(cin>>n>>m){
		Graph graph;
		for(int i=0;i<n;i++){
			int s,t,c;cin>>s>>t>>c;
			safeInsert(graph,s,t,c);
		}
		cout<<max_flow(graph,m)<<endl;
	}
	return 0;
}